/*********************************************************************
 *		
 *  文      件:    Command.h   		
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：通用数据库接口Command类，代表数据库命令对象
 *
 *  版本历史		
 *      1.0    2009-12-08    lumengyi    创建
 *      1.0		2010-06-09	 haykin		 change the implementation    
 *      1.1    2012-4-16	 haykin         ExecuteSQL
*********************************************************************/
#pragma once
#include <string>
namespace iPlature
{
	namespace iDA
	{
		class Connection;
		class CommandImpl;
		class Parameter;
		class Fields;

		class Command
		{
			friend class Parameter;
			friend class Fields;
		public:
			Command();
			Command(Connection *pConnection,const std::string& sSQL);
			~Command();

			void SetConnection(Connection *pConnection);
			void SetCommandText(const std::string& sSQL);
			void Execute();
			bool FetchNext();
			long RowsAffected();
			void Cancel();
			bool IsResultSet();
			int ParamCount();
			int FieldCount();
			Parameter& ParamByIndex(int i);	// zero based index of C array
			Parameter& Param(int nParamByID);	// id in SQL statement, not in C array
			Parameter& Param(const std::string& sParamByName);

			Command& operator<<(long Value);
			Command& operator<<(double Value);
			Command& operator<<(const std::string& Value);

			Fields& Field(int nField);	// 1-based field number in result set
			Fields& Field(const std::string& sFieldName);

			std::string ExecuteSQL(); 
		private:
			CommandImpl* _impl;
			Command(CommandImpl* pCmmdImpl):_impl(pCmmdImpl){}
		};
	}//namespace iDA
}//namespace iPlature
