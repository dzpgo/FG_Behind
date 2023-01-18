// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef __MsgTube_I_h__
#define __MsgTube_I_h__

#include <pace/P99Component.h>

namespace iPlature
{
	class MsgTubeI : public MsgTube
	{
	public:
		MsgTubeI(P99Component* const);
		virtual ByteSeq SynHandleMessage(const ByteSeq&, const ::Ice::Current&);
		virtual void AsyHandleMessage(const ByteSeq&, const ::Ice::Current&);
	private:
		P99Component* m_CallBackComponent;
	};
}


#endif


