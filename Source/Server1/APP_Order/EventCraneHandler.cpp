#include "EventCraneHandler.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"


using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;


EventCraneHandler::EventCraneHandler(void)
{
	
}

EventCraneHandler::~EventCraneHandler(void)
{

}

void EventCraneHandler::OrderCmdStatusRcv(string strValue, string logFileName)
{
	LOG log("EventCraneHandler::OrderCreateReq",logFileName);
	try
	{
		log.Info()<<"OrderCmdStatusRcv  start........."<<endl;

		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 4)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string strOrderNO = kValues[0];//指令号
		string strCmdSeq = kValues[1];//作业次数序号
		string strCmdStatus = kValues[2];//状态
		string strCurWgt = kValues[3];//当次作业量

		log.Info()<<"strOrderNO = "<<strOrderNO<<endl;
		log.Info()<<"strCmdSeq = "<<strCmdSeq<<endl;
		log.Info()<<"strCmdStatus = "<<strCmdStatus<<endl;
		log.Info()<<"strCurWgt = "<<strCurWgt<<endl;

		long orderNO = StringHelper::ToNumber<long>(strOrderNO);
		long cmdSeq = StringHelper::ToNumber<long>(strCmdSeq);
		string cmdStatus = strCmdStatus;
		long curWgt = StringHelper::ToNumber<long>(strCurWgt);

		OrderQueueBase orderQueueInfo;
		SQL4Order::SelOrderQueueInfo(orderNO, orderQueueInfo);
		orderQueueInfo.logOutValues();

		string tagName = "";
		string tagValue = "";

//==================================cmdStatus == "F"============================================================

		//20220818 zhangyuhong add
		//新增状态cmsStatus=F  当收到F时,认为指令执行完毕
		// 情况一：当吊运物料放到车上后，如果重量达标，认为是指令完成，发送F
		// 情况二：当吊运物料放到料格内后，行车再次扫描卸料区，激光反馈无料可吊，认为是指令完成，发送F
		if (cmdStatus == "F")
		{
			log.Info()<<"Enter cmdstatus = F  handle......................................................"<<endl;
			//删除uacs_order_queue表中的记录
			log.Info()<<"1....DelOrderQueue"<<endl;
			SQL4Order::DelOrderQueue(orderNO);

			//更新uacs_order_data表中记录的order_status为已完成=3
			log.Info()<<"2....UpdOrderDataStatus"<<endl;
			SQL4Order::UpdOrderDataStatus(orderNO, "3");

			//如果是入库指令 ：结束，不再更新重量
			//如果是L3 电炉指令：更新order_data表中的重量  更新库图重量
			log.Info()<<"3.....orderType = "<<orderQueueInfo.getOrderType()<<endl;

			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				//通知L3电文  HCP411 单品种废钢进出二炼钢废钢堆场装卸信息
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE，WORK_STATUS,  WORK_TIME
				vector<string> vecMsg;
				vecMsg.push_back("I");//新增
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("2");//卸车
				vecMsg.push_back("5");//归堆结束
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

				//归堆结束，删除车辆信息绑定表
				SQL4Order::DelParkingCarBandInfo(orderQueueInfo.getPlanNO());

				//通知车辆模块 更新停车位状态表为 归堆完成，即是重新为 100（后续有可能还有扫地需求  具体业务逻辑现场调试时确定）
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=停车位号,状态
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//停车位号就是 orderQueueInfo 中的fromStockNO
				string parkingNO = orderQueueInfo.getFromStockNO();
				string workStatus = "305";//归堆完成 是 305 
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);

			}

			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 )
			{
				//更新order_data表中的重量
				SQL4Order::UpdOrderDataWgt(orderNO, curWgt);				
				//更新库图
				//电炉装车 或 L3装车 ，料格号就是fromstockNO
				//在起吊后就更新库图
				//SQL4Order::UpdYardMapMatWgt(orderQueueInfo.getFromStockNO(), curWgt, "-");

				//通知L3电文  HCP411 单品种废钢进出二炼钢废钢堆场装卸信息
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE，WORK_STATUS,  WORK_TIME
				vector<string> vecMsg;
				vecMsg.push_back("I");//新增
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("1");//装车
				vecMsg.push_back("F");//最后一吊装车结束
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				//20220825 补个重量
				vecMsg.push_back(strCurWgt);
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

				//通知parking模块 更新  UACS_PARKING_WORK_STATUS 中的停车位状态为 装车结束-206
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=停车位号,状态
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//停车位号就是 orderQueueInfo 中的toStockNO
				string parkingNO = orderQueueInfo.getToStockNO();
				string workStatus = "206";//装车完成 是 206 
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);
				

				//通知PARKING模块车辆可以离开  此时吊具可能没有起升  放到另外的状态再通知
				//通知功能由Parking模块自己完成

			}

			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
			{
				//组织EVtag数据 通知电炉L2模块装车实绩
				vector<string> vecMsg;
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back(StringHelper::ToString(orderQueueInfo.getPlanDetailID()));
				vecMsg.push_back(orderQueueInfo.getFromStockNO());
				vecMsg.push_back(orderQueueInfo.getMatCode());
				vecMsg.push_back(orderQueueInfo.getCompCode());
				vecMsg.push_back(strCurWgt);
				vecMsg.push_back("1");//最后一吊
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_EAFL2_ORDER_ZCSJ";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

				//通知parking模块 更新  UACS_PARKING_WORK_STATUS 中的停车位状态为 装车结束-206
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=停车位号,状态
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//停车位号就是 orderQueueInfo 中的toStockNO
				string parkingNO = orderQueueInfo.getToStockNO();
				string workStatus = "206";//装车完成 是 206 
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);
				
			}
		}

