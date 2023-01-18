/**
*宝信Oralib数据库访问技术，来源于开源项目http://606u.dir.bg/
2008-03-27 全新整理、修改
当前版本1.1
最后修改时间2008-03-20
最初开发时间2006-05-08
*/

#ifndef	_COLUMN_H
#define	_COLUMN_H


namespace oralib {


class column
{
	// friends
	friend class resultset;

private:
	std::string		col_name;		// in the exact case
	DataTypesEnum	col_type;		// as it will be returned
	ub2				oci_type;		// oracle's data type
	ub2				oci_type_ex;		// add by haykin, 2010-08-24
	int				size;			// number of bytes required for

	sb2				*indicators;	// an array with indicators: 0 - ok; -1 - null
	ub2				*data_lens;		// an array with data lengths (for text columns)
	char			*fetch_buffer;	// where data is returned (fetched)

	OCIDefine		*define_handle;	// used for the column
	resultset		*result_set;	// is the column's owner

private:
	// public not creatable; use connection.select or statement.select
	// attaches this column to a result set; allocates memory for the fetch buffer
	column (
		IN resultset *rs,
		IN const char *name,
		IN ub4 name_len,
		IN ub2 oci_data_type,
		IN ub4 max_data_size,
		IN OPTIONAL int fetch_size = FETCH_SIZE);

	// public not deletable; deleted, when result set is released
	~column ();

	// initialize data members
	void initialize (void);

	// free resources allocated
	void cleanup (void);

	// private copy-constructor and assignment operator - class could not be copied
	column (
		IN const column& /* col */) { /* could not be copy-constructed */ };
	column& operator = (
		IN const column& /* col */) { return (*this); /* could not be assigned */ };



public:
	// returns whether column value is null
	bool is_null (void) const;

	// returns column type
	inline DataTypesEnum type (void) const { return (col_type); };

	// returns column value as a text
	inline operator Pstr (void) const { return (as_string ()); };
	Pstr as_string (void) const;

	// returns column value as a double
	inline operator double (void) const { return (as_double ()); };
	double as_double (void) const;

	// returns column value as a long
	inline operator long (void) const { return (as_long ()); };
	long as_long (void) const;

	// returns column value as a date/time helper class
	inline operator datetime (void) const { return (as_datetime ()); };
	datetime as_datetime (void) const;

	// (column is not deleted by the client, but when result set is released instead)
	inline void release (void) { };
}; // column class


}; // oralib namespace


#endif	// _COLUMN_H


