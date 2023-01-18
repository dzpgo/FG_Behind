#pragma once

#include <IceUtil/Monitor.h>
#include <IceUtil/Handle.h>
#include <IceUtil/Thread.h>
#include <log4cplus/LOG.h>

namespace log4cplus
{
	class ExThread;

	class ALOG
	{
		friend class ExThread;
	public:
		ALOG(string category);
		virtual ~ALOG();
		static void doConfigure(string name);
		static void doConfigure(string name,string logconfig,string logdir);
		void flushLog();
		//void setLogLevel(LogLevel ll);

		ALOG& Debug();
		ALOG& Info();
		ALOG& Warn();
		ALOG& Error();
		ALOG& Fatal();
		ALOG& flush();

		template<typename T> ALOG& operator <<(const T& t)
		{
			ostringstream s;
			s<<t;
			buffer+=s.str();
			return *this;
		}

		typedef ALOG& (*Manipulator)(ALOG&);
		ALOG& operator<<(Manipulator  pf);
		ALOG& operator<<(int t);
		ALOG& operator<<(float t);
		ALOG& operator<<(double t);
		ALOG& operator<<(const char* t);
		ALOG& operator<<(const string& t);
		ALOG& operator<<(size_t t);

		int Debug(std::string strMsg);
		int DebugHex(void* data,const int len,const string& split=" ",bool needorigin=true);
		int Debug(const char* strFormat,...);

		int Info(std::string strMsg);
		int InfoHex(void* data,const int len,const string& split=" ",bool needorigin=true);
		int Info(const char* strFormat,...);

		int Warn(std::string strMsg);
		int WarnHex(void* data,const int len,const string& split=" ",bool needorigin=true);
		int Warn(const char* strFormat,...);

		int Error(std::string strMsg);
		int ErrorHex(void* data,const int len,const string& split=" ",bool needorigin=true);
		int Error(const char* strFormat,...);

		int Fatal(std::string strMsg);
		int FatalHex(void* data,const int len,const string& split=" ",bool needorigin=true);
		int Fatal(const char* strFormat,...);
	private:
		typedef pair<LogLevel,string> OneLog;

		void put(const LogLevel ll,const string & strMsg);
	private:
		deque<OneLog> _q;
		IceUtil::Handle<IceUtil::Thread> threadptr;
		string buffer;
		LogLevel curlevel;
		string _category;
	};
}

namespace std
{
	log4cplus::ALOG& endl(log4cplus::ALOG& log);
}