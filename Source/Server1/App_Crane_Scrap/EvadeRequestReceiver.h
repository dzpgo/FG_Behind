//收到一个避让要求  包括接收行车号  发出行车号   最初发出行车号  避让要求X，避让实际X（等待解析）避让方向，避让动作类型（等待解析）
//解析实际避让X  解析动作类型（立即避让还是关后避让，这依据行车的等级来决定）

//如果我在手动状态，那么我什么也不能做了，不响应任何避让请求
//如果我在自动状态，那么我试图接受这个避让要求




//接受避让动作的过程
//						我原来有压入弹夹的避让指令吗？
//						如果没有，那么我将这发子弹压入弹夹。
//						如果弹夹里面原来有一发字段 那么
//								新的避让指令比老的避让指令等级高，那么用新的避让指令覆盖原来老的避让指令
//								如果新避让指令与老避让指令的方向相同，并且新的避让指令避让的范围更长，那么更新避让指令为新指令


#pragma once 
#ifndef   _EvadeRequestReceiver_ 
#define   _EvadeRequestReceiver_ 

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
#include "ACTION_COMMON_FUNCTION.h"

namespace Monitor
{




	class  EvadeRequestReceiver
	{





	public:
		EvadeRequestReceiver( void );
		~EvadeRequestReceiver( void );




	public:


		


	public:
		static void  receive(string craneNO, string sender, string origianlSender,  long evadeXRequest,  string evadeDirection, long evadeRequestOrderNO);

	

	   static bool splitTag_EvadeRequest(string tagVal, string& theCraneNO, string& theSender, string& theOrigianlSender, long& theEvadeXRequest, string & theEvadeDirection, long & theEvadeRequestOrderNO);
	};



}
#endif