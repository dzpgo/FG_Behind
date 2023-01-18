#pragma once
#ifndef _MsgLU02_
#define _MsgLU02_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "tagUtility.h"
#include <iXcomTCP2.h>
#include <json/json.h>

namespace Monitor
{
	class MsgLU02
	{
	public:
		MsgLU02();
		~MsgLU02(void);

	private:
		string m_strMsgId;
	public:
		string getMsgID();
		void  setMsgID(string theVal);

	private:
		static MsgLU02*	m_pMsgLU02;

	public:
		static  MsgLU02* getInstance(void);

	public:
		//ByteSeq HandleMessage(const SmartData& sd);
		ByteSeq HandleMessage(const string& jsonStr, string craneNO);

	private:
		bool isJsonStr(const char *jsoncontent);
		//json解析
		bool MsgLU02Convert(string jsonStr, SmartData& sdJson);
		//读取停车位车号
		bool Get_CarNO(string strParking_No, string& strCar_NO);	

		bool EVTagSnd(string tagName, string tagValue);

		long GetMax(long a, long b, long c, long d);
		long GetMin(long a, long b, long c, long d);
	};
}
#endif
