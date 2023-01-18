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
	BLOCK,		//������ʽ��getConnectionʱ��sleep
	NONBLOCK	//��������ʽ��getConnectionʱ���׳��쳣ConnectionPoolException
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
	static int availableConnection();//���ؿ��õ�������
	~ConnectionPool();
private:
	ConnectionPool();
private:
	static ConnectionPoolImpl* _impl;
};

typedef int CP_HANDLE;//�����
//connection���Proxy�����࣬������Ƶ�Ŀ���ǣ�1������close���� 2������CP_HANDLE��ʹ��
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
