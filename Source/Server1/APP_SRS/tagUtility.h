#pragma once
#ifndef _tagUtility_
#define _tagUtility_

#include <time.h>
#include "DataAccess.h"
#include "log4cplus/LOG.h"
#include <tag/Tag.h>
#include <utility/StringHelper.h>
#include <math.h>

using namespace Monitor;
using namespace iPlature;

namespace Monitor
{
	class tagUtility
	{
	public:
		tagUtility(void);
		~tagUtility(void);

		//写内部Tag点的函数
		static void setL2Tag(string strTagName,string strTagValue);
	};
}
#endif

