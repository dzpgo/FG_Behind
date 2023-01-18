/*********************************************************************
 *		
 *  ��      ��:    CranePLCAlarmBase.h   		
 *
 *
 *  ������
 *        ��CranePLCAlarmBase �ǵ�����
 *        �������г�PLC�����������ı���������Ϣ
 *  �汾��ʷ		
 *      2017��04�½���
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