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
			  //2控制模式
			 const static string ADRESS_CONTROL_MODE;
			 //3准备好
			 const static string ADRESS_READY;
			 //4急停状态
			 const static string ADRESS_EMG_STOP;
			 //5请求计划
			 const static string ADRESS_ASK_PLAN;
			 //6任务执行中
			 const static string ADRESS_TASK_EXCUTING;
			 //7大车正方向<--------------------------------------------new tag
			 const static string ADRESS_XDIR_P;
			 //8大车负方向<--------------------------------------------new tag
			 const static string ADRESS_XDIR_N;
			 //9小车正方向<--------------------------------------------new tag
			 const static string ADRESS_YDIR_P;
			 //10小车负方向<--------------------------------------------new tag
			 const static string ADRESS_YDIR_N;
			 //11升降正方向<--------------------------------------------new tag
			 const static string ADRESS_ZDIR_P;
			 //12升降负方向<--------------------------------------------new tag
			 const static string ADRESS_ZDIR_N;
			 //13有卷标志
			 const static string ADRESS_HAS_COIL;
			 //14当前指令号
			 const static string ADRESS_ORDER_ID;
			 //15行车运行步骤
			 const static string ADRESS_RunStep;
			 //16大车方向实际速度<--------------------------------------------new tag
			 const static string ADRESS_XSPEED;
			 //17小车方向实际速度<--------------------------------------------new tag
			 const static string ADRESS_YSPEED;
			 //18升降实际速度<--------------------------------------------new tag
			 const static string ADRESS_ZSPEED;
			 //19大车位置
			 const static string ADRESS_XACT;
			 //20小车位置
			 const static string ADRESS_YACT;
			 //21吸盘高度
			 const static string ADRESS_ZACT;
			 //22称重信号<--------------------------------------------new tag
			 const static string ADRESS_WEIGHT_LOADED;
			 //23倾斜角度<--------------------------------------------new tag
			 const static string ADRESS_DIP_ANGLE_ACT;
			 //24X轴当前目标位
			 const static string ADRESS_CurrTarg_X;
			 //25Y轴当前目标位
			 const static string ADRESS_CurrTarg_Y;
			 //26Z轴当前目标位
			 const static string ADRESS_CurrTarg_Z;
			 //27计划起卷X
			 const static string ADRESS_PLAN_UP_X;
			 //28计划起卷Y
			 const static string ADRESS_PLAN_UP_Y;
			 //29计划起卷Z
			 const static string ADRESS_PLAN_UP_Z;
			 //30计划落卷X
			 const static string ADRESS_PLAN_DOWN_X;
			 //31计划落卷Y
			 const static string ADRESS_PLAN_DOWN_Y;
			 //32计划落卷Z
			 const static string ADRESS_PLAN_DOWN_Z;
			 //33故障代码0
			 const static string ADRESS_FaultCode_0;
			 //34故障代码1
			 const static string ADRESS_FaultCode_1;
			 //35故障代码2
			 const static string ADRESS_FaultCode_2;
			 //36故障代码3
			 const static string ADRESS_FaultCode_3;
			 //37故障代码4
			 const static string ADRESS_FaultCode_4;
			 //38故障代码5
			 const static string ADRESS_FaultCode_5;
			 //39故障代码6
			 const static string ADRESS_FaultCode_6;
			 //40故障代码7
			 const static string ADRESS_FaultCode_7;
			 //41故障代码8
			 const static string ADRESS_FaultCode_8;
			 //42故障代码9
			 const static string ADRESS_FaultCode_9;
			 //43心跳
			 const static string ADRESS_Heart;
			 

			 //44timeReceive
			 //const static string ADRESS_CRANE_PLC_HEART_BEAT;
		

			 //---------------------------------------------------------------------------------------------------------------------------------------------------

		};




}
#endif