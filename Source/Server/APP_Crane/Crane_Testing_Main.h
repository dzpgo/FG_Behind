/*********************************************************************
*		
*  ��      ��:    CRANE_TESTING_D202_EXIT.h   		
*
*
*  ������
*        ���г�ACTION���������õĹ���������

*
*  �汾��ʷ		
*      2017��04�½���
*********************************************************************/
#pragma once
#ifndef  _Crane_Testing_Main_
#define  _Crane_Testing_Main_

#include "log4cplus/LOG.h"

#include "CraneMonitor.h"
#include "OrderCurrentBase.h"
#include "OrderQueueBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"


//----------------------------------------------------------------------------------
#include "Test_L3_Car_To_Yard.h"

namespace Monitor
{



	class Crane_Testing_Main
	{

	public:
		Crane_Testing_Main(void );
		~Crane_Testing_Main(void );


	public:

		static bool Test_AfterRolling(string craneNO, CranePLCStatusBase cranePLCStatusBase);

	};

}

#endif