#pragma once
#ifndef  _YARD_MAP_TRACKER_H_
#define  _YARD_MAP_TRACKER_H_

#include "DataAccess.h"
#include "CraneMonitor.h"
#include "CranePLCStatusBase.h"
#include "OrderCurrentBase.h"
#include "OrderQueueBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"
#include "Adapter_UACS_CRANE_MOVEORDER_MSG.h"
#include "Adapter_UACS_YARDMAP_STOCK_INFO.h"
#include "MsgUS01.h"
#include "MsgUS02.h"
#include "SafetyArea_Bay.h"

using namespace Monitor;

class  YardMapTracker
{


public:
	YardMapTracker();

	


private:

	//�г���������
	string actionTrack;



	//��ǰ���г�״̬���ݶ���
	CranePLCStatusBase    cranePLCStatus_Current;

	//ǰһ�ε��г�״̬���ݶ���
	CranePLCStatusBase    cranePLCStatus_Last;

	//2018.3.12 zhangyuhong add
	//��uacs�г��Զ�ִ��Aָ��δִ�����ʱ���е��ֶ���Ȼ�����е��Զ��һ���ִ��Bָ���ʱ��tag�� 3_1_ACTIONS_TRACKER��ΪINIT
	long orderIDOld;
	long orderIDNew;
	int orderNODurTrack;



	

public:

	void   EventTrack_CraneActions();  

private:

	bool existSubString(string str1, string str2);

	void sendUL01(OrderCurrentBase orderCurrent, CranePLCStatusBase cranePLCStatus);

	void sendUL02(OrderCurrentBase orderCurrent, CranePLCStatusBase cranePLCStatus);

	bool getUL01TagValue(OrderCurrentBase orderCurrent, CranePLCStatusBase cranePLCStatus, string& tagValue);

	bool getUL02TagValue(OrderCurrentBase orderCurrent, string& tagValue);

	bool notLeaveCenter(string moveDir, long startX, long endX, long startY, long endY, CranePLCStatusBase cranePLCStatus);



const static bool COIL_UP;
const static bool COIL_DOWN;

};

#endif
