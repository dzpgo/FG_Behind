#include "MsgLU01.h"
#include "SQL4Parking.h"

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;

MsgLU01*  MsgLU01::m_pMsgLU01 = NULL;

MsgLU01::MsgLU01() 
{

}

MsgLU01 :: ~MsgLU01(void)
{
	delete m_pMsgLU01;
}

MsgLU01* MsgLU01::getInstance(void)
{
	if (m_pMsgLU01 == NULL)
	{
		m_pMsgLU01 = new MsgLU01;
	}
	return m_pMsgLU01;
}

string MsgLU01 :: getMsgID()
{
	return m_strMsgId;
}
void MsgLU01 :: setMsgID(string theVal)
{
	m_strMsgId = theVal;
}


ByteSeq MsgLU01::HandleMessage(const SmartData& sd)
{
	string functionName = "MsgLU01 :: HandleMessage()";
	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{
		//打印到测试日志 接收时间
		log.Info()<<sd.toString()<<endl;
		string JsonData = "";
		JsonData=sd["JsonData"].toString();
		if(JsonData == "{}")
		{
			log.Debug()<<"No strJsonScanResult............return.............."<<endl;
			return ret;
		}
		//获取LU01的json格式的smartdata格式
		SmartData sdLU01SD = MsgSmartDataManager::InsRef().GetMsgSmartData("LU01SD");
		if( MsgLU01Convert(JsonData, sdLU01SD) == false)
		{
			log.Debug()<<"MsgLU01Convert  FAILED! return.................."<<endl;
			return ret;
		}

		//对SD数据进行数据库表操作
		string scanNO = sdLU01SD["KEY_TreatmentNo"].toString();
		long pointX = StringHelper::ToNumber<long>(sdLU01SD["KEY_Points"][0]["KEY_PointX"].toString());
		long pointY = StringHelper::ToNumber<long>(sdLU01SD["KEY_Points"][0]["KEY_PointY"].toString());
		long pointZ = StringHelper::ToNumber<long>(sdLU01SD["KEY_Points"][0]["KEY_PointZ"].toString());
		string scanResult = sdLU01SD["KEY_ResultState"].toString(); 

		long orderNO = 0;
		SQL4Parking::UpdParkingSRSMatInfo(scanNO, 
																			 scanResult, 
																			 pointX, 
																			 pointY, 
																			 pointZ, 
																			 orderNO);

		if (scanResult != "1")
		{
			log.Info()<<" SRS Scan Mat FAILED...........scanResult = "<<scanResult<<", return false............"<<endl;
			return ret;
		}

		//向行车发送激光数据
		//tagName = EV_PARKING_SRS_MAT_INFO
		//tagValue = 行车号,指令号,激光扫描号,取放料标记（0-取料 1-放料）,pointX，pointY，pointZ
		string craneNO = sdLU01SD["KEY_CraneNo"].toString();
		string strOrderNO = StringHelper::ToString(orderNO);
		//scanNO
		string scanType = sdLU01SD["KEY_ActionType"].toString();
		string strPointX = StringHelper::ToString(pointX);
		string strPointY = StringHelper::ToString(pointY);
		string strPointZ = StringHelper::ToString(pointZ);

		string tagName = "EV_PARKING_SRS_MAT_INFO";
		string tagValue = craneNO + "," + strOrderNO + "," + scanNO + "," + scanType + "," + strPointX + "," + strPointY + "," + strPointZ;
		EVTagSnd(tagName, tagValue);



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

bool	MsgLU01::MsgLU01Convert(string jsonStr, SmartData& sdJson)
{
	bool ret=false;
	string functionName="MsgLU01 :: MsgLU01Convert()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		bool bIsJsonStr = isJsonStr(jsonStr.c_str());
		if (!bIsJsonStr)
		{
			log.Info()<<"Receive From MsgLU01 Result String IS NOT Json format! Exit........."<<endl;
			return ret;
		}

		Json::Value root;
		Json::Reader reader;

		if (jsonStr !="{}" && reader.parse(jsonStr, root))
		{
			sdJson["KEY_MessageNo"] = root["KEY_MessageNo"].asString();//事件号
			sdJson["KEY_TreatmentNo"] = root["KEY_TreatmentNo"].asString();//处理号
			sdJson["KEY_CraneNo"] = root["KEY_CraneNo"].asString();//行车号
			sdJson["KEY_ActionType"] = root["KEY_ActionType"].asString();//动作标记 取料 放料
			sdJson["KEY_Points"][0]["KEY_PointX"] = root["KEY_Points"]["1"]["KEY_PointX"].asString();//X
			sdJson["KEY_Points"][0]["KEY_PointY"] = root["KEY_Points"]["1"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Points"][0]["KEY_PointZ"] = root["KEY_Points"]["1"]["KEY_PointZ"].asString();//Z
			sdJson["KEY_ResultState"] = root["KEY_ResultState"].asString();//计算成功/失败

			//准备打印所有数据
			string strstart = "\n========================Json String Convert Result========================";
			string str1 = "\n KEY_MessageNo:" + sdJson["KEY_MessageNo"].toString() + "\n KEY_TreatmentNo:" + sdJson["KEY_TreatmentNo"].toString();
			str1 += "\n KEY_CraneNo:" + sdJson["KEY_CraneNo"].toString() +"\n KEY_ActionType:" + sdJson["KEY_ActionType"].toString();
			str1 += "\n 1:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Points"][0]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Points"][0]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Points"][0]["KEY_PointZ"].toString();
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

bool	MsgLU01::isJsonStr(const char *jsoncontent)
{
	std::stack<char> jsonstr;
	const char *p = jsoncontent;
	char startChar = jsoncontent[0];
	char endChar = '\0';
	bool isObject = false; //防止 {}{}的判断
	bool isArray = false;  //防止[][]的判断

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
			else if (jsonstr.empty()) //对象重复入栈
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
			else if (jsonstr.empty()) //数组重复入栈
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
		case '\\': //被转义的字符,跳过
			p++;
			break;
		default:;
		}
		p++;
	}

	if (jsonstr.empty())
	{
		//确保是对象或者是数组,之外的都不算有效
		switch (startChar) //确保首尾符号对应
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


bool MsgLU01::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgLU01 :: EVTagSnd()";
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