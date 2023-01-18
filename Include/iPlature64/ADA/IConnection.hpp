/*********************************************************************
 *		
 *  文      件:    IConnection.hpp   		
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：
 *
 *  版本历史		
 *      1.0    2009-08-06    lumengyi    创建
 *     
*********************************************************************/
#ifndef	_ICONNECTION_HPP_
#define	_ICONNECTION_HPP_
#include <ADA/IResultSet.hpp>
#include <ADA/IStatement.hpp>
#include <string>
#include <vector>

namespace ADA
{
	template <class ADAAdapter>
	class IConnection
	{
		typedef typename ADAAdapter::Connection ConnectionImpl;
	public:
		IConnection():_impl(){}
		IConnection(const std::string& login,const std::string& password,const std::string& service_name)
			:_impl(login,password,service_name){}
		~IConnection()
		{
			
		}
		inline void open (const std::string& login,const std::string& password,const std::string& service_name)
		{
			_impl.open(login,password,service_name);
		}
		inline void beginTrans()
		{
			_impl.beginTrans();
		}
		inline void close()
		{
			//所有的释放必须在connection close之前
			for (unsigned int i = 0; i < _IResultSets.size(); i ++)
			{
				delete _IResultSets[i];
			}
			_IResultSets.clear();

			for (unsigned int i = 0; i < _IStatements.size(); i ++)
			{
				delete _IStatements[i];
			}
			_IStatements.clear();

			_impl.close();
		}
		inline void reopen()
		{
			_impl.reopen();
		}
		inline int execute(const std::string& sql_block)
		{
			return _impl.execute(sql_block.c_str());
		}
		inline IResultSet<ADAAdapter>* select(const std::string& sql_block)
		{
			IResultSet<ADAAdapter>* ret = new IResultSet<ADAAdapter>(*_impl.select(sql_block.c_str()));
			_IResultSets.push_back(ret);
			return ret;
		}
		inline IStatement<ADAAdapter>* prepare(const std::string& sql_block)
		{
			IStatement<ADAAdapter>* ret = new IStatement<ADAAdapter>(*_impl.prepare(sql_block.c_str()));
			_IStatements.push_back(ret);
			return ret;
		}
		inline void commit()
		{
			_impl.commit();
		}
		inline void rollback()
		{
			_impl.rollback();
		}
	private:
		std::vector<IResultSet<ADAAdapter>*> _IResultSets;
		std::vector<IStatement<ADAAdapter>*> _IStatements;
		ConnectionImpl _impl;
	};
}

#endif