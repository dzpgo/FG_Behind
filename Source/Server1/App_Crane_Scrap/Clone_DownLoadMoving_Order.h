#pragma once
#ifndef  _Clone_DownLoadMoving_Order_
#define  _Clone_DownLoadMoving_Order_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "OrderCurrentBase.h"
#include "CranePLCStatusBase.h"

#include "CranePLCOrderBase.h"
#include "RouteStepPointBase.h"
#include "SafetyArea_Bay.h"

#include "MsgEUCR01.h"

#include "JUDGE_BEFORE_MOVING.h"
#include "EvadeCancelSender.h"
#include "EvadeRequestSender.h"


namespace Monitor
{
	class Clone_DownLoadMoving_Order
	{

	public:
		Clone_DownLoadMoving_Order(void );
		~Clone_DownLoadMoving_Order(void );

	public:
		static bool go( string bayNO, 
									string craneNO, 
									long orderNO, 
									long currentX, 
									long currentY, 
									long targetX, 
									long targetY, 
									long hasCoil, 
									long downRotateAngle, 
									long upRotateAngle, 
									long shortCmd );  
	};

}

#endif