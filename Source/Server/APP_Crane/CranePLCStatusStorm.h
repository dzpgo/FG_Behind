// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.7.1
//
// <auto-generated>
//
// Generated from file `CranePLCStatusStorm.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __CranePLCStatusStorm_h__
#define __CranePLCStatusStorm_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/GCObject.h>
#include <Ice/Value.h>
#include <Ice/Incoming.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/Optional.h>
#include <Ice/BuiltinSequences.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace CLTS
{

class CranePublisher;
class CranePublisherPrx;

}

namespace CLTS
{

/**
 * 行车状态信息
 */
struct CranePLCStatusDesc
{
    ::std::string craneNO;
    long long int ready;
    long long int controlMode;
    long long int askPlan;
    long long int taskExcuting;
    long long int xAct;
    long long int yAct;
    long long int zAct;
    long long int xSpeed;
    long long int ySpeed;
    long long int zSpeed;
    long long int xDirectPositive;
    long long int xDirectNegative;
    long long int yDirectPositive;
    long long int yDirectNegative;
    long long int zDirectPositive;
    long long int zDirectNegative;
    long long int hasCoil;
    long long int weightLoaded;
    long long int rotateAngleAct;
    long long int emgStop;
    long long int orderID;
    long long int planUpX;
    long long int planUpY;
    long long int planUpZ;
    long long int planDownX;
    long long int planDownY;
    long long int planDownZ;
    long long int craneStatus;
    long long int craneAlarm;
    ::std::string timeReceive;

    /**
     * Obtains a tuple containing all of the exception's data members.
     * @return The data members in a tuple.
     */

    std::tuple<const ::std::string&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const long long int&, const ::std::string&> ice_tuple() const
    {
        return std::tie(craneNO, ready, controlMode, askPlan, taskExcuting, xAct, yAct, zAct, xSpeed, ySpeed, zSpeed, xDirectPositive, xDirectNegative, yDirectPositive, yDirectNegative, zDirectPositive, zDirectNegative, hasCoil, weightLoaded, rotateAngleAct, emgStop, orderID, planUpX, planUpY, planUpZ, planDownX, planDownY, planDownZ, craneStatus, craneAlarm, timeReceive);
    }
};

using Ice::operator<;
using Ice::operator<=;
using Ice::operator>;
using Ice::operator>=;
using Ice::operator==;
using Ice::operator!=;

}

namespace CLTS
{

/**
 * 行车发布接口
 */
class CranePublisher : public virtual ::Ice::Object
{
public:

    using ProxyType = CranePublisherPrx;

    /**
     * Determines whether this object supports an interface with the given Slice type ID.
     * @param id The fully-scoped Slice type ID.
     * @param current The Current object for the invocation.
     * @return True if this object supports the interface, false, otherwise.
     */
    virtual bool ice_isA(::std::string id, const ::Ice::Current& current) const override;

    /**
     * Obtains a list of the Slice type IDs representing the interfaces supported by this object.
     * @param current The Current object for the invocation.
     * @return A list of fully-scoped type IDs.
     */
    virtual ::std::vector<::std::string> ice_ids(const ::Ice::Current& current) const override;

    /**
     * Obtains a Slice type ID representing the most-derived interface supported by this object.
     * @param current The Current object for the invocation.
     * @return A fully-scoped type ID.
     */
    virtual ::std::string ice_id(const ::Ice::Current& current) const override;

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param current The Current object for the invocation.
     */
    virtual void CWatchEventHandlerI(CranePLCStatusDesc desc, const ::Ice::Current& current) = 0;
    /// \cond INTERNAL
    bool _iceD_CWatchEventHandlerI(::IceInternal::Incoming&, const ::Ice::Current&);
    /// \endcond

    /// \cond INTERNAL
    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&) override;
    /// \endcond
};

}

