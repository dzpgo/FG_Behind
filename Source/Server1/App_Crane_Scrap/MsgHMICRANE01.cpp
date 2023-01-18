#include "MsgHMICRANE01.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;



MsgHMICRANE01*  MsgHMICRANE01::m_pMsgHMICRANE01 = NULL;



MsgHMICRANE01::MsgHMICRANE01() 
{
	
}


MsgHMICRANE01 :: ~MsgHMICRANE01(void)
{
	
	delete m_pMsgHMICRANE01;


}

 MsgHMICRANE01* MsgHMICRANE01::getInstance(void)
{
	if (m_pMsgHMICRANE01 == NULL)
	{
		m_pMsgHMICRANE01 = new MsgHMICRANE01;
	}
	return m_pMsgHMICRANE01;
}




bool MsgHMICRANE01::HandleMessage(string myCraneNO,string messageData)
{
	string functionName="MsgHMICRANE01 :: HandleMessage()";

	bool ret=true;

	LOG log(functionName, AUTO_CATCH_PID);


	AlarmWrapper _p("");

	try
	{
		log.Debug()<<"........................................................................................log of  data int the message HMICRANE01..................................................................................................................."<<endl;

		log.Debug()<<"messageData="<<messageData<<endl;

		vector<string> vectorMessageItems;
		vectorMessageItems= StringHelper::ToVector<string>(messageData, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

		if(vectorMessageItems.size() != 1)
		{
					log.Debug()<<"HMICRANE01 data has error format"<<endl;
					return false;
		}
		string craneNOInMessage=vectorMessageItems[0];
		StringHelper::Trim(craneNOInMessage);

		if(myCraneNO!=craneNOInMessage)
		{
					log.Debug()<<"HMICRANE01 include a wrong craneNO"<<endl;
					return false;
		}

		string strCmdCode=vectorMessageItems[1];
		StringHelper::Trim(strCmdCode);
		
		bool cmdCodeFormatOK=false;
		if (strCmdCode==StringHelper::ToString( CranePLCShortCmdBase::SHORT_CMD_NORMAL_STOP )  ||  
			strCmdCode==StringHelper::ToString( CranePLCShortCmdBase::SHORT_CMD_CANCEL_COMPUTER_AUTO )  ||
			strCmdCode==StringHelper::ToString( CranePLCShortCmdBase::SHORT_CMD_ASK_COMPUTER_AUTO ) || 
			strCmdCode==StringHelper::ToString( CranePLCShortCmdBase::SHORT_CMD_EMG_STOP ) || 
			strCmdCode==StringHelper::ToString( CranePLCShortCmdBase::SHORT_CMD_RESET) )
		{
			cmdCodeFormatOK=true;
		}
	
		if(cmdCodeFormatOK==false)
		{
				log.Debug()<<"HMICRANE01 command Code is not defined"<<endl;
				return false;
		}
		long cmdCode=StringHelper::ToNumber<long>(vectorMessageItems[1]);

		log.Debug()<<"......"<<endl;
		log.Debug()<<"........................................................................................now begin to send the message to PLC..................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;

		CranePLCShortCmdBase cranePLCShortCmdBase;
		cranePLCShortCmdBase.setCraneNO(craneNOInMessage);
		cranePLCShortCmdBase.setCmdCode(cmdCode);

		CraneMonitor::getInstance()->DownLoadCranePLCShortCmd(cranePLCShortCmdBase);

		log.Debug()<<"........................................................................................sending message to PLC finished........................................................................................................................"<<endl;











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









