// **********************************************************************
//
// Copyright (c) 2003-2010 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_INCOMING_H
#define ICE_INCOMING_H

#include <Ice/InstanceF.h>
#include <Ice/ConnectionIF.h>
#include <Ice/ServantLocatorF.h>
#include <Ice/ServantManagerF.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <Ice/Current.h>
#include <Ice/IncomingAsyncF.h>
#include <deque>

namespace IceInternal
{

class ICE_API IncomingBase : private IceUtil::noncopyable
{
public:

    void adopt(IncomingBase&);

protected:

    IncomingBase(Instance*, Ice::ConnectionI*, const Ice::ObjectAdapterPtr&, bool, Ice::Byte, Ice::Int);
    IncomingBase(IncomingBase&); // Adopts the argument. It must not be used afterwards.
    
    void __warning(const Ice::Exception&) const;
    void __warning(const std::string&) const;

    bool __servantLocatorFinished();

    void __handleException(const std::exception&);
    void __handleException();

    Ice::Current _current;
    Ice::ObjectPtr _servant;
    Ice::ServantLocatorPtr _locator;
    Ice::LocalObjectPtr _cookie;

    bool _response;
    Ice::Byte _compress;

    BasicStream _os;

    //
    // Optimization. The connection may not be deleted while a
    // stack-allocated Incoming still holds it.
    //
    Ice::ConnectionI* _connection;

    std::deque<Ice::DispatchInterceptorAsyncCallbackPtr> _interceptorAsyncCallbackQueue;
};

class ICE_API Incoming : public IncomingBase
{
public:

    Incoming(Instance*, Ice::ConnectionI*, const Ice::ObjectAdapterPtr&, bool, Ice::Byte, Ice::Int);

    const Ice::Current& getCurrent()
    {
        return _current;
    }

    void push(const Ice::DispatchInterceptorAsyncCallbackPtr&);
    void pop();
    void startOver();
    void killAsync();
    void setActive(IncomingAsync&);
    
    bool isRetriable()
    {
        return _inParamPos != 0;
    }

    void invoke(const ServantManagerPtr&);

    // Inlined for speed optimization.
    BasicStream* is() { return &_is; }
    BasicStream* os() { return &_os; }

private:

    BasicStream _is;
    
    IncomingAsyncPtr _cb;
    Ice::Byte* _inParamPos;
};

}

#endif
