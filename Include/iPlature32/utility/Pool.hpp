/*********************************************************************
*		
*  文      件:    Pool.hpp
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述： 通用存储池，支持阻塞方式和非阻塞方式，若使用了默认的互斥体，即
*		  IceUtil::RecMutex和IceUtil::Monitor，请在编译时添加IceUtil(d).lib库
*
*		  使用方法：
*		  typedef Pool<iDA::Connection> iDAConnectionPool;
*		  //默认是非阻塞方式的，若要想改成阻塞方式
*		  //typedef Pool<iDA::Connection,Block<>> iDAConnectionPool;
*         //若同时使用iDAConnectionCreation构建
*		  //typedef Pool<iDA::Connection ,Block<> ,iDAConnectionCreation> iDAConnectionPool;
*
*		  //若希望使用单件,可配合Singleton模式。
*		  typedef SingletonHolder<iDAConnectionPool> PoolMgr;
*
*		  //fetch方法从池中获取资源
*		  iDA::Connection& cn = PoolMgr::getInstance().fetch();
*
*         //release方法释放资源回池
*		  PoolMgr::getInstance().release(cn);
*
*
*
*  版本历史		
*      1.0    2009-12-14    lumengyi    仅仅是实现了一个思路，将来可实现更多的策略：可替换
*										的核心数据结构、自动增长、废弃后自动回收、阻塞后超
*										时、具名对象等。
*	   1.01   2009-12-16    lumengyi    增加了一个iDA连接的构建策略类iDAConnectionCreation
										若使用该类，请在编译时添加iDA(R).lib库
*     
*********************************************************************/
#ifndef __POOL_HPP__
#define __POOL_HPP__
#include <list>
#include <IceUtil/RecMutex.h>
#include <IceUtil/Monitor.h>
namespace iPlature
{
	namespace Tools
	{
		///////////////////////Exception////////////////////////////////////////
		class PoolException
		{
		public:
			PoolException(const std::string& sErrMsg):_ErrMsg(sErrMsg){}
			virtual ~PoolException(){}

			std::string ErrMsg() const
			{
				return _ErrMsg;
			}
		private:
			std::string _ErrMsg;
		};
		///////////////////////构建时的策略/////////////////////////////////////
		//默认的构建方式，若希望有自己构建方式，可自定制
		template<class Object>
		struct ObjectCreationDefault
		{
			static Object* Create()
			{
				return new Object();
			}
			
			static void Destroy(Object* pObj)
			{
				if(pObj) 
				{
					delete pObj;
					pObj = NULL;
				}
			}

			static void Check(Object* pObj)
			{
				//do nothing
			}
		};
		///////////////////////池不足时的策略/////////////////////////////////////
		//方式一：非阻塞且抛出异常（默认模式）
		struct NonBlock{};

		//方式二：阻塞且等待可用
		template<template<class>class MonitorType = IceUtil::Monitor>
		struct Block{};
		//////////////////////////////////////////////////////////////////////////
		template <class MutexType,class LackPolicy>
		struct LackTraits;

		template<class MutexType>
		struct LackTraits<MutexType,NonBlock>
		{
			typedef MutexType MutexObject;
			typedef typename MutexType::Lock Lock;
			static void inLack(MutexObject&)
			{
				throw PoolException("Pool is out of stock now!");
			}
			static void notify(MutexObject&)
			{
				//do nothing
			}
		};

