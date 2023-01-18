#include "MsgLU02.h"
#include "SQL4Parking.h"

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;

MsgLU02*  MsgLU02::m_pMsgLU02 = NULL;

MsgLU02::MsgLU02() 
{

}

MsgLU02 :: ~MsgLU02(void)
{
	delete m_pMsgLU02;
}

MsgLU02* MsgLU02::getInstance(void)
{
	if (m_pMsgLU02 == NULL)
	{
		m_pMsgLU02 = new MsgLU02;
	}
	return m_pMsgLU02;
}

string MsgLU02 :: getMsgID()
{
	return m_strMsgId;
}
void MsgLU02 :: setMsgID(string theVal)
{
	m_strMsgId = theVal;
}


ByteSeq MsgLU02::HandleMessage(const SmartData& sd)
{
	string functionName = "MsgLU02 :: HandleMessage()";
	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{
		//��ӡ��������־ ����ʱ��
		string JsonData = "";
		log.Info()<<"\t"<< sd.toString() << endl;
		JsonData=sd["JsonData"].toString();
		if(JsonData == "{}")
		{
			log.Debug()<<"No strJsonScanResult............return.............."<<endl;
			return ret;
		}
		//��ȡLU02��json��ʽ��smartdata��ʽ
		SmartData sdLU02SD = MsgSmartDataManager::InsRef().GetMsgSmartData("LU02SD");
		if( MsgLU02Convert(JsonData, sdLU02SD) == false)
		{
			log.Debug()<<"MsgLU02Convert  FAILED! return.................."<<endl;
			return ret;
		}

		//��SD���ݽ������ݿ�����
		string scanNO = sdLU02SD["KEY_TreatmentNo"].toString();
		string scanResult = sdLU02SD["KEY_ResultState"].toString();
		long pointX1 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][0]["KEY_PointX"].toString());
		long pointY1 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][0]["KEY_PointY"].toString());
		long pointZ1 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][0]["KEY_PointZ"].toString());
		long pointX2 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][1]["KEY_PointX"].toString());
		long pointY2 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][1]["KEY_PointY"].toString());
		long pointZ2 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][1]["KEY_PointZ"].toString());
		long pointX3 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][2]["KEY_PointX"].toString());
		long pointY3 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][2]["KEY_PointY"].toString());
		long pointZ3 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][2]["KEY_PointZ"].toString());
		long pointX4 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][3]["KEY_PointX"].toString());
		long pointY4 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][3]["KEY_PointY"].toString());
		long pointZ4 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][3]["KEY_PointZ"].toString());
		long pointX = 0;//��ʱ�޽ӿ� �����ټ�
		long pointY = 0;
		long pointZ = 0;

		long orderNO = 0;
		string scanRGVFlag = "";
		string parkingNO = "";
		SQL4Parking::UpdParkingSRSCarInfo(scanNO, 
																			scanResult,
																			pointX1, 
																			pointY1, 
																			pointZ1, 
																			pointX2, 
																			pointY2, 
																			pointZ2, 
																			pointX3, 
																			pointY3,	
																			pointZ3, 
																			pointX4, 
																			pointY4, 
																			pointZ4, 
																			pointX, 
																			pointY, 
																			pointZ, 
																			orderNO, 
																			scanRGVFlag,
																			parkingNO);

		if (scanResult != "1")
		{
			log.Info()<<" SRS Scan Car FAILED...........scanResult = "<<scanResult<<", return false............"<<endl;
			return ret;
		}

		if (scanRGVFlag == "1")//rgv����ɨ������ д��UACS_PARKING_RGV_STATUS
		{
			//��ȡRGV�м���ɨ��������X�����С  Y�����С
			long xMax = GetMax(pointX1, pointX2, pointX3, pointX4);
			long xMin = GetMin(pointX1, pointX2, pointX3, pointX4);
			long yMax = GetMax(pointY1, pointY2, pointY3, pointY4);
			long yMin = GetMin(pointY1, pointY2, pointY3, pointY4);

			SQL4Parking::UpdParkingRGVStatusSRS(parkingNO, xMin, xMax, yMin, yMax);
		}

