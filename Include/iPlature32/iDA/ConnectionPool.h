/*********************************************************************
 *		
 *  文      件:    ConnectionPool.h   		数据库连接池
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2010-11-23    Haykin-2010    //TODO请添加本次主要修改内容
 *      %USER%   
*********************************************************************/
#pragma once
#include <iDA/iDA.h>
#include <IceUtil/Shared.h>
#include <IceUtil/Handle.h>
namespace iPlature
{
	namespace iDA
	{

		class ConnectionPoolException : public std::exception
		{
		public:
			virtual ~ConnectionPoolException() throw();
			ConnectionPoolException(const std::string& msg);
			virtual const char* what() const throw();
		private:
			std::string  _what;
		};

		enum CP_BLOCK_MODE
		{
			BLOCK,		//阻塞方式，getConnection时会sleep
			NONBLOCK	//非阻塞方式，getConnection时会抛出异常ConnectionPoolException
		};

		class ConnectionProxy;
		typedef IceUtil::Handle<ConnectionProxy> ConnectionProxyPtr;


		class ConnectionPoolImpl;

		class ConnectionPool
		{
			friend class ConnectionProxy;
		public:
			static void initialize(const std::string& dbname
											, const std::string& login
											, const std::string& password
											, iDA::iDA_Client_t client
											, unsigned int PoolSize = 1,
											CP_BLOCK_MODE mode = BLOCK);
			static void destroy();
			static ConnectionProxyPtr getConnection();
			static int availableConnection();//返回可用的链接数
			~ConnectionPool();
		private:
			ConnectionPool(){}
			static void returnConnection(int id);
		private:
			static ConnectionPoolImpl* _impl;
		};

		class ConnectionProxy : public iDA::Connection
		{
		public:
			ConnectionProxy( int id);

			void __incRef();
			void __decRef();
			bool operator == (const ConnectionProxy& rsh);
		private:
			int _id;
			int _ref;
		};

		inline bool ConnectionProxy::operator == (const ConnectionProxy& rsh)
		{
			return this->_id == rsh._id;
		}

		/*class ConnectionProxyHolder : public IceUtil::SimpleShared
		{
		public:
			ConnectionProxyHolder(ConnectionProxy* _cnn);
			~ConnectionProxyHolder();
		public:
			iDA::Connection* operator -> ();
		private:
			ConnectionProxy* _cnn;
			
		};*/
	}
}

