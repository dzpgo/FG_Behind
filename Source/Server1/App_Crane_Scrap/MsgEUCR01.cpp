#include "MsgEUCR01.h"
//#include <Util.h>

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;


MsgEUCR01*  MsgEUCR01::m_pMsgEUCR01 = NULL;


MsgEUCR01::MsgEUCR01() 
{
	msgId="UC01";
}


MsgEUCR01 :: ~MsgEUCR01(void)
{
	
	delete m_pMsgEUCR01;


}

 MsgEUCR01* MsgEUCR01::getInstance(void)
{
	if (m_pMsgEUCR01 == NULL)
	{
		m_pMsgEUCR01 = new MsgEUCR01;
	}
	return m_pMsgEUCR01;
}




//bool MsgEUCR01::SendOutMessage(CranePLCOrderBase cranePLCOrderBase)
//{
//	bool ret=true;
//	string functionName="MsgEUCR01 :: SendOutMessage()";
//
//
//	LOG log(functionName, AUTO_CATCH_PID);
//
//
//	AlarmWrapper _p("");
//
//	try
//	{
//		log.Debug()<<"........................................................................................now begin to treat the message UC01.................................................................................................................."<<endl;
//
//		ArrayMsg arrayMsgDataBuf;
//
//		//2017.9.25  zhangyuhong add
//		struct msgStruct4EUCR01
//		{
//			int craneNo;							//行车号
//			int orderID;							//当前指令号
//			int matWeight;						//取料重量
//			int matType;							//取料类型
//			int planUpX;							//计划起卷X
//			int planUpY;							//计划落卷Y
//			int planUpZ;							//计划落卷Z	
//			int upRotateAngle;				//起吊夹钳旋转角度
//			int planDownX;						//计划落卷X
//			int planDownY;						//计划落卷Y
//			int planDownZ;						//计划落卷Z	
//			int downRotateAngle;		//落关夹钳旋转角度
//			int shortCmd;						//短指令  0=不执行命令   1=执行命令    100=要求停车   200=要求紧急停车  300=要求故障复位   400=要求计算机自动  500=取消计算机自动
//			int midPoint1X;					//1X
//			int midPoint1Y;						//1Y
//			int midPoint2X;					//2X
//			int midPoint2Y;						//2Y
//			int midPoint3X;					//3X
//			int midPoint3Y;						//3Y
//			int midPoint4X;					//4X
//			int midPoint4Y;						//4Y
//			int midPoint5X;					//5X
//			int midPoint5Y;						//5Y
//			int midPoint6X;					//6X
//			int midPoint6Y;						//6Y
//			int midPoint7X;					//7X
//			int midPoint7Y;						//7Y
//			int midPoint8X;					//8X
//			int midPoint8Y;						//8Y
//			int midPoint9X;					//9X
//			int midPoint9Y;						//9Y
//			int midPoint10X;					//10X
//			int midPoint10Y;					//10Y
//			int midPoint11X;					//11X
//			int midPoint11Y;					//11Y
//			int midPoint12X;					//12X
//			int midPoint12Y;					//12Y
//			int midPoint13X;					//13X
//			int midPoint13Y;					//13Y
//			int midPoint14X;					//14X
//			int midPoint14Y;					//14Y
//			int midPoint15X;					//15X
//			int midPoint15Y;					//15Y
//			int midPoint16X;					//16X
//			int midPoint16Y;					//16Y
//			int midPoint17X;					//17X
//			int midPoint17Y;					//17Y
//			int midPoint18X;					//18X
//			int midPoint18Y;					//18Y
//			int midPoint19X;					//19X
//			int midPoint19Y;					//19Y
//			int midPoint20X;					//20X
//			int midPoint20Y;					//20Y
//		}stuMsgData;
//
//		//cranePLCOrderBase类里面的craneNO是string型，需要转换成int型，以供电文用（电文里是int型）
//		/*vector<string> vec1 = StringHelper::Split(cranePLCOrderBase.getCraneNO(),'_');
//		int craneNO1st = StringHelper::ToNumber<int>(vec1[0]);
//		int craneNOlast = StringHelper::ToNumber<int>(vec1[1]);
//		int trueCraneNO = craneNO1st*100 + craneNOlast;*/
//
//		int trueCraneNO = StringHelper::ToNumber<int>(cranePLCOrderBase.getCraneNO());
//
//		//组织发送电文数据
//		stuMsgData.craneNo = trueCraneNO;
//		stuMsgData.orderID = cranePLCOrderBase.getOrderID();
//		stuMsgData.matWeight = cranePLCOrderBase.getMatWeight();
//		stuMsgData.matType = cranePLCOrderBase.getMatType();
//		stuMsgData.planUpX = cranePLCOrderBase.getPlanUpX();
//		stuMsgData.planUpY = cranePLCOrderBase.getPlanUpY();
//		stuMsgData.planUpZ = cranePLCOrderBase.getPlanUpZ();
//		stuMsgData.upRotateAngle = cranePLCOrderBase.getUpRotateAngleSet();
//		stuMsgData.planDownX = cranePLCOrderBase.getPlanDownX();
//		stuMsgData.planDownY =cranePLCOrderBase.getPlanDownY();
//		stuMsgData.planDownZ =cranePLCOrderBase.getPlanDownZ();
//		stuMsgData.downRotateAngle = cranePLCOrderBase.getDownRotateAngleSet();
//		stuMsgData.shortCmd = cranePLCOrderBase.getShortCmd();
//
//		//=======================以下是中间点赋值===========================
//		map<long, map<string, long> >  mapPointList = cranePLCOrderBase.getMapMidPointList();
//		map<string, long> mapPoint;
//
//		mapPoint = mapPointList[1];
//		stuMsgData.midPoint1X = (int)mapPoint["X"];
//		stuMsgData.midPoint1Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[2];
//		stuMsgData.midPoint2X = (int)mapPoint["X"];
//		stuMsgData.midPoint2Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[3];
//		stuMsgData.midPoint3X = (int)mapPoint["X"];
//		stuMsgData.midPoint3Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[4];
//		stuMsgData.midPoint4X = (int)mapPoint["X"];
//		stuMsgData.midPoint4Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[5];
//		stuMsgData.midPoint5X = (int)mapPoint["X"];
//		stuMsgData.midPoint5Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[6];
//		stuMsgData.midPoint6X = (int)mapPoint["X"];
//		stuMsgData.midPoint6Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[7];
//		stuMsgData.midPoint7X = (int)mapPoint["X"];
//		stuMsgData.midPoint7Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[8];
//		stuMsgData.midPoint8X = (int)mapPoint["X"];
//		stuMsgData.midPoint8Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[9];
//		stuMsgData.midPoint9X = (int)mapPoint["X"];
//		stuMsgData.midPoint9Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[10];
//		stuMsgData.midPoint10X = (int)mapPoint["X"];
//		stuMsgData.midPoint10Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[11];
//		stuMsgData.midPoint11X = (int)mapPoint["X"];
//		stuMsgData.midPoint11Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[12];
//		stuMsgData.midPoint12X = (int)mapPoint["X"];
//		stuMsgData.midPoint12Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[13];
//		stuMsgData.midPoint13X = (int)mapPoint["X"];
//		stuMsgData.midPoint13Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[14];
//		stuMsgData.midPoint14X = (int)mapPoint["X"];
//		stuMsgData.midPoint14Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[15];
//		stuMsgData.midPoint15X = (int)mapPoint["X"];
//		stuMsgData.midPoint15Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[16];
//		stuMsgData.midPoint16X = (int)mapPoint["X"];
//		stuMsgData.midPoint16Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[17];
//		stuMsgData.midPoint17X = (int)mapPoint["X"];
//		stuMsgData.midPoint17Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[18];
//		stuMsgData.midPoint18X = (int)mapPoint["X"];
//		stuMsgData.midPoint18Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[19];
//		stuMsgData.midPoint19X = (int)mapPoint["X"];
//		stuMsgData.midPoint19Y = (int)mapPoint["Y"];
//
//		mapPoint = mapPointList[20];
//		stuMsgData.midPoint20X = (int)mapPoint["X"];
//		stuMsgData.midPoint20Y = (int)mapPoint["Y"];
//
//
//
//		arrayMsgDataBuf.resize(sizeof(stuMsgData));
//
//		memcpy((void*)&arrayMsgDataBuf.front(),(char*)&stuMsgData,sizeof(stuMsgData));
//
//		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );
//
//		//打印发送电文内容日志
//		log.Debug()<<"craneNo="<<stuMsgData.craneNo<<endl;
//		log.Debug()<<"orderID="<<stuMsgData.orderID<<endl;
//		log.Debug()<<"matWeight="<<stuMsgData.matWeight<<endl;
//		log.Debug()<<"matType="<<stuMsgData.matType<<endl;
//		log.Debug()<<"planUpX="<<stuMsgData.planUpX<<endl;
//		log.Debug()<<"planUpY="<<stuMsgData.planUpY<<endl;
//		log.Debug()<<"planUpZ="<<stuMsgData.planUpZ<<endl;
//		log.Debug()<<"uprotateAngle="<<stuMsgData.upRotateAngle<<endl;
//		log.Debug()<<"planDownX="<<stuMsgData.planDownX<<endl;
//		log.Debug()<<"planDownY="<<stuMsgData.planDownY<<endl;
//		log.Debug()<<"planDownZ="<<stuMsgData.planDownZ<<endl;
//		log.Debug()<<"downrotateAngle="<<stuMsgData.downRotateAngle<<endl;
//		log.Debug()<<"shortCmd="<<stuMsgData.shortCmd<<endl;
//		log.Debug()<<"midPoint1X="<<stuMsgData.midPoint1X<<endl;
//		log.Debug()<<"midPoint1Y="<<stuMsgData.midPoint1Y<<endl;
//		log.Debug()<<"midPoint2X="<<stuMsgData.midPoint2X<<endl;
//		log.Debug()<<"midPoint2Y="<<stuMsgData.midPoint2Y<<endl;
//		log.Debug()<<"midPoint3X="<<stuMsgData.midPoint3X<<endl;
//		log.Debug()<<"midPoint3Y="<<stuMsgData.midPoint3Y<<endl;
//		log.Debug()<<"midPoint4X="<<stuMsgData.midPoint4X<<endl;
//		log.Debug()<<"midPoint4Y="<<stuMsgData.midPoint4Y<<endl;
//		log.Debug()<<"midPoint5X="<<stuMsgData.midPoint5X<<endl;
//		log.Debug()<<"midPoint5Y="<<stuMsgData.midPoint5Y<<endl;
//		log.Debug()<<"midPoint6X="<<stuMsgData.midPoint6X<<endl;
//		log.Debug()<<"midPoint6Y="<<stuMsgData.midPoint6Y<<endl;
//		log.Debug()<<"midPoint7X="<<stuMsgData.midPoint7X<<endl;
//		log.Debug()<<"midPoint7Y="<<stuMsgData.midPoint7Y<<endl;
//		log.Debug()<<"midPoint8X="<<stuMsgData.midPoint8X<<endl;
//		log.Debug()<<"midPoint8Y="<<stuMsgData.midPoint8Y<<endl;
//		log.Debug()<<"midPoint9X="<<stuMsgData.midPoint9X<<endl;
//		log.Debug()<<"midPoint9Y="<<stuMsgData.midPoint9Y<<endl;
//		log.Debug()<<"midPoint10X="<<stuMsgData.midPoint10X<<endl;
//		log.Debug()<<"midPoint10Y="<<stuMsgData.midPoint10Y<<endl;
//		log.Debug()<<"midPoint11X="<<stuMsgData.midPoint11X<<endl;
//		log.Debug()<<"midPoint11Y="<<stuMsgData.midPoint11Y<<endl;
//		log.Debug()<<"midPoint12X="<<stuMsgData.midPoint12X<<endl;
//		log.Debug()<<"midPoint12Y="<<stuMsgData.midPoint12Y<<endl;
//		log.Debug()<<"midPoint13X="<<stuMsgData.midPoint13X<<endl;
//		log.Debug()<<"midPoint13Y="<<stuMsgData.midPoint13Y<<endl;
//		log.Debug()<<"midPoint14X="<<stuMsgData.midPoint14X<<endl;
//		log.Debug()<<"midPoint14Y="<<stuMsgData.midPoint14Y<<endl;
//		log.Debug()<<"midPoint15X="<<stuMsgData.midPoint15X<<endl;
//		log.Debug()<<"midPoint15Y="<<stuMsgData.midPoint15Y<<endl;
//		log.Debug()<<"midPoint16X="<<stuMsgData.midPoint16X<<endl;
//		log.Debug()<<"midPoint16Y="<<stuMsgData.midPoint16Y<<endl;
//		log.Debug()<<"midPoint17X="<<stuMsgData.midPoint17X<<endl;
//		log.Debug()<<"midPoint17Y="<<stuMsgData.midPoint17Y<<endl;
//		log.Debug()<<"midPoint18X="<<stuMsgData.midPoint18X<<endl;
//		log.Debug()<<"midPoint18Y="<<stuMsgData.midPoint18Y<<endl;
//		log.Debug()<<"midPoint19X="<<stuMsgData.midPoint19X<<endl;
//		log.Debug()<<"midPoint19Y="<<stuMsgData.midPoint19Y<<endl;
//		log.Debug()<<"midPoint20X="<<stuMsgData.midPoint20X<<endl;
//		log.Debug()<<"midPoint20Y="<<stuMsgData.midPoint20Y<<endl;
//
//
//		int lineNO = getLineNO( cranePLCOrderBase.getCraneNO());
//
//		log.Debug()<<"lineNO="<<lineNO<<endl;
//		
//		int ret=PCS_Send(lineNO,msgId,arrayMsgDataBuf);
//		log.Debug()<<"ret="<<ret<<endl;
//
//		log.Info()<<endl<<"UC01 sended out ............................................................................................................................................................................................................................. "<<endl;
//
//		//2017.12.15 zhangyuhong add
//		//将发送的行车指令电文存储到数据库表UACS_CRANE_MOVEORDER_MSG，除了心跳电文不发（shortCMD=900）
//		if (cranePLCOrderBase.getShortCmd() != 900)
//		{
//			//20190807 zhangyuhong add
//			//新增行车当前 X Y Z 插入到表里
//			CranePLCStatusBase cranePLCStatusCurrent;
//			CraneMonitor::getInstance()->getNeighborPLCStatus(cranePLCOrderBase.getCraneNO(), cranePLCStatusCurrent);
//
//			//获取msgID
//			long msgID = 0;
//			Adapter_UACS_CRANE_MOVEORDER_MSG::SelMsgID(msgID);
//
//			if(true == Adapter_UACS_CRANE_MOVEORDER_MSG::insertMoveOrderMsg( msgID, 
//																																					   (long)trueCraneNO, 
//																																						cranePLCOrderBase.getOrderID(),
//																																						cranePLCOrderBase.getMatWeight(), 
//																																						cranePLCOrderBase.getMatType(), 
//																																					    cranePLCOrderBase.getPlanUpX(),
//																																					    cranePLCOrderBase.getPlanUpY(),
//																																					    cranePLCOrderBase.getPlanUpZ(),
//																																					    cranePLCOrderBase.getUpRotateAngleSet(),
//																																					    cranePLCOrderBase.getPlanDownX(),
//																																					    cranePLCOrderBase.getPlanDownY(),
//																																					    cranePLCOrderBase.getPlanDownZ(),
//																																					    cranePLCOrderBase.getDownRotateAngleSet(),
//																																					    cranePLCOrderBase.getShortCmd(), 
//																																					    cranePLCStatusCurrent.getXAct(), 
//																																					    cranePLCStatusCurrent.getYAct(), 
//																																					    cranePLCStatusCurrent.getZAct() 
//																																					    )  )
//			{
//				log.Debug()<<"指令下发数据表日志写入成功！"<<endl;
//			}
//
//			if( true == Adapter_UACS_CRANE_MOVEORDER_MSG::insertMoveOrderMsgMidPT( msgID, cranePLCOrderBase.getMapMidPointList() ) )
//			{
//				log.Debug()<<"中间点数据表日志写入成功！"<<endl;
//			}			
//		}
//
//	}
//	catch(iDA::Exception &x)
//	{
//		try
//		{
//			CDataAccess::GetInstance()->m_DBCon.Rollback();
//		}
//		catch(iDA::Exception &)
//		{
//		}
//
//		string msg = functionName +"   error:"+ x.ErrMsg();
//		log.Debug()<<msg<<endl;
//	}
//    catch (std::exception& stdex)
//    {
//		string errorMessage=stdex.what();
//		string msg=functionName +"   error:"+ errorMessage;
//		log.Debug()<<msg<<endl;
//    }
//	catch (...)
//	{
//		string msg = functionName +"   error:";
//		log.Debug()<<msg<<endl;
//	}
//	return ret;
//}



