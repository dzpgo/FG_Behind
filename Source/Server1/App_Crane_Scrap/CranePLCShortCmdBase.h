/*********************************************************************
 *		
 *  文      件:    CranePLCShortCmdBase.h   		
 *
 *
 *  概述：
 *        ：CranePLCShortCmdBase 非单例类
 *        ：储存下达行车的单条短控制指令
 *  版本历史		
 *      2017年04月建立
*********************************************************************/
#pragma once
#ifndef _CranePLCShortCmdBase_
#define _CranePLCShortCmdBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{



		class CranePLCShortCmdBase
		{


		public:
				CranePLCShortCmdBase(void);

				~CranePLCShortCmdBase(void);

		private:
			    void initValues();
	
		//1 CRANE_NO 
		private:
			string craneNO;
		public:
			string getCraneNO();
			void   setCraneNO(string theVal);

		//2 cmdCode
		private:
			long cmdCode;
		public:
			long getCmdCode();
			void setCmdCode(long theVal);

		public:
			void  logOutValues();

	
		public:
			//--------------------------------------------------下达PLC系统的初始值设定----------------------------------------------------------------
			//正常停车
			const static  long SHORT_CMD_NORMAL_STOP;
			//紧停
			 const static  long SHORT_CMD_EMG_STOP;
			 //复位
			 const static  long SHORT_CMD_RESET;
			 //要求计算机自动
			 const static long  SHORT_CMD_ASK_COMPUTER_AUTO;
			 //要求取消计算机自动
			 const static long SHORT_CMD_CANCEL_COMPUTER_AUTO;
			
			 //---------------------------------------------------------------------------------------------------------------------------------------------------


		};




}
#endif