namespace CLTS
{

/**
 * 行车发布接口
 */
class CranePublisherPrx : public virtual ::Ice::Proxy<CranePublisherPrx, ::Ice::ObjectPrx>
{
public:

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param context The Context map to send with the invocation.
     */
    void CWatchEventHandlerI(const CranePLCStatusDesc& desc, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        _makePromiseOutgoing<void>(true, this, &CranePublisherPrx::_iceI_CWatchEventHandlerI, desc, context).get();
    }

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param context The Context map to send with the invocation.
     * @return The future object for the invocation.
     */
    template<template<typename> class P = ::std::promise>
    auto CWatchEventHandlerIAsync(const CranePLCStatusDesc& desc, const ::Ice::Context& context = ::Ice::noExplicitContext)
        -> decltype(::std::declval<P<void>>().get_future())
    {
        return _makePromiseOutgoing<void, P>(false, this, &CranePublisherPrx::_iceI_CWatchEventHandlerI, desc, context);
    }

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param response The response callback.
     * @param ex The exception callback.
     * @param sent The sent callback.
     * @param context The Context map to send with the invocation.
     * @return A function that can be called to cancel the invocation locally.
     */
    ::std::function<void()>
    CWatchEventHandlerIAsync(const CranePLCStatusDesc& desc,
                             ::std::function<void()> response,
                             ::std::function<void(::std::exception_ptr)> ex = nullptr,
                             ::std::function<void(bool)> sent = nullptr,
                             const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<void>(response, ex, sent, this, &CranePublisherPrx::_iceI_CWatchEventHandlerI, desc, context);
    }

    /// \cond INTERNAL
    void _iceI_CWatchEventHandlerI(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<void>>&, const CranePLCStatusDesc&, const ::Ice::Context&);
    /// \endcond

    /**
     * Obtains the Slice type ID of this interface.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:

    /// \cond INTERNAL
    CranePublisherPrx() = default;
    friend ::std::shared_ptr<CranePublisherPrx> IceInternal::createProxy<CranePublisherPrx>();

    virtual ::std::shared_ptr<::Ice::ObjectPrx> _newInstance() const override;
    /// \endcond
};

}

/// \cond STREAM
namespace Ice
{

template<>
struct StreamableTraits<::CLTS::CranePLCStatusDesc>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 234;
    static const bool fixedLength = false;
};

template<typename S>
struct StreamReader<::CLTS::CranePLCStatusDesc, S>
{
    static void read(S* istr, ::CLTS::CranePLCStatusDesc& v)
    {
        istr->readAll(v.craneNO, v.ready, v.controlMode, v.askPlan, v.taskExcuting, v.xAct, v.yAct, v.zAct, v.xSpeed, v.ySpeed, v.zSpeed, v.xDirectPositive, v.xDirectNegative, v.yDirectPositive, v.yDirectNegative, v.zDirectPositive, v.zDirectNegative, v.hasCoil, v.weightLoaded, v.rotateAngleAct, v.emgStop, v.orderID, v.planUpX, v.planUpY, v.planUpZ, v.planDownX, v.planDownY, v.planDownZ, v.craneStatus, v.craneAlarm, v.timeReceive);
    }
};

}
/// \endcond

/// \cond INTERNAL
namespace CLTS
{

using CranePublisherPtr = ::std::shared_ptr<CranePublisher>;
using CranePublisherPrxPtr = ::std::shared_ptr<CranePublisherPrx>;

}
/// \endcond

#else // C++98 mapping

namespace IceProxy
{

namespace CLTS
{

class CranePublisher;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< ::IceProxy::CLTS::CranePublisher>&);
::IceProxy::Ice::Object* upCast(::IceProxy::CLTS::CranePublisher*);
/// \endcond

}

}

namespace CLTS
{

class CranePublisher;
/// \cond INTERNAL
::Ice::Object* upCast(CranePublisher*);
/// \endcond
typedef ::IceInternal::Handle< CranePublisher> CranePublisherPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::CLTS::CranePublisher> CranePublisherPrx;
typedef CranePublisherPrx CranePublisherPrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(CranePublisherPtr&, const ::Ice::ObjectPtr&);
/// \endcond

}

namespace CLTS
{

/**
 * 行车状态信息
 */
struct CranePLCStatusDesc
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
    ::Ice::Long emgStop;
    ::Ice::Long orderID;
    ::Ice::Long planUpX;
    ::Ice::Long planUpY;
    ::Ice::Long planUpZ;
    ::Ice::Long planDownX;
    ::Ice::Long planDownY;
    ::Ice::Long planDownZ;
    ::Ice::Long craneStatus;
    ::Ice::Long craneAlarm;
    ::std::string timeReceive;

