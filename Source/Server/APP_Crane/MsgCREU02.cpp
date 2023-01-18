#include "MsgCREU02.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;



MsgCREU02*  MsgCREU02::m_pMsgCREU02 = NULL;



MsgCREU02::MsgCREU02() 
{
	msgId="CU02";
	readSmartDataSuccessed=false;
}


MsgCREU02 :: ~MsgCREU02(void)
{
	
	delete m_pMsgCREU02;


}

 MsgCREU02* MsgCREU02::getInstance(void)
{
	if (m_pMsgCREU02 == NULL)
	{
		m_pMsgCREU02 = new MsgCREU02;
	}
	return m_pMsgCREU02;
}

 //2017.9.1  zhangyuhong add
 //param1:data							字节流
 //param2:start4BytesPos		起始转换的位置（4字节一组，从0开始编号）
 //param3:countShift				需要转换的DINT型数量
 ByteSeq MsgCREU02::HighLowByteShift(ByteSeq data, int start4BytesPos , int countShift)
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


ByteSeq MsgCREU02::HandleMessage(string myCraneNO,const ByteSeq& ParamBuffer)
{
	string functionName="MsgCREU02 :: HandleMessage()";

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

		//现在只转一次，电文所有字段均为DIN
		ByteSeq dataAfterShift = HighLowByteShift(ParamBuffer, 0, 30);

		//zhangyuhong add
		//正式测试时，需要放开！！！！   自己测试时需要屏蔽
		//读取高低字节转换后的字节流
		sd.readFrom(dataAfterShift);


		//自己测试时，需要放开！！！！  正式测试时需要屏蔽
		//读取原始字节流
		//sd.readFrom(ParamBuffer);
	

		log.Debug()<<"......"<<endl;
		log.Debug()<<"........................................................................................log of samrt data..................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;

		//1		CRANE_NO
		log.Debug()<<"\t\t CRANE_NO="<<sd["CRANE_NO"].toInt();

		//2		EncoderVal
		//log.Debug()<<"\t\t EncoderVal="<<sd["EncoderVal"].toString();


		//3		ErrorNum
		log.Debug()<<"\t\t ErrorNum="<<sd["ERROR_NUM"].toInt();
		int ErrorNum=sd["ERROR_NUM"].toInt();

		//创建循环体   车皮
		SmartData sdCarriges =sd["CRANE_ALARM_LIST"];


		string strErrorList="";
		for(int index = 0; index < ErrorNum; index++)
		{
			//单节车皮的smartData
			SmartData sdCarrige = sdCarriges[index];

			log.Debug()<<"..........................................................................................................................................................................................................."<<endl;


			//ALARM_CODE
			log.Debug()<<"ALARM_CODE="<<sdCarrige["ALARM_CODE"].toInt()<<endl;

			string strAlarmCode = StringHelper::ToString(sdCarrige["ALARM_CODE"].toInt());
			//strErrorList=strErrorList+sdCarrige["ALARM_CODE"].toString()+",";
			strErrorList=strErrorList+strAlarmCode+",";

		}
		strErrorList=strErrorList.substr(0,strErrorList.length()-1);
		log.Debug()<<"strErrorList"<<strErrorList<<endl;

		log.Debug()<<"......"<<endl;
		log.Debug()<<"........................................................................................now begin to treat the message..................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;



		//行车PLC报警信息的基本类
		CranePLCAlarmBase cranePLCAlarmBase;

		//1		CRANE_NO
		string craneNO=sd["CRANE_NO"].toString();
		StringHelper::Trim(craneNO);

		if(craneNO!=myCraneNO)
		{
			log.Debug()<<"received message from other crane this message will not be treated....";
			return ret;
		}

		cranePLCAlarmBase.setCraneNO(craneNO);
		log.Debug()<<"1...setCraneNO...";

		//2		EncoderVal
		//cranePLCAlarmBase.setEncodeVal(sd["EncoderVal"].toString() );
		log.Debug()<<"2...setEncodeVal...目前电文中无此项......";

		//3		ErrorNum
		cranePLCAlarmBase.setErrorNum( sd["ErrorNum"].toInt() );
		log.Debug()<<"3....setErrorNum...";
		
		//4		strErrorList
		cranePLCAlarmBase.setErrorList(strErrorList );
		log.Debug()<<"4...setErrorList...";


		//5 timeReceive
		cranePLCAlarmBase.setTimeReceive( iDA::DateTime::Now().ToShortTimeString() );

		cranePLCAlarmBase.logOutValues();

		log.Debug()<<" 准备把 PLC Alarm  放入 Crane Monitor  CranePLCAlarmBase Class................................................"<<endl;
		
		CraneMonitor::getInstance()->inputPLCAlamrs( cranePLCAlarmBase );

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

