/*********************************************************************
 *		
 *  ��      ��:    DBConnect.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2013-10-23    haykin    //TODO����ӱ�����Ҫ�޸�����
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

