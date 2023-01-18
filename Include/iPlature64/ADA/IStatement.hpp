/*********************************************************************
 *		
 *  文      件:    IStatement.hpp   		
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：
 *
 *  版本历史		
 *      1.0    2009-08-06    lumengyi    
 *     
*********************************************************************/
#ifndef	_ISTATEMENT_HPP_
#define	_ISTATEMENT_HPP_
#include <string>
#include <vector>

namespace ADA
{
	template <class ADAAdapter>
	class IStatement
	{
		typedef typename ADAAdapter::Statement StatementImpl;
		typedef typename ADAAdapter::Parameter Parameter;
		typedef typename ADAAdapter::DataTypesEnum DataTypesEnum;
	public:
		IStatement(StatementImpl& impl):_impl(impl),isReleased(false){}
		~IStatement()
		{
			for (unsigned int i = 0; i < _IResultSets.size(); i ++)
			{
				delete _IResultSets[i];
			}
			_IResultSets.clear();

			if(!isReleased)_impl.release();
		}
		inline Parameter& bind (const std::string& name,DataTypesEnum type)
		{
			return _impl.bind(name.c_str(),type);
		}
		inline int execute()
		{
			return _impl.execute();
		}
		inline IResultSet<ADAAdapter>* select()
		{
			IResultSet<ADAAdapter>* ret = new IResultSet<ADAAdapter>(*_impl.select());
			_IResultSets.push_back(ret);
			return ret;
		}
		inline Parameter& operator [](const std::string& column_name)
		{
			return _impl[column_name.c_str()];
		}
		inline Parameter& operator [](unsigned int column_index)
		{
			return _impl[column_index];
		}
		inline void release()
		{
			if (!isReleased)
			{
				_impl.release();
				isReleased = true;
			}
		}
	private:
		std::vector<IResultSet<ADAAdapter>*> _IResultSets;
		StatementImpl& _impl;
		bool isReleased;
	};
}

#endif