    bool operator==(const CranePLCStatusDesc& rhs_) const
    {
        if(this == &rhs_)
        {
            return true;
        }
        if(craneNO != rhs_.craneNO)
        {
            return false;
        }
        if(ready != rhs_.ready)
        {
            return false;
        }
        if(controlMode != rhs_.controlMode)
        {
            return false;
        }
        if(askPlan != rhs_.askPlan)
        {
            return false;
        }
        if(taskExcuting != rhs_.taskExcuting)
        {
            return false;
        }
        if(xAct != rhs_.xAct)
        {
            return false;
        }
        if(yAct != rhs_.yAct)
        {
            return false;
        }
        if(zAct != rhs_.zAct)
        {
            return false;
        }
        if(xSpeed != rhs_.xSpeed)
        {
            return false;
        }
        if(ySpeed != rhs_.ySpeed)
        {
            return false;
        }
        if(zSpeed != rhs_.zSpeed)
        {
            return false;
        }
        if(xDirectPositive != rhs_.xDirectPositive)
        {
            return false;
        }
        if(xDirectNegative != rhs_.xDirectNegative)
        {
            return false;
        }
        if(yDirectPositive != rhs_.yDirectPositive)
        {
            return false;
        }
        if(yDirectNegative != rhs_.yDirectNegative)
        {
            return false;
        }
        if(zDirectPositive != rhs_.zDirectPositive)
        {
            return false;
        }
        if(zDirectNegative != rhs_.zDirectNegative)
        {
            return false;
        }
        if(hasCoil != rhs_.hasCoil)
        {
            return false;
        }
        if(weightLoaded != rhs_.weightLoaded)
        {
            return false;
        }
        if(rotateAngleAct != rhs_.rotateAngleAct)
        {
            return false;
        }
        if(emgStop != rhs_.emgStop)
        {
            return false;
        }
        if(orderID != rhs_.orderID)
        {
            return false;
        }
        if(planUpX != rhs_.planUpX)
        {
            return false;
        }
        if(planUpY != rhs_.planUpY)
        {
            return false;
        }
        if(planUpZ != rhs_.planUpZ)
        {
            return false;
        }
        if(planDownX != rhs_.planDownX)
        {
            return false;
        }
        if(planDownY != rhs_.planDownY)
        {
            return false;
        }
        if(planDownZ != rhs_.planDownZ)
        {
            return false;
        }
        if(craneStatus != rhs_.craneStatus)
        {
            return false;
        }
        if(craneAlarm != rhs_.craneAlarm)
        {
            return false;
        }
        if(timeReceive != rhs_.timeReceive)
        {
            return false;
        }
        return true;
    }

