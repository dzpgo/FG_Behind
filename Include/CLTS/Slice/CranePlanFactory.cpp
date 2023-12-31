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
// Generated from file `CranePlanFactory.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

#include <CranePlanFactory.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <IceUtil/Iterator.h>

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

static const ::std::string __CLTS__CranePlanFactory__getCranePlan_name = "getCranePlan";

static const ::std::string __CLTS__CranePlanFactory__initCranePlan_name = "initCranePlan";

::Ice::Object* IceInternal::upCast(::CLTS::CranePlanFactory* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::CLTS::CranePlanFactory* p) { return p; }

void
CLTS::__read(::IceInternal::BasicStream* __is, ::CLTS::CranePlanFactoryPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::CLTS::CranePlanFactory;
        v->__copyFrom(proxy);
    }
}

::CLTS::CranePlanPrx
IceProxy::CLTS::CranePlanFactory::getCranePlan(::Ice::Int cranePlanNo, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__CLTS__CranePlanFactory__getCranePlan_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::CranePlanFactory* __del = dynamic_cast< ::IceDelegate::CLTS::CranePlanFactory*>(__delBase.get());
            return __del->getCranePlan(cranePlanNo, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::CLTS::CranePlanFactory::begin_getCranePlan(::Ice::Int cranePlanNo, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__CLTS__CranePlanFactory__getCranePlan_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__CranePlanFactory__getCranePlan_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__CranePlanFactory__getCranePlan_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        __os->write(cranePlanNo);
        __os->endWriteEncaps();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::CLTS::CranePlanPrx
IceProxy::CLTS::CranePlanFactory::end_getCranePlan(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __CLTS__CranePlanFactory__getCranePlan_name);
    ::CLTS::CranePlanPrx __ret;
    if(!__result->__wait())
    {
        try
        {
            __result->__throwUserException();
        }
        catch(const ::CLTS::CLTSException&)
        {
            throw;
        }
        catch(const ::Ice::UserException& __ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
        }
    }
    ::IceInternal::BasicStream* __is = __result->__getIs();
    __is->startReadEncaps();
    ::CLTS::__read(__is, __ret);
    __is->endReadEncaps();
    return __ret;
}

void
IceProxy::CLTS::CranePlanFactory::initCranePlan(const ::std::string& yardNo, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__CLTS__CranePlanFactory__initCranePlan_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::CranePlanFactory* __del = dynamic_cast< ::IceDelegate::CLTS::CranePlanFactory*>(__delBase.get());
            __del->initCranePlan(yardNo, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::CLTS::CranePlanFactory::begin_initCranePlan(const ::std::string& yardNo, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__CLTS__CranePlanFactory__initCranePlan_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__CranePlanFactory__initCranePlan_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__CranePlanFactory__initCranePlan_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        __os->write(yardNo);
        __os->endWriteEncaps();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

void
IceProxy::CLTS::CranePlanFactory::end_initCranePlan(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __CLTS__CranePlanFactory__initCranePlan_name);
    if(!__result->__wait())
    {
        try
        {
            __result->__throwUserException();
        }
        catch(const ::CLTS::CLTSException&)
        {
            throw;
        }
        catch(const ::Ice::UserException& __ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
        }
    }
    ::IceInternal::BasicStream* __is = __result->__getIs();
    __is->skipEmptyEncaps();
}

const ::std::string&
IceProxy::CLTS::CranePlanFactory::ice_staticId()
{
    return ::CLTS::CranePlanFactory::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::CLTS::CranePlanFactory::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::CLTS::CranePlanFactory);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::CLTS::CranePlanFactory::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::CLTS::CranePlanFactory);
}

::IceProxy::Ice::Object*
IceProxy::CLTS::CranePlanFactory::__newInstance() const
{
    return new CranePlanFactory;
}

::CLTS::CranePlanPrx
IceDelegateM::CLTS::CranePlanFactory::getCranePlan(::Ice::Int cranePlanNo, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__CranePlanFactory__getCranePlan_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(cranePlanNo);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::CLTS::CranePlanPrx __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::CLTS::CLTSException&)
            {
                throw;
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.is();
        __is->startReadEncaps();
        ::CLTS::__read(__is, __ret);
        __is->endReadEncaps();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::CLTS::CranePlanFactory::initCranePlan(const ::std::string& yardNo, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__CranePlanFactory__initCranePlan_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(yardNo);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::CLTS::CLTSException&)
            {
                throw;
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        __og.is()->skipEmptyEncaps();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::CLTS::CranePlanPrx
IceDelegateD::CLTS::CranePlanFactory::getCranePlan(::Ice::Int cranePlanNo, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::CLTS::CranePlanPrx& __result, ::Ice::Int cranePlanNo, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_cranePlanNo(cranePlanNo)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::CranePlanFactory* servant = dynamic_cast< ::CLTS::CranePlanFactory*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            try
            {
                _result = servant->getCranePlan(_m_cranePlanNo, _current);
                return ::Ice::DispatchOK;
            }
            catch(const ::Ice::UserException& __ex)
            {
                setUserException(__ex);
                return ::Ice::DispatchUserException;
            }
        }
        
    private:
        
        ::CLTS::CranePlanPrx& _result;
        ::Ice::Int _m_cranePlanNo;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__CranePlanFactory__getCranePlan_name, ::Ice::Normal, __context);
    ::CLTS::CranePlanPrx __result;
    try
    {
        _DirectI __direct(__result, cranePlanNo, __current);
        try
        {
            __direct.servant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::CLTS::CLTSException&)
    {
        throw;
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

void
IceDelegateD::CLTS::CranePlanFactory::initCranePlan(const ::std::string& yardNo, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(const ::std::string& yardNo, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _m_yardNo(yardNo)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::CranePlanFactory* servant = dynamic_cast< ::CLTS::CranePlanFactory*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            try
            {
                servant->initCranePlan(_m_yardNo, _current);
                return ::Ice::DispatchOK;
            }
            catch(const ::Ice::UserException& __ex)
            {
                setUserException(__ex);
                return ::Ice::DispatchUserException;
            }
        }
        
    private:
        
        const ::std::string& _m_yardNo;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__CranePlanFactory__initCranePlan_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(yardNo, __current);
        try
        {
            __direct.servant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::CLTS::CLTSException&)
    {
        throw;
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
}

::Ice::ObjectPtr
CLTS::CranePlanFactory::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __CLTS__CranePlanFactory_ids[2] =
{
    "::CLTS::CranePlanFactory",
    "::Ice::Object"
};

bool
CLTS::CranePlanFactory::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__CLTS__CranePlanFactory_ids, __CLTS__CranePlanFactory_ids + 2, _s);
}

::std::vector< ::std::string>
CLTS::CranePlanFactory::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__CLTS__CranePlanFactory_ids[0], &__CLTS__CranePlanFactory_ids[2]);
}

const ::std::string&
CLTS::CranePlanFactory::ice_id(const ::Ice::Current&) const
{
    return __CLTS__CranePlanFactory_ids[0];
}

const ::std::string&
CLTS::CranePlanFactory::ice_staticId()
{
    return __CLTS__CranePlanFactory_ids[0];
}

::Ice::DispatchStatus
CLTS::CranePlanFactory::___getCranePlan(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::Ice::Int cranePlanNo;
    __is->read(cranePlanNo);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        ::CLTS::CranePlanPrx __ret = getCranePlan(cranePlanNo, __current);
        __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    }
    catch(const ::CLTS::CLTSException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
CLTS::CranePlanFactory::___initCranePlan(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::std::string yardNo;
    __is->read(yardNo);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        initCranePlan(yardNo, __current);
    }
    catch(const ::CLTS::CLTSException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}

static ::std::string __CLTS__CranePlanFactory_all[] =
{
    "getCranePlan",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "initCranePlan"
};

::Ice::DispatchStatus
CLTS::CranePlanFactory::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__CLTS__CranePlanFactory_all, __CLTS__CranePlanFactory_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __CLTS__CranePlanFactory_all)
    {
        case 0:
        {
            return ___getCranePlan(in, current);
        }
        case 1:
        {
            return ___ice_id(in, current);
        }
        case 2:
        {
            return ___ice_ids(in, current);
        }
        case 3:
        {
            return ___ice_isA(in, current);
        }
        case 4:
        {
            return ___ice_ping(in, current);
        }
        case 5:
        {
            return ___initCranePlan(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
CLTS::CranePlanFactory::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
CLTS::CranePlanFactory::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

// COMPILERFIX: Stream API is not supported with VC++ 6
#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
void
CLTS::CranePlanFactory::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type CLTS::CranePlanFactory was not generated with stream support";
    throw ex;
}

void
CLTS::CranePlanFactory::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type CLTS::CranePlanFactory was not generated with stream support";
    throw ex;
}
#endif

void 
CLTS::__patch__CranePlanFactoryPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::CLTS::CranePlanFactoryPtr* p = static_cast< ::CLTS::CranePlanFactoryPtr*>(__addr);
    assert(p);
    *p = ::CLTS::CranePlanFactoryPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::CLTS::CranePlanFactory::ice_staticId(), v->ice_id());
    }
}
