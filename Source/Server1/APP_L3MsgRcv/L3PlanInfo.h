/*********************************************************************
*		
*  文      件:    L3PlanInfo.h   		
*
*
*********************************************************************/
#pragma once
#ifndef _L3PlanInfo_
#define _L3PlanInfo_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{
	class L3PlanInfo
	{

	public:
		L3PlanInfo(void);

		~L3PlanInfo(void);

	private:
		void initValues();

		//1 WORK_SEQ_NO 
	private:
		string workSeqNO;
	public:
		string getWorkSeqNO();
		void   setWorkSeqNO(string theVal);

		//2 OPERATE_FLAG
	private:
		string operateFlag;
	public:
		string getOperateFlag();
		void setOperateFlag(string theVal);

		//3 CAR_NO
	private:
		string carNO;
	public:
		string getCarNO();
		void setCarNO(string theVal);

		//4 WEIGH_APP_NO
	private:
		string weighAppNO;
	public:
		string getWeighAppNO();
		void setWeighAppNO(string theVal);

		//5 WEIGH_APP_TIME
	private:
		iDA::DateTime weighAppTime;
	public:
		iDA::DateTime getWeighAppTime();
		void setWeighAppTime(iDA::DateTime theVal);

		//6 REC_CREATOR
	private:
		string recCreator;
	public:
		string getRecCreator();
		void setRecCreator(string theVal);

		//7 SRC_STOCK_CODE
	private:
		string srcStockCode;
	public:
		string getSrcStockCode();
		void setSrcStockCode(string theVal);

		//8 SRC_LOC_CODE
	private:
		string srcLocCode;
	public:
		string getSrcLocCode();
		void setSrcLocCode(string theVal);

		//9 SRC_MAT_CODE
	private:
		string srcMatCode;
	public:
		string getSrcMatCode();
		void setSrcMatCode(string theVal);

		//10 SRC_COMP_CODE
	private:
		string srcCompCode;
	public:
		string getSrcCompCode();
		void setSrcCompCode(string theVal);

		//11 DST_STOCK_CODE
	private:
		string dstStockCode;
	public:
		string getDstStockCode();
		void setDstStockCode(string theVal);

		//12 DST_LOC_CODE
	private:
		string dstLocCode;
	public:
		string getDstLocCode();
		void setDstLocCode(string theVal);

		//13 DST_MAT_CODE
	private:
		string dstMatCode;
	public:
		string getDstMatCode();
		void setDstMatCode(string theVal);

		//14 DST_COMP_CODE
	private:
		string dstCompCode;
	public:
		string getDstCompCode();
		void setDstCompCode(string theVal);

		//15 ESTIMATE_WGT
	private:
		long estimateWgt;
	public:
		long getEstimateWgt();
		void setEstimateWgt(long theVal);

		//16 START_FLAG
	private:
		string startFlag;
	public:
		string getStartFlag();
		void setStartFlag(string theVal);

		//17 QC_FLAG
	private:
		string qcFlag;
	public:
		string getQCFlag();
		void setQCFlag(string theVal);

		//18 PLAN_TYPE
	private:
		string planType;
	public:
		string getPlanType();
		void setPlanType(string theVal);

		//19 PLAN_STATUS
	private:
		string planStatus;
	public:
		string getPlanStatus();
		void setPlanStatus(string theVal);

		//20 PLAN_VALID
	private:
		string planValid;
	public:
		string getPlanValid();
		void setPlanValid(string theVal);


	public:
		void logOutValues();


		//建议归堆标记
		const static string START_FLAG_G;//建议
		const static string START_FLAG_C;//取消建议

		//是否需要质检
		const static string QC_FLAG_1;//需要
		const static string QC_FLAG_0;//不需要

		//计划类型
		const static string PLAN_TYPE_ZC;//1
		const static string PLAN_TYPE_XL;//2
		const static string PLAN_TYPE_ZC_XL;//3

		const	static string PLAN_VALID_YES;
		const static string PLAN_VALID_NO;

		const static string OPERATE_FLAG_I;
		const static string OPERATE_FLAG_D;
		

		
	};




}
#endif