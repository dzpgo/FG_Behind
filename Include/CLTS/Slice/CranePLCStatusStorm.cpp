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
// Generated from file `CranePLCStatusStorm.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

#include <CranePLCStatusStorm.h>
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

static const ::std::string __CLTS__CranePublisher__CWatchEventHandlerI_name = "CWatchEventHandlerI";

::Ice::Object* IceInternal::upCast(::CLTS::CranePublisher* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::CLTS::CranePublisher* p) { return p; }

void
CLTS::__read(::IceInternal::BasicStream* __is, ::CLTS::CranePublisherPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::CLTS::CranePublisher;
        v->__copyFrom(proxy);
    }
}

void
CLTS::CranePLCStatusDesc::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(craneNO);
    __os->write(ready);
    __os->write(controlMode);
    __os->write(askPlan);
    __os->write(taskExcuting);
    __os->write(xAct);
    __os->write(yAct);
    __os->write(zAct);
    __os->write(xSpeed);
    __os->write(ySpeed);
    __os->write(zSpeed);
    __os->write(xDirectPositive);
    __os->write(xDirectNegative);
    __os->write(yDirectPositive);
    __os->write(yDirectNegative);
    __os->write(zDirectPositive);
    __os->write(zDirectNegative);
    __os->write(hasCoil);
    __os->write(weightLoaded);
    __os->write(rotateAngleAct);
    __os->write(clampWidthAct);
    __os->write(emgStop);
    __os->write(orderID);
    __os->write(planUpX);
    __os->write(planUpY);
    __os->write(planUpZ);
    __os->write(planDownX);
    __os->write(planDownY);
    __os->write(planDownZ);
    __os->write(craneStatus);
    __os->write(timeReceive);
}

void
CLTS::CranePLCStatusDesc::__read(::IceInternal::BasicStream* __is)
{
    __is->read(craneNO);
    __is->read(ready);
    __is->read(controlMode);
    __is->read(askPlan);
    __is->read(taskExcuting);
    __is->read(xAct);
    __is->read(yAct);
    __is->read(zAct);
    __is->read(xSpeed);
    __is->read(ySpeed);
    __is->read(zSpeed);
    __is->read(xDirectPositive);
    __is->read(xDirectNegative);
    __is->read(yDirectPositive);
    __is->read(yDirectNegative);
    __is->read(zDirectPositive);
    __is->read(zDirectNegative);
    __is->read(hasCoil);
    __is->read(weightLoaded);
    __is->read(rotateAngleAct);
    __is->read(clampWidthAct);
    __is->read(emgStop);
    __is->read(orderID);
    __is->read(planUpX);
    __is->read(planUpY);
    __is->read(planUpZ);
    __is->read(planDownX);
    __is->read(planDownY);
    __is->read(planDownZ);
    __is->read(craneStatus);
    __is->read(timeReceive);
}

void
IceProxy::CLTS::CranePublisher::CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __delBase = __getDelegate(false);
            ::IceDelegate::CLTS::CranePublisher* __del = dynamic_cast< ::IceDelegate::CLTS::CranePublisher*>(__delBase.get());
            __del->CWatchEventHandlerI(desc, __ctx);
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
IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __CLTS__CranePublisher__CWatchEventHandlerI_name, __del, __cookie);
    try
    {
        __result->__prepare(__CLTS__CranePublisher__CWatchEventHandlerI_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__getOs();
        desc.__write(__os);
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
IceProxy::CLTS::CranePublisher::end_CWatchEventHandlerI(const ::Ice::AsyncResultPtr& __result)
{
    __end(__result, __CLTS__CranePublisher__CWatchEventHandlerI_name);
}

const ::std::string&
IceProxy::CLTS::CranePublisher::ice_staticId()
{
    return ::CLTS::CranePublisher::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::CLTS::CranePublisher::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::CLTS::CranePublisher);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::CLTS::CranePublisher::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::CLTS::CranePublisher);
}

::IceProxy::Ice::Object*
IceProxy::CLTS::CranePublisher::__newInstance() const
{
    return new CranePublisher;
}

void
IceDelegateM::CLTS::CranePublisher::CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __CLTS__CranePublisher__CWatchEventHandlerI_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        desc.__write(__os);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    if(!__og.is()->b.empty())
    {
        try
        {
            if(!__ok)
            {
                try
                {
                    __og.throwUserException();
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
}

void
IceDelegateD::CLTS::CranePublisher::CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _m_desc(desc)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::CLTS::CranePublisher* servant = dynamic_cast< ::CLTS::CranePublisher*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            servant->CWatchEventHandlerI(_m_desc, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        const ::CLTS::CranePLCStatusDesc& _m_desc;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __CLTS__CranePublisher__CWatchEventHandlerI_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(desc, __current);
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
CLTS::CranePublisher::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __CLTS__CranePublisher_ids[2] =
{
    "::CLTS::CranePublisher",
    "::Ice::Object"
};

bool
CLTS::CranePublisher::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__CLTS__CranePublisher_ids, __CLTS__CranePublisher_ids + 2, _s);
}

::std::vector< ::std::string>
CLTS::CranePublisher::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__CLTS__CranePublisher_ids[0], &__CLTS__CranePublisher_ids[2]);
}

const ::std::string&
CLTS::CranePublisher::ice_id(const ::Ice::Current&) const
{
    return __CLTS__CranePublisher_ids[0];
}

const ::std::string&
CLTS::CranePublisher::ice_staticId()
{
    return __CLTS__CranePublisher_ids[0];
}

::Ice::DispatchStatus
CLTS::CranePublisher::___CWatchEventHandlerI(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::CLTS::CranePLCStatusDesc desc;
    desc.__read(__is);
    __is->endReadEncaps();
    CWatchEventHandlerI(desc, __current);
    return ::Ice::DispatchOK;
}

static ::std::string __CLTS__CranePublisher_all[] =
{
    "CWatchEventHandlerI",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::Ice::DispatchStatus
CLTS::CranePublisher::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__CLTS__CranePublisher_all, __CLTS__CranePublisher_all + 5, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __CLTS__CranePublisher_all)
    {
        case 0:
        {
            return ___CWatchEventHandlerI(in, current);
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
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
CLTS::CranePublisher::__write(::IceInternal::BasicStream* __os) const
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
CLTS::CranePublisher::__read(::IceInternal::BasicStream* __is, bool __rid)
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
CLTS::CranePublisher::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type CLTS::CranePublisher was not generated with stream support";
    throw ex;
}

void
CLTS::CranePublisher::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type CLTS::CranePublisher was not generated with stream support";
    throw ex;
}
#endif

void 
CLTS::__patch__CranePublisherPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::CLTS::CranePublisherPtr* p = static_cast< ::CLTS::CranePublisherPtr*>(__addr);
    assert(p);
    *p = ::CLTS::CranePublisherPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::CLTS::CranePublisher::ice_staticId(), v->ice_id());
    }
}
