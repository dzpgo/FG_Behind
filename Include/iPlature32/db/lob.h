/**
*����Oralib���ݿ���ʼ���
 2008-8-31 ��������ͨ��;
 2007-8-28������Lob������
*/
#ifndef	_LOBHELPER_H
#define	_LOBHELPER_H

namespace oralib {
	
	class connection;
	
	class LobHelper{
	
	friend class connection;

		public:
			//����connection��Ϊ����
			LobHelper (IN connection *use);
			~LobHelper();
		
		public:
			//����clob����Ϣ
			//����ʵ��ʹ�ã����ֲ���LobLocator�ƺ�Ҳ��
			int update(string tablename,string colname,string condition,void* data,	ub4	data_len,ub2 lobtype = SQLT_CLOB);

			//������LobLocator
			int update2(string tablename,string colname,string condition,void* data, ub4 data_len,ub2 lobtype = SQLT_CLOB);

			//��ȡ����
			void* read(string tablename,string colname,string condition,ub2 lobtype = SQLT_CLOB);

			//ʹ��LobLocator
			void* read2(string tablename,string colname,string condition,int* preadlen,ub2 lobtype = SQLT_CLOB);
			
			//�ͷ���Դ
			int release();
	
		private:
			// initialize private data
			void initialize (void);
			void prepare ();
			void cleanup();

		private:
			connection		*conn;			// being used
			void *buffer;  //���ض�ȡ������
			void *tempbuffer;  //piecewise��ʽ��ȡ����
			OCILobLocator * one_lob;
			OCIBind			*bndhp;
		    OCIStmt			*stmt_handle;
			OCIParam	    *param_handle;  
			OCIDefine		*define_handle;//�������
   };
};

#endif

