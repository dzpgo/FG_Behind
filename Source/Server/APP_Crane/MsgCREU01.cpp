#include "MsgCREU01.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;



MsgCREU01*  MsgCREU01::m_pMsgCREU01 = NULL;



MsgCREU01::MsgCREU01() 
{
	msgId="CU01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgCREU01 :: ~MsgCREU01(void)
{
	
	delete m_pMsgCREU01;


}

 MsgCREU01* MsgCREU01::getInstance(void)
{
	if (m_pMsgCREU01 == NULL)
	{
		m_pMsgCREU01 = new MsgCREU01;
	}
	return m_pMsgCREU01;
}

 //2017.9.1  zhangyuhong add
 //param1:data							�ֽ���
 //param2:start4BytesPos		��ʼת����λ�ã�4�ֽ�һ�飬��0��ʼ��ţ�
 //param3:countShift				��Ҫת����DINT������
 ByteSeq MsgCREU01::HighLowByteShift(ByteSeq data, int start4BytesPos , int countShift)
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

 string MsgCREU01::GetRealCraneNO(int PlcCraneNO)
 {
	string realCraneNO = "";

	switch(PlcCraneNO) 
	{
	  case 1:
		  realCraneNO = "A1";
		  break;
	  case 2:
		  realCraneNO = "A2";
		  break;
	  case 3:
		  realCraneNO = "B1";
		  break;
	  case 4:
		  realCraneNO = "B2";
		  break;
	  case 5:
		  realCraneNO = "B3";
		  break;
	  case 6:
		  realCraneNO = "C1";
		  break;
	  case 7:
		  realCraneNO = "C2";
		  break;
	  case 8:
		  realCraneNO = "C3";
		  break;
	  case 9:
		  realCraneNO = "E1";
		  break;
	  case 10:
		  realCraneNO = "E2";
		  break;
	  case 11:
		  realCraneNO = "F1";
		  break;
	  case 12:
		  realCraneNO = "F2";
		  break;
	  default:
		  break;
	}

	return realCraneNO;
 }


ByteSeq MsgCREU01::HandleMessage(string myCraneNO,
																		string cranePLCStatusTopicName,
																		const ByteSeq& ParamBuffer, 
																		vector<long>& vecOrderIDAlarmCodeLast, 
																		CranePLCStatusBase& cranePLCStatus_Last)
{
	string functionName="MsgCREU01 :: HandleMessage()";

	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{

		// ��ȡpowertrans���Ľṹ
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			readSmartDataSuccessed=true;
		}
		
		//2017.9.18   zhangyuhong  add 
		//���C612���г�PLC��Siemens S7-300���ڸߵ��ֽ�ת�����⣬���޸��ֽ������մ���

		//******************�ߵ��ֽ�ת����ʼ************************************

		//ת��ԭ���ַ����ֽ�����ת����4�ֽ����Ͷ���������ת��
				
		//����ֻתһ�Σ����������ֶξ�ΪDIN
		//ByteSeq dataAfterShift = HighLowByteShift(ParamBuffer, 0, 32);
		//2018.8.28 zhangyuhong add
		//�����˷�ˮ����
		ByteSeq dataAfterShift = HighLowByteShift(ParamBuffer, 0, 33);

		//zhangyuhong add
		//��ʽ����ʱ����Ҫ�ſ���������   �Լ�����ʱ��Ҫ����
		//��ȡ�ߵ��ֽ�ת������ֽ���
		sd.readFrom(dataAfterShift);

		//******************�ߵ��ֽ�ת������************************************
		//�Լ�����ʱ����Ҫ�ſ���������  ��ʽ����ʱ��Ҫ����
		//��ȡԭʼ�ֽ���
		//sd.readFrom(ParamBuffer);

		log.Debug()<<"........................................................................................log of samrt data..................................................................................................................."<<endl;

		//1		CRANE_NO
		log.Debug()<<"\t\t 1.CRANE_NO="<<sd["CRANE_NO"].toInt();

		//2		READY
		log.Debug()<<"\t\t 2.READY="<<sd["READY"].toInt();

		//3		CONTROL_MODE
		log.Debug()<<"\t\t 3.CONTROL_MODE="<<sd["CONTROL_MODE"].toInt();
		
		//4		ASK_PLAN
		log.Debug()<<"\t\t  4.ASK_PLAN="<<sd["ASK_PLAN"].toInt() ;

		//5		TASK_EXCUTING
		log.Debug()<<"\t\t 5.TASK_EXCUTING="<<sd["TASK_EXCUTING"].toInt()<<endl;

		//6		XACT
		log.Debug()<<"\t\t 6.XACT="<<sd["XACT"].toInt();

		//7		YACT
		log.Debug()<<"\t \t 7.YACT="<<sd["YACT"].toInt();
		
		//8		ZACT
		log.Debug()<<"\t\t 8.ZACT="<<sd["ZACT"].toInt();

		//9		XSPEED
		log.Debug()<<"\t\t 9.XSPEED="<<sd["XSPEED"].toInt();

		//10		YSPEED
		log.Debug()<<"\t\t 10.YSPEED="<<sd["YSPEED"].toInt()<<endl;				

		//11		ZSPEED
		log.Debug()<<"\t\t 11.ZSPEED="<<sd["ZSPEED"].toInt();		

		//12		XDIR_P
		log.Debug()<<"\t\t 12.XDIR_P="<<sd["XDIR_P"].toInt();		

		//13		XDIR_N
		log.Debug()<<"\t\t 13.XDIR_N="<<sd["XDIR_N"].toInt();

		//14		YDIR_P
		log.Debug()<<"\t\t 14.YDIR_P="<< sd["YDIR_P"].toInt() ;

		//15		YDIR_N
		log.Debug()<<"\t\t 15.YDIR_N="<< sd["YDIR_N"].toInt()<<endl ;

		//16		ZDIR_P
		log.Debug()<<"\t\t 16ZDIR_P="<<sd["ZDIR_P"].toInt();

		//17		ZDIR_N
		log.Debug()<<"\t\t 17.ZDIR_N="<<sd["ZDIR_N"].toInt();

		//18		HAS_COIL
		log.Debug()<<"\t\t 18.HAS_COIL="<<sd["HAS_COIL"].toInt();

		//19		WEIGHT_LOADED
		log.Debug()<<"\t\t 19.WEIGHT_LOADED="<<sd["WEIGHT_LOADED"].toInt();

		//20		ROTATE_ANGLE_ACT
		log.Debug()<<"\t\t 20.ROTATE_ANGLE_ACT="<<sd["ROTATE_ANGLE_ACT"].toInt()<<endl;

		//21		EMG_STOP
		log.Debug()<<"\t\t 21.EMG_STOP="<<sd["EMG_STOP"].toInt();

		//22		ORDER_ID
		log.Debug()<<"\t\t 22.ORDER_ID="<<sd["ORDER_ID"].toInt();

		//23		PLAN_UP_X
		log.Debug()<<"\t\t 23.PLAN_UP_X="<<sd["PLAN_UP_X"].toInt();

		//24		PLAN_UP_Y
		log.Debug()<<"\t\t 24.PLAN_UP_Y="<<sd["PLAN_UP_Y"].toInt()<<endl;

		//25		PLAN_UP_Z
		log.Debug()<<"\t\t 25.PLAN_UP_Z="<<sd["PLAN_UP_Z"].toInt();

		//26		PLAN_DOWN_X
		log.Debug()<<"\t\t 26.PLAN_DOWN_X="<<sd["PLAN_DOWN_X"].toInt();

		//27		PLAN_DOWN_Y
		log.Debug()<<"\t\t 27.PLAN_DOWN_Y="<<sd["PLAN_DOWN_Y"].toInt();

		//28		PLAN_DOWN_Z
		log.Debug()<<"\t\t 28.PLAN_DOWN_Z="<<sd["PLAN_DOWN_Z"].toInt();

		//29		CRANE_STATUS
		log.Debug()<<"\t\t 29.CRANE_STATUS="<<sd["CRANE_STATUS"].toInt();

		//30		CRANE_ALARM
		log.Debug()<<"\t\t 30.CRANE_ALARM="<<sd["CRANE_ALARM"].toInt()<<endl;

		log.Debug()<<"........................................................................................now begin to treat the message..................................................................................................................."<<endl;



		//�г�PLC״̬��Ϣ�Ļ�����
		CranePLCStatusBase cranePLCStatusBase;
		

		//1		CRANE_NO
		//�г��ŵĸ�ʽΪ   301   ����   3_1   ��Ҫת��һ��
		//�г��ŵ�1λ�����̻��
		//string craneNO1st = StringHelper::ToString(sd["CRANE_NO"].toInt()/100);
		//�г��ź���λ��������
		//string craneNOLast = StringHelper::ToString(sd["CRANE_NO"].toInt()%100);
		//����string���͵��г��ſ���ƴ�ɣ�3_1
		//string craneNO=craneNO1st + "_" + craneNOLast;
		//string craneNO=sd["CRANE_NO"].toString();
		//StringHelper::Trim(craneNO);

		//��ʱ��ת���г��ž��� 1 2 3 
		//string craneNO = StringHelper::ToString(sd["CRANE_NO"].toInt());

		//��ȡplc�����е�craneNO��ʵ��craneNO���չ�ϵ
		// 1-A1  2-A2  ......
		string craneNO = GetRealCraneNO(sd["CRANE_NO"].toInt());

		if(craneNO!=myCraneNO)
		{
			log.Debug()<<"��ǰ�г�="<<myCraneNO<<"���յ����������г�="<<craneNO<<" ��״̬���ģ������账��"<<endl;
			return ret;
		}

		cranePLCStatusBase.setCraneNO(craneNO);
		log.Debug()<<"1......";

		//2		READY
		cranePLCStatusBase.setReady(sd["READY"].toInt() );
		log.Debug()<<"2......";

		//3		CONTROL_MODE
		cranePLCStatusBase.setControlMode( sd["CONTROL_MODE"].toInt() );
		log.Debug()<<"3......";
		
		//4		ASK_PLAN
		cranePLCStatusBase.setAskPlan( sd["ASK_PLAN"].toInt() );
		log.Debug()<<"4......";


		//5		TASK_EXCUTING
		cranePLCStatusBase.setTaskExcuting(sd["TASK_EXCUTING"].toInt() );
		log.Debug()<<"5......";

		//6		XACT
		cranePLCStatusBase.setXAct( sd["XACT"].toInt() );
		log.Debug()<<"6......";

		//7		YACT
		cranePLCStatusBase.setYAct( sd["YACT"].toInt() );
		log.Debug()<<"7......";
	
		//8		ZACT
		cranePLCStatusBase.setZAct( sd["ZACT"].toInt() );
		log.Debug()<<"8......";

		//9		XSPEED
		cranePLCStatusBase.setXSpeed( sd["XSPEED"].toInt() );
		log.Debug()<<"9......";

		//10	YSPEED
		cranePLCStatusBase.setYSpeed( sd["YSPEED"].toInt() );
		log.Debug()<<"10......";

		//11	ZSPEED
		cranePLCStatusBase.setZSpeed( sd["ZSPEED"].toInt() );
		log.Debug()<<"11......";

		//12	XDIR_P
		cranePLCStatusBase.setXDirectPositive( sd["XDIR_P"].toInt() );
		log.Debug()<<"12......";

		//13	XDIR_N
		cranePLCStatusBase.setXDirectNegative( sd["XDIR_N"].toInt() );
		log.Debug()<<"13......";

		//14	YDIR_P
		cranePLCStatusBase.setYDirectPositive( sd["YDIR_P"].toInt() );
		log.Debug()<<"14......";

		//15	YDIR_N
		cranePLCStatusBase.setYDirectNegative( sd["YDIR_N"].toInt() );
		log.Debug()<<"15......"<<endl;

		//16	zDirectPositive
		cranePLCStatusBase.setZDirectPositive( sd["ZDIR_P"].toInt() );
		log.Debug()<<"16......";

		//17	zDirectNegative
		cranePLCStatusBase.setZDirectNegative( sd["ZDIR_N"].toInt() );
		log.Debug()<<"17......";

		//18	hasCoil
		cranePLCStatusBase.setHasCoil( sd["HAS_COIL"].toInt() );
		log.Debug()<<"18......";

		//19	weightLoaded
		cranePLCStatusBase.setWeightLoaded( sd["WEIGHT_LOADED"].toInt() );
		log.Debug()<<"19......";

		//20	rotateAngleAct
		cranePLCStatusBase.setRotateAngleAct( sd["ROTATE_ANGLE_ACT"].toInt() );
		log.Debug()<<"20......";

		//21	emgStop
		cranePLCStatusBase.setEmgStop( sd["EMG_STOP"].toInt() );
		log.Debug()<<"21......";

		//22	orderID

		//2017.9.18 zhangyuhong �޸�
		cranePLCStatusBase.setOrderID( sd["ORDER_ID"].toInt() );
		log.Debug()<<"22......";
		
		//�������������ģ��г�״̬���ı��������������
		//�����һ���Ƿ��Զ����������Զ������6�����ݷ�9
		if (cranePLCStatus_Last.getControlMode() != CranePLCStatusBase::CONTROL_MODE_AUTO && 
			cranePLCStatusBase.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			cranePLCStatusBase.setPlanUpX(DB_INT_NULL);
			log.Debug()<<"23......���Զ����Զ�����9";
			cranePLCStatusBase.setPlanUpY(DB_INT_NULL);
			log.Debug()<<"24......���Զ����Զ�����9";
			cranePLCStatusBase.setPlanUpZ(DB_INT_NULL);
			log.Debug()<<"25......���Զ����Զ�����9";

			log.Debug()<<"26......���Զ����Զ�����9";
			cranePLCStatusBase.setPlanDownX(DB_INT_NULL);
			log.Debug()<<"27......���Զ����Զ�����9";
			cranePLCStatusBase.setPlanDownY(DB_INT_NULL);
			log.Debug()<<"28......���Զ����Զ�����9";
			cranePLCStatusBase.setPlanDownZ(DB_INT_NULL);
		}
		else
		{
			//23	planUpX
			cranePLCStatusBase.setPlanUpX( sd["PLAN_UP_X"].toInt() );
			log.Debug()<<"23......";

			//24	planUpY
			cranePLCStatusBase.setPlanUpY( sd["PLAN_UP_Y"].toInt() );
			log.Debug()<<"24......";

			//25	planUpZ
			cranePLCStatusBase.setPlanUpZ( sd["PLAN_UP_Z"].toInt() );
			log.Debug()<<"25......";

			//26	planDownX
			cranePLCStatusBase.setPlanDownX( sd["PLAN_DOWN_X"].toInt() );
			log.Debug()<<"26.....";

			//27	planDownY
			cranePLCStatusBase.setPlanDownY( sd["PLAN_DOWN_Y"].toInt() );
			log.Debug()<<"27......";

			//28	planDownZ
			cranePLCStatusBase.setPlanDownZ( sd["PLAN_DOWN_Z"].toInt() );
			log.Debug()<<"28......";				
		}	

		//29	craneStatus
		cranePLCStatusBase.setCraneStatus( sd["CRANE_STATUS"].toInt() );
		log.Debug()<<"29......";

		//30 �г�����
		cranePLCStatusBase.setCraneAlarm(sd["CRANE_ALARM"].toInt());
		log.Debug()<<"30......"<<endl;

		//31 timeReceive
		cranePLCStatusBase.setTimeReceive( iDA::DateTime::Now().ToShortTimeString() );

		cranePLCStatusBase.logOutValues();

		log.Debug()<<" now try to input the PLC Status to Crane Monitor Class................................................"<<endl;
		CraneMonitor::getInstance()->inputPLCStatus( cranePLCStatusBase );

		log.Debug()<<" ׼����PLC Status д��UACS   tagϵͳ................................................"<<endl;		
		cranePLCStatusBase.wirteValues2TagSystem();

		
		
		//����Storm�������Ϣ������������
		log.Debug()<<" now try to dispatch the topic name="<<cranePLCStatusTopicName<<"................................................"<<endl;
		CLTS::CranePLCStatusDesc desc=CranePLCStatusBase::TransFromClass(cranePLCStatusBase);	

		CLTS::CranePublisherPrx cranePublisher;
		cranePublisher = getPublishProxy<CLTS::CranePublisherPrx>(cranePLCStatusTopicName); 
		cranePublisher->CWatchEventHandlerI(desc);

		//2018.6.30 zhangyuhong add
		//׼���ѵ�ش���д���ش�����ʷ��¼����
		//���ظ�д��ֻд����һ���յ��ı������벻ͬ �� ��ָ��Ų�ͬ�ı�������
		//ֻ���г�ʱ�Զ�ģʽ��д�뱨��������ģʽ��д����
		if ( cranePLCStatusBase.getOrderID() != vecOrderIDAlarmCodeLast[0] || cranePLCStatusBase.getCraneAlarm() != vecOrderIDAlarmCodeLast[1] ) 
		{			
			if (cranePLCStatusBase.getCraneAlarm() != 0 && cranePLCStatusBase.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO)
			{
				//��д���ش�����ʷ��¼�����
				if (true == Adapter_UACS_CRANE_MOVEORDER_MSG::insertCraneAlarmMsg(cranePLCStatusBase.getCraneNO(), 
																																							cranePLCStatusBase.getOrderID(), 
																																							cranePLCStatusBase.getCraneAlarm()))
				{
					log.Debug()<<"���յ����г���������д�����ݱ�ɹ���"<<endl;
				}
			}
			//�����ν��յ���OrderID��CraneAlarmд�� vecOrderIDAlarmCode
			vecOrderIDAlarmCodeLast.clear();
			vecOrderIDAlarmCodeLast.push_back(cranePLCStatusBase.getOrderID());
			vecOrderIDAlarmCodeLast.push_back(cranePLCStatusBase.getCraneAlarm());
		}

		//�µĸ����ɡ����¾ɵ�
		cranePLCStatus_Last = cranePLCStatusBase;

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
