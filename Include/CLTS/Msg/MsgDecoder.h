//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 创建人：张晓荣
//** 类名称\文件名：MsgDecoder.h
//** 类功能：电文解析类
//** 描述：依据PowerTranser的配置，将电文解析成SmartData类型
//** 创建日期：2016-9-21
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#pragma once
#include <PowerTranser/MsgSmartData.h>
#include <iDA/iDA.h>
#include <Msg/MsgSetting.h>
#include <Ice/Ice.h>

namespace CLTS
{
	namespace MSG
	{
		class MsgDecoder
		{
		private:
			// decoder映射电文设定
			typedef multimap<string, MsgSetting> MapMsgId2Settings;

			// 所有电文设定
			MapMsgId2Settings m_mapSettings;	// 电文分配设定

			/** 电文配置[powertranser].
			 *   
			 */
			SmartData m_SmartData;

			/** 数据库连接实例
			 *
			 */
			iPlature::iDA::Connection m_iDaConn;

			/** 处理电文时的筛选设定.
			 *
			 */
			MsgSetting m_msgSetting;

			/** 读取文件内的设定.
			 *  函数名： loadSettingFile 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    settingFile：string                                   设定文件名（全局路径）
			 */
			void loadSettingFile(string settingFile);

			/** 设定数据库连接.
			 *  函数名： connect 
			 *  返回值： 
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    strDbConn : string                                    数据库连接字符串
			 *    strDbType : string                                    数据库类型
			 */
			void connect(string strDbConn, string strDbType);

			/** 将有上下级关系的电文字段拆分成最小单元组成的字段数组.
			 *  函数名： split 
			 *  返回值： vector<SmartData>      拆分后的字段数组
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    sd : SmartData                                        电文字段
			 */
			vector<SmartData> split(SmartData& sd);

		public:
			MsgDecoder();
			~MsgDecoder();

			/** 载入设定
			 *  函数名： load
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    settingFile：string                                   设定文件名（全局路径）
			 *    strDbConn : string                                    数据库连接字符串
			 *    strDbType : string                                    数据库类型
			 */
			void load(string settingFile, string strDbConn, string strDbType);

			/** 读取powertranser中的电文配置.
			 *  函数名： readPowerTranser
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    msgid : const string&                                 解析电文号
			 *    decoder : const string&                               解析进程名
			 */
			void readPowerTranser(const string& msgid, const string& decoder);

			/** 解析电文.
			 *  函数名： decode 
			 *  返回值： SmartData        解析后的电文数据块
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    ParamBuffer                   const Ice::ByteSeq&     电文数据
			 */
			SmartData decode(const Ice::ByteSeq& ParamBuffer);

			/** 对电文进行筛选过滤处理.
			 *  函数名： filter 
			 *  返回值： bool        是否符合处理条件
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    data  :       SmartData&        						电文字段
			 */
			bool filter(SmartData& data);

			/** 获取电文处理设定.
			 *  函数名： getSetting 
			 *  返回值： MsgSetting        设定
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 * 
			 */
			MsgSetting getSetting();
		};
	};
};
