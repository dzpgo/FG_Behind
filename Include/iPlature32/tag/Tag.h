/********************************************************************
	created:	2008/01/19
	created:	19:1:2008   11:37
	file base:	Tag
	file ext:	h
	author:		zhaoyan
	
	purpose:	Tag Interface Wrapper Class for C++

	Usage:		::iPlature::Tag::GetInst().StartCyclic()
*********************************************************************/

#pragma once

#include "tag/Admin.h"
#include "tag/Cache.h"
#include "tag/Viewer.h"
#include "tag/Watch.h"
#include "tag/WatchWithData.h"
#include "tag/TagMonitor.h"
#include "tag/TimerEvent.h"
#include "tag/TagDefines.h"
#include "tag/TagDefinesMore.h"
#include "tag/TagAdapter.h"

namespace iPlature
{
	class Tag : private IceUtil::noncopyable
	{
		friend class TagAppTimerBase;
		friend class TagAppEventBase;

		Tag(void);						// Disable default constructor
		Tag(const Tag&);				// Disable copy constructor
		Tag& operator=(const Tag&);		// Disable evaluate operation
		~Tag(void);

		static Tag* m_pTagInstance;		// Tag wrapper instance
		static bool m_bDestroyed;		// Instance destroy flag

		::iPlature::AdminInterfacePrx	m_tagAdmin;			// TagAdmin service proxy
		::iPlature::CacheInterfacePrx	m_tagCache;			// TagCache service proxy
		::iPlature::ViewerInterfacePrx	m_tagViewer;		// TagViewer service proxy

		std::string m_strTopicName;
		std::string m_strEventTopicName;

		iPlature::AdapterInterfacePrx m_tagAdapter;		// TagAdapter service proxy

		::iPlature::TAGNAMEARRAY m_tagTimerNames;
		::iPlature::TAGNAMEARRAY m_tagEventNames;

		static void Create(void);			// Create the only one
		static void OnDeadReference(void);	// Dead reference handler after creation of the instance
		std::string GetLocalIP(void);		// Get local IP
		std::string GetProcessName(void);	// Get process name
		std::string GetProcessID(void);		// Get process ID
		std::string GetTopicName(void);		// Get topic name
		std::string GetEventTopicName(void);		// Get topic name

	public:
		//	���ܣ���ȡTagϵͳ��Ψһʵ����
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ����û�з����쳣������tagϵͳ��Ψһʵ������
		//	��������
		static Tag& GetInst();			// Singleton tag instance
		
		// ���������ڲɼ�����
		::Ice::Int StartCyclic(void);						

		// ֹͣ�����ڲɼ�����
		::Ice::Int StopCyclic(void);

		//	���ܣ�ע���¼����⼰����ĵ��¼���
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�0���ɹ���1��ʧ��
		//	������ 
		//	objStatusWatcher�����������WatchWithDataInterfacePtr����
		//	tagEventNames�������������Ҫע����¼������Ķ��󡣸ò���Ϊ�ջ򲻴������������¼�������
		::Ice::Int RegisterEventWatch(const iPlature::WatchWithDataInterfacePtr& objStatusWatcher, 
			const ::iPlature::TAGNAMEARRAY& tagEventNames = ::iPlature::TAGNAMEARRAY());

		//	���ܣ�ע���¼����⼰����ĵ��¼���
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�0���ɹ���1��ʧ��
		//	������ 
		//	objStatusWatcher�����������WatchInterfacePtr����
		//	tagEventNames�������������Ҫע����¼������Ķ��󡣸ò���Ϊ�ջ򲻴������������¼�������
		//::Ice::Int RegisterEventWatch(const iPlature::WatchInterfacePtr& objStatusWatcher, 
		//	const ::iPlature::TAGNAMEARRAY& tagEventNames = ::iPlature::TAGNAMEARRAY());
		
		//	���ܣ�ȥ����ע����¼����⼰����ĵ��¼���
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�0���ɹ���1��ʧ��
		//	������ ��
		::Ice::Int UnRegisterEventWatch(void);

		//	���ܣ�ע���������⣬��Ӷ�����������Ľ�����������MD�������ݵĽ��̼�ͬ��
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�0���ɹ���1��ʧ��
		//	������ ��
		//	objStatusWatcher�����������WatchInterfacePtr����
		//	tagEventNames�������������ҪMD��������ͬ�������ʱ���������С��ò���Ϊ�ջ򲻴�����������Ҫ��MD�������ݵ�ͬ������
		::Ice::Int RegisterTimerWatch(const iPlature::TimerEventInterfacePtr& objStatusWatcher, 
			const ::iPlature::TAGNAMEARRAY& tagTimerNames = ::iPlature::TAGNAMEARRAY());

