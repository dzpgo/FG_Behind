/*********************************************************************
 *		
 *  ��      ��:    LOG.h   		interface for the LOG class.
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2006-10-12    lihaigang       ����
 *      1.0    2007-03-25    xuchangsheng    �޸�
 *      1.0    2007-11-26    xuchangsheng    �ı�16���ƵĲ�����char * --> void *
 *      1.0    2008-03-21    xuchangsheng    ���flag������doConfigure���
 *      1.1    2009-05-22    lujianwei       ���֧�ֶ��̶߳���־�ļ����
 *      1.1    2009-06-23    lujianwei       App4Log.cfg�����%f��������ڰ��ļ�����log�����
 *      1.1    2009-07-06    lujianwei       �޸Ķ��̵߳���ʱû��ִ��doThreadConfigureʱ�ڴ�й¶��bug
 *      1.1    2009-07-07    lujianwei       �޸�ͬһ���̱߳�����doThreadConfigure
 *      1.1    2009-07-14    lujianwei       ���eraseThreadInstance����������ȥ���̵߳�����
 *      1.1    2009-11-24    lujianwei       ����doConfigure��֧�������̡���֧�����߳���־
 *      %USER%   
*********************************************************************/

#if _WIN32_WINNT < 0x0400
#undef  _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#ifndef AFX_LOG_H__345E073D_7445_4768_962C_E572847596D5__INCLUDED_
#define AFX_LOG_H__345E073D_7445_4768_962C_E572847596D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdarg.h>				// va_start on linux
#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/fileappender.h>
//����16����
#include <utility/StringHelper.h>
//
//using namespace std;
using namespace baosight;
using namespace log4cplus;
//using namespace log4cplus::helpers;

namespace log4cplus 
{
	typedef enum
	{
		ROOT_CONFIG			= 1		//������log��ʼ������
		,THREAD_CONFIG		= 2		//���߳�log��ʼ������
		,BRANCH_CONFIG		= 3		//��֧log��ʼ������
	}en_config_type;

	typedef enum
	{
		AUTO_CATCH_PID		= 1		//�����̹߳��죬�Զ���ȡ�߳�ID
	}en_thread;

	typedef enum
	{
		LOG_SUCCESS				= 0		//�����óɹ�
		,LOG_CONFIG_UNEXIST		= 1		//App4Log.cfg�����ļ�������
		,LOG_PATH_UNEXIST		= 2		//log���Ŀ¼������
		,LOG_ONLY_ONCE_FAILD	= 3		//��ͬ��doConfigure����ִ�ж��
		,LOG_OTHER				= 4		//��������
	}en_doconfigure_error_code;

	class LOG4CPLUS_EXPORT LOG  
	{
	public:
		/**********************************************************************
		 *  ����: ���ι��죬��������log��
		 *  �������� LOG 
		 *  ����ֵ�� 	 	//TODO:����ֵ����
		 *  �����б�	��������    				ȡֵ��Χ     		    ����
		 *    category:	[IN] const std::string &	//TODO:����ȡֵ��Χ		log�����ʶ
		 *
		 *  �汾��ʷ		
		 *       1.0    2007-03-25  xuchangsheng    ʵ�ֹ���
		 *       1.1    2009-11-24  jacklu			��Ӷ���������
		 *  
		 **********************************************************************/
		LOG(const std::string& category);

		/**********************************************************************
		 *  ����: ���ι��죬����֧log��
		 *  �������� LOG 
		 *  ����ֵ�� 	 	//TODO:����ֵ����
		 *  �����б�			��������    				ȡֵ��Χ     		    ����
		 *    category  :		[IN] const std::string &	//TODO:����ȡֵ��Χ		log�����ʶ
		 *    strLogFileName  : [IN] const std::string &	//TODO:����ȡֵ��Χ		��־����
		 *
		 *  �汾��ʷ		
		 *       1.1    2009-11-24  jacklu    ʵ�ֹ���
		 *  
		 **********************************************************************/
		LOG(const std::string& category, const std::string& strLogFileName);

