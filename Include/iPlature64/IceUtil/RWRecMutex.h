// **********************************************************************
//
// Copyright (c) 2003-2010 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_UTIL_RW_REC_MUTEX_H
#define ICE_UTIL_RW_REC_MUTEX_H

#include <IceUtil/Mutex.h>
#include <IceUtil/Cond.h>
#include <IceUtil/Thread.h>

namespace IceUtil
{
    
//
// All classes defined in this file are now deprecated.
//

class ICE_UTIL_API DeadlockException : public Exception
{
public:

    ICE_DEPRECATED_API DeadlockException(const char*, int);
    ICE_DEPRECATED_API virtual std::string ice_name() const;
    ICE_DEPRECATED_API virtual Exception* ice_clone() const;
    ICE_DEPRECATED_API virtual void ice_throw() const;

private:

    static const char* _name;
};

template <typename T>
class RLockT
{
public:

    ICE_DEPRECATED_API RLockT(const T& mutex) :
        _mutex(mutex)
    {
        _mutex.readLock();
        _acquired = true;
    }

    ICE_DEPRECATED_API ~RLockT()
    {
        if (_acquired)
        {
            _mutex.unlock();
        }
    }

    ICE_DEPRECATED_API void acquire() const
    {
        if (_acquired)
        {
            throw ThreadLockedException(__FILE__, __LINE__);
        }
        _mutex.readLock();
        _acquired = true;
    }

    ICE_DEPRECATED_API bool tryAcquire() const
    {
        if (_acquired)
        {
            throw ThreadLockedException(__FILE__, __LINE__);
        }
        _acquired = _mutex.tryReadLock();
        return _acquired;
    }

    ICE_DEPRECATED_API bool timedAcquire(const Time& timeout) const
    {
        if (_acquired)
        {
            throw ThreadLockedException(__FILE__, __LINE__);
        }
        _acquired = _mutex.timedReadLock(timeout);
        return _acquired;
    }    

    ICE_DEPRECATED_API void release() const
    {
        if (!_acquired)
        {
            throw ThreadLockedException(__FILE__, __LINE__);
        }
        _mutex.unlock();
        _acquired = false;
    }

    ICE_DEPRECATED_API bool acquired() const
    {
        return _acquired;
    }

    ICE_DEPRECATED_API void
    upgrade() const
    {
        _mutex.upgrade();
    }

    ICE_DEPRECATED_API bool
    timedUpgrade(const Time& timeout) const
    {
        return _mutex.timedUpgrade(timeout);
    }

    ICE_DEPRECATED_API void
    downgrade() const
    {
        _mutex.downgrade();
    }

protected:
    
    // TryRLockT's constructors

    RLockT(const T& mutex, bool) :
        _mutex(mutex)
    {
        _acquired = _mutex.tryReadLock();
    }


    RLockT(const T& mutex, const Time& timeout) :
        _mutex(mutex)
    {
        _acquired = _mutex.timedReadLock(timeout);
    }


private:

    // Not implemented; prevents accidental use.
    //
    RLockT(const RLockT&);
    RLockT& operator=(const RLockT&);

    const T& _mutex;
    mutable bool _acquired;
};

template <typename T>
class TryRLockT : public RLockT<T>
{
public:

    ICE_DEPRECATED_API TryRLockT(const T& mutex) :
        RLockT<T>(mutex, true)
    {
    }

    ICE_DEPRECATED_API TryRLockT(const T& mutex, const Time& timeout) :
        RLockT<T>(mutex, timeout)
    {
    }
};

template <typename T>
class WLockT
{
public:

    ICE_DEPRECATED_API WLockT(const T& mutex) :
        _mutex(mutex)
    {
        _mutex.writeLock();
        _acquired = true;
    }

    ICE_DEPRECATED_API ~WLockT()
    {
        if(_acquired)
        {
            _mutex.unlock();
        }
    }

    ICE_DEPRECATED_API void acquire() const
    {
        if (_acquired)
        {
            throw ThreadLockedException(__FILE__, __LINE__);
        }
        _mutex.writeLock();
        _acquired = true;
    }

    ICE_DEPRECATED_API bool tryAcquire() const
    {
        if (_acquired)
        {
            throw ThreadLockedException(__FILE__, __LINE__);
        }
        _acquired = _mutex.tryWriteLock();
        return _acquired;
    }

    ICE_DEPRECATED_API bool timedAcquire(const Time& timeout) const
    {
        if (_acquired)
        {
            throw ThreadLockedException(__FILE__, __LINE__);
        }
        _acquired = _mutex.timedWriteLock(timeout);
        return _acquired;
    }

