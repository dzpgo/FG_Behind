/*********************************************************************
 *		
 *  文      件:    Singleton.hpp
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：单件模式的简单封装类
 *		  使用方法：
 *
 *			  //声明
 *		      class TestClass
 *			  {
 *			  public:
 *			      void doSomething(){}
 *			  };
 *            typedef SingletonHolder<TestClass> TestClassSingleton;
 *			  
 *            //以后就可以这样获取唯一实例
 *            TestClassSingleton::getInstance().doSomething();
 *
 *
 *  版本历史		
 *      1.0    2009-12-04    lumengyi    创建
 *     
*********************************************************************/
#ifndef __SINGLETON_HPP_
#define __SINGLETON_HPP_
#include <IceUtil/StaticMutex.h>

namespace iPlature
{
	namespace Tools
	{
		template<class T,class MutexType = IceUtil::StaticMutex>
		class SingletonHolder
		{
		public:
			virtual ~SingletonHolder(){}

			static T& getInstance()
			{
				if(_instance == 0)
				{
					typename MutexType::Lock lock(_mutex);
					if (_instance == 0)
					{
						_instance = new T;
						atexit(destroyInstance);
					}
				}
				return *_instance;
			}
		private:
			SingletonHolder(){}
			static void destroyInstance() 
			{
				if ( _instance != 0 ) 
				{
					delete _instance;
					_instance = 0;
				}
			}

			static T* volatile _instance;
			static MutexType _mutex;
		};

		template<class T,class MutexType>
		T* volatile SingletonHolder<T,MutexType>::_instance = 0;

		template<class T,class MutexType>
		MutexType SingletonHolder<T,MutexType>::_mutex = { 0 };
	}//namespace Tools
}//namespace iPlature

#endif