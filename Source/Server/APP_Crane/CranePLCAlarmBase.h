/*********************************************************************
 *		
 *  文      件:    CranePLCAlarmBase.h   		
 *
 *
 *  概述：
 *        ：CranePLCAlarmBase 非单例类
 *        ：储存行车PLC送来的完整的报警数据信息
 *  版本历史		
 *      2017年04月建立
*********************************************************************/
#pragma once
#ifndef _CranePLCAlarmBase_
#define _CranePLCAlarmBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

//#include <Slice/CranePLCStatusStorm.h>
#include "CranePLCStatusStorm.h"

namespace Monitor
{



		class CranePLCAlarmBase
		{


		public:
				CranePLCAlarmBase(void);

				~CranePLCAlarmBase(void);

		private:
			    void initValues();
	
		//1 CRANE_NO 
		private:
			string craneNO;
		public:
			string getCraneNO();
			void   setCraneNO(string theVal);

		//2 EncoderVal
		private:
			string encoderVal;
		public:
			string getEncoderVal();
			void setEncodeVal(string theVal);

		//3 ErrorNum
		private:
			long errorNum;
		public:
			long getErrorNum();
			void   setErrorNum(long theVal);


		//4 ErrorList
		private:
			string errorList;
		public:
			string getErrorList();
			void setErrorList(string theVal);


		//5 timeReceive
		private:
			string timeReceive;
		public:
			string getTimeReceive();
			void setTimeReceive(string theVal);
	
		public:
			void  logOutValues();

		public:
			void wirteValues2TagSystem();

	
		public:
			
		

			 //---------------------------------------------------------------------------------------------------------------------------------------------------

		};




}
#endif