		//	���ܣ����ٶ�����������Ľ�����������MD�������ݵĽ��̼�ͬ��
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�0���ɹ���1��ʧ��
		//	������ ��
		//::Ice::Int UnRegisterTimerWatch(void);

		//	���ܣ�����tag�����ƻ�ȡ�䵱ǰֵ
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagNames�������������Ҫ��ȡֵ��tag�����Ƶ�vector����
		//	tagPairs����������������tag�����ƺ���ֵ��map����
		::Ice::Int GetActual(const ::iPlature::TAGNAMEARRAY& tagNames, ::iPlature::TAGVALUEMAP& tagPairs);

		//	���ܣ���Tagϵͳ�����Ը�������
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagPairs���������������tag�����ƺ���ֵ��map����
		::Ice::Int CyclicPut(const ::iPlature::TAGVALUEMAP& tagPairs);

		//	���ܣ���Tagϵͳ�����¼��������ݣ�����һ���¼������ź�
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagPairs�������������������tag�����ƺ���ֵ��map����
		//	eventName���������������ΪEV���͵�tag�����ƣ�Ψһȷ����һ���¼��ź�
		//	eventValue�����������EV����tag���ֵ
		::Ice::Int EventPut(const ::iPlature::TAGVALUEMAP& tagPairs, const ::std::string& eventName, const ::std::string& eventValue);

		//	���ܣ�����ʱ�����Tagϵͳ����tagֵ
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagTimeStamp���������������ʱ�����map
		//	tagPairs���������������tag�����ƺ���ֵ��map����
		::Ice::Int MDPut(const ::iPlature::TAGVALUEMAP& tagTimeStamp, const ::iPlature::TAGVALUEMAP& tagPairs);
	
		//	���ܣ�����ʱ�����Tagϵͳ����Ӧ�ô�������ź�
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagTimeStamp���������������ʱ�����map
		::Ice::Int MDPutEnd(const ::iPlature::TAGVALUEMAP& tagTimeStamp);

		//	���ܣ���Tagϵͳ����L1���ݣ��������ݻᱻд�뵽L1ϵͳ
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagPairs���������������tag�����ƺ���ֵ��map����
		//	nType�����������OPCд��ʽ��Ŀǰֻʵ���˷�ʽһ���̶���1
		::Ice::Int Write2Level1(const ::iPlature::TAGVALUEMAP& tagPairs, ::Ice::Int nType);

		//	���ܣ�����tag�����ƻ�ȡ�仺��ֵ
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ���
		//	������ 
		//	strName�����������tag������
		//	nOffset�������������Ե�ǰʱ���ƫ��������λΪ��
		//	nPeriod����������������ƫ��ֵ��ȡֵʱ���ȣ���λΪ��
		//	tagValue����������������ʱ�䣨�Ӿɵ��£���ֵ����
		void GetCache(const ::std::string& strName,	::Ice::Int nOffset,	::Ice::Int nPeriod,	::iPlature::TAGNAMEARRAY& tagValue);

		//	���ܣ����ݻ�׼ʱ���ƫ��ʱ���ȡTagϵͳ��ʷ����
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagNameList�������������Ҫ��ȡֵ��tag�����Ƶ�vector����
		//	nAct��������������μ������ͣ��μ�t_bm_tag_dbaction_define����
		//	strInterval�����������ʱ���ź����ƣ���ʾ�洢ʱ����
		//	strDateTime�������������׼ʱ�䡣Ӧ��ϵͳ��Tagϵͳ������ʱ�Ӳ��죬���ǵ�ͬ�����⣬���Ե�ǰʱ����Ϊ��׼ʱ��ȡֵʱ��
		//				��1970��1��1��0��0��0���ʾ��ǰʱ�䡣��14λ���ַ�����ʾʱ�䣬��ʽΪ��YYYYMMDDhhmmss��
		//				��1970��1��1��0��0��0���ʾΪ��19700101000000��
		//	nPeriod������������ӻ�׼ʱ�俪ʼƫ�Ƶ�ʱ�䣬��λ���롣��ֵΪ��ʱ����ʾ�ӻ�׼ʱ�䵽��ǰʱ���ƫ�ƣ�
		//				Ϊ����ʾ��׼ʱ��֮ǰ��ƫ�ƣ�Ϊ0��ʾ��׼ʱ������ǰ�����һ��ֵ.
		//	thv�����������LEFTRIGHT��TagDefines.h�ж���Ϊö�����ͣ�����ȡֵ�߽����ͣ�
		//				ֵ��thvLeftOpenRightClose��thvLeftOpenRightOpen��thvLeftCloseRightOpen��thvLeftCloseRightClose
		//	mapHistory���������������淵��ֵ��map����һ��tag���ƶ�Ӧһ��TAGDBACTIONMAP����
		//				TAGDBACTIONMAP���󱣴���action��cach����ļ�ֵ�ԣ�cache������ʱ�����б����˸�tag���Ӧ��action������ֵ
		::Ice::Int GetHistoryBasePeriod(const ::iPlature::TAGNAMEARRAY& tagNameList,
										::Ice::Int nAct,
										const ::std::string& strInterval,
										const ::std::string& strDateTime,
										::Ice::Int nPeriod,
										::iPlature::LEFTRIGHT thv,
										::iPlature::TAGHISTORYMAP& mapHistory);

