#pragma once
#ifndef _WatchEventHandlerI_Crane_
#define _WatchEventHandlerI_Crane_



#include "log4cplus/LOG.h"
#include "DataAccess.h"


//#include <Slice/CranePLCStatusStorm.h>
#include "CranePLCStatusStorm.h"

#include "CranePLCStatusBase.h"
#include "CraneMonitor.h"


using namespace CLTS;
using namespace Monitor;
using namespace iPlature;

class WatchEventHandlerI_Crane : public CranePublisher
{
public:
	WatchEventHandlerI_Crane(string myCraneNO);
	~WatchEventHandlerI_Crane();

	virtual void CWatchEventHandlerI(const CranePLCStatusDesc& desc, const Ice::Current& current);

private:
	string craneNO;
};


#endif