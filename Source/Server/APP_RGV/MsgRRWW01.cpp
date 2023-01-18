#include "MsgRRWW01.h"
#include "SQL4RGV.h"



using namespace Monitor;
using namespace iPlature;



MsgRRWW01*  MsgRRWW01::m_pMsgRRWW01 = NULL;


MsgRRWW01::MsgRRWW01() 
{
	msgId="RRWW01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgRRWW01 :: ~MsgRRWW01(void)
{
	
	delete m_pMsgRRWW01;


}

 MsgRRWW01* MsgRRWW01::getInstance(void)
{
	if (m_pMsgRRWW01 == NULL)
	{
		m_pMsgRRWW01 = new MsgRRWW01;
	}
	return m_pMsgRRWW01;
}

ByteSeq MsgRRWW01::HandleMessage(const ByteSeq& ParamBuffer)
{
	string functionName="MsgRRWW01 :: HandleMessage()";

	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{

		// 读取powertrans电文结构
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			readSmartDataSuccessed=true;
		}
		
				
		//读取原始字节流
		sd.readFrom(ParamBuffer);

		log.Info()<<"......"<<endl;
		log.Info()<<"........................................................................................log of samrt data..................................................................................................................."<<endl;
		log.Info()<<"......."<<endl;

		//RGV车辆到位信息
		//json格式字符串
		string strTelJson = sd["JsonData"].toString();
		log.Info()<<"\t\t RGV_ARRIVE_INFO="<<strTelJson;
		
		log.Info()<<"\t\t RCV_TIME="<<iDA::DateTime::Now().ToShortTimeString()<<endl;

		//解析json格式
		string rgvNo="";
		string parkNo="";
		long loadFlag;
		long troughDir;
		if (RRWW01Convert(strTelJson, rgvNo, parkNo, loadFlag, troughDir) == false)
		{
			log.Info()<<"RRWW01Convert  is  ERROR! return................."<<endl;
			return ret;
		}

		//写表或写tag点
		//1. 写表UACS_PARKING_RGV_STATUS
		string strLoadFlag = StringHelper::ToString(loadFlag);
		string strTroughDir = StringHelper::ToString(troughDir);
		SQL4RGV::UpdRGVStatusArrive(parkNo, rgvNo, strLoadFlag, strTroughDir);

		//2. 通知指令模块RGV车到位,可以根据炼钢计划生成指令
		string tagName = "EV_RGV_CAR_ARRIVE";
		string tagValue = parkNo + "," + rgvNo;
		EVTagSnd(tagName, tagValue);

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


bool	MsgRRWW01::RRWW01Convert(string jsonStr, 
																		string& rgvNo, 
																		string& parkNo, 
																		long& loadFlag, 
																		long& troughDir)
{
	bool ret=false;
	string functionName="MsgRRWW01 :: RRWW01Convert()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		bool bIsJsonStr = isJsonStr(jsonStr.c_str());
		if (!bIsJsonStr)
		{
			log.Info()<<"Receive Result String IS NOT Json format! Exit........."<<endl;
			return ret;
		}

		Json::Value root;
		Json::Reader reader;

		if (jsonStr !="{}" && reader.parse(jsonStr, root))
		{
			rgvNo = root["rgvNo"].asString();
			parkNo = root["parkNo"].asString();
			loadFlag = (long)root["loadFlag"].asInt();
			troughDir = (long)root["troughDir"].asInt();

			//准备打印所有数据
			string strstart = "\n========================Json String Convert Result========================";
			string str1 = "\n1....rgvNo =" + rgvNo;
			string str2 = "\n2....parkNo =" + parkNo;
			string str3 = "\n3....loadFlag =" + StringHelper::ToString(loadFlag);
			string str4 = "\n4....troughDir =" + StringHelper::ToString(troughDir);
			string strend = "\n=================================================================";

			string strall = strstart + str1+ str2 + str3 + str4 + strend;
			log.Info()<<strall<<endl;

			ret = true;
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


bool	MsgRRWW01::isJsonStr(const char *jsoncontent)
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


bool MsgRRWW01::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgRRWW01 :: EVTagSnd()";
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