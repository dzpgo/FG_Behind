#pragma once 
#ifndef   _CraneEvadeLimitDefine_ 
#define   _CraneEvadeLimitDefine_ 

#include "DataAccess.h"
#include "log4cplus/LOG.h"
#include "MOVING_DIR.h"
#include "CranePLCOrderBase.h"
namespace Monitor
{




	class  CraneEvadeLimitDefine
	{





	public:
		CraneEvadeLimitDefine( void );
		~CraneEvadeLimitDefine( void );




	public:
	
		
		//4-4
		const static  bool       CRANE_4_4_CAN_EVADE_TO_X_INC;
		const static  bool       CRANE_4_4_CAN_EVADE_TO_X_DES;
		const  static  long	 	CRANE_4_4_X_MAX_HAS_COIL;
		const  static  long	 	CRANE_4_4_X_MAX_NO_COIL;

		//4-5
		const static  bool       CRANE_4_5_CAN_EVADE_TO_X_INC;
		const static  bool       CRANE_4_5_CAN_EVADE_TO_X_DES;
		const  static  long	 	CRANE_4_5_X_MIN_HAS_COIL;
		const  static  long	 	CRANE_4_5_X_MAX_HAS_COIL;
		const  static  long	 	CRANE_4_5_X_MIN_NO_COIL;		
		const  static  long	 	CRANE_4_5_X_MAX_NO_COIL;

		//4-6
		const static  bool       CRANE_4_6_CAN_EVADE_TO_X_INC;
		const static  bool       CRANE_4_6_CAN_EVADE_TO_X_DES;
		const  static  long	 	CRANE_4_6_X_MIN_HAS_COIL;
		const  static  long	 	CRANE_4_6_X_MAX_HAS_COIL;
		const  static  long	 	CRANE_4_6_X_MIN_NO_COIL;		
		const  static  long	 	CRANE_4_6_X_MAX_NO_COIL;

		//4-7
		const static  bool       CRANE_4_7_CAN_EVADE_TO_X_INC;
		const static  bool       CRANE_4_7_CAN_EVADE_TO_X_DES;
		const  static  long	 	CRANE_4_7_X_MIN_HAS_COIL;
		const  static  long	 	CRANE_4_7_X_MIN_NO_COIL;



	public:
		static bool  isDirectionOK(string craneNO, string direction ) ;

		static bool calEvadeXAct(string craneNO, string direction, long hasCoil, long evadeXRequest, long& evadeX);



	private:
		static bool calEvadeXAct_4_5(string craneNO, string direction, long hasCoil, long evadeXRequest, long& evadeX);
		static bool calEvadeXAct_4_6(string craneNO, string direction, long hasCoil, long evadeXRequest, long& evadeX);
		static bool calEvadeXAct_4_4(string craneNO, string direction, long hasCoil, long evadeXRequest, long& evadeX);
		static bool calEvadeXAct_4_7(string craneNO, string direction, long hasCoil, long evadeXRequest, long& evadeX);

		


	};



}
#endif