// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `Tel.ice'

#ifndef __Tel_h__
#define __Tel_h__

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
#include <TelBase.h>
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

class Tel;
bool operator==(const Tel&, const Tel&);
bool operator!=(const Tel&, const Tel&);
bool operator<(const Tel&, const Tel&);
bool operator<=(const Tel&, const Tel&);
bool operator>(const Tel&, const Tel&);
bool operator>=(const Tel&, const Tel&);

}

}

namespace iPlature
{

class Tel;
bool operator==(const Tel&, const Tel&);
bool operator!=(const Tel&, const Tel&);
bool operator<(const Tel&, const Tel&);
bool operator<=(const Tel&, const Tel&);
bool operator>(const Tel&, const Tel&);
bool operator>=(const Tel&, const Tel&);

}

namespace IceInternal
{

void incRef(::iPlature::Tel*);
void decRef(::iPlature::Tel*);

void incRef(::IceProxy::iPlature::Tel*);
void decRef(::IceProxy::iPlature::Tel*);

}

namespace iPlature
{

typedef ::IceInternal::Handle< ::iPlature::Tel> TelPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::iPlature::Tel> TelPrx;

void __write(::IceInternal::BasicStream*, const TelPrx&);
void __read(::IceInternal::BasicStream*, TelPrx&);
void __write(::IceInternal::BasicStream*, const TelPtr&);
void __patch__TelPtr(void*, ::Ice::ObjectPtr&);

}

namespace iPlature
{

}

namespace IceProxy
{

namespace iPlature
{

class Tel : virtual public ::IceProxy::iPlature::TelBase
{
public:

    void sayHello()
    {
	sayHello(__defaultContext());
    }
    void sayHello(const ::Ice::Context&);
    
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

class Tel : virtual public ::IceDelegate::iPlature::TelBase
{
public:

    virtual void sayHello(const ::Ice::Context&) = 0;
};

}

}

namespace IceDelegateM
{

namespace iPlature
{

class Tel : virtual public ::IceDelegate::iPlature::Tel,
	    virtual public ::IceDelegateM::iPlature::TelBase
{
public:

    virtual void sayHello(const ::Ice::Context&);
};

}

}

namespace IceDelegateD
{

namespace iPlature
{

class Tel : virtual public ::IceDelegate::iPlature::Tel,
	    virtual public ::IceDelegateD::iPlature::TelBase
{
public:

    virtual void sayHello(const ::Ice::Context&);
};

}

}

namespace iPlature
{

class Tel : virtual public ::iPlature::TelBase
{
public:

    typedef TelPrx ProxyType;
    typedef TelPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void sayHello(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___sayHello(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__TelPtr(void*, ::Ice::ObjectPtr&);

}

#endif
