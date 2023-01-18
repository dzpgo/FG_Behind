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
		* 默认构造器
		*/
		CWatchEventHandlerI(string theCraneNO);
	public:
		/** 
		* 析构
		*/
		~CWatchEventHandlerI(void);

	public:
		/** 
		* 该主题接口上的操作定义
		* @param[in] tagValueMap和指定事件信号关联的tag点名称及其值的map对象
		* @param[in] strEventName定义为EV类型的tag点名称，唯一确定了一个事件信号
		* @param[in] strValue EV类型tag点的值
		* @return void
		* 
		*/
		virtual void EventWatchWithData(const iPlature::TAGVALUEMAP& tagValueMap,
														const std::string& strEventName,
														const std::string& strValue,
														const Ice::Current&);
	private:
	
		string craneNO;

		IceUtil::Mutex	m_mutexValue;	//保护参数值的互斥体

		string eventTagName_Evade_Request;
		string eventTagName_Evade_Cancel;



	};
}
