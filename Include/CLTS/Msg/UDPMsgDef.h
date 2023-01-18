//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 创建人：张晓荣
//** 类名称\文件名：UDPMsgDef.h
//** 类功能：UDP电文数据结构
//** 描述：
//** 创建日期：2016-12-09
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#pragma once
#include <string>
#include <vector>
#include <Ice/Ice.h>
#include <pace/SmartData.h>

using namespace std;

namespace CLTS
{
	namespace MSG
	{
		const int MAX_MSG_BUFFER_LENGTH = 4096;
		const int POWER_TRANS_HEAD = 32;

		/** 自定义UDP电文结构.
		 *   
		 */
		struct MY_UDP_MSG
		{
			unsigned char msgId[POWER_TRANS_HEAD];	  // 电文号
			int lenMsgId;					  // 电文号长度
			unsigned char msgData[MAX_MSG_BUFFER_LENGTH];  // 电文内容
		};

		class UdpUtil
		{
		public:
			/** 将电文信息转换成PowerTranser可读数据.
			 *  函数名： trans2SmartData
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    msg : MY_UDP_MSG*										UDP中拆分出的电文信息
			 *    lenMsgData : const int								实际电文长度
			 *    sd : Ice::ByteSeq&									PowerTranser可读数据
			 *    vecField : Ice::StringSeq&							依据分隔符拆分出的字段
			 *    split : char											电文信息中的分隔符[不输入]
			 */
			static void trans2SmartData(MY_UDP_MSG* msg, const int lenMsgData, Ice::ByteSeq& sd);

			/** 接收UDP电文转换成自定义电文结构.
			 *  函数名： rcv2UdpMsg
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    rcv : Ice::ByteSeq&									接收UDP电文
			 *    msg : MY_UDP_MSG&										自定义电文结构.
			 *    lenMsgId : const int									UDP电文包含的电文号长度
			 */
			static void rcv2UdpMsg(const Ice::ByteSeq& rcv, MY_UDP_MSG& msg, const int lenMsgId);

			/** 定义电文结构拆分.
			 *  函数名： splitUdpMsg
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    msg : MY_UDP_MSG&										自定义电文结构
			 *    lenMsgData : const int								实际电文长度
			 *    vecField : Ice::StringSeq&							拆分后的字段数组
			 *    lenMsgId : const int									采用的分隔符
			 */
			static void splitUdpMsg(MY_UDP_MSG& msg, const int lenMsgData, Ice::StringSeq& vecField, char split='#');

			static void wrapSmartData(const Ice::StringSeq& vecField, iPlature::SmartData& sd, int& index);
		};
	};
};