    ICE_DEPRECATED_API void release() const
    {
        if (!_acquired)
        {
            throw ThreadLockedException(__FILE__, __LINE__);
        }
        _mutex.unlock();
        _acquired = false;
    }

    ICE_DEPRECATED_API bool acquired() const
    {
        return _acquired;
    }

protected:

    // TryWLockT's constructor

    WLockT(const T& mutex, bool) :
        _mutex(mutex)
    {
        _acquired = _mutex.tryWriteLock();
    }

    WLockT(const T& mutex, const Time& timeout) :
        _mutex(mutex)
    {
        _acquired = _mutex.timedWriteLock(timeout);
    }

private:

    // Not implemented; prevents accidental use.
    //
    WLockT(const WLockT&);
    WLockT& operator=(const WLockT&);

    const T& _mutex;
    mutable bool _acquired;
};

template <typename T>
class TryWLockT : public WLockT<T>
{
public:

    ICE_DEPRECATED_API TryWLockT(const T& mutex) :
        WLockT<T>(mutex, true)
    {
    }

    ICE_DEPRECATED_API TryWLockT(const T& mutex, const Time& timeout) :
        WLockT<T>(mutex, timeout)
    {
    }
};

//
// Concurrency primitive that allows many readers & one writer access
// to a data structure. Writers have priority over readers. The
// structure is not strictly fair in that there is no absolute queue
// of waiting writers - that is managed by a condition variable.
//
// Both Reader & Writer mutexes can be recursively locked. Calling
// upgrade() or timedUpgrade() while holding a read lock promotes
// the reader to a writer lock.
//

class ICE_UTIL_API RWRecMutex
{
public:

    //
    // RLock (reader) & WLock (writer) typedefs.
    //
    typedef RLockT<RWRecMutex> RLock;
    typedef TryRLockT<RWRecMutex> TryRLock;
    typedef WLockT<RWRecMutex> WLock;
    typedef TryWLockT<RWRecMutex> TryWLock;

    ICE_DEPRECATED_API RWRecMutex();
    ICE_DEPRECATED_API ~RWRecMutex();

    //
    // Note that readLock/writeLock & unlock in general should not be
    // used directly. Instead use RLock & WLock.
    //

    //
    // Acquire a read lock.
    //
    ICE_DEPRECATED_API void readLock() const;

    //
    // Try to acquire a read lock.
    //
    ICE_DEPRECATED_API bool tryReadLock() const;

    //
    // Try to acquire a read lock for upto the given timeout.
    //
    ICE_DEPRECATED_API bool timedReadLock(const Time&) const;

    //
    // Acquire a write lock.
    //
    ICE_DEPRECATED_API void writeLock() const;

    //
    // Acquire a write lock.
    //
    ICE_DEPRECATED_API bool tryWriteLock() const;

    //
    // Acquire a write lock for up to the given timeout.
    //
    ICE_DEPRECATED_API bool timedWriteLock(const Time&) const;

    //
    // Unlock the reader/writer lock.
    //
    ICE_DEPRECATED_API void unlock() const;

    //
    // Upgrade the read lock to a writer lock. Note that this method
    // can only be called if the reader lock is not held recursively.
    //
    ICE_DEPRECATED_API void upgrade() const;

    //
    // Upgrade the read lock to a writer lock for up to the given
    // timeout Note that this method can only be called if the reader
    // lock is not held recursively.
    //
    ICE_DEPRECATED_API bool timedUpgrade(const Time&) const;

    //
    // Downgrade a write lock to a read lock.
    //
    ICE_DEPRECATED_API void downgrade() const;

private:

    // noncopyable
    RWRecMutex(const RWRecMutex&);
    void operator=(const RWRecMutex&);

    //
    // Number of readers holding the lock. A positive number indicates
    // readers are active. A negative number means that a writer is
    // active and indicates the number of times writeLock() was called.
    //
    mutable int _count;

    //
    // If there is an active writer this is the ID of the writer thread.
    //
    mutable ThreadControl _writerId;

    //
    // Number of waiting writers (including any upgrader).
    //
    mutable unsigned int _waitingWriters;

    //
    // True if an upgrader wants the lock.
    //
    mutable bool _upgrading;

    //
    // Internal mutex.
    //
    Mutex _mutex;

    //
    // Condition variables for waiting readers, writers, and upgrader.
    //
    mutable Cond _readers;
    mutable Cond _writers;
    mutable Cond _upgrader;
};

} // End namespace IceUtil

#endif
