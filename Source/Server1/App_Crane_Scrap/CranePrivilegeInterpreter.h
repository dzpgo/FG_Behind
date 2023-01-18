
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
					//�г�����ʱ�ж��г����ȼ������� judge ��
					/*static string VSByOrderWhenApproach(long orderNO, 
																							string craneNO, 
																							string neighborCraneNO, 
																							CranePLCStatusBase cranePLCStatus, 
																							CranePLCStatusBase neighborCranePLCStatus);*/

					//2018.11.27 zhangyuhong add
					//�г�����ʱ�ж��г����ȼ������� receive ��
					/*static string VSByOrderWhenEvade(string targetCraneNO, 
																					CranePLCStatusBase targetCranePLCStatus, 
																					string senderCraneNO, 
																					long senderCraneOrderNO);*/


		public:
			//�ȽϽ�� �����ȼ���
	      const	 static   string  COMPARE_RESULT_HIGH  ;
			//�ȽϽ�� �����ȼ���
		  const	 static   string  COMPARE_RESULT_LOW  ;
			//�ȽϽ�� �ȽϽ����ȷ��
		  const	 static   string  COMPARE_RESULT_UNKNOW  ;






		
		};
}

#endif
