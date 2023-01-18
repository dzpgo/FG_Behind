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
// Generated from file `CranePLCStatusStormProductYard.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

#ifndef ___________include_clts_slice_CranePLCStatusStormProductYard_h__
#define ___________include_clts_slice_CranePLCStatusStormProductYard_h__

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
#include <Ice/BuiltinSequences.h>
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

namespace CLTS
{

class CranePublisherProductYard;

}

}

namespace CLTS
{

class CranePublisherProductYard;
bool operator==(const CranePublisherProductYard&, const CranePublisherProductYard&);
bool operator<(const CranePublisherProductYard&, const CranePublisherProductYard&);

}

namespace IceInternal
{

::Ice::Object* upCast(::CLTS::CranePublisherProductYard*);
::IceProxy::Ice::Object* upCast(::IceProxy::CLTS::CranePublisherProductYard*);

}

namespace CLTS
{

typedef ::IceInternal::Handle< ::CLTS::CranePublisherProductYard> CranePublisherProductYardPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::CLTS::CranePublisherProductYard> CranePublisherProductYardPrx;

void __read(::IceInternal::BasicStream*, CranePublisherProductYardPrx&);
void __patch__CranePublisherProductYardPtr(void*, ::Ice::ObjectPtr&);

}

namespace CLTS
{

struct CranePLCStatusDescProductYard
{
    ::std::string craneNO;
    ::Ice::Long ready;
    ::Ice::Long controlMode;
    ::Ice::Long askPlan;
    ::Ice::Long taskExcuting;
    ::Ice::Long xAct;
    ::Ice::Long yAct;
    ::Ice::Long zAct;
    ::Ice::Long xSpeed;
    ::Ice::Long ySpeed;
    ::Ice::Long zSpeed;
    ::Ice::Long xDirectPositive;
    ::Ice::Long xDirectNegative;
    ::Ice::Long yDirectPositive;
    ::Ice::Long yDirectNegative;
    ::Ice::Long zDirectPositive;
    ::Ice::Long zDirectNegative;
    ::Ice::Long hasCoil;
    ::Ice::Long weightLoaded;
    ::Ice::Long rotateAngleAct;
    ::Ice::Long clampWidthAct;
    ::Ice::Long emgStop;
    ::Ice::Long orderID;
    ::Ice::Long planUpX;
    ::Ice::Long planUpY;
    ::Ice::Long planUpZ;
    ::Ice::Long planDownX;
    ::Ice::Long planDownY;
    ::Ice::Long planDownZ;
    ::Ice::Long craneStatus;
    ::std::string timeReceive;
    ::Ice::Long xExcuting;
    ::Ice::Long yExcuting;
    ::Ice::Long zExcuting;
    ::Ice::Long rExcuting;
	::Ice::Long xGear;
	::Ice::Long yGear;

