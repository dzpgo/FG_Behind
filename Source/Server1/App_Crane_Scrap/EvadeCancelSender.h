

#pragma once 
#ifndef   _EvadeCancelSender_ 
#define   _EvadeCancelSender_ 

#include "DataAccess.h"
#include "log4cplus/LOG.h"
#include "MOVING_DIR.h"
#include "CranePLCOrderBase.h"
#include "CraneEvadeRequestBase.h"
#include "CranePLCStatusBase.h"
#include "CraneMonitor.h"
#include "CraneEvadeLimitDefine.h"
#include "CranePrivilegeInterpreter.h"
#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"
#include "Evade_Tag_Define.h"

namespace Monitor
{




	class  EvadeCancelSender
	{





	public:
		EvadeCancelSender( void );
		~EvadeCancelSender( void );




	public:


		


	public:
		static void  senderByMovingAction(string sender,  long currentX,  long targetX) ;

		static void  senderByManuAutoSwitch(string sender) ;
	
	private:
	   static bool wirteEvadeCancelTag( string theSender, string  theCancelDirection);
	};



}
#endif