		//	���ܣ���ȡTagϵͳ�����µ���ʷ����
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagNameList�������������Ҫ��ȡֵ��tag�����Ƶ�vector����
		//	nAct��������������μ������ͣ��μ�t_bm_tag_dbaction_define���塣
		//	strInterval�����������ʱ���ź����ƣ���ʾ�洢ʱ������
		//	mapHistory���������������淵��ֵ��map����һ��tag���ƶ�Ӧһ��TAGDBACTIONMAP����
		//				TAGDBACTIONMAP���󱣴���action��cach����ļ�ֵ�ԣ�cache������ʱ�����б����˸�tag���Ӧ��action������ֵ
		::Ice::Int GetHistoryBasePeriod(const ::iPlature::TAGNAMEARRAY& tagNameList,
										::Ice::Int nAct,
										const ::std::string& strInterval,
										::iPlature::TAGHISTORYMAP& mapHistory);

		//	���ܣ����ݿ�ʼ��ƫ��ʱ���ȡTagϵͳ��ʷ����
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagNameList�������������Ҫ��ȡֵ��tag�����Ƶ�vector����
		//	nAct��������������μ������ͣ��μ�t_bm_tag_dbaction_define���塣
		//	strInterval�����������ʱ���ź����ƣ���ʾ�洢ʱ������
		//	strStart�������������ʼʱ�䣨��ʽ��YYYYMMDDhhmmss����
		//	strEnd���������������ʱ�䣨��ʽ��YYYYMMDDhhmmss����
		//	thv�����������LEFTRIGHT��TagDefines.h�ж���Ϊö�����ͣ�����ȡֵ�߽����ͣ�
		//			ֵ��thvLeftOpenRightClose��thvLeftOpenRightOpen��thvLeftCloseRightOpen��thvLeftCloseRightClose��
		//	mapHistory���������������淵��ֵ��map����һ��tag���ƶ�Ӧһ��TAGDBACTIONMAP����
		//			TAGDBACTIONMAP���󱣴���action��cach����ļ�ֵ�ԣ�cache������ʱ�����б����˸�tag���Ӧ��action������ֵ��
		::Ice::Int GetHistoryStartEnd(const ::iPlature::TAGNAMEARRAY& tagNameList,
									  ::Ice::Int nAct,
									  const ::std::string& strInterval,
									  const ::std::string& strStart,
									  const ::std::string& strEnd,
									  ::iPlature::LEFTRIGHT thv,
									  ::iPlature::TAGHISTORYMAP& mapHistory);

		//	���ܣ���ȡTagϵͳ�����µ���ʷ����
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	tagNameList�������������Ҫ��ȡֵ��tag�����Ƶ�vector����
		//	nAct��������������μ������ͣ��μ�t_bm_tag_dbaction_define���塣
		//	strInterval�����������ʱ���ź����ƣ���ʾ�洢ʱ������
		//	mapHistory���������������淵��ֵ��map����һ��tag���ƶ�Ӧһ��TAGDBACTIONMAP����
		//			TAGDBACTIONMAP���󱣴���action��cach����ļ�ֵ�ԣ�cache������ʱ�����б����˸�tag���Ӧ��action������ֵ��
		::Ice::Int GetHistoryStartEnd(const ::iPlature::TAGNAMEARRAY& tagNameList,
									::Ice::Int nAct,
									const ::std::string& strInterval,
									::iPlature::TAGHISTORYMAP& mapHistory);

		//	���ܣ�����/������ָ��tag������ݿ�洢
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	bFlag��������������ݿ�洢��־��Ϊtrueʱ����洢��false������
		//	tagNameList�������������Ҫ������tag�����б�
		::Ice::Int EnableArchive(bool bFlag, const ::iPlature::TAGNAMEARRAY& tagNameList);

