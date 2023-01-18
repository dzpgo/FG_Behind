#pragma once
#include <iostream>
#include <Ice/Ice.h>
#include <iDA/iDA.h>
#include <pace/pace.h>
#include <Slice/CltsException.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		struct AlarmMsg
		{
			string strTitle;
			string strMsg;
			string strDetail;
		};

		/** 读取调用端的事件号.
		 *  函数名： getEventID 
		 *  返回值： bool                  读取结果
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    current : const Ice::Context&                         调用上下游数据（调用者信息）
		 *    nEventID : int&										事件编号
		 */
		bool getEventID(const Ice::Current& current, int& nEventID);

		/** 设定调用的事件号.
		 *  函数名： setEventID 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    current : Ice::Context&								调用上下游数据
		 *    nEventID : int&										事件编号
		 */
		void setEventID(Ice::Current& current, int nEventID);

		/** 推送报警.
		 *  函数名： pushAlarm 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    p     : AlarmWrapper&                                 报警模块
		 *    function : const string&                              发生异常的函数
		 *    nAlarmId    : int										报警事件号
		 *    alarmMsg    : const AlarmMsg&							报警内容
		 *    ex      : std::exception&                             异常信息
		 */
		void pushAlarm(AlarmWrapper& p, const string& function, int nAlarmId, const AlarmMsg& alarmMsg, std::exception& ex);

		/** 推送报警.
		 *  函数名： pushAlarm 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    p     : AlarmWrapper&                                 报警模块
		 *    nAlarmId    : int										报警事件号
		 *    alarmMsg    : const AlarmMsg&							报警内容
		 */
		void pushAlarm(AlarmWrapper& p, int nAlarmId, const AlarmMsg& alarmMsg);

		/** 记录报警日志.
		 *  函数名： logAlarm 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&										日志模块
		 *    alarmMsg    : const AlarmMsg&							报警内容
		 */
		void logAlarm(LOG& log, const AlarmMsg& alarmMsg);
	}
}
