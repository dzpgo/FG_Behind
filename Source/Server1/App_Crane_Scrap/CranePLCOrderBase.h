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

		//2 SHORT_CMD
		private:
			long shortCmd;
		public:
			long getShortCmd();
			void setShortCmd(long theVal);

		//3 ORDER_Id
		private:
			long orderID;
		public:
			long getOrderID();
			void setOrderID(long theVal);

		//4 MAT_TYPE
		private:
			long matType;
		public:
			long getMatType();
			void setMatType(long theVal);

		//5 MAT_YARD
		private:
			string matYard;
		public:
			string getMatYard();
			void setMatYard(string theVal);

		//6 MAT_WEIGHT
		private:
			long matWeight;
		public:
			long getMatWeight();
			void setMatWeight(long theVal);

		//7 PLAN_UP_X
		private:
			long planUpX;
		public:
			long getPlanUpX();
			void   setPlanUpX(long theVal);

		//8 PLAN_UP_Y
		private:
			long planUpY;
		public:
			long getPlanUpY();
			void setPlanUpY(long theVal);

		//9 PLAN_UP_Z
		private:
			long planUpZ;
		public:
			long getPlanUpZ();
			void setPlanUpZ(long theVal);

		////8 UP_ROTATE_ANGLE_SET
		//private:
		//	long upRotateAngleSet;
		//public:
			//long getUpRotateAngleSet();
			//void setUpRptateAngleSet(long theVal);

		//10 PLAN_DOWN_X
		private:
			long planDownX;
		public:
			long getPlanDownX();
			void setPlanDownX(long theVal);

		//11 PLAN_DOWN_Y
		private:
			long planDownY;
		public:
			long getPlanDownY();
			void setPlanDownY(long theVal);

		//12 PLAN_DOWN_Z
		private:
			long planDownZ;
		public:
			long getPlanDownZ();
			void setPlanDownZ(long theVal);

		//13 SPACE
		private:
			long space;
		public:
			long getSpace();
			void setSpace(long theVal);

		//14 CRC
			long crc;
		public:
			long getCrc();
			void setCrc(long theVal);


		////12 DOWN_ROTATE_ANGLE_SET
		//private:
		//	long downRotateAngleSet;
		//public:
		//	long getDownRotateAngleSet();
		//	void setDownRotateAngleSet(long theVal);

		

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

			 			 //---------------------------------------------------------------------------------------------------------------------------------------------------
			 //--------------------------------------------------行车状态信号对应的系统内部tag点定义-------------------------------------
			 //--------------------------------------------------系统内部tag点主要供给画面使用，行车后台程序不使用------------
			//1 CRANE_NO
			 const static string ADRESS_CRANE_NO_SET;
			 //2 SHORT_CMD
			 const static string ADRESS_SHORT_CMD_SET;
			 //3 ORDER_Id
			 const static string ADRESS_ORDER_Id_SET;
			 //4 MAT_TYPE
			 const static string ADRESS_MAT_TYPE_SET;
			 //5 MAT_YARD
			 const static string ADRESS_MAT_YARD_SET;
			 //6 MAT_WEIGHT
			 const static string ADRESS_MAT_WEIGHT_SET;
			 //7 PLAN_UP_X
			 const static string  ADRESS_PLAN_UP_X_SET;
			 //8 PLAN_UP_Y
			 const static string ADRESS_PLAN_UP_Y_SET;
			 //9 PLAN_UP_Z
			 const static string ADRESS_PLAN_UP_Z_SET;
			 //10 PLAN_DOWN_X
			 const static string ADRESS_PLAN_DOWN_X_SET;
			 //11 PLAN_DOWN_Y
			 const static string ADRESS_PLAN_DOWN_Y_SET;
			 //12 PLAN_DOWN_Z
			 const static string ADRESS_PLAN_DOWN_Z_SET;
			 //13 SPACE
			 const static string ADRESS_SPACE_SET;
			 //14 CRC
			 const static string ADRESS_CRC_SET;
			

			 //99 DownLoadOrder
			 const static string ADRESS_DOWN_LOAD_ORDER;

		};




}
#endif