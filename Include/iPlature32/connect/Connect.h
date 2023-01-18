// **********************************************************************
//
// Copyright (c) 2003-2010 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.4.1

// <auto-generated>
//
// Generated from file `Connect.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

#ifndef __connect___Connect_h__
#define __connect___Connect_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/StreamF.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 304
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace iPlature
{

class Connect;

}

}

namespace iPlature
{

class Connect;
bool operator==(const Connect&, const Connect&);
bool operator<(const Connect&, const Connect&);

}

namespace IceInternal
{

::Ice::Object* upCast(::iPlature::Connect*);
::IceProxy::Ice::Object* upCast(::IceProxy::iPlature::Connect*);

}

namespace iPlature
{

typedef ::IceInternal::Handle< ::iPlature::Connect> ConnectPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::iPlature::Connect> ConnectPrx;

void __read(::IceInternal::BasicStream*, ConnectPrx&);
void __patch__ConnectPtr(void*, ::Ice::ObjectPtr&);

}

namespace iPlature
{

class Callback_Connect_updateConnect_Base : virtual public ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_Connect_updateConnect_Base> Callback_Connect_updateConnectPtr;

}

namespace IceProxy
{

namespace iPlature
{

class Connect : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int updateConnect(const ::std::string& ConnectName, ::Ice::Int ConnectStatus)
    {
        return updateConnect(ConnectName, ConnectStatus, 0);
    }
    ::Ice::Int updateConnect(const ::std::string& ConnectName, ::Ice::Int ConnectStatus, const ::Ice::Context& __ctx)
    {
        return updateConnect(ConnectName, ConnectStatus, &__ctx);
    }

    ::Ice::AsyncResultPtr begin_updateConnect(const ::std::string& ConnectName, ::Ice::Int ConnectStatus)
    {
        return begin_updateConnect(ConnectName, ConnectStatus, 0, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_updateConnect(const ::std::string& ConnectName, ::Ice::Int ConnectStatus, const ::Ice::Context& __ctx)
    {
        return begin_updateConnect(ConnectName, ConnectStatus, &__ctx, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_updateConnect(const ::std::string& ConnectName, ::Ice::Int ConnectStatus, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_updateConnect(ConnectName, ConnectStatus, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_updateConnect(const ::std::string& ConnectName, ::Ice::Int ConnectStatus, const ::Ice::Context& __ctx, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_updateConnect(ConnectName, ConnectStatus, &__ctx, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_updateConnect(const ::std::string& ConnectName, ::Ice::Int ConnectStatus, const ::iPlature::Callback_Connect_updateConnectPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_updateConnect(ConnectName, ConnectStatus, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_updateConnect(const ::std::string& ConnectName, ::Ice::Int ConnectStatus, const ::Ice::Context& __ctx, const ::iPlature::Callback_Connect_updateConnectPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_updateConnect(ConnectName, ConnectStatus, &__ctx, __del, __cookie);
    }

    ::Ice::Int end_updateConnect(const ::Ice::AsyncResultPtr&);
    
private:

    ::Ice::Int updateConnect(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    ::Ice::AsyncResultPtr begin_updateConnect(const ::std::string&, ::Ice::Int, const ::Ice::Context*, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& __cookie = 0);
    
public:
    
    ::IceInternal::ProxyHandle<Connect> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Connect> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Connect*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Connect*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace iPlature
{

class Connect : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int updateConnect(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace iPlature
{

class Connect : virtual public ::IceDelegate::iPlature::Connect,
                virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int updateConnect(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace iPlature
{

class Connect : virtual public ::IceDelegate::iPlature::Connect,
                virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int updateConnect(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
};

}

}

namespace iPlature
{

class Connect : virtual public ::Ice::Object
{
public:

    typedef ConnectPrx ProxyType;
    typedef ConnectPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int updateConnect(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___updateConnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
// COMPILERFIX: Stream API is not supported with VC++ 6
#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
#endif
};

inline bool operator==(const Connect& l, const Connect& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

inline bool operator<(const Connect& l, const Connect& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

}

namespace iPlature
{

template<class T>
class CallbackNC_Connect_updateConnect : public Callback_Connect_updateConnect_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(::Ice::Int);

    CallbackNC_Connect_updateConnect(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), response(cb)
    {
    }

    virtual void __completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::iPlature::ConnectPrx __proxy = ::iPlature::ConnectPrx::uncheckedCast(__result->getProxy());
        ::Ice::Int __ret;
        try
        {
            __ret = __proxy->end_updateConnect(__result);
        }
        catch(::Ice::Exception& ex)
        {
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
            __exception(__result, ex);
#else
            ::IceInternal::CallbackNC<T>::__exception(__result, ex);
#endif
            return;
        }
        if(response)
        {
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
            (callback.get()->*response)(__ret);
#else
            (::IceInternal::CallbackNC<T>::callback.get()->*response)(__ret);
#endif
        }
    }

    Response response;
};

template<class T> Callback_Connect_updateConnectPtr
newCallback_Connect_updateConnect(const IceUtil::Handle<T>& instance, void (T::*cb)(::Ice::Int), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Connect_updateConnect<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_Connect_updateConnectPtr
newCallback_Connect_updateConnect(T* instance, void (T::*cb)(::Ice::Int), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Connect_updateConnect<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_Connect_updateConnect : public Callback_Connect_updateConnect_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(::Ice::Int, const CT&);

    Callback_Connect_updateConnect(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), response(cb)
    {
    }

    virtual void __completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::iPlature::ConnectPrx __proxy = ::iPlature::ConnectPrx::uncheckedCast(__result->getProxy());
        ::Ice::Int __ret;
        try
        {
            __ret = __proxy->end_updateConnect(__result);
        }
        catch(::Ice::Exception& ex)
        {
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
            __exception(__result, ex);
#else
            ::IceInternal::Callback<T, CT>::__exception(__result, ex);
#endif
            return;
        }
        if(response)
        {
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
            (callback.get()->*response)(__ret, CT::dynamicCast(__result->getCookie()));
#else
            (::IceInternal::Callback<T, CT>::callback.get()->*response)(__ret, CT::dynamicCast(__result->getCookie()));
#endif
        }
    }

    Response response;
};

template<class T, typename CT> Callback_Connect_updateConnectPtr
newCallback_Connect_updateConnect(const IceUtil::Handle<T>& instance, void (T::*cb)(::Ice::Int, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Connect_updateConnect<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_Connect_updateConnectPtr
newCallback_Connect_updateConnect(T* instance, void (T::*cb)(::Ice::Int, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Connect_updateConnect<T, CT>(instance, cb, excb, sentcb);
}

}

#endif