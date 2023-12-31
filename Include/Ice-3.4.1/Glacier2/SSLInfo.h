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
// Generated from file `SSLInfo.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

#ifndef __Glacier2_SSLInfo_h__
#define __Glacier2_SSLInfo_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <IceUtil/ScopedArray.h>
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

#ifndef GLACIER2_API
#   ifdef GLACIER2_API_EXPORTS
#       define GLACIER2_API ICE_DECLSPEC_EXPORT
#   else
#       define GLACIER2_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace Glacier2
{

struct SSLInfo
{
    ::std::string remoteHost;
    ::Ice::Int remotePort;
    ::std::string localHost;
    ::Ice::Int localPort;
    ::std::string cipher;
    ::Ice::StringSeq certs;

    bool operator==(const SSLInfo& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(remoteHost != __rhs.remoteHost)
        {
            return false;
        }
        if(remotePort != __rhs.remotePort)
        {
            return false;
        }
        if(localHost != __rhs.localHost)
        {
            return false;
        }
        if(localPort != __rhs.localPort)
        {
            return false;
        }
        if(cipher != __rhs.cipher)
        {
            return false;
        }
        if(certs != __rhs.certs)
        {
            return false;
        }
        return true;
    }

    bool operator<(const SSLInfo& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(remoteHost < __rhs.remoteHost)
        {
            return true;
        }
        else if(__rhs.remoteHost < remoteHost)
        {
            return false;
        }
        if(remotePort < __rhs.remotePort)
        {
            return true;
        }
        else if(__rhs.remotePort < remotePort)
        {
            return false;
        }
        if(localHost < __rhs.localHost)
        {
            return true;
        }
        else if(__rhs.localHost < localHost)
        {
            return false;
        }
        if(localPort < __rhs.localPort)
        {
            return true;
        }
        else if(__rhs.localPort < localPort)
        {
            return false;
        }
        if(cipher < __rhs.cipher)
        {
            return true;
        }
        else if(__rhs.cipher < cipher)
        {
            return false;
        }
        if(certs < __rhs.certs)
        {
            return true;
        }
        else if(__rhs.certs < certs)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const SSLInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const SSLInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const SSLInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const SSLInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    GLACIER2_API void __write(::IceInternal::BasicStream*) const;
    GLACIER2_API void __read(::IceInternal::BasicStream*);
};

}

#endif
