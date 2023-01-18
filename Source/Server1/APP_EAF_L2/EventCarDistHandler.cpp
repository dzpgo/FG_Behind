#include "EventCarDistHandler.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "EAFPlanInfoDetail.h"
#include "EAFPlanInfoMain.h"
#include "MsgUE02.h"


using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

const  string EventCarDistHandler::EXTER_SYSTEM_BOF = "LG";//
const  string EventCarDistHandler::EXTER_SYSTEM_EAF = "DL";//

const  long EventCarDistHandler::MPE_WGT = 100;//

EventCarDistHandler::EventCarDistHandler(void)
{

}

EventCarDistHandler::~EventCarDistHandler(void)
{

}

//收到车辆分配业务处理
void EventCarDistHandler::CarDistHandler(string strValue, string logFileName)
{
	LOG log("EventCarDistHandler::CarDistHandler",logFileName);
	try
	{
		log.Info()<<"CarDistHandler  start........."<<endl;
		//1.解析tag值字符串
		//EV格式：电炉配料计划主计划号,子计划号,车号
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 3)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string planNO = kValues[0];//主计划号
		string strPlanDetailID = kValues[1];//子计划号 
		string carNO = kValues[2];//车号
		log.Info()<<"planNO = "<<planNO<<" , strPlanDetailID = "<<strPlanDetailID<<" , carNO = "<<carNO<<endl;
		
		long planDetailID = StringHelper::ToNumber<long>(strPlanDetailID);

		//如果无主表计划 ,则返回return并报警提示
		string recipeType = "";
		if (false == SQL4EAF::SelMainPlanInfo(planNO, recipeType))
		{
			log.Info()<<"planNO = "<<planNO<<" , SelMainPlanInfo  ERROR , return............ "<<endl;
			return;
		}
		//如果主表计划的配方状态是"删除",则返回return并报警提示
		if (recipeType == EAFPlanInfoMain::RECIPE_TYPE_DELETE)
		{
			log.Info()<<"recipeType = "<<recipeType<<" , plan is DELETE , SelMainPlanInfo  ERROR , return............ "<<endl;
			return;
		}

		//以下是recipeType=1 或2 的情况  
		//有2张表需要处理
		//1. EAF配料计划子表，更新其中的车辆号字段(对于主机号状态是删除的不做更新)
		//根据planNO,planDetailID 判断子表中 status 如果不是"1"未开始状态,说明已经开始装车,不允许在进行车辆分配  报警提示
		bool bFlag1 = false;
		string status = "";
		string layValid= "";
		if (false == SQL4EAF::SelDetailPlanInfo(planNO, planDetailID, status, layValid))
		{
			log.Info()<<"planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<"  , detailPlan is not EXIST , SelDetailPlanInfo  ERROR , return............ "<<endl;
			return;
		}
		if (status != EAFPlanInfoDetail::STATUS_NOT_START)//如果已经开始了
		{
			log.Info()<<"planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<"  , status = "<<status<<" ,  have arrive into yard or  load to car , ERROR return............ "<<endl;
			return;
		}
		if (layValid == EAFPlanInfoDetail::LAY_VALID_NO)//如果是非法的
		{
			log.Info()<<"planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<"  , layValid = "<<layValid<<" , is  INVALID , ERROR return............ "<<endl;
			return;
		}
		bFlag1 = true;

		//2. 车辆计划绑定信息表
		bool bFlag2 = false;
		bool bFlag3 = false;

		string carType = "1";
		string planSrc = "EAF";		
		string enterFlag = "1";
		string orderFlag = "1";
		string workType = "ZC";
		iDA::DateTime bandTime = iDA::DateTime::Now();
		if (false == SQL4EAF::SelCarPlanBand(planNO, planDetailID, enterFlag, orderFlag))//无记录 插入
		{
			log.Info()<<"  planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<" ,  SelCarPlanBand  no record ,ready to insert.........."<<endl;
			bFlag2 = true;
		}
		//车辆计划绑定表里有记录的情况
		else if (enterFlag == "1" && orderFlag == "1")//车辆没有进入库区并且没有生成指令  更新
		{
			bFlag3 = true;
		}
		else
		{
			//车辆已经进入 或者 已经有对应指令生成  车号分配失败 报警提示
			log.Info()<<"carNO = "<<carNO<<" , planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<" ,  enterFlag = "<<enterFlag<<" , orderFlag = "<<orderFlag<<" , ERROR return...."<<endl;
		}

		if (bFlag1 == true && bFlag2 == true)//更新计划子表  插入车辆信息绑定表
		{
			SQL4EAF::UpdCarNOInPlanDetail(planNO, planDetailID, carNO);
			SQL4EAF::InsCarPlanBand(carNO, carType, workType, planNO, planSrc, planDetailID, enterFlag, 	orderFlag,	bandTime);
			return;
		}
		if (bFlag1 == true && bFlag3 == true)//更新计划子表,  更新车辆信息绑定表
		{
			SQL4EAF::UpdCarNOInPlanDetail(planNO, planDetailID, carNO);
			SQL4EAF::UpdCarPlanBand(carNO, planNO, planDetailID);
			return;
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


//收到车辆到达通知
void EventCarDistHandler::CarArriveHandler(string strValue, string logFileName)
{
	LOG log("EventCarDistHandler::CarArriveHandler",logFileName);
	try
	{
		log.Info()<<"CarArriveHandler  start........."<<endl;
		//1.解析tag值字符串
		//EV格式：电炉配料计划主计划号,子计划号
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string planNO = kValues[0];//主计划号
		string strPlanDetailID = kValues[1];//子计划号 
		log.Info()<<"planNO = "<<planNO<<" , strPlanDetailID = "<<strPlanDetailID<<endl;

		long planDetailID = StringHelper::ToNumber<long>(strPlanDetailID);

		//如果无主表计划 ,则返回return并报警提示
		string recipeType = "";
		if (false == SQL4EAF::SelMainPlanInfo(planNO, recipeType))
		{
			log.Info()<<"planNO = "<<planNO<<" , SelMainPlanInfo  ERROR , return............ "<<endl;
			return;
		}
		//如果主表计划的配方状态是"删除",则返回return并报警提示
		if (recipeType == EAFPlanInfoMain::RECIPE_TYPE_DELETE)
		{
			log.Info()<<"recipeType = "<<recipeType<<" , plan is DELETE , SelMainPlanInfo  ERROR , return............ "<<endl;
			return;
		}

//=====================================================================================		
		//根据主计划号 子计划号  更新status=2
		SQL4EAF::UpdPlanDetailStatusByDetailID(planDetailID, EAFPlanInfoDetail::STATUS_START);

//=====================================================================================
		//组织装车启动电文数据发给废钢L2
		EAFPlanInfoMain planInfoMain;
		SQL4EAF::SelEAFPlanInfoMain(planNO, planInfoMain);
		EAFPlanInfoDetail planInfoDetail;
		SQL4EAF::SelEAFPlanInfoDetailByDetailID(planDetailID, planInfoDetail);

		vector<string> vecMsg;
		vecMsg.push_back(planInfoMain.getPono());
		vecMsg.push_back(planInfoMain.getHtno());
		vecMsg.push_back(planInfoDetail.getBSeqNum());
		vecMsg.push_back(planInfoDetail.getPitNum());
		vecMsg.push_back( StringHelper::ToString( planInfoDetail.getLayNO() ) );
		vecMsg.push_back(planInfoDetail.getScrID());
		vecMsg.push_back( StringHelper::ToString( planInfoDetail.getScrWeight() ) );
		vecMsg.push_back(planInfoDetail.getCarNO());
		vecMsg.push_back(planInfoMain.getPlanSrc());//新旧电炉区分


		string msg = GetStrMsg(vecMsg, ",");

		log.Info()<<"msg = "<<msg<<endl;

		MsgUE02 handler;
		handler.HandleMessage(msg, logFileName);
		
	

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



//组织电文内容
string EventCarDistHandler::GetMsgUE02Text(EAFPlanInfoMain planInfoMain, EAFPlanInfoDetail planInfoDetail)
{
	LOG log("EventCarDistHandler::CarArriveHandler",AUTO_CATCH_PID);
	string strMsg = "";
	try
	{
		//组织数据
		string pitNum = "";
		if (planInfoDetail.getPitNum().empty())
		{
			pitNum = "@";
		}
		else
		{
			pitNum = planInfoDetail.getPitNum();
		}

		strMsg = planInfoMain.getPono() + "," + planInfoMain.getHtno() + ",";
		strMsg += planInfoDetail.getBSeqNum() + "," + pitNum + ",";
		strMsg += StringHelper::ToString(planInfoDetail.getLayNO()) + "," + planInfoDetail.getScrID() + ",";
		strMsg += StringHelper::ToString(planInfoDetail.getScrWeight()) + "," + planInfoDetail.getCarNO();
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


string EventCarDistHandler::GetStrMsg(vector<string> vecStr, string splitFlag)
{
	LOG log("EventCarDistHandler::GetStrMsg",AUTO_CATCH_PID);
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