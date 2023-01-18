#pragma once 
#ifndef   _SrsMsgRcvHandler_ 
#define   _SrsMsgRcvHandler_ 

#include "DataAccess.h"
#include "log4cplus/LOG.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"
#include "ACTION_COMMON_FUNCTION.h"
#include "OrderCurrentBase.h"

namespace Monitor
{




	class  SrsMsgRcvHandler
	{





	public:
		SrsMsgRcvHandler( void );
		~SrsMsgRcvHandler( void );




	public:

		void LU01Handler(string strValue, string craneNO);

		void LU02Handler(string strValue, string craneNO);


		

	};



}
#endif