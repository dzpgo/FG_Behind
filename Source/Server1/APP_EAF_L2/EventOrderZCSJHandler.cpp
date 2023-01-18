#include "EventOrderZCSJHandler.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "EAFPlanInfoDetail.h"
#include "EAFPlanInfoMain.h"
#include "MsgUE01.h"


using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

const  string EventOrderZCSJHandler::EXTER_SYSTEM_BOF = "LG";//
const  string EventOrderZCSJHandler::EXTER_SYSTEM_EAF = "DL";//

const  long EventOrderZCSJHandler::MPE_WGT = 100;//

EventOrderZCSJHandler::EventOrderZCSJHandler(void)
{

}

EventOrderZCSJHandler::~EventOrderZCSJHandler(void)
{

}

//收到装车实绩
void EventOrderZCSJHandler::OrderZCSJHandler(string strValue, string logFileName)
{
	LOG log("EventOrderZCSJHandler::OrderZCSJHandler",logFileName);
	try
	{
		log.Info()<<"OrderZCSJHandler  start........."<<endl;
		//1.解析tag值字符串
		//EV格式：制造命令号,子计划号,料格号,物料代码,钢制码,装料重量,是否最后一吊标记(1-是,0-不是  最后一吊需要向电炉L2发送装车实绩，还需要向L3发送装车实绩)
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 7)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string planNO = kValues[0];//主计划号(制造命令号)
		string strPlanDetailID = kValues[1];//子计划号 
		string gridNO = kValues[2];
		string matCode = kValues[3];
		string compCode = kValues[4];
		string strMatWgt = kValues[5];//装料重量（行车称重）
		string lastFlag =  kValues[6];
		log.Info()<<"planNO = "<<planNO<<" , strPlanDetailID = "<<strPlanDetailID<<" , strMatWgt = "<<strMatWgt<<" , lastFlag = "<<lastFlag<<endl;

		long planDetailID = StringHelper::ToNumber<long>(strPlanDetailID);
		long matWgt = StringHelper::ToNumber<long>(strMatWgt);

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

		//1. 更新电炉L2子计划表中物料信息
		SQL4EAF::UpdEAFPlanDetailMatInfo(planNO, 
																			planDetailID, 
																			gridNO, 
																			matCode, 
																			compCode, 
																			matWgt);

		//2. 判断是否是最后一吊 
		if (lastFlag == "0")//不是最后一吊
		{
			log.Info()<<"Not Last ZC Job..................return.................."<<endl;
			return;
		}

		//以下是最后一吊
		//更新子表中status=3 已完成
		SQL4EAF::UpdEAFPlanDetailStatus(planDetailID, "3");

		//获取主表信息
		EAFPlanInfoMain eafPlanMain;
		EAFPlanInfoDetail eafPlanDetail;
		SQL4EAF::SelEAFPlanInfoMain(planNO, eafPlanMain);
		SQL4EAF::SelEAFPlanInfoDetailByDetailID(planDetailID, eafPlanDetail);

		//组织UE01电文
		vector<string> vecMsg;
		vecMsg.push_back(eafPlanMain.getPono());
		vecMsg.push_back(eafPlanMain.getHtno());
		vecMsg.push_back(eafPlanDetail.getBSeqNum());
		vecMsg.push_back(eafPlanDetail.getPitNum());
		vecMsg.push_back("1");//行车称重重量标志
		vecMsg.push_back( StringHelper::ToString( eafPlanDetail.getLayNO() ) );
		vecMsg.push_back(eafPlanDetail.getCarNO());
		vecMsg.push_back(eafPlanDetail.getScrID());
		vecMsg.push_back( StringHelper::ToString( eafPlanDetail.getCraneWeight() ) );
		vecMsg.push_back(eafPlanMain.getPlanSrc());

		string msg = GetStrMsg(vecMsg, ",");
		log.Info()<<"msg = "<<msg<<endl;

		//向电炉L2发送
		MsgUE01 handler;
		handler.HandleMessage(msg, logFileName);

		vecMsg.clear();

//============================================================================================

		//向L3发送电文 HCP412		
		vecMsg.push_back("I");
		vecMsg.push_back(eafPlanDetail.getOperID());
		vecMsg.push_back(eafPlanDetail.getCarNO());
		vecMsg.push_back("DLC");
		string destStockCode = "";//L3的目的库区定义
		if (eafPlanMain.getPlanSrc() == "1")
		{
			destStockCode = "ABEE";
		}
		else
		{
			destStockCode = "ABEO";
		}
		vecMsg.push_back(destStockCode);
		vecMsg.push_back(eafPlanDetail.getPitNum());
		vecMsg.push_back(eafPlanMain.getHtno());
		vecMsg.push_back(eafPlanMain.getPono());
		vecMsg.push_back(eafPlanMain.getSteelGrade());
		vecMsg.push_back("1");//电炉废钢只有1个循环体

		//循环体用#分割
		vector<string> vecLoop;
		vecLoop.push_back(eafPlanDetail.getGridNO());
		vecLoop.push_back(eafPlanDetail.getMatCode());
		vecLoop.push_back(eafPlanDetail.getCompCode());
		vecLoop.push_back( StringHelper::ToString(eafPlanDetail.getCraneWeight()) );
		string strLoop = GetStrMsg(vecLoop, "#");

		vecMsg.push_back(strLoop);

		string L3Msg = GetStrMsg(vecMsg, ",");

		log.Info()<<"L3Msg = "<<L3Msg<<endl;

		//向L3发送
		EVTagSnd("EV_L3MSG_SND_HCP412", L3Msg);


		

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


//收到L3校秤重量
void EventOrderZCSJHandler::L3WgtHandler(string strValue, string logFileName)
{
	LOG log("EventOrderZCSJHandler::L3WgtHandler", logFileName);
	try
	{
		log.Info()<<"L3WgtHandler  start........."<<endl;
		
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string operID = kValues[0];//计划子表的实绩号
		string strNetWgt = kValues[1];//L3的称重量 
		log.Info()<<"operID = "<<operID<<" , strNetWgt = "<<strNetWgt<<endl;

		long netWgt = StringHelper::ToNumber<long>(strNetWgt);

	    //1. 更新电炉计划子表中的sclweight字段
		SQL4EAF::UpdEAFPlanDetailSclWgt(operID, netWgt);
		//向电炉L2发送L3称量实绩
		//根据operID获取主计划号planNO
		string planNO = "";
		long planDetailID = 0;
		SQL4EAF::SelPlanNOByOperID(operID, planNO, planDetailID);

		EAFPlanInfoMain eafPlanMain;
		EAFPlanInfoDetail eafPlanDetail;
		SQL4EAF::SelEAFPlanInfoMain(planNO, eafPlanMain);
		SQL4EAF::SelEAFPlanInfoDetailByDetailID(planDetailID, eafPlanDetail);

		//组织UE01电文
		vector<string> vecMsg;
		vecMsg.push_back(eafPlanMain.getPono());
		vecMsg.push_back(eafPlanMain.getHtno());
		vecMsg.push_back(eafPlanDetail.getBSeqNum());
		vecMsg.push_back(eafPlanDetail.getPitNum());
		vecMsg.push_back("2");//车辆过磅称重标志
		vecMsg.push_back( StringHelper::ToString( eafPlanDetail.getLayNO() ) );
		vecMsg.push_back(eafPlanDetail.getCarNO());
		vecMsg.push_back(eafPlanDetail.getScrID());
		vecMsg.push_back( StringHelper::ToString( eafPlanDetail.getScrWeight() ) );
		vecMsg.push_back(eafPlanMain.getPlanSrc());

		string msg = GetStrMsg(vecMsg, ",");
		log.Info()<<"msg = "<<msg<<endl;

		//向电炉L2发送
		MsgUE01 handler;
		handler.HandleMessage(msg, logFileName);

//=======================================================================================

		//2.通知指令模块校正料格存量
		//获取行车称量
		long craneWgt = 0;
		string gridNO = "";
		string matCode = "";
		string compCode = "";
		SQL4EAF::SelGridMatCompCraneWgt(operID, 
																			gridNO, 
																			matCode, 
																			compCode, 
																			craneWgt);
		//组织ev点数据发送
		string tagName = "EV_EAF_ORDER_L3_CRANE_WGT";
		string tagValue = gridNO + "," + matCode + "," + compCode + "," + strNetWgt + "," + StringHelper::ToString(craneWgt);
		EVTagSnd(tagName, tagValue);


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





string EventOrderZCSJHandler::GetStrMsg(vector<string> vecStr, string splitFlag)
{
	LOG log("EventOrderZCSJHandler::GetStrMsg",AUTO_CATCH_PID);
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


bool EventOrderZCSJHandler::EVTagSnd(string tagName, string tagValue)
{
	string functionName="EventOrderZCSJHandler :: EVTagSnd()";
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