		/**********************************************************************
		 *  ����: ���ι��죬�����߳�log��
		 *  �������� LOG 
		 *  ����ֵ�� 	 	//TODO:����ֵ����
		 *  �����б�		��������    				ȡֵ��Χ     		    ����
		 *    category  :   [IN] const std::string &	//TODO:����ȡֵ��Χ		log�����ʶ
		 *    nThreadID  :  [IN] int					//TODO:����ȡֵ��Χ		�̺߳�
		 *
		 *  �汾��ʷ		
		 *       1.1    2009-11-24  jacklu    ʵ�ֹ���
		 *  
		 **********************************************************************/
		LOG(const std::string& category, int nThreadID);
	public:
		virtual ~LOG();

	public:
		typedef LOG& (*Manipulator)(LOG&);
		LOG& operator<<(Manipulator  pf);

		LOG& Debug();
		LOG& Info();
		LOG& Warn();
		LOG& Error();
		LOG& Fatal();
		LOG& flush();

		template<typename T> LOG& operator <<(const T& t)
		{
			if (!buffer) 
			{
				if (!(buffer = new log4cplus::tostringstream)) 
				{
					// memory malloc error,just return
					return *this;
				}
			}
			(*buffer) << t;
			return *this;
		}

	private:
		/**********************************************************************
		 *  ����: ��ʼ������־
		 *  �������� DealLog4cplus 
		 *  ����ֵ�� int	 	//TODO:����ֵ����
		 *  �����б�		��������    				ȡֵ��Χ     		    ����
		 *    strBuffer  :  [IN] const std::string &	//TODO:����ȡֵ��Χ		��־����
		 *    nCurlevel  :  [IN] LogLevel				//TODO:����ȡֵ��Χ		��־����
		 *
		 *  �汾��ʷ		
		 *       1.0    2009-11-24  jacklu    ʵ�ֹ���
		 *  
		 **********************************************************************/
		int DealLog4cplus(const std::string& strBuffer, LogLevel nCurlevel);

	public:
		/**********************************************************************
		 *  ����: ��־����
		 *  �������� doConfigure 
		 *  ����ֵ�� int	 	0���ɹ���1��App4Log.cfg�����ļ������ڣ�2��log���Ŀ¼������
		 *						3����ͬ��doConfigure����ִ�ж�飬4����������
		 *  �����б�		��������    				ȡֵ��Χ     		    ����
		 *    strLogName:	[IN] const std::string &	//TODO:����ȡֵ��Χ		log�ļ�����
		 *    nType  :		[IN] int					//TODO:����ȡֵ��Χ		��־���ͣ�Ĭ��Ϊ��������־
		 *
		 *  �汾��ʷ		
		 *       1.0    2007-03-25  xuchangsheng    ʵ�ֹ���
		 *       1.1    2009-11-24  jacklu			�޸Ķ����ã��������̡���֧���߳���־���úϲ�
		 *       1.1    2009-11-30  jacklu			��Ӵ��󷵻�ֵ�Լ��������ļ�����־����·���ļ��
		 *  
		 **********************************************************************/
		static int doConfigure(const std::string& strLogName, int nType = ROOT_CONFIG);

		/**********************************************************************
		 *  ����: ��־����
		 *  �������� doConfigure 
		 *  ����ֵ�� int	 	0���ɹ���1��App4Log.cfg�����ļ������ڣ�2��log���Ŀ¼������
		 *						3����ͬ��doConfigure����ִ�ж�飬4����������
		 *  �����б�		��������    				ȡֵ��Χ     		    ����
		 *    strLogName  : [IN] const std::string &	//TODO:����ȡֵ��Χ		log�ļ�����
		 *    strLogConfig:	[IN] const std::string &	//TODO:����ȡֵ��Χ		log�����ļ�
		 *    strLogDir  :  [IN] const std::string &	//TODO:����ȡֵ��Χ		log���·��
		 *    nType  :		[IN] int					//TODO:����ȡֵ��Χ		��־���ͣ�Ĭ��Ϊ��������־
		 *
		 *  �汾��ʷ		
		 *       1.1    2009-11-24  jacklu		ʵ�ֹ���
		 *       1.1    2009-11-30  jacklu		��Ӵ��󷵻�ֵ�Լ��������ļ�����־����·���ļ��
		 *  
		 **********************************************************************/
		static int doConfigure(const std::string& strLogName, const std::string& strLogConfig, 
								const std::string& strLogDir, int nType = ROOT_CONFIG);

