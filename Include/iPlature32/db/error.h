/**
*宝信Oralib数据库访问技术，来源于开源项目http://606u.dir.bg/
 2007-6-22日重新整理
*/


#ifndef	_ERROR_H
#define	_ERROR_H


namespace oralib {


// error codes thrown from the library
enum ErrorCodesEnum
{
	EC_OCI_ERROR = -1,
	EC_ENV_CREATE_FAILED = 1000,
	EC_TIMEOUT,
	EC_NO_MEMORY,
	EC_BAD_PARAM_TYPE,
	EC_POOL_NOT_SETUP,
	EC_BAD_INPUT_TYPE,
	EC_BAD_OUTPUT_TYPE,
	EC_BAD_TRANSFORM,
	EC_BAD_PARAM_PREFIX,
	EC_UNSUP_ORA_TYPE,
	EC_PARAMETER_NOT_FOUND,
	EC_COLUMN_NOT_FOUND,
	EC_INTERNAL,
	EC_USER_DEFINE //xcs
};


// error types
enum ErrorTypesEnum
{
	ET_UNKNOWN = 0,
	ET_ORACLE,
	ET_ORALIB,
	ET_WINAPI,
	ET_USER_APP //xcs
};


class error
{
private:
	ErrorTypesEnum	type;		// type
	sword		code;			// error code if library error or -1 if Oracle error
	sb4			ora_code;		// Oracle's error code - ORA-xxxxx
//#if	defined (_WIN32)
	unsigned long	winapi_code;	// win32 api error code (Windows platform only!)
//#endif
	std::string	description;	// error description as a text
	std::string	source;			// source file, where error was thrown (optional)
	long		line_no;		// line number, where error was thrown (optional)

private:
	// sets-up an oracle error details
	void oracle_error (
		IN sword ora_err,
		IN OCIError *error_handle,
		IN OCIEnv *env_handle);

	// sets-up a library error details
	void oralib_error (
		IN sword oralib_err);

#if	defined (_WIN32)
	// sets-up a winapi call error details
	void winapi_error (void);
#endif

	// formats printf-like message and concats it to the description
	void concat_message (
		IN const char *format,
		IN va_list va);

private:
	// private assignment operator - class could not be copied
	error& operator = (
		IN const error& /* err */) { return (*this); /* could not be copy-constructed */ };


//2006-2-6
public:
    int getOCICode();


public:
//2007-1-15徐长盛加入	
		error (const char * msg);
		error (const std::string& msg);

//2007-8-13 add
		error (sb4 code,const std::string& msg);
	
	// oracle error via error handle
	error (
		IN sword ora_err,
		IN OCIError *error_handle,
		IN OPTIONAL const char *source_name = NULL,
		IN OPTIONAL long line_number = -1,
		IN OPTIONAL const char *format = NULL,
		...);

	// oracle error via environment handle
	error (
		IN sword ora_err,
		IN OCIEnv *env_handle,
		IN OPTIONAL const char *source_name = NULL,
		IN OPTIONAL long line_number = -1,
		IN OPTIONAL const char *format = NULL,
		...);

	// library error
	error (
		IN sword oralib_err,
		IN OPTIONAL const char *source_name = NULL,
		IN OPTIONAL long line_number = -1,
		IN OPTIONAL const char *format = NULL,
		...);

#if	defined (_WIN32)
	// winapi error
	error (
		IN OPTIONAL const char *source_name = NULL,
		IN OPTIONAL long line_number = -1,
		IN OPTIONAL const char *format = NULL,
		...);
#endif

	// copy constructor
	error (
		IN const error& err);

	~error ();

	// return error details (in a format, similar to display method output)
	std::string	details (void) const;

#if	!defined (ORALIB_NO_ERROR_DISPLAY)
	// dumps error details to cout
	void	display (void);
#endif
}; // error class


}; // oralib namespace


#endif	// _ERROR_H

