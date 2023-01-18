#pragma once

#include <tag/Tag.h>

#include "MsgHMICRANE01.h"
#include "MsgHMICRANE02.h"
#include "EvadeCancelReceiver.h"
#include "EvadeRequestReceiver.h"
#include "Evade_Tag_Define.h"
#include "ACTION_COMMON_FUNCTION.h"
#include "SrsMsgRcvHandler.h"

namespace Monitor
{
	class CWatchEventHandlerI : virtual public iPlature::WatchWithDataInterface
	{
	public:
		/** 
		* Ĭ�Ϲ�����
		*/
		CWatchEventHandlerI(string theCraneNO);
	public:
		/** 
		* ����
		*/
		~CWatchEventHandlerI(void);

	public:
		/** 
		* ������ӿ��ϵĲ�������
		* @param[in] tagValueMap��ָ���¼��źŹ�����tag�����Ƽ���ֵ��map����
		* @param[in] strEventName����ΪEV���͵�tag�����ƣ�Ψһȷ����һ���¼��ź�
		* @param[in] strValue EV����tag���ֵ
		* @return void
		* 
		*/
		virtual void EventWatchWithData(const iPlature::TAGVALUEMAP& tagValueMap,
														const std::string& strEventName,
														const std::string& strValue,
														const Ice::Current&);
	private:
	
		string craneNO;

		IceUtil::Mutex	m_mutexValue;	//��������ֵ�Ļ�����

		string eventTagName_Evade_Request;
		string eventTagName_Evade_Cancel;



	};
}