    bool operator==(const CranePLCStatusDescProductYard& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(craneNO != __rhs.craneNO)
        {
            return false;
        }
        if(ready != __rhs.ready)
        {
            return false;
        }
        if(controlMode != __rhs.controlMode)
        {
            return false;
        }
        if(askPlan != __rhs.askPlan)
        {
            return false;
        }
        if(taskExcuting != __rhs.taskExcuting)
        {
            return false;
        }
        if(xAct != __rhs.xAct)
        {
            return false;
        }
        if(yAct != __rhs.yAct)
        {
            return false;
        }
        if(zAct != __rhs.zAct)
        {
            return false;
        }
        if(xSpeed != __rhs.xSpeed)
        {
            return false;
        }
        if(ySpeed != __rhs.ySpeed)
        {
            return false;
        }
        if(zSpeed != __rhs.zSpeed)
        {
            return false;
        }
        if(xDirectPositive != __rhs.xDirectPositive)
        {
            return false;
        }
        if(xDirectNegative != __rhs.xDirectNegative)
        {
            return false;
        }
        if(yDirectPositive != __rhs.yDirectPositive)
        {
            return false;
        }
        if(yDirectNegative != __rhs.yDirectNegative)
        {
            return false;
        }
        if(zDirectPositive != __rhs.zDirectPositive)
        {
            return false;
        }
        if(zDirectNegative != __rhs.zDirectNegative)
        {
            return false;
        }
        if(hasCoil != __rhs.hasCoil)
        {
            return false;
        }
        if(weightLoaded != __rhs.weightLoaded)
        {
            return false;
        }
        if(rotateAngleAct != __rhs.rotateAngleAct)
        {
            return false;
        }
        if(clampWidthAct != __rhs.clampWidthAct)
        {
            return false;
        }
        if(emgStop != __rhs.emgStop)
        {
            return false;
        }
        if(orderID != __rhs.orderID)
        {
            return false;
        }
        if(planUpX != __rhs.planUpX)
        {
            return false;
        }
        if(planUpY != __rhs.planUpY)
        {
            return false;
        }
        if(planUpZ != __rhs.planUpZ)
        {
            return false;
        }
        if(planDownX != __rhs.planDownX)
        {
            return false;
        }
        if(planDownY != __rhs.planDownY)
        {
            return false;
        }
        if(planDownZ != __rhs.planDownZ)
        {
            return false;
        }
        if(craneStatus != __rhs.craneStatus)
        {
            return false;
        }
        if(timeReceive != __rhs.timeReceive)
        {
            return false;
        }
        if(xExcuting != __rhs.xExcuting)
        {
            return false;
        }
        if(yExcuting != __rhs.yExcuting)
        {
            return false;
        }
        if(zExcuting != __rhs.zExcuting)
        {
            return false;
        }
        if(rExcuting != __rhs.rExcuting)
        {
            return false;
        }
        return true;
    }

