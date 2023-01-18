#pragma once
#ifndef _WATCH_DOG_LIFT_COIL_DOWN_PHASE_
#define _WATCH_DOG_LIFT_COIL_DOWN_PHASE_

#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "CranePLCStatusBase.h"
#include "CraneMonitor.h"
#include "CraneOrderCurrentBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"

#include "ACTION_COMMON_FUNCTION.h"

#include "CranePLCShortCmdBase.h"
#include "MsgUS01.h"
#include "CranePLCOrderBase.h"

#include "Adapter_UACS_CRANE_MOVEORDER_MSG.h"

namespace Monitor
{

		const static long DISTANCE_MIN_BETWEEN_2_CRANES = 19000;

		const static long ORDER_ID_WHEN_WATCHDOG = 113;

		const static long AC2CTV_X_MIN = 40428;
		const static long AC2CTV_X_MAX = 48866;

		const static long AC1CTV_X_MIN = 329146;
		const static long AC1CTV_X_MAX = 341340;

		const static long HAS_COIL_HIGH_5700 = 5700;
		const static long NO_COIL_HIGH_4800 = 4800;


		class WATCH_DOG_LIFT_COIL_DOWN_PHASE
		{


		public:
				WATCH_DOG_LIFT_COIL_DOWN_PHASE();

				//~WATCH_DOG_LIFT_COIL_DOWN_PHASE();		


		private:

				


		private:				

				CraneOrderCurrentBase craneOrderCurrent;
				CranePLCStatusBase cranePLCStatus_Current;

				//20200914 zhangyuhong add
				//增加上一个plc状态旧照
				CranePLCStatusBase cranePLCStatus_Last;

				int nCountPA1Lock;

				string tagValuePA1LockLast;
				string tagValuePA1LockCurrent;
				string craneNOSendPA1Lock;

				long wmsAlarmCodeCurrent;
				long wmsAlarmCodeLast;




		public:

				void watch(string craneNO);

				

		


		};




}
#endif

