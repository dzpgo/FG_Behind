/*********************************************************************
*		
*  文      件:    OrderQueueBase.h   		
*
*
*********************************************************************/
#pragma once
#ifndef _OrderQueueBase_
#define _OrderQueueBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{
	class OrderQueueBase
	{

	public:
		OrderQueueBase(void);

		~OrderQueueBase(void);

	private:
		void initValues();

		//1 ORDER_NO 
	private:
		long orderNO;
	public:
		long getOrderNO();
		void   setOrderNO(long theVal);

		//2 ORDER_GROUP_NO
	private:
		long orderGroupNO;
	public:
		long getOrderGroupNO();
		void setOrderGroupNO(long theVal);

		//3 EXE_SEQ
	private:
		long exeSeq;
	public:
		long getExeSeq();
		void setExeSeq(long theVal);

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

		//6 EXE_ENABLE
	private:
		string exeEnable;
	public:
		string getExeEnable();
		void setExeEnable(string theVal);

		//7 CRANE_NO
	private:
		string craneNO;
	public:
		string getCraneNO();
		void setCraneNO(string theVal);

		//8 CMD_STATUS
	private:
		string cmdStatus;
	public:
		string getCmdStatus();
		void setCmdStatus(string theVal);

		//9 CMD_SEQ
	private:
		long cmdSeq;
	public:
		long getCmdSeq();
		void setCmdSeq(long theVal);

		//10 PLAN_SRC
	private:
		string planSrc;
	public:
		string getPlanSrc();
		void setPlanSrc(string theVal);

		//11 PLAN_NO
	private:
		string planNO;
	public:
		string getPlanNO();
		void setPlanNO(string theVal);

		//12 PLAN_DETAIL_ID
	private:
		long planDetailID;
	public:
		long getPlanDetailID();
		void setPlanDetailID(long theVal);

		//13 SCRAP_CODE
	private:
		string scrapCode;
	public:
		string getScrapCode();
		void setScrapCode(string theVal);

		//14 REQ_WEIGHT
	private:
		long reqWeight;
	public:
		long getReqWeight();
		void setReqWeight(long theVal);

		//15 CAR_NO
	private:
		string carNO;
	public:
		string getCarNO();
		void setCarNO(string theVal);

		//16 CAR_TYPE
	private:
		string carType;
	public:
		string getCarType();
		void setCarType(string theVal);

		//17 BAY_NO
	private:
		string bayNO;
	public:
		string getBayNO();
		void setBayNO(string theVal);

		//18 MAT_CODE
	private:
		string matCode;
	public:
		string getMatCode();
		void setMatCode(string theVal);

		//19 COMP_CODE
	private:
		string compCode;
	public:
		string getCompCode();
		void setCompCode(string theVal);

		//20 CAL_WEIGHT
	private:
		long calWeight;
	public:
		long getCalWeight();
		void setCalWeight(long theVal);

		//21 ACT_WEIGHT
	private:
		long actWeight;
	public:
		long getActWeight();
		void setActWeight(long theVal);

		//22 FROM_STOCK_NO
	private:
		string fromStockNO;
	public:
		string getFromStockNO();
		void setFromStockNO(string theVal);

		//23 TO_STOCK_NO
	private:
		string toStockNO;
	public:
		string getToStockNO();
		void setToStockNO(string theVal);

		//24 DOWN_POS_SEQ
	private:
		long downPosSeq;
	public:
		long getDownPosSeq();
		void setDownPosSeq(long theVal);

		//25 CUR_WEIGHT
	private:
		long curWeight;
	public:
		long getCurWeight();
		void setCurWeight(long theVal);



	public:
		void logOutValues();

		//指令类型定义
		const static string ORDER_TYPE_L3_CAR_TO_YARD_11;//L3计划物料入库
		const static string ORDER_TYPE_L3_YARD_TO_CAR_21;//L3计划物料装车
		const static string ORDER_TYPE_EAF_YARD_TO_CAR_22;//电炉计划物料装车
		const static string ORDER_TYPE_BOF_YARD_TO_RGV_23;//转炉计划物料装RGV
		const static string ORDER_TYPE_BOF_YARD_TO_CAR_24;//转炉计划物料装运槽车

		//指令执行状态定义
		const static string CMD_STATUS_INIT_0;//指令初始化
		const static string CMD_STATUS_START_1;//指令获取
		const static string CMD_STATUS_SRS_S;//激光扫描
		const static string CMD_STATUS_PLAN_UP_POS_ARRIVE_2;//取料点上方
		const static string CMD_STATUS_EMPTY_CLAMP_DOWN_3;//吸盘空载下降到位
		const static string CMD_STATUS_CLAMP_EMPTY_TO_FULL_4;//吸盘空载变有载
		const static string CMD_STATUS_FULL_CLAMP_UP_5;//吸盘重载上升到位
		const static string CMD_STATUS_PLAN_DOWN_POS_ARRIVE_6;//放料点上方
		const static string CMD_STATUS_FULL_CLAMP_DOWN_7;//吸盘重载下降到位
		const static string CMD_STATUS_CLAMP_FULL_TO_EMPTY_8;//吸盘空载上升到位
		const static string CMD_STATUS_EMPTY_CLAMP_UP_9;//吸盘空载上升到位

		//指令删除标识定义
		const static string EXE_ENABLE_YES_1;//指令可执行
		const static string EXE_ENABLE_NO_2;//指令不可执行






	};




}
#endif