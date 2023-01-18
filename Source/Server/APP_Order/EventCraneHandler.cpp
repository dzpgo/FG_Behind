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

		string strOrderNO = kValues[0];//ָ���
		string strCmdSeq = kValues[1];//��ҵ�������
		string strCmdStatus = kValues[2];//״̬
		string strCurWgt = kValues[3];//������ҵ��

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
		//����״̬cmsStatus=F  ���յ�Fʱ,��Ϊָ��ִ�����
		// ���һ�����������Ϸŵ����Ϻ����������꣬��Ϊ��ָ����ɣ�����F
		// ����������������Ϸŵ��ϸ��ں��г��ٴ�ɨ��ж���������ⷴ�����Ͽɵ�����Ϊ��ָ����ɣ�����F
		if (cmdStatus == "F")
		{
			log.Info()<<"Enter cmdstatus = F  handle......................................................"<<endl;
			//ɾ��uacs_order_queue���еļ�¼
			log.Info()<<"1....DelOrderQueue"<<endl;
			SQL4Order::DelOrderQueue(orderNO);

			//����uacs_order_data���м�¼��order_statusΪ�����=3
			log.Info()<<"2....UpdOrderDataStatus"<<endl;
			SQL4Order::UpdOrderDataStatus(orderNO, "3");

			//��������ָ�� �����������ٸ�������
			//�����L3 ��¯ָ�����order_data���е�����  ���¿�ͼ����
			log.Info()<<"3.....orderType = "<<orderQueueInfo.getOrderType()<<endl;

			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				//֪ͨL3����  HCP411 ��Ʒ�ַϸֽ��������ַϸֶѳ�װж��Ϣ
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE��WORK_STATUS,  WORK_TIME
				vector<string> vecMsg;
				vecMsg.push_back("I");//����
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("2");//ж��
				vecMsg.push_back("5");//��ѽ���
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

				//��ѽ�����ɾ��������Ϣ�󶨱�
				SQL4Order::DelParkingCarBandInfo(orderQueueInfo.getPlanNO());

				//֪ͨ����ģ�� ����ͣ��λ״̬��Ϊ �����ɣ���������Ϊ 100�������п��ܻ���ɨ������  ����ҵ���߼��ֳ�����ʱȷ����
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=ͣ��λ��,״̬
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//ͣ��λ�ž��� orderQueueInfo �е�fromStockNO
				string parkingNO = orderQueueInfo.getFromStockNO();
				string workStatus = "305";//������ �� 305 
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);

			}

			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 )
			{
				//����order_data���е�����
				SQL4Order::UpdOrderDataWgt(orderNO, curWgt);				
				//���¿�ͼ
				//��¯װ�� �� L3װ�� ���ϸ�ž���fromstockNO
				//�������͸��¿�ͼ
				//SQL4Order::UpdYardMapMatWgt(orderQueueInfo.getFromStockNO(), curWgt, "-");

				//֪ͨL3����  HCP411 ��Ʒ�ַϸֽ��������ַϸֶѳ�װж��Ϣ
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE��WORK_STATUS,  WORK_TIME
				vector<string> vecMsg;
				vecMsg.push_back("I");//����
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("1");//װ��
				vecMsg.push_back("F");//���һ��װ������
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				//20220825 ��������
				vecMsg.push_back(strCurWgt);
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

				//֪ͨparkingģ�� ����  UACS_PARKING_WORK_STATUS �е�ͣ��λ״̬Ϊ װ������-206
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=ͣ��λ��,״̬
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//ͣ��λ�ž��� orderQueueInfo �е�toStockNO
				string parkingNO = orderQueueInfo.getToStockNO();
				string workStatus = "206";//װ����� �� 206 
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);
				

				//֪ͨPARKINGģ�鳵�������뿪  ��ʱ���߿���û������  �ŵ������״̬��֪ͨ
				//֪ͨ������Parkingģ���Լ����

			}

			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
			{
				//��֯EVtag���� ֪ͨ��¯L2ģ��װ��ʵ��
				vector<string> vecMsg;
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back(StringHelper::ToString(orderQueueInfo.getPlanDetailID()));
				vecMsg.push_back(orderQueueInfo.getFromStockNO());
				vecMsg.push_back(orderQueueInfo.getMatCode());
				vecMsg.push_back(orderQueueInfo.getCompCode());
				vecMsg.push_back(strCurWgt);
				vecMsg.push_back("1");//���һ��
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_EAFL2_ORDER_ZCSJ";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

				//֪ͨparkingģ�� ����  UACS_PARKING_WORK_STATUS �е�ͣ��λ״̬Ϊ װ������-206
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=ͣ��λ��,״̬
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//ͣ��λ�ž��� orderQueueInfo �е�toStockNO
				string parkingNO = orderQueueInfo.getToStockNO();
				string workStatus = "206";//װ����� �� 206 
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);
				
			}
		}