//==============================================================================================================
//=====20220816 zhangyuhong add
//���ڳ���ɨ�����ֻ���س�����ܽ���������ط��ϵ�������˲���Ҫ��tag��֪ͨ��ֻ��������ݱ��ɣ�������´�������
//==============================================================================================================
/*
		//���г����ͼ�������
		//tagName = EV_PARKING_SRS_CAR_INFO
		//tagValue = �г���,ָ���,����ɨ���,ȡ���ϱ�ǣ�0-ȡ�� 1-����  �����ǹ̶����ϱ�� 1��,��ɨ���־(1-RGV����ɨ�� 2-RGV�ֶ�ɨ�� 3-��������ɨ��)��pointX��pointY��pointZ
		string craneNO = sdLU02SD["KEY_CraneNo"].toString();
		string strOrderNO = StringHelper::ToString(orderNO);
		//scanNO
		string scanType = "1";
		//scanRGVFlag 
		string strPointX = StringHelper::ToString(pointX);
		string strPointY = StringHelper::ToString(pointY);
		string strPointZ = StringHelper::ToString(pointZ);

		//���г��յ������scanRGVFlag��
		//1. RGV����ɨ�� ���г�ģ��д��scanNO����ǰָ���,  ����ȡ UACS_PARKING_RGV_STATUS����ȡRGV����ɨ�����ݣ�Ȼ�����ֶ�ɨ������ ���͸�parkingģ���ٽ���������������ɨ��
		//2. RGV�ֶ�ɨ�裺�г�ģ��д��scanNO����ǰָ���,����strPointXYZ д�뵱ǰָ���
		//3. ��������ɨ�裺�г�ģ��д��scanNO����ǰָ���,����strPointXYZ д�뵱ǰָ���
		string tagName = "EV_PARKING_SRS_CAR_INFO";
		string tagValue = craneNO + "," + strOrderNO + "," + scanNO + "," + scanType + "," + scanRGVFlag + ","+strPointX + "," + strPointY + "," + strPointZ;
		EVTagSnd(tagName, tagValue);
*/
		


	}
	catch(iDA::Exception &x)
	{
		try
		{
			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage = stdex.what();
		string msg = functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;
}

bool	MsgLU02::MsgLU02Convert(string jsonStr, SmartData& sdJson)
{
	bool ret=false;
	string functionName="MsgLU02 :: MsgLU02Convert()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		bool bIsJsonStr = isJsonStr(jsonStr.c_str());
		if (!bIsJsonStr)
		{
			log.Info()<<"Receive From MsgLU02 Result String IS NOT Json format! Exit........."<<endl;
			return ret;
		}

		Json::Value root;
		Json::Reader reader;

		if (jsonStr !="{}" && reader.parse(jsonStr, root))
		{
			sdJson["KEY_CraneNo"] = root["KEY_CraneNo"].asString();//�г���
			sdJson["KEY_MessageNo"] = root["KEY_MessageNo"].asString();//�¼���			
			sdJson["KEY_TreatmentNo"] = root["KEY_TreatmentNo"].asString();//�����
			sdJson["KEY_ParkingNo"] = root["KEY_ParkingNo"].asString();//ͣ��λ��
			//�����ĸ�������
			//��1������
			sdJson["KEY_Boundary"][0]["KEY_PointX"] = root["KEY_Boundary"]["1"]["KEY_PointX"].asString();//X
			sdJson["KEY_Boundary"][0]["KEY_PointY"] = root["KEY_Boundary"]["1"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Boundary"][0]["KEY_PointZ"] = root["KEY_Boundary"]["1"]["KEY_PointZ"].asString();//Z
			//��2������
			sdJson["KEY_Boundary"][1]["KEY_PointX"] = root["KEY_Boundary"]["2"]["KEY_PointX"].asString();//X
			sdJson["KEY_Boundary"][1]["KEY_PointY"] = root["KEY_Boundary"]["2"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Boundary"][1]["KEY_PointZ"] = root["KEY_Boundary"]["2"]["KEY_PointZ"].asString();//Z
			//��3������
			sdJson["KEY_Boundary"][2]["KEY_PointX"] = root["KEY_Boundary"]["3"]["KEY_PointX"].asString();//X
			sdJson["KEY_Boundary"][2]["KEY_PointY"] = root["KEY_Boundary"]["3"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Boundary"][2]["KEY_PointZ"] = root["KEY_Boundary"]["3"]["KEY_PointZ"].asString();//Z
			//��4������
			sdJson["KEY_Boundary"][3]["KEY_PointX"] = root["KEY_Boundary"]["4"]["KEY_PointX"].asString();//X
			sdJson["KEY_Boundary"][3]["KEY_PointY"] = root["KEY_Boundary"]["4"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Boundary"][3]["KEY_PointZ"] = root["KEY_Boundary"]["4"]["KEY_PointZ"].asString();//Z

			sdJson["KEY_ResultState"] = root["KEY_ResultState"].asString();//����ɹ�/ʧ��

			//׼����ӡ��������
			string strstart = "\n========================Json String Convert Result========================";
			string str1 = "\n KEY_CraneNo:" + sdJson["KEY_CraneNo"].toString() + "\n KEY_MessageNo:" + sdJson["KEY_MessageNo"].toString();
			str1 += "\n KEY_TreatmentNo:" + sdJson["KEY_TreatmentNo"].toString() +"\n KEY_ParkingNo:" + sdJson["KEY_ParkingNo"].toString();
			str1 += "\n 1:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Boundary"][0]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Boundary"][0]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Boundary"][0]["KEY_PointZ"].toString();
			str1 += "\n 2:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Boundary"][1]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Boundary"][1]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Boundary"][1]["KEY_PointZ"].toString();
			str1 += "\n 3:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Boundary"][2]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Boundary"][2]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Boundary"][2]["KEY_PointZ"].toString();
			str1 += "\n 4:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Boundary"][3]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Boundary"][3]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Boundary"][3]["KEY_PointZ"].toString();

			str1 += "\n KEY_ResultState:" + sdJson["KEY_ResultState"].toString(); 
			string strend = "\n=================================================================";
			string strall = strstart + str1 + strend;
			log.Info()<<strall<<endl;

			ret = true;
			return ret;

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
	return ret;

}

