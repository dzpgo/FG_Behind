/*********************************************************************
 *		
 *  文      件:    ClientManager.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2013-07-22    hanlu    ClientManager
 *      %USER%   
*********************************************************************/
#include "ClientStatus.h"
#include <string>

using namespace std;

namespace iPlature
{
	enum StatusEnum
	{
		STATUS_FAILED,
		STATUS_SUCCESS,
		STATUS_UNKNOWN
	};
	class ClientManager
	{
	public:
		
		/**********************************************************************
		 *  概述: //TODO:请添加函数描述
		 *  函数名： SetClientStatus 
		 *  返回值： int	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    strName  :    [IN/OUT] string	          						   应用名称
		 *    nStatus  :    [IN/OUT] int	            StatusEnum		       应用状态
		 *
		 *  版本历史		
		 *       1.0    2013-07-22  hanlu    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		static int SetClientStatus(string strName,int nStatus);
	};


}
