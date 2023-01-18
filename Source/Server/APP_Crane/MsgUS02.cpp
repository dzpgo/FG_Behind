#include "MsgUS02.h"
#include "Adapter_UACS_CRANE_SAFE_PLC_MSG.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;


MsgUS02*  MsgUS02::m_pMsgUS02 = NULL;


MsgUS02::MsgUS02() 
{
	msgId="US02";
}


MsgUS02 :: ~MsgUS02(void)
{

	delete m_pMsgUS02;


}

MsgUS02* MsgUS02::getInstance(void)
{
	if (m_pMsgUS02 == NULL)
	{
		m_pMsgUS02 = new MsgUS02;
	}
	return m_pMsgUS02;
}




bool MsgUS02::SendOutMessage(vector <string> vecLineName, string craneNO, string itemValue)
{
	bool ret=false;
	string functionName="MsgUS02 :: SendOutMessage()";

	LOG log(functionName, AUTO_CATCH_PID);

	AlarmWrapper _p("");

	try
	{

		log.Debug()<<"......"<<endl;
		log.Debug()<<"........................................................................................now begin to treat the message MsgUS02.................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;

		ArrayMsg arrayMsgDataBuf;



		//2017.9.25  zhangyuhong add
		//1：请求锁定
		//0：不请求锁定
		struct msgStruct4US02
		{
			char C612_AREA_UNLOCK_1[1];									//C612入口步进梁解锁1
			char C612_AREA_UNLOCK_2[1];									//C612入口步进梁解锁2
			char C175MC_AREA_UNLOCK[1];							//C175入口区域解锁
			char C175MR_AREA_UNLOCK[1];							//C175出口区域解锁
			char C176MC_AREA_UNLOCK[1];							//C176入口区域解锁
			char C176MR_AREA_UNLOCK[1];							//C176出口区域解锁
			char C612_EXIT_AREA_UNLOCK[1];							//PA1入口区域解锁  ->  改成C612出口解锁请求
			char PA1MR_AREA_UNLOCK[1];							//PA1出口区域解锁
			char PA2MC_AREA_UNLOCK[1];								//PA2入口区域解锁
			char PA2MR_AREA_UNLOCK[1];								//PA2出口区域解锁
			char END_AREA_UNLOCK[1];											//尾料区域解锁
			char TURN_CAR_INIT_SET_NUM[1];							//倾翻小车初始设定翻斗次数
			char TURN_CAR_INIT_SET_POS[1];							//倾翻小车初始设定移动位置
			
		}stuMsgData;

		arrayMsgDataBuf.resize(sizeof(stuMsgData));

		//初始化
		memcpy(&stuMsgData.C612_AREA_UNLOCK_1,"0",1);
		memcpy(&stuMsgData.C612_AREA_UNLOCK_2,"0",1);
		memcpy(&stuMsgData.C175MC_AREA_UNLOCK,"0",1);		
		memcpy(&stuMsgData.C175MR_AREA_UNLOCK,"0",1);
		memcpy(&stuMsgData.C176MC_AREA_UNLOCK,"0",1);
		memcpy(&stuMsgData.C176MR_AREA_UNLOCK,"0",1);
		memcpy(&stuMsgData.C612_EXIT_AREA_UNLOCK,"0",1);
		memcpy(&stuMsgData.PA1MR_AREA_UNLOCK,"0",1);
		memcpy(&stuMsgData.PA2MC_AREA_UNLOCK,"0",1);
		memcpy(&stuMsgData.PA2MR_AREA_UNLOCK,"0",1);
		memcpy(&stuMsgData.END_AREA_UNLOCK,"0",1);
		memcpy(&stuMsgData.TURN_CAR_INIT_SET_NUM,"0",1);
		memcpy(&stuMsgData.TURN_CAR_INIT_SET_POS,"0",1);
		

		for (size_t i=0; i<vecLineName.size();i++)
		{
			//1
			if (vecLineName[i] == "C612_AREA_UNLOCK_1")
			{
				memcpy(&stuMsgData.C612_AREA_UNLOCK_1,"1",1);
			}
			//2
			else if (vecLineName[i] == "C612_AREA_UNLOCK_2")
			{
				memcpy(&stuMsgData.C612_AREA_UNLOCK_2,"1",1);
			}
			//3
			else if (vecLineName[i] == "C175MC_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.C175MC_AREA_UNLOCK,"1",1);
			}
			//4
			else if (vecLineName[i] == "C175MR_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.C175MR_AREA_UNLOCK,"1",1);
			}
			//5
			else if (vecLineName[i] == "C176MC_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.C176MC_AREA_UNLOCK,"1",1);
			}
			//6
			else if (vecLineName[i] == "C176MR_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.C176MR_AREA_UNLOCK,"1",1);
			}
			//7
			else if (vecLineName[i] == "C612_EXIT_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.C612_EXIT_AREA_UNLOCK,"1",1);
			}
			//8
			else if (vecLineName[i] == "PA1MR_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.PA1MR_AREA_UNLOCK,"1",1);
			}
			//9
			else if (vecLineName[i] == "PA2MC_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.PA2MC_AREA_UNLOCK,"1",1);
			}
			//10
			else if (vecLineName[i] == "PA2MR_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.PA2MR_AREA_UNLOCK,"1",1);
			}
			//11
			else if (vecLineName[i] == "END_AREA_UNLOCK")
			{
				memcpy(&stuMsgData.END_AREA_UNLOCK,"1",1);
			}
			//12
			else if (vecLineName[i] == "TURN_CAR_INIT_SET_NUM")
			{
				memcpy(&stuMsgData.TURN_CAR_INIT_SET_NUM, itemValue.c_str(),1);
			}
			//13
			else if (vecLineName[i] == "TURN_CAR_INIT_SET_POS")
			{
				memcpy(&stuMsgData.TURN_CAR_INIT_SET_POS, itemValue.c_str(),1);
			}
			
		}

		memcpy((void*)&arrayMsgDataBuf.front(),(char*)&stuMsgData,sizeof(stuMsgData));

		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//打印发送电文内容日志
		log.Debug()<<"\t\t C612_AREA_UNLOCK_1="<<stuMsgData.C612_AREA_UNLOCK_1[0]<<endl;
		log.Debug()<<"\t\t C612_AREA_UNLOCK_2="<<stuMsgData.C612_AREA_UNLOCK_2[0]<<endl;
		log.Debug()<<"\t\t C175MC_AREA_UNLOCK="<<stuMsgData.C175MC_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t C175MR_AREA_UNLOCK="<<stuMsgData.C175MR_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t C176MC_AREA_UNLOCK="<<stuMsgData.C176MC_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t C176MR_AREA_UNLOCK="<<stuMsgData.C176MR_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t C612_EXIT_AREA_UNLOCK="<<stuMsgData.C612_EXIT_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t PA1MR_AREA_UNLOCK="<<stuMsgData.PA1MR_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t PA2MC_UNLOCK="<<stuMsgData.PA2MC_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t PA2MR_UNLOCK="<<stuMsgData.PA2MR_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t END_AREA_UNLOCK="<<stuMsgData.END_AREA_UNLOCK[0]<<endl;
		log.Debug()<<"\t\t TURN_CAR_INIT_SET_NUM="<<stuMsgData.TURN_CAR_INIT_SET_NUM[0]<<endl;
		log.Debug()<<"\t\t TURN_CAR_INIT_SET_POS="<<stuMsgData.TURN_CAR_INIT_SET_POS[0]<<endl;
		

		//int lineNO=RelationCrane2TCPLinePLC::getLineNO( cranePLCOrderBase.getCraneNO() );
		int lineNO = 27;

		log.Debug()<<"lineNO="<<lineNO<<endl;

		int nRet=PCS_Send(lineNO,msgId,arrayMsgDataBuf);
		log.Debug()<<"nRet="<<nRet<<endl;

		if (nRet != 0)
		{
			ret = false;
		}
		else
		{
			ret = true;
			log.Info()<<endl<<"US02 sended out ............................................................................................................................................................................................................................. "<<endl;
			//2018.1.9 zhangyuhong add
			//组织安全PLC发送电文内容，存入数据库做记录备查
			string msgText1 = stuMsgData.C612_AREA_UNLOCK_1;
			msgText1 = msgText1.at(0);

			string msgText2 = stuMsgData.C612_AREA_UNLOCK_2;
			msgText2 = msgText2.at(0);

			string msgText3 = stuMsgData.C175MC_AREA_UNLOCK;
			msgText3 = msgText3.at(0);

			string msgText4 = stuMsgData.C175MR_AREA_UNLOCK;
			msgText4 = msgText4.at(0);

			string msgText5 = stuMsgData.C176MC_AREA_UNLOCK;
			msgText5 = msgText5.at(0);

			string msgText6 = stuMsgData.C176MR_AREA_UNLOCK;
			msgText6 = msgText6.at(0);

			string msgText7 = stuMsgData.C612_EXIT_AREA_UNLOCK;
			msgText7 = msgText7.at(0);

			string msgText8 = stuMsgData.PA1MR_AREA_UNLOCK;
			msgText8 = msgText8.at(0);

			string msgText9 = stuMsgData.PA2MC_AREA_UNLOCK;
			msgText9 = msgText9.at(0);

			string msgText10 = stuMsgData.PA2MR_AREA_UNLOCK;
			msgText10 = msgText10.at(0);

			string msgText11 = stuMsgData.END_AREA_UNLOCK;
			msgText11 = msgText11.at(0);

			string msgText12 = stuMsgData.TURN_CAR_INIT_SET_NUM;
			msgText12 = msgText12.at(0);

			string msgText13 = stuMsgData.TURN_CAR_INIT_SET_POS;
			msgText13 = msgText13.at(0);

			string msgText = "1:" + msgText1 + "  2:" + msgText2 + "  3:" + msgText3 + "  4:" + msgText4 + "  5:" + msgText5 + "  6:" + msgText6;
			msgText += "  7:" + msgText7 + "  8:" + msgText8 + "  9:" + msgText9 + "  10:" +msgText10 + "  11:" +msgText11 + "  12:" +msgText12 + "  13:" +msgText13;

			if(true == Adapter_UACS_CRANE_SAFE_PLC_MSG::insertSAFEPLCMsg(craneNO, "US02", msgText))
				log.Debug()<<"下发的行车指令写入数据表UACS_CRANE_SAFEPLC_MSG成功！"<<endl;
		}		
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
