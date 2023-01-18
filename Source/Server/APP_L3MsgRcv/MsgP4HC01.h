/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgP4HC01.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgP4HC01_
#define _MsgP4HC01_

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
		class MsgP4HC01
		{
			public:
					MsgP4HC01( );
					~MsgP4HC01(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgP4HC01*	m_pMsgP4HC01;

			public:
					static  MsgP4HC01*  getInstance(void);

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
