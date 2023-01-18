/**
*宝信Oralib数据库访问技术，来源于开源项目http://606u.dir.bg/
 2007-6-22日重新整理
*/


#ifndef	_RESULTSET_H
#define	_RESULTSET_H


namespace oralib {
	 class connection;
	 class statement;
	 class parameter;
	 class column;

class resultset
{
	// friends
	friend class connection;
	friend class statement;
	friend class parameter;
	friend class column;

private:
	bool isreleased ;

private:
	typedef std::vector <column*>	Columns;
	typedef std::map <std::string, column*>	ColumnsMap;
	Columns			columns;		// an array with result set columns
	ColumnsMap		columns_map;	// a map with columns against their names

	connection		*conn;			// active connection
	OCIStmt			*rs_handle;		// oci statement handle for the result set
	
	statement		*stmt;			// if created via connection.select
	ub4				fetch_count;	// number of rows to fetch at once

	ub4				rows_fetched;	// number of rows fetched so far
	ub4				current_row;	// current row (0-based)
	bool			is_eod;			// end-of-data reached?

	bool			is_described;	// is result set (columns) described flag
	bool			is_defined;		// is result set defined flag

private:
	// public - not creatable
	resultset (
		IN OCIStmt *rs,
		IN connection *use,
		IN OPTIONAL ub2 fetch_size = FETCH_SIZE);
	
	// public - not deletable - use release instead
	~resultset ();

	// private copy-constructor and assignment operator - class could not be copied
	resultset (
		IN const resultset& /* rs */) { /* could not be copy-constructed */ };
	resultset& operator = (
		IN const resultset& /* rs */) { return (*this); /* could not be copy-constructed */ };

	// initialize private data
	void initialize (void);

	// free resources allocated
	void cleanup (void);

	// attaches a result set object to a statement handle
	void attach (
		IN OCIStmt *rs,
		IN connection *use,
		IN OPTIONAL ub2 fetch_size = FETCH_SIZE);

public://2008-06-26  private-->public
	// returns number of columns
	ub4 columns_count (void);

	// returns number of rows fetched so far
	ub4 rows_count (void);

private:
	// attaches a statement - freed, when the result set is released (connection.select)
	void attach_statement (
		IN statement *select);

	// describe columns of the result set
	void describe (void);

	// define columns of the result set - bound buffers to columns
	void define (void);

	// fetch new block of rows in the buffers
	void fetch_rows (void);

public:
	// return end-of-data indicator
	inline bool eod (void) const { return (current_row >= rows_fetched && is_eod); };

	// skip to next row; returns false if current one is the last
	inline bool operator ++ () { return (next ()); };
	bool next (void);

	// access columns in the current row by name or index
	column& operator [] (const char *column_name);
	column& operator [] (ub2 column_index);

	//void release (void);

	void print(){cout<<"current:"<<isreleased<<endl;}
	//inline void release (void) { if(!isreleased)delete this;isreleased = true; };
	void release (void) { delete this; };
}; // resultset class


}; // oralib namespace


#endif	// _RESULTSET_H