int MsgEUCR01::getLineNO(string craneNO)
{
	string functionName="MsgEUCR01 :: getLineNO()";
	LOG log(functionName, AUTO_CATCH_PID);	

	int lineNO=0;
	try
	{		
		if (craneNO == "1")
		{
			lineNO = 11;
		}
		else if (craneNO == "2")
		{
			lineNO = 12;
		}
		else if (craneNO == "3")
		{
			lineNO = 13;
		}
		else if (craneNO == "4")
		{
			lineNO = 14;
		}
		return lineNO;

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
	return lineNO;
}






bool MsgEUCR01::SendOutMessage_III(CranePLCOrderBase cranePLCOrderBase)
{
	bool ret=true;
	string functionName="MsgCREU01 :: SendOutMessage()";


	LOG log(functionName, AUTO_CATCH_PID);
	LOG log_EV(functionName, "WatchEventHandlerI");


	//获取远地iMultiLink的代理

	::iPlature::iMultiLink::MultiLinkAPIPrx	iMultiLinkAPIPrx;	

	iMultiLinkAPIPrx = ProxyWrapper< ::iPlature::iMultiLink::MultiLinkAPIPrx>("iMultiLink/API");

	

	typedef ::std::map< ::std::string, ::std::string> TAGVALUEMAP;
	TAGVALUEMAP tagPairs;

	//获得schedulerName
	string schedulerName=::iPlature::iMultiLink::MultiLine_MDProxy_TimerWatchInterfaceI::getSchedulerName(  cranePLCOrderBase.getCraneNO());


	string adressHead=cranePLCOrderBase.getCraneNO()+"_";

	try
	{

		log.Debug()<<"........................................................................................now begin to treat the message EUCR01.................................................................................................................."<<endl;
		log_EV.Debug()<<"........................................................................................now begin to treat the message EUCR01.................................................................................................................."<<endl;



		string TagName="";
		string TagValue="";

		//1 CRANE_NO     
		TagName=adressHead+CranePLCOrderBase::ADRESS_CRANE_NO_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getCraneNO());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//2 SHORT_CMD     
		TagName=adressHead+CranePLCOrderBase::ADRESS_SHORT_CMD_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getShortCmd());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;

		//3 ORDER_Id     
		TagName=adressHead+CranePLCOrderBase::ADRESS_ORDER_Id_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getOrderID());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;

		//4 MAT_TYPE     
		TagName=adressHead+CranePLCOrderBase::ADRESS_MAT_TYPE_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getMatType());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;

		//5 MAT_YARD     
		TagName=adressHead+CranePLCOrderBase::ADRESS_MAT_YARD_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getMatYard());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;

		//6 MAT_WEIGHT     
		TagName=adressHead+CranePLCOrderBase::ADRESS_MAT_WEIGHT_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getMatWeight());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;

		//7 PLAN_UP_X
		TagName=adressHead+CranePLCOrderBase::ADRESS_PLAN_UP_X_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getPlanUpX());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//8 PLAN_UP_Y
		TagName=adressHead+CranePLCOrderBase::ADRESS_PLAN_UP_Y_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getPlanUpY());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//9 PLAN_UP_Z
		TagName=adressHead+CranePLCOrderBase::ADRESS_PLAN_UP_Z_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getPlanUpZ());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//10 PLAN_DOWN_X
		TagName=adressHead+CranePLCOrderBase::ADRESS_PLAN_DOWN_X_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getPlanDownX());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//11 PLAN_DOWN_Y
		TagName=adressHead+CranePLCOrderBase::ADRESS_PLAN_DOWN_Y_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getPlanDownY());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//12 PLAN_DOWN_Z
		TagName=adressHead+CranePLCOrderBase::ADRESS_PLAN_DOWN_Z_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getPlanDownZ());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//13 SPACE
		TagName=adressHead+CranePLCOrderBase::ADRESS_SPACE_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getSpace());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//14 CRC
		TagName=adressHead+CranePLCOrderBase::ADRESS_CRC_SET;
		TagValue=StringHelper::ToString(cranePLCOrderBase.getCrc());
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		log.Debug()<<TagName<<"="<<TagValue<<endl;
		log_EV.Debug()<<TagName<<"="<<TagValue<<endl;


		//tag点写入系统
		iMultiLinkAPIPrx->WriteDownByBatch(schedulerName, tagPairs, 1);
		log.Debug()<<"指令下达到PLC完成！"<<endl;
		log_EV.Debug()<<"指令下达到PLC完成！"<<endl;
		cranePLCOrderBase.logOutValues();

		//MySleep::doSleep(200);
		//Sleep(1000);
