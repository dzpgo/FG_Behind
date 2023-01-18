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




bool MsgEUCR01::SendOutMessage(CranePLCOrderBase cranePLCOrderBase)
{
	bool ret=true;
	string functionName="MsgEUCR01 :: SendOutMessage()";


	LOG log(functionName, AUTO_CATCH_PID);


	AlarmWrapper _p("");

	try
	{
		log.Debug()<<"........................................................................................now begin to treat the message UC01.................................................................................................................."<<endl;

		ArrayMsg arrayMsgDataBuf;

		//2017.9.25  zhangyuhong add
		struct msgStruct4EUCR01
		{
			int craneNo;							//�г���
			int orderID;							//��ǰָ���
			int matWeight;						//ȡ������
			int matType;							//ȡ������
			int planUpX;							//�ƻ����X
			int planUpY;							//�ƻ����Y
			int planUpZ;							//�ƻ����Z	
			int upRotateAngle;				//�����ǯ��ת�Ƕ�
			int planDownX;						//�ƻ����X
			int planDownY;						//�ƻ����Y
			int planDownZ;						//�ƻ����Z	
			int downRotateAngle;		//��ؼ�ǯ��ת�Ƕ�
			int shortCmd;						//��ָ��  0=��ִ������   1=ִ������    100=Ҫ��ͣ��   200=Ҫ�����ͣ��  300=Ҫ����ϸ�λ   400=Ҫ�������Զ�  500=ȡ��������Զ�
			int midPoint1X;					//1X
			int midPoint1Y;						//1Y
			int midPoint2X;					//2X
			int midPoint2Y;						//2Y
			int midPoint3X;					//3X
			int midPoint3Y;						//3Y
			int midPoint4X;					//4X
			int midPoint4Y;						//4Y
			int midPoint5X;					//5X
			int midPoint5Y;						//5Y
			int midPoint6X;					//6X
			int midPoint6Y;						//6Y
			int midPoint7X;					//7X
			int midPoint7Y;						//7Y
			int midPoint8X;					//8X
			int midPoint8Y;						//8Y
			int midPoint9X;					//9X
			int midPoint9Y;						//9Y
			int midPoint10X;					//10X
			int midPoint10Y;					//10Y
			int midPoint11X;					//11X
			int midPoint11Y;					//11Y
			int midPoint12X;					//12X
			int midPoint12Y;					//12Y
			int midPoint13X;					//13X
			int midPoint13Y;					//13Y
			int midPoint14X;					//14X
			int midPoint14Y;					//14Y
			int midPoint15X;					//15X
			int midPoint15Y;					//15Y
			int midPoint16X;					//16X
			int midPoint16Y;					//16Y
			int midPoint17X;					//17X
			int midPoint17Y;					//17Y
			int midPoint18X;					//18X
			int midPoint18Y;					//18Y
			int midPoint19X;					//19X
			int midPoint19Y;					//19Y
			int midPoint20X;					//20X
			int midPoint20Y;					//20Y
		}stuMsgData;

		//cranePLCOrderBase�������craneNO��string�ͣ���Ҫת����int�ͣ��Թ������ã���������int�ͣ�
		/*vector<string> vec1 = StringHelper::Split(cranePLCOrderBase.getCraneNO(),'_');
		int craneNO1st = StringHelper::ToNumber<int>(vec1[0]);
		int craneNOlast = StringHelper::ToNumber<int>(vec1[1]);
		int trueCraneNO = craneNO1st*100 + craneNOlast;*/

		int trueCraneNO = StringHelper::ToNumber<int>(cranePLCOrderBase.getCraneNO());

		//��֯���͵�������
		stuMsgData.craneNo = trueCraneNO;
		stuMsgData.orderID = cranePLCOrderBase.getOrderID();
		stuMsgData.matWeight = cranePLCOrderBase.getMatWeight();
		stuMsgData.matType = cranePLCOrderBase.getMatType();
		stuMsgData.planUpX = cranePLCOrderBase.getPlanUpX();
		stuMsgData.planUpY = cranePLCOrderBase.getPlanUpY();
		stuMsgData.planUpZ = cranePLCOrderBase.getPlanUpZ();
		stuMsgData.upRotateAngle = cranePLCOrderBase.getUpRotateAngleSet();
		stuMsgData.planDownX = cranePLCOrderBase.getPlanDownX();
		stuMsgData.planDownY =cranePLCOrderBase.getPlanDownY();
		stuMsgData.planDownZ =cranePLCOrderBase.getPlanDownZ();
		stuMsgData.downRotateAngle = cranePLCOrderBase.getDownRotateAngleSet();
		stuMsgData.shortCmd = cranePLCOrderBase.getShortCmd();

		//=======================�������м�㸳ֵ===========================
		map<long, map<string, long> >  mapPointList = cranePLCOrderBase.getMapMidPointList();
		map<string, long> mapPoint;

		mapPoint = mapPointList[1];
		stuMsgData.midPoint1X = (int)mapPoint["X"];
		stuMsgData.midPoint1Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[2];
		stuMsgData.midPoint2X = (int)mapPoint["X"];
		stuMsgData.midPoint2Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[3];
		stuMsgData.midPoint3X = (int)mapPoint["X"];
		stuMsgData.midPoint3Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[4];
		stuMsgData.midPoint4X = (int)mapPoint["X"];
		stuMsgData.midPoint4Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[5];
		stuMsgData.midPoint5X = (int)mapPoint["X"];
		stuMsgData.midPoint5Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[6];
		stuMsgData.midPoint6X = (int)mapPoint["X"];
		stuMsgData.midPoint6Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[7];
		stuMsgData.midPoint7X = (int)mapPoint["X"];
		stuMsgData.midPoint7Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[8];
		stuMsgData.midPoint8X = (int)mapPoint["X"];
		stuMsgData.midPoint8Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[9];
		stuMsgData.midPoint9X = (int)mapPoint["X"];
		stuMsgData.midPoint9Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[10];
		stuMsgData.midPoint10X = (int)mapPoint["X"];
		stuMsgData.midPoint10Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[11];
		stuMsgData.midPoint11X = (int)mapPoint["X"];
		stuMsgData.midPoint11Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[12];
		stuMsgData.midPoint12X = (int)mapPoint["X"];
		stuMsgData.midPoint12Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[13];
		stuMsgData.midPoint13X = (int)mapPoint["X"];
		stuMsgData.midPoint13Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[14];
		stuMsgData.midPoint14X = (int)mapPoint["X"];
		stuMsgData.midPoint14Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[15];
		stuMsgData.midPoint15X = (int)mapPoint["X"];
		stuMsgData.midPoint15Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[16];
		stuMsgData.midPoint16X = (int)mapPoint["X"];
		stuMsgData.midPoint16Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[17];
		stuMsgData.midPoint17X = (int)mapPoint["X"];
		stuMsgData.midPoint17Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[18];
		stuMsgData.midPoint18X = (int)mapPoint["X"];
		stuMsgData.midPoint18Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[19];
		stuMsgData.midPoint19X = (int)mapPoint["X"];
		stuMsgData.midPoint19Y = (int)mapPoint["Y"];

		mapPoint = mapPointList[20];
		stuMsgData.midPoint20X = (int)mapPoint["X"];
		stuMsgData.midPoint20Y = (int)mapPoint["Y"];



		arrayMsgDataBuf.resize(sizeof(stuMsgData));

		memcpy((void*)&arrayMsgDataBuf.front(),(char*)&stuMsgData,sizeof(stuMsgData));

		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//��ӡ���͵���������־
		log.Debug()<<"craneNo="<<stuMsgData.craneNo<<endl;
		log.Debug()<<"orderID="<<stuMsgData.orderID<<endl;
		log.Debug()<<"matWeight="<<stuMsgData.matWeight<<endl;
		log.Debug()<<"matType="<<stuMsgData.matType<<endl;
		log.Debug()<<"planUpX="<<stuMsgData.planUpX<<endl;
		log.Debug()<<"planUpY="<<stuMsgData.planUpY<<endl;
		log.Debug()<<"planUpZ="<<stuMsgData.planUpZ<<endl;
		log.Debug()<<"uprotateAngle="<<stuMsgData.upRotateAngle<<endl;
		log.Debug()<<"planDownX="<<stuMsgData.planDownX<<endl;
		log.Debug()<<"planDownY="<<stuMsgData.planDownY<<endl;
		log.Debug()<<"planDownZ="<<stuMsgData.planDownZ<<endl;
		log.Debug()<<"downrotateAngle="<<stuMsgData.downRotateAngle<<endl;
		log.Debug()<<"shortCmd="<<stuMsgData.shortCmd<<endl;
		log.Debug()<<"midPoint1X="<<stuMsgData.midPoint1X<<endl;
		log.Debug()<<"midPoint1Y="<<stuMsgData.midPoint1Y<<endl;
		log.Debug()<<"midPoint2X="<<stuMsgData.midPoint2X<<endl;
		log.Debug()<<"midPoint2Y="<<stuMsgData.midPoint2Y<<endl;
		log.Debug()<<"midPoint3X="<<stuMsgData.midPoint3X<<endl;
		log.Debug()<<"midPoint3Y="<<stuMsgData.midPoint3Y<<endl;
		log.Debug()<<"midPoint4X="<<stuMsgData.midPoint4X<<endl;
		log.Debug()<<"midPoint4Y="<<stuMsgData.midPoint4Y<<endl;
		log.Debug()<<"midPoint5X="<<stuMsgData.midPoint5X<<endl;
		log.Debug()<<"midPoint5Y="<<stuMsgData.midPoint5Y<<endl;
		log.Debug()<<"midPoint6X="<<stuMsgData.midPoint6X<<endl;
		log.Debug()<<"midPoint6Y="<<stuMsgData.midPoint6Y<<endl;
		log.Debug()<<"midPoint7X="<<stuMsgData.midPoint7X<<endl;
		log.Debug()<<"midPoint7Y="<<stuMsgData.midPoint7Y<<endl;
		log.Debug()<<"midPoint8X="<<stuMsgData.midPoint8X<<endl;
		log.Debug()<<"midPoint8Y="<<stuMsgData.midPoint8Y<<endl;
		log.Debug()<<"midPoint9X="<<stuMsgData.midPoint9X<<endl;
		log.Debug()<<"midPoint9Y="<<stuMsgData.midPoint9Y<<endl;
		log.Debug()<<"midPoint10X="<<stuMsgData.midPoint10X<<endl;
		log.Debug()<<"midPoint10Y="<<stuMsgData.midPoint10Y<<endl;
		log.Debug()<<"midPoint11X="<<stuMsgData.midPoint11X<<endl;
		log.Debug()<<"midPoint11Y="<<stuMsgData.midPoint11Y<<endl;
		log.Debug()<<"midPoint12X="<<stuMsgData.midPoint12X<<endl;
		log.Debug()<<"midPoint12Y="<<stuMsgData.midPoint12Y<<endl;
		log.Debug()<<"midPoint13X="<<stuMsgData.midPoint13X<<endl;
		log.Debug()<<"midPoint13Y="<<stuMsgData.midPoint13Y<<endl;
		log.Debug()<<"midPoint14X="<<stuMsgData.midPoint14X<<endl;
		log.Debug()<<"midPoint14Y="<<stuMsgData.midPoint14Y<<endl;
		log.Debug()<<"midPoint15X="<<stuMsgData.midPoint15X<<endl;
		log.Debug()<<"midPoint15Y="<<stuMsgData.midPoint15Y<<endl;
		log.Debug()<<"midPoint16X="<<stuMsgData.midPoint16X<<endl;
		log.Debug()<<"midPoint16Y="<<stuMsgData.midPoint16Y<<endl;
		log.Debug()<<"midPoint17X="<<stuMsgData.midPoint17X<<endl;
		log.Debug()<<"midPoint17Y="<<stuMsgData.midPoint17Y<<endl;
		log.Debug()<<"midPoint18X="<<stuMsgData.midPoint18X<<endl;
		log.Debug()<<"midPoint18Y="<<stuMsgData.midPoint18Y<<endl;
		log.Debug()<<"midPoint19X="<<stuMsgData.midPoint19X<<endl;
		log.Debug()<<"midPoint19Y="<<stuMsgData.midPoint19Y<<endl;
		log.Debug()<<"midPoint20X="<<stuMsgData.midPoint20X<<endl;
		log.Debug()<<"midPoint20Y="<<stuMsgData.midPoint20Y<<endl;


		int lineNO = getLineNO( cranePLCOrderBase.getCraneNO());

		log.Debug()<<"lineNO="<<lineNO<<endl;
		
		int ret=PCS_Send(lineNO,msgId,arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;

		log.Info()<<endl<<"UC01 sended out ............................................................................................................................................................................................................................. "<<endl;

		//2017.12.15 zhangyuhong add
		//�����͵��г�ָ����Ĵ洢�����ݿ��UACS_CRANE_MOVEORDER_MSG�������������Ĳ�����shortCMD=900��
		if (cranePLCOrderBase.getShortCmd() != 900)
		{
			//20190807 zhangyuhong add
			//�����г���ǰ X Y Z ���뵽����
			CranePLCStatusBase cranePLCStatusCurrent;
			CraneMonitor::getInstance()->getNeighborPLCStatus(cranePLCOrderBase.getCraneNO(), cranePLCStatusCurrent);

			//��ȡmsgID
			long msgID = 0;
			Adapter_UACS_CRANE_MOVEORDER_MSG::SelMsgID(msgID);

			if(true == Adapter_UACS_CRANE_MOVEORDER_MSG::insertMoveOrderMsg( msgID, 
																																					   (long)trueCraneNO, 
																																						cranePLCOrderBase.getOrderID(),
																																						cranePLCOrderBase.getMatWeight(), 
																																						cranePLCOrderBase.getMatType(), 
																																					    cranePLCOrderBase.getPlanUpX(),
																																					    cranePLCOrderBase.getPlanUpY(),
																																					    cranePLCOrderBase.getPlanUpZ(),
																																					    cranePLCOrderBase.getUpRotateAngleSet(),
																																					    cranePLCOrderBase.getPlanDownX(),
																																					    cranePLCOrderBase.getPlanDownY(),
																																					    cranePLCOrderBase.getPlanDownZ(),
																																					    cranePLCOrderBase.getDownRotateAngleSet(),
																																					    cranePLCOrderBase.getShortCmd(), 
																																					    cranePLCStatusCurrent.getXAct(), 
																																					    cranePLCStatusCurrent.getYAct(), 
																																					    cranePLCStatusCurrent.getZAct() 
																																					    )  )
			{
				log.Debug()<<"ָ���·����ݱ���־д��ɹ���"<<endl;
			}

			if( true == Adapter_UACS_CRANE_MOVEORDER_MSG::insertMoveOrderMsgMidPT( msgID, cranePLCOrderBase.getMapMidPointList() ) )
			{
				log.Debug()<<"�м�����ݱ���־д��ɹ���"<<endl;
			}			
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



