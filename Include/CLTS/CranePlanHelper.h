#pragma once
#include <Slice/CranePlan.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		/** 吊运计划帮助类.
		 *  函数名： catchFunc 
		 */
		class CranePlanHelper
		{
			/** 字符串转换为吊运状态.
			 *  函数名： convert 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    strStatus : const string&                             吊运状态字符串
			 *    status    : PLANSTATUS&                               吊运状态
			 */
			static void convert(const string& strStatus, CLTS::PLANSTATUS& status);
		};
	}
}