#ifdef WIN32
			Sleep(1000);
#else
			sleep(1);
#endif				

		//tagPairs.clear();
		//TagName=adressHead+CranePLCOrderBase::ADRESS_DOWN_LOAD_ORDER;
		//TagValue="1";
		//tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		//iMultiLinkAPIPrx->WriteDownByBatch(schedulerName, tagPairs, 1);

		//log.Debug()<<"行车启动脉冲置1"<<endl;
		//log_EV.Debug()<<"行车启动脉冲置1"<<endl;

//#ifdef WIN32
//			Sleep(1000);
//#else
//			sleep(1);
//#endif				
		//Sleep(1000);

		//MySleep::doSleep(200);

		//tagPairs.clear();
		//TagName=adressHead+CranePLCOrderBase::ADRESS_DOWN_LOAD_ORDER;
		//TagValue="0";
		//tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		//iMultiLinkAPIPrx->WriteDownByBatch(schedulerName, tagPairs, 1);

		//log.Debug()<<"行车启动脉冲置0"<<endl;
		//log_EV.Debug()<<"行车启动脉冲置0"<<endl;

		//tagPairs.clear();
		//TagName=adressHead+CranePLCOrderBase::ADRESS_SPACE_SET;
		//TagValue="1";
		//tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		//iMultiLinkAPIPrx->WriteDownByBatch(schedulerName, tagPairs, 1);

		//log.Debug()<<"行车启动脉冲置1"<<endl;
		//log_EV.Debug()<<"行车启动脉冲置1"<<endl;

		tagPairs.clear();
		TagName=adressHead+CranePLCOrderBase::ADRESS_SPACE_SET;
		TagValue="0";
		tagPairs.insert(map<string,string>::value_type( TagName , TagValue ) );

		iMultiLinkAPIPrx->WriteDownByBatch(schedulerName, tagPairs, 1);

		log.Debug()<<"行车启动脉冲置0"<<endl;
		log_EV.Debug()<<"行车启动脉冲置0"<<endl;


		log.Info()<<endl<<"EUCR01 sended out ............................................................................................................................................................................................................................. "<<endl;
		log_EV.Info()<<endl<<"EUCR01 sended out ............................................................................................................................................................................................................................. "<<endl;


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