// **********************************************************************
//
// Copyright (c) 2003-2010 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef FREEZE_DB_ICE
#define FREEZE_DB_ICE

[["cpp:header-ext:h"]]

/**
 *
 * Freeze provides automatic persistence for Ice servants.
 *
 **/
module Freeze
{

/**
 *
 * A database key, represented as a sequence of bytes.
 *
 **/
sequence<byte> Key;

/**
 *
 * A database value, represented as a sequence of bytes.
 *
 **/
sequence<byte> Value;

};

#endif
