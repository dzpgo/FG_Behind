/*********************************************************************
 *		
 *  ��      ��:    CranePLCStatusBase.h   		
 *
 *
 *  ������
 *        ��CranePLCStatusBase �ǵ�����
 *        �������г�PLC������������״̬������Ϣ
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/
#pragma once
#ifndef _CranePLCStatusBase_
#define _CranePLCStatusBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

//#include <Slice/CranePLCStatusStorm.h>
#include "CranePLCStatusStorm.h"

namespace Monitor
{



		class CranePLCStatusBase
		{


		public:
				CranePLCStatusBase(void);

				~CranePLCStatusBase(void);

		private:
			    void initValues();
	
		//1 CRANE_NO 
		private:
			string craneNO;
		public:
			string getCraneNO();
			void   setCraneNO(string theVal);

		//2 CONTROL_MODE
		private:
			long controlMode;
		public:
			long getControlMode();
			void   setControlMode(long theVal);

		//3 READY
		private:
			long ready;
		public:
			long getReady();
			void setReady(long theVal);

		//4 EMG_STOP
		private:
			long emgStop;
		public:
			long getEmgStop();
			void setEmgStop(long theVal);

		//5 ASK_PLAN
		private:
			long askPlan;
		public:
			long getAskPlan();
			void setAskPlan(long theVal);

		//6 TASK_EXCUTING
		private:
			long taskExcuting;
		public:
			long getTaskExcuting();
			void setTaskExcuting(long theVal);

		//7 XDIR_P;
		private:
			long xDirectPositive;
		public:
			long getXDirectPositive();
			void setXDirectPositive(long theVal);

		//8 XDIR_N
		private:
			long xDirectNegative;
		public:
			long getXDirectNegative();
			void setXDirectNegative(long theVal);

		//9 YDIR_P
		private:
			long yDirectPositive;
		public:
			long getYDirectPositive();
			void setYDirectPositive(long theVal);

		//10 YDIR_N
		private:
			long yDirectNegative;
		public:
			long getYDirectNegative();
			void setYDirectNegative(long theVal);


		//11 ZDIR_P
		private:
			long zDirectPositive;
		public:
			long getZDirectPositive();
			void setZDirectPositive(long theVal);

		//12 ZDIR_N
		private:
			long zDirectNegative;
		public:
			long getZDirectNegative();
			void setZDirectNegative(long theVal);

		//13 HAS_COIL
		private:
			long hasCoil;
		public:
			long getHasCoil();
			void setHasCoil(long theVal);

		//14 ORDER_ID
		private:
			long orderID;
		public:
			long getOrderID();
			void setOrderID(long theVal);

		//15 RunStep
		private:
			long runStep;
		public:
			long getRunStep();
			void setRunStep(long theVal);

		//16 XSPEED
		private:
			long xSpeed;
		public:
			long getXSpeed();
			void setXSpeed(long theVal);

		//17 YSPEED
		private:
			long ySpeed;
		public:
			long getYSpeed();
			void setYSpeed(long theVal);

		//18 ZSPEED
		private:
			long zSpeed;
		public:
			long getZSpeed();
			void setZSpeed(long theVal);

		//19 XACT
		private:
			long xAct;
		public:
			long getXAct();
			void setXAct(long theVal);

		//20 YACT
		private:
			long yAct;
		public:
			long getYAct();
			void setYAct(long theVal);

		//21 ZACT
		private:
			long zAct;
		public:
			long getZAct();
			void setZAct(long theVal);

		//22 WEIGHT_LOADED
		private:
			long weightLoaded;
		public:
			long getWeightLoaded();
			void setWeightLoaded(long theVal);

		//23 DIP_ANGLE_ACT
		private:
			long dipAngleAct;
		public:
			long getDipAngleAct();
			void setDipAngleAct(long theVal);

		//24 CurrTarg_X
		private:
			long currTargX;
		public:
			long getCurrTargX();
			void setCurrTargX(long theVal);
		
		//25 CurrTarg_Y
		private:
			long currTargY;
		public:
			long getCurrTargY();
			void setCurrTargY(long theVal);

		//26 CurrTarg_Z
		private:
			long currTargZ;
		public:
			long getCurrTargZ();
			void setCurrTargZ(long theVal);

		//27 PLAN_UP_X
		private:
			long planUpX;
		public:
			long getPlanUpX();
			void setPlanUpX(long theVal);

		//28 PLAN_UP_Y
		private:
			long planUpY;
		public:
			long getPlanUpY();
			void setPlanUpY(long theVal);


		//29 PLAN_UP_Z
		private:
			long planUpZ;
		public:
			long getPlanUpZ();
			void setPlanUpZ(long theVal);

		//30 PLAN_DOWN_X
		private:
			long planDownX;
		public:
			long getPlanDownX();
			void setPlanDownX(long theVal);

		//31 PLAN_DOWN_Y
		private:
			long planDownY;
		public:
			long getPlanDownY();
			void setPlanDownY(long theVal);

		//32 PLAN_DOWN_Z
		private:
			long planDownZ;
		public:
			long getPlanDownZ();
			void setPlanDownZ(long theVal);

		//33 FaultCode_0
		private:
			long faultCode0;
		public:
			long getFaultCode0();
			void setFaultCode0(long theVal);

		//34 FaultCode_1
		private:
			long faultCode1;
		public:
			long getFaultCode1();
			void setFaultCode1(long theVal);

		//35 FaultCode_2
		private:
			long faultCode2;
		public:
			long getFaultCode2();
			void setFaultCode2(long theVal);

		//36 FaultCode_3
		private:
			long faultCode3;
		public:
			long getFaultCode3();
			void setFaultCode3(long theVal);

		//37 FaultCode_4
		private:
			long faultCode4;
		public:
			long getFaultCode4();
			void setFaultCode4(long theVal);

		//38 FaultCode_5
		private:
			long faultCode5;
		public:
			long getFaultCode5();
			void setFaultCode5(long theVal);

		//39 FaultCode_6
		private:
			long faultCode6;
		public:
			long getFaultCode6();
			void setFaultCode6(long theVal);

		//40 FaultCode_7
		private:
			long faultCode7;
		public:
			long getFaultCode7();
			void setFaultCode7(long theVal);

		//41 FaultCode_8
		private:
			long faultCode8;
		public:
			long getFaultCode8();
			void setFaultCode8(long theVal);

		//42 FaultCode_9
		private:
			long faultCode9;
		public:
			long getFaultCode9();
			void setFaultCode9(long theVal);

		//43 Heart
		private:
			long heart;
		public:
			long getHeart();
			void setHeart(long theVal);

		//44 timeReceive
		private:
			string timeReceive;
		public:
			string getTimeReceive();
			void setTimeReceive(string theVal);
	
		public:
			void  logOutValues();

		public:
			void wirteValues2TagSystem(TAGVALUEMAP& Tags);


		//2018.12.22 zhangyuhong add
		//���յ��г�״̬�����У�״̬�Ƿ��Զ��ģ����9
		public:
			void setPlanUpDownXYZIs9();

		public:
			static CLTS::CranePLCStatusDesc TransFromClass(CranePLCStatusBase cranePLCStatusBase);

			static CranePLCStatusBase  TransFromStruct(CLTS::CranePLCStatusDesc desc);
		public:
			//--------------------------------------------------�г��豸״̬����----------------------------------------------------------------
			 //�չ���������= 000;
			 const static  long STATUS_NEED_TO_READY;
			 //�չ��ȴ�״̬= 010
			 const static  long STATUS_WAITING_ORDER_WITH_OUT_COIL;
			 //�չ�����״̬= 020
			 const static  long STATUS_MOVING_WITH_OUT_COIL;
			 //�չ����е�λ״̬= 030
			 const static  long STATUS_ARRIVED_POS_WITH_OUT_COIL;
			 //�չ��½�ȥȡ��= 040
			 const static  long STATUS_LIFT_COIL_DOWN_PHASE;
			 //�־����= 050
			 const static  long STATUS_COIL_LIFTED;
			 //�ع���������= 060
			 const static  long STATUS_LIFT_COIL_UP_PHASE;
			 //�ع��ȴ�״̬= 070
			 const static  long STATUS_WAITING_ORDER_WITH_COIL;
			 //�ع�����״̬= 080
			 const static  long STATUS_MOVING_WITH_COIL;
			 //�ع����е�λ= 090
			 const static  long STATUS_ARRIVED_POS_WITH_COIL;
			 //�ع��½�ȥ���= 100
			 const static  long STATUS_DOWN_COIL_DOWN_PHASE;
			 //�־����= 110
			 const static  long STATUS_COIL_DOWN;
			 //---------------------------------------------------------------------------------------------------------------------------------------------------

			 //--------------------------------------------------�г�����ģʽ����----------------------------------------------------------------
			 //ң��ģʽ
			 const static long CONTROL_MODE_REMOTE_CONTROL;
			 //˾��ģʽ
			 const static long CONTROL_MODE_DRIVER_CONTROL;
			 //���Զ�ģʽ
			 const static long CONTROL_MODE_HALF_AUTO;
			 //����ģʽ
			 const static long CONTROL_MODE_CHECK_REPAIR;
			 //ȫ�Զ�ģʽ
			 const static long CONTROL_MODE_AUTO;


			//--------------------------------------------------�г�״̬�źŶ�Ӧ��ϵͳ�ڲ�tag�㶨��-------------------------------------
			//--------------------------------------------------ϵͳ�ڲ�tag����Ҫ��������ʹ�ã��г���̨����ʹ��------------
			  //2����ģʽ
			 const static string ADRESS_CONTROL_MODE;
			 //3׼����
			 const static string ADRESS_READY;
			 //4��ͣ״̬
			 const static string ADRESS_EMG_STOP;
			 //5����ƻ�
			 const static string ADRESS_ASK_PLAN;
			 //6����ִ����
			 const static string ADRESS_TASK_EXCUTING;
			 //7��������<--------------------------------------------new tag
			 const static string ADRESS_XDIR_P;
			 //8�󳵸�����<--------------------------------------------new tag
			 const static string ADRESS_XDIR_N;
			 //9С��������<--------------------------------------------new tag
			 const static string ADRESS_YDIR_P;
			 //10С��������<--------------------------------------------new tag
			 const static string ADRESS_YDIR_N;
			 //11����������<--------------------------------------------new tag
			 const static string ADRESS_ZDIR_P;
			 //12����������<--------------------------------------------new tag
			 const static string ADRESS_ZDIR_N;
			 //13�о��־
			 const static string ADRESS_HAS_COIL;
			 //14��ǰָ���
			 const static string ADRESS_ORDER_ID;
			 //15�г����в���
			 const static string ADRESS_RunStep;
			 //16�󳵷���ʵ���ٶ�<--------------------------------------------new tag
			 const static string ADRESS_XSPEED;
			 //17С������ʵ���ٶ�<--------------------------------------------new tag
			 const static string ADRESS_YSPEED;
			 //18����ʵ���ٶ�<--------------------------------------------new tag
			 const static string ADRESS_ZSPEED;
			 //19��λ��
			 const static string ADRESS_XACT;
			 //20С��λ��
			 const static string ADRESS_YACT;
			 //21���̸߶�
			 const static string ADRESS_ZACT;
			 //22�����ź�<--------------------------------------------new tag
			 const static string ADRESS_WEIGHT_LOADED;
			 //23��б�Ƕ�<--------------------------------------------new tag
			 const static string ADRESS_DIP_ANGLE_ACT;
			 //24X�ᵱǰĿ��λ
			 const static string ADRESS_CurrTarg_X;
			 //25Y�ᵱǰĿ��λ
			 const static string ADRESS_CurrTarg_Y;
			 //26Z�ᵱǰĿ��λ
			 const static string ADRESS_CurrTarg_Z;
			 //27�ƻ����X
			 const static string ADRESS_PLAN_UP_X;
			 //28�ƻ����Y
			 const static string ADRESS_PLAN_UP_Y;
			 //29�ƻ����Z
			 const static string ADRESS_PLAN_UP_Z;
			 //30�ƻ����X
			 const static string ADRESS_PLAN_DOWN_X;
			 //31�ƻ����Y
			 const static string ADRESS_PLAN_DOWN_Y;
			 //32�ƻ����Z
			 const static string ADRESS_PLAN_DOWN_Z;
			 //33���ϴ���0
			 const static string ADRESS_FaultCode_0;
			 //34���ϴ���1
			 const static string ADRESS_FaultCode_1;
			 //35���ϴ���2
			 const static string ADRESS_FaultCode_2;
			 //36���ϴ���3
			 const static string ADRESS_FaultCode_3;
			 //37���ϴ���4
			 const static string ADRESS_FaultCode_4;
			 //38���ϴ���5
			 const static string ADRESS_FaultCode_5;
			 //39���ϴ���6
			 const static string ADRESS_FaultCode_6;
			 //40���ϴ���7
			 const static string ADRESS_FaultCode_7;
			 //41���ϴ���8
			 const static string ADRESS_FaultCode_8;
			 //42���ϴ���9
			 const static string ADRESS_FaultCode_9;
			 //43����
			 const static string ADRESS_Heart;
			 

			 //44timeReceive
			 //const static string ADRESS_CRANE_PLC_HEART_BEAT;
		

			 //---------------------------------------------------------------------------------------------------------------------------------------------------

		};




}
#endif