    bool operator<(const CranePLCStatusDescProductYard& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(craneNO < __rhs.craneNO)
        {
            return true;
        }
        else if(__rhs.craneNO < craneNO)
        {
            return false;
        }
        if(ready < __rhs.ready)
        {
            return true;
        }
        else if(__rhs.ready < ready)
        {
            return false;
        }
        if(controlMode < __rhs.controlMode)
        {
            return true;
        }
        else if(__rhs.controlMode < controlMode)
        {
            return false;
        }
        if(askPlan < __rhs.askPlan)
        {
            return true;
        }
        else if(__rhs.askPlan < askPlan)
        {
            return false;
        }
        if(taskExcuting < __rhs.taskExcuting)
        {
            return true;
        }
        else if(__rhs.taskExcuting < taskExcuting)
        {
            return false;
        }
        if(xAct < __rhs.xAct)
        {
            return true;
        }
        else if(__rhs.xAct < xAct)
        {
            return false;
        }
        if(yAct < __rhs.yAct)
        {
            return true;
        }
        else if(__rhs.yAct < yAct)
        {
            return false;
        }
        if(zAct < __rhs.zAct)
        {
            return true;
        }
        else if(__rhs.zAct < zAct)
        {
            return false;
        }
        if(xSpeed < __rhs.xSpeed)
        {
            return true;
        }
        else if(__rhs.xSpeed < xSpeed)
        {
            return false;
        }
        if(ySpeed < __rhs.ySpeed)
        {
            return true;
        }
        else if(__rhs.ySpeed < ySpeed)
        {
            return false;
        }
        if(zSpeed < __rhs.zSpeed)
        {
            return true;
        }
        else if(__rhs.zSpeed < zSpeed)
        {
            return false;
        }
        if(xDirectPositive < __rhs.xDirectPositive)
        {
            return true;
        }
        else if(__rhs.xDirectPositive < xDirectPositive)
        {
            return false;
        }
        if(xDirectNegative < __rhs.xDirectNegative)
        {
            return true;
        }
        else if(__rhs.xDirectNegative < xDirectNegative)
        {
            return false;
        }
        if(yDirectPositive < __rhs.yDirectPositive)
        {
            return true;
        }
        else if(__rhs.yDirectPositive < yDirectPositive)
        {
            return false;
        }
        if(yDirectNegative < __rhs.yDirectNegative)
        {
            return true;
        }
        else if(__rhs.yDirectNegative < yDirectNegative)
        {
            return false;
        }
        if(zDirectPositive < __rhs.zDirectPositive)
        {
            return true;
        }
        else if(__rhs.zDirectPositive < zDirectPositive)
        {
            return false;
        }
        if(zDirectNegative < __rhs.zDirectNegative)
        {
            return true;
        }
        else if(__rhs.zDirectNegative < zDirectNegative)
        {
            return false;
        }
        if(hasCoil < __rhs.hasCoil)
        {
            return true;
        }
        else if(__rhs.hasCoil < hasCoil)
        {
            return false;
        }
        if(weightLoaded < __rhs.weightLoaded)
        {
            return true;
        }
        else if(__rhs.weightLoaded < weightLoaded)
        {
            return false;
        }
        if(rotateAngleAct < __rhs.rotateAngleAct)
        {
            return true;
        }
        else if(__rhs.rotateAngleAct < rotateAngleAct)
        {
            return false;
        }
        if(clampWidthAct < __rhs.clampWidthAct)
        {
            return true;
        }
        else if(__rhs.clampWidthAct < clampWidthAct)
        {
            return false;
        }
        if(emgStop < __rhs.emgStop)
        {
            return true;
        }
        else if(__rhs.emgStop < emgStop)
        {
            return false;
        }
        if(orderID < __rhs.orderID)
        {
            return true;
        }
        else if(__rhs.orderID < orderID)
        {
            return false;
        }
        if(planUpX < __rhs.planUpX)
        {
            return true;
        }
        else if(__rhs.planUpX < planUpX)
        {
            return false;
        }
        if(planUpY < __rhs.planUpY)
        {
            return true;
        }
        else if(__rhs.planUpY < planUpY)
        {
            return false;
        }
        if(planUpZ < __rhs.planUpZ)
        {
            return true;
        }
        else if(__rhs.planUpZ < planUpZ)
        {
            return false;
        }
        if(planDownX < __rhs.planDownX)
        {
            return true;
        }
        else if(__rhs.planDownX < planDownX)
        {
            return false;
        }
        if(planDownY < __rhs.planDownY)
        {
            return true;
        }
        else if(__rhs.planDownY < planDownY)
        {
            return false;
        }
        if(planDownZ < __rhs.planDownZ)
        {
            return true;
        }
        else if(__rhs.planDownZ < planDownZ)
        {
            return false;
        }
        if(craneStatus < __rhs.craneStatus)
        {
            return true;
        }
        else if(__rhs.craneStatus < craneStatus)
        {
            return false;
        }
        if(timeReceive < __rhs.timeReceive)
        {
            return true;
        }
        else if(__rhs.timeReceive < timeReceive)
        {
            return false;
        }
        if(xExcuting < __rhs.xExcuting)
        {
            return true;
        }
        else if(__rhs.xExcuting < xExcuting)
        {
            return false;
        }
        if(yExcuting < __rhs.yExcuting)
        {
            return true;
        }
        else if(__rhs.yExcuting < yExcuting)
        {
            return false;
        }
        if(zExcuting < __rhs.zExcuting)
        {
            return true;
        }
        else if(__rhs.zExcuting < zExcuting)
        {
            return false;
        }
        if(rExcuting < __rhs.rExcuting)
        {
            return true;
        }
        else if(__rhs.rExcuting < rExcuting)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const CranePLCStatusDescProductYard& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const CranePLCStatusDescProductYard& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const CranePLCStatusDescProductYard& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const CranePLCStatusDescProductYard& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

}

namespace CLTS
{

class Callback_CranePublisherProductYard_CWatchEventHandlerI_Base : virtual public ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_CranePublisherProductYard_CWatchEventHandlerI_Base> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr;

}

namespace IceProxy
{

namespace CLTS
{

class CranePublisherProductYard : virtual public ::IceProxy::Ice::Object
{
public:

