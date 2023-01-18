/*********************************************************************
 *		
 *  文      件:    FileUtil.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2011-08-31    Haykin-2010    //TODO请添加本次主要修改内容
 *      %USER%   
*********************************************************************/
#pragma once
#include <string>
namespace iPlature
{
	class FileUtil
	{
	public:
		/**********************************************************************
		 *  概述: make directory
		 *  函数名： mkdir 
		 *  返回值： int	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    path  :    [IN/OUT] const std::string &	     路径
		 *    recursive  :    [IN/OUT] bool					Allows the creation of nested directories specified in the pathname. Defaults to FALSE，or can create only one new directory per call, so only the last component of dirname can name a new directory
		 *    mode  :    [IN/OUT] int							he mode is 0777 by default, which means the widest possible access
		 *
		 *  版本历史		
		 *       1.0    2011-08-31  Haykin-2010    create
		 *  
		 **********************************************************************/
		static int MkDir(const std::string& path, bool recursive = false, int mode = 0777);

		/**********************************************************************
		 *  概述: //TODO:请添加函数描述
		 *  函数名： GetAppName 
		 *  返回值： std::string	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    path  :    [IN/OUT] const std::string &	     //TODO:参数取值范围		  <//TODO:参数描述>
		 *
		 *  版本历史		
		 *       1.0    2011-08-31  Haykin-2010    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		static std::string GetAppName(const std::string& path);
	};
}

