// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1
// Generated from file `CommonDef.ice'

#ifndef __CommonDef_h__
#define __CommonDef_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 301
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace iPlature
{

const ::Ice::Int IPLATURESUCCESS = 0;

typedef ::std::vector< ::Ice::Byte> ByteSeq;

class __U__ByteSeq { };

typedef ::std::vector< ::Ice::Int> IntSeq;

class __U__IntSeq { };

typedef ::std::vector< ::Ice::Float> FloatSeq;

class __U__FloatSeq { };

typedef ::std::vector< ::std::string> StringSeq;

class __U__StringSeq { };

typedef ::std::vector< ::Ice::Long> LongSeq;

class __U__LongSeq { };

typedef ::std::vector< ::Ice::Double> DoubleSeq;

class __U__DoubleSeq { };

typedef ::std::map< ::Ice::Int, ::iPlature::IntSeq> IntSeqMap;

class __U__IntSeqMap { };
void __write(::IceInternal::BasicStream*, const IntSeqMap&, __U__IntSeqMap);
void __read(::IceInternal::BasicStream*, IntSeqMap&, __U__IntSeqMap);

}

#endif