		template<class MutexType,template<class>class MonitorType>
		struct LackTraits<MutexType,Block<MonitorType> >
		{
			typedef MonitorType<MutexType> MutexObject;
			typedef typename MonitorType<MutexType>::Lock Lock;
			static void inLack(MutexObject& mutexObj)
			{
				mutexObj.wait();
			}
			static void notify(MutexObject& mutexObj)
			{
				mutexObj.notify();
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template <class Object,
			      class LackPolicy = NonBlock,
			      template<class>class CreationPolicy = ObjectCreationDefault,
				  class MutexType = IceUtil::RecMutex,
				  typename LackPolicyTraits = LackTraits<MutexType,LackPolicy>
				  >
		class Pool
		{
		public:
			Pool()
			{
				_isInitialized = false;
			}
			~Pool()
			{
				destroy();
			}
			void initialize(unsigned int nPoolSize = 1)
			{
				if(_isInitialized)
				{
					throw PoolException("Pool is already Initialized.");
				}
				else
				{
					_isInitialized = true;
					_PoolSize = nPoolSize;
				}
			}
			void destroy()
			{
				while(!_freePool.empty())
				{
					ObjectCreationDefault<Object>::Destroy(_freePool.front());
					_freePool.pop_front();
				}
				while(!_reservePool.empty())
				{
					ObjectCreationDefault<Object>::Destroy(_reservePool.front());
					_reservePool.pop_front();
				}
				_isInitialized = false;
			}
			Object& fetch()
			{
				//加锁
				typename LackPolicyTraits::Lock lock(_mutex);

				Object* obj = NULL;
				//若空闲队列里有剩余，优先使用空闲队列里的
				if (_freePool.size() > 0)
				{
					obj = _freePool.front();
					_freePool.pop_front();
					_reservePool.push_back(obj);
					return *obj;
				}

				//若池中还有剩余空间
				if (availableNo() > 0)
				{
					obj = CreationPolicy<Object>::Create();
					_reservePool.push_back(obj);
					return *obj;
				}
				//若已经到达池上限
				else
				{
					LackPolicyTraits::inLack(_mutex);
					//肯定是空闲队列中有了新数据，再去空闲队列中去取
					assert(_freePool.size() > 0);

					obj = _freePool.front();
					_freePool.pop_front();
					_reservePool.push_back(obj);
					return *obj;
				}
			}
			void release(Object& obj)
			{
				//加锁
				typename LackPolicyTraits::Lock lock(_mutex);

				//先检查状态
				CreationPolicy<Object>::Check(&obj);

				//搜寻_reservePool，看是否存在该Object
				for (typename std::list<Object*>::iterator iter = _reservePool.begin();
					iter != _reservePool.end(); ++iter)
				{
					if (&obj == *iter)
					{
						_freePool.push_back(&obj);
						_reservePool.erase(iter);
						if (1 == availableNo())
						{
							LackPolicyTraits::notify(_mutex);
						}
						return;
					}
				}

				throw PoolException("Release which not existing in pool!");
			}
			unsigned int availableNo()
			{
				return _PoolSize - _reservePool.size();
			}
		private:
			std::list<Object*> _freePool;
			std::list<Object*> _reservePool;
			bool _isInitialized;
			unsigned int _PoolSize;
			typename LackPolicyTraits::MutexObject _mutex;
		};
	}//namespace Tools
}//namespace iPlature

#ifndef NO_USE_IDA
#include <iDA/iDA.h>
namespace iPlature
{
	namespace Tools
	{
		//iDA连接的创建方式
		template<class Object>
		struct iDAConnectionCreation
		{
			static Object* Create()
			{
				Object* pObj = NULL;
				pObj = new Object();
				pObj->Connect(_sDBString,_sUserName,_sPassword,_eClient);
				return pObj;
			}

			static void Destroy(Object* pObj)
			{
				if(pObj) 
				{
					if (pObj->IsConnected())
					{
						pObj->Disconnect();
					}
					delete pObj;
					pObj = NULL;
				}
			}

			static void Check(Object* pObj)
			{
				if (pObj && !pObj->IsConnected())
				{
					pObj->Connect(_sDBString,_sUserName,_sPassword,_eClient);
				}
			}

			static void SetDBProPerty(const std::string& sDBString,
				const std::string& sUserName,
				const std::string& sPassword,
				iPlature::iDA::iDA_Client_t eClient)
			{
				_sDBString = sDBString;
				_sUserName = sUserName;
				_sPassword = sPassword;
				_eClient = eClient;
			}
		private:
			static std::string _sDBString;
			static std::string _sUserName;
			static std::string _sPassword;
			static iPlature::iDA::iDA_Client_t _eClient;
		};
		template<class Object>
		std::string iDAConnectionCreation<Object>::_sDBString = "iPlature";
		template<class Object>
		std::string iDAConnectionCreation<Object>::_sUserName = "auth";
		template<class Object>
		std::string iDAConnectionCreation<Object>::_sPassword = "auth";
		template<class Object>
		iPlature::iDA::iDA_Client_t iDAConnectionCreation<Object>::_eClient = iDA::iDA_Oracle_Client;
	}//namespace Tools
}//namespace iPlature
#endif

#endif