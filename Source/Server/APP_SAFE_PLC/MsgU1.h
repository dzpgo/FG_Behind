/*********************************************************************
 *		
 *  ÎÄ      ¼þ:    MsgU1.h   		
 *
 *
 *  ¸ÅÊö£º
*********************************************************************/

#pragma once
#ifndef _MsgU1_
#define _MsgU1_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include <iXcomTCP2.h>

#include "DataAccess.h"

namespace Monitor
{
		class MsgU1
		{
			public:
					MsgU1();
					~MsgU1(void);
			private:
					string msgId;

			private:
					static MsgU1*	m_pMsgU1;

			public:
					static  MsgU1*  getInstance(void);

			public:

					bool SendOutMessage(vector<long>  vecSafePLC4EAFYard);


			
		};
}

#endif
