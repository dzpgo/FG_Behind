#pragma once 

#include <CLTS.h>
#include <Util.h>

namespace CLTS
{
	namespace DAL
	{
		class EventDAL
		{
		private:
			string m_strDbCfgFile; // 数据库连接配置文件
			iDA::Connection* m_pCon; // 数据库连接指针

			/** 产生调用事件号.
			 *  函数名： generateEventID 
			 *  返回值： int					调用事件号	                 
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    无
			 */
			int generateEventID();

		public:
			EventDAL(string strDbCfgFile, iDA::Connection* pCon);
			~EventDAL(void);

			/** 调用上下文信息中加入调用事件号.
			 *  函数名： generateEventID 
			 *  返回值： int					                 
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    current : Ice::Current&		 						调用上下文信息
			 */
			int generateEventID(Ice::Current& current);
		};
	}
}