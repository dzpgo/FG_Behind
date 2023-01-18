#include "MsgEU02.h"



using namespace Monitor;
using namespace iPlature;



MsgEU02*  MsgEU02::m_pMsgEU02 = NULL;


MsgEU02::MsgEU02() 
{
	msgId="EU01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgEU02 :: ~MsgEU02(void)
{
	
	delete m_pMsgEU02;


}

 MsgEU02* MsgEU02::getInstance(void)
{
	if (m_pMsgEU02 == NULL)
	{
		m_pMsgEU02 = new MsgEU02;
	}
	return m_pMsgEU02;
}

ByteSeq MsgEU02::HandleMessage(const ByteSeq& ParamBuffer)
{
	string functionName="MsgEU02 :: HandleMessage()";

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

		//1		出钢钢号1
		log.Info()<<"\t\t HTNO1="<<sd["HTNO1"].toString();

		//2		变更前PONO1
		log.Info()<<"\t\t PONO1="<<sd["PONO1"].toString();

		//3		炉次等级1
		log.Info()<<"\t\t HEAT_CLASS1="<<sd["HEAT_CLASS1"].toString();

		//4		保留代码1
		log.Info()<<"\t\t KEEP_CODE1="<<sd["KEEP_CODE1"].toString();

		//5		变更后PONO2
		log.Info()<<"\t\t PONO2="<<sd["PONO2"].toString();

		//6		炉次等级2
		log.Info()<<"\t\t HEAT_CLASS2="<<sd["HEAT_CLASS2"].toString();

		//7		保留代码2
		log.Info()<<"\t\t KEEP_CODE2="<<sd["KEEP_CODE2"].toString();

		//8		变更工位点
		log.Info()<<"\t\t CHANGING_SECTION="<<sd["CHANGING_SECTION"].toString();
	
		//		接收时刻
		log.Info()<<"\t\t RCV_TIME="<<iDA::DateTime::Now().ToShortTimeString()<<endl;

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



