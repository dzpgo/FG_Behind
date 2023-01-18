/*********************************************************************
*		
*  ��      ��:    Pool.hpp
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������ ͨ�ô洢�أ�֧��������ʽ�ͷ�������ʽ����ʹ����Ĭ�ϵĻ����壬��
*		  IceUtil::RecMutex��IceUtil::Monitor�����ڱ���ʱ���IceUtil(d).lib��
*
*		  ʹ�÷�����
*		  typedef Pool<iDA::Connection> iDAConnectionPool;
*		  //Ĭ���Ƿ�������ʽ�ģ���Ҫ��ĳ�������ʽ
*		  //typedef Pool<iDA::Connection,Block<>> iDAConnectionPool;
*         //��ͬʱʹ��iDAConnectionCreation����
*		  //typedef Pool<iDA::Connection ,Block<> ,iDAConnectionCreation> iDAConnectionPool;
*
*		  //��ϣ��ʹ�õ���,�����Singletonģʽ��
*		  typedef SingletonHolder<iDAConnectionPool> PoolMgr;
*
*		  //fetch�����ӳ��л�ȡ��Դ
*		  iDA::Connection& cn = PoolMgr::getInstance().fetch();
*
*         //release�����ͷ���Դ�س�
*		  PoolMgr::getInstance().release(cn);
*
*
*
*  �汾��ʷ		
*      1.0    2009-12-14    lumengyi    ������ʵ����һ��˼·��������ʵ�ָ���Ĳ��ԣ����滻
*										�ĺ������ݽṹ���Զ��������������Զ����ա�������
*										ʱ����������ȡ�
*	   1.01   2009-12-16    lumengyi    ������һ��iDA���ӵĹ���������iDAConnectionCreation
										��ʹ�ø��࣬���ڱ���ʱ���iDA(R).lib��
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
		///////////////////////����ʱ�Ĳ���/////////////////////////////////////
		//Ĭ�ϵĹ�����ʽ����ϣ�����Լ�������ʽ�����Զ���
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
		///////////////////////�ز���ʱ�Ĳ���/////////////////////////////////////
		//��ʽһ�����������׳��쳣��Ĭ��ģʽ��
		struct NonBlock{};

		//��ʽ���������ҵȴ�����
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
				//����
				typename LackPolicyTraits::Lock lock(_mutex);

				Object* obj = NULL;
				//�����ж�������ʣ�࣬����ʹ�ÿ��ж������
				if (_freePool.size() > 0)
				{
					obj = _freePool.front();
					_freePool.pop_front();
					_reservePool.push_back(obj);
					return *obj;
				}

				//�����л���ʣ��ռ�
				if (availableNo() > 0)
				{
					obj = CreationPolicy<Object>::Create();
					_reservePool.push_back(obj);
					return *obj;
				}
				//���Ѿ����������
				else
				{
					LackPolicyTraits::inLack(_mutex);
					//�϶��ǿ��ж��������������ݣ���ȥ���ж�����ȥȡ
					assert(_freePool.size() > 0);

					obj = _freePool.front();
					_freePool.pop_front();
					_reservePool.push_back(obj);
					return *obj;
				}
			}
			void release(Object& obj)
			{
				//����
				typename LackPolicyTraits::Lock lock(_mutex);

				//�ȼ��״̬
				CreationPolicy<Object>::Check(&obj);

				//��Ѱ_reservePool�����Ƿ���ڸ�Object
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
		//iDA���ӵĴ�����ʽ
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