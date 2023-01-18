#include "MsgUS04.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;


MsgUS04*  MsgUS04::m_pMsgUS04 = NULL;


MsgUS04::MsgUS04() 
{
	msgId="US04";
}


MsgUS04 :: ~MsgUS04(void)
{

	delete m_pMsgUS04;


}

MsgUS04* MsgUS04::getInstance(void)
{
	if (m_pMsgUS04 == NULL)
	{
		m_pMsgUS04 = new MsgUS04;
	}
	return m_pMsgUS04;
}




bool MsgUS04::SendOutMessage(vector <long> vecSafeDoorID)
{
	bool ret=true;
	string functionName="MsgUS04 :: SendOutMessage()";

	LOG log(functionName, AUTO_CATCH_PID);

	AlarmWrapper _p("");

	try
	{

		log.Debug()<<"......"<<endl;
		log.Debug()<<"........................................................................................now begin to treat the message MsgUS04.................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;

		ArrayMsg arrayMsgDataBuf;



		//2018.1.4  zhangyuhong add
		//1：危险
		//0：安全
		struct msgStruct4US04
		{
			//后库安全门定义
			char C2A_DO1_NOTIFY[1];							//库区C2A
			char C2A_DO2_NOTIFY[1];		
			char C2A_DO3_NOTIFY[1];		
			char C2A_DO4_NOTIFY[1];		
			char C2A_DO5_NOTIFY[1];		
			char C2A_DO6_NOTIFY[1];		
			char C2A_DO7_NOTIFY[1];		
			char C2A_DO8_NOTIFY[1];		
			char C2A_DO9_NOTIFY[1];		
			char C2A_DO10_NOTIFY[1];	

			char C2A_DO11_NOTIFY[1];							//库区C2A
			char C2A_DO12_NOTIFY[1];		
			char C2A_DO13_NOTIFY[1];		
			char C2A_DO14_NOTIFY[1];		
			char C2A_DO15_NOTIFY[1];		
			char C2A_DO16_NOTIFY[1];		
			char C2A_DO17_NOTIFY[1];		
			char C2A_DO18_NOTIFY[1];		
			char C2A_DO19_NOTIFY[1];		
			char C2A_DO20_NOTIFY[1];	

			char C2A_DO21_NOTIFY[1];							//库区C2A
			char C2A_DO22_NOTIFY[1];					
		}stuMsgData;

		arrayMsgDataBuf.resize(sizeof(stuMsgData));

		//初始化
		//612后库
		memcpy(&stuMsgData.C2A_DO1_NOTIFY,"0",1);		
		memcpy(&stuMsgData.C2A_DO2_NOTIFY,"0",1);
		memcpy(&stuMsgData.C2A_DO3_NOTIFY,"0",1);
		memcpy(&stuMsgData.C2A_DO4_NOTIFY,"0",1);
		memcpy(&stuMsgData.C2A_DO5_NOTIFY,"0",1);
		memcpy(&stuMsgData.C2A_DO6_NOTIFY,"0",1);
		memcpy(&stuMsgData.C2A_DO7_NOTIFY,"0",1);
		memcpy(&stuMsgData.C2A_DO8_NOTIFY,"0",1);
		memcpy(&stuMsgData.C2A_DO9_NOTIFY,"0",1);
		memcpy(&stuMsgData.C2A_DO10_NOTIFY,"0",1);	

		memcpy(&stuMsgData.C2A_DO11_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO12_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO13_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO14_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO15_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO16_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO17_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO18_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO19_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO20_NOTIFY,"0",1);	

		memcpy(&stuMsgData.C2A_DO21_NOTIFY,"0",1);	
		memcpy(&stuMsgData.C2A_DO22_NOTIFY,"0",1);	

		for (size_t i=0; i<vecSafeDoorID.size();i++)
		{
			//1
			if (vecSafeDoorID[i] == 1)
			{
				memcpy(&stuMsgData.C2A_DO1_NOTIFY,"1",1);
			} 
			//2
			else if (vecSafeDoorID[i] == 2)
			{
				memcpy(&stuMsgData.C2A_DO2_NOTIFY,"1",1);
			}
			//3
			else if (vecSafeDoorID[i] == 3)
			{
				memcpy(&stuMsgData.C2A_DO3_NOTIFY,"1",1);
			}
			//4
			else if (vecSafeDoorID[i] == 4)
			{
				memcpy(&stuMsgData.C2A_DO4_NOTIFY,"1",1);
			}
			//5
			else if (vecSafeDoorID[i] == 5)
			{
				memcpy(&stuMsgData.C2A_DO5_NOTIFY,"1",1);
			}
			//6
			else if (vecSafeDoorID[i] == 6)
			{
				memcpy(&stuMsgData.C2A_DO6_NOTIFY,"1",1);
			}
			//7
			else if (vecSafeDoorID[i] == 7)
			{
				memcpy(&stuMsgData.C2A_DO7_NOTIFY,"1",1);
			}
			//8
			else if (vecSafeDoorID[i] == 8)
			{
				memcpy(&stuMsgData.C2A_DO8_NOTIFY,"1",1);
			}
			//9
			else if (vecSafeDoorID[i] == 9)
			{
				memcpy(&stuMsgData.C2A_DO9_NOTIFY,"1",1);
			}
			//10
			else if (vecSafeDoorID[i] == 10)
			{
				memcpy(&stuMsgData.C2A_DO10_NOTIFY,"1",1);
			}
			//11
			else if (vecSafeDoorID[i] == 11)
			{
				memcpy(&stuMsgData.C2A_DO11_NOTIFY,"1",1);
			}
			//12
			else if (vecSafeDoorID[i] == 12)
			{
				memcpy(&stuMsgData.C2A_DO12_NOTIFY,"1",1);
			}
			//13
			else if (vecSafeDoorID[i] == 13)
			{
				memcpy(&stuMsgData.C2A_DO13_NOTIFY,"1",1);
			}
			//14
			else if (vecSafeDoorID[i] == 14)
			{
				memcpy(&stuMsgData.C2A_DO14_NOTIFY,"1",1);
			}
			//15
			else if (vecSafeDoorID[i] == 15)
			{
				memcpy(&stuMsgData.C2A_DO15_NOTIFY,"1",1);
			}
			//16
			else if (vecSafeDoorID[i] == 16)
			{
				memcpy(&stuMsgData.C2A_DO16_NOTIFY,"1",1);
			}
			//17
			else if (vecSafeDoorID[i] == 17)
			{
				memcpy(&stuMsgData.C2A_DO17_NOTIFY,"1",1);
			}
			//18
			else if (vecSafeDoorID[i] == 18)
			{
				memcpy(&stuMsgData.C2A_DO18_NOTIFY,"1",1);
			}
			//19
			else if (vecSafeDoorID[i] == 19)
			{
				memcpy(&stuMsgData.C2A_DO19_NOTIFY,"1",1);
			}
			//20
			else if (vecSafeDoorID[i] == 20)
			{
				memcpy(&stuMsgData.C2A_DO20_NOTIFY,"1",1);
			}
			//21
			else if (vecSafeDoorID[i] == 21)
			{
				memcpy(&stuMsgData.C2A_DO21_NOTIFY,"1",1);
			}
			//22
			else if (vecSafeDoorID[i] == 22)
			{
				memcpy(&stuMsgData.C2A_DO22_NOTIFY,"1",1);
			}

		}

		memcpy((void*)&arrayMsgDataBuf.front(),(char*)&stuMsgData,sizeof(stuMsgData));

		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );


		//打印发送电文内容日志

		//后库
		log.Debug()<<"\t\t C2A_DO1_NOTIFY="<<stuMsgData.C2A_DO1_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO2_NOTIFY="<<stuMsgData.C2A_DO2_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO3_NOTIFY="<<stuMsgData.C2A_DO3_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO4_NOTIFY="<<stuMsgData.C2A_DO4_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO5_NOTIFY="<<stuMsgData.C2A_DO5_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO6_NOTIFY="<<stuMsgData.C2A_DO6_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO7_NOTIFY="<<stuMsgData.C2A_DO7_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO8_NOTIFY="<<stuMsgData.C2A_DO8_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO9_NOTIFY="<<stuMsgData.C2A_DO9_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO10_NOTIFY="<<stuMsgData.C2A_DO10_NOTIFY[0]<<endl;

		log.Debug()<<"\t\t C2A_DO11_NOTIFY="<<stuMsgData.C2A_DO11_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO12_NOTIFY="<<stuMsgData.C2A_DO12_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO13_NOTIFY="<<stuMsgData.C2A_DO13_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO14_NOTIFY="<<stuMsgData.C2A_DO14_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO15_NOTIFY="<<stuMsgData.C2A_DO15_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO16_NOTIFY="<<stuMsgData.C2A_DO16_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO17_NOTIFY="<<stuMsgData.C2A_DO17_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO18_NOTIFY="<<stuMsgData.C2A_DO18_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO19_NOTIFY="<<stuMsgData.C2A_DO19_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO20_NOTIFY="<<stuMsgData.C2A_DO20_NOTIFY[0]<<endl;

		log.Debug()<<"\t\t C2A_DO21_NOTIFY="<<stuMsgData.C2A_DO21_NOTIFY[0]<<endl;
		log.Debug()<<"\t\t C2A_DO22_NOTIFY="<<stuMsgData.C2A_DO22_NOTIFY[0]<<endl;

		//int lineNO=RelationCrane2TCPLinePLC::getLineNO( cranePLCOrderBase.getCraneNO() );
		//向安全plc发送后库安全门电文的  回线号=29
		int lineNO = 29;

		log.Debug()<<"lineNO="<<lineNO<<endl;

		int ret=PCS_Send(lineNO,msgId,arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;

		log.Info()<<endl<<"US04 发送完成 ............................................................................................................................................................................................................................. "<<endl;


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