    bool operator<(const CranePLCStatusDesc& rhs_) const
    {
        if(this == &rhs_)
        {
            return false;
        }
        if(craneNO < rhs_.craneNO)
        {
            return true;
        }
        else if(rhs_.craneNO < craneNO)
        {
            return false;
        }
        if(ready < rhs_.ready)
        {
            return true;
        }
        else if(rhs_.ready < ready)
        {
            return false;
        }
        if(controlMode < rhs_.controlMode)
        {
            return true;
        }
        else if(rhs_.controlMode < controlMode)
        {
            return false;
        }
        if(askPlan < rhs_.askPlan)
        {
            return true;
        }
        else if(rhs_.askPlan < askPlan)
        {
            return false;
        }
        if(taskExcuting < rhs_.taskExcuting)
        {
            return true;
        }
        else if(rhs_.taskExcuting < taskExcuting)
        {
            return false;
        }
        if(xAct < rhs_.xAct)
        {
            return true;
        }
        else if(rhs_.xAct < xAct)
        {
            return false;
        }
        if(yAct < rhs_.yAct)
        {
            return true;
        }
        else if(rhs_.yAct < yAct)
        {
            return false;
        }
        if(zAct < rhs_.zAct)
        {
            return true;
        }
        else if(rhs_.zAct < zAct)
        {
            return false;
        }
        if(xSpeed < rhs_.xSpeed)
        {
            return true;
        }
        else if(rhs_.xSpeed < xSpeed)
        {
            return false;
        }
        if(ySpeed < rhs_.ySpeed)
        {
            return true;
        }
        else if(rhs_.ySpeed < ySpeed)
        {
            return false;
        }
        if(zSpeed < rhs_.zSpeed)
        {
            return true;
        }
        else if(rhs_.zSpeed < zSpeed)
        {
            return false;
        }
        if(xDirectPositive < rhs_.xDirectPositive)
        {
            return true;
        }
        else if(rhs_.xDirectPositive < xDirectPositive)
        {
            return false;
        }
        if(xDirectNegative < rhs_.xDirectNegative)
        {
            return true;
        }
        else if(rhs_.xDirectNegative < xDirectNegative)
        {
            return false;
        }
        if(yDirectPositive < rhs_.yDirectPositive)
        {
            return true;
        }
        else if(rhs_.yDirectPositive < yDirectPositive)
        {
            return false;
        }
        if(yDirectNegative < rhs_.yDirectNegative)
        {
            return true;
        }
        else if(rhs_.yDirectNegative < yDirectNegative)
        {
            return false;
        }
        if(zDirectPositive < rhs_.zDirectPositive)
        {
            return true;
        }
        else if(rhs_.zDirectPositive < zDirectPositive)
        {
            return false;
        }
        if(zDirectNegative < rhs_.zDirectNegative)
        {
            return true;
        }
        else if(rhs_.zDirectNegative < zDirectNegative)
        {
            return false;
        }
        if(hasCoil < rhs_.hasCoil)
        {
            return true;
        }
        else if(rhs_.hasCoil < hasCoil)
        {
            return false;
        }
        if(weightLoaded < rhs_.weightLoaded)
        {
            return true;
        }
        else if(rhs_.weightLoaded < weightLoaded)
        {
            return false;
        }
        if(rotateAngleAct < rhs_.rotateAngleAct)
        {
            return true;
        }
        else if(rhs_.rotateAngleAct < rotateAngleAct)
        {
            return false;
        }
        if(emgStop < rhs_.emgStop)
        {
            return true;
        }
        else if(rhs_.emgStop < emgStop)
        {
            return false;
        }
        if(orderID < rhs_.orderID)
        {
            return true;
        }
        else if(rhs_.orderID < orderID)
        {
            return false;
        }
        if(planUpX < rhs_.planUpX)
        {
            return true;
        }
        else if(rhs_.planUpX < planUpX)
        {
            return false;
        }
        if(planUpY < rhs_.planUpY)
        {
            return true;
        }
        else if(rhs_.planUpY < planUpY)
        {
            return false;
        }
        if(planUpZ < rhs_.planUpZ)
        {
            return true;
        }
        else if(rhs_.planUpZ < planUpZ)
        {
            return false;
        }
        if(planDownX < rhs_.planDownX)
        {
            return true;
        }
        else if(rhs_.planDownX < planDownX)
        {
            return false;
        }
        if(planDownY < rhs_.planDownY)
        {
            return true;
        }
        else if(rhs_.planDownY < planDownY)
        {
            return false;
        }
        if(planDownZ < rhs_.planDownZ)
        {
            return true;
        }
        else if(rhs_.planDownZ < planDownZ)
        {
            return false;
        }
        if(craneStatus < rhs_.craneStatus)
        {
            return true;
        }
        else if(rhs_.craneStatus < craneStatus)
        {
            return false;
        }
        if(craneAlarm < rhs_.craneAlarm)
        {
            return true;
        }
        else if(rhs_.craneAlarm < craneAlarm)
        {
            return false;
        }
        if(timeReceive < rhs_.timeReceive)
        {
            return true;
        }
        else if(rhs_.timeReceive < timeReceive)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const CranePLCStatusDesc& rhs_) const
    {
        return !operator==(rhs_);
    }
    bool operator<=(const CranePLCStatusDesc& rhs_) const
    {
        return operator<(rhs_) || operator==(rhs_);
    }
    bool operator>(const CranePLCStatusDesc& rhs_) const
    {
        return !operator<(rhs_) && !operator==(rhs_);
    }
    bool operator>=(const CranePLCStatusDesc& rhs_) const
    {
        return !operator<(rhs_);
    }
};

}

