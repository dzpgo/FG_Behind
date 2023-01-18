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
		//	功能：获取Tag系统的唯一实例。
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：如果没有发生异常，返回tag系统的唯一实例对象
		//	参数：无
		static Tag& GetInst();			// Singleton tag instance
		
		// 启动定周期采集任务
		::Ice::Int StartCyclic(void);						

		// 停止定周期采集任务
		::Ice::Int StopCyclic(void);

		//	功能：注册事件主题及其关心的事件点
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：0：成功，1：失败
		//	参数： 
		//	objStatusWatcher：传入参数，WatchWithDataInterfacePtr对象
		//	tagEventNames：传入参数，需要注册的事件点名的对象。该参数为空或不传，表明所有事件都接收
		::Ice::Int RegisterEventWatch(const iPlature::WatchWithDataInterfacePtr& objStatusWatcher, 
			const ::iPlature::TAGNAMEARRAY& tagEventNames = ::iPlature::TAGNAMEARRAY());

		//	功能：注册事件主题及其关心的事件点
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：0：成功，1：失败
		//	参数： 
		//	objStatusWatcher：传入参数，WatchInterfacePtr对象
		//	tagEventNames：传入参数，需要注册的事件点名的对象。该参数为空或不传，表明所有事件都接收
		//::Ice::Int RegisterEventWatch(const iPlature::WatchInterfacePtr& objStatusWatcher, 
		//	const ::iPlature::TAGNAMEARRAY& tagEventNames = ::iPlature::TAGNAMEARRAY());
		
		//	功能：去除已注册的事件主题及其关心的事件点
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：0：成功，1：失败
		//	参数： 无
		::Ice::Int UnRegisterEventWatch(void);

		//	功能：注册周期主题，添加订阅周期主题的进程数，用于MD类型数据的进程间同步
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：0：成功，1：失败
		//	参数： 无
		//	objStatusWatcher：传入参数，WatchInterfacePtr对象
		//	tagEventNames：传入参数，需要MD类型数据同步处理的时钟名称序列。该参数为空或不传，表明不需要做MD类型数据的同步处理
		::Ice::Int RegisterTimerWatch(const iPlature::TimerEventInterfacePtr& objStatusWatcher, 
			const ::iPlature::TAGNAMEARRAY& tagTimerNames = ::iPlature::TAGNAMEARRAY());

		//	功能：减少订阅周期主题的进程数，用于MD类型数据的进程间同步
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：0：成功，1：失败
		//	参数： 无
		//::Ice::Int UnRegisterTimerWatch(void);

		//	功能：根据tag点名称获取其当前值
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagNames：传入参数，需要获取值的tag点名称的vector对象
		//	tagPairs：传出参数，保存tag点名称和其值的map对象
		::Ice::Int GetActual(const ::iPlature::TAGNAMEARRAY& tagNames, ::iPlature::TAGVALUEMAP& tagPairs);

		//	功能：向Tag系统周期性更新数据
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagPairs：传入参数，保存tag点名称和其值的map对象
		::Ice::Int CyclicPut(const ::iPlature::TAGVALUEMAP& tagPairs);

		//	功能：向Tag系统更新事件触发数据，产生一个事件激励信号
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagPairs：传入参数，保存数据tag点名称和其值的map对象
		//	eventName：传入参数，定义为EV类型的tag点名称，唯一确定了一个事件信号
		//	eventValue：传入参数，EV类型tag点的值
		::Ice::Int EventPut(const ::iPlature::TAGVALUEMAP& tagPairs, const ::std::string& eventName, const ::std::string& eventValue);

		//	功能：根据时间戳向Tag系统更新tag值
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagTimeStamp：传入参数，保存时间戳的map
		//	tagPairs：传入参数，保存tag点名称和其值的map对象
		::Ice::Int MDPut(const ::iPlature::TAGVALUEMAP& tagTimeStamp, const ::iPlature::TAGVALUEMAP& tagPairs);
	
		//	功能：根据时间戳向Tag系统发送应用处理结束信号
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagTimeStamp：传入参数，保存时间戳的map
		::Ice::Int MDPutEnd(const ::iPlature::TAGVALUEMAP& tagTimeStamp);

		//	功能：向Tag系统更新L1数据，此类数据会被写入到L1系统
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagPairs：传入参数，保存tag点名称和其值的map对象
		//	nType：传入参数，OPC写方式，目前只实现了方式一，固定填1
		::Ice::Int Write2Level1(const ::iPlature::TAGVALUEMAP& tagPairs, ::Ice::Int nType);

		//	功能：根据tag点名称获取其缓存值
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：无
		//	参数： 
		//	strName：传入参数，tag点名称
		//	nOffset：传入参数，相对当前时间的偏移量，单位为秒
		//	nPeriod：传入参数，相对于偏移值的取值时间跨度，单位为秒
		//	tagValue：传出参数，按照时间（从旧到新）的值序列
		void GetCache(const ::std::string& strName,	::Ice::Int nOffset,	::Ice::Int nPeriod,	::iPlature::TAGNAMEARRAY& tagValue);

		//	功能：根据基准时间和偏移时间获取Tag系统历史数据
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagNameList：传入参数，需要获取值的tag点名称的vector对象
		//	nAct：传入参数，二次计算类型，参见t_bm_tag_dbaction_define定义
		//	strInterval：传入参数，时钟信号名称，表示存储时间间隔
		//	strDateTime：传入参数，基准时间。应用系统和Tag系统存在着时钟差异，考虑到同步问题，在以当前时间做为基准时间取值时，
		//				用1970年1月1日0点0分0秒表示当前时间。用14位的字符串表示时间，格式为：YYYYMMDDhhmmss。
		//				如1970年1月1日0点0分0秒表示为：19700101000000。
		//	nPeriod：传入参数，从基准时间开始偏移的时间，单位：秒。该值为正时，表示从基准时间到当前时间的偏移，
		//				为负表示基准时间之前的偏移，为0表示基准时间起往前最近的一次值.
		//	thv：传入参数，LEFTRIGHT在TagDefines.h中定义为枚举类型，代表取值边界类型，
		//				值：thvLeftOpenRightClose，thvLeftOpenRightOpen，thvLeftCloseRightOpen，thvLeftCloseRightClose
		//	mapHistory：传出参数，保存返回值的map，由一个tag名称对应一个TAGDBACTIONMAP对象，
		//				TAGDBACTIONMAP对象保存了action和cach对象的键值对，cache对象按照时间序列保存了该tag点对应的action的所有值
		::Ice::Int GetHistoryBasePeriod(const ::iPlature::TAGNAMEARRAY& tagNameList,
										::Ice::Int nAct,
										const ::std::string& strInterval,
										const ::std::string& strDateTime,
										::Ice::Int nPeriod,
										::iPlature::LEFTRIGHT thv,
										::iPlature::TAGHISTORYMAP& mapHistory);

		//	功能：获取Tag系统中最新的历史数据
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagNameList：传入参数，需要获取值的tag点名称的vector对象
		//	nAct：传入参数，二次计算类型，参见t_bm_tag_dbaction_define定义。
		//	strInterval：传入参数，时钟信号名称，表示存储时间间隔。
		//	mapHistory：传出参数，保存返回值的map，由一个tag名称对应一个TAGDBACTIONMAP对象，
		//				TAGDBACTIONMAP对象保存了action和cach对象的键值对，cache对象按照时间序列保存了该tag点对应的action的所有值
		::Ice::Int GetHistoryBasePeriod(const ::iPlature::TAGNAMEARRAY& tagNameList,
										::Ice::Int nAct,
										const ::std::string& strInterval,
										::iPlature::TAGHISTORYMAP& mapHistory);

		//	功能：根据开始和偏移时间获取Tag系统历史数据
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagNameList：传入参数，需要获取值的tag点名称的vector对象。
		//	nAct：传入参数，二次计算类型，参见t_bm_tag_dbaction_define定义。
		//	strInterval：传入参数，时钟信号名称，表示存储时间间隔。
		//	strStart：传入参数，开始时间（格式：YYYYMMDDhhmmss）。
		//	strEnd：传入参数，结束时间（格式：YYYYMMDDhhmmss）。
		//	thv：传入参数，LEFTRIGHT在TagDefines.h中定义为枚举类型，代表取值边界类型，
		//			值：thvLeftOpenRightClose，thvLeftOpenRightOpen，thvLeftCloseRightOpen，thvLeftCloseRightClose。
		//	mapHistory：传出参数，保存返回值的map，由一个tag名称对应一个TAGDBACTIONMAP对象，
		//			TAGDBACTIONMAP对象保存了action和cach对象的键值对，cache对象按照时间序列保存了该tag点对应的action的所有值。
		::Ice::Int GetHistoryStartEnd(const ::iPlature::TAGNAMEARRAY& tagNameList,
									  ::Ice::Int nAct,
									  const ::std::string& strInterval,
									  const ::std::string& strStart,
									  const ::std::string& strEnd,
									  ::iPlature::LEFTRIGHT thv,
									  ::iPlature::TAGHISTORYMAP& mapHistory);

		//	功能：获取Tag系统中最新的历史数据
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	tagNameList：传入参数，需要获取值的tag点名称的vector对象。
		//	nAct：传入参数，二次计算类型，参见t_bm_tag_dbaction_define定义。
		//	strInterval：传入参数，时钟信号名称，表示存储时间间隔。
		//	mapHistory：传出参数，保存返回值的map，由一个tag名称对应一个TAGDBACTIONMAP对象，
		//			TAGDBACTIONMAP对象保存了action和cach对象的键值对，cache对象按照时间序列保存了该tag点对应的action的所有值。
		::Ice::Int GetHistoryStartEnd(const ::iPlature::TAGNAMEARRAY& tagNameList,
									::Ice::Int nAct,
									const ::std::string& strInterval,
									::iPlature::TAGHISTORYMAP& mapHistory);

		//	功能：允许/不允许指定tag点的数据库存储
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	bFlag：传入参数，数据库存储标志，为true时允许存储，false不允许
		//	tagNameList：传入参数，需要操作的tag点名列表
		::Ice::Int EnableArchive(bool bFlag, const ::iPlature::TAGNAMEARRAY& tagNameList);

		//	功能：允许/不允许所有tag点的数据库存储
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
		//	参数： 
		//	bFlag：传入参数，数据库存储标志，为true时允许存储，false不允许
		::Ice::Int EnableAllArchives(bool bFlag);

		//	功能：重新读取所有配置
		//	所需头文件：tag.h
		//	所需库文件：tag.lib
		//	返回：返回值为0（暂时未用）
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
	*  类      名:   	TagAppTimerBase、TagAppEventBase
	*  版权所有:   Shanghai Baosight Software Co., Ltd.
	*  类 职 责：提供给使用Tag的应用的父类，需要接收Event信号和Timer信号
	*  版本历史		
	*       1.0    2009-11-09    lumengyi    创建
	*     
	*********************************************************************/
	class TagAppTimerBase:virtual public ::iPlature::TimerEventInterface
	{
	protected:
		virtual void OnTimerEvent(const ::iPlature::TAGVALUEMAP& tagPairs, ::Ice::Int nCount, const Ice::Current&);
	public:
		/**********************************************************************
		 *  概述: 发布周期信号，应用需要实现该接口
		 *  函数名： OnTimerEvent 
		 *  返回值： void	 	//TODO:返回值描述
		 *  参数列表：	参数类型    							取值范围     		    描述
		 *    tagPairs:	[IN] const ::iPlature::TAGVALUEMAP &	//TODO:参数取值范围		时钟名称及其值的map对象
		 *    nCount  : [IN] ::Ice::Int							//TODO:参数取值范围		当前时刻需要发布时钟的个数
		 *
		 *  版本历史		
		 *       1.0    2009-11-09  jacklu    实现功能
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
		 *  概述: 发布事件信号，应用需要实现该接口
		 *  函数名： EventWatchWithData 
		 *  返回值： void	 	//TODO:返回值描述
		 *  参数列表：		参数类型    							取值范围     		    描述
		 *    tagValues  :  [IN] const ::iPlature::TAGVALUEMAP &	//TODO:参数取值范围		和指定事件信号关联的tag点名称及其值的map对象
		 *    strEventName:	[IN] const ::std::string &				//TODO:参数取值范围		EV类型的tag点名称，唯一确定了一个事件信号
		 *    strValue  :   [IN] const ::std::string &				//TODO:参数取值范围		EV类型tag点的值
		 *
		 *  版本历史		
		 *       1.0    2009-11-09  jacklu    实现功能
		 *  
		 **********************************************************************/
		virtual void EventWatchWithData(const ::iPlature::TAGVALUEMAP& tagValues,const ::std::string& strEventName, const ::std::string& strValue) = 0;
	};
}//namespace iPlature

