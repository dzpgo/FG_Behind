// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef __LogLevel_I_h__
#define __LogLevel_I_h__

#include <pace/LogLevel.h>
#include <pace/Component.h>

namespace iPlature
{
	class LogLevelChangerI : public LogLevelChanger
	{
	public:
		LogLevelChangerI(Component* const);
		virtual void ChangeLogLevel(Ice::Int, const ::Ice::Current&);
	private:
		Component* m_CallBackComponent;
	};
}


#endif


