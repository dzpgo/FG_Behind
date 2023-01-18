/*********************************************************************
*		
*  文      件:    CraneOrderCurrentBase.h   		
*
*
*  概述：
*        ：CraneUACSOrderBase 非单例类
*        ：存储行车自动的行车指令状态表内的信息，这张表用行车号做键字，每个行车一条
*  版本历史		
*      2017年04月建立
*********************************************************************/
#pragma once
#ifndef _CraneOrderCurrentBase_
#define _CraneOrderCurrentBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{
	class CraneOrderCurrentBase
	{

	public:
		CraneOrderCurrentBase(void);

		~CraneOrderCurrentBase(void);

	private:
		void initValues();

		//1 ORDER_NO 
	private:
		long orderNO;
	public:
		long getOrderNO();
		void   setOrderNO(long theVal);

		//2 BAY_NO
	private:
		string bayNO;
	public:
		string getBayNO();
		void setBayNO(string theVal);

		//3 MAT_NO
	private:
		string matNO;
	public:
		string getMatNO();
		void setMatNO(string theVal);

		//4 ORDER_TYPE
	private:
		string orderType;
	public:
		string getOrderType();
		void setOrderType(string theVal);

		//5 ORDER_PRIORITY
	private:
		long orderPriority;
	public:
		long getOrderPriority();
		void setOrderPriority(long theVal);

		//6 FROM_STOCK_NO
	private:
		string fromStockNO;
	public:
		string getFromStockNO();
		void setFromStockNO(string theVal);

		//6.5 FROM_STOCK_TYPE
	private:
		string fromStockType;
	public:
		string getFromStockType();
		void setFromStockType(string theVal);

		//7 TO_STOCK_NO
	private:
		string toStockNO;
	public:
		string getToStockNO();
		void setToStockNO(string theVal);

		//7.5 TO_STOCK_TYPE
	private:
		string toStockType;
	public:
		string getToStockType();
		void setToStockType(string theVal);

		//8 CMD_STATUS
	private:
		string cmdStatus;
	public:
		string getCMDStatus();
		void setCMDStatus(string theVal);

		//9 CRANE_NO
	private:
		string craneNO;
	public:
		string getCraneNO();
		void setCraneNO(string theVal);

		//10 PLAN_UP_X
	private:
		long planUpX;
	public:
		long getPlanUpX();
		void setPlanUpX(long theVal);

		//11 PLAN_UP_Y
	private:
		long planUpY;
	public:
		long getPlanUpY();
		void setPlanUpY(long theVal);

		//12 PLAN_UP_Z
	private:
		long planUpZ;
	public:
		long getPlanUpZ();
		void setPlanUpZ(long theVal);

		//13 UP_ROTATE_ANGLE_SET
	private:
		long upRotateAngleSet;
	public:
		long getUpRotateAngleSet();
		void setUpRotateAngleSet(long theVal);

		//14 CLAMP_WIDTH_SET
	private:
		long clampWidthSet;
	public:
		long getClampWidthSet();
		void setClampWidthSet(long theVal);

		//15 PLAN_DOWN_X
	private:
		long planDownX;
	public:
		long getPlanDownX();
		void setPlanDownX(long theVal);

		//16 PLAN_DOWN_Y
	private:
		long planDownY;
	public:
		long getPlanDownY();
		void setPlanDownY(long theVal);

		//17 PLAN_DOWN_Z
	private:
		long planDownZ;
	public:
		long getPlanDownZ();
		void setPlanDownZ(long theVal);

		//18 Down_Rotate_AngleSet
	private:
		long downRotateAngleSet;
	public:
		long getDownRotateAngleSet();
		void setDownRotateAngleSet(long theVal);

		//19 COIL_WIDTH
	private:
		long coilWidth;
	public:
		long getCoilWidth();
		void setCoilWidth(long theVal);

		//20 COIL_WEIGHT
	private:
		long coilWeight;
	public:
		long getCoilWeight();
		void setCoilWeight(long theVal);

		//21 COIL_OUT_DIA
	private:
		long coilOutDia;
	public:
		long getCoilOutDia();
		void setCoilOutDia(long theVal);

		//22 COIL_IN_DIA
	private:
		long coilInDia;
	public:
		long getCoilInDia();
		void setCoilInDia(long theVal);

		//23 FLOOR_UP_Z
	private:
		long floor_Up_Z;
	public:
		long getFloor_Up_Z();
		void setFloor_Up_Z(long theVal);

		//24 FLAG_SMALL_COIL
	private:
		long flag_Small_Coil;
	public:
		long getFlag_Small_Coil();
		void setFlag_Small_Coil(long theVal);
		//25 FLOOR_DOWN_Z
	private:
		long floor_Down_Z;
	public:
		long getFloor_Down_Z();
		void setFloor_Down_Z(long theVal);

	public:
		void logOutValues();


		const static string CRANE_ORDER_CURRENT_STATUS_EMPTY;

		const static string CRANE_ORDER_CURRENT_STATUS_ORDER_INIT;

		const static string CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS;

		const static string CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS;

	};




}
#endif