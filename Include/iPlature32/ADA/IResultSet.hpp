/*********************************************************************
 *		
 *  文      件:    IResultSet.hpp   		
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：
 *
 *  版本历史		
 *      1.0    2009-08-06    lumengyi   创建
 *     
*********************************************************************/
#ifndef	_IRESULTSET_HPP_
#define	_IRESULTSET_HPP_
#include <string>

namespace ADA
{
	template <class ADAAdapter>
	class IResultSet
	{
		typedef typename ADAAdapter::ResultSet ResultSetImpl;
		typedef typename ADAAdapter::Column Column;
	public:
		IResultSet(ResultSetImpl& impl):_impl(impl),isReleased(false){}
		~IResultSet(){if(!isReleased)_impl.release();}
		inline unsigned int columns_count ()
		{
			return _impl.columns_count();
		}
		inline unsigned int rows_count()
		{
			return _impl.rows_count();
		}
		inline bool eod()
		{
			return _impl.eod();
		}
		inline bool next()
		{
			return _impl.next();
		}
		inline bool operator ++()
		{
			return _impl.next();
		}
		inline Column& operator [](const std::string& column_name)
		{
			return _impl[column_name.c_str()];
		}
		inline Column& operator [](unsigned int column_index)
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
		ResultSetImpl& _impl;
		bool isReleased;
	};
}

#endif