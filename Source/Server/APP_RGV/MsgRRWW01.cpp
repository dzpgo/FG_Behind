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

		// ��ȡpowertrans���Ľṹ
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			readSmartDataSuccessed=true;
		}
		
				
		//��ȡԭʼ�ֽ���
		sd.readFrom(ParamBuffer);

		log.Info()<<"......"<<endl;
		log.Info()<<"........................................................................................log of samrt data..................................................................................................................."<<endl;
		log.Info()<<"......."<<endl;

		//RGV������λ��Ϣ
		//json��ʽ�ַ���
		string strTelJson = sd["JsonData"].toString();
		log.Info()<<"\t\t RGV_ARRIVE_INFO="<<strTelJson;
		
		log.Info()<<"\t\t RCV_TIME="<<iDA::DateTime::Now().ToShortTimeString()<<endl;

		//����json��ʽ
		string rgvNo="";
		string parkNo="";
		long loadFlag;
		long troughDir;
		if (RRWW01Convert(strTelJson, rgvNo, parkNo, loadFlag, troughDir) == false)
		{
			log.Info()<<"RRWW01Convert  is  ERROR! return................."<<endl;
			return ret;
		}

		//д���дtag��
		//1. д��UACS_PARKING_RGV_STATUS
		string strLoadFlag = StringHelper::ToString(loadFlag);
		string strTroughDir = StringHelper::ToString(troughDir);
		SQL4RGV::UpdRGVStatusArrive(parkNo, rgvNo, strLoadFlag, strTroughDir);

		//2. ָ֪ͨ��ģ��RGV����λ,���Ը������ּƻ�����ָ��
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

			//׼����ӡ��������
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