namespace CLTS
{

/**
 * Base class for asynchronous callback wrapper classes used for calls to
 * IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 * Create a wrapper instance by calling ::CLTS::newCallback_CranePublisher_CWatchEventHandlerI.
 */
class Callback_CranePublisher_CWatchEventHandlerI_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_CranePublisher_CWatchEventHandlerI_Base> Callback_CranePublisher_CWatchEventHandlerIPtr;

}

namespace IceProxy
{

namespace CLTS
{

class CranePublisher : public virtual ::Ice::Proxy<CranePublisher, ::IceProxy::Ice::Object>
{
public:

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param context The Context map to send with the invocation.
     */
    void CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        end_CWatchEventHandlerI(_iceI_begin_CWatchEventHandlerI(desc, context, ::IceInternal::dummyCallback, 0, true));
    }

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param context The Context map to send with the invocation.
     * @return The asynchronous result object for the invocation.
     */
    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_CWatchEventHandlerI(desc, context, ::IceInternal::dummyCallback, 0);
    }

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param cb Asynchronous callback object.
     * @param cookie User-defined data to associate with the invocation.
     * @return The asynchronous result object for the invocation.
     */
    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::CallbackPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_CWatchEventHandlerI(desc, ::Ice::noExplicitContext, cb, cookie);
    }

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param context The Context map to send with the invocation.
     * @param cb Asynchronous callback object.
     * @param cookie User-defined data to associate with the invocation.
     * @return The asynchronous result object for the invocation.
     */
    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Context& context, const ::Ice::CallbackPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_CWatchEventHandlerI(desc, context, cb, cookie);
    }

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param cb Asynchronous callback object.
     * @param cookie User-defined data to associate with the invocation.
     * @return The asynchronous result object for the invocation.
     */
    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::CLTS::Callback_CranePublisher_CWatchEventHandlerIPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_CWatchEventHandlerI(desc, ::Ice::noExplicitContext, cb, cookie);
    }

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param context The Context map to send with the invocation.
     * @param cb Asynchronous callback object.
     * @param cookie User-defined data to associate with the invocation.
     * @return The asynchronous result object for the invocation.
     */
    ::Ice::AsyncResultPtr begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc& desc, const ::Ice::Context& context, const ::CLTS::Callback_CranePublisher_CWatchEventHandlerIPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_CWatchEventHandlerI(desc, context, cb, cookie);
    }

    /**
     * Completes an invocation of begin_CWatchEventHandlerI.
     * @param result The asynchronous result object for the invocation.
     */
    void end_CWatchEventHandlerI(const ::Ice::AsyncResultPtr& result);

