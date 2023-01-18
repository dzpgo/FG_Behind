/*********************************************************************
 *		
 *  ��      ��:    Logger.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2011-02-12    Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
 *      %USER%   
*********************************************************************/
#ifndef _PACE_LOGGER_H_
#define _PACE_LOGGER_H_
#include <string>
#include <sstream>
#include <Ice/Identity.h>
//#include <log4cplus/LOG.h>

namespace log4cplus
{
	class LOG;
}

namespace iPlature
{ 
	/**
	* pace::Logger��
	* ���ݲ�ͬ�ļ���,����,�����ʽ,���ֵȽ�����־���
	* ��־����: debug < info < notice <  warn < error < alert < fatal
	* �Ƽ�ʹ�������־����debug < warn < error
	*/
	class Log
	{ 
	public:
		/**
		* Logger���Ĳ�������������
		*/
		typedef Log& (*Manipulator)(Log&);

		/**
		* Logger�๹����
		* ����Logger����,����ָ����LogĿ¼,���ڵ�ǰLOGĿ¼��¼log.start��Ϣ
		*
		* @param category ��־Ŀ¼,��������־Ŀ¼�õ�ָ�,
		* ��:app.function����namespace.class.method��.
		*/
		Log(std::string category);
		/**
		* Log��������
		* ���Log���󻺴�,��¼Log.end��Ϣ
		*/
		~Log();
		/**
		* �ı�Log�����Log��¼����Ϊdebug
		* @return ��ǰLog����
		*/
		Log& debug();	
		/**
		* ����printf��ʽ���debug������־��Ϣ
		* @param _format ��־��ʽ����Ϣ��
		* @param ...   ��Ӧ_format��ʽ����ֵ�б�
		*/
		void debug(const char* _format, ...) throw();
		/**
		* ���debug������־��Ϣ,��ʽΪstd::string����
		* @param message ��־��Ϣ�ַ���
		*/
		void debug(const std::string& message) throw();
		/**
		* �ı�Log�����Log��¼����Ϊdebug
		* @return ��ǰLog����
		*/
		Log& info();
		/**
		* ����printf��ʽ���debug������־��Ϣ
		* @param _format ��־��ʽ����Ϣ��
		* @param ...   ��Ӧ_format��ʽ����ֵ�б�
		*/
		void info(const char* _format, ...) throw();
		/**
		* ���info������־��Ϣ,��ʽΪstd::string����
		* @param message ��־��Ϣ�ַ���
		*/
		void info(const std::string& message) throw();
		/**
		* �ı�Log�����Log��¼����Ϊnotice
		* @return ��ǰLog����
		*/
		//Log& notice();
		/**
		* ����printf��ʽ���notice������־��Ϣ
		* @param _format ��־��ʽ����Ϣ��
		* @param ...   ��Ӧ_format��ʽ����ֵ�б�
		*/
		//void notice(const char* _format, ...) throw();
		/**
		* ���notice������־��Ϣ,��ʽΪstd::string����
		* @param message ��־��Ϣ�ַ���
		*/      
		//void notice(const std::string& message) throw();
		/**
		* �ı�Log�����Log��¼����Ϊwarn
		* @return ��ǰLog����
		*/
		Log& warn();
		/**
		* ����printf��ʽ���warn������־��Ϣ
		* @param _format ��־��ʽ����Ϣ��
		* @param ...   ��Ӧ_format��ʽ����ֵ�б�
		*/
		void warn(const char* _format, ...) throw();
		/**
		* ���warn������־��Ϣ,��ʽΪstd::string����
		* @param message ��־��Ϣ�ַ���
		*/
		void warn(const std::string& message) throw();
		/**
		* �ı�Log�����Log��¼����Ϊerror
		* @return ��ǰLog����
		*/
		Log& error();
		/**
		* ����printf��ʽ���error������־��Ϣ
		* @param _format ��־��ʽ����Ϣ��
		* @param ...   ��Ӧ_format��ʽ����ֵ�б�
		*/
		void error(const char* _format, ...) throw();
		/**
		* ���error������־��Ϣ,��ʽΪstd::string����
		* @param message ��־��Ϣ�ַ���
		*/
		void error(const std::string& message) throw();
		/**
		* �ı�Log�����Log��¼����Ϊalert
		* @return ��ǰLog����
		*/
		//Log& alert();
		/**
		* ����printf��ʽ���alert������־��Ϣ
		* @param _format ��־��ʽ����Ϣ��
		* @param ...   ��Ӧ_format��ʽ����ֵ�б�
		*/
		//void alert(const char* _format, ...) throw();
		/**
		* ���alert������־��Ϣ,��ʽΪstd::string����
		* @param message ��־��Ϣ�ַ���
		*/
		//void alert(const std::string& message) throw();
		/**
		* �ı�Log�����Log��¼����Ϊfatal
		* @return ��ǰLog����
		*/
		Log& fatal();
		/**
		* ����printf��ʽ���fatal������־��Ϣ
		* @param _format ��־��ʽ����Ϣ��
		* @param ...   ��Ӧ_format��ʽ����ֵ�б�
		*/
		void fatal(const char* _format, ...) throw();
		/**
		* ���fatal������־��Ϣ,��ʽΪstd::string����
		* @param message ��־��Ϣ�ַ���
		*/
		void fatal(const std::string& message) throw();
		/**
		* ����printf��ʽ�����ǰLog���������м������־��Ϣ
		* @param _format ��־��ʽ����Ϣ��
		* @param ...   ��Ӧ_format��ʽ����ֵ�б�
		*/
		//void log(const char* _format, ...) throw();     
		/**
		* ��ǰLog���������м������־��Ϣ,��ʽΪstd::string����
		* @param message ��־��Ϣ�ַ���
		*/
		//void log(const std::string& message) throw();
		/**
		* ͬ����ʽ��־��Ϣ
		* @return ��ǰLog����
		* @see operator<<
		*/      
		Log& flush();
		/**
		* Log���Ĳ�����
		* @param pf Manipulator���͵�Log������������ָ��
		* @return ��ǰLog����
		* @see std::endl
		* @see Manipulator
		* @see template<typename T> Log& operator <<(const T& t)
		*/
		Log& operator<<(Manipulator  pf)
		{
			return (*pf)(*this);
		};
		/**
		* Log����������
		* @param t ģ������,���뵽Log����ֵ����
		* @return ��ǰLog����
		*/
		template<typename T> Log& operator <<(const T& t)
		{
			//if (!_buffer) 
			//{
			//	if (!(_buffer = new std::ostringstream)) 
			//	{
			//		// memory malloc error,just return
			//		return *this;
			//	}
			//}
			//(*_buffer) << t;
			(*_impl)<<t;
			return *this;
		}
		/**
		* ���������ļ�������Log����.
		* ��̬��Ա����,Ӱ�쵱ǰ��������Log����.
		* @param configFile �����ļ�ȫ·���ַ���
		*/
		static void configure(const std::string& configFile);
		/**
		* �ر���־����,��̬��Ա����,�رպ�����Log���󶼽�ʧЧ.
		*/
		/*static void shutdown();*/

		int DebugHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

	private:
		Log();
		/*void* _category;
		std::ostringstream* _buffer;
		int _priority;*/

		log4cplus::LOG* _impl;
	};

}//namespace pace

namespace std
{
	/**
	* ��ʽ��һ��Log����,Ч���൱�ڵ���Log�����flush����.
	* @param log ����ʽ����Log����
	* @return ��endl��������ʽ�����Log����
	*/
	iPlature::Log& endl(iPlature::Log& log);
}
iPlature::Log& operator<<(iPlature::Log&,const Ice::Identity& id);

#endif
