/*********************************************************************
 *		
 *  文      件:    SafePLC4EAFYardBase.h 		
 *
 *
 *  概述：
 *        ：SafePLC4EAFYardBase 非单例类
 *        ：储存安全PLC送来的完整的机组相关状态数据信息
 *  版本历史		
 *      2017年11月建立
*********************************************************************/
#pragma once
#ifndef  _SafePLC4EAFYardBase_
#define  _SafePLC4EAFYardBase_



#include "log4cplus/LOG.h"
#include <tag/Tag.h>

namespace Monitor
{

		class SafePLC4EAFYardBase
		{
		public:
				SafePLC4EAFYardBase(void);

				~SafePLC4EAFYardBase(void);

		private:
			    void initValues();
	
		//1 
		private:
			string E1Status;
		public:
			string getE1Status();
			void   setE1Status(string theVal);

		//2 
		private:
			string E2Status;
		public:
			string getE2Status();
			void   setE2Status(string theVal);

		//3 
		private:
			string E3Status;
		public:
			string getE3Status();
			void   setE3Status(string theVal);

		//4 
		private:
			string E4Status;
		public:
			string getE4Status();
			void   setE4Status(string theVal);

		//5 
		private:
			string E5Status;
		public:
			string getE5Status();
			void   setE5Status(string theVal);

		//6
		private:
			string E6Status;
		public:
			string getE6Status();
			void   setE6Status(string theVal);

		//7 
		private:
			string E7Status;
		public:
			string getE7Status();
			void   setE7Status(string theVal);

		//8 
		private:
			string E8Status;
		public:
			string getE8Status();
			void   setE8Status(string theVal);

		//9 
		private:
			string E9Status;
		public:
			string getE9Status();
			void   setE9Status(string theVal);

		//10 
		private:
			string E10Status;
		public:
			string getE10Status();
			void   setE10Status(string theVal);

		//11 
		private:
			string F1Status;
		public:
			string getF1Status();
			void   setF1Status(string theVal);

		//12 
		private:
			string F2Status;
		public:
			string getF2Status();
			void   setF2Status(string theVal);

		//13 
		private:
			string F3Status;
		public:
			string getF3Status();
			void   setF3Status(string theVal);

		//14 
		private:
			string F4Status;
		public:
			string getF4Status();
			void   setF4Status(string theVal);

		//15 
		private:
			string F5Status;
		public:
			string getF5Status();
			void   setF5Status(string theVal);

		//16 
		private:
			string F6Status;
		public:
			string getF6Status();
			void   setF6Status(string theVal);

		//17 
		private:
			string F7Status;
		public:
			string getF7Status();
			void   setF7Status(string theVal);

		//18 
		private:
			string F8Status;
		public:
			string getF8Status();
			void   setF8Status(string theVal);

		//19 
		private:
			string F9Status;
		public:
			string getF9Status();
			void   setF9Status(string theVal);

		//20 
		private:
			string F10Status;
		public:
			string getF10Status();
			void   setF10Status(string theVal);

		//21 
		private:
			string F11Status;
		public:
			string getF11Status();
			void   setF11Status(string theVal);

		//22 
		private:
			string F12Status;
		public:
			string getF12Status();
			void   setF12Status(string theVal);

		//23 
		private:
			string F13Status;
		public:
			string getF13Status();
			void   setF13Status(string theVal);
			
		//24 
		private:
			string F14Status;
		public:
			string getF14Status();
			void   setF14Status(string theVal);
			
		
			
		public:
			void wirteValues2TagSystem();	
			
		//--------------------------------------------------安全PLC机组状态信号对应的系统内部tag点定义-------------------------------------
		//1 
		const static string ADRESS_SAFE_PLC_DL_YARD_E1;
		
		//2 
		const static string ADRESS_SAFE_PLC_DL_YARD_E2;
		
		//3 
		const static string ADRESS_SAFE_PLC_DL_YARD_E3;
		
		//4 
		const static string ADRESS_SAFE_PLC_DL_YARD_E4;
		
		//5 
		const static string ADRESS_SAFE_PLC_DL_YARD_E5;
		
		//6 
		const static string ADRESS_SAFE_PLC_DL_YARD_E6;
	
		//7 
		const static string ADRESS_SAFE_PLC_DL_YARD_E7;
		
		//8
		const static string ADRESS_SAFE_PLC_DL_YARD_E8;
		
		//9
		const static string ADRESS_SAFE_PLC_DL_YARD_E9;
		
		//10
		const static string ADRESS_SAFE_PLC_DL_YARD_E10;
		
		//11
		const static string ADRESS_SAFE_PLC_DL_YARD_F1;
		
		//12
		const static string ADRESS_SAFE_PLC_DL_YARD_F2;
				
		//13
		const static string ADRESS_SAFE_PLC_DL_YARD_F3;
		
		//14
		const static string ADRESS_SAFE_PLC_DL_YARD_F4;
		
		//15
		const static string ADRESS_SAFE_PLC_DL_YARD_F5;
		
		//16
		const static string ADRESS_SAFE_PLC_DL_YARD_F6;
		
		//17
		const static string ADRESS_SAFE_PLC_DL_YARD_F7;
			
		//18
		const static string ADRESS_SAFE_PLC_DL_YARD_F8;
		
		//19
		const static string ADRESS_SAFE_PLC_DL_YARD_F9;
			
		//20 
		const static string ADRESS_SAFE_PLC_DL_YARD_F10;
		
		//21 
		const static string ADRESS_SAFE_PLC_DL_YARD_F11;
		
		//22 
		const static string ADRESS_SAFE_PLC_DL_YARD_F12;
		
		//23 
		const static string ADRESS_SAFE_PLC_DL_YARD_F13;
		
		//24 
		const static string ADRESS_SAFE_PLC_DL_YARD_F14;
	

		};
}
#endif