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

//�յ�װ��ʵ��
void EventOrderZCSJHandler::OrderZCSJHandler(string strValue, string logFileName)
{
	LOG log("EventOrderZCSJHandler::OrderZCSJHandler",logFileName);
	try
	{
		log.Info()<<"OrderZCSJHandler  start........."<<endl;
		//1.����tagֵ�ַ���
		//EV��ʽ�����������,�Ӽƻ���,�ϸ��,���ϴ���,������,װ������,�Ƿ����һ�����(1-��,0-����  ���һ����Ҫ���¯L2����װ��ʵ��������Ҫ��L3����װ��ʵ��)
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 7)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string planNO = kValues[0];//���ƻ���(���������)
		string strPlanDetailID = kValues[1];//�Ӽƻ��� 
		string gridNO = kValues[2];
		string matCode = kValues[3];
		string compCode = kValues[4];
		string strMatWgt = kValues[5];//װ���������г����أ�
		string lastFlag =  kValues[6];
		log.Info()<<"planNO = "<<planNO<<" , strPlanDetailID = "<<strPlanDetailID<<" , strMatWgt = "<<strMatWgt<<" , lastFlag = "<<lastFlag<<endl;

		long planDetailID = StringHelper::ToNumber<long>(strPlanDetailID);
		long matWgt = StringHelper::ToNumber<long>(strMatWgt);

		//���������ƻ� ,�򷵻�return��������ʾ
		string recipeType = "";
		if (false == SQL4EAF::SelMainPlanInfo(planNO, recipeType))
		{
			log.Info()<<"planNO = "<<planNO<<" , SelMainPlanInfo  ERROR , return............ "<<endl;
			return;
		}
		//�������ƻ����䷽״̬��"ɾ��",�򷵻�return��������ʾ
		if (recipeType == EAFPlanInfoMain::RECIPE_TYPE_DELETE)
		{
			log.Info()<<"recipeType = "<<recipeType<<" , plan is DELETE , SelMainPlanInfo  ERROR , return............ "<<endl;
			return;
		}

		//1. ���µ�¯L2�Ӽƻ�����������Ϣ
		SQL4EAF::UpdEAFPlanDetailMatInfo(planNO, 
																			planDetailID, 
																			gridNO, 
																			matCode, 
																			compCode, 
																			matWgt);

		//2. �ж��Ƿ������һ�� 
		if (lastFlag == "0")//�������һ��
		{
			log.Info()<<"Not Last ZC Job..................return.................."<<endl;
			return;
		}

		//���������һ��
		//�����ӱ���status=3 �����
		SQL4EAF::UpdEAFPlanDetailStatus(planDetailID, "3");

		//��ȡ������Ϣ
		EAFPlanInfoMain eafPlanMain;
		EAFPlanInfoDetail eafPlanDetail;
		SQL4EAF::SelEAFPlanInfoMain(planNO, eafPlanMain);
		SQL4EAF::SelEAFPlanInfoDetailByDetailID(planDetailID, eafPlanDetail);

		//��֯UE01����
		vector<string> vecMsg;
		vecMsg.push_back(eafPlanMain.getPono());
		vecMsg.push_back(eafPlanMain.getHtno());
		vecMsg.push_back(eafPlanDetail.getBSeqNum());
		vecMsg.push_back(eafPlanDetail.getPitNum());
		vecMsg.push_back("1");//�г�����������־
		vecMsg.push_back( StringHelper::ToString( eafPlanDetail.getLayNO() ) );
		vecMsg.push_back(eafPlanDetail.getCarNO());
		vecMsg.push_back(eafPlanDetail.getScrID());
		vecMsg.push_back( StringHelper::ToString( eafPlanDetail.getCraneWeight() ) );
		vecMsg.push_back(eafPlanMain.getPlanSrc());

		string msg = GetStrMsg(vecMsg, ",");
		log.Info()<<"msg = "<<msg<<endl;

		//���¯L2����
		MsgUE01 handler;
		handler.HandleMessage(msg, logFileName);

		vecMsg.clear();

//============================================================================================

		//��L3���͵��� HCP412		
		vecMsg.push_back("I");
		vecMsg.push_back(eafPlanDetail.getOperID());
		vecMsg.push_back(eafPlanDetail.getCarNO());
		vecMsg.push_back("DLC");
		string destStockCode = "";//L3��Ŀ�Ŀ�������
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
		vecMsg.push_back("1");//��¯�ϸ�ֻ��1��ѭ����

		//ѭ������#�ָ�
		vector<string> vecLoop;
		vecLoop.push_back(eafPlanDetail.getGridNO());
		vecLoop.push_back(eafPlanDetail.getMatCode());
		vecLoop.push_back(eafPlanDetail.getCompCode());
		vecLoop.push_back( StringHelper::ToString(eafPlanDetail.getCraneWeight()) );
		string strLoop = GetStrMsg(vecLoop, "#");

		vecMsg.push_back(strLoop);

		string L3Msg = GetStrMsg(vecMsg, ",");

		log.Info()<<"L3Msg = "<<L3Msg<<endl;

		//��L3����
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


//�յ�L3У������
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
		string operID = kValues[0];//�ƻ��ӱ��ʵ����
		string strNetWgt = kValues[1];//L3�ĳ����� 
		log.Info()<<"operID = "<<operID<<" , strNetWgt = "<<strNetWgt<<endl;

		long netWgt = StringHelper::ToNumber<long>(strNetWgt);

	    //1. ���µ�¯�ƻ��ӱ��е�sclweight�ֶ�
		SQL4EAF::UpdEAFPlanDetailSclWgt(operID, netWgt);
		//���¯L2����L3����ʵ��
		//����operID��ȡ���ƻ���planNO
		string planNO = "";
		long planDetailID = 0;
		SQL4EAF::SelPlanNOByOperID(operID, planNO, planDetailID);

		EAFPlanInfoMain eafPlanMain;
		EAFPlanInfoDetail eafPlanDetail;
		SQL4EAF::SelEAFPlanInfoMain(planNO, eafPlanMain);
		SQL4EAF::SelEAFPlanInfoDetailByDetailID(planDetailID, eafPlanDetail);

		//��֯UE01����
		vector<string> vecMsg;
		vecMsg.push_back(eafPlanMain.getPono());
		vecMsg.push_back(eafPlanMain.getHtno());
		vecMsg.push_back(eafPlanDetail.getBSeqNum());
		vecMsg.push_back(eafPlanDetail.getPitNum());
		vecMsg.push_back("2");//�����������ر�־
		vecMsg.push_back( StringHelper::ToString( eafPlanDetail.getLayNO() ) );
		vecMsg.push_back(eafPlanDetail.getCarNO());
		vecMsg.push_back(eafPlanDetail.getScrID());
		vecMsg.push_back( StringHelper::ToString( eafPlanDetail.getScrWeight() ) );
		vecMsg.push_back(eafPlanMain.getPlanSrc());

		string msg = GetStrMsg(vecMsg, ",");
		log.Info()<<"msg = "<<msg<<endl;

		//���¯L2����
		MsgUE01 handler;
		handler.HandleMessage(msg, logFileName);

//=======================================================================================

		//2.ָ֪ͨ��ģ��У���ϸ����
		//��ȡ�г�����
		long craneWgt = 0;
		string gridNO = "";
		string matCode = "";
		string compCode = "";
		SQL4EAF::SelGridMatCompCraneWgt(operID, 
																			gridNO, 
																			matCode, 
																			compCode, 
																			craneWgt);
		//��֯ev�����ݷ���
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