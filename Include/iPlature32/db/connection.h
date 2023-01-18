/**


*/


#ifndef	_CONNECTION_H
#define	_CONNECTION_H


namespace oralib {


class statement;
class resultset;
class column;     //2007-6-22 add ,aix下需要。
class parameter;

class connection
{
	// friends
	friend class statement;
	friend class parameter;
	friend class resultset;
	friend class column;
	friend class LobHelper;

private:
	OCIEnv		*environment_handle;
	OCIServer	*server_handle;
	mutable OCIError	*error_handle;	// because it could be changed by most oracle APIs
	OCISession	*session_handle;
	OCISvcCtx	*svc_context_handle;

	bool		is_opened;
	bool		is_available;			// (used for connection pooling)?
	bool		is_blocking;			// mode (a call could return OCI_STILL_EXECUTING)
    string		strLogin;
	string		strPassword;
	string 		strService_Name;

private://add by xcs.2006-7-4
	typedef std::vector <column*>	Columns;
	Columns			columns;		// an array with result set columns	

	//add by xcs.2008-3-24解决statement和resultset的自动释放问题
	//2008-10-06取消此功能.

private:
	statement* currentstat;
	resultset* currentrs;
	//std::vector<statement*> vec_statements;
	//std::vector<resultset*> vec_resultsets;

public:
	void release();

private:
	// private copy-constructor and assignment operator - class could not be copied
	inline connection (
		IN const connection& /* cn */) { /* could not be copy-constructed */ };
	inline connection& operator = (
		IN const connection& /* cn */) { return (*this); /* could not be copy-constructed */ };

	// initialize private data
	void initialize (void);

	// free resources allocated
	inline void cleanup (void) { close (); };


public:
	connection (void);

	//connection (
	//	IN const char* login,
	//	IN const char* password,
	//	IN const char* service_name,
	//	IN OPTIONAL unsigned long env_mode = OCI_OBJECT,
	//	IN OPTIONAL bool non_blocking_mode = false);

	// create an instance and open the connection
	//service_name不提供默认为本机的
	connection (
		IN const string& login,
		IN const string& password,
		IN const string& service_name="",
		IN OPTIONAL unsigned long env_mode = OCI_OBJECT,
		IN OPTIONAL bool non_blocking_mode = false);

	~connection ();

	// connects to an Oracle server
	void open (
		IN const string& login,
		IN const string& password,
		IN const string& service_name,
		IN OPTIONAL unsigned long env_mode = OCI_OBJECT,
		IN OPTIONAL bool non_blocking_mode = false);

	//void open (
	//	IN const char* login,
	//	IN const char* password,
	//	IN const char* service_name,
	//	IN OPTIONAL unsigned long env_mode = OCI_OBJECT,
	//	IN OPTIONAL bool non_blocking_mode = false);

	// closes the connection
	void close (void);
    void reopen();

public:
	//2007年8月13日，增加检查Oracle状态的代码
	int checkstatus();

public:
	int statcount(string sql); //代替select count(*) 的功能,2008-10-06发现一个bug，就是没有释放该statement和resultset.
	//各参数分开，组合用
	int statcount(string columnname,string table,string szwhere,int distincnt = 0);//代替select count(column) 的功能

public:
	// executes a sql statement with no result
	int execute (
		IN const char *sql_block,
		IN OPTIONAL int sql_len = -1);

	// prepares (and returns) a sql statement for execution
	statement *prepare (
		IN const char *sql_block,
		IN OPTIONAL int sql_len = -1);

	// executes a select sql statement and return the result set
	resultset *select (
		IN const char *select,
		IN OPTIONAL int select_len = -1);

	// commits changes
	inline void commit (void)
		{ execute ("commit", 6); };

	// rollbacks changes
	inline void rollback (void)
		{ execute ("rollback", 8); };
}; // connection class


}; // oralib namespace




#endif	// _CONNECTION_H

