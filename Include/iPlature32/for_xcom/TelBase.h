// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `TelBase.ice'

#ifndef __TelBase_h__
#define __TelBase_h__

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
#include <CommonDef.h>
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

class TelBase;
bool operator==(const TelBase&, const TelBase&);
bool operator!=(const TelBase&, const TelBase&);
bool operator<(const TelBase&, const TelBase&);
bool operator<=(const TelBase&, const TelBase&);
bool operator>(const TelBase&, const TelBase&);
bool operator>=(const TelBase&, const TelBase&);

}

}

namespace iPlature
{

class TelBase;
bool operator==(const TelBase&, const TelBase&);
bool operator!=(const TelBase&, const TelBase&);
bool operator<(const TelBase&, const TelBase&);
bool operator<=(const TelBase&, const TelBase&);
bool operator>(const TelBase&, const TelBase&);
bool operator>=(const TelBase&, const TelBase&);

}

namespace IceInternal
{

void incRef(::iPlature::TelBase*);
void decRef(::iPlature::TelBase*);

void incRef(::IceProxy::iPlature::TelBase*);
void decRef(::IceProxy::iPlature::TelBase*);

}

namespace iPlature
{

typedef ::IceInternal::Handle< ::iPlature::TelBase> TelBasePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::iPlature::TelBase> TelBasePrx;

void __write(::IceInternal::BasicStream*, const TelBasePrx&);
void __read(::IceInternal::BasicStream*, TelBasePrx&);
void __write(::IceInternal::BasicStream*, const TelBasePtr&);
void __patch__TelBasePtr(void*, ::Ice::ObjectPtr&);

}

namespace iPlature
{

}

namespace IceProxy
{

namespace iPlature
{

class TelBase : virtual public ::IceProxy::Ice::Object
{
public:

    void handleMessage(const ::iPlature::ByteSeq& dataBuf)
    {
	handleMessage(dataBuf, __defaultContext());
    }
    void handleMessage(const ::iPlature::ByteSeq&, const ::Ice::Context&);
    
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

class TelBase : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void handleMessage(const ::iPlature::ByteSeq&, const ::Ice::Context&) = 0;
};

}

}

namespace IceDelegateM
{

namespace iPlature
{

class TelBase : virtual public ::IceDelegate::iPlature::TelBase,
		virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void handleMessage(const ::iPlature::ByteSeq&, const ::Ice::Context&);
};

}

}

namespace IceDelegateD
{

namespace iPlature
{

class TelBase : virtual public ::IceDelegate::iPlature::TelBase,
		virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void handleMessage(const ::iPlature::ByteSeq&, const ::Ice::Context&);
};

}

}

namespace iPlature
{

class TelBase : virtual public ::Ice::Object
{
public:

    typedef TelBasePrx ProxyType;
    typedef TelBasePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void handleMessage(const ::iPlature::ByteSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___handleMessage(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__TelBasePtr(void*, ::Ice::ObjectPtr&);

}

#endif
