/*********************************************************************
 *		
 *  文      件:    DllUtil.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2013-08-20    hanlu    create
 *      %USER%   
*********************************************************************/
#pragma once
#include <string>

#ifdef _WIN32
#	include <windows.h> 
#	include <tchar.h> 
#else
#	include <dlfcn.h>
#endif


namespace iPlature
{
#ifdef _WIN32
	typedef HMODULE DLLHandle;
	typedef FARPROC DLLFunAddress;
#else
	typedef void* DLLHandle;
	typedef void* DLLFunAddress;
#endif

	class DllUtilException : public std::exception
	{
	public:
		DllUtilException(const std::string& msg):_what(msg){}
		virtual ~DllUtilException() throw(){}
		virtual const char* what() const throw(){return _what.c_str();}
	private:
		std::string  _what;
	};

	class DllUtil
	{
	public:
		/**********************************************************************
		 *  概述: 加载动态库 若加载失败返回NULL
		 *  函数名： LoadDll 
		 *  返回值： iPlature::DLLHandle	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    dllName  :    [IN] std::string	     //TODO:参数取值范围		动态库路径
		 *
		 *  版本历史		
		 *       1.0    2013-09-23  hanlu     create
		 *  
		 **********************************************************************/
		static DLLHandle LoadDll(const std::string& dllName);
		

		/**********************************************************************
		 *  概述: 获取动态库中指定方法地址, 若获取失败返回NULL
		 *  函数名： GetFunAddress 
		 *  返回值： iPlature::DLLFunAddress	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    hModule  :    [IN] DLLHandle	     //TODO:参数取值范围		  
		 *    procName  :    [IN] std::string	     //TODO:参数取值范围		  
		 *
		 *  版本历史		
		 *       1.0    2013-09-23  hanlu     create
		 *  
		 **********************************************************************/
		static DLLFunAddress GetFunAddress(DLLHandle hModule, const std::string& fucName);


		/**********************************************************************
		 *  概述: 释放动态库 若失败返回false
		 *  函数名： FreeDll 
		 *  返回值： void	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    hModule  :    [IN/OUT] DLLHandle	     //TODO:参数取值范围		  <//TODO:参数描述>
		 *
		 *  版本历史		
		 *       1.0    2013-09-23  hanlu    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		static bool FreeDll(DLLHandle hModule);

		/**********************************************************************
		 *  概述: 错误信息
		 *  函数名： DllError 
		 *  返回值： std::string	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *
		 *  版本历史		
		 *       1.0    2013-09-23  haykin    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		static std::string DllError();

		/**********************************************************************
		 *  概述: 加载指定动态库 若失败抛出异常
		 *  函数名： LoadDllEx 
		 *  返回值： iPlature::DLLHandle	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    dllName  :    [IN/OUT] const std::string &	     //TODO:参数取值范围		  <//TODO:参数描述>
		 *
		 *  版本历史		
		 *       1.0    2013-09-24  haykin    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		static DLLHandle LoadDllEx(const std::string& dllName);

		/**********************************************************************
		*  概述: 获取动态库中指定方法地址（动态库仅加载一次） 若失败抛出异常
		*  函数名： GetFunAddress 
		*  返回值： iPlature::DLLFunAddress	 	//TODO:返回值描述
		*  参数列表：	参数类型    					取值范围     		    描述
		*    dllName  :    [IN/OUT] std::string	     //TODO:参数取值范围		  动态库名称
		*    procName  :    [IN/OUT] std::string	     //TODO:参数取值范围		  方法名称
		*
		*  版本历史		
		*       1.0    2013-09-23  haykin   create
		*  
		**********************************************************************/
		static DLLFunAddress GetFunAddressEx(DLLHandle hModule, const std::string& fucName);
		static DLLFunAddress GetFunAddressEx(const std::string& dllName, const std::string& fucName);

		/**********************************************************************
		 *  概述: 释放动态库 若失败抛出异常
		 *  函数名： FreeDllEx 
		 *  返回值： bool	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    hModule  :    [IN/OUT] DLLHandle	     //TODO:参数取值范围		  <//TODO:参数描述>
		 *
		 *  版本历史		
		 *       1.0    2013-09-24  haykin    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		static bool FreeDllEx(DLLHandle hModule);

		static bool FreeDllEx(const std::string& dllName);

	};


	


	
}