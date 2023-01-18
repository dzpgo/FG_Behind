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

//�յ���������ҵ����
void EventCarDistHandler::CarDistHandler(string strValue, string logFileName)
{
	LOG log("EventCarDistHandler::CarDistHandler",logFileName);
	try
	{
		log.Info()<<"CarDistHandler  start........."<<endl;
		//1.����tagֵ�ַ���
		//EV��ʽ����¯���ϼƻ����ƻ���,�Ӽƻ���,����
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 3)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string planNO = kValues[0];//���ƻ���
		string strPlanDetailID = kValues[1];//�Ӽƻ��� 
		string carNO = kValues[2];//����
		log.Info()<<"planNO = "<<planNO<<" , strPlanDetailID = "<<strPlanDetailID<<" , carNO = "<<carNO<<endl;
		
		long planDetailID = StringHelper::ToNumber<long>(strPlanDetailID);

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

		//������recipeType=1 ��2 �����  
		//��2�ű���Ҫ����
		//1. EAF���ϼƻ��ӱ��������еĳ������ֶ�(����������״̬��ɾ���Ĳ�������)
		//����planNO,planDetailID �ж��ӱ��� status �������"1"δ��ʼ״̬,˵���Ѿ���ʼװ��,�������ڽ��г�������  ������ʾ
		bool bFlag1 = false;
		string status = "";
		string layValid= "";
		if (false == SQL4EAF::SelDetailPlanInfo(planNO, planDetailID, status, layValid))
		{
			log.Info()<<"planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<"  , detailPlan is not EXIST , SelDetailPlanInfo  ERROR , return............ "<<endl;
			return;
		}
		if (status != EAFPlanInfoDetail::STATUS_NOT_START)//����Ѿ���ʼ��
		{
			log.Info()<<"planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<"  , status = "<<status<<" ,  have arrive into yard or  load to car , ERROR return............ "<<endl;
			return;
		}
		if (layValid == EAFPlanInfoDetail::LAY_VALID_NO)//����ǷǷ���
		{
			log.Info()<<"planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<"  , layValid = "<<layValid<<" , is  INVALID , ERROR return............ "<<endl;
			return;
		}
		bFlag1 = true;

		//2. �����ƻ�����Ϣ��
		bool bFlag2 = false;
		bool bFlag3 = false;

		string carType = "1";
		string planSrc = "EAF";		
		string enterFlag = "1";
		string orderFlag = "1";
		string workType = "ZC";
		iDA::DateTime bandTime = iDA::DateTime::Now();
		if (false == SQL4EAF::SelCarPlanBand(planNO, planDetailID, enterFlag, orderFlag))//�޼�¼ ����
		{
			log.Info()<<"  planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<" ,  SelCarPlanBand  no record ,ready to insert.........."<<endl;
			bFlag2 = true;
		}
		//�����ƻ��󶨱����м�¼�����
		else if (enterFlag == "1" && orderFlag == "1")//����û�н����������û������ָ��  ����
		{
			bFlag3 = true;
		}
		else
		{
			//�����Ѿ����� ���� �Ѿ��ж�Ӧָ������  ���ŷ���ʧ�� ������ʾ
			log.Info()<<"carNO = "<<carNO<<" , planNO = "<<planNO<<" , planDetailID = "<<planDetailID<<" ,  enterFlag = "<<enterFlag<<" , orderFlag = "<<orderFlag<<" , ERROR return...."<<endl;
		}

		if (bFlag1 == true && bFlag2 == true)//���¼ƻ��ӱ�  ���복����Ϣ�󶨱�
		{
			SQL4EAF::UpdCarNOInPlanDetail(planNO, planDetailID, carNO);
			SQL4EAF::InsCarPlanBand(carNO, carType, workType, planNO, planSrc, planDetailID, enterFlag, 	orderFlag,	bandTime);
			return;
		}
		if (bFlag1 == true && bFlag3 == true)//���¼ƻ��ӱ�,  ���³�����Ϣ�󶨱�
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


//�յ���������֪ͨ
void EventCarDistHandler::CarArriveHandler(string strValue, string logFileName)
{
	LOG log("EventCarDistHandler::CarArriveHandler",logFileName);
	try
	{
		log.Info()<<"CarArriveHandler  start........."<<endl;
		//1.����tagֵ�ַ���
		//EV��ʽ����¯���ϼƻ����ƻ���,�Ӽƻ���
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string planNO = kValues[0];//���ƻ���
		string strPlanDetailID = kValues[1];//�Ӽƻ��� 
		log.Info()<<"planNO = "<<planNO<<" , strPlanDetailID = "<<strPlanDetailID<<endl;

		long planDetailID = StringHelper::ToNumber<long>(strPlanDetailID);

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

//=====================================================================================		
		//�������ƻ��� �Ӽƻ���  ����status=2
		SQL4EAF::UpdPlanDetailStatusByDetailID(planDetailID, EAFPlanInfoDetail::STATUS_START);

//=====================================================================================
		//��֯װ�������������ݷ����ϸ�L2
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
		vecMsg.push_back(planInfoMain.getPlanSrc());//�¾ɵ�¯����


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



//��֯��������
string EventCarDistHandler::GetMsgUE02Text(EAFPlanInfoMain planInfoMain, EAFPlanInfoDetail planInfoDetail)
{
	LOG log("EventCarDistHandler::CarArriveHandler",AUTO_CATCH_PID);
	string strMsg = "";
	try
	{
		//��֯����
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