#include "MsgU1.h"

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;


MsgU1*  MsgU1::m_pMsgU1 = NULL;


MsgU1::MsgU1() 
{
	msgId="U1";
}


MsgU1 :: ~MsgU1(void)
{
	
	delete m_pMsgU1;


}

 MsgU1* MsgU1::getInstance(void)
{
	if (m_pMsgU1 == NULL)
	{
		m_pMsgU1 = new MsgU1;
	}
	return m_pMsgU1;
}




bool MsgU1::SendOutMessage(vector<long>  vecSafePLC4EAFYard)
{
	bool ret=true;
	string functionName="MsgU1 :: SendOutMessage()";

	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<".....................................................now begin to treat the message U1.........................................................."<<endl;

		ArrayMsg arrayMsgDataBuf;

		struct msgStruct4U1
		{
			int e1;	
			int e2;	
			int e3;	
			int e4;	
			int e5;
			int e6;	
			int e7;	
			int e8;
			int e9;	
			int e10;
			int f1;
			int f2;
			int f3;
			int f4;
			int f5;
			int f6;
			int f7;
			int f8;
			int f9;
			int f10;
			int f11;
			int f12;
			int f13;
			int f14;
		}stuMsgData;

		//组织发送电文数据
		stuMsgData.e1 = vecSafePLC4EAFYard[0];  //1-作业开始   0-作业结束
		stuMsgData.e2 = vecSafePLC4EAFYard[1];
		stuMsgData.e3 = vecSafePLC4EAFYard[2];
		stuMsgData.e4 = vecSafePLC4EAFYard[3];
		stuMsgData.e5 = vecSafePLC4EAFYard[4];
		stuMsgData.e6 = vecSafePLC4EAFYard[5];
		stuMsgData.e7 = vecSafePLC4EAFYard[6];
		stuMsgData.e8 = vecSafePLC4EAFYard[7];
		stuMsgData.e9 = vecSafePLC4EAFYard[8];
		stuMsgData.e10 = vecSafePLC4EAFYard[9];
		stuMsgData.f1 = vecSafePLC4EAFYard[10];
		stuMsgData.f2 = vecSafePLC4EAFYard[11];
		stuMsgData.f3 = vecSafePLC4EAFYard[12];
		stuMsgData.f4 = vecSafePLC4EAFYard[13];
		stuMsgData.f5 = vecSafePLC4EAFYard[14];
		stuMsgData.f6 = vecSafePLC4EAFYard[15];
		stuMsgData.f7 = vecSafePLC4EAFYard[16];
		stuMsgData.f8 = vecSafePLC4EAFYard[17];
		stuMsgData.f9 = vecSafePLC4EAFYard[18];
		stuMsgData.f10 = vecSafePLC4EAFYard[19];
		stuMsgData.f11 = vecSafePLC4EAFYard[20];
		stuMsgData.f12 = vecSafePLC4EAFYard[21];
		stuMsgData.f13 = vecSafePLC4EAFYard[22];
		stuMsgData.f14 = vecSafePLC4EAFYard[23];

		arrayMsgDataBuf.resize(sizeof(stuMsgData));
		memcpy((void*)&arrayMsgDataBuf.front(),(char*)&stuMsgData,sizeof(stuMsgData));
		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//打印发送电文内容日志
		log.Debug()<<"s1="<<stuMsgData.e1<<endl;
		log.Debug()<<"s2="<<stuMsgData.e2<<endl;
		log.Debug()<<"s3="<<stuMsgData.e3<<endl;
		log.Debug()<<"s4="<<stuMsgData.e4<<endl;
		log.Debug()<<"s5="<<stuMsgData.e5<<endl;
		log.Debug()<<"s6="<<stuMsgData.e6<<endl;
		log.Debug()<<"s7="<<stuMsgData.e7<<endl;
		log.Debug()<<"s8="<<stuMsgData.e8<<endl;
		log.Debug()<<"s9="<<stuMsgData.e9<<endl;
		log.Debug()<<"s10="<<stuMsgData.e10<<endl;
		log.Debug()<<"s11="<<stuMsgData.f1<<endl;
		log.Debug()<<"s12="<<stuMsgData.f2<<endl;
		log.Debug()<<"s13="<<stuMsgData.f3<<endl;
		log.Debug()<<"s141="<<stuMsgData.f4<<endl;
		log.Debug()<<"s142="<<stuMsgData.f5<<endl;
		log.Debug()<<"s15="<<stuMsgData.f6<<endl;
		log.Debug()<<"s16="<<stuMsgData.f7<<endl;
		log.Debug()<<"s17="<<stuMsgData.f8<<endl;
		log.Debug()<<"s18="<<stuMsgData.f9<<endl;
		log.Debug()<<"s19="<<stuMsgData.f10<<endl;
		log.Debug()<<"s20="<<stuMsgData.f11<<endl;
		log.Debug()<<"s21="<<stuMsgData.f12<<endl;
		log.Debug()<<"s22="<<stuMsgData.f13<<endl;
		log.Debug()<<"s23="<<stuMsgData.f14<<endl;

		int lineNO = 10;

		log.Debug()<<"lineNO="<<lineNO<<endl;
		
		int ret=PCS_Send(lineNO,msgId,arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;

		log.Info()<<endl<<"U1 sended out ................................................................................................. "<<endl;		

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

