
#ifndef _EvadeRequestSender_
#define _EvadeRequestSender_

#include <map>
#include <vector>

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
#include "NEIGHBOR_AHEAD.h"
#include "RED_LINE_BASIC_DATA.h"
#include "CraneOrderCurrentBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"
#include "EvadeRequestSenderException.h"

namespace Monitor
{



		class EvadeRequestSender
		{


		public:
				//构造行数
				EvadeRequestSender(void);
				//析构函数
				~EvadeRequestSender(void);

		private:
				//单例函数指针
				static EvadeRequestSender*	m_pEvadeRequestSender;

		public:
				//获得指针的方法
				static  EvadeRequestSender*  getInstance(void);

		

		public:
			void  senderByMovingAction(string craneNO,  long orderNO, long currentX,  long targetX) ;
			void  reset();

		private:
			//2018.11.29 zhangyuhong add
			//增加1个参数：发送避让请求时的发起者 sender 的指令号：evadeRequestOrderNO
		   bool wirteEvadeRequestTag(string targetCraneNO, string theSender, string origianlSender , long evadeXRequest, string  evadeDirection, long evadeRequestOrderNO);


		private:
			long  orderNO_LastSentOut;
			long  evadeXRequest_LastSentOut;
			long count;

		public:
			const static long MaxCount;
		};




}
#endif