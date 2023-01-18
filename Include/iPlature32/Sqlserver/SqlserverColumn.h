/*********************************************************************
 *		
 *  文      件:    SqlserverColumn.h   		
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

namespace Sqlserver
{
	class SqlserverColumn
	{
	private:
		_variant_t m_pVariant;
	public:
		SqlserverColumn(const _variant_t& var);
		/**********************************************************************
		*  概述: 是否为空
		*  函数名： is_null
		*  返回值： bool		
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		bool is_null();
		/**********************************************************************
		*  概述: 返回类型
		*  函数名： type
		*  返回值： DataTypesEnum		
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		DataTypesEnum type();
		/**********************************************************************
		*  概述: 取值
		*  函数名： as_string
		*  返回值： const char*		
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		inline operator const char* (void) const { return (as_string ()); }
		const char* as_string() const;
		/**********************************************************************
		*  概述: 取值
		*  函数名： as_double
		*  返回值： double
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		inline operator double (void) const { return (as_double ()); }
		double as_double() const;
		/**********************************************************************
		*  概述: 取值
		*  函数名： as_long
		*  返回值： long
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		inline operator long (void) const { return (as_long ()); }
		long as_long() const;
		/**********************************************************************
		*  概述: 取值
		*  函数名： as_datetime
		*  返回值： DATE
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		inline operator datetime (void) const { return (as_datetime ()); }
		datetime as_datetime() const;
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
		void release();
	};
}