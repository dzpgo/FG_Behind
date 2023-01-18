
//激光扫描启动电文MsgUL02
#include "MsgUL02.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "SQL4Parking.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgUL02::MsgUL02(void)
{
	m_strMsgId = "UL02";
}

MsgUL02::~MsgUL02(void)
{

}


void MsgUL02::HandleMessage(const string strValue, const string logFileName)
{
	LOG log("MsgUL02::HandleMessage",logFileName);
	try
	{
		//strValue格式：
		//KEY_CraneNo,KEY_MessageNo,KEY_ParkingNo,KEY_VehicleType,KEY_MaterialType,KEY_LoadFlag,KEY_ScanMode,KEY_StartP,KEY_EndP,KEY_ScanCount,KEY_LaserIP
		//orderNO,SCAN_RGV_FLAG(1-RGV整车扫描， 2-RGV分段扫描 ，3卡车扫描)
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() != 13)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string keyTreatmentNo = "";
		if (false == SQL4Parking::SelScanNO4Car(keyTreatmentNo))
		{
			log.Info()<<"SelScanNO4Car is ERROR, return false..........."<<endl;
			return;
		}

		string KEY_CraneNo = kValues[0];
		string KEY_MessageNo = kValues[1];
		string KEY_TreatmentNo = keyTreatmentNo;
		string KEY_ParkingNo = kValues[2];
		string KEY_VehicleType = kValues[3];
		string KEY_MaterialType = kValues[4];
		string KEY_LoadFlag = kValues[5];
		string KEY_ScanMode = kValues[6];
		string KEY_StartP = kValues[7];
		string KEY_EndP = kValues[8];
		string KEY_ScanCount = kValues[9];
		string KEY_LaserIP = kValues[10];

		long orderNO = StringHelper::ToNumber<long>(kValues[11]);
		string scanRGVFlag = kValues[12];

		long startPoint = StringHelper::ToNumber<long>(KEY_StartP);
		long endPoint = StringHelper::ToNumber<long>(KEY_EndP);

		long scanCount = StringHelper::ToNumber<long>(KEY_ScanCount);

		//组织json发送数据格式
		//  电文号#json数据
		string json1 = "\"KEY_CraneNo\":\"" + KEY_CraneNo + "\",";
		json1 += "\"KEY_MessageNo\":\"" + KEY_MessageNo + "\",";
		json1 += "\"KEY_TreatmentNo\":\"" + KEY_TreatmentNo + "\",";
		json1 += "\"KEY_ParkingNo\":\"" + KEY_ParkingNo + "\",";
		json1 += "\"KEY_VehicleType\":\"" + KEY_VehicleType + "\",";
		json1 += "\"KEY_MaterialType\":\"" + KEY_MaterialType + "\",";
		json1 += "\"KEY_LoadFlag\":\"" + KEY_LoadFlag + "\",";
		json1 += "\"KEY_ScanMode\":\"" + KEY_ScanMode + "\",";
		json1 += "\"KEY_StartP\":\"" + KEY_StartP + "\",";
		json1 += "\"KEY_EndP\":\"" + KEY_EndP + "\",";
		json1 += "\"KEY_ScanCount\":\"" + KEY_ScanCount + "\",";
		json1 += "\"KEY_LaserIP\":\"" + KEY_LaserIP + "\"";

		string sndJson = "{" + json1 +"}";

		string sndTel = m_strMsgId + "#" + sndJson;

		log.Info()<<"sndTel = "<<sndTel<<endl;

		ArrayMsg arrayMsgDataBuf;
		for (int i = 0; i < sndTel.length(); i ++)
		{
			arrayMsgDataBuf.push_back(*(sndTel.c_str() + i));
		}
		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		int lineNO = 0;
		if (false == SQL4Parking::SelComLineNO("SRS", lineNO ))
		{
			log.Info()<<"SelComLineNO is ERROR, return false............"<<endl;
			return;
		}

		int ret = PCS_Send(lineNO, m_strMsgId, arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;
		log.Info()<<endl<<"UL01 sended out .. "<<endl;

		//根据停车位号获取当前停车位处理号
		string parkingTreatmentNO = "";
		string carNO = "";
		//RGV扫描 
		if (scanRGVFlag == "1" || scanRGVFlag == "2")
		{
			//不需要停车位处理号
			SQL4Parking::SelRGVNO(KEY_ParkingNo, carNO);
		}
		//卡车扫描
		else
		{
			SQL4Parking::SelParkingTreatmentNOCarNO(KEY_ParkingNo, parkingTreatmentNO, carNO);
		}
		

		//准备插入激光车辆扫描表
		SQL4Parking::InsParkingSRSCarInfo(keyTreatmentNo,
																		parkingTreatmentNO, 
																		KEY_ParkingNo, 
																		carNO, 
																		KEY_VehicleType, 
																		KEY_MaterialType, 
																		KEY_LoadFlag, 
																		KEY_ScanMode, 
																		orderNO, 
																		KEY_MessageNo, 
																		KEY_CraneNo, 
																		startPoint, 
																		endPoint, 
																		scanCount, 
																		KEY_LaserIP, 
																		scanRGVFlag);
	}
	catch (std::exception& ex)
	{
		log.Info()<<endl<<"UL01 sended error .. "<<endl;
	}
	catch (...)
	{
		log.Info()<<endl<<"UL01 sended error .. "<<endl;
	}
}
