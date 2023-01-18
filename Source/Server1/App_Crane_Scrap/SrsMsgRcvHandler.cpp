
#pragma once 

#include "SrsMsgRcvHandler.h"


using namespace Monitor;



SrsMsgRcvHandler:: SrsMsgRcvHandler()
{

}

SrsMsgRcvHandler:: ~SrsMsgRcvHandler()
{

}

void SrsMsgRcvHandler::LU01Handler(string strValue, string craneNO)
{
	string functionName = "SrsMsgRcvHandler :: LU01Handler()";
	LOG log(functionName, "SrsMsgRcvHandler");

	try
	{
		log.Info()<<"LU01Handler  Start............................................................................................................................................................................"<<endl;

		//string tagValue = craneNO + "," + strOrderNO + "," + cmdSeq + "," + scanNO + "," + scanType + "," + strPointX + "," + strPointY + "," + strPointZ;
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 8)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string strCraneNO = kValues[0];//�г���
		string strOrderNO = kValues[1];//ָ���
		string strCmdSeq = kValues[2];//����ɨ���
		string strScanNO = kValues[3];//����ɨ���
		string strScanType = kValues[4];//ɨ�趯������ 0-ȡ�� 1-����
		string strPointX = kValues[5];
		string strPointY = kValues[6];
		string strPointZ = kValues[7];


		log.Info()<<"strCraneNO = "<<strCraneNO<<endl;
		log.Info()<<"strOrderNO = "<<strOrderNO<<endl;
		log.Info()<<"strCmdSeq = "<<strCmdSeq<<endl;
		log.Info()<<"strScanNO = "<<strScanNO<<endl;
		log.Info()<<"strScanType = "<<strScanType<<endl;
		log.Info()<<"strPointX = "<<strPointX<<endl;
		log.Info()<<"strPointY = "<<strPointY<<endl;
		log.Info()<<"strPointZ = "<<strPointZ<<endl;

		long orderNO = StringHelper::ToNumber<long>(strOrderNO);
		long cmdSeq = StringHelper::ToNumber<long>(strCmdSeq);
		long pointX = StringHelper::ToNumber<long>(strPointX);
		long pointY = StringHelper::ToNumber<long>(strPointY);
		long pointZ = StringHelper::ToNumber<long>(strPointZ);

		//��ȡ�г���ǰָ���
		OrderCurrentBase orderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

		//1. ���ָ��״̬��empty ����
		if (orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			log.Info()<<"order status is EMPTY, return....................................."<<endl;
			return;
		}

		//2. �����ǰָ�����ָ��ź�tagvalue�е�orderNO��һ�� ����
		if (orderCurrent.getOrderNO() != orderNO)
		{
			log.Info()<<"orderNO  is NOT SAME to OrderCurrent, return....................................."<<endl;
			return;
		}

		//2.1 ���cmdSeq��һ�£�����
		if (orderCurrent.getCmdSeq() != cmdSeq)
		{
			log.Info()<<"cmdSeq  is NOT SAME to OrderCurrent, return....................................."<<endl;
			return;
		}

		bool bPlanUpXYZIsNull = (orderCurrent.getPlanUpX() == DB_INT_NULL && orderCurrent.getPlanUpY() == DB_INT_NULL && orderCurrent.getPlanUpZ() == DB_INT_NULL);

		//3. strScanType=0 ȡ�� && ָ����ȡ�ϵ�ɨ�账���isEmpty && planUpXYZ ��9  ��  �����д�� ȡ�ϵ�ɨ��� , planUpXYZ
		if (strScanType == "0" && orderCurrent.getMatUpScanNO().empty() && bPlanUpXYZIsNull == true)
		{
			log.Info()<<"the MatUpScanNO and  matUp Point XYZ In Tag Ready to Write into OrderCurrent table..................."<<endl;
			Adapter_UACS_CRANE_ORDER_CURRENT::UpdOrderCurrentUpScanNOAndPoint(craneNO, strScanNO, pointX, pointY, pointZ);
			return;
		}

		bool bPlanDownXYZIsNull = (orderCurrent.getPlanDownX() == DB_INT_NULL && orderCurrent.getPlanDownY() == DB_INT_NULL && orderCurrent.getPlanDownZ() == DB_INT_NULL);
		
		//4. strScanType=1 ���� && ָ���з��ϵ�ɨ�账���isEmpty && planDownXYZ ��9  ��  �����д�� ���ϵ�ɨ��� , planDownXYZ
		if (strScanType == "1" && orderCurrent.getMatDownScanNO().empty() && bPlanDownXYZIsNull == true)
		{
			log.Info()<<"the MatDownScanNO and  matDown Point XYZ In Tag Ready to Write into OrderCurrent table..................."<<endl;
			Adapter_UACS_CRANE_ORDER_CURRENT::UpdOrderCurrentDownScanNOAndPoint(craneNO, strScanNO, pointX, pointY, pointZ);
			return;
		}




	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}
}



void SrsMsgRcvHandler::LU02Handler(string strValue, string craneNO)
{
	string functionName = "SrsMsgRcvHandler :: LU02Handler()";
	LOG log(functionName, "SrsMsgRcvHandler");

	try
	{
		log.Info()<<"LU02Handler  Start............................................................................................................................................................................"<<endl;

		//string tagValue = orderNO, carScanNO;
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string strOrderNO = kValues[0];//ָ���
		string strCarScanNO = kValues[1];//��������ɨ���

		log.Info()<<"strOrderNO = "<<strOrderNO<<endl;
		log.Info()<<"strCarScanNO = "<<strCarScanNO<<endl;

		//��ȡ�г���ǰָ���
		OrderCurrentBase orderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

		//1. ���ָ��״̬��empty ����
		if (orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			log.Info()<<"order status is EMPTY, return....................................."<<endl;
			return;
		}

		long orderNO = StringHelper::ToNumber<long>(strOrderNO);

		//2. �����ǰָ�����ָ��ź�tagvalue�е�orderNO��һ�� ����
		if (orderCurrent.getOrderNO() != orderNO)
		{
			log.Info()<<"orderNO  is NOT SAME to OrderCurrent, return....................................."<<endl;
			return;
		}

		//3. �����ǰָ�����û��carScanNO���ݣ���д��
		if (orderCurrent.getCarScanNO().empty())
		{
			log.Info()<<"the CarScanNO Tag Ready to Write into OrderCurrent table..................."<<endl;
			Adapter_UACS_CRANE_ORDER_CURRENT::UpdOrderCurrentCarScanNO(craneNO, strCarScanNO);
			return;
		}




	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}
}



