#include "EventGateHandler.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "MsgWG01.h"


using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

const  string EventGateHandler::EXTER_SYSTEM_BOF = "LG";//
const  string EventGateHandler::EXTER_SYSTEM_EAF = "DL";//

const  long EventGateHandler::MPE_WGT = 100;//

EventGateHandler::EventGateHandler(void)
{
}

EventGateHandler::~EventGateHandler(void)
{
}

//道闸识别车牌号处理
void EventGateHandler::CarArriveGateHandler(string strValue, string logFileName)
{
	LOG log("EventGateHandler::CarArriveGateHandler",logFileName);
	try
	{
		log.Info()<<"start........."<<endl;
		//1.解析tag值字符串
		//EV格式：车号,道闸编号
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string carNO = kValues[0];//车号
		string gateNO = kValues[1];//道闸号 
		log.Info()<<" carNO = "<<carNO<<" , gateNO = "<<gateNO<<endl;

		//1.如果有车辆已经在库区内作业，报警退出
		if (true == SQL4Parking::CarEnterYardExist(carNO))
		{
			log.Info()<<"carNO = "<<carNO<<" has  ENTER into yard  and  not leave yet,  return.................."<<endl;
			//组织报警提示信息发给道闸led屏
			//发送内容：车号XXX，已经在库区！
			//https协议接口，具体实现方式待定
			return;
		}

		//2.如果没有对应计划,报警退出
		CarPlanBandInfo carPlanBandInfoBase;
		//选择规则:
		//按照车号选择, 按照bandtime从早到晚排序,选第一个
		if (false == SQL4Parking::SelCarPlanBandInfo(carNO, carPlanBandInfoBase))
		{
			log.Info()<<"carNO = "<<carNO<<" has  NO PLAN,  return.................."<<endl;
			//组织报警提示信息发给道闸led屏
			//发送内容:车号XXX，没有计划！
			//https协议接口，具体实现方式待定
			return;
		}
		//打印获取到的车辆绑定信息
		carPlanBandInfoBase.logOutValues();

		//初始化车辆计划绑定信息表中目的料格号道闸号停车位号的信息
		SQL4Parking::InitGateGridParking(carNO, carPlanBandInfoBase.getPlanNO());
		
		//L3计划
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_L3)
		{
			//1.对L3计划来说,获取取料料格  或 放料料格编号  
			//2.根据此料格编号获取对应跨号 
			//3.如果跨号和道闸对应跨号一致  ，且能找到对应空闲停车位（按照大车距离从近到远排列的空闲车位），放行，更新车辆计划信息绑定表中的 道闸号 ，更新目的料格号
			//4.如果跨号和道闸不一致, 报警提示:  应该去XX跨，当前跨为XXX  更新此记录道闸号  、目的料格号为空
			//5.如果跨号一致,但是没有空闲停车位, 报警提示: 当前跨无空闲停车位  
			string locCode = "";
			string matCode = "";
			string compCode = "";
			long reqWgt = DF_INT_NULL;
			//==================对是否有计划判断==================================================
			if (false == SQL4Parking::SelScrapCodeReqWgtFormL3(carPlanBandInfoBase.getPlanNO(), 
																												carPlanBandInfoBase.getWorkType(), 
																												locCode, 
																												matCode, 
																												compCode, 
																												reqWgt))
			{
				//L3没有计划，退出
				log.Info()<<"carNO = "<<carNO<<" ,  SelScrapCodeReqWgtFormL3   error,  return.................."<<endl;
				//发送道闸LED屏内容：车号XXX，无计划
				//todo
				return;
			}
			log.Info()<<"locCode = "<<locCode<<" , matCode = "<<matCode<<" , compCode = "<<compCode<<" , reqWgt = "<<reqWgt<<endl;
			//================================================================================

			//================对道闸和计划中道闸是否一致判断============================================
			string bayNO = "";
			string tempGateNO = "";
			if (false == SQL4Parking::SelBayNOGateNOByGridNO(locCode, bayNO, tempGateNO))
			{
				//没有道闸和跨对应关系 退出
				log.Info()<<"carNO = "<<carNO<<" ,  SelBayNOGateNOByGridNO   error,  return.................."<<endl;
				return;
			}
			if (gateNO != tempGateNO)
			{
				//当前道闸和计划中要去的料格道闸不符，退出
				log.Info()<<"carNO = "<<carNO<<" ,  gateNO != tempGateNO   error,  return.................."<<endl;
				//发送道闸LED屏内容：车号XXX，应去XX跨，当前为XX跨
				//todo
				return;
			}
			//================================================================================

			//=================对L3给的料格信息对应的物料和 WMS系统的料格信息对应物料是否一致进行判断，包括钢制码======
			string wmsMatCode = "";
			string wmsCompCode = "";
			long wmsMatWgt = DF_INT_NULL;
			if (false == SQL4Parking::SelGridInfoByGridNO(locCode, wmsMatCode, wmsCompCode, wmsMatWgt))
			{
				//要去的料格在WMS中不存在，退出
				log.Info()<<"SelMatCompCodeByGridNO   error,  return.................."<<endl;
				return;
			}
			if (matCode  == wmsMatCode && compCode == wmsCompCode)
			{
			}
			else
			{
				//要去的料格在WMS中所放物料和钢制码与L3的不符，退出
				log.Info()<<"matCode = "<<matCode<<" ,  wmsMatCode = "<<wmsMatCode<<" ;  compCode = "<<compCode<<" ,wmsCompCode = "<<wmsCompCode<<" ,  return.................."<<endl;
				//发送道闸LED屏内容：车号XXX，应去XX料格，此料格所存物料和L3不符
				//todo
				return;
			}
			//================================================================================

			//================如果是装车，进行库存是否足够判断==========================================
			if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC && wmsMatWgt < reqWgt && abs(wmsMatWgt - reqWgt) > 100)
			{
				//要去的料格在WMS中所放物料量不满足L3要求装车量，退出
				log.Info()<<"gridNO = "<<locCode<<" ,  wmsMatWgt = "<<wmsMatWgt<<" , reqWgt = "<<reqWgt<<" ,  NOT  REACHE L3 NEED REQWGT,  return.................."<<endl;
				//发送道闸LED屏内容：车号XXX，所去XX料格，此料格物料存量不满足作业需求
				//todo
			}
			//================================================================================

			//===========================对要去料格对应的停车位是否空闲进行判断===========================
			string workStatus = "";
			string parkingNO = "";
			if (false == SQL4Parking::SelPKStatusByGridNO(locCode, parkingNO, workStatus))
			{
				//要去的料格对应停车位在WMS中不存在，退出
				log.Info()<<"SelPKStatusByGridNO   error,  return.................."<<endl;
				return;
			}
			if (workStatus != "100")
			{
				log.Info()<<"workStatus = "<<workStatus<<"  ,  NOT FREE,  return.................."<<endl;
				//发送道闸LED屏内容：车号XXX，所去料格对应停车位正在作业，不可进入
				//todo
				return;
			}
			//===============================================================================

			//以下是可以进入处理：
			//1.更新车辆计划绑定表:道闸号,目的料格号,目的停车位号
			SQL4Parking::UpdGateGridPKByCarPlan(carNO, carPlanBandInfoBase.getPlanNO(), gateNO, locCode, parkingNO);


			//向L3发送电文HCP411 ：单品种废钢进出二炼钢废钢堆场装卸信息
			//	操作标记（I:新增  D:删除),流水号(也就是L3计划号) ,类型(1:装车  2:卸料)，作业状态(1:车辆入场;2:车到料格;3:车离开;4:归堆开始;5:归堆结束;)，作业时刻(yyyymmddhh24miss)
			iDA::DateTime dtNow = iDA::DateTime::Now();
			string tagName = "EV_L3MSG_SND_HCP411";
			string tagValue = "I," + carPlanBandInfoBase.getPlanNO() + "," + workTypeConvert(carPlanBandInfoBase.getWorkType()) + ",1," + dtNow.ToShortTimeString();
			EVTagSnd(tagName, tagValue);



			//向道闸系统发送同意进入信号：准许进入，
			//todo
			//发送道闸LED屏内容：车号XXX，去料格XX执行装车/卸料作业
			//todo

			log.Info()<<"CAR = "<<carNO<<" is arrive gate success..............................................."<<endl;
			return;
		}

		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_EAF)
		{
			//1.对电炉计划来说，获取电炉计划子表的对应的scrapCode
			//2.根据此道闸编号获取对应跨号
			//3.根据此跨号找出是否此跨内的matCode存量可否满足（按照料格存量从大到小排列），如果满足，放行，找出存量最大的料格作为目的料格；
			//4.如果不满足，按照电炉配料间另一个跨查询跨内matCode存量是否满足(按照料格存量从大到小排列), 如果满足, 提示:应该去XX跨，当前跨为XXX，废钢存量不足  如果还不满足，提示：两个跨废钢存量均不足
			//5.不满足的情况下，更新此记录道闸号  、目的料格号为空
			string scrapCode = "";
			long reqWgt = DF_INT_NULL;
			if (false == SQL4Parking::SelScrapCodeReqWgtFromEAF(carPlanBandInfoBase.getPlanNO(), carPlanBandInfoBase.getPlanDetailID(), scrapCode, reqWgt))
			{
				log.Info()<<"carNO = "<<carNO<<" ,  SelScrapCodeReqWgtFromEAF   error,  return.................."<<endl;
				return;
			}
			string bayNO = "";
			if (false == SQL4Parking::SelBayNOByGateNO(gateNO, bayNO))
			{
				log.Info()<<"carNO = "<<carNO<<" ,  SelBayNOByGateNO   error,  return.................."<<endl;
				return;
			}
			string targetGridNO = "";
			long falseReason = 0;
			string targetParkingNO = "";
			if (false == SQL4Parking::SelGridNOMatchScrapCode2(bayNO, scrapCode, reqWgt, EventGateHandler::EXTER_SYSTEM_EAF, targetGridNO, targetParkingNO, falseReason))
			{
				log.Info()<<"carNO = "<<carNO<<" ,  SelGridNOMatchScrapCode2   error, falseReason = "<<falseReason<<" , return.................."<<endl;		
				if (falseReason == 1)
				{
					//提示本跨对应无空闲停车位，
					//发送提示到LED屏:  车号XXX，无空闲停车位
					//todo
				}
				if (falseReason == 2)
				{
					//提示本跨对应物料库存不足，
					//发送提示到LED屏:  车号XXX，需作业物料本跨库存不足
					//todo
				}				
				return;
			}

			//通过检查，可以进入
			//更新车辆计划绑定表中的 目的料格号和 道闸号
			SQL4Parking::UpdGridGateByCarNOPlanNOPlanDetailID(carNO, carPlanBandInfoBase.getPlanNO(), carPlanBandInfoBase.getPlanDetailID(), targetGridNO, gateNO, targetParkingNO);

			//20220520 zhangyuhong add
			//增加：向电炉L2发送“配料装车启动电文”tag点
			//tag点名称：EV_EAFL2_PARKING_CAR_ARRIVE
			//格式 : PONO,DETAIL_ID
			string tagName = "EV_EAFL2_PARKING_CAR_ARRIVE";
			string tagValue = carPlanBandInfoBase.getPlanNO() + "," + StringHelper::ToString(carPlanBandInfoBase.getPlanDetailID());
			EVTagSnd(tagName, tagValue);


			//向道闸系统LED屏发送：
			//车号XXX，去料格XXX进行装车作业
			//todo

			//向道闸系统发送同意进入信号：准许进入，去料格号：locCode  
			//todo

		}

		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_BOF)
		{
			//1.对转炉计划来说，事先是没有车辆计划绑定的，所以需要先绑定计划  而且这个计划一定是固定的备用计划 
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


//道闸抬杆处理
void EventGateHandler::CarEnterGateHandler(string strValue, string logFileName)
{
	LOG log("EventGateHandler::CarEnterGateHandler",logFileName);
	try
	{
		log.Info()<<"start........."<<endl;
		//1.解析tag值字符串
		//EV格式：车号,道闸编号
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string carNO = kValues[0];//车号
		string gateNO = kValues[1];//道闸号 
		log.Info()<<" carNO = "<<carNO<<" , gateNO = "<<gateNO<<endl;
		
		//根据车号，道闸号  获取指定记录,如果没记录,报警退出(没有记录的可能是, 道闸识别成功,且WMS可以放行，但是道闸没提竿，此时车辆换了一个跨道闸，此时就不通过了，然后就会清空道闸号)
		//如果有记录，根据绑定更新ENTER_FLAG=2 说明已经进入
		//从车辆计划绑定信息表中，获取目的料格编号,通知料格管理系统
		string carType = "";
		string targetGridNO = "";
		string targetParkingNO = "";
		string workType = "";
		string planNO = "";
		string planSrc = "";
		long planDetailID = DF_INT_NULL;
		if (false == SQL4Parking::SelTargetGridNO(carNO, 
																					gateNO, 
																					carType, 
																					targetGridNO, 
																					targetParkingNO, 
																					workType, 
																					planNO, 
																					planSrc, 
																					planDetailID))
		{
			log.Info()<<"carNO = "<<carNO<<" SelTargetGridNO ERROR  , return.................."<<endl;
			return;
		}

		//以下准备更新相关表

		//1.更新车辆计划绑定表，UACS_PARKING_CAR_PLAN_INFO   进入标志=2 
		SQL4Parking::UpdEnterFlag2Enter(carNO, gateNO);

		//2.更新停车位状态表，UACS_PARKING_WORK_STATUS  处理号，workstatus， worktype，carno
		long parkingTM = DF_INT_NULL;
		if (false == SQL4Parking::SelParkingTM(parkingTM))
		{
			log.Info()<<"carNO = "<<carNO<<" SelParkingTM ERROR  , return.................."<<endl;
			return;
		}
		string treatment1 = workType;
		string treatment2 = StringHelper::ToString(parkingTM);
		string treatment = treatment1 + treatment2;//处理号格式：ZC+数字  或者  XL+数字
		string workStatus = GetArriveStatusByWorkType(workType);
		SQL4Parking::UpdParkingWorkStautsInfo(targetParkingNO, treatment, workStatus, workType, carNO, carType);
		
		//3.插入装车卸车物料信息表（履历表） UACS_PARKING_MAT_INFO  
		//处理号，停车位号，车号，计划来源，计划号，子计划号，物料代码，钢制码，作业类型，起吊位置，放下位置，是否完成=1（未完成）
		//根据料格号获取到物料代码和钢制码
		string matCode = "";
		string compCode = "";
		long matWgt = DF_INT_NULL;
		if (false == SQL4Parking::SelGridInfoByGridNO(targetGridNO, matCode, compCode, matWgt))
		{
			log.Info()<<"carNO = "<<carNO<<" SelGridInfoByGridNO is ERROR  , return.................."<<endl;
			return;
		}
		string fromPlace = "";
		string toPlace = "";
		string finishFlag = "1";
		GetFromToPlaceByWorkType(workType, targetGridNO, targetParkingNO, fromPlace, toPlace);
		//插入表UACS_PARKING_MAT_INFO
		SQL4Parking::InsParkingMatInfo(treatment, 
																	targetParkingNO, 
																	carNO, 
																	planSrc, 
																	planNO, 
																	planDetailID, 
																	matCode, 
																	compCode, 
																	workType, 
																	fromPlace, 
																	toPlace, 
																	finishFlag);

		//通知料格管理系统信息： 车号，目的料格号 , 作业类型（worktype）
		//向料格管理系统发送车辆引导目的料格电文
		string msgData = carNO + "," + targetGridNO + "," + workType;
		MsgWG01 handler;
		handler.HandleMessage(msgData);

		


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

string EventGateHandler::GetArriveStatusByWorkType(string workType)
{
	string functionName="EventGateHandler :: GetArriveStatusByWorkType()";
	LOG log(functionName, AUTO_CATCH_PID);
	string workStatus = "";

	try
	{		
		if (workType == "ZC")
		{
			workStatus = "201";
		}
		if (workType == "XL")
		{
			workStatus = "301";
		}
		return workStatus;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return workStatus;
}

void EventGateHandler::GetFromToPlaceByWorkType(string workType, string gridNO, string parkingNO, string& fromPlace, string& toPlace)
{
	string functionName="EventGateHandler :: GetFromToPlaceByWorkType()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{		
		if (workType == "ZC")
		{
			fromPlace = gridNO;
			toPlace = parkingNO;
		}
		if (workType == "XL")
		{
			fromPlace = parkingNO;
			toPlace = gridNO;
		}
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
}

bool EventGateHandler::EVTagSnd(string tagName, string tagValue)
{
	string functionName="EventGateHandler :: EVTagSnd()";
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

string EventGateHandler::workTypeConvert(string workType)
{
	string functionName="EventGateHandler :: workTypeConvert()";
	LOG log(functionName, AUTO_CATCH_PID);

	string workTypeL3 = "";
	try
	{
		if (workType == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			workTypeL3 = "1";
		}
		else if (workType == CarPlanBandInfo::WORK_TYPE_XL)
		{
			workTypeL3 = "2";
		}		
	}
	catch(...)
	{
		log.Debug()<<"workTypeConvert  error..........."<<endl;
	}
	return workTypeL3;
}