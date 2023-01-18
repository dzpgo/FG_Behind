/*********************************************************************
*		
*  文      件:    ObjectCache.h   		//TODO请概述文件功能
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：//TODO请添加本文件包含功能详细描述
*        ：//TODO
*        ：//TODO
*
*  版本历史		
*      1.0    2010-09-09    Haykin-2010    //TODO请添加本次主要修改内容
*      %USER%   
*********************************************************************/
#ifndef __PACE_OBJECTCACHE_H__
#define __PACE_OBJECTCACHE_H__
#include <pace/Component.h>
#include <log4cplus/LOG.h>
#include <pace/ClassFactory.h> 
//#include <pace/Util.h>
#include <pace/ExceptionTracer.h>
#include <pace/BaseObject.h>
#include <pace/ObjectCacheImpl.h>

namespace iPlature
{
class ObjectCacheException : public std::exception
{
public:
	ObjectCacheException(const std::string& strError)
		: _what(std::string("ObjectCacheException:") + strError){}
	virtual const char* what() const throw() { return _what.c_str();}
	virtual ~ObjectCacheException() throw(){}
private:
	std::string _what;
};

template <class T>
class ObjectCache
{
public:
    ObjectCache(const std::string& category);

    /**
     * @brief add a object into cache with object id.
     * @param object 
     * @param oid
     * @return found object proxy.
     */
    ::Ice::ObjectPrx add(const ::Ice::ObjectPtr& object,const std::string& oid )
    {
      return _pImpl->add(object, oid);
    }

	/**
	* @brief add a object into cache with object id. If it already exist, remove it first
	* @param object 
	* @param oid
	* @return found object proxy.
	*/
	::Ice::ObjectPrx put(const ::Ice::ObjectPtr& object,const std::string& oid )
	{
		return _pImpl->put(object, oid);
	}
     /**
      * @brief find a object proxy with a oid from cache. 
      * @param oid
      * @return found object proxy.
      */
    ::Ice::ObjectPrx lookup(const std::string& oid)
    {
		return _pImpl->lookup(oid);
    }
     /**
      * @brief 根据指定对象ID从Cache中得到对象代理，但是不保证代理的有效性。
      * @param oid
      * @return found object proxy.
      */
    ::Ice::ObjectPrx fastlookup(const std::string& oid)
    {
       return  _pImpl->fastlookup(oid);
    }
    /**
     * @brief get all object proxy identities from object cache.
     * @return object proxies sequence.
     */
	iPlature::StringSeq getAllObjectIds()
	{
		return _pImpl->getAllObjectIds();
    }
    /**
     * @brief get all object proxies from object cache.
     * @return object proxies sequence.
     */
	iPlature::ObjectProxySeq getAllObjects()
    {
       return _pImpl->getAllObjects();
    }
    /**
     * @brief get the count of objects with class T in the ObjectCache.
     * @return the count of objects cached.
     */
   int count() const
    {
		return _pImpl->count();
    }
    /**
     * @brief remove a object from cache and delete it from disk.
     * @param oid
     */
    void remove(const std::string& oid )
	{
		_pImpl->remove(oid);
    }
    /**
     * @brief make a object always in memory cache(locked),no evictored.
     * @param oid
     */
    void keep(const std::string& oid )
    {
        _pImpl->keep(oid);
    }
    /**
     * @brief release(unlock) a object which be kept by keep() method,
     *        make it can be evictor to disk database.
     * @param oid.
     */
    void release(const std::string& oid )
    {
       _pImpl->release(oid);
    }

	bool hasObject(const std::string& oid)
	{
		return _pImpl->hasObject(oid);
	}

private:
    static bool _initializing;
	ObjectCacheImpl* _pImpl;
};

template <typename T> 
bool ObjectCache<T>::_initializing = true;

template <typename T>
ObjectCache<T>::ObjectCache(const std::string& category)
{
	if(_initializing)
	{ 
		IceUtil::Mutex::Lock lock(*ObjectCacheImpl::ObjectCacheMutex());
		if(_initializing)
		{
			{
				T* obj = new T();
				iPlature::BaseObject* base = dynamic_cast<iPlature::BaseObject*>(obj);
				if(! base)
				{
					delete obj;
					throw ObjectCacheException("ObjectCache managed object must derived from iPlature::BaseObject!" );
				}
				delete obj;
			}
			//install class factory...
			Component::instance()->communicator()->addObjectFactory(new ClassFactory<T>(),T::ice_staticId());
			_initializing = false;
		}//inter check
	}//outer check

	_pImpl = ObjectCacheImpl::GetObjectCacheImpl(category);
}

}



#endif




