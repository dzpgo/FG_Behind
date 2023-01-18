
#pragma once
#ifndef _CranePrivilegeInterpreter_
#define _CranePrivilegeInterpreter_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "CranePLCOrderBase.h"
#include "DataAccess.h"

#include "CranePLCStatusBase.h"
#include "CraneOrderCurrentBase.h"
#include "CraneEvadeRequestBase.h"
#include "ACTION_COMMON_FUNCTION.h"

namespace Monitor
{
		class CranePrivilegeInterpreter
		{
			public:
					CranePrivilegeInterpreter();
					~CranePrivilegeInterpreter(void);
			private:


			public:

					static  string compareByCrane(string craneNO, string neighborCraneNO);

					//2018.11.27 zhangyuhong add
					//行车靠近时判断行车优先级，用在 judge 中
					/*static string VSByOrderWhenApproach(long orderNO, 
																							string craneNO, 
																							string neighborCraneNO, 
																							CranePLCStatusBase cranePLCStatus, 
																							CranePLCStatusBase neighborCranePLCStatus);*/

					//2018.11.27 zhangyuhong add
					//行车避让时判断行车优先级，用在 receive 中
					/*static string VSByOrderWhenEvade(string targetCraneNO, 
																					CranePLCStatusBase targetCranePLCStatus, 
																					string senderCraneNO, 
																					long senderCraneOrderNO);*/


		public:
			//比较结果 本车等级高
	      const	 static   string  COMPARE_RESULT_HIGH  ;
			//比较结果 本车等级底
		  const	 static   string  COMPARE_RESULT_LOW  ;
			//比较结果 比较结果不确定
		  const	 static   string  COMPARE_RESULT_UNKNOW  ;






		
		};
}

#endif