//==================================cmdStatus == "0"============================================================

		//根据cmdStatus对 uacs_order_queue  uacs_order_data进行更新
		if (cmdStatus == "0")//取消指令，行车本来有指令，切成手动后，指令丢弃
		{
			log.Info()<<"Enter cmdstatus = 0  handle......................................................"<<endl;
			//指令取消：只有当行车空钩升起一定高度，且载荷称重（或其它标准判断）小于某误差范围内时，才可丢弃
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
			//如果是第1吊运就取消，则uacs_order_data中指令状态恢复为1-生成
			if (cmdSeq = 1)
			{
				SQL4Order::UpdOrderDataStatus(orderNO, "1");
			}
		}

//==================================cmdStatus == "1"============================================================

		if (cmdStatus == "1")//获取指令
		{
			log.Info()<<"Enter cmdstatus = 1  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
			SQL4Order::UpdOrderDataStatus(orderNO, "2");

			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE，WORK_STATUS,  WORK_TIME
				vector<string> vecMsg;
				vecMsg.push_back("I");//新增
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("2");//卸车
				vecMsg.push_back("4");//归堆开始
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

				//通知车辆模块 更新停车位状态表为 归堆开始，
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=停车位号,状态
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//停车位号就是 orderQueueInfo 中的fromStockNO
				string parkingNO = orderQueueInfo.getFromStockNO();
				string workStatus = "304";//归堆开始是 304 
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);

			}

			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 )
			{
				//通知L3电文  HCP411 单品种废钢进出二炼钢废钢堆场装卸信息
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE，WORK_STATUS,  WORK_TIME
				//L3的装车开始  不用发送 HCP411
				
				//通知parking模块 更新  UACS_PARKING_WORK_STATUS 中的停车位状态为 装车结束-206
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=停车位号,状态
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//停车位号就是 orderQueueInfo 中的toStockNO
				string parkingNO = orderQueueInfo.getToStockNO();
				string workStatus = "205";//装车完成 是 205
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);

			}

			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
			{

				//电炉子计划表中的 状态 已启动  由 车辆到达事件来更新

				//通知parking模块 更新  UACS_PARKING_WORK_STATUS 中的停车位状态为 装车结束-206
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=停车位号,状态
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//停车位号就是 orderQueueInfo 中的toStockNO
				string parkingNO = orderQueueInfo.getToStockNO();
				string workStatus = "205";//装车开始 是 205
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);

			}
		}

