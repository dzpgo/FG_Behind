//�յ�һ������Ҫ��  ���������г���  �����г���   ��������г���  ����Ҫ��X������ʵ��X���ȴ����������÷��򣬱��ö������ͣ��ȴ�������
//����ʵ�ʱ���X  �����������ͣ��������û��ǹغ���ã��������г��ĵȼ���������

//��������ֶ�״̬����ô��ʲôҲ�������ˣ�����Ӧ�κα�������
//��������Զ�״̬����ô����ͼ�����������Ҫ��




//���ܱ��ö����Ĺ���
//						��ԭ����ѹ�뵯�еı���ָ����
//						���û�У���ô�ҽ��ⷢ�ӵ�ѹ�뵯�С�
//						�����������ԭ����һ���ֶ� ��ô
//								�µı���ָ����ϵı���ָ��ȼ��ߣ���ô���µı���ָ���ԭ���ϵı���ָ��
//								����±���ָ�����ϱ���ָ��ķ�����ͬ�������µı���ָ����õķ�Χ��������ô���±���ָ��Ϊ��ָ��


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