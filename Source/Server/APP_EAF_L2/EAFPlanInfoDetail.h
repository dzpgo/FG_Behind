/*********************************************************************
*		
*  нд      ╪Ч:    EAFPlanInfoDetail.h   		
*
*
*********************************************************************/
#pragma once
#ifndef _EAFPlanInfoDetail_
#define _EAFPlanInfoDetail_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{
	class EAFPlanInfoDetail
	{

	public:
		EAFPlanInfoDetail(void);

		~EAFPlanInfoDetail(void);

	private:
		void initValues();

		//0 operID 
	private:
		string operID;
	public:
		string getOperID();
		void   setOperID(string theVal);

		//1 detailID 
	private:
		long detailID;
	public:
		long getDetailID();
		void   setDetailID(long theVal);

		//2 PONO
	private:
		string pono;
	public:
		string getPono();
		void setPono(string theVal);

		//3 B_SEQ_NUM
	private:
		string bSeqNum;
	public:
		string getBSeqNum();
		void setBSeqNum(string theVal);

		//4 PIT_NUM
	private:
		string pitNum;
	public:
		string getPitNum();
		void setPitNum(string theVal);

		//5 LAY_NO
	private:
		long layNO;
	public:
		long getLayNO();
		void setLayNO(long theVal);

		//6 SCR_ID
	private:
		string scrID;
	public:
		string getScrID();
		void setScrID(string theVal);

		//7 SCR_WEIGHT
	private:
		long scrWeight;
	public:
		long getScrWeight();
		void setScrWeight(long theVal);

		//8 CRANE_WEIGHT
	private:
		long craneWeight;
	public:
		long getCraneWeight();
		void setCraneWeight(long theVal);

		//9 SCL_WEIGHT
	private:
		long sclWeight;
	public:
		long getSclWeight();
		void setSclWeight(long theVal);

		//10 CAR_NO
	private:
		string carNO;
	public:
		string getCarNO();
		void setCarNO(string theVal);

		//11 GRID_NO
	private:
		string gridNO;
	public:
		string getGridNO();
		void setGridNO(string theVal);

		//12 MAT_CODE
	private:
		string matCode;
	public:
		string getMatCode();
		void setMatCode(string theVal);

		//13 COMP_CODE
	private:
		string compCode;
	public:
		string getCompCode();
		void setCompCode(string theVal);

		//14 LAY_VALID
	private:
		string layValid;
	public:
		string getLayValid();
		void setLayValid(string theVal);

		//15 STATUS
	private:
		string status;
	public:
		string getStatus();
		void setStatus(string theVal);




	public:
		void logOutValues();


		const	static string LAY_VALID_YES;
		const static string LAY_VALID_NO;

		const static string STATUS_NOT_START;
		const static string STATUS_START;
		const static string STATUS_FINISH;
		

		
	};




}
#endif