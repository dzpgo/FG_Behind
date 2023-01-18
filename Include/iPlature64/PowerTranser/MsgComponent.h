/*********************************************************************
 *		
 *  文      件:    MsgComponent.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2013-08-08    hanlu    MsgComponent
 *      %USER%   
*********************************************************************/

#ifndef __MsgComponent_h__
#define __MsgComponent_h__

#include <pace/pace.h>
#include <pace/P99Component.h>
#include <iDA/iDA.h>
#include <pace/SmartData.h>
#include <PowerTranser/PowerTranser.h>
#include <PowerTranser/MsgSmartDataManager.h>

namespace iPlature
{
	
	class MsgComponent : public P99Component
	{
	/*typedef std::map<string,SmartData> MAPSMARTDATA;
	private:
		MAPSMARTDATA m_mapSmartData;
		bool m_registResult;*/
	public:
		
		/**********************************************************************
		 *  概述: 应用初始化
		 *  函数名： StartUp 
		 *  返回值： int   0:成功     非零值：失败	 	
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *
		 *  版本历史		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		virtual int StartUp()=0;

		/**********************************************************************
		 *  概述: 应用处理接收信息
		 *  函数名： HandleMessage 
		 *  返回值： Ice::ByteSeq	 	
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    msgName  :    [IN/OUT] const string &	     		                电文名称
		 *    sd  :    [IN/OUT] SmartData	&                     		    电文SmartData结构
		 *
		 *  版本历史		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		virtual ByteSeq HandleMessage(const string& msgName,  SmartData& sd) = 0;

		/**********************************************************************
		 *  概述: 应用可按规则注册一批电文
		 *  函数名： RegistMsg 
		 *  返回值： bool true：注册成功   false：注册失败		 	
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    strRegex  :    [IN/OUT] const std::string &	    		     正则表达式
		 *
		 *  版本历史		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		bool RegistMsg(const std::string& strRegex);

		/**********************************************************************
		 *  概述: 应用可按电文来源，去向注册一批电文
		 *  函数名： RegistMsg 
		 *  返回值： bool true：注册成功   false：注册失败	 	
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    strSource  :    [IN/OUT] const std::string &	     	           电文来源
		 *    strDest  :    [IN/OUT] const std::string &	                   电文去向
		 *
		 *  版本历史		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		bool RegistMsg(const std::string& strSource,const std::string& strDest);

		/**********************************************************************
		 *  概述: 应用可按规则注册一批电文
		 *  函数名： RegistMsg 
		 *  返回值： bool true：注册成功   false：注册失败		 	
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    con  :    [IN/OUT] iPlature::iDA::Connection &	     		  数据库连接
		 *    strRegex  :    [IN/OUT] const std::string &	     		      正则表达式
		 *
		 *  版本历史		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		bool RegistMsg(iPlature::iDA::Connection& con,const std::string& strRegex);

		/**********************************************************************
		 *  概述: 应用可按电文来源，去向注册一批电文
		 *  函数名： RegistMsg 
		 *  返回值： bool true：注册成功   false：注册失败		 	
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    con  :    [IN/OUT] iPlature::iDA::Connection &	              数据库连接
		 *    strSource  :    [IN/OUT] const std::string &	                  电文来源
		 *    strDest  :    [IN/OUT] const std::string &	                  电文去向
		 *
		 *  版本历史		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		bool RegistMsg(iPlature::iDA::Connection& con,const std::string& strSource,const std::string& strDest);

		bool SendMessage(const std::string& msgname, SmartData& sd);

		static bool SendMsg(const std::string& msgname, SmartData& sd);
	private:
		//int start();
	    void PostInitCall();
		void SmartDataInit();
		void ResetData(SmartData&);
		ByteSeq HandleMessage(const ByteSeq& Param);

		iPlature::PowerTranserPrx _PTPrx;

	};

}
#endif