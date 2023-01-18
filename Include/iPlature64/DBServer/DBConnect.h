/*********************************************************************
 *		
 *  文      件:    DBConnect.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2013-10-23    haykin    //TODO请添加本次主要修改内容
 *      %USER%   
*********************************************************************/
#pragma once
#include <DBServer/DBServerSlice.h>
#include <string>

namespace iPlature
{
	class DBConnect
	{
	public:
		DBConnect();

		void Connect(const std::string& dbname);

		int ExecuteSQL(const std::string& sql);

		ResultDataSet Query(const std::string& sql);

		int ExecuteEx(const std::string& sql, ResultDataSet& rs);

		void Commit();

		void Rollback();

		void Close();
	private:
	private:
		
		SQLCommandPrx _cmdPrx;
	};
}