    void CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard& desc)
    {
        CWatchEventHandlerI(desc, 0);
    }
    void CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard& desc, const ::Ice::Context& __ctx)
    {
        CWatchEventHandlerI(desc, &__ctx);
    }

    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard& desc)
    {
        return begin_CWatchEventHandlerI(desc, 0, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard& desc, const ::Ice::Context& __ctx)
    {
        return begin_CWatchEventHandlerI(desc, &__ctx, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard& desc, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_CWatchEventHandlerI(desc, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard& desc, const ::Ice::Context& __ctx, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_CWatchEventHandlerI(desc, &__ctx, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard& desc, const ::CLTS::Callback_CranePublisherProductYard_CWatchEventHandlerIPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_CWatchEventHandlerI(desc, 0, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard& desc, const ::Ice::Context& __ctx, const ::CLTS::Callback_CranePublisherProductYard_CWatchEventHandlerIPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return begin_CWatchEventHandlerI(desc, &__ctx, __del, __cookie);
    }

    void end_CWatchEventHandlerI(const ::Ice::AsyncResultPtr&);
    
private:

    void CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard&, const ::Ice::Context*);
    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard&, const ::Ice::Context*, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& __cookie = 0);
    
public:
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CranePublisherProductYard> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CranePublisherProductYard*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<CranePublisherProductYard*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

namespace CLTS
{

class CranePublisherProductYard : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard&, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace CLTS
{

class CranePublisherProductYard : virtual public ::IceDelegate::CLTS::CranePublisherProductYard,
                                  virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard&, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace CLTS
{

class CranePublisherProductYard : virtual public ::IceDelegate::CLTS::CranePublisherProductYard,
                                  virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard&, const ::Ice::Context*);
};

}

}

namespace CLTS
{

class CranePublisherProductYard : virtual public ::Ice::Object
{
public:

    typedef CranePublisherProductYardPrx ProxyType;
    typedef CranePublisherProductYardPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void CWatchEventHandlerI(const ::CLTS::CranePLCStatusDescProductYard&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___CWatchEventHandlerI(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
// COMPILERFIX: Stream API is not supported with VC++ 6
#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
#endif
};

inline bool operator==(const CranePublisherProductYard& l, const CranePublisherProductYard& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

inline bool operator<(const CranePublisherProductYard& l, const CranePublisherProductYard& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

}

namespace CLTS
{

template<class T>
class CallbackNC_CranePublisherProductYard_CWatchEventHandlerI : public Callback_CranePublisherProductYard_CWatchEventHandlerI_Base, public ::IceInternal::OnewayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)();

    CallbackNC_CranePublisherProductYard_CWatchEventHandlerI(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallbackNC<T>(obj, cb, excb, sentcb)
    {
    }
};

template<class T> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr
newCallback_CranePublisherProductYard_CWatchEventHandlerI(const IceUtil::Handle<T>& instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_CranePublisherProductYard_CWatchEventHandlerI<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr
newCallback_CranePublisherProductYard_CWatchEventHandlerI(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_CranePublisherProductYard_CWatchEventHandlerI<T>(instance, 0, excb, sentcb);
}

template<class T> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr
newCallback_CranePublisherProductYard_CWatchEventHandlerI(T* instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_CranePublisherProductYard_CWatchEventHandlerI<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr
newCallback_CranePublisherProductYard_CWatchEventHandlerI(T* instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_CranePublisherProductYard_CWatchEventHandlerI<T>(instance, 0, excb, sentcb);
}

template<class T, typename CT>
class Callback_CranePublisherProductYard_CWatchEventHandlerI : public Callback_CranePublisherProductYard_CWatchEventHandlerI_Base, public ::IceInternal::OnewayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const CT&);

    Callback_CranePublisherProductYard_CWatchEventHandlerI(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallback<T, CT>(obj, cb, excb, sentcb)
    {
    }
};

template<class T, typename CT> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr
newCallback_CranePublisherProductYard_CWatchEventHandlerI(const IceUtil::Handle<T>& instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_CranePublisherProductYard_CWatchEventHandlerI<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr
newCallback_CranePublisherProductYard_CWatchEventHandlerI(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_CranePublisherProductYard_CWatchEventHandlerI<T, CT>(instance, 0, excb, sentcb);
}

template<class T, typename CT> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr
newCallback_CranePublisherProductYard_CWatchEventHandlerI(T* instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_CranePublisherProductYard_CWatchEventHandlerI<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_CranePublisherProductYard_CWatchEventHandlerIPtr
newCallback_CranePublisherProductYard_CWatchEventHandlerI(T* instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_CranePublisherProductYard_CWatchEventHandlerI<T, CT>(instance, 0, excb, sentcb);
}

}

#endif
