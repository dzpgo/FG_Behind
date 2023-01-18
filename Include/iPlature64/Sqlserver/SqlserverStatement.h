/*********************************************************************
 *		
 *  文      件:    SqlserverStatement.h   		
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：
 *
 *  版本历史		
 *      1.0    2009-08-12    linchangbo    创建
 *     
*********************************************************************/
#pragma once
#include <Sqlserver/Sqlserver.h>
#include <string>
#include <map>
#include <vector>

namespace Sqlserver
{
	class SqlserverParameter;
	class SqlserverResultSet;
	class SqlserverStatement
	{
	private:
		_CommandPtr m_pCommand;
		std::vector<SqlserverParameter*> m_Parameters;
		std::vector<SqlserverResultSet*> resultsets;
	public:
		SqlserverStatement();
		~SqlserverStatement();
		inline _CommandPtr& getCommand(){return m_pCommand;};
		/**********************************************************************
		 *  概述: 参数绑定
		 *  函数名： bind 
		 *  返回值： SqlserverParameter&
		 *  参数列表：	参数类型    					取值范围     	描述
		 *    name  :  [IN] const char*	     						绑定的参数名
		 *    type  :  [IN] DataTypesEnum	     					绑定的参数类型
		 *
		 *  版本历史		
		 *       1.0    2009-09-07  lumengyi    添加注释
		 *  
		 **********************************************************************/
		SqlserverParameter &bind (const char *name,DataTypesEnum type = DT_UNKNOWN);
		/**********************************************************************
		*  概述: 执行SQL语句
		*  函数名： execute 
		*  返回值： int		执行SQL语句后产生影响的记录数
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		int execute ();
		/**********************************************************************
		*  概述: 查询SQL语句
		*  函数名： select 
		*  返回值： SqlserverResultSet*		查询SQL语句后得到的结果集
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		SqlserverResultSet* select ();
		/**********************************************************************
		*  概述: 根据名字获得参数对象
		*  函数名： operator [] 
		*  返回值： SqlserverParameter&		参数对象
		*  参数列表：	参数类型    					取值范围     	描述
		*    name  :  [IN] const char*	     							参数名
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		SqlserverParameter& operator [] (const char *name);
		/**********************************************************************
		*  概述: 根据索引号获得参数对象
		*  函数名： operator [] 
		*  返回值： SqlserverParameter&		参数对象
		*  参数列表：	参数类型    					取值范围     	描述
		*  parameter_index  :  [IN] unsigned int	     				索引号
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		SqlserverParameter& operator [] (unsigned int parameter_index);
		/**********************************************************************
		*  概述: 释放资源
		*  函数名： release 
		*  返回值： void
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		inline void release (void) {/*m_pCommand.Release();*/}
	};
}