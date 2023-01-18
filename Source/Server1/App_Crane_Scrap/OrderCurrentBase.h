/*********************************************************************
*		
*  文      件:    OrderCurrentBase.h   		
*
*
*  概述：
*        ：CraneUACSOrderBase 非单例类
*        ：存储行车自动的行车指令状态表内的信息，这张表用行车号做键字，每个行车一条
*  版本历史		
*      2017年04月建立
*********************************************************************/
#pragma once
#ifndef _OrderCurrentBase_
#define _OrderCurrentBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{
	class OrderCurrentBase
	{

	public:
		OrderCurrentBase(void);

		~OrderCurrentBase(void);

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

		//3 MAT_CODE
	private:
		string matCode;
	public:
		string getMatCode();
		void setMatCode(string theVal);

		//4 COMP_CODE
	private:
		string compCode;
	public:
		string getCompCode();
		void setCompCode(string theVal);

		//5 MAT_TYPE   1-轻废 2-中废  3-重废
	private:
		string matType;
	public:
		string getMatType();
		void setMatType(string theVal);

		//6 MAT_REQ_WGT
	private:
		long matReqWgt;
	public:
		long getMatReqWgt();
		void setMatReqWgt(long theVal);

		//7 MAT_ACT_WGT
	private:
		long matActWgt;
	public:
		long getMatActWgt();
		void setMatActWgt(long theVal);

		//8 MAT_CUR_WGT
	private:
		long matCurWgt;
	public:
		long getMatCurWgt();
		void setMatCurWgt(long theVal);

		//9 ORDER_TYPE
	private:
		string orderType;
	public:
		string getOrderType();
		void setOrderType(string theVal);

		//10 ORDER_PRIORITY
	private:
		long orderPriority;
	public:
		long getOrderPriority();
		void setOrderPriority(long theVal);

		//11 FROM_STOCK_NO
	private:
		string fromStockNO;
	public:
		string getFromStockNO();
		void setFromStockNO(string theVal);

		//12 TO_STOCK_NO
	private:
		string toStockNO;
	public:
		string getToStockNO();
		void setToStockNO(string theVal);

		//13 CMD_STATUS
	private:
		string cmdStatus;
	public:
		string getCmdStatus();
		void setCmdStatus(string theVal);

		//14 CMD_SEQ
	private:
		long cmdSeq;
	public:
		long getCmdSeq();
		void setCmdSeq(long theVal);

		//15 CRANE_NO
	private:
		string craneNO;
	public:
		string getCraneNO();
		void setCraneNO(string theVal);

		//16 CAR_SCAN_NO
	private:
		string carScanNO;
	public:
		string getCarScanNO();
		void setCarScanNO(string theVal);

		//17 MAT_UP_SCAN_NO
	private:
		string matUpScanNO;
	public:
		string getMatUpScanNO();
		void setMatUpScanNO(string theVal);

		//18 PLAN_UP_X
	private:
		long planUpX;
	public:
		long getPlanUpX();
		void setPlanUpX(long theVal);

		//19 PLAN_UP_Y
	private:
		long planUpY;
	public:
		long getPlanUpY();
		void setPlanUpY(long theVal);

		//20 PLAN_UP_Z
	private:
		long planUpZ;
	public:
		long getPlanUpZ();
		void setPlanUpZ(long theVal);

		//21 UP_ROTATE_ANGLE
	private:
		long upRotateAngle;
	public:
		long getUpRotateAngle();
		void setUpRotateAngle(long theVal);

		//22 MAT_DOWN_SCAN_NO
	private:
		string matDownScanNO;
	public:
		string getMatDownScanNO();
		void setMatDownScanNO(string theVal);		

		//23 PLAN_DOWN_X
	private:
		long planDownX;
	public:
		long getPlanDownX();
		void setPlanDownX(long theVal);

		//24 PLAN_DOWN_Y
	private:
		long planDownY;
	public:
		long getPlanDownY();
		void setPlanDownY(long theVal);

		//25 PLAN_DOWN_Z
	private:
		long planDownZ;
	public:
		long getPlanDownZ();
		void setPlanDownZ(long theVal);

		//26 DOWN_ROTATE_ANGLE
	private:
		long downRotateAngle;
	public:
		long getDownRotateAngle();
		void setDownRotateAngle(long theVal);


	public:
		void logOutValues();


		const static string CRANE_ORDER_CURRENT_STATUS_EMPTY;

		const static string CRANE_ORDER_CURRENT_STATUS_ORDER_INIT;

		const static string CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS;

		const static string CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS;

	};




}
#endif