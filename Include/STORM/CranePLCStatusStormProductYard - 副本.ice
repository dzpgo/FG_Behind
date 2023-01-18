#ifndef CRANE_PLC_STATUS_STORM_PRODUCT_YARD_H
#define CRANE_PLC_STATUS_STORM_PRODUCT_YARD_H

#include <Ice/BuiltinSequences.ice>

module CLTS
{
	/** 行车状态信息
	 *
	 */
	struct CranePLCStatusDescProductYard
	{
		//1 CRANE_NO 
		string craneNO;

		//2 CONTROL_MODE	
		long controlMode;		
		
		//3 READY
		long ready;

		//4 EMG_STOP
		long emgStop;
		
		//5 ASK_PLAN
		long askPlan;
		
		//6 TASK_EXCUTING
		long taskExcuting;
		
		//7 XDIR_P;
		long xDirectPositive;
		
		//8 XDIR_N
		long xDirectNegative;
		
		//9 YDIR_P
		long yDirectPositive;
		
		//10 YDIR_N
		long yDirectNegative;
		
		//11 ZDIR_P
		long zDirectPositive;
		
		//12 ZDIR_N
		long zDirectNegative;

		//13 HAS_COIL
		long hasCoil;

		//14 ORDER_ID
		long orderID;

		//15 RunStep
		long RunStep;

		//16 XSPEED
		long xSpeed;
		
		//17 YSPEED
		long ySpeed;
		
		//18 ZSPEED
		long zSpeed;

		//19 XACT
		long xAct;
		
		//20 YACT
		long yAct;
		
		//21 ZACT
		long zAct;

		//22 WEIGHT_LOADED
		long weightLoaded;
		
		//23 DIP_ANGLE_ACT
		long dipAngleAct;
		
		//24 CurrTarg_X
		long CurrTargX;
		
		//25 CurrTarg_Y
		long CurrTargY;
		
		//26 CurrTarg_Z
		long CurrTargZ;	
	
		//27 PLAN_UP_X
		long planUpX;
		
		//28 PLAN_UP_Y
		long planUpY;
		
		//29 PLAN_UP_Z
		long planUpZ;
		
		//30 PLAN_DOWN_X
		long planDownX;
		
		//31 PLAN_DOWN_Y
		long planDownY;
		
		//32 PLAN_DOWN_Z
		long planDownZ;
		
		//33 FaultCode_0
		long FaultCode0;
		
		//34 FaultCode_1
		long FaultCode1;

		//35 FaultCode_2
		long FaultCode2;

		//36 FaultCode_3
		long FaultCode3;

		//37 FaultCode_4
		long FaultCode4;

		//38 FaultCode_5
		long FaultCode5;

		//39 FaultCode_6
		long FaultCode6;

		//40 FaultCode_7
		long FaultCode7;

		//41 FaultCode_8
		long FaultCode8;

		//42 FaultCode_9
		long FaultCode9;

		//43 Heart
		long Heart;

	};
	
	/**  行车发布接口
	 *
	 */	
	interface CranePublisherProductYard
	{
		/** 广播行车状态.
		 *  函数名： stormCrane 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    desc : CraneStatusDesc								卸下库位
		 */
		void CWatchEventHandlerI(CranePLCStatusDescProductYard desc);
	};
};

#endif
