
//激光扫描启动电文MsgUL01
#include "MsgUL01.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "SQL4SRS.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgUL01::MsgUL01(void)
{
	m_strMsgId = "UL01";
}

MsgUL01::~MsgUL01(void)
{

}


void MsgUL01::HandleMessage(const string strValue, const string logFileName)
{
	LOG log("MsgUL01::HandleMessage",logFileName);
	try
	{
		//strValue格式：
		//KEY_MessageNo,KEY_CraneNo,KEY_ActionType,KEY_CraneX,KEY_CraneY, orderNO, cmdSeq, areaType,areaNO，
		//（车辆上料取料点请求/库区倒料取料点请求/库区倒料放料点请求）KEY_AreaStartX,KEY_AreaEndX,KEY_AreaStartY,KEY_AreaEndY,
		//（车辆上料放料点请求）KEY_PointX1，KEY_PointY1,KEY_PointZ1,KEY_PointX2，KEY_PointY2,KEY_PointZ2,KEY_PointX3，KEY_PointY3,KEY_PointZ3,KEY_PointX4，KEY_PointY4,KEY_PointZ4
		//其中，处理号 KEY_TreatmentNo 由本模块生成

		//KEY_MessageNo=1001  KEY_ActionType=0  ：车辆上料取料点请求
		//KEY_MessageNo=1001  KEY_ActionType=1  ：车辆上料放料点请求  : 这个比较特殊，传过来的字段比其它事件多
		//KEY_MessageNo=1003  KEY_ActionType=0  ：库区倒料取料点请求
		//KEY_MessageNo=1003  KEY_ActionType=1  ：库区倒料放料点请求

		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 13)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string keyTreatmentNo = "";
		if (false == SQL4SRS::SelScanNO4Mat(keyTreatmentNo))
		{
			log.Info()<<"SelScanNO4Mat is ERROR, return false..........."<<endl;
			return;
		}		

		string KEY_MessageNo = kValues[0];
		string KEY_TreatmentNo = keyTreatmentNo;
		string KEY_CraneNo = kValues[1];
		string KEY_ActionType = kValues[2];
		string KEY_CraneX = kValues[3];
		string KEY_CraneY = kValues[4];
		long orderNO = StringHelper::ToNumber<long>(kValues[5]);
		long cmdSeq = StringHelper::ToNumber<long>(kValues[6]);
		string areaType = kValues[7];
		string areaNO = kValues[8];

		long actX = StringHelper::ToNumber<long>(KEY_CraneX);
		long actY = StringHelper::ToNumber<long>(KEY_CraneY);

		string KEY_PointX1 = "0";
		string KEY_PointY1 = "0";
		string KEY_PointZ1 = "0";
		string KEY_PointX2 = "0";
		string KEY_PointY2 = "0";
		string KEY_PointZ2 = "0";
		string KEY_PointX3 = "0";
		string KEY_PointY3 = "0";
		string KEY_PointZ3 = "0";
		string KEY_PointX4 = "0";
		string KEY_PointY4 = "0";
		string KEY_PointZ4 = "0";

		string KEY_AreaStartX = "0";
		string KEY_AreaEndX = "0";
		string KEY_AreaStartY = "0";
		string KEY_AreaEndY = "0";

		if (KEY_MessageNo == "1001" && KEY_ActionType == "1")
		{
			KEY_PointX1 = kValues[9];
			KEY_PointY1 = kValues[10];
			KEY_PointZ1 = kValues[11];
			KEY_PointX2 = kValues[12];
			KEY_PointY2 = kValues[13];
			KEY_PointZ2 = kValues[14];
			KEY_PointX3 = kValues[15];
			KEY_PointY3 = kValues[16];
			KEY_PointZ3 = kValues[17];
			KEY_PointX4 = kValues[18];
			KEY_PointY4 = kValues[19];
			KEY_PointZ4 = kValues[20];
		}

		long carPointX1 = StringHelper::ToNumber<long>(KEY_PointX1);
		long carPointY1 = StringHelper::ToNumber<long>(KEY_PointY1);
		long carPointZ1 = StringHelper::ToNumber<long>(KEY_PointZ1);
		long carPointX2 = StringHelper::ToNumber<long>(KEY_PointX2);
		long carPointY2 = StringHelper::ToNumber<long>(KEY_PointY2);
		long carPointZ2 = StringHelper::ToNumber<long>(KEY_PointZ2);
		long carPointX3 = StringHelper::ToNumber<long>(KEY_PointX3);
		long carPointY3 = StringHelper::ToNumber<long>(KEY_PointY3);
		long carPointZ3 = StringHelper::ToNumber<long>(KEY_PointZ3);
		long carPointX4 = StringHelper::ToNumber<long>(KEY_PointX4);
		long carPointY4 = StringHelper::ToNumber<long>(KEY_PointY4);
		long carPointZ4 = StringHelper::ToNumber<long>(KEY_PointZ4);

		if (KEY_MessageNo == "1001" && KEY_ActionType == "0" || KEY_MessageNo == "1003" && KEY_ActionType == "0" || KEY_MessageNo == "1003" && KEY_ActionType == "1" )
		{
			KEY_AreaStartX = kValues[8];
			KEY_AreaEndX = kValues[9];
			KEY_AreaStartY = kValues[10];
			KEY_AreaEndY = kValues[11];
		}

		long startX = StringHelper::ToNumber<long>(KEY_AreaStartX);
		long endX = StringHelper::ToNumber<long>(KEY_AreaEndX);
		long startY = StringHelper::ToNumber<long>(KEY_AreaStartY);
		long endY = StringHelper::ToNumber<long>(KEY_AreaEndY);

		//组织json发送数据格式
		//  电文号#json数据
		string json1 = "";

		if (KEY_MessageNo == "1001" && KEY_ActionType == "1")
		{
			json1 += "\"KEY_MessageNo\":\"" + KEY_MessageNo + "\",";
			json1 += "\"KEY_TreatmentNo\":\"" + KEY_TreatmentNo + "\",";
			json1 += "\"KEY_CraneNo\":\"" + KEY_CraneNo + "\",";
			json1 += "\"KEY_ActionType\":\"" + KEY_ActionType + "\",";
			json1 += "\"KEY_CraneX\":\"" + KEY_CraneX + "\",";
			json1 += "\"KEY_CraneY\":\"" + KEY_CraneY + "\",";
			//车辆框架4个点坐标
			json1 += "\"KEY_Boundary\":{";
			string jsonP1 = "\"1\":{\"KEY_PointX1\":\"" + KEY_PointX1 + "\"," + "\"KEY_PointY1\":\"" + KEY_PointY1 + "\"," + "\"KEY_PointZ1\":\"" + KEY_PointZ1 + "\"}";
			string jsonP2 = "\"2\":{\"KEY_PointX2\":\"" + KEY_PointX2 + "\"," + "\"KEY_PointY2\":\"" + KEY_PointY2 + "\"," + "\"KEY_PointZ2\":\"" + KEY_PointZ2 + "\"}";
			string jsonP3 = "\"3\":{\"KEY_PointX3\":\"" + KEY_PointX3 + "\"," + "\"KEY_PointY3\":\"" + KEY_PointY3 + "\"," + "\"KEY_PointZ3\":\"" + KEY_PointZ3 + "\"}";
			string jsonP4 = "\"4\":{\"KEY_PointX4\":\"" + KEY_PointX4 + "\"," + "\"KEY_PointY4\":\"" + KEY_PointY4 + "\"," + "\"KEY_PointZ4\":\"" + KEY_PointZ4 + "\"}";
			json1 += jsonP1 + "," + jsonP2 + "," + jsonP3 + "," + jsonP4 + "}";
		}


		if (KEY_MessageNo == "1001" && KEY_ActionType == "0" || KEY_MessageNo == "1003" && KEY_ActionType == "0" || KEY_MessageNo == "1003" && KEY_ActionType == "1" )
		{
			json1 += "\"KEY_MessageNo\":\"" + KEY_MessageNo + "\",";
			json1 += "\"KEY_TreatmentNo\":\"" + KEY_TreatmentNo + "\",";
			json1 += "\"KEY_CraneNo\":\"" + KEY_CraneNo + "\",";
			json1 += "\"KEY_ActionType\":\"" + KEY_ActionType + "\",";
			json1 += "\"KEY_AreaStartX\":\"" + KEY_AreaStartX + "\",";
			json1 += "\"KEY_AreaEndX\":\"" + KEY_AreaEndX + "\",";
			json1 += "\"KEY_AreaStartY\":\"" + KEY_AreaStartY + "\",";
			json1 += "\"KEY_AreaEndY\":\"" + KEY_AreaEndY + "\",";
			json1 += "\"KEY_CraneX\":\"" + KEY_CraneX + "\",";
			json1 += "\"KEY_CraneY\":\"" + KEY_CraneY + "\"";
		}
		
		

		string sndJson = "{" + json1 +"}";

		//string sndTel = m_strMsgId + "#" + sndJson;

		//20220930 zhangyuhong add
		//不再附加电文号
		string sndTel = sndJson;

		log.Info()<<"sndTel = "<<sndTel<<endl;
	
		ArrayMsg arrayMsgDataBuf;
		for (int i = 0; i < sndTel.length(); i ++)
		{
			arrayMsgDataBuf.push_back(*(sndTel.c_str() + i));
		}
		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		int lineNO = 0;
		string lineName = "SRS_" + KEY_CraneNo;
		if (false == SQL4SRS::SelComLineNO(lineName, lineNO ))
		{
			log.Info()<<"SelComLineNO is ERROR, return false............"<<endl;
			return;
		}

		log.Info()<<"SRS lineNO = "<<lineNO<<endl;

		int ret = PCS_Send(lineNO, m_strMsgId, arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;
		log.Info()<<endl<<"UL01 sended out ....... "<<endl;

		//准备插入激光料堆扫描表
		//区分是车辆上料放料请求还是其它
		if (KEY_MessageNo == "1001" && KEY_ActionType == "1")
		{
			SQL4SRS::InsParkingSRSMatInfo2(keyTreatmentNo,
																				areaType, 
																				areaNO, 
																				orderNO, 
																				KEY_MessageNo, 
																				KEY_CraneNo, 
																				KEY_ActionType, 
																				carPointX1, 
																				carPointY1, 
																				carPointZ1, 
																				carPointX2, 
																				carPointY2, 
																				carPointZ2, 
																				carPointX3, 
																				carPointY3, 
																				carPointZ3, 
																				carPointX4, 
																				carPointY4, 
																				carPointZ4, 
																				actX, 
																				actY);
		}



		if (KEY_MessageNo == "1001" && KEY_ActionType == "0" || KEY_MessageNo == "1003" && KEY_ActionType == "0" || KEY_MessageNo == "1003" && KEY_ActionType == "1" )
		{
			SQL4SRS::InsParkingSRSMatInfo(keyTreatmentNo,
																			areaType, 
																			areaNO, 
																			orderNO, 
																			KEY_MessageNo, 
																			KEY_CraneNo, 
																			KEY_ActionType, 
																			startX, 
																			endX, 
																			startY, 
																			endY, 
																			actX, 
																			actY);
		}
		

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
