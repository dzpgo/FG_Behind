/*********************************************************************
 *		
 *  ��      ��:    Exception.h   		
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������ͨ�����ݿ�ӿ�Exception�࣬�����쳣��
 *
 *  �汾��ʷ		
 *      1.0    2009-12-08    lumengyi    ����
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