		//	���ܣ�����/����������tag������ݿ�洢
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		//	������ 
		//	bFlag��������������ݿ�洢��־��Ϊtrueʱ����洢��false������
		::Ice::Int EnableAllArchives(bool bFlag);

		//	���ܣ����¶�ȡ��������
		//	����ͷ�ļ���tag.h
		//	������ļ���tag.lib
		//	���أ�����ֵΪ0����ʱδ�ã�
		::Ice::Int ReReadConfiguration(void);

		::Ice::Int AdapterGetActual(const std::string & adapterName, const ::iPlature::TAGNAMEARRAY& tagNames,	::iPlature::TAGVALUEMAP& tagPairs);
		::Ice::Int AdapterCyclicPut(const std::string & adapterName, const ::iPlature::TAGVALUEMAP& tagPairs);
		::Ice::Int AdapterEventPut(const std::string & adapterName, const ::iPlature::TAGVALUEMAP& tagPairs, const ::std::string& eventName, const ::std::string& eventValue);
		::Ice::Int AdapterMDPut(const std::string & adapterName, const ::iPlature::TAGVALUEMAP& tagTimeStamp, const ::iPlature::TAGVALUEMAP& tagPairs);
		::Ice::Int AdapterWrite2Level1(const std::string & adapterName, const ::iPlature::TAGVALUEMAP& tagPairs, ::Ice::Int nType);
		::Ice::Int AdapterEnableArchive(const std::string & adapterName, bool bFlag, const ::iPlature::TAGNAMEARRAY& tagNameList);
		::Ice::Int AdapterEnableAllArchives(const std::string & adapterName, bool bFlag);
	};

	/*********************************************************************
	*  ��      ��:   	TagAppTimerBase��TagAppEventBase
	*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
	*  �� ְ ���ṩ��ʹ��Tag��Ӧ�õĸ��࣬��Ҫ����Event�źź�Timer�ź�
	*  �汾��ʷ		
	*       1.0    2009-11-09    lumengyi    ����
	*     
	*********************************************************************/
	class TagAppTimerBase:virtual public ::iPlature::TimerEventInterface
	{
	protected:
		virtual void OnTimerEvent(const ::iPlature::TAGVALUEMAP& tagPairs, ::Ice::Int nCount, const Ice::Current&);
	public:
		/**********************************************************************
		 *  ����: ���������źţ�Ӧ����Ҫʵ�ָýӿ�
		 *  �������� OnTimerEvent 
		 *  ����ֵ�� void	 	//TODO:����ֵ����
		 *  �����б�	��������    							ȡֵ��Χ     		    ����
		 *    tagPairs:	[IN] const ::iPlature::TAGVALUEMAP &	//TODO:����ȡֵ��Χ		ʱ�����Ƽ���ֵ��map����
		 *    nCount  : [IN] ::Ice::Int							//TODO:����ȡֵ��Χ		��ǰʱ����Ҫ����ʱ�ӵĸ���
		 *
		 *  �汾��ʷ		
		 *       1.0    2009-11-09  jacklu    ʵ�ֹ���
		 *  
		 **********************************************************************/
		virtual void OnTimerEvent(const ::iPlature::TAGVALUEMAP& tagPairs, ::Ice::Int nCount) = 0;
	};

	class TagAppEventBase:virtual public ::iPlature::WatchWithDataInterface
	{
	protected:
		virtual void EventWatchWithData(const ::iPlature::TAGVALUEMAP& tagValues,const ::std::string& strEventName, const ::std::string& strValue,  const ::Ice::Current&);
	public:
		/**********************************************************************
		 *  ����: �����¼��źţ�Ӧ����Ҫʵ�ָýӿ�
		 *  �������� EventWatchWithData 
		 *  ����ֵ�� void	 	//TODO:����ֵ����
		 *  �����б�		��������    							ȡֵ��Χ     		    ����
		 *    tagValues  :  [IN] const ::iPlature::TAGVALUEMAP &	//TODO:����ȡֵ��Χ		��ָ���¼��źŹ�����tag�����Ƽ���ֵ��map����
		 *    strEventName:	[IN] const ::std::string &				//TODO:����ȡֵ��Χ		EV���͵�tag�����ƣ�Ψһȷ����һ���¼��ź�
		 *    strValue  :   [IN] const ::std::string &				//TODO:����ȡֵ��Χ		EV����tag���ֵ
		 *
		 *  �汾��ʷ		
		 *       1.0    2009-11-09  jacklu    ʵ�ֹ���
		 *  
		 **********************************************************************/
		virtual void EventWatchWithData(const ::iPlature::TAGVALUEMAP& tagValues,const ::std::string& strEventName, const ::std::string& strValue) = 0;
	};
}//namespace iPlature

