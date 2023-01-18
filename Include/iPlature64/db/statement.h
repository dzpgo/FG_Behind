/**
*宝信Oralib数据库访问技术，来源于开源项目http://606u.dir.bg/
当前版本1.1
最后修改时间2008-03-20
最初开发时间2006-05-08
*/


#ifndef	_STATEMENT_H
#define	_STATEMENT_H


namespace oralib {


// statement type - select statements and pl/sql blocks are handled with care
enum StatementTypesEnum
{
	ST_UNKNOWN,
	ST_SELECT = OCI_STMT_SELECT,
	ST_UPDATE = OCI_STMT_UPDATE,
	ST_DELETE = OCI_STMT_DELETE,
	ST_INSERT = OCI_STMT_INSERT,
	ST_CREATE = OCI_STMT_CREATE,
	ST_DROP = OCI_STMT_DROP,
	ST_ALTER = OCI_STMT_ALTER,
	ST_BEGIN = OCI_STMT_BEGIN,
	ST_DECLARE = OCI_STMT_DECLARE
};


class statement
{
	// friends
	friend class parameter;
	friend class connection;

private:
	bool isreleased ;
private:
	connection		*conn;			// being used
	OCIStmt			*stmt_handle;
	std::string		sql;			// being executed
	StatementTypesEnum	type;		// of the statement

	typedef std::vector <parameter *> Parameters;
	typedef std::map <std::string, parameter *> ParametersMap;
	Parameters		parameters;		// an array with bound parameters
	ParametersMap	parameters_map;	// a map with parameters against their names

	bool			is_prepared;
	bool			is_executed;

	int count ;
	int interval_time;

private:

	void rebindparameter(); //重新绑定参数信息，2007-8-13日


	// public not creatable; use connection.execute, .prepare or .select
	// prepares an sql statement for execution
	statement (
		IN connection &use,
		IN const char *sql_block,
		IN OPTIONAL int sql_len = -1);

	// public not deletable; use release method instead
	~statement ();

	// private copy-constructor and assignment operator - class could not be copied
	statement (
		IN const statement& /* st */) { /* could not be copy-constructed */ };
	statement& operator = (
		IN const statement& /* st */) { return (*this); /* could not be copy-constructed */ };

	// initialize private data
	void initialize (void);

	// free resources allocated
	void cleanup (void);

	// prepares an sql statement for execution
	void prepare (
		IN const char *sql_block,
		IN OPTIONAL int sql_len = -1);

	// executes already prepared statement
	int execute_prepared (void);

public:
	// binds a named variable to the statement
	// when type is set to DT_UNKNOWN type is taken from name's prefix
	parameter &bind (
		IN const char *name,
		IN OPTIONAL DataTypesEnum type = DT_UNKNOWN);

	// executes a prepared statement with no output parameters
	inline int execute (void) { return execute_prepared (); };

	// executes a prepared select sql statement and returns the result set
	resultset *select (void);

	// releases statement
	//inline void release (void) { if(!isreleased)delete this;isreleased = true; };
	inline void release (void) { delete this;};

	// returns a bound parameter by name or index
	parameter& operator [] (
		const char *name);
	parameter& operator [] (
		ub2 parameter_index);
}; // statement class


}; // oralib namespace


#endif	// _STATEMENT_H