//==================================cmdStatus == "0"============================================================

		//����cmdStatus�� uacs_order_queue  uacs_order_data���и���
		if (cmdStatus == "0")//ȡ��ָ��г�������ָ��г��ֶ���ָ���
		{
			log.Info()<<"Enter cmdstatus = 0  handle......................................................"<<endl;
			//ָ��ȡ����ֻ�е��г��չ�����һ���߶ȣ����غɳ��أ���������׼�жϣ�С��ĳ��Χ��ʱ���ſɶ���
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
			//����ǵ�1���˾�ȡ������uacs_order_data��ָ��״̬�ָ�Ϊ1-����
			if (cmdSeq = 1)
			{
				SQL4Order::UpdOrderDataStatus(orderNO, "1");
			}
		}

//==================================cmdStatus == "1"============================================================

		if (cmdStatus == "1")//��ȡָ��
		{
			log.Info()<<"Enter cmdstatus = 1  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
			SQL4Order::UpdOrderDataStatus(orderNO, "2");

			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE��WORK_STATUS,  WORK_TIME
				vector<string> vecMsg;
				vecMsg.push_back("I");//����
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("2");//ж��
				vecMsg.push_back("4");//��ѿ�ʼ
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

				//֪ͨ����ģ�� ����ͣ��λ״̬��Ϊ ��ѿ�ʼ��
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=ͣ��λ��,״̬
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//ͣ��λ�ž��� orderQueueInfo �е�fromStockNO
				string parkingNO = orderQueueInfo.getFromStockNO();
				string workStatus = "304";//��ѿ�ʼ�� 304 
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);

			}

			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 )
			{
				//֪ͨL3����  HCP411 ��Ʒ�ַϸֽ��������ַϸֶѳ�װж��Ϣ
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE��WORK_STATUS,  WORK_TIME
				//L3��װ����ʼ  ���÷��� HCP411
				
				//֪ͨparkingģ�� ����  UACS_PARKING_WORK_STATUS �е�ͣ��λ״̬Ϊ װ������-206
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=ͣ��λ��,״̬
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//ͣ��λ�ž��� orderQueueInfo �е�toStockNO
				string parkingNO = orderQueueInfo.getToStockNO();
				string workStatus = "205";//װ����� �� 205
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);

			}

			if ( orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
			{

				//��¯�Ӽƻ����е� ״̬ ������  �� ���������¼�������

				//֪ͨparkingģ�� ����  UACS_PARKING_WORK_STATUS �е�ͣ��λ״̬Ϊ װ������-206
				//tagname=EV_ORDER_PARKING_WORK_STATUS
				//tagvalue=ͣ��λ��,״̬
				tagName = "EV_ORDER_PARKING_WORK_STATUS";
				//ͣ��λ�ž��� orderQueueInfo �е�toStockNO
				string parkingNO = orderQueueInfo.getToStockNO();
				string workStatus = "205";//װ����ʼ �� 205
				tagValue = parkingNO + "," + workStatus;
				EVTagSnd(tagName, tagValue);

			}
		}

