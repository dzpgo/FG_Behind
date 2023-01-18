/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgKIBH01.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgKIBH01_
#define _MsgKIBH01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "SQL4L3.h"

namespace Monitor
{
		class MsgKIBH01
		{
			public:
					MsgKIBH01( );
					~MsgKIBH01(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgKIBH01*	m_pMsgKIBH01;

			public:
					static  MsgKIBH01*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName);

			private:

					void HandleDataIntoDB(SmartData sd, string logFileName);

					int code_convert(const char *from_charset, const char *to_charset, char *inbuf, size_t inlen,
						char *outbuf, size_t outlen);

					int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen);

					int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen);

					string GBKToUTF8(const std::string& strGBK);

					string UTFtoGBK(const char* utf8);



		
		};
}

#endif
