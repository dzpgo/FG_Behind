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
// Generated from file `CraneOrderFactory.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

#include <CraneOrderFactory.h>
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

static const ::std::string __CLTS__CraneOrderFactory__getCraneOrder_name = "getCraneOrder";

static const ::std::string __CLTS__CraneOrderFactory__createCraneOrder_name = "createCraneOrder";

static const ::std::string __CLTS__CraneOrderFactory__reponseRecommendToOrder_name = "reponseRecommendToOrder";

::Ice::Object* IceInternal::upCast(::CLTS::CraneOrderFactory* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::CLTS::CraneOrderFactory* p) { return p; }

void
CLTS::__read(::IceInternal::BasicStream* __is, ::CLTS::CraneOrderFactoryPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::CLTS::CraneOrderFactory;
        v->__copyFrom(proxy);
    }
}

::CLTS::CraneOrderPrx
IceProxy::CLTS::CraneOrderFactory::getCraneOrder(::Ice::Int craneOrderNo, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__CLTS__CraneOrderFactory__getCraneOrder_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::CraneOrderFactory* __del = dynamic_cast< ::IceDelegate::CLTS::CraneOrderFactory*>(__delBase.get());
            return __del->getCraneOrder(craneOrderNo, __ctx);
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
IceProxy::CLTS::CraneOrderFactory::begin_getCraneOrder(::Ice::Int craneOrderNo, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__CLTS__CraneOrderFactory__getCraneOrder_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__CraneOrderFactory__getCraneOrder_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__CraneOrderFactory__getCraneOrder_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        __os->write(craneOrderNo);
        __os->endWriteEncaps();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::CLTS::CraneOrderPrx
IceProxy::CLTS::CraneOrderFactory::end_getCraneOrder(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __CLTS__CraneOrderFactory__getCraneOrder_name);
    ::CLTS::CraneOrderPrx __ret;
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

::CLTS::CraneOrderPrx
IceProxy::CLTS::CraneOrderFactory::createCraneOrder(const ::std::string& matNo, ::Ice::Int orderType, const ::std::string& toStockNo, const ::std::string& craneNo, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__CLTS__CraneOrderFactory__createCraneOrder_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::CraneOrderFactory* __del = dynamic_cast< ::IceDelegate::CLTS::CraneOrderFactory*>(__delBase.get());
            return __del->createCraneOrder(matNo, orderType, toStockNo, craneNo, __ctx);
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
IceProxy::CLTS::CraneOrderFactory::begin_createCraneOrder(const ::std::string& matNo, ::Ice::Int orderType, const ::std::string& toStockNo, const ::std::string& craneNo, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__CLTS__CraneOrderFactory__createCraneOrder_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__CraneOrderFactory__createCraneOrder_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__CraneOrderFactory__createCraneOrder_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        __os->write(matNo);
        __os->write(orderType);
        __os->write(toStockNo);
        __os->write(craneNo);
        __os->endWriteEncaps();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::CLTS::CraneOrderPrx
IceProxy::CLTS::CraneOrderFactory::end_createCraneOrder(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __CLTS__CraneOrderFactory__createCraneOrder_name);
    ::CLTS::CraneOrderPrx __ret;
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
IceProxy::CLTS::CraneOrderFactory::reponseRecommendToOrder(const ::CLTS::RecommRepoDesc& reponse, const ::std::string& stockNo, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__CLTS__CraneOrderFactory__reponseRecommendToOrder_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::CraneOrderFactory* __del = dynamic_cast< ::IceDelegate::CLTS::CraneOrderFactory*>(__delBase.get());
            __del->reponseRecommendToOrder(reponse, stockNo, __ctx);
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
IceProxy::CLTS::CraneOrderFactory::begin_reponseRecommendToOrder(const ::CLTS::RecommRepoDesc& reponse, const ::std::string& stockNo, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__CLTS__CraneOrderFactory__reponseRecommendToOrder_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__CraneOrderFactory__reponseRecommendToOrder_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__CraneOrderFactory__reponseRecommendToOrder_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        reponse.__write(__os);
        __os->write(stockNo);
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
IceProxy::CLTS::CraneOrderFactory::end_reponseRecommendToOrder(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __CLTS__CraneOrderFactory__reponseRecommendToOrder_name);
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
IceProxy::CLTS::CraneOrderFactory::ice_staticId()
{
    return ::CLTS::CraneOrderFactory::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::CLTS::CraneOrderFactory::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::CLTS::CraneOrderFactory);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::CLTS::CraneOrderFactory::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::CLTS::CraneOrderFactory);
}

::IceProxy::Ice::Object*
IceProxy::CLTS::CraneOrderFactory::__newInstance() const
{
    return new CraneOrderFactory;
}

::CLTS::CraneOrderPrx
IceDelegateM::CLTS::CraneOrderFactory::getCraneOrder(::Ice::Int craneOrderNo, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__CraneOrderFactory__getCraneOrder_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(craneOrderNo);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::CLTS::CraneOrderPrx __ret;
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

::CLTS::CraneOrderPrx
IceDelegateM::CLTS::CraneOrderFactory::createCraneOrder(const ::std::string& matNo, ::Ice::Int orderType, const ::std::string& toStockNo, const ::std::string& craneNo, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__CraneOrderFactory__createCraneOrder_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(matNo);
        __os->write(orderType);
        __os->write(toStockNo);
        __os->write(craneNo);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::CLTS::CraneOrderPrx __ret;
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
IceDelegateM::CLTS::CraneOrderFactory::reponseRecommendToOrder(const ::CLTS::RecommRepoDesc& reponse, const ::std::string& stockNo, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__CraneOrderFactory__reponseRecommendToOrder_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        reponse.__write(__os);
        __os->write(stockNo);
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

::CLTS::CraneOrderPrx
IceDelegateD::CLTS::CraneOrderFactory::getCraneOrder(::Ice::Int craneOrderNo, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::CLTS::CraneOrderPrx& __result, ::Ice::Int craneOrderNo, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_craneOrderNo(craneOrderNo)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::CraneOrderFactory* servant = dynamic_cast< ::CLTS::CraneOrderFactory*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            try
            {
                _result = servant->getCraneOrder(_m_craneOrderNo, _current);
                return ::Ice::DispatchOK;
            }
            catch(const ::Ice::UserException& __ex)
            {
                setUserException(__ex);
                return ::Ice::DispatchUserException;
            }
        }
        
    private:
        
        ::CLTS::CraneOrderPrx& _result;
        ::Ice::Int _m_craneOrderNo;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__CraneOrderFactory__getCraneOrder_name, ::Ice::Normal, __context);
    ::CLTS::CraneOrderPrx __result;
    try
    {
        _DirectI __direct(__result, craneOrderNo, __current);
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

::CLTS::CraneOrderPrx
IceDelegateD::CLTS::CraneOrderFactory::createCraneOrder(const ::std::string& matNo, ::Ice::Int orderType, const ::std::string& toStockNo, const ::std::string& craneNo, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::CLTS::CraneOrderPrx& __result, const ::std::string& matNo, ::Ice::Int orderType, const ::std::string& toStockNo, const ::std::string& craneNo, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_matNo(matNo),
            _m_orderType(orderType),
            _m_toStockNo(toStockNo),
            _m_craneNo(craneNo)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::CraneOrderFactory* servant = dynamic_cast< ::CLTS::CraneOrderFactory*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            try
            {
                _result = servant->createCraneOrder(_m_matNo, _m_orderType, _m_toStockNo, _m_craneNo, _current);
                return ::Ice::DispatchOK;
            }
            catch(const ::Ice::UserException& __ex)
            {
                setUserException(__ex);
                return ::Ice::DispatchUserException;
            }
        }
        
    private:
        
        ::CLTS::CraneOrderPrx& _result;
        const ::std::string& _m_matNo;
        ::Ice::Int _m_orderType;
        const ::std::string& _m_toStockNo;
        const ::std::string& _m_craneNo;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__CraneOrderFactory__createCraneOrder_name, ::Ice::Normal, __context);
    ::CLTS::CraneOrderPrx __result;
    try
    {
        _DirectI __direct(__result, matNo, orderType, toStockNo, craneNo, __current);
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
IceDelegateD::CLTS::CraneOrderFactory::reponseRecommendToOrder(const ::CLTS::RecommRepoDesc& reponse, const ::std::string& stockNo, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(const ::CLTS::RecommRepoDesc& reponse, const ::std::string& stockNo, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _m_reponse(reponse),
            _m_stockNo(stockNo)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::CraneOrderFactory* servant = dynamic_cast< ::CLTS::CraneOrderFactory*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            try
            {
                servant->reponseRecommendToOrder(_m_reponse, _m_stockNo, _current);
                return ::Ice::DispatchOK;
            }
            catch(const ::Ice::UserException& __ex)
            {
                setUserException(__ex);
                return ::Ice::DispatchUserException;
            }
        }
        
    private:
        
        const ::CLTS::RecommRepoDesc& _m_reponse;
        const ::std::string& _m_stockNo;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__CraneOrderFactory__reponseRecommendToOrder_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(reponse, stockNo, __current);
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
CLTS::CraneOrderFactory::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __CLTS__CraneOrderFactory_ids[2] =
{
    "::CLTS::CraneOrderFactory",
    "::Ice::Object"
};

bool
CLTS::CraneOrderFactory::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__CLTS__CraneOrderFactory_ids, __CLTS__CraneOrderFactory_ids + 2, _s);
}

::std::vector< ::std::string>
CLTS::CraneOrderFactory::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__CLTS__CraneOrderFactory_ids[0], &__CLTS__CraneOrderFactory_ids[2]);
}

const ::std::string&
CLTS::CraneOrderFactory::ice_id(const ::Ice::Current&) const
{
    return __CLTS__CraneOrderFactory_ids[0];
}

const ::std::string&
CLTS::CraneOrderFactory::ice_staticId()
{
    return __CLTS__CraneOrderFactory_ids[0];
}

::Ice::DispatchStatus
CLTS::CraneOrderFactory::___getCraneOrder(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::Ice::Int craneOrderNo;
    __is->read(craneOrderNo);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        ::CLTS::CraneOrderPrx __ret = getCraneOrder(craneOrderNo, __current);
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
CLTS::CraneOrderFactory::___createCraneOrder(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::std::string matNo;
    ::Ice::Int orderType;
    ::std::string toStockNo;
    ::std::string craneNo;
    __is->read(matNo);
    __is->read(orderType);
    __is->read(toStockNo);
    __is->read(craneNo);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        ::CLTS::CraneOrderPrx __ret = createCraneOrder(matNo, orderType, toStockNo, craneNo, __current);
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
CLTS::CraneOrderFactory::___reponseRecommendToOrder(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::CLTS::RecommRepoDesc reponse;
    ::std::string stockNo;
    reponse.__read(__is);
    __is->read(stockNo);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        reponseRecommendToOrder(reponse, stockNo, __current);
    }
    catch(const ::CLTS::CLTSException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}

static ::std::string __CLTS__CraneOrderFactory_all[] =
{
    "createCraneOrder",
    "getCraneOrder",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "reponseRecommendToOrder"
};

::Ice::DispatchStatus
CLTS::CraneOrderFactory::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__CLTS__CraneOrderFactory_all, __CLTS__CraneOrderFactory_all + 7, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __CLTS__CraneOrderFactory_all)
    {
        case 0:
        {
            return ___createCraneOrder(in, current);
        }
        case 1:
        {
            return ___getCraneOrder(in, current);
        }
        case 2:
        {
            return ___ice_id(in, current);
        }
        case 3:
        {
            return ___ice_ids(in, current);
        }
        case 4:
        {
            return ___ice_isA(in, current);
        }
        case 5:
        {
            return ___ice_ping(in, current);
        }
        case 6:
        {
            return ___reponseRecommendToOrder(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
CLTS::CraneOrderFactory::__write(::IceInternal::BasicStream* __os) const
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
CLTS::CraneOrderFactory::__read(::IceInternal::BasicStream* __is, bool __rid)
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
CLTS::CraneOrderFactory::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type CLTS::CraneOrderFactory was not generated with stream support";
    throw ex;
}

void
CLTS::CraneOrderFactory::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type CLTS::CraneOrderFactory was not generated with stream support";
    throw ex;
}
#endif

void 
CLTS::__patch__CraneOrderFactoryPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::CLTS::CraneOrderFactoryPtr* p = static_cast< ::CLTS::CraneOrderFactoryPtr*>(__addr);
    assert(p);
    *p = ::CLTS::CraneOrderFactoryPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::CLTS::CraneOrderFactory::ice_staticId(), v->ice_id());
    }
}
