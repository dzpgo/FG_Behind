
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

		string strCraneNO = kValues[0];//行车号
		string strOrderNO = kValues[1];//指令号
		string strCmdSeq = kValues[2];//激光扫描号
		string strScanNO = kValues[3];//激光扫描号
		string strScanType = kValues[4];//扫描动作类型 0-取料 1-放料
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

		//获取行车当前指令表
		OrderCurrentBase orderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

		//1. 如果指令状态是empty 返回
		if (orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			log.Info()<<"order status is EMPTY, return....................................."<<endl;
			return;
		}

		//2. 如果当前指令表中指令号和tagvalue中的orderNO不一致 返回
		if (orderCurrent.getOrderNO() != orderNO)
		{
			log.Info()<<"orderNO  is NOT SAME to OrderCurrent, return....................................."<<endl;
			return;
		}

		//2.1 如果cmdSeq不一致，返回
		if (orderCurrent.getCmdSeq() != cmdSeq)
		{
			log.Info()<<"cmdSeq  is NOT SAME to OrderCurrent, return....................................."<<endl;
			return;
		}

		bool bPlanUpXYZIsNull = (orderCurrent.getPlanUpX() == DB_INT_NULL && orderCurrent.getPlanUpY() == DB_INT_NULL && orderCurrent.getPlanUpZ() == DB_INT_NULL);

		//3. strScanType=0 取料 && 指令中取料点扫描处理号isEmpty && planUpXYZ 封9  ，  则更新写入 取料点扫描号 , planUpXYZ
		if (strScanType == "0" && orderCurrent.getMatUpScanNO().empty() && bPlanUpXYZIsNull == true)
		{
			log.Info()<<"the MatUpScanNO and  matUp Point XYZ In Tag Ready to Write into OrderCurrent table..................."<<endl;
			Adapter_UACS_CRANE_ORDER_CURRENT::UpdOrderCurrentUpScanNOAndPoint(craneNO, strScanNO, pointX, pointY, pointZ);
			return;
		}

		bool bPlanDownXYZIsNull = (orderCurrent.getPlanDownX() == DB_INT_NULL && orderCurrent.getPlanDownY() == DB_INT_NULL && orderCurrent.getPlanDownZ() == DB_INT_NULL);
		
		//4. strScanType=1 放料 && 指令中放料点扫描处理号isEmpty && planDownXYZ 封9  ，  则更新写入 放料点扫描号 , planDownXYZ
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
		string strOrderNO = kValues[0];//指令号
		string strCarScanNO = kValues[1];//车辆激光扫描号

		log.Info()<<"strOrderNO = "<<strOrderNO<<endl;
		log.Info()<<"strCarScanNO = "<<strCarScanNO<<endl;

		//获取行车当前指令表
		OrderCurrentBase orderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

		//1. 如果指令状态是empty 返回
		if (orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			log.Info()<<"order status is EMPTY, return....................................."<<endl;
			return;
		}

		long orderNO = StringHelper::ToNumber<long>(strOrderNO);

		//2. 如果当前指令表中指令号和tagvalue中的orderNO不一致 返回
		if (orderCurrent.getOrderNO() != orderNO)
		{
			log.Info()<<"orderNO  is NOT SAME to OrderCurrent, return....................................."<<endl;
			return;
		}

		//3. 如果当前指令表中没有carScanNO数据，则写入
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



