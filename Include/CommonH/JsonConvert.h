/********************************************************************* *		
 *  ��      ��:    JsonConvert.h   	
 *
 *  ������

 *  �汾��ʷ		
 *      2021��12�½���
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

		typedef map<string, long> mapPointValue;//x,y,z ֵ

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