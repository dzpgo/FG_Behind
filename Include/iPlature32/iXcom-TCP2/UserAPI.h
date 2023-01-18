/*********************************************************************
*		
*  文      件:    UserAPI.h   		//TODO请概述文件功能
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：//TODO请添加本文件包含功能详细描述
*        ：//TODO
*        ：//TODO
*
*  版本历史		
*      1.0    2009-05-31    lumengyi    创建
*     
*********************************************************************/
#ifndef __USERAPI_H__
#define __USERAPI_H__

#include <string>
#include <iXcom-TCP2/iXcomDefine.h>
#include <signal.h>

namespace iXcomTCP2
{

	/**********************************************************************
	*  概述: 初始化，当外部没有对日志进行初始化时，需要调用本接口，以便记录接口中的重要信息
	 *  函数名： PCS_Init 
	 *  返回值： void	 	
	 *  参数列表：	参数类型    					取值范围     		    描述
	 *    strLogName  : [IN] const std::string &	//TODO:参数取值范围		日志名称，默认值为进程名
	 *    strLogConfig:	[IN] const std::string &	//TODO:参数取值范围		日志的配置文件，默认为环境变量$iXComPCS\Config\App4Log.cfg
	 *    strLogDir  :  [IN] const std::string &	//TODO:参数取值范围		日志的输出类型，默认为环境变量$iXComPCS\Log
	 *
	 *  版本历史		
	 *       1.0    2010-07-12  jacklu    //TODO实现功能
	 *       1.0    2011-03-23  jacklu    //TODO添加win下信号捕获处理
	 *  
	 **********************************************************************/
	IXCOMTCP2_EXPORT void PCS_Init(const std::string& strLogName ="", const std::string& strLogConfig = "", 
		const std::string& strLogDir = "");

	IXCOMTCP2_EXPORT void PCS_Init_C();
	IXCOMTCP2_EXPORT int PCS_Send_C(int nLineNo,const char* chMsgID,int nIDLength, const unsigned   char* chMsgBuffer,int nLength);
	IXCOMTCP2_EXPORT int PCS_Receive_C(int& nLineNO,char chMsgID[],int& nMsgIDLength,unsigned   char chMsgBuffer[],int& nMsgBufferLength, int nWaitTime = 0);

	/**********************************************************************
	 *  概述: 发送电文API
	 *  函数名： PCS_Send 
	 *  返回值： int	 	发送成功与否的标示
	 *  参数列表：	参数类型    					取值范围     		    描述
	 *    nLineNo  :    [IN] int	     1~32		  回线号
	 *    strMsgID  :    [IN] const std::string &	     //TODO:参数取值范围		  电文号
	 *    strMsgBuffer  :    [IN] const ArrayMsg &	     //TODO:参数取值范围		  电文内容（裸数据，不含电文头和结束符）
	 *
	 *  版本历史		
	 *       1.0    2009-07-09  gaoxin    实现
	 *       1.0    2010-01-14  jacklu    进程间Q采用message_queue
	 *       1.0    2010-04-14  jacklu    进程间Q采用CMessageQueue
	 *       1.0    2010-04-16  jacklu    进程间Q采用cmessage_queue
	 *       1.0    2010-09-28  jacklu    //TODO修改Linux4.6 boost1.44之前CPU100%bug，改为POSIX mq
	 *  
	 **********************************************************************/
	IXCOMTCP2_EXPORT int PCS_Send(IN int nLineNo, IN const std::string& strMsgID, IN const ArrayMsg& strMsgBuffer);

	/**********************************************************************
	 *  概述: 接收电文API
	 *  函数名： PCS_Receive 
	 *  返回值： int	 	//TODO:返回值描述
	 *  参数列表：			参数类型    			取值范围     		    描述
	 *    stReceiveInfo  :	[OUT] RECEIVE_INFO &	//TODO:参数取值范围		 接收电文信息
	 *
	 *  版本历史		
	 *       1.0    2009-08-05  jacklu    实现功能
	 *       1.0    2009-10-23  jacklu    修改vector赋值方式
	 *       1.0    2010-01-14  jacklu    进程间Q采用message_queue
	 *       1.0    2010-04-14  jacklu    进程间Q采用CMessageQueue
	 *       1.0    2010-04-16  jacklu    进程间Q采用cmessage_queue
	 *       1.0    2010-09-28  jacklu    //TODO修改Linux4.6 boost1.44之前CPU100%bug，改为POSIX mq
	 *  
	 **********************************************************************/
	IXCOMTCP2_EXPORT int PCS_Receive(OUT RECEIVE_INFO& stReceiveInfo, int nWaitTime = 0);

	/**********************************************************************
	*  概述: 向多目标主机发送，根据配置文件中的同一个电文号的电文在不同的回线中的信息，通过不同的回线进行发送
	*  函数名： PCS_MultiSend 
	*  返回值： int	 	//TODO:返回值描述
	*  参数列表：	参数类型    					取值范围     		    描述
	*    strMsgID  :    [IN] const std::string &	     //TODO:参数取值范围		  <电文号>
	*    strMsgBuffer  :    [IN] const ArrayMsg &	     //TODO:参数取值范围		  <电文内容（电文体）>
	*
	*  版本历史		
	*       1.0    2009-11-17  gaoxin    实现
	*  
	**********************************************************************/
	IXCOMTCP2_EXPORT int PCS_MultiSend(IN const std::string& strMsgID,IN const ArrayMsg& strMsgBuffer);
	/**********************************************************************
	*  概述: 发送电文API
	*  函数名： PCS_Send2DB 
	*  返回值： int	 	发送成功与否的标示
	*  参数列表：	参数类型    					取值范围     		    描述
	*    nLineNo  :    [IN] int	     1~32		  回线号
	*    strMsgID  :    [IN] const std::string &	     //TODO:参数取值范围		  电文号
	*    strMsgBuffer  :    [IN] const ArrayMsg &	     //TODO:参数取值范围		  电文内容（裸数据，不含电文头和结束符）
	*
	*  版本历史		
	*       1.0    2012-05-23  gaoxin    实现
	*  
	**********************************************************************/
#ifndef _AIX
	//int PCS_Send2DB(IN int nLineNo, IN const std::string& strMsgID, IN const ArrayMsg& strMsgBuffer);
#endif
	IXCOMTCP2_EXPORT int getSessionStatus(int nLineNo);
	IXCOMTCP2_EXPORT int getAllSessionsStatus(stSessionsInfo *SessionsInfo);
	IXCOMTCP2_EXPORT int setSessionStatus(int nLineNo, int nControl);
	IXCOMTCP2_EXPORT void PCS_Receive_Exit(void);
	IXCOMTCP2_EXPORT int PCS_Send_Syn(IN int nLineNo, IN const std::string& strMsgID, IN const ArrayMsg& strMsgBuffer);
}
#endif