//==================================cmdStatus == "2"============================================================

		if (cmdStatus == "2")//到取料位上方
		{
			log.Info()<<"Enter cmdstatus = 2  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}

//==================================cmdStatus == "3"============================================================

		if (cmdStatus == "3")//吊具空载下降到位
		{
			log.Info()<<"Enter cmdstatus = 3  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}

//==================================cmdStatus == "4"============================================================

		if (cmdStatus == "4")//吊具有载荷重量
		{
			log.Info()<<"Enter cmdstatus = 4  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);


			//根据指令类型 
			//1. L3装车
			// 更新料格物料存量减少
			//2. 电炉装车
			// 更新料格物料存量减少
			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
				  orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
			{
				//
				SQL4Order::UpdYardMapMatWgt(orderQueueInfo.getFromStockNO(), curWgt, "-");
			}

			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				//
			}

		}

//==================================cmdStatus == "5"============================================================

		if (cmdStatus == "5")//吊具重载上升到位
		{
			log.Info()<<"Enter cmdstatus = 5  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}
//==================================cmdStatus == "6"============================================================

		if (cmdStatus == "6")//吊具重载到放下位
		{
			log.Info()<<"Enter cmdstatus = 6  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}

//==================================cmdStatus == "6"============================================================

		if (cmdStatus == "7")//吊具重载下降到位
		{
			log.Info()<<"Enter cmdstatus = 7  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}

//==================================cmdStatus == "6"============================================================

		if (cmdStatus == "8")//吊具载荷重量消失  非最后一次吊运
		{
			log.Info()<<"Enter cmdstatus = 8  handle......................................................"<<endl;
			//注意8状态时，curWgt来自行车模块时,这个值需要用cranePlcStatus_Last才可以
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
			SQL4Order::UpdOrderQueueWgt(orderNO, curWgt);//累加重量//放下的时候  认为是作业完成 才累加重量
			SQL4Order::UpdOrderDataWgt(orderNO, curWgt);

			//根据指令类型 
			//1. L3卸料
			//更新库图物料存量增加
			//更新L3计划表中的craneWgt
			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				SQL4Order::UpdYardMapMatWgt(orderQueueInfo.getToStockNO(), curWgt, "+");

				//L3 卸料入库 归堆重量
				//通知L3 rcv tag点 更新  uacs_L3_MAT_IN_OUT_INFO 中crane_wgt
				//通过tag点  更新
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE，WORK_STATUS,  WORK_TIME,重量
				vector<string> vecMsg;
				vecMsg.push_back("I");//新增
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("2");//卸料
				vecMsg.push_back("8");//
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				//20220825 补个重量
				vecMsg.push_back(strCurWgt);
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

			}

			//2. L3装车
			// 更新uacs_L3_MAT_IN_OUT_INFO 中crane_wgt
			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21)
			{
				//在车上放料  更新 uacs_L3_MAT_IN_OUT_INFO 中crane_wgt
				//通知L3 rcv tag点 更新  uacs_L3_MAT_IN_OUT_INFO 中crane_wgt
				//通过tag点  更新
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE，WORK_STATUS,  WORK_TIME,重量
				vector<string> vecMsg;
				vecMsg.push_back("I");//新增
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("1");//卸料
				vecMsg.push_back("8");//
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				//20220825 补个重量
				vecMsg.push_back(strCurWgt);
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);
				
			}



			//3. 电炉装车
			//发送装车实绩tag点给电炉模块
			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
			{
				//在车上放料  更新 uacs_eaf_l2_plan_detail 中crane_wgt
				//通知eafL2模块  tag点 更新  uacs_eaf_l2_plan_detail 中crane_wgt
				//tagname=EV_EAFL2_ORDER_ZCSJ
				//tagvalue=计划号,子计划号,料格号,物料代码,钢制码,吊放重量,是否最后一吊标记  0-不是 1-是
				//组织EVtag数据 通知电炉L2模块装车实绩
				vector<string> vecMsg;
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back(StringHelper::ToString(orderQueueInfo.getPlanDetailID()));
				vecMsg.push_back(orderQueueInfo.getFromStockNO());
				vecMsg.push_back(orderQueueInfo.getMatCode());
				vecMsg.push_back(orderQueueInfo.getCompCode());
				vecMsg.push_back(strCurWgt);
				vecMsg.push_back("0");//不是最后一吊
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_EAFL2_ORDER_ZCSJ";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

			}

			
		


		}

		if (cmdStatus == "9")//吊具空载上升到位
		{
			log.Info()<<"Enter cmdstatus = 9  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}
		

		


	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
}


string EventCraneHandler::GetStrMsg(vector<string> vecStr, string splitFlag)
{
	LOG log("EventCraneHandler::GetStrMsg",AUTO_CATCH_PID);
	string strMsg = "";
	int nCount = 0;
	try
	{
		vector<string>::iterator itor;
		for (itor = vecStr.begin(); itor != vecStr.end(); itor ++)
		{
			if (nCount > 0)
			{
				strMsg += splitFlag;
			}
			if (*itor == "")
			{
				strMsg += "@";
			}
			else
			{
				strMsg += *itor;
			}
			nCount ++;
		}
		return strMsg;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return strMsg;
}


bool EventCraneHandler::EVTagSnd(string tagName, string tagValue)
{
	string functionName="EventCraneHandler :: EVTagSnd()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		iPlature::TAGVALUEMAP tagPairs;
		log.Info()<<"eventPut tagName="<<tagName<<"    tagValue="<<tagValue<<endl;
		Tag::GetInst().EventPut(tagPairs,tagName,tagValue);
		ret=true;
		return ret;
	}
	catch(...)
	{
		log.Debug()<<"EVTagSnd  error..........."<<endl;
	}
	return ret;
}