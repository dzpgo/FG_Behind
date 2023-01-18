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

		//2 READY
		private:
			long ready;
		public:
			long getReady();
			void setReady(long theVal);

		//3 CONTROL_MODE
		private:
			long controlMode;
		public:
			long getControlMode();
			void   setControlMode(long theVal);


		//4 ASK_PLAN
		private:
			long askPlan;
		public:
			long getAskPlan();
			void setAskPlan(long theVal);

		//5 TASK_EXCUTING
		private:
			long taskExcuting;
		public:
			long getTaskExcuting();
			void setTaskExcuting(long theVal);

		//6 XACT
		private:
			long xAct;
		public:
			long getXAct();
			void setXAct(long theVal);

		//7 YACT
		private:
			long yAct;
		public:
			long getYAct();
			void setYAct(long theVal);

		//8 ZACT
		private:
			long zAct;
		public:
			long getZAct();
			void setZAct(long theVal);

		//9 XSPEED
		private:
			long xSpeed;
		public:
			long getXSpeed();
			void setXSpeed(long theVal);

		//10 YSPEED
		private:
			long ySpeed;
		public:
			long getYSpeed();
			void setYSpeed(long theVal);

		//11 ZSPEED
		private:
			long zSpeed;
		public:
			long getZSpeed();
			void setZSpeed(long theVal);

		//12 XDIR_P;
		private:
			long xDirectPositive;
		public:
			long getXDirectPositive();
			void setXDirectPositive(long theVal);

		//13 XDIR_N
		private:
			long xDirectNegative;
		public:
			long getXDirectNegative();
			void setXDirectNegative(long theVal);

		//14 YDIR_P
		private:
			long yDirectPositive;
		public:
			long getYDirectPositive();
			void setYDirectPositive(long theVal);

		//15 YDIR_N
		private:
			long yDirectNegative;
		public:
			long getYDirectNegative();
			void setYDirectNegative(long theVal);


		//16 ZDIR_P
		private:
			long zDirectPositive;
		public:
			long getZDirectPositive();
			void setZDirectPositive(long theVal);

		//17 ZDIR_N
		private:
			long zDirectNegative;
		public:
			long getZDirectNegative();
			void setZDirectNegative(long theVal);

		//18 HAS_COIL
		private:
			long hasCoil;
		public:
			long getHasCoil();
			void setHasCoil(long theVal);

		//19 WEIGHT_LOADED
		private:
			long weightLoaded;
		public:
			long getWeightLoaded();
			void setWeightLoaded(long theVal);

		//20 ROTATE_ANGLE_ACT
		private:
			long rotateAngleAct;
		public:
			long getRotateAngleAct();
			void setRotateAngleAct(long theVal);

		//21 EMG_STOP
		private:
			long emgStop;
		public:
			long getEmgStop();
			void setEmgStop(long theVal);

		//22 ORDER_ID
		private:
			long orderID;
		public:
			long getOrderID();
			void setOrderID(long theVal);

		//23 PLAN_UP_X
		private:
			long planUpX;
		public:
			long getPlanUpX();
			void setPlanUpX(long theVal);

		//24 PLAN_UP_Y
		private:
			long planUpY;
		public:
			long getPlanUpY();
			void setPlanUpY(long theVal);


		//25 PLAN_UP_Z
		private:
			long planUpZ;
		public:
			long getPlanUpZ();
			void setPlanUpZ(long theVal);

		//26 PLAN_DOWN_X
		private:
			long planDownX;
		public:
			long getPlanDownX();
			void setPlanDownX(long theVal);

		//27 PLAN_DOWN_Y
		private:
			long planDownY;
		public:
			long getPlanDownY();
			void setPlanDownY(long theVal);

		//28 PLAN_DOWN_Z
		private:
			long planDownZ;
		public:
			long getPlanDownZ();
			void setPlanDownZ(long theVal);

		//29 CRANE_STATUS
		private:
			long craneStatus;
		public:
			long getCraneStatus();
			void setCraneStatus(long theVal);
	
		//30 CRANE_ALARM
		private:
			long craneAlarm;
		public:
			long getCraneAlarm();
			void setCraneAlarm(long theVal);

		//31 timeReceive
		private:
			string timeReceive;
		public:
			string getTimeReceive();
			void setTimeReceive(string theVal);
	
		public:
			void  logOutValues();

		public:
			void wirteValues2TagSystem();


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
			 //2׼����
			 const static string ADRESS_READY;
			 //3����ģʽ
			 const static string  ADRESS_CONTROL_MODE;
			 //4����ƻ�
			 const static string ADRESS_ASK_PLAN;
			 //5����ִ����
			 const static string ADRESS_TASK_EXCUTING;
			 //6��λ��
			 const static string ADRESS_XACT;
			 //7С��λ��
			 const static string ADRESS_YACT;
			 //8��ǯ�߶�
			 const static string ADRESS_ZACT;
			 //9�󳵷���ʵ���ٶ�
			 const static string ADRESS_XSPEED;
			 //10С������ʵ���ٶ�
			 const static string ADRESS_YSPEED;
			 //11����ʵ���ٶ�
			 const static string ADRESS_ZSPEED;
			 //12��������
			 const static string ADRESS_XDIR_P;
			 //13�󳵸�����
			 const static string ADRESS_XDIR_N;
			 //14С��������
			 const static string ADRESS_YDIR_P;
			 //15С��������
			 const static string ADRESS_YDIR_N;
			 //16����������
			 const static string ADRESS_ZDIR_P;
			 //17����������
			 const static string ADRESS_ZDIR_N;
			 //18�о��־
			 const static string ADRESS_HAS_COIL;
			 //19�����ź�
			 const static string ADRESS_WEIGHT_LOADED;
			 //20��ǯ��ת�Ƕ�
			 const static string ADRESS_ROTATE_ANGLE_ACT;
			 //21��ǯ����
			 const static string ADRESS_CLAMP_WIDTH_ACT;
			 //22��ͣ״̬
			 const static string ADRESS_EMG_STOP;
			 //23��ǰָ���
			 const static string ADRESS_ORDER_ID;
			 //24�ƻ����X
			 const static string ADRESS_PLAN_UP_X;
			 //25�ƻ����Y
			 const static string ADRESS_PLAN_UP_Y;
			 //26�ƻ����Z
			 const static string ADRESS_PLAN_UP_Z;
			 //27�ƻ����X
			 const static string ADRESS_PLAN_DOWN_X;
			 //28�ƻ����Y
			 const static string ADRESS_PLAN_DOWN_Y;
			 //29�ƻ����Z
			 const static string ADRESS_PLAN_DOWN_Z;
			 //30�г�״̬
			 const static string ADRESS_CRANE_STATUS;
			
			//31 �󳵼��ⷴ�����
			 const static string ADRESS_LASER_DISTANCE;

			 //32 �г���������
			 const static string ADRESS_CRANE_ALARM;

			 //33 �յ�ˮ��ˮ����
			 const static string ADRESS_AC_WATER_CODE;

			 //31timeReceive
			 const static string ADRESS_CRANE_PLC_HEART_BEAT;
		

			 //---------------------------------------------------------------------------------------------------------------------------------------------------

		};




}
#endif