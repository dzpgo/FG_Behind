#pragma once
#include <pace/pace.h>
#include <log4cplus/LOG.h>
#include <Slice/CltsException.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		/** 登记调用者进程.
		 *  函数名： cltsInit 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    pComponent：iPlature::Component*                      实例地址
		 */
		void cltsInit(Component* pComponent);

		/** 打印事务结束.
		 *  函数名： logInvokedEnd 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log : LOG                                             日志对象
		 *    timeStart :  IceUtil::Time                            调用开始时间
		 */
		void logInvokedEnd(LOG& log, IceUtil::Time timeStart);

		/** 创建调用上下游数据(添加调用者).
		 *  函数名： createCurrent 
		 *  返回值： Current                调用上下游数据（调用者信息）
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    strCallerFunc : const string&							调用者函数名
		 */
		Ice::Current createCurrent(const string& strCallerFunc);

		/** 创建调用上下游数据(添加被调者).
		 *  函数名： createCurrent 
		 *  返回值： Current                调用上下游数据（调用者信息）
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    current : const Ice::Current&                         调用上下游数据
		 *    strInvokdeFunc : const string&						被调用者函数名
		 */
		Ice::Current createCurrent(const Ice::Current& current, const string& strInvokdeFunc);
	}
}
