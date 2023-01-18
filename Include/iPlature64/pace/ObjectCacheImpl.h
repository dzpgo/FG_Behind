
/*********************************************************************
*  类      名:   	ObjectCacheImpl
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*  类 职 责： ObjectCache实现类
*  版本历史		
*       1.0    2011-04-01    Haykin-2010    //TODO请添加本次主要修改内容
*     
*********************************************************************/
#pragma once
#include <Ice/ObjectAdapter.h>
#include <IceUtil/RecMutex.h>
#include <Freeze/Freeze.h>
#include <Ice/ObjectAdapter.h>

namespace iPlature
{
	typedef std::vector< ::Ice::ObjectPrx > ObjectProxySeq;
	typedef std::vector<std::string> StringSeq;

	
	//extern ObjectCacheImpl_Init G_ObjectCacheImpl_Init;
	

	class ObjectCacheImpl
	{
	public:
		ObjectCacheImpl(const std::string& category);
		~ObjectCacheImpl(void);
	public:
		::Ice::ObjectPrx add(const ::Ice::ObjectPtr& object, const std::string& oid );
		::Ice::ObjectPrx put(const ::Ice::ObjectPtr& object, const std::string& oid );
		::Ice::ObjectPrx lookup(const std::string& oid);
		::Ice::ObjectPrx fastlookup(const std::string& oid);
		StringSeq getAllObjectIds();

		ObjectProxySeq getAllObjects();

		 void remove(const std::string& oid );

		 void keep(const std::string& oid );

		 void release(const std::string& oid );

		 Ice::ObjectPtr lookupObject(const std::string& oid);

		 bool hasObject(const std::string& oid);

		 int count();

		 static IceUtil::Mutex* ObjectCacheMutex();

		 static ObjectCacheImpl* GetObjectCacheImpl(const std::string& category);

		 bool deletable(const std::string& oid);

	private:
		Ice::Identity toIdentity(const std::string& oid);
	private:
		IceUtil::RecMutex _mtx;

#if ICE_INT_VERSION >= 30300
		Freeze::BackgroundSaveEvictorPtr _evictor;
#else
		Freeze::EvictorPtr _evictor;
#endif
		
		std::string _category;
		Ice::ObjectAdapterPtr _adapter;
		Ice::CommunicatorPtr _cmmtor;
		int _count;
	};
}

