// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `TagAdapter.ice'

#ifndef __TagAdapter_h__
#define __TagAdapter_h__

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
#include <tag/TagDefines.h>
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

class AdapterInterface;
bool operator==(const AdapterInterface&, const AdapterInterface&);
bool operator!=(const AdapterInterface&, const AdapterInterface&);
bool operator<(const AdapterInterface&, const AdapterInterface&);
bool operator<=(const AdapterInterface&, const AdapterInterface&);
bool operator>(const AdapterInterface&, const AdapterInterface&);
bool operator>=(const AdapterInterface&, const AdapterInterface&);

}

}

namespace iPlature
{

class AdapterInterface;
bool operator==(const AdapterInterface&, const AdapterInterface&);
bool operator!=(const AdapterInterface&, const AdapterInterface&);
bool operator<(const AdapterInterface&, const AdapterInterface&);
bool operator<=(const AdapterInterface&, const AdapterInterface&);
bool operator>(const AdapterInterface&, const AdapterInterface&);
bool operator>=(const AdapterInterface&, const AdapterInterface&);

}

namespace IceInternal
{

void incRef(::iPlature::AdapterInterface*);
void decRef(::iPlature::AdapterInterface*);

void incRef(::IceProxy::iPlature::AdapterInterface*);
void decRef(::IceProxy::iPlature::AdapterInterface*);

}

namespace iPlature
{

typedef ::IceInternal::Handle< ::iPlature::AdapterInterface> AdapterInterfacePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::iPlature::AdapterInterface> AdapterInterfacePrx;

void __write(::IceInternal::BasicStream*, const AdapterInterfacePrx&);
void __read(::IceInternal::BasicStream*, AdapterInterfacePrx&);
void __write(::IceInternal::BasicStream*, const AdapterInterfacePtr&);
void __patch__AdapterInterfacePtr(void*, ::Ice::ObjectPtr&);

}

namespace iPlature
{

}

namespace IceProxy
{

namespace iPlature
{

class AdapterInterface : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int AdapterGetActual(const ::iPlature::TAGNAMEARRAY& tagNames, ::iPlature::TAGVALUEMAP& tagPairs)
    {
	return AdapterGetActual(tagNames, tagPairs, __defaultContext());
    }
    ::Ice::Int AdapterGetActual(const ::iPlature::TAGNAMEARRAY&, ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    ::Ice::Int AdapterCyclicPut(const ::iPlature::TAGVALUEMAP& tagPairs)
    {
	return AdapterCyclicPut(tagPairs, __defaultContext());
    }
    ::Ice::Int AdapterCyclicPut(const ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    ::Ice::Int AdapterEventPut(const ::iPlature::TAGVALUEMAP& tagPairs, const ::std::string& eventName, const ::std::string& eventValue)
    {
	return AdapterEventPut(tagPairs, eventName, eventValue, __defaultContext());
    }
    ::Ice::Int AdapterEventPut(const ::iPlature::TAGVALUEMAP&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    ::Ice::Int AdapterMDPut(const ::iPlature::TAGVALUEMAP& tagTimeStamp, const ::iPlature::TAGVALUEMAP& tagPairs)
    {
	return AdapterMDPut(tagTimeStamp, tagPairs, __defaultContext());
    }
    ::Ice::Int AdapterMDPut(const ::iPlature::TAGVALUEMAP&, const ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    ::Ice::Int AdapterWrite2Level1(const ::iPlature::TAGVALUEMAP& tagPairs, ::Ice::Int nType)
    {
	return AdapterWrite2Level1(tagPairs, nType, __defaultContext());
    }
    ::Ice::Int AdapterWrite2Level1(const ::iPlature::TAGVALUEMAP&, ::Ice::Int, const ::Ice::Context&);

    ::Ice::Int AdapterEnableArchive(bool bFlag, const ::iPlature::TAGNAMEARRAY& tagNames)
    {
	return AdapterEnableArchive(bFlag, tagNames, __defaultContext());
    }
    ::Ice::Int AdapterEnableArchive(bool, const ::iPlature::TAGNAMEARRAY&, const ::Ice::Context&);

    ::Ice::Int AdapterEnableAllArchives(bool bFlag)
    {
	return AdapterEnableAllArchives(bFlag, __defaultContext());
    }
    ::Ice::Int AdapterEnableAllArchives(bool, const ::Ice::Context&);
    
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

class AdapterInterface : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int AdapterGetActual(const ::iPlature::TAGNAMEARRAY&, ::iPlature::TAGVALUEMAP&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int AdapterCyclicPut(const ::iPlature::TAGVALUEMAP&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int AdapterEventPut(const ::iPlature::TAGVALUEMAP&, const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int AdapterMDPut(const ::iPlature::TAGVALUEMAP&, const ::iPlature::TAGVALUEMAP&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int AdapterWrite2Level1(const ::iPlature::TAGVALUEMAP&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int AdapterEnableArchive(bool, const ::iPlature::TAGNAMEARRAY&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int AdapterEnableAllArchives(bool, const ::Ice::Context&) = 0;
};

}

}

namespace IceDelegateM
{

namespace iPlature
{

class AdapterInterface : virtual public ::IceDelegate::iPlature::AdapterInterface,
			 virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int AdapterGetActual(const ::iPlature::TAGNAMEARRAY&, ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterCyclicPut(const ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterEventPut(const ::iPlature::TAGVALUEMAP&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterMDPut(const ::iPlature::TAGVALUEMAP&, const ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterWrite2Level1(const ::iPlature::TAGVALUEMAP&, ::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int AdapterEnableArchive(bool, const ::iPlature::TAGNAMEARRAY&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterEnableAllArchives(bool, const ::Ice::Context&);
};

}

}

namespace IceDelegateD
{

namespace iPlature
{

class AdapterInterface : virtual public ::IceDelegate::iPlature::AdapterInterface,
			 virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int AdapterGetActual(const ::iPlature::TAGNAMEARRAY&, ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterCyclicPut(const ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterEventPut(const ::iPlature::TAGVALUEMAP&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterMDPut(const ::iPlature::TAGVALUEMAP&, const ::iPlature::TAGVALUEMAP&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterWrite2Level1(const ::iPlature::TAGVALUEMAP&, ::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int AdapterEnableArchive(bool, const ::iPlature::TAGNAMEARRAY&, const ::Ice::Context&);

    virtual ::Ice::Int AdapterEnableAllArchives(bool, const ::Ice::Context&);
};

}

}

namespace iPlature
{

class AdapterInterface : virtual public ::Ice::Object
{
public:

    typedef AdapterInterfacePrx ProxyType;
    typedef AdapterInterfacePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int AdapterGetActual(const ::iPlature::TAGNAMEARRAY&, ::iPlature::TAGVALUEMAP&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AdapterGetActual(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int AdapterCyclicPut(const ::iPlature::TAGVALUEMAP&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AdapterCyclicPut(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int AdapterEventPut(const ::iPlature::TAGVALUEMAP&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AdapterEventPut(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int AdapterMDPut(const ::iPlature::TAGVALUEMAP&, const ::iPlature::TAGVALUEMAP&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AdapterMDPut(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int AdapterWrite2Level1(const ::iPlature::TAGVALUEMAP&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AdapterWrite2Level1(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int AdapterEnableArchive(bool, const ::iPlature::TAGNAMEARRAY&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AdapterEnableArchive(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int AdapterEnableAllArchives(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AdapterEnableAllArchives(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__AdapterInterfacePtr(void*, ::Ice::ObjectPtr&);

}

#endif