		/**********************************************************************
		*  ����: ȥ����������
		*  �������� remove 
		*  ����ֵ�� void	 	//TODO:����ֵ����
		*  �����б�		��������    				ȡֵ��Χ     		    ����
		*  strLogName  :    [IN] const std::string &	//TODO:����ȡֵ��Χ		��־���ƣ�Ĭ��Ϊȥ���߳�����
		*
		*  �汾��ʷ		
		*       1.0    2009-07-14  jacklu    //ʵ�ֹ���
		*  
		**********************************************************************/
		static void remove(const std::string& strLogName = log4cplus::thread::getCurrentThreadName());

		/**********************************************************************
		*  ����: �����߳�log����
		*  �������� setThreadLogLevel 
		*  ����ֵ�� void	 	//TODO:����ֵ����
		*  �����б�	��������    	ȡֵ��Χ     		    ����
		*    ll  :    [IN] LogLevel		//TODO:����ȡֵ��Χ		log����
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			���ݵ��÷�ʽʵ�ֵȼ�����
		*  
		**********************************************************************/
		void setLogLevel(LogLevel ll);

		/**********************************************************************
		*  ����: Debug�����������
		*  �������� Debug 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    					ȡֵ��Χ     		    ����
		*    strMsg  :    [IN] const std::string&	     //TODO:����ȡֵ��Χ	log�����Ϣ
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Debug(const std::string& strMsg);	

		/**********************************************************************
		*  ����: Debug������ʮ���������
		*  �������� DebugHex 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    			ȡֵ��Χ     			����
		*    data  :    [IN] void *				//TODO:����ȡֵ��Χ		�׵�ַ
		*    len  :		[IN] const int			//TODO:����ȡֵ��Χ		���ݳ��ȣ��ֽ�
		*    split  :   [IN] const string &		//TODO:����ȡֵ��Χ		�ָ����ַ�
		*    needorigin:[IN] bool				//TODO:����ȡֵ��Χ		�Ƿ���Ҫ���ԭʼ����
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int DebugHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  ����: Debug������printf��ʽ���
		*  �������� Debug 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    				ȡֵ��Χ     		    ����
		*    strformat  :    [IN] const char *	    //TODO:����ȡֵ��Χ		  log�����Ϣ
		*      :    [IN] ...						//TODO:����ȡֵ��Χ		  <//TODO:��������>
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Debug(const char* strFormat,...);

		/**********************************************************************
		*  ����: Info�����������
		*  �������� Info 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    					ȡֵ��Χ     		    ����
		*    strMsg  :    [IN] const std::string&	    //TODO:����ȡֵ��Χ		log�����Ϣ
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Info(const std::string& strMsg);

		/**********************************************************************
		*  ����: Info������ʮ���������
		*  �������� InfoHex 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    			ȡֵ��Χ     			����
		*    data  :    [IN] void *				//TODO:����ȡֵ��Χ		�׵�ַ
		*    len  :		[IN] const int			//TODO:����ȡֵ��Χ		���ݳ��ȣ��ֽ�
		*    split  :   [IN] const string &		//TODO:����ȡֵ��Χ		�ָ����ַ�
		*    needorigin:[IN] bool				//TODO:����ȡֵ��Χ		�Ƿ���Ҫ���ԭʼ����
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int InfoHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  ����: �߳�Info������printf��ʽ���
		*  �������� ThreadInfo 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    			ȡֵ��Χ     		    ����
		*    strformat  :[IN] const char *	    //TODO:����ȡֵ��Χ		log�����Ϣ
		*      :    [IN] ...					//TODO:����ȡֵ��Χ		<//TODO:��������>
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Info(const char* strFormat,...);

		/**********************************************************************
		*  ����: Warn�����������
		*  �������� Warn 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    				ȡֵ��Χ     		    ����
		*    strMsg  :  [IN] const std::string&	    //TODO:����ȡֵ��Χ		log�����Ϣ
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Warn(const std::string& strMsg);

		/**********************************************************************
		*  ����: Warn������ʮ���������
		*  �������� WarnHex 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    			ȡֵ��Χ     			����
		*    data  :    [IN] void *				//TODO:����ȡֵ��Χ		�׵�ַ
		*    len  :		[IN] const int			//TODO:����ȡֵ��Χ		���ݳ��ȣ��ֽ�
		*    split  :   [IN] const string &		//TODO:����ȡֵ��Χ		�ָ����ַ�
		*    needorigin:[IN] bool				//TODO:����ȡֵ��Χ		�Ƿ���Ҫ���ԭʼ����
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int WarnHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  ����: Warn������printf��ʽ���
		*  �������� Warn 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    			ȡֵ��Χ     		    ����
		*    strformat  :[IN] const char *	    //TODO:����ȡֵ��Χ		log�����Ϣ
		*      :    [IN] ...					//TODO:����ȡֵ��Χ		<//TODO:��������>
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Warn(const char* strFormat,...);

		/**********************************************************************
		*  ����: Error�����������
		*  �������� Error 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    					ȡֵ��Χ     		    ����
		*    strMsg  :    [IN] const std::string&	     //TODO:����ȡֵ��Χ	log�����Ϣ
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Error(const std::string& strMsg);

		/**********************************************************************
		*  ����: �߳�Error������ʮ���������
		*  �������� ThreadErrorHex 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    			ȡֵ��Χ     			����
		*    data  :    [IN] void *				//TODO:����ȡֵ��Χ		�׵�ַ
		*    len  :		[IN] const int			//TODO:����ȡֵ��Χ		���ݳ��ȣ��ֽ�
		*    split  :   [IN] const string &		//TODO:����ȡֵ��Χ		�ָ����ַ�
		*    needorigin:[IN] bool				//TODO:����ȡֵ��Χ		�Ƿ���Ҫ���ԭʼ����
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int ErrorHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  ����: Error������printf��ʽ���
		*  �������� Error 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�		��������    			ȡֵ��Χ     		    ����
		*    strformat  :   [IN] const char *	    //TODO:����ȡֵ��Χ		log�����Ϣ
		*      :    [IN] ...						//TODO:����ȡֵ��Χ		<//TODO:��������>
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Error(const char* strFormat,...);
		
		/**********************************************************************
		*  ����: Fatal�����������
		*  �������� Fatal 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    					ȡֵ��Χ     		    ����
		*    strMsg  :    [IN] const std::string&	     //TODO:����ȡֵ��Χ		log�����Ϣ
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Fatal(const std::string& strMsg);

		/**********************************************************************
		*  ����: �߳�Fatal������ʮ���������
		*  �������� FatalHex 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    			ȡֵ��Χ     			����
		*    data  :    [IN] void *				//TODO:����ȡֵ��Χ		�׵�ַ
		*    len  :		[IN] const int			//TODO:����ȡֵ��Χ		���ݳ��ȣ��ֽ�
		*    split  :   [IN] const string &		//TODO:����ȡֵ��Χ		�ָ����ַ�
		*    needorigin:[IN] bool				//TODO:����ȡֵ��Χ		�Ƿ���Ҫ���ԭʼ����
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int FatalHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  ����: Fatal������printf��ʽ���
		*  �������� Fatal 
		*  ����ֵ�� int	 	0���ɹ���1��ʧ��
		*  �����б�	��������    					ȡֵ��Χ     		    ����
		*    strformat  :    [IN] const char *	    //TODO:����ȡֵ��Χ		  log�����Ϣ
		*      :    [IN] ...						//TODO:����ȡֵ��Χ		  <//TODO:��������>
		*
		*  �汾��ʷ		
		*       1.0    2007-03-25  xuchangsheng		ʵ�ֹ���
		*       1.1    2009-11-24  jacklu			��ȡ������־����
		*  
		**********************************************************************/
		int Fatal(const char* strFormat,...);
		void print(){std::cout<<"hi ,in LOG"<<std::endl;}

	private:
		log4cplus::tostringstream *buffer;
		std::string prefix;
		LogLevel curlevel;//current log level
		
	private:
		std::string m_strLogFileName;
		int			m_nType;
		static int flag ; //2008-03-21��ֹ��γ�ʼ��
	};
}

namespace std
{
	LOG4CPLUS_EXPORT log4cplus::LOG& endl(log4cplus::LOG& log);
}
#endif // !defined(AFX_LOG_H__345E073D_7445_4768_962C_E572847596D5__INCLUDED_)

//#define _WIN32

