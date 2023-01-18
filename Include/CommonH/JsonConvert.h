/********************************************************************* *		
 *  文      件:    JsonConvert.h   	
 *
 *  概述：

 *  版本历史		
 *      2021年12月建立
*********************************************************************/

#pragma once
#ifndef _JsonConvert_
#define _JsonConvert_


#include "log4cplus/LOG.h"
#include <json/json.h>

namespace JsonC
{
	class JsonConvert
	{
	public:
		JsonConvert(void);

		~JsonConvert(void);


	public:

		typedef map<string, long> mapPointValue;//x,y,z 值

		bool inputConvert(string requestCraneNO, 
											long requestID, 
											vector<long> activeBlock, 
											long endPointX, 
											long endPointY, 
											long endPointZ, 
											string requestType, 
											long startPointX, 
											long startPointY, 
											long startPointZ, 
											string & jsonStr);

		bool outputConvert(string jsonStr, 
											  string& answerCraneNO, 
											  long& answerID, 
											  long& calReturnCode,
											  long& pointNum, 
											  map<long, mapPointValue>& pointValueList ,
											  vector<long>& throughBlock);

	private:
		bool isJsonStr(const char *jsoncontent);


	};
}


#endif