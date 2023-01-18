#pragma once
#ifndef _Adapter_UACS_CRANE_MOVEORDER_MSG_
#define _Adapter_UACS_CRANE_MOVEORDER_MSG_

#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "OrderCurrentBase.h"

namespace Monitor
{


	class Adapter_UACS_CRANE_MOVEORDER_MSG
	{
	public:
		Adapter_UACS_CRANE_MOVEORDER_MSG(void);

		~Adapter_UACS_CRANE_MOVEORDER_MSG(void);

		//��ȡ UACS_CRANE_ORDER_MSG ��MSG_ID�����к�
		static bool SelMsgID(long& msgID);

		//�����������Ĳ�������⣬�������·����г���ָ����Ĵ������ݿ�
		static bool insertMoveOrderMsg(long msgID, 
																	 long craneNO,
																	 long orderID,
																	 long matWeight, 
																	 long matType, 
																	 long planUpX,
																	 long planUpY,
																	 long planUpZ,
																	 long upRotateAngle,
																	 long planDownX,
																	 long planDownY,
																	 long planDownZ,
																	 long downRotateAngle,
																	 long shortCMD, 
																	 long currentX, 
																	 long currentY, 
																	 long currentZ );

		static bool insertMoveOrderMsgMidPT(long msgID, 
																				map<long, map<string, long> > mapMidPointList);

		//2018.7.1 zhangyuhong add
		//�����г���������д�����ݿ��-�г�����������
		//UACS_CRANE_ALARM_HIS
		static bool insertCraneAlarmMsg(string craneNO, 
																	 long orderID, 
																	 long alarmCode);

		//2018.7.12 zhangyuhong add
		//�����г����Զ��л���������Ҫ��Ϊ�˼�¼ �г� ���Զ�ģʽͻ������
		//UACS_CRANE_AUTOMANU_SWITCH_HIS
		static bool insertCraneAutoManuSwitch(string craneNO, 
																				string switchBefore, 
																				string switchAfter);

		//2019.6.19 zhangyuhong add
		//�����г�����״��ֹͣ��¼�����
		//UACS_CRANE_URGENT_RECORD
		static bool insertCraneUrgentRecord(long eventNO, 
																			long orderNO, 
																			string craneNO, 
																			long xAct, 
																			long yAct, 
																			long zAct, 
																			long hasCoil
																			);

		//��ȡ�����ϸ� xmax xmin ysplit
		static bool SelXMaxXMinYSplit(long pointX, long pointY, long& xLimitMax, long& xLimitMin, long& ySplit);

	};
}



#endif