private:

    ::Ice::AsyncResultPtr _iceI_begin_CWatchEventHandlerI(const ::CLTS::CranePLCStatusDesc&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

public:

    /**
     * Obtains the Slice type ID corresponding to this interface.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:
    /// \cond INTERNAL

    virtual ::IceProxy::Ice::Object* _newInstance() const;
    /// \endcond
};

}

}

namespace CLTS
{

/**
 * 行车发布接口
 */
class CranePublisher : public virtual ::Ice::Object
{
public:

    typedef CranePublisherPrx ProxyType;
    typedef CranePublisherPtr PointerType;

    virtual ~CranePublisher();

    /**
     * Determines whether this object supports an interface with the given Slice type ID.
     * @param id The fully-scoped Slice type ID.
     * @param current The Current object for the invocation.
     * @return True if this object supports the interface, false, otherwise.
     */
    virtual bool ice_isA(const ::std::string& id, const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a list of the Slice type IDs representing the interfaces supported by this object.
     * @param current The Current object for the invocation.
     * @return A list of fully-scoped type IDs.
     */
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a Slice type ID representing the most-derived interface supported by this object.
     * @param current The Current object for the invocation.
     * @return A fully-scoped type ID.
     */
    virtual const ::std::string& ice_id(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    /**
     * 广播行车状态.
     * 函数名： stormCrane
     * 返回值： void
     * 参数列表：
     * 参数类型    					取值范围     		    描述
     * desc : CraneStatusDesc								卸下库位
     * @param current The Current object for the invocation.
     */
    virtual void CWatchEventHandlerI(const CranePLCStatusDesc& desc, const ::Ice::Current& current = ::Ice::emptyCurrent) = 0;
    /// \cond INTERNAL
    bool _iceD_CWatchEventHandlerI(::IceInternal::Incoming&, const ::Ice::Current&);
    /// \endcond

    /// \cond INTERNAL
    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&);
    /// \endcond

protected:

    /// \cond STREAM
    virtual void _iceWriteImpl(::Ice::OutputStream*) const;
    virtual void _iceReadImpl(::Ice::InputStream*);
    /// \endcond
};

/// \cond INTERNAL
inline bool operator==(const CranePublisher& lhs, const CranePublisher& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const CranePublisher& lhs, const CranePublisher& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

}

/// \cond STREAM
namespace Ice
{

template<>
struct StreamableTraits< ::CLTS::CranePLCStatusDesc>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 234;
    static const bool fixedLength = false;
};

template<typename S>
struct StreamWriter< ::CLTS::CranePLCStatusDesc, S>
{
    static void write(S* ostr, const ::CLTS::CranePLCStatusDesc& v)
    {
        ostr->write(v.craneNO);
        ostr->write(v.ready);
        ostr->write(v.controlMode);
        ostr->write(v.askPlan);
        ostr->write(v.taskExcuting);
        ostr->write(v.xAct);
        ostr->write(v.yAct);
        ostr->write(v.zAct);
        ostr->write(v.xSpeed);
        ostr->write(v.ySpeed);
        ostr->write(v.zSpeed);
        ostr->write(v.xDirectPositive);
        ostr->write(v.xDirectNegative);
        ostr->write(v.yDirectPositive);
        ostr->write(v.yDirectNegative);
        ostr->write(v.zDirectPositive);
        ostr->write(v.zDirectNegative);
        ostr->write(v.hasCoil);
        ostr->write(v.weightLoaded);
        ostr->write(v.rotateAngleAct);
        ostr->write(v.emgStop);
        ostr->write(v.orderID);
        ostr->write(v.planUpX);
        ostr->write(v.planUpY);
        ostr->write(v.planUpZ);
        ostr->write(v.planDownX);
        ostr->write(v.planDownY);
        ostr->write(v.planDownZ);
        ostr->write(v.craneStatus);
        ostr->write(v.craneAlarm);
        ostr->write(v.timeReceive);
    }
};

template<typename S>
struct StreamReader< ::CLTS::CranePLCStatusDesc, S>
{
    static void read(S* istr, ::CLTS::CranePLCStatusDesc& v)
    {
        istr->read(v.craneNO);
        istr->read(v.ready);
        istr->read(v.controlMode);
        istr->read(v.askPlan);
        istr->read(v.taskExcuting);
        istr->read(v.xAct);
        istr->read(v.yAct);
        istr->read(v.zAct);
        istr->read(v.xSpeed);
        istr->read(v.ySpeed);
        istr->read(v.zSpeed);
        istr->read(v.xDirectPositive);
        istr->read(v.xDirectNegative);
        istr->read(v.yDirectPositive);
        istr->read(v.yDirectNegative);
        istr->read(v.zDirectPositive);
        istr->read(v.zDirectNegative);
        istr->read(v.hasCoil);
        istr->read(v.weightLoaded);
        istr->read(v.rotateAngleAct);
        istr->read(v.emgStop);
        istr->read(v.orderID);
        istr->read(v.planUpX);
        istr->read(v.planUpY);
        istr->read(v.planUpZ);
        istr->read(v.planDownX);
        istr->read(v.planDownY);
        istr->read(v.planDownZ);
        istr->read(v.craneStatus);
        istr->read(v.craneAlarm);
        istr->read(v.timeReceive);
    }
};

}
/// \endcond

namespace CLTS
{

/**
 * Type-safe asynchronous callback wrapper class used for calls to
 * IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 * Create a wrapper instance by calling ::CLTS::newCallback_CranePublisher_CWatchEventHandlerI.
 */
template<class T>
class CallbackNC_CranePublisher_CWatchEventHandlerI : public Callback_CranePublisher_CWatchEventHandlerI_Base, public ::IceInternal::OnewayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)();

    CallbackNC_CranePublisher_CWatchEventHandlerI(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallbackNC<T>(obj, cb, excb, sentcb)
    {
    }
};

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 */
template<class T> Callback_CranePublisher_CWatchEventHandlerIPtr
newCallback_CranePublisher_CWatchEventHandlerI(const IceUtil::Handle<T>& instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_CranePublisher_CWatchEventHandlerI<T>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 */
template<class T> Callback_CranePublisher_CWatchEventHandlerIPtr
newCallback_CranePublisher_CWatchEventHandlerI(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_CranePublisher_CWatchEventHandlerI<T>(instance, 0, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 */
template<class T> Callback_CranePublisher_CWatchEventHandlerIPtr
newCallback_CranePublisher_CWatchEventHandlerI(T* instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_CranePublisher_CWatchEventHandlerI<T>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 */
template<class T> Callback_CranePublisher_CWatchEventHandlerIPtr
newCallback_CranePublisher_CWatchEventHandlerI(T* instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_CranePublisher_CWatchEventHandlerI<T>(instance, 0, excb, sentcb);
}

/**
 * Type-safe asynchronous callback wrapper class with cookie support used for calls to
 * IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 * Create a wrapper instance by calling ::CLTS::newCallback_CranePublisher_CWatchEventHandlerI.
 */
template<class T, typename CT>
class Callback_CranePublisher_CWatchEventHandlerI : public Callback_CranePublisher_CWatchEventHandlerI_Base, public ::IceInternal::OnewayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const CT&);

    Callback_CranePublisher_CWatchEventHandlerI(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallback<T, CT>(obj, cb, excb, sentcb)
    {
    }
};

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 */
template<class T, typename CT> Callback_CranePublisher_CWatchEventHandlerIPtr
newCallback_CranePublisher_CWatchEventHandlerI(const IceUtil::Handle<T>& instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_CranePublisher_CWatchEventHandlerI<T, CT>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 */
template<class T, typename CT> Callback_CranePublisher_CWatchEventHandlerIPtr
newCallback_CranePublisher_CWatchEventHandlerI(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_CranePublisher_CWatchEventHandlerI<T, CT>(instance, 0, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 */
template<class T, typename CT> Callback_CranePublisher_CWatchEventHandlerIPtr
newCallback_CranePublisher_CWatchEventHandlerI(T* instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_CranePublisher_CWatchEventHandlerI<T, CT>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::CLTS::CranePublisher::begin_CWatchEventHandlerI.
 */
template<class T, typename CT> Callback_CranePublisher_CWatchEventHandlerIPtr
newCallback_CranePublisher_CWatchEventHandlerI(T* instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_CranePublisher_CWatchEventHandlerI<T, CT>(instance, 0, excb, sentcb);
}

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
