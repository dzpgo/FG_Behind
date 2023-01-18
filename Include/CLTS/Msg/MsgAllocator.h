//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 创建人：张晓荣
//** 类名称\文件名：MsgAllocator.h
//** 类功能：电文处理分配类
//** 描述：依据分配文件设定的分配配置，将电文分配给指定处理对象处理
//** 创建日期：2016-9-21
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#pragma once
#include <Msg/MsgSetting.h>
#include <map>
#include <Ice/Ice.h>

using namespace std;

namespace CLTS
{
	namespace MSG
	{
		class MsgAllocator
		{
		// msgid映射电文设定
		typedef multimap<string, MsgSetting> MapMsgId2Settings;

		private:
			MapMsgId2Settings m_mapSettings;	// 电文分配设定

		public:
			MsgAllocator(void);
			~MsgAllocator(void);

			/** 读取文件内的电文分配设定.
			 *  函数名： loadSettingFile 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    settingFile：string                                   设定文件名（全局路径）
			 */
			void loadSettingFile(string settingFile);

			/** 分配电文到对应的处理程序.
			 *  函数名： allocate 
			 *  返回值： bool        分配结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    data    :     Ice::ByteSeq&                           电文数据
			 */
			bool allocate(Ice::ByteSeq& data);
		};
	};
};