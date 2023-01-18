/*********************************************************************
 *		
 *  ��      ��:    MsgComponent.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
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
		 *  ����: Ӧ�ó�ʼ��
		 *  �������� StartUp 
		 *  ����ֵ�� int   0:�ɹ�     ����ֵ��ʧ��	 	
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		virtual int StartUp()=0;

		/**********************************************************************
		 *  ����: Ӧ�ô��������Ϣ
		 *  �������� HandleMessage 
		 *  ����ֵ�� Ice::ByteSeq	 	
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    msgName  :    [IN/OUT] const string &	     		                ��������
		 *    sd  :    [IN/OUT] SmartData	&                     		    ����SmartData�ṹ
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		virtual ByteSeq HandleMessage(const string& msgName,  SmartData& sd) = 0;

		/**********************************************************************
		 *  ����: Ӧ�ÿɰ�����ע��һ������
		 *  �������� RegistMsg 
		 *  ����ֵ�� bool true��ע��ɹ�   false��ע��ʧ��		 	
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    strRegex  :    [IN/OUT] const std::string &	    		     ������ʽ
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		bool RegistMsg(const std::string& strRegex);

		/**********************************************************************
		 *  ����: Ӧ�ÿɰ�������Դ��ȥ��ע��һ������
		 *  �������� RegistMsg 
		 *  ����ֵ�� bool true��ע��ɹ�   false��ע��ʧ��	 	
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    strSource  :    [IN/OUT] const std::string &	     	           ������Դ
		 *    strDest  :    [IN/OUT] const std::string &	                   ����ȥ��
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		bool RegistMsg(const std::string& strSource,const std::string& strDest);

		/**********************************************************************
		 *  ����: Ӧ�ÿɰ�����ע��һ������
		 *  �������� RegistMsg 
		 *  ����ֵ�� bool true��ע��ɹ�   false��ע��ʧ��		 	
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    con  :    [IN/OUT] iPlature::iDA::Connection &	     		  ���ݿ�����
		 *    strRegex  :    [IN/OUT] const std::string &	     		      ������ʽ
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-08-15  hanlu    
		 *  
		 **********************************************************************/
		bool RegistMsg(iPlature::iDA::Connection& con,const std::string& strRegex);

		/**********************************************************************
		 *  ����: Ӧ�ÿɰ�������Դ��ȥ��ע��һ������
		 *  �������� RegistMsg 
		 *  ����ֵ�� bool true��ע��ɹ�   false��ע��ʧ��		 	
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    con  :    [IN/OUT] iPlature::iDA::Connection &	              ���ݿ�����
		 *    strSource  :    [IN/OUT] const std::string &	                  ������Դ
		 *    strDest  :    [IN/OUT] const std::string &	                  ����ȥ��
		 *
		 *  �汾��ʷ		
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