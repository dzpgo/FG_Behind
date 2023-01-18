#pragma once
#ifndef  _CraneAutoManuSwitch_Tracker_
#define  _CraneAutoManuSwitch_Tracker_

#include "CraneMonitor.h"
#include "CranePLCStatusBase.h"
#include "OrderCurrentBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"
#include "App_Order_Msg_Def.h"

#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>
#include "EvadeCancelSender.h"
#include "EvadeRequestSender.h"

using namespace Monitor;

class  CraneAutoManuSwitch_Tracker
{


public:
	CraneAutoManuSwitch_Tracker();


private:
	//��ǰ���г�״̬���ݶ���
	CranePLCStatusBase    cranePLCStatus_Current;

	//ǰһ�ε��г�״̬���ݶ���
	CranePLCStatusBase    cranePLCStatus_Last;

	OrderCurrentBase craneOrderCurrentLastAuto;



public:

	void   Track_AutoManuSwitch();  




	
};

#endif
