#include "MsgS1.h"



using namespace Monitor;
using namespace iPlature;



MsgS1*  MsgS1::m_pMsgS1 = NULL;



MsgS1::MsgS1() 
{
	msgId="S1";
}


MsgS1 :: ~MsgS1(void)
{
	delete m_pMsgS1;
}

MsgS1* MsgS1::getInstance(void)
{
	if (m_pMsgS1 == NULL)
	{
		m_pMsgS1 = new MsgS1;
	}
	return m_pMsgS1;
}

//2017.9.1  zhangyuhong add
//param1:data							字节流
//param2:start4BytesPos		起始转换的位置（4字节一组，从0开始编号）
//param3:countShift				需要转换的DINT型数量
ByteSeq MsgS1::HighLowByteShift(ByteSeq data, int start4BytesPos , int countShift)
{
	for (int i=start4BytesPos; i<countShift; i++)
	{
		
		ByteSeq	data1,data2;
		data1<<data[4*i+3];
		data[4*i+3]=data[4*i];
		data[4*i]=data1[0];

		data2<<data[4*i+1];
		data[4*i+1]=data[4*i+2];
		data[4*i+2]=data2[0];
	}
	return data;
}


ByteSeq MsgS1::HandleMessage(const ByteSeq& ParamBuffer, SafePLC4EAFYardBase& safePLC4EAFYard_Last)
{
	string functionName="MsgS1 :: HandleMessage()";
	ByteSeq ret;
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);

		//现在只转一次，电文所有字段均为DIN
		ByteSeq dataAfterShift = HighLowByteShift(ParamBuffer, 0, 25);

		//zhangyuhong add
		//正式测试时，需要放开！！！！   自己测试时需要屏蔽
		//读取高低字节转换后的字节流
		sd.readFrom(dataAfterShift);


		//自己测试时，需要放开！！！！  正式测试时需要屏蔽
		//读取原始字节流
		//sd.readFrom(ParamBuffer);

		log.Debug()<<"...........................................log of samrt data.............................................................................."<<endl;

		//0	MSGID
		log.Debug()<<"\t\t MSGID="<<sd["MSGID"].toInt()<<endl;//电文号肯定是乱码，不用关心

		//1	G1
		log.Debug()<<"\t\t S1="<<sd["E1"].toInt()<<endl;

		//2	G2
		log.Debug()<<"\t\t S2="<<sd["E2"].toInt()<<endl;

		//3	G3
		log.Debug()<<"\t\t S3="<<sd["E3"].toInt()<<endl;

		//4	G4
		log.Debug()<<"\t\t S4="<<sd["E4"].toInt()<<endl;

		//5	G1
		log.Debug()<<"\t\t S5="<<sd["E5"].toInt()<<endl;

		//6	G1
		log.Debug()<<"\t\t S6="<<sd["E6"].toInt()<<endl;

		//7	G1
		log.Debug()<<"\t\t S7="<<sd["E7"].toInt()<<endl;

		//8	G1
		log.Debug()<<"\t\t S8="<<sd["E8"].toInt()<<endl;

		//9	G1
		log.Debug()<<"\t\t S9="<<sd["E9"].toInt()<<endl;

		//10	G1
		log.Debug()<<"\t\t S10="<<sd["E10"].toInt()<<endl;

		//11	G1
		log.Debug()<<"\t\t S11="<<sd["F1"].toInt()<<endl;

		//12	G1
		log.Debug()<<"\t\t S12="<<sd["F2"].toInt()<<endl;

		//13	G1
		log.Debug()<<"\t\t S13="<<sd["F3"].toInt()<<endl;

		//14	G1
		log.Debug()<<"\t\t S141="<<sd["F4"].toInt()<<endl;

		//15	G1
		log.Debug()<<"\t\t S142="<<sd["F5"].toInt()<<endl;

		//16	G1
		log.Debug()<<"\t\t S15="<<sd["F6"].toInt()<<endl;

		//17	G1
		log.Debug()<<"\t\t S16="<<sd["F7"].toInt()<<endl;

		//18	G1
		log.Debug()<<"\t\t S17="<<sd["F8"].toInt()<<endl;

		//19	G1
		log.Debug()<<"\t\t S18="<<sd["F9"].toInt()<<endl;

		//20	G1
		log.Debug()<<"\t\t S19="<<sd["F10"].toInt()<<endl;

		//21	G1
		log.Debug()<<"\t\t S20="<<sd["F11"].toInt()<<endl;

		//22	G1
		log.Debug()<<"\t\t S21="<<sd["F12"].toInt()<<endl;

		//23	G1
		log.Debug()<<"\t\t S22="<<sd["F13"].toInt()<<endl;

		//24	G1
		log.Debug()<<"\t\t S23="<<sd["F14"].toInt()<<endl;


		log.Debug()<<"....................................now begin to treat the message..................................................."<<endl;

		//安全PLC状态信息的基本类
		SafePLC4EAFYardBase safePLC4EAFYard_Current;
		//1
		safePLC4EAFYard_Current.setE1Status(sd["E1"].toString());
		//2
		safePLC4EAFYard_Current.setE2Status(sd["E2"].toString());
		//3
		safePLC4EAFYard_Current.setE3Status(sd["E3"].toString());
		//4
		safePLC4EAFYard_Current.setE4Status(sd["E4"].toString());
		//5
		safePLC4EAFYard_Current.setE5Status(sd["E5"].toString());
		//6
		safePLC4EAFYard_Current.setE6Status(sd["E6"].toString());
		//7
		safePLC4EAFYard_Current.setE7Status(sd["E7"].toString());
		//8
		safePLC4EAFYard_Current.setE8Status(sd["E8"].toString());
		//9
		safePLC4EAFYard_Current.setE9Status(sd["E9"].toString());
		//10
		safePLC4EAFYard_Current.setE10Status(sd["E10"].toString());
		//11
		safePLC4EAFYard_Current.setF1Status(sd["F1"].toString());
		//12
		safePLC4EAFYard_Current.setF2Status(sd["F2"].toString());
		//13
		safePLC4EAFYard_Current.setF3Status(sd["F3"].toString());
		//14
		safePLC4EAFYard_Current.setF4Status(sd["F4"].toString());
		//15
		safePLC4EAFYard_Current.setF5Status(sd["F5"].toString());
		//16
		safePLC4EAFYard_Current.setF6Status(sd["F6"].toString());
		//17
		safePLC4EAFYard_Current.setF7Status(sd["F7"].toString());
		//18
		safePLC4EAFYard_Current.setF8Status(sd["F8"].toString());
		//19
		safePLC4EAFYard_Current.setF9Status(sd["F9"].toString());
		//20
		safePLC4EAFYard_Current.setF10Status(sd["F10"].toString());
		//21
		safePLC4EAFYard_Current.setF11Status(sd["F11"].toString());
		//22
		safePLC4EAFYard_Current.setF12Status(sd["F12"].toString());
		//23
		safePLC4EAFYard_Current.setF13Status(sd["F13"].toString());
		//24
		safePLC4EAFYard_Current.setF14Status(sd["F14"].toString());

		log.Info()<<"..............safePLC4EAFYard_Current  set OK ! "<<endl;

		log.Debug()<<" 准备将安全PLC 信号点写入UACS   tag系统................................................"<<endl;
		safePLC4EAFYard_Current.wirteValues2TagSystem();

		UpdSafePLC4EAFYard(safePLC4EAFYard_Last, safePLC4EAFYard_Current);

		safePLC4EAFYard_Last = safePLC4EAFYard_Current;

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


