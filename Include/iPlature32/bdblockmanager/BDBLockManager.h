// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `BDBLockManager.ice'

#ifndef __bdblockmanager___BDBLockManager_h__
#define __bdblockmanager___BDBLockManager_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/StreamF.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 301
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace iPlature
{

class BDBLockManager;
bool operator==(const BDBLockManager&, const BDBLockManager&);
bool operator!=(const BDBLockManager&, const BDBLockManager&);
bool operator<(const BDBLockManager&, const BDBLockManager&);
bool operator<=(const BDBLockManager&, const BDBLockManager&);
bool operator>(const BDBLockManager&, const BDBLockManager&);
bool operator>=(const BDBLockManager&, const BDBLockManager&);

}

}

namespace iPlature
{

class BDBLockManager;
bool operator==(const BDBLockManager&, const BDBLockManager&);
bool operator!=(const BDBLockManager&, const BDBLockManager&);
bool operator<(const BDBLockManager&, const BDBLockManager&);
bool operator<=(const BDBLockManager&, const BDBLockManager&);
bool operator>(const BDBLockManager&, const BDBLockManager&);
bool operator>=(const BDBLockManager&, const BDBLockManager&);

}

namespace IceInternal
{

void incRef(::iPlature::BDBLockManager*);
void decRef(::iPlature::BDBLockManager*);

void incRef(::IceProxy::iPlature::BDBLockManager*);
void decRef(::IceProxy::iPlature::BDBLockManager*);

}

namespace iPlature
{

typedef ::IceInternal::Handle< ::iPlature::BDBLockManager> BDBLockManagerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::iPlature::BDBLockManager> BDBLockManagerPrx;

void __write(::IceInternal::BasicStream*, const BDBLockManagerPrx&);
void __read(::IceInternal::BasicStream*, BDBLockManagerPrx&);
void __write(::IceInternal::BasicStream*, const BDBLockManagerPtr&);
void __patch__BDBLockManagerPtr(void*, ::Ice::ObjectPtr&);

}

namespace iPlature
{

enum RWFlag
{
    ReadLock,
    WriteLock
};

void __write(::IceInternal::BasicStream*, RWFlag);
void __read(::IceInternal::BasicStream*, RWFlag&);

}

namespace IceProxy
{

namespace iPlature
{

class BDBLockManager : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int Lock(const ::std::string& mapName, ::iPlature::RWFlag flag, ::Ice::Int& lockID)
    {
	return Lock(mapName, flag, lockID, __defaultContext());
    }
    ::Ice::Int Lock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int&, const ::Ice::Context&);

    ::Ice::Int Unlock(const ::std::string& mapName, ::iPlature::RWFlag flag, ::Ice::Int lockID)
    {
	return Unlock(mapName, flag, lockID, __defaultContext());
    }
    ::Ice::Int Unlock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int, const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

}

}

namespace IceDelegate
{

namespace iPlature
{

class BDBLockManager : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int Lock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int Unlock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int, const ::Ice::Context&) = 0;
};

}

}

namespace IceDelegateM
{

namespace iPlature
{

class BDBLockManager : virtual public ::IceDelegate::iPlature::BDBLockManager,
		       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int Lock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int&, const ::Ice::Context&);

    virtual ::Ice::Int Unlock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int, const ::Ice::Context&);
};

}

}

namespace IceDelegateD
{

namespace iPlature
{

class BDBLockManager : virtual public ::IceDelegate::iPlature::BDBLockManager,
		       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int Lock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int&, const ::Ice::Context&);

    virtual ::Ice::Int Unlock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int, const ::Ice::Context&);
};

}

}

namespace iPlature
{

class BDBLockManager : virtual public ::Ice::Object
{
public:

    typedef BDBLockManagerPrx ProxyType;
    typedef BDBLockManagerPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int Lock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Lock(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int Unlock(const ::std::string&, ::iPlature::RWFlag, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Unlock(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__BDBLockManagerPtr(void*, ::Ice::ObjectPtr&);

}

#endif
