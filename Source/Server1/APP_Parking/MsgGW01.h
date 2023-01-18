#pragma once
#ifndef _MsgGW01_
#define _MsgGW01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "tagUtility.h"
#include <iXcomTCP2.h>

namespace Monitor
{
	class MsgGW01
	{
	public:
		MsgGW01();
		~MsgGW01(void);

	private:
		string m_strMsgId;
	public:
		string getMsgID();
		void  setMsgID(string theVal);

	private:
		static MsgGW01*	m_pMsgGW01;

	public:
		static  MsgGW01* getInstance(void);

	public:
		ByteSeq HandleMessage(const SmartData& sd);

	private:

		void HandleData(SmartData sd);

		bool CarArriveParking(string parkingNO, string truckNO, string& workType, string& carType, string& planSrc, string& planNO);

		bool CarLeaveParking(string parkingNO, string truckNO, string& workType, string& carType, string& planSrc, string& planNO, long& planDetailID);

		string GetWorkStatusByWorkType(string workType);

		bool EVTagSnd(string tagName, string tagValue);

		string workTypeConvert(string workType);
		
	
	};
}
#endif