void MsgS1:: UpdSafePLC4EAFYard(SafePLC4EAFYardBase safePLC4EAFYard_Last, SafePLC4EAFYardBase safePLC4EAFYard_Current)
{
	string functionName="MsgS1 :: UpdSafePLC4EAFYard()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		UpdSafeValue("E1", safePLC4EAFYard_Last.getE1Status(), safePLC4EAFYard_Current.getE1Status());
		UpdSafeValue("E2", safePLC4EAFYard_Last.getE2Status(), safePLC4EAFYard_Current.getE2Status());
		UpdSafeValue("E3", safePLC4EAFYard_Last.getE3Status(), safePLC4EAFYard_Current.getE3Status());
		UpdSafeValue("E4", safePLC4EAFYard_Last.getE4Status(), safePLC4EAFYard_Current.getE4Status());
		UpdSafeValue("E5", safePLC4EAFYard_Last.getE5Status(), safePLC4EAFYard_Current.getE5Status());
		UpdSafeValue("E6", safePLC4EAFYard_Last.getE6Status(), safePLC4EAFYard_Current.getE6Status());
		UpdSafeValue("E7", safePLC4EAFYard_Last.getE7Status(), safePLC4EAFYard_Current.getE7Status());
		UpdSafeValue("E8", safePLC4EAFYard_Last.getE8Status(), safePLC4EAFYard_Current.getE8Status());
		UpdSafeValue("E9", safePLC4EAFYard_Last.getE9Status(), safePLC4EAFYard_Current.getE9Status());
		UpdSafeValue("E10", safePLC4EAFYard_Last.getE10Status(), safePLC4EAFYard_Current.getE10Status());

		UpdSafeValue("F1", safePLC4EAFYard_Last.getF1Status(), safePLC4EAFYard_Current.getF1Status());
		UpdSafeValue("F2", safePLC4EAFYard_Last.getF2Status(), safePLC4EAFYard_Current.getF2Status());
		UpdSafeValue("F3", safePLC4EAFYard_Last.getF3Status(), safePLC4EAFYard_Current.getF3Status());
		UpdSafeValue("F4", safePLC4EAFYard_Last.getF4Status(), safePLC4EAFYard_Current.getF4Status());
		UpdSafeValue("F5", safePLC4EAFYard_Last.getF5Status(), safePLC4EAFYard_Current.getF5Status());
		UpdSafeValue("F6", safePLC4EAFYard_Last.getF6Status(), safePLC4EAFYard_Current.getF6Status());
		UpdSafeValue("F7", safePLC4EAFYard_Last.getF7Status(), safePLC4EAFYard_Current.getF7Status());
		UpdSafeValue("F8", safePLC4EAFYard_Last.getF8Status(), safePLC4EAFYard_Current.getF8Status());
		UpdSafeValue("F9", safePLC4EAFYard_Last.getF9Status(), safePLC4EAFYard_Current.getF9Status());
		UpdSafeValue("F10", safePLC4EAFYard_Last.getF10Status(), safePLC4EAFYard_Current.getF10Status());
		UpdSafeValue("F11", safePLC4EAFYard_Last.getF11Status(), safePLC4EAFYard_Current.getF11Status());
		UpdSafeValue("F12", safePLC4EAFYard_Last.getF12Status(), safePLC4EAFYard_Current.getF12Status());
		UpdSafeValue("F13", safePLC4EAFYard_Last.getF13Status(), safePLC4EAFYard_Current.getF13Status());
		UpdSafeValue("F14", safePLC4EAFYard_Last.getF14Status(), safePLC4EAFYard_Current.getF14Status());

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
}

void MsgS1:: UpdSafeValue(string safeID, string lastValue, string currentValue)
{
	string functionName="MsgS1 :: UpdSafeValue()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		if (lastValue == currentValue)
		{
			//no need to update
			return;
		}

		string strSql="";
		strSql = "UPDATE  UACS_SAFE_PLC_STATUS  SET ";
		strSql += " SAFE_VALUE = :p_SAFE_VALUE,  ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE SAFE_ID = :p_SAFE_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_SAFE_VALUE") = currentValue;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();
		cmd.Param("p_SAFE_ID") = safeID;

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();

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
}






