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
// Generated from file `LoadUnloadFactory.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

#include <LoadUnloadFactory.h>
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

static const ::std::string __CLTS__LoadUnLoadFactory__createLoadStock_name = "createLoadStock";

static const ::std::string __CLTS__LoadUnLoadFactory__createUnLoadStock_name = "createUnLoadStock";

static const ::std::string __CLTS__LoadUnLoadFactory__resetParkingStock_name = "resetParkingStock";

::Ice::Object* IceInternal::upCast(::CLTS::LoadUnLoadFactory* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::CLTS::LoadUnLoadFactory* p) { return p; }

void
CLTS::__read(::IceInternal::BasicStream* __is, ::CLTS::LoadUnLoadFactoryPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::CLTS::LoadUnLoadFactory;
        v->__copyFrom(proxy);
    }
}

void
IceProxy::CLTS::LoadUnLoadFactory::createLoadStock(::Ice::Int stowageID, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__CLTS__LoadUnLoadFactory__createLoadStock_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::LoadUnLoadFactory* __del = dynamic_cast< ::IceDelegate::CLTS::LoadUnLoadFactory*>(__delBase.get());
            __del->createLoadStock(stowageID, __ctx);
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
IceProxy::CLTS::LoadUnLoadFactory::begin_createLoadStock(::Ice::Int stowageID, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__CLTS__LoadUnLoadFactory__createLoadStock_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__LoadUnLoadFactory__createLoadStock_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__LoadUnLoadFactory__createLoadStock_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        __os->write(stowageID);
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
IceProxy::CLTS::LoadUnLoadFactory::end_createLoadStock(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __CLTS__LoadUnLoadFactory__createLoadStock_name);
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

void
IceProxy::CLTS::LoadUnLoadFactory::createUnLoadStock(::Ice::Int stowageID, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__CLTS__LoadUnLoadFactory__createUnLoadStock_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::LoadUnLoadFactory* __del = dynamic_cast< ::IceDelegate::CLTS::LoadUnLoadFactory*>(__delBase.get());
            __del->createUnLoadStock(stowageID, __ctx);
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
IceProxy::CLTS::LoadUnLoadFactory::begin_createUnLoadStock(::Ice::Int stowageID, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__CLTS__LoadUnLoadFactory__createUnLoadStock_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__LoadUnLoadFactory__createUnLoadStock_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__LoadUnLoadFactory__createUnLoadStock_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        __os->write(stowageID);
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
IceProxy::CLTS::LoadUnLoadFactory::end_createUnLoadStock(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __CLTS__LoadUnLoadFactory__createUnLoadStock_name);
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

void
IceProxy::CLTS::LoadUnLoadFactory::resetParkingStock(const ::std::string& parkingNo, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__CLTS__LoadUnLoadFactory__resetParkingStock_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::LoadUnLoadFactory* __del = dynamic_cast< ::IceDelegate::CLTS::LoadUnLoadFactory*>(__delBase.get());
            __del->resetParkingStock(parkingNo, __ctx);
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
IceProxy::CLTS::LoadUnLoadFactory::begin_resetParkingStock(const ::std::string& parkingNo, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__CLTS__LoadUnLoadFactory__resetParkingStock_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__LoadUnLoadFactory__resetParkingStock_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__LoadUnLoadFactory__resetParkingStock_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        __os->write(parkingNo);
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
IceProxy::CLTS::LoadUnLoadFactory::end_resetParkingStock(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __CLTS__LoadUnLoadFactory__resetParkingStock_name);
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
IceProxy::CLTS::LoadUnLoadFactory::ice_staticId()
{
    return ::CLTS::LoadUnLoadFactory::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::CLTS::LoadUnLoadFactory::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::CLTS::LoadUnLoadFactory);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::CLTS::LoadUnLoadFactory::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::CLTS::LoadUnLoadFactory);
}

::IceProxy::Ice::Object*
IceProxy::CLTS::LoadUnLoadFactory::__newInstance() const
{
    return new LoadUnLoadFactory;
}

void
IceDelegateM::CLTS::LoadUnLoadFactory::createLoadStock(::Ice::Int stowageID, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__LoadUnLoadFactory__createLoadStock_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(stowageID);
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

void
IceDelegateM::CLTS::LoadUnLoadFactory::createUnLoadStock(::Ice::Int stowageID, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__LoadUnLoadFactory__createUnLoadStock_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(stowageID);
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

void
IceDelegateM::CLTS::LoadUnLoadFactory::resetParkingStock(const ::std::string& parkingNo, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__LoadUnLoadFactory__resetParkingStock_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(parkingNo);
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

void
IceDelegateD::CLTS::LoadUnLoadFactory::createLoadStock(::Ice::Int stowageID, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::Ice::Int stowageID, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _m_stowageID(stowageID)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::LoadUnLoadFactory* servant = dynamic_cast< ::CLTS::LoadUnLoadFactory*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            try
            {
                servant->createLoadStock(_m_stowageID, _current);
                return ::Ice::DispatchOK;
            }
            catch(const ::Ice::UserException& __ex)
            {
                setUserException(__ex);
                return ::Ice::DispatchUserException;
            }
        }
        
    private:
        
        ::Ice::Int _m_stowageID;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__LoadUnLoadFactory__createLoadStock_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(stowageID, __current);
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

void
IceDelegateD::CLTS::LoadUnLoadFactory::createUnLoadStock(::Ice::Int stowageID, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::Ice::Int stowageID, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _m_stowageID(stowageID)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::LoadUnLoadFactory* servant = dynamic_cast< ::CLTS::LoadUnLoadFactory*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            try
            {
                servant->createUnLoadStock(_m_stowageID, _current);
                return ::Ice::DispatchOK;
            }
            catch(const ::Ice::UserException& __ex)
            {
                setUserException(__ex);
                return ::Ice::DispatchUserException;
            }
        }
        
    private:
        
        ::Ice::Int _m_stowageID;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__LoadUnLoadFactory__createUnLoadStock_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(stowageID, __current);
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

void
IceDelegateD::CLTS::LoadUnLoadFactory::resetParkingStock(const ::std::string& parkingNo, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(const ::std::string& parkingNo, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _m_parkingNo(parkingNo)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::LoadUnLoadFactory* servant = dynamic_cast< ::CLTS::LoadUnLoadFactory*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            try
            {
                servant->resetParkingStock(_m_parkingNo, _current);
                return ::Ice::DispatchOK;
            }
            catch(const ::Ice::UserException& __ex)
            {
                setUserException(__ex);
                return ::Ice::DispatchUserException;
            }
        }
        
    private:
        
        const ::std::string& _m_parkingNo;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__LoadUnLoadFactory__resetParkingStock_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(parkingNo, __current);
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
CLTS::LoadUnLoadFactory::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __CLTS__LoadUnLoadFactory_ids[2] =
{
    "::CLTS::LoadUnLoadFactory",
    "::Ice::Object"
};

bool
CLTS::LoadUnLoadFactory::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__CLTS__LoadUnLoadFactory_ids, __CLTS__LoadUnLoadFactory_ids + 2, _s);
}

::std::vector< ::std::string>
CLTS::LoadUnLoadFactory::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__CLTS__LoadUnLoadFactory_ids[0], &__CLTS__LoadUnLoadFactory_ids[2]);
}

const ::std::string&
CLTS::LoadUnLoadFactory::ice_id(const ::Ice::Current&) const
{
    return __CLTS__LoadUnLoadFactory_ids[0];
}

const ::std::string&
CLTS::LoadUnLoadFactory::ice_staticId()
{
    return __CLTS__LoadUnLoadFactory_ids[0];
}

::Ice::DispatchStatus
CLTS::LoadUnLoadFactory::___createLoadStock(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::Ice::Int stowageID;
    __is->read(stowageID);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        createLoadStock(stowageID, __current);
    }
    catch(const ::CLTS::CLTSException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
CLTS::LoadUnLoadFactory::___createUnLoadStock(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::Ice::Int stowageID;
    __is->read(stowageID);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        createUnLoadStock(stowageID, __current);
    }
    catch(const ::CLTS::CLTSException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
CLTS::LoadUnLoadFactory::___resetParkingStock(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::std::string parkingNo;
    __is->read(parkingNo);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        resetParkingStock(parkingNo, __current);
    }
    catch(const ::CLTS::CLTSException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}

static ::std::string __CLTS__LoadUnLoadFactory_all[] =
{
    "createLoadStock",
    "createUnLoadStock",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "resetParkingStock"
};

::Ice::DispatchStatus
CLTS::LoadUnLoadFactory::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__CLTS__LoadUnLoadFactory_all, __CLTS__LoadUnLoadFactory_all + 7, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __CLTS__LoadUnLoadFactory_all)
    {
        case 0:
        {
            return ___createLoadStock(in, current);
        }
        case 1:
        {
            return ___createUnLoadStock(in, current);
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
            return ___resetParkingStock(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
CLTS::LoadUnLoadFactory::__write(::IceInternal::BasicStream* __os) const
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
CLTS::LoadUnLoadFactory::__read(::IceInternal::BasicStream* __is, bool __rid)
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
CLTS::LoadUnLoadFactory::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type CLTS::LoadUnLoadFactory was not generated with stream support";
    throw ex;
}

void
CLTS::LoadUnLoadFactory::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type CLTS::LoadUnLoadFactory was not generated with stream support";
    throw ex;
}
#endif

void 
CLTS::__patch__LoadUnLoadFactoryPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::CLTS::LoadUnLoadFactoryPtr* p = static_cast< ::CLTS::LoadUnLoadFactoryPtr*>(__addr);
    assert(p);
    *p = ::CLTS::LoadUnLoadFactoryPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::CLTS::LoadUnLoadFactory::ice_staticId(), v->ice_id());
    }
}
