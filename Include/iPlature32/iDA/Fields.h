/*********************************************************************
*		
*  文      件:    Fields.h
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：通用数据库接口Fields类，代表数据库结果集中的字段
*
*  版本历史		
*      1.0    2009-12-08    lumengyi    创建
*	   1.0    2010-06-09	haykin		add  operator  Name
*	   1.0    2013-09-29	haykin		add  operator  FieldType
*********************************************************************/
#pragma once

#include <string>
#include <iDA/DataTime.h>
#include <iDA/iDADef.h>

namespace iPlature
{
	namespace iDA
	{
		class FieldsImpl;
		class Command;

		class Fields
		{
			friend class Command;
		public:
			~Fields();

			std::string Name() const;
			bool IsNull() const;
			long AsLong() const;
			double AsDouble() const;
			std::string AsString() const;
			DateTime AsDateTime() const;
			void AsBlob(unsigned char* data,int& length) const;
			void AsBlob(wchar_t* data,int& length) const;
			//2013.3.26
			Command * AsCursor();

			iDA_Data_t FieldType();
		private:
			Fields(); //should not create Parameter object,while using Command

			FieldsImpl* _impl;
		};
	}//namespace iDA
}//namespace iPlature
