/**
*宝信Oralib数据库访问技术
 2008-2-26日connection的open函数第3个参数不提供，则直接登录，注释
 	//ASSERT (!service_name.empty() && !login.empty() && !password.empty());
 2007-8-13日增加REOPEN_INTERVAL和REOPEN_COUNT
*/


 #ifndef	_ORALIB_H
#define	_ORALIB_H


namespace oralib {


//默认值

const int DEF_INT = -999;
const long DEF_LONG = -999;
const float DEF_FLOAT = -999.99f;
const double DEF_DOUBLE = -999.99;

#if	defined (_WIN32) // Windows platform
const int REOPEN_INTERVAL = 3000;
#else
const int REOPEN_INTERVAL = 3;
#endif

const int REOPEN_COUNT = 3;//重新连接的次数

//const Pstr DEF_STRING = "Null";



// L I B R A R Y   C O N F I G


// uncomment next line if you wish not to have error.display method
// (usable, because it forces linker to include iostream library)
#define	ORALIB_NO_ERROR_DISPLAY

// maximal length (in characters) of a text input and/or output parameter
const ub2 MAX_OUTPUT_TEXT_BYTES = 4000;  //2007-8-22，修改此参数为4000

const ub2 MAX_LOB_BUF_LEN = 8000; //2007-8-31，为Lob分配的最大空间

// number of rows to request on each fetch
//默认一次性读取的数目
const ub2 FETCH_SIZE = 20;

// maximal length (in ansi characters) of user-supplied error message to format
const ub2 ERROR_FORMAT_MAX_MSG_LEN = 1024;

// index of the first column in a result set (one of 0, 1)
const ub2 FIRST_COLUMN_NO = 1;

// index of the first parameter in a statement (one of 0, 1)
const ub2 FIRST_PARAMETER_NO = 1;

// unicode/ansi
// keep in mind, that those are valid for data values only
// parameter and column names are still in ansi
#if defined (UNICODE)
	typedef std::wstring String;
	typedef const wchar_t *Pstr;
	const int CHAR_SIZE = sizeof (wchar_t);
#else
	typedef std::string String;
	typedef const char *Pstr;
	const int CHAR_SIZE = sizeof (char);
#endif

#ifdef _WIN32
#   include <sys/timeb.h>
#   include <time.h>
#pragma warning (disable : 4996)
#else
#   include <sys/time.h>
#endif
	
	const time_t TIMEMAX = 2147426047;

// IN means an input parameter; OUT is an output parameter
// IN OUT is both input and output parameter
// OPTIONAL means, that value is not required - a default will be used instead
#if	!defined (IN)
#	define	IN
#endif
#if	!defined (OUT)
#	define	OUT
#endif
#if	!defined (OPTIONAL)
#	define	OPTIONAL
#endif


// internal data types are 4 only: number, date, text and result set
enum DataTypesEnum
{
	DT_UNKNOWN,
	DT_NUMBER,
	DT_DATE,
	DT_TEXT,
	DT_RESULT_SET,
	DT_CLOB   //2007年8月22日增加
};


// parameter prefixes (for example: :n1 is a number, :sName is a text)
enum ParameterPrefixesEnum
{
	PP_ARRAY = 't',
	PP_NUMERIC = 'n',
	PP_DATE = 'd',
	PP_TEXT = 's',
	PP_RESULT_SET = 'c',
	PP_CLOB = 'l'
};


}; // oralib namespace


#endif	// _ORALIB_H

#include "error.h"
#include "datetime.inl"
#include "connection.h"
#include "column.h"
#include "resultset.h"
#include "statement.h"
#include "parameter.h"
#include "lob.h"

