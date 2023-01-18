#pragma once

#include <db/_p.h>
#include <db/oralib.h>

class ConnectionPoolException : public exception
{
public:
	virtual ~ConnectionPoolException() throw();
	ConnectionPoolException(const std::string& msg);
	virtual const char* what() const throw();
private:
	string  _what;
};

enum CP_BLOCK_MODE
{
	BLOCK,		//阻塞方式，getConnection时会sleep
	NONBLOCK	//非阻塞方式，getConnection时会抛出异常ConnectionPoolException
};

class ConnectionPoolImpl;
class ConnectionProxy;
class ConnectionPool
{
public:
	static void initialize(const string& login,
						   const string& password,
						   const string& service_name="",
						   unsigned int PoolSize = 1,
						   CP_BLOCK_MODE mode = BLOCK);
	static void destroy();
	static ConnectionProxy& getConnection();
	static void returnConnection(const ConnectionProxy& cn);
	static int availableConnection();//返回可用的链接数
	~ConnectionPool();
private:
	ConnectionPool();
private:
	static ConnectionPoolImpl* _impl;
};

typedef int CP_HANDLE;//句柄号
//connection类的Proxy包覆类，该类设计的目的是：1、隐藏close方法 2、隐藏CP_HANDLE的使用
class ConnectionProxy:public oralib::connection
{
	friend class ConnectionPoolImpl;
	friend bool operator==(const ConnectionProxy& lhs, const ConnectionProxy& rhs);
	ConnectionProxy(const string& login,const string& password,const string& service_name,CP_HANDLE handle)
		:connection(login,password,service_name),_handle(handle){}
	using connection::close;
	CP_HANDLE getHandle() const{return _handle;}
	CP_HANDLE _handle;
};

inline bool operator==(const ConnectionProxy& lhs, const ConnectionProxy& rhs)
{
	return lhs.getHandle() == rhs.getHandle();
}
