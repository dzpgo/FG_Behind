/*********************************************************************
*		
*  文      件:    OrderDataBase.h   		
*
*
*********************************************************************/
#pragma once
#ifndef _OrderDataBase_
#define _OrderDataBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{
	class OrderDataBase
	{

	public:
		OrderDataBase(void);

		~OrderDataBase(void);

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

		//6 ORDER_STATUS
	private:
		string orderStatus;
	public:
		string getOrderStatus();
		void setOrderStatus(string theVal);

		//7 ORDER_DEL_FLAG
	private:
		string orderDelFlag;
	public:
		string getOrderDelFlag();
		void setOrderDelFlag(string theVal);

		//8 PLAN_SRC
	private:
		string planSrc;
	public:
		string getPlanSrc();
		void setPlanSrc(string theVal);

		//9 PLAN_NO
	private:
		string planNO;
	public:
		string getPlanNO();
		void setPlanNO(string theVal);

		//10 PLAN_DETAIL_ID
	private:
		long planDetailID;
	public:
		long getPlanDetailID();
		void setPlanDetailID(long theVal);

		//11 SCRAP_CODE
	private:
		string scrapCode;
	public:
		string getScrapCode();
		void setScrapCode(string theVal);

		//12 REQ_WEIGHT
	private:
		long reqWeight;
	public:
		long getReqWeight();
		void setReqWeight(long theVal);

		//13 CAR_NO
	private:
		string carNO;
	public:
		string getCarNO();
		void setCarNO(string theVal);

		//14 CAR_TYPE
	private:
		string carType;
	public:
		string getCarType();
		void setCarType(string theVal);

		//15 BAY_NO
	private:
		string bayNO;
	public:
		string getBayNO();
		void setBayNO(string theVal);

		//16 MAT_CODE
	private:
		string matCode;
	public:
		string getMatCode();
		void setMatCode(string theVal);

		//17 COMP_CODE
	private:
		string compCode;
	public:
		string getCompCode();
		void setCompCode(string theVal);

		//18 CAL_WEIGHT
	private:
		long calWeight;
	public:
		long getCalWeight();
		void setCalWeight(long theVal);

		//19 ACT_WEIGHT
	private:
		long actWeight;
	public:
		long getActWeight();
		void setActWeight(long theVal);

		//20 FROM_STOCK_NO
	private:
		string fromStockNO;
	public:
		string getFromStockNO();
		void setFromStockNO(string theVal);

		//21 TO_STOCK_NO
	private:
		string toStockNO;
	public:
		string getToStockNO();
		void setToStockNO(string theVal);

		//22 DOWN_POS_SEQ
	private:
		long downPosSeq;
	public:
		long getDownPosSeq();
		void setDownPosSeq(long theVal);

		//23 是否需要卸料质检
	private:
			string qcFlag;
	public:
		string getQCFlag();
		void setQCFlag(string theVal);


		

	public:
		void logOutValues();

		//指令类型定义
		const static string ORDER_TYPE_L3_CAR_TO_YARD_11;//L3计划物料入库
		const static string ORDER_TYPE_L3_YARD_TO_CAR_21;//L3计划物料装车
		const static string ORDER_TYPE_EAF_YARD_TO_CAR_22;//电炉计划物料装车
		const static string ORDER_TYPE_BOF_YARD_TO_RGV_23;//转炉计划物料装RGV
		const static string ORDER_TYPE_BOF_YARD_TO_CAR_24;//转炉计划物料装运槽车

		//指令状态定义
		const static string ORDER_STATUS_NOT_START_1;//指令未开始
		const static string ORDER_STATUS_START_2;//指令开始
		const static string ORDER_STATUS_END_3;//指令结束

		//指令删除标识定义
		const static string ORDER_DEL_FLAG_NOT_DEL_1;//指令未删除
		const static string ORDER_DEL_FLAG_DEL_2;//指令删除

		//卸料是否质检标识定义
		const static string ORDER_QC_FLAG_1;//需要质检
		const static string ORDER_QC_FLAG_0;//不需要质检







	};




}
#endif