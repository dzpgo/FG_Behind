/*********************************************************************
*		
*  ��      ��:    UserAPI.h   		//TODO������ļ�����
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������//TODO����ӱ��ļ�����������ϸ����
*        ��//TODO
*        ��//TODO
*
*  �汾��ʷ		
*      1.0    2009-05-31    lumengyi    ����
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
	*  ����: ��ʼ�������ⲿû�ж���־���г�ʼ��ʱ����Ҫ���ñ��ӿڣ��Ա��¼�ӿ��е���Ҫ��Ϣ
	 *  �������� PCS_Init 
	 *  ����ֵ�� void	 	
	 *  �����б�	��������    					ȡֵ��Χ     		    ����
	 *    strLogName  : [IN] const std::string &	//TODO:����ȡֵ��Χ		��־���ƣ�Ĭ��ֵΪ������
	 *    strLogConfig:	[IN] const std::string &	//TODO:����ȡֵ��Χ		��־�������ļ���Ĭ��Ϊ��������$iXComPCS\Config\App4Log.cfg
	 *    strLogDir  :  [IN] const std::string &	//TODO:����ȡֵ��Χ		��־��������ͣ�Ĭ��Ϊ��������$iXComPCS\Log
	 *
	 *  �汾��ʷ		
	 *       1.0    2010-07-12  jacklu    //TODOʵ�ֹ���
	 *       1.0    2011-03-23  jacklu    //TODO���win���źŲ�����
	 *  
	 **********************************************************************/
	IXCOMTCP2_EXPORT void PCS_Init(const std::string& strLogName ="", const std::string& strLogConfig = "", 
		const std::string& strLogDir = "");

	IXCOMTCP2_EXPORT void PCS_Init_C();
	IXCOMTCP2_EXPORT int PCS_Send_C(int nLineNo,const char* chMsgID,int nIDLength, const unsigned   char* chMsgBuffer,int nLength);
	IXCOMTCP2_EXPORT int PCS_Receive_C(int& nLineNO,char chMsgID[],int& nMsgIDLength,unsigned   char chMsgBuffer[],int& nMsgBufferLength, int nWaitTime = 0);

	/**********************************************************************
	 *  ����: ���͵���API
	 *  �������� PCS_Send 
	 *  ����ֵ�� int	 	���ͳɹ����ı�ʾ
	 *  �����б�	��������    					ȡֵ��Χ     		    ����
	 *    nLineNo  :    [IN] int	     1~32		  ���ߺ�
	 *    strMsgID  :    [IN] const std::string &	     //TODO:����ȡֵ��Χ		  ���ĺ�
	 *    strMsgBuffer  :    [IN] const ArrayMsg &	     //TODO:����ȡֵ��Χ		  �������ݣ������ݣ���������ͷ�ͽ�������
	 *
	 *  �汾��ʷ		
	 *       1.0    2009-07-09  gaoxin    ʵ��
	 *       1.0    2010-01-14  jacklu    ���̼�Q����message_queue
	 *       1.0    2010-04-14  jacklu    ���̼�Q����CMessageQueue
	 *       1.0    2010-04-16  jacklu    ���̼�Q����cmessage_queue
	 *       1.0    2010-09-28  jacklu    //TODO�޸�Linux4.6 boost1.44֮ǰCPU100%bug����ΪPOSIX mq
	 *  
	 **********************************************************************/
	IXCOMTCP2_EXPORT int PCS_Send(IN int nLineNo, IN const std::string& strMsgID, IN const ArrayMsg& strMsgBuffer);

	/**********************************************************************
	 *  ����: ���յ���API
	 *  �������� PCS_Receive 
	 *  ����ֵ�� int	 	//TODO:����ֵ����
	 *  �����б�			��������    			ȡֵ��Χ     		    ����
	 *    stReceiveInfo  :	[OUT] RECEIVE_INFO &	//TODO:����ȡֵ��Χ		 ���յ�����Ϣ
	 *
	 *  �汾��ʷ		
	 *       1.0    2009-08-05  jacklu    ʵ�ֹ���
	 *       1.0    2009-10-23  jacklu    �޸�vector��ֵ��ʽ
	 *       1.0    2010-01-14  jacklu    ���̼�Q����message_queue
	 *       1.0    2010-04-14  jacklu    ���̼�Q����CMessageQueue
	 *       1.0    2010-04-16  jacklu    ���̼�Q����cmessage_queue
	 *       1.0    2010-09-28  jacklu    //TODO�޸�Linux4.6 boost1.44֮ǰCPU100%bug����ΪPOSIX mq
	 *  
	 **********************************************************************/
	IXCOMTCP2_EXPORT int PCS_Receive(OUT RECEIVE_INFO& stReceiveInfo, int nWaitTime = 0);

	/**********************************************************************
	*  ����: ���Ŀ���������ͣ����������ļ��е�ͬһ�����ĺŵĵ����ڲ�ͬ�Ļ����е���Ϣ��ͨ����ͬ�Ļ��߽��з���
	*  �������� PCS_MultiSend 
	*  ����ֵ�� int	 	//TODO:����ֵ����
	*  �����б�	��������    					ȡֵ��Χ     		    ����
	*    strMsgID  :    [IN] const std::string &	     //TODO:����ȡֵ��Χ		  <���ĺ�>
	*    strMsgBuffer  :    [IN] const ArrayMsg &	     //TODO:����ȡֵ��Χ		  <�������ݣ������壩>
	*
	*  �汾��ʷ		
	*       1.0    2009-11-17  gaoxin    ʵ��
	*  
	**********************************************************************/
	IXCOMTCP2_EXPORT int PCS_MultiSend(IN const std::string& strMsgID,IN const ArrayMsg& strMsgBuffer);
	/**********************************************************************
	*  ����: ���͵���API
	*  �������� PCS_Send2DB 
	*  ����ֵ�� int	 	���ͳɹ����ı�ʾ
	*  �����б�	��������    					ȡֵ��Χ     		    ����
	*    nLineNo  :    [IN] int	     1~32		  ���ߺ�
	*    strMsgID  :    [IN] const std::string &	     //TODO:����ȡֵ��Χ		  ���ĺ�
	*    strMsgBuffer  :    [IN] const ArrayMsg &	     //TODO:����ȡֵ��Χ		  �������ݣ������ݣ���������ͷ�ͽ�������
	*
	*  �汾��ʷ		
	*       1.0    2012-05-23  gaoxin    ʵ��
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
