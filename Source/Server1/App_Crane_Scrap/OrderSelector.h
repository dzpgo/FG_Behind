#pragma once
#ifndef  _Order_Selector_
#define  _Order_Selector_

#include "WMSCraneOrder_Resolver.h"
#include "DataAccess.h"
#include "log4cplus/LOG.h"

namespace Monitor
{
	class OrderSelector
	{
	public:
		OrderSelector(void);
		~OrderSelector(void);

	public:
		static bool Selector(string craneNO);
	};
}
#endif