#pragma once

#include <tag/Tag.h>

namespace Monitor
{
	class CWatchEventHandlerI : virtual public iPlature::WatchWithDataInterface
	{
	public:
		/** 
		* Ĭ�Ϲ�����
		*/
		CWatchEventHandlerI(string logFileName);
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
	

		IceUtil::Mutex	m_mutexValue;	//��������ֵ�Ļ�����

		string mLogFileName;



	};
}
