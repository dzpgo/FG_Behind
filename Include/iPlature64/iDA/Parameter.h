/*********************************************************************
*		
*  ��      ��:    Parameter.h
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������ͨ�����ݿ�ӿ�Parameter�࣬�������ݿ��������ִ��ʱ�Ĳ���
*
*  �汾��ʷ		
*      1.0    2009-12-08    lumengyi    ����
*      1.0	  2010-06-09	haykin		add operator SetAsCursor/Name/AsXXX
*********************************************************************/
#pragma once

#include <iDA/iDADef.h>
#include <iDA/DataTime.h>

namespace iPlature
{
	namespace iDA
	{
		class ParameterImpl;
		class Command;

		

		class Parameter
		{
			friend class Command;
		public:
			~Parameter();

			Parameter& operator=(const NullValue& value);
			Parameter& operator=(long value);
			Parameter& operator=(double value);
			Parameter& operator=(const std::string& value);
			Parameter& operator=(const DateTime& value);
			void SetBlobData(const unsigned char* data, int length);
			void SetBlobData(const wchar_t* data, int length);

			void SetAsNull();

			Command * SetAsCursor();
			std::string Name() const;
			bool IsNull() const;
			long AsLong() const;
			double AsDouble() const;
			std::string AsString() const;
			DateTime AsDateTime() const;

		private:
			Parameter(); //should not create Parameter object,while using Command

			ParameterImpl* _impl;
		};
	}//namespace iDA
}//namespace iPlature
