#include "MsgEUCR02.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;


MsgEUCR02*  MsgEUCR02::m_pMsgEUCR02 = NULL;


MsgEUCR02::MsgEUCR02() 
{
	msgId="UC02";
}


MsgEUCR02 :: ~MsgEUCR02(void)
{
	
	delete m_pMsgEUCR02;


}

 MsgEUCR02* MsgEUCR02::getInstance(void)
{
	if (m_pMsgEUCR02 == NULL)
	{
		m_pMsgEUCR02 = new MsgEUCR02;
	}
	return m_pMsgEUCR02;
}




bool MsgEUCR02::SendOutMessage(CranePLCShortCmdBase cranePLCShortCmdBase)
{
	bool ret=true;
	string functionName="MsgCREU02 :: SendOutMessage()";


	LOG log(functionName, AUTO_CATCH_PID);


	AlarmWrapper _p("");

	try
	{

		log.Debug()<<"......"<<endl;
		log.Debug()<<"........................................................................................now begin to treat the message UC02.................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;

		ArrayMsg arrayMsgDataBuf;
		
		struct msgStruct4EUCR02
		{
			int craneNo;							//行车号
			int orderCode;							//命令代码
		}stuMsgData;

		//cranePLCOrderBase类里面的craneNO是string型，需要转换成int型，以供电文用（电文里是int型）
		vector<string> vec1 = StringHelper::Split(cranePLCShortCmdBase.getCraneNO(),'_');
		int craneNO1st = StringHelper::ToNumber<int>(vec1[0]);
		int craneNOlast = StringHelper::ToNumber<int>(vec1[1]);
		int trueCraneNO = craneNO1st*100 + craneNOlast;

		//组织发送电文数据
		stuMsgData.craneNo = trueCraneNO;
		stuMsgData.orderCode = cranePLCShortCmdBase.getCmdCode();

		arrayMsgDataBuf.resize(sizeof(stuMsgData));

		memcpy((void*)&arrayMsgDataBuf.front(),(char*)&stuMsgData,sizeof(stuMsgData));

		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//打印发送电文内容日志
		log.Debug()<<"craneNo="<<stuMsgData.craneNo<<endl;
		log.Debug()<<"orderID="<<stuMsgData.orderCode<<endl;

		
		//log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );



		int lineNO=11;

		log.Debug()<<"lineNO="<<lineNO<<endl;
		
		int ret=PCS_Send(lineNO,msgId,arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;

		log.Info()<<endl<<"UC02 sended out ............................................................................................................................................................................................................................. "<<endl;

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



//char szTemp[20];

////1	CRANE_NO
//sprintf(szTemp, "%6.6s", cranePLCShortCmdBase.getCraneNO().c_str());

//log.Debug()<<"CRANE_NO="<<szTemp<<"\t length="<<strlen(szTemp)<<endl;

//for (int i = 0; i <strlen(szTemp) ; i ++)
//{
//	arrayMsgDataBuf.push_back(*(szTemp + i));
//}

////2 	CmdCode
//sprintf(szTemp, "%03d", cranePLCShortCmdBase.getCmdCode());

//log.Debug()<<"CmdCode="<<szTemp<<"\t length="<<strlen(szTemp)<<endl;

//for (int i = 0; i <strlen(szTemp) ; i ++)
//{
//	arrayMsgDataBuf.push_back(*(szTemp + i));
//}






