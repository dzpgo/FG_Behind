/*********************************************************************
 *		
 *  文      件:    Exception.h   		
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：通用数据库接口Exception类，代表异常类
 *
 *  版本历史		
 *      1.0    2009-12-08    lumengyi    创建
 *     
*********************************************************************/
#pragma once
#include <string>
namespace iPlature
{
	namespace iDA
	{
		class Exception : public std::exception
		{
		public:
			Exception(const std::string& sErrMsg,int nErrPos);

			virtual ~Exception() throw() {}

			const char*  what() const  throw();

			std::string ErrMsg() const;

			int ErrPos() const;
		private:
			std::string _ErrMsg;
			int _ErrPos;
		};
	}//namespace iDA
}//namespace iPlature
