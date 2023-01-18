#include "MsgUS01.h"
#include "Adapter_UACS_CRANE_SAFE_PLC_MSG.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;


MsgUS01*  MsgUS01::m_pMsgUS01 = NULL;


MsgUS01::MsgUS01() 
{
	msgId="US01";
}


MsgUS01 :: ~MsgUS01(void)
{

	delete m_pMsgUS01;


}

MsgUS01* MsgUS01::getInstance(void)
{
	if (m_pMsgUS01 == NULL)
	{
		m_pMsgUS01 = new MsgUS01;
	}
	return m_pMsgUS01;
}




bool MsgUS01::SendOutMessage(vector <string> vecLineName, string craneNO)
{
	bool ret=true;
	string functionName="MsgUS01 :: SendOutMessage()";

	LOG log(functionName, AUTO_CATCH_PID);

	AlarmWrapper _p("");

	try
	{

		log.Debug()<<"......"<<endl;
		log.Debug()<<"........................................................................................now begin to treat the message MsgUS01.................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;

		ArrayMsg arrayMsgDataBuf;



		//2017.9.25  zhangyuhong add
		//1����������
		//0������������
		struct msgStruct4US01
		{
			char C612MC1_AREA_LOCK[1];							//C612�����������1
			char C612MC2_AREA_LOCK[1];							//C612�����������2
			char C175MC_AREA_LOCK[1];							//C175�����������
			char C175MR_AREA_LOCK[1];							//C175������������
			char C176MC_AREA_LOCK[1];							//C176�����������	
			char C176MR_AREA_LOCK[1];							//C176������������
			//char PA1MC_AREA_LOCK[1];								//PA1�����������
			char C612_EXIT_AREA_LOCK[1];								//612������������
			char PA1MR_AREA_LOCK[1];								//PA1������������
			char PA2MC_AREA_LOCK[1];											//PA2�����������
			char PA2MR_AREA_LOCK[1];											//PA2������������	
			char END_AREA_LOCK[1];									//β����������
		}stuMsgData;

		arrayMsgDataBuf.resize(sizeof(stuMsgData));

		//��ʼ��
		memcpy(&stuMsgData.C612MC1_AREA_LOCK,"0",1);		
		memcpy(&stuMsgData.C612MC2_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.C175MC_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.C175MR_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.C176MC_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.C176MR_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.C612_EXIT_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.PA1MR_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.PA2MC_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.PA2MR_AREA_LOCK,"0",1);
		memcpy(&stuMsgData.END_AREA_LOCK,"0",1);

		for (size_t i=0; i<vecLineName.size();i++)
		{
			//1
			if (vecLineName[i] == "C612MC1_AREA_LOCK")
			{
				memcpy(&stuMsgData.C612MC1_AREA_LOCK,"1",1);
			} 
			//2
			else if (vecLineName[i] == "C612MC2_AREA_LOCK")
			{
				memcpy(&stuMsgData.C612MC2_AREA_LOCK,"1",1);
			}
			//3
			else if (vecLineName[i] == "C175MC_AREA_LOCK")
			{
				memcpy(&stuMsgData.C175MC_AREA_LOCK,"1",1);
			}
			//4
			else if (vecLineName[i] == "C175MR_AREA_LOCK")
			{
				memcpy(&stuMsgData.C175MR_AREA_LOCK,"1",1);
			}
			//5
			else if (vecLineName[i] == "C176MC_AREA_LOCK")
			{
				memcpy(&stuMsgData.C176MC_AREA_LOCK,"1",1);
			}
			//6
			else if (vecLineName[i] == "C176MR_AREA_LOCK")
			{
				memcpy(&stuMsgData.C176MR_AREA_LOCK,"1",1);
			}
			//7
			else if (vecLineName[i] == "C612_EXIT_AREA_LOCK")
			{
				memcpy(&stuMsgData.C612_EXIT_AREA_LOCK,"1",1);
			}
			//8
			else if (vecLineName[i] == "PA1MR_AREA_LOCK")
			{
				memcpy(&stuMsgData.PA1MR_AREA_LOCK,"1",1);
			}
			//9
			else if (vecLineName[i] == "PA2MC_AREA_LOCK")
			{
				memcpy(&stuMsgData.PA2MC_AREA_LOCK,"1",1);
			}
			//10
			else if (vecLineName[i] == "PA2MR_AREA_LOCK")
			{
				memcpy(&stuMsgData.PA2MR_AREA_LOCK,"1",1);
			}
			//11
			else if (vecLineName[i] == "END_AREA_LOCK")
			{
				memcpy(&stuMsgData.END_AREA_LOCK,"1",1);
			}
		}

		memcpy((void*)&arrayMsgDataBuf.front(),(char*)&stuMsgData,sizeof(stuMsgData));

		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//��ӡ���͵���������־
		log.Debug()<<"\t\t C612MC1_AREA_LOCK="<<stuMsgData.C612MC1_AREA_LOCK[0]<<endl;
		log.Debug()<<"\t\t C612MC2_AREA_LOCK="<<stuMsgData.C612MC2_AREA_LOCK[0]<<endl;
		log.Debug()<<"\t\t C175MC_AREA_LOCK="<<stuMsgData.C175MC_AREA_LOCK[0]<<endl;
		log.Debug()<<"\t\t C175MR_AREA_LOCK="<<stuMsgData.C175MR_AREA_LOCK[0]<<endl;
		log.Debug()<<"\t\t C176MC_AREA_LOCK="<<stuMsgData.C176MC_AREA_LOCK[0]<<endl;
		log.Debug()<<"\t\t C176MR_AREA_LOCK="<<stuMsgData.C176MR_AREA_LOCK[0]<<endl;
		//log.Debug()<<"\t\t PA1MC_AREA_LOCK="<<stuMsgData.PA1MC_AREA_LOCK[0]<<endl;		//�ĳ�C612������������
		log.Debug()<<"\t\t C612_EXIT_AREA_LOCK="<<stuMsgData.C612_EXIT_AREA_LOCK[0]<<endl;		//�ĳ�C612������������
		log.Debug()<<"\t\t PA1MR_AREA_LOCK="<<stuMsgData.PA1MR_AREA_LOCK[0]<<endl;
		log.Debug()<<"\t\t PA2MC_AREA_LOCK="<<stuMsgData.PA2MC_AREA_LOCK[0]<<endl;
		log.Debug()<<"\t\t PA2MR_AREA_LOCK="<<stuMsgData.PA2MR_AREA_LOCK[0]<<endl;
		log.Debug()<<"\t\t END_AREA_LOCK="<<stuMsgData.END_AREA_LOCK[0]<<endl;

		//int lineNO=RelationCrane2TCPLinePLC::getLineNO( cranePLCOrderBase.getCraneNO() );
		int lineNO = 26;

		log.Debug()<<"lineNO="<<lineNO<<endl;

		int ret=PCS_Send(lineNO,msgId,arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;

		log.Info()<<endl<<"US01 sended out ............................................................................................................................................................................................................................. "<<endl;
		
		//2018.1.9 zhangyuhong add
		//��֯��ȫPLC���͵������ݣ��������ݿ�����¼����
		string msgText1 = stuMsgData.C612MC1_AREA_LOCK;
		msgText1 = msgText1.at(0);

		string msgText2 = stuMsgData.C612MC2_AREA_LOCK;
		msgText2 = msgText2.at(0);

		string msgText3 = stuMsgData.C175MC_AREA_LOCK;
		msgText3 = msgText3.at(0);

		string msgText4 = stuMsgData.C175MR_AREA_LOCK;
		msgText4 = msgText4.at(0);

		string msgText5 = stuMsgData.C176MC_AREA_LOCK;
		msgText5 = msgText5.at(0);

		string msgText6 = stuMsgData.C176MR_AREA_LOCK;
		msgText6 = msgText6.at(0);

		string msgText7 = stuMsgData.C612_EXIT_AREA_LOCK;
		msgText7 = msgText7.at(0);

		string msgText8 = stuMsgData.PA1MR_AREA_LOCK;
		msgText8 = msgText8.at(0);

		string msgText9 = stuMsgData.PA2MC_AREA_LOCK;
		msgText9 = msgText9.at(0);

		string msgText10 = stuMsgData.PA2MR_AREA_LOCK;
		msgText10 = msgText10.at(0);

		string msgText11 = stuMsgData.END_AREA_LOCK;
		msgText11 = msgText11.at(0);

		string msgText = "1:" + msgText1 + "  2:" + msgText2 + "  3:" + msgText3 + "  4:" + msgText4 + "  5:" + msgText5 + "  6:" + msgText6;
		msgText += "  7:" + msgText7 + "  8:" + msgText8 + "  9:" + msgText9 + "  10:" +msgText10 + "  11:" +msgText11;

		if(true == Adapter_UACS_CRANE_SAFE_PLC_MSG::insertSAFEPLCMsg(craneNO, "US01", msgText))
			log.Debug()<<"�·����г�ָ��д�����ݱ�UACS_CRANE_SAFEPLC_MSG�ɹ���"<<endl;

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