//==================================cmdStatus == "2"============================================================

		if (cmdStatus == "2")//��ȡ��λ�Ϸ�
		{
			log.Info()<<"Enter cmdstatus = 2  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}

//==================================cmdStatus == "3"============================================================

		if (cmdStatus == "3")//���߿����½���λ
		{
			log.Info()<<"Enter cmdstatus = 3  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}

//==================================cmdStatus == "4"============================================================

		if (cmdStatus == "4")//�������غ�����
		{
			log.Info()<<"Enter cmdstatus = 4  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);


			//����ָ������ 
			//1. L3װ��
			// �����ϸ����ϴ�������
			//2. ��¯װ��
			// �����ϸ����ϴ�������
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

		if (cmdStatus == "5")//��������������λ
		{
			log.Info()<<"Enter cmdstatus = 5  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}
//==================================cmdStatus == "6"============================================================

		if (cmdStatus == "6")//�������ص�����λ
		{
			log.Info()<<"Enter cmdstatus = 6  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}

//==================================cmdStatus == "6"============================================================

		if (cmdStatus == "7")//���������½���λ
		{
			log.Info()<<"Enter cmdstatus = 7  handle......................................................"<<endl;
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
		}

//==================================cmdStatus == "6"============================================================

		if (cmdStatus == "8")//�����غ�������ʧ  �����һ�ε���
		{
			log.Info()<<"Enter cmdstatus = 8  handle......................................................"<<endl;
			//ע��8״̬ʱ��curWgt�����г�ģ��ʱ,���ֵ��Ҫ��cranePlcStatus_Last�ſ���
			SQL4Order::UpdOrderQueueCmdStatus(orderNO, cmdSeq, cmdStatus, curWgt);
			SQL4Order::UpdOrderQueueWgt(orderNO, curWgt);//�ۼ�����//���µ�ʱ��  ��Ϊ����ҵ��� ���ۼ�����
			SQL4Order::UpdOrderDataWgt(orderNO, curWgt);

			//����ָ������ 
			//1. L3ж��
			//���¿�ͼ���ϴ�������
			//����L3�ƻ����е�craneWgt
			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				SQL4Order::UpdYardMapMatWgt(orderQueueInfo.getToStockNO(), curWgt, "+");

				//L3 ж����� �������
				//֪ͨL3 rcv tag�� ����  uacs_L3_MAT_IN_OUT_INFO ��crane_wgt
				//ͨ��tag��  ����
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE��WORK_STATUS,  WORK_TIME,����
				vector<string> vecMsg;
				vecMsg.push_back("I");//����
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("2");//ж��
				vecMsg.push_back("8");//
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				//20220825 ��������
				vecMsg.push_back(strCurWgt);
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

			}

			//2. L3װ��
			// ����uacs_L3_MAT_IN_OUT_INFO ��crane_wgt
			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21)
			{
				//�ڳ��Ϸ���  ���� uacs_L3_MAT_IN_OUT_INFO ��crane_wgt
				//֪ͨL3 rcv tag�� ����  uacs_L3_MAT_IN_OUT_INFO ��crane_wgt
				//ͨ��tag��  ����
				//tagname=EV_L3MSG_SND_HCP411
				//tagvalue=OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE��WORK_STATUS,  WORK_TIME,����
				vector<string> vecMsg;
				vecMsg.push_back("I");//����
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back("1");//ж��
				vecMsg.push_back("8");//
				vecMsg.push_back(iDA::DateTime::Now().ToShortTimeString());
				//20220825 ��������
				vecMsg.push_back(strCurWgt);
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_L3MSG_SND_HCP411";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);
				
			}



			//3. ��¯װ��
			//����װ��ʵ��tag�����¯ģ��
			if (orderQueueInfo.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
			{
				//�ڳ��Ϸ���  ���� uacs_eaf_l2_plan_detail ��crane_wgt
				//֪ͨeafL2ģ��  tag�� ����  uacs_eaf_l2_plan_detail ��crane_wgt
				//tagname=EV_EAFL2_ORDER_ZCSJ
				//tagvalue=�ƻ���,�Ӽƻ���,�ϸ��,���ϴ���,������,��������,�Ƿ����һ�����  0-���� 1-��
				//��֯EVtag���� ֪ͨ��¯L2ģ��װ��ʵ��
				vector<string> vecMsg;
				vecMsg.push_back(orderQueueInfo.getPlanNO());
				vecMsg.push_back(StringHelper::ToString(orderQueueInfo.getPlanDetailID()));
				vecMsg.push_back(orderQueueInfo.getFromStockNO());
				vecMsg.push_back(orderQueueInfo.getMatCode());
				vecMsg.push_back(orderQueueInfo.getCompCode());
				vecMsg.push_back(strCurWgt);
				vecMsg.push_back("0");//�������һ��
				tagValue = GetStrMsg(vecMsg, ",");
				tagName = "EV_EAFL2_ORDER_ZCSJ";
				log.Info()<<"tagName = "<<tagName<<endl;
				log.Info()<<"tagValue = "<<tagValue<<endl;
				EVTagSnd(tagName, tagValue);

			}

			
		


		}

		if (cmdStatus == "9")//���߿���������λ
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