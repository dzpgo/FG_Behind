// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `NotifyiPlature.ice'

#ifndef __NotifyiPlature_h__
#define __NotifyiPlature_h__

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

class NotifyiPlature;
bool operator==(const NotifyiPlature&, const NotifyiPlature&);
bool operator!=(const NotifyiPlature&, const NotifyiPlature&);
bool operator<(const NotifyiPlature&, const NotifyiPlature&);
bool operator<=(const NotifyiPlature&, const NotifyiPlature&);
bool operator>(const NotifyiPlature&, const NotifyiPlature&);
bool operator>=(const NotifyiPlature&, const NotifyiPlature&);

}

}

namespace iPlature
{

class NotifyiPlature;
bool operator==(const NotifyiPlature&, const NotifyiPlature&);
bool operator!=(const NotifyiPlature&, const NotifyiPlature&);
bool operator<(const NotifyiPlature&, const NotifyiPlature&);
bool operator<=(const NotifyiPlature&, const NotifyiPlature&);
bool operator>(const NotifyiPlature&, const NotifyiPlature&);
bool operator>=(const NotifyiPlature&, const NotifyiPlature&);

}

namespace IceInternal
{

void incRef(::iPlature::NotifyiPlature*);
void decRef(::iPlature::NotifyiPlature*);

void incRef(::IceProxy::iPlature::NotifyiPlature*);
void decRef(::IceProxy::iPlature::NotifyiPlature*);

}

namespace iPlature
{

typedef ::IceInternal::Handle< ::iPlature::NotifyiPlature> NotifyiPlaturePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::iPlature::NotifyiPlature> NotifyiPlaturePrx;

void __write(::IceInternal::BasicStream*, const NotifyiPlaturePrx&);
void __read(::IceInternal::BasicStream*, NotifyiPlaturePrx&);
void __write(::IceInternal::BasicStream*, const NotifyiPlaturePtr&);
void __patch__NotifyiPlaturePtr(void*, ::Ice::ObjectPtr&);

}

namespace iPlature
{

}

namespace IceProxy
{

namespace iPlature
{

class NotifyiPlature : virtual public ::IceProxy::Ice::Object
{
public:

    void triggerApp(const ::std::string& strProgramName, const ::iPlature::ByteSeq& dataBuf)
    {
	triggerApp(strProgramName, dataBuf, __defaultContext());
    }
    void triggerApp(const ::std::string&, const ::iPlature::ByteSeq&, const ::Ice::Context&);
    
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

class NotifyiPlature : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void triggerApp(const ::std::string&, const ::iPlature::ByteSeq&, const ::Ice::Context&) = 0;
};

}

}

namespace IceDelegateM
{

namespace iPlature
{

class NotifyiPlature : virtual public ::IceDelegate::iPlature::NotifyiPlature,
		       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void triggerApp(const ::std::string&, const ::iPlature::ByteSeq&, const ::Ice::Context&);
};

}

}

namespace IceDelegateD
{

namespace iPlature
{

class NotifyiPlature : virtual public ::IceDelegate::iPlature::NotifyiPlature,
		       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void triggerApp(const ::std::string&, const ::iPlature::ByteSeq&, const ::Ice::Context&);
};

}

}

namespace iPlature
{

class NotifyiPlature : virtual public ::Ice::Object
{
public:

    typedef NotifyiPlaturePrx ProxyType;
    typedef NotifyiPlaturePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void triggerApp(const ::std::string&, const ::iPlature::ByteSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___triggerApp(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__NotifyiPlaturePtr(void*, ::Ice::ObjectPtr&);

}

#endif
