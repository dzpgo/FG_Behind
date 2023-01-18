/*********************************************************************
*		
*  文      件:    CarPlanBandInfo.h   		
*
*
*********************************************************************/
#pragma once
#ifndef _CarPlanBandInfo_
#define _CarPlanBandInfo_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{
	class CarPlanBandInfo
	{

	public:
		CarPlanBandInfo(void);

		~CarPlanBandInfo(void);

	private:
		void initValues();

		//1 CAR_NO 
	private:
		string carNO;
	public:
		string getCarNO();
		void   setCarNO(string theVal);

		//2 CAR_TYPE
	private:
		string carType;
	public:
		string getCarType();
		void setCarType(string theVal);

		//3 WORK_TYPE
	private:
		string workType;
	public:
		string getWorkType();
		void setWorkType(string theVal);

		//4 PLAN_NO
	private:
		string planNO;
	public:
		string getPlanNO();
		void setPlanNO(string theVal);

		//5 PLAN_SRC
	private:
		string planSrc;
	public:
		string getPlanSrc();
		void setPlanSrc(string theVal);

		//6 PLAN_DETAIL_ID
	private:
		long planDetailID;
	public:
		long getPlanDetailID();
		void setPlanDetailID(long theVal);

		//7 GATE_NO
	private:
		string gateNO;
	public:
		string getGateNO();
		void setGateNO(string theVal);

		//8 TARGET_GRID_NO
	private:
		string targetGridNO;
	public:
		string getTargetGridNO();
		void setTargetGridNO(string theVal);

		//9 TARGET_PARKING_NO
	private:
		string targetParkingNO;
	public:
		string getTargetParkingNO();
		void setTargetParkingNO(string theVal);

		//10 ENTER_FLAG
	private:
		string enterFlag;
	public:
		string getEnterFlag();
		void setEnterFlag(string theVal);

		//11 ORDER_FLAG
	private:
		string orderFlag;
	public:
		string getOrderFlag();
		void setOrderFlag(string theVal);

		//12 BAND_TIME
	private:
		iDA::DateTime bandTime;
	public:
		iDA::DateTime getBandTime();
		void setBandTime(iDA::DateTime theVal);



	public:
		void logOutValues();


		//作业类型定义
		const static string WORK_TYPE_XL;//卸料
		const static string WORK_TYPE_ZC;//装车

		//指令标记定义
		const static string ORDER_FLAG_1_NO_ORDER;//无对应指令
		const static string ORDER_FLAG_2_HAVE_ORDER;//有对应指令

		//计划来源
		const static string PLAN_SRC_L3;//L3计划
		const static string PLAN_SRC_EAF;//电炉L2计划
		const static string PLAN_SRC_BOF;//转炉L2计划

		//车辆类型
		const static string CAR_TYPE_TRUCK;//一般卡车 ：L3、EAF用
		const static string CAR_TYPE_TANK_TRUCK;//料槽车 转炉用
		const static string CAR_TYPE_RGV;//RGV 转炉用

		//是否已经已进入库区标记
		const static string ENTER_YARD_1_NO;//未进入库区
		const static string ENTER_YARD_2_YES;//已进入库区
		const static string ENTER_YARD_3_XLLK;//卸料离开
	};




}
#endif