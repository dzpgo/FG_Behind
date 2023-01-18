/*********************************************************************
 *		
 *  文      件:    CranePLCStatusBase.h   		
 *
 *
 *  概述：
 *        ：CranePLCStatusBase 非单例类
 *        ：储存行车PLC送来的完整的状态数据信息
 *  版本历史		
 *      2017年04月建立
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
		//当收到行车状态电文中，状态是非自动的，则封9
		public:
			void setPlanUpDownXYZIs9();

		public:
			static CLTS::CranePLCStatusDesc TransFromClass(CranePLCStatusBase cranePLCStatusBase);

			static CranePLCStatusBase  TransFromStruct(CLTS::CranePLCStatusDesc desc);
		public:
			//--------------------------------------------------行车设备状态定义----------------------------------------------------------------
			 //空钩起升过程= 000;
			 const static  long STATUS_NEED_TO_READY;
			 //空钩等待状态= 010
			 const static  long STATUS_WAITING_ORDER_WITH_OUT_COIL;
			 //空钩走行状态= 020
			 const static  long STATUS_MOVING_WITH_OUT_COIL;
			 //空钩走行到位状态= 030
			 const static  long STATUS_ARRIVED_POS_WITH_OUT_COIL;
			 //空钩下降去取卷= 040
			 const static  long STATUS_LIFT_COIL_DOWN_PHASE;
			 //钢卷起吊= 050
			 const static  long STATUS_COIL_LIFTED;
			 //重钩起升过程= 060
			 const static  long STATUS_LIFT_COIL_UP_PHASE;
			 //重钩等待状态= 070
			 const static  long STATUS_WAITING_ORDER_WITH_COIL;
			 //重钩走行状态= 080
			 const static  long STATUS_MOVING_WITH_COIL;
			 //重钩走行到位= 090
			 const static  long STATUS_ARRIVED_POS_WITH_COIL;
			 //重钩下降去落卷= 100
			 const static  long STATUS_DOWN_COIL_DOWN_PHASE;
			 //钢卷落关= 110
			 const static  long STATUS_COIL_DOWN;
			 //---------------------------------------------------------------------------------------------------------------------------------------------------

			 //--------------------------------------------------行车控制模式定义----------------------------------------------------------------
			 //遥控模式
			 const static long CONTROL_MODE_REMOTE_CONTROL;
			 //司机模式
			 const static long CONTROL_MODE_DRIVER_CONTROL;
			 //半自动模式
			 const static long CONTROL_MODE_HALF_AUTO;
			 //检修模式
			 const static long CONTROL_MODE_CHECK_REPAIR;
			 //全自动模式
			 const static long CONTROL_MODE_AUTO;


			//--------------------------------------------------行车状态信号对应的系统内部tag点定义-------------------------------------
			//--------------------------------------------------系统内部tag点主要供给画面使用，行车后台程序不使用------------
			 //2准备好
			 const static string ADRESS_READY;
			 //3控制模式
			 const static string  ADRESS_CONTROL_MODE;
			 //4请求计划
			 const static string ADRESS_ASK_PLAN;
			 //5任务执行中
			 const static string ADRESS_TASK_EXCUTING;
			 //6大车位置
			 const static string ADRESS_XACT;
			 //7小车位置
			 const static string ADRESS_YACT;
			 //8夹钳高度
			 const static string ADRESS_ZACT;
			 //9大车方向实际速度
			 const static string ADRESS_XSPEED;
			 //10小车方向实际速度
			 const static string ADRESS_YSPEED;
			 //11升降实际速度
			 const static string ADRESS_ZSPEED;
			 //12大车正方向
			 const static string ADRESS_XDIR_P;
			 //13大车负方向
			 const static string ADRESS_XDIR_N;
			 //14小车正方向
			 const static string ADRESS_YDIR_P;
			 //15小车负方向
			 const static string ADRESS_YDIR_N;
			 //16升降正方向
			 const static string ADRESS_ZDIR_P;
			 //17升降负方向
			 const static string ADRESS_ZDIR_N;
			 //18有卷标志
			 const static string ADRESS_HAS_COIL;
			 //19称重信号
			 const static string ADRESS_WEIGHT_LOADED;
			 //20夹钳旋转角度
			 const static string ADRESS_ROTATE_ANGLE_ACT;
			 //21夹钳开度
			 const static string ADRESS_CLAMP_WIDTH_ACT;
			 //22急停状态
			 const static string ADRESS_EMG_STOP;
			 //23当前指令号
			 const static string ADRESS_ORDER_ID;
			 //24计划起卷X
			 const static string ADRESS_PLAN_UP_X;
			 //25计划起卷Y
			 const static string ADRESS_PLAN_UP_Y;
			 //26计划起卷Z
			 const static string ADRESS_PLAN_UP_Z;
			 //27计划落卷X
			 const static string ADRESS_PLAN_DOWN_X;
			 //28计划落卷Y
			 const static string ADRESS_PLAN_DOWN_Y;
			 //29计划落卷Z
			 const static string ADRESS_PLAN_DOWN_Z;
			 //30行车状态
			 const static string ADRESS_CRANE_STATUS;
			
			//31 大车激光反光板测距
			 const static string ADRESS_LASER_DISTANCE;

			 //32 行车报警代码
			 const static string ADRESS_CRANE_ALARM;

			 //33 空调水放水代码
			 const static string ADRESS_AC_WATER_CODE;

			 //31timeReceive
			 const static string ADRESS_CRANE_PLC_HEART_BEAT;
		

			 //---------------------------------------------------------------------------------------------------------------------------------------------------

		};




}
#endif