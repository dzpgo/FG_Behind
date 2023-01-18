/*********************************************************************
 *		
 *  文      件:    CranePLCOrderBase.h   		
 *
 *
 *  概述：
 *        ：CranePLCOrderBase 非单例类
 *        ：储存下达行车的单条行车走行指令
 *  版本历史		
 *      2017年04月建立
*********************************************************************/
#pragma once
#ifndef _CranePLCOrderBase_
#define _CranePLCOrderBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{



		class CranePLCOrderBase
		{


		public:
				CranePLCOrderBase(void);

				~CranePLCOrderBase(void);

		private:
			    void initValues();
	
		//1 CRANE_NO 
		private:
			string craneNO;
		public:
			string getCraneNO();
			void   setCraneNO(string theVal);

		//2 ORDER_Id
		private:
			long orderID;
		public:
			long getOrderID();
			void setOrderID(long theVal);

		//3 MAT_WEIGHT
		private:
			long matWeight;
		public:
			long getMatWeight();
			void setMatWeight(long theVal);

		//4 MAT_TYPE
		private:
			long matType;
		public:
			long getMatType();
			void setMatType(long theVal);

		//5 PLAN_UP_X
		private:
			long planUpX;
		public:
			long getPlanUpX();
			void   setPlanUpX(long theVal);

		//6 PLAN_UP_Y
		private:
			long planUpY;
		public:
			long getPlanUpY();
			void setPlanUpY(long theVal);

		//7 PLAN_UP_Z
		private:
			long planUpZ;
		public:
			long getPlanUpZ();
			void setPlanUpZ(long theVal);

		//8 UP_ROTATE_ANGLE_SET
		private:
			long upRotateAngleSet;
		public:
			long getUpRotateAngleSet();
			void setUpRptateAngleSet(long theVal);

		//9 PLAN_DOWN_X
		private:
			long planDownX;
		public:
			long getPlanDownX();
			void setPlanDownX(long theVal);

		//10 PLAN_DOWN_Y
		private:
			long planDownY;
		public:
			long getPlanDownY();
			void setPlanDownY(long theVal);

		//11 PLAN_DOWN_Z
		private:
			long planDownZ;
		public:
			long getPlanDownZ();
			void setPlanDownZ(long theVal);

		//12 DOWN_ROTATE_ANGLE_SET
		private:
			long downRotateAngleSet;
		public:
			long getDownRotateAngleSet();
			void setDownRotateAngleSet(long theVal);

		//13 SHORT_CMD
		private:
			long shortCmd;
		public:
			long getShortCmd();
			void setShortCmd(long theVal);

		//14 中间路径点map
		private:
			map< long, map<string, long> > mapMidPointList;
		public:
			map< long, map<string, long> > getMapMidPointList();
			void setMapMidPointList(map< long, map<string, long> > theVal);

		public:
			void  logOutValues();

	
		public:
			//--------------------------------------------------下达PLC系统的初始值设定----------------------------------------------------------------
			 //PLC开关量初始值;
			 const static  long PLC_X_NULL;
			 //PLC模拟量初始值
			 const static  long PLC_INT_NULL;
			
			 //---------------------------------------------------------------------------------------------------------------------------------------------------


		};




}
#endif