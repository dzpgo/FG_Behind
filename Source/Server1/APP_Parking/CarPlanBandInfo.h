/*********************************************************************
*		
*  ��      ��:    CarPlanBandInfo.h   		
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


		//��ҵ���Ͷ���
		const static string WORK_TYPE_XL;//ж��
		const static string WORK_TYPE_ZC;//װ��

		//ָ���Ƕ���
		const static string ORDER_FLAG_1_NO_ORDER;//�޶�Ӧָ��
		const static string ORDER_FLAG_2_HAVE_ORDER;//�ж�Ӧָ��

		//�ƻ���Դ
		const static string PLAN_SRC_L3;//L3�ƻ�
		const static string PLAN_SRC_EAF;//��¯L2�ƻ�
		const static string PLAN_SRC_BOF;//ת¯L2�ƻ�

		//��������
		const static string CAR_TYPE_TRUCK;//һ�㿨�� ��L3��EAF��
		const static string CAR_TYPE_TANK_TRUCK;//�ϲ۳� ת¯��
		const static string CAR_TYPE_RGV;//RGV ת¯��

		//�Ƿ��Ѿ��ѽ���������
		const static string ENTER_YARD_1_NO;//δ�������
		const static string ENTER_YARD_2_YES;//�ѽ������
		const static string ENTER_YARD_3_XLLK;//ж���뿪
	};




}
#endif