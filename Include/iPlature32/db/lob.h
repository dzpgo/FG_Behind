/**
*宝信Oralib数据库访问技术
 2008-8-31 经过测试通过;
 2007-8-28日增加Lob处理功能
*/
#ifndef	_LOBHELPER_H
#define	_LOBHELPER_H

namespace oralib {
	
	class connection;
	
	class LobHelper{
	
	friend class connection;

		public:
			//传入connection作为参数
			LobHelper (IN connection *use);
			~LobHelper();
		
		public:
			//更新clob的信息
			//经过实际使用，发现不用LobLocator似乎也可
			int update(string tablename,string colname,string condition,void* data,	ub4	data_len,ub2 lobtype = SQLT_CLOB);

			//尝试用LobLocator
			int update2(string tablename,string colname,string condition,void* data, ub4 data_len,ub2 lobtype = SQLT_CLOB);

			//读取数据
			void* read(string tablename,string colname,string condition,ub2 lobtype = SQLT_CLOB);

			//使用LobLocator
			void* read2(string tablename,string colname,string condition,int* preadlen,ub2 lobtype = SQLT_CLOB);
			
			//释放资源
			int release();
	
		private:
			// initialize private data
			void initialize (void);
			void prepare ();
			void cleanup();

		private:
			connection		*conn;			// being used
			void *buffer;  //返回读取的数据
			void *tempbuffer;  //piecewise方式读取数据
			OCILobLocator * one_lob;
			OCIBind			*bndhp;
		    OCIStmt			*stmt_handle;
			OCIParam	    *param_handle;  
			OCIDefine		*define_handle;//输出参数
   };
};

#endif

