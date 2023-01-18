#include "MsgRRWW02.h"
#include "SQL4RGV.h"



using namespace Monitor;
using namespace iPlature;



MsgRRWW02*  MsgRRWW02::m_pMsgRRWW02 = NULL;


MsgRRWW02::MsgRRWW02() 
{
	msgId="RRWW02";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgRRWW02 :: ~MsgRRWW02(void)
{
	
	delete m_pMsgRRWW02;


}

 MsgRRWW02* MsgRRWW02::getInstance(void)
{
	if (m_pMsgRRWW02 == NULL)
	{
		m_pMsgRRWW02 = new MsgRRWW02;
	}
	return m_pMsgRRWW02;
}

ByteSeq MsgRRWW02::HandleMessage(const ByteSeq& ParamBuffer)
{
	string functionName="MsgRRWW02 :: HandleMessage()";

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

		//RGV����״̬����
		//json��ʽ�ַ���
		string strTelJson = sd["JsonData"].toString();
		log.Info()<<"\t\t RGV_LOCKING_LIST="<<strTelJson;		
		log.Info()<<"\t\t RCV_TIME="<<iDA::DateTime::Now().ToShortTimeString()<<endl;

		//����json��ʽ
		map<string, long> mapRGVList;
		if (RRWW02Convert(strTelJson, mapRGVList) == false)
		{
			log.Info()<<"RRWW02Convert  is  ERROR! return................."<<endl;
			return ret;
		}

		//д���дtag��
		//1. ���±� UACS_PARKING_RGV_STATUS
		map<string, long>::iterator itor;
		for (itor = mapRGVList.begin(); itor != mapRGVList.end(); itor++)
		{
			string rgvNO = itor->first;
			string lockFlag = StringHelper::ToString(itor->second);

			//1. �����źţ�����±���lockFlag�ֶ�Ϊ1
			if (lockFlag == "1")
			{
				SQL4RGV::UpdRGVStatusLock(rgvNO);
			}
			//2. �����ź�, ����ݳ�����ձ�������,��Ϊ������ζ�ų��뿪
			if (lockFlag == "0")
			{
				SQL4RGV::InitRGVStatusUnlock(rgvNO);
			}			
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


bool	MsgRRWW02::RRWW02Convert(string jsonStr, 
																		 map<string, long>& mapRGVLocking)
{
	bool ret=false;
	string functionName="MsgRRWW02 :: RRWW02Convert()";
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
		Json::Value rgvLockingList;
		Json::Reader reader;

		if (jsonStr !="{}" && reader.parse(jsonStr, root))
		{
			rgvLockingList = root["rgvLockingList"];
			long listNum = rgvLockingList.size();
			for (int i = 0; i < listNum; i++)
			{
				string rgvNo = rgvLockingList[i]["rgvNo"].asString();
				long  LockingFlag = (long)(rgvLockingList[i]["LockingFlag"].asInt());
				mapRGVLocking.insert(pair<string, long>(rgvNo, LockingFlag));
			}

			if (mapRGVLocking.size() <= 0)
			{
				log.Info()<<"mapRGVLocking.size() <= 0 ! Exit........."<<endl;
				ret = false;
				return ret;
			}

			//׼����ӡ��������
			string strstart = "\n========================Json String Convert Result========================";
			string str1 = "";
			map<string, long>::iterator itor;
			for (itor = mapRGVLocking.begin(); itor != mapRGVLocking.end(); ++itor)
			{
				str1 += "\n	rgvNo = " +  itor->first + " , LockingFlag = " + StringHelper::ToString(itor->second);
			}
			string strend = "\n=================================================================";
			string strall = strstart + str1+ strend;
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


bool	MsgRRWW02::isJsonStr(const char *jsoncontent)
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


bool MsgRRWW02::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgRRWW02 :: EVTagSnd()";
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



