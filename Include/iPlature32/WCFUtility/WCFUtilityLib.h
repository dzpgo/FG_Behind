/*********************************************************************
 *		
 *  文      件:    DBConnect.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2013-10-23    haykin    //TODO请添加本次主要修改内容
 *      %USER%   
*********************************************************************/
#pragma once

#include <ice/Ice.h>
#include <string>
#include <vector>
#include <map>
#include <pace/ProxyWrapper.h>
#include <pace/SmartData.h>
#include "Communicator.h"

using namespace std;
using namespace iPlature;

namespace iPlature
{
	class WCFUtility
	{
	private:
		static int CallNetServiceWithParam(const std::string& ServiceName, const std::string& Operation, std::map<string,string> parameters, vector<byte> buffer);
		static int CallNetServiceWithParam(const string& ServiceName, const string& Operation, const string& msgName, map<string, string> parameters, vector<byte> buffer);

	public:
		static int CallNetService(const string& ServiceName, const string& Operation, vector<byte> buffer);
		static int CallNetService(const string& ServiceName, const string& Operation, SmartData& buffer);
		static int CallNetService(const std::string& ServiceName, const std::string& Operation, const std::string& msgName, std::vector<byte> buffer);
		static int CallNetService(const std::string& ServiceName, const std::string& Operation, const std::string& msgName, SmartData& buffer);
	};
}