#ifndef __PACE_QUEUE_H__
#define __PACE_QUEUE_H__
/*********************************************************************
*		
*  ��      ��:    Queue.h   		//TODO������ļ�����
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������//TODO����ӱ��ļ�����������ϸ����
*        ��//TODO
*        ��//TODO
*
*  �汾��ʷ		
*      1.0    2012-01-19    Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
*      1.1	  2013-08-06	Haykin			ȡ��MAXCOUNT��Ϊģ�����   
*********************************************************************/

#include <IceUtil/Monitor.h>
#include <pace/Simple_cast.h>
#include <list>

namespace iPlature
{
	class  QueueException : public std::exception
	{
	public:
		QueueException(const std::string& reason) : _what(reason) {}
		virtual ~QueueException() throw() {}
		virtual const char* what() const throw() { return _what.c_str(); }
	private:
		std::string _what;
	}; //QueueException

	class QueueOverFlowException : public QueueException
	{
	public:
		QueueOverFlowException(int nMaxCount)
			: QueueException(std::string("Queue over flow [" + simple_cast<std::string>(nMaxCount) + "]") ){}
	}; //QueueOverFlowException

	class QueueStopException : public QueueException
	{
	public:
		QueueStopException()
			: QueueException(std::string("Queue stop") ) {}
	};//QueueStopException

	template<typename T>
	class Queue : public IceUtil::Monitor<IceUtil::Mutex>
	{
	public:
		Queue(int nMaxCount) : _waitingReaders(0), _stop(false), _maxcount(nMaxCount) {}

		void put(const T& item)
		{
			IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

			if (simple_cast<int>(_q.size()) > _maxcount)
			{
				throw QueueOverFlowException(_maxcount);
			}//size
			_q.push_back(item);
			if (_waitingReaders)
			{
				notify();
			}//waitingReaders
		}//put

		T get() 
		{
			IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
			while (_q.size() == 0) 
			{
				if (_stop)
				{
					throw QueueStopException();
				}

				try {
					++_waitingReaders;
					wait();
					--_waitingReaders;
				} catch (...) {
					--_waitingReaders;
					throw;
				}
			}//while
			T item = _q.front();
			_q.pop_front();
			return item;
		}//get

		void stop()
		{
			IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
			_stop = true;
			notifyAll();
		}

		size_t size()
		{
			IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
			return _q.size();
		}

	private:
		std::list<T> _q;
		int _waitingReaders;
		bool _stop;
		int _maxcount;
	};//Queue

	
}//namespace iPlature

#endif