bool	MsgLU02::isJsonStr(const char *jsoncontent)
{
	std::stack<char> jsonstr;
	const char *p = jsoncontent;
	char startChar = jsoncontent[0];
	char endChar = '\0';
	bool isObject = false; //��ֹ {}{}���ж�
	bool isArray = false;  //��ֹ[][]���ж�

	while (*p != '\0')
	{
		endChar = *p;
		switch (*p)
		{
		case '{':
			if (!isObject)
			{
				isObject = true;
			}
			else if (jsonstr.empty()) //�����ظ���ջ
			{
				return false;
			}
			jsonstr.push('{');
			break;
		case '"':
			if (jsonstr.empty() || jsonstr.top() != '"')
			{
				jsonstr.push(*p);
			}
			else
			{
				jsonstr.pop();
			}
			break;
		case '[':
			if (!isArray)
			{
				isArray = true;
			}
			else if (jsonstr.empty()) //�����ظ���ջ
			{
				return false;
			}
			jsonstr.push('[');
			break;
		case ']':
			if (jsonstr.empty() || jsonstr.top() != '[')
			{
				return false;
			}
			else
			{
				jsonstr.pop();
			}
			break;
		case '}':
			if (jsonstr.empty() || jsonstr.top() != '{')
			{
				return false;
			}
			else
			{
				jsonstr.pop();
			}
			break;
		case '\\': //��ת����ַ�,����
			p++;
			break;
		default:;
		}
		p++;
	}

	if (jsonstr.empty())
	{
		//ȷ���Ƕ������������,֮��Ķ�������Ч
		switch (startChar) //ȷ����β���Ŷ�Ӧ
		{
		case '{':
			{
				if (endChar = '}')
				{
					return true;
				}
				return false;
			}
		case '[':
			{
				if (endChar = ']')
				{
					return true;
				}
				return false;
			}
		default:
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}


bool MsgLU02::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgLU02 :: EVTagSnd()";
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

long MsgLU02::GetMax(long a, long b, long c, long d)
{
	string functionName="MsgLU02 :: GetMax()";
	LOG log(functionName, AUTO_CATCH_PID);
	long maxValue = a;
	try
	{
		if (b >maxValue)
		{
			maxValue = b;
		}
		if (c > maxValue)
		{
			maxValue = c;
		}
		if (d > maxValue)
		{
			maxValue = d;
		}
	}
	catch(...)
	{
		log.Debug()<<"GetMax  error..........."<<endl;
	}
	return maxValue;
}

long MsgLU02::GetMin(long a, long b, long c, long d)
{
	string functionName="MsgLU02 :: GetMin()";
	LOG log(functionName, AUTO_CATCH_PID);
	long minValue = a;
	try
	{
		if (b < minValue)
		{
			minValue = b;
		}
		if (c < minValue)
		{
			minValue = c;
		}
		if (d < minValue)
		{
			minValue = d;
		}
	}
	catch(...)
	{
		log.Debug()<<"GetMin  error..........."<<endl;
	}
	return minValue;
}