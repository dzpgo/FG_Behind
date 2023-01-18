#pragma once
namespace iPlature
{
	namespace iDA
	{
		typedef	enum
		{
			//! DBMS client is not specified
			iDA_Client_NotSpecified,
			//! ODBC
			iDA_ODBC_Client,
			//! Oracle
			iDA_Oracle_Client,
			//! Microsoft SQL Server
			iDA_SQLServer_Client,
			//! InterBase or Firebird
			iDA_InterBase_Client,
			//! SQLBase
			iDA_SQLBase_Client,
			//! IBM DB2
			iDA_DB2_Client,
			//! Informix
			iDA_Informix_Client,
			//! Sybase ASE 
			iDA_Sybase_Client,
			//! MySQL
			iDA_MySQL_Client,
			//! PostgreSQL
			iDA_PostgreSQL_Client,
			//! SQLite
			iDA_SQLite_Client,
			//! DBServer
			iDA_DBServer_Client,
			_iDA_Client_Reserverd = (int)(((unsigned int)(-1))/2)
		} iDA_Client_t;

		typedef enum
		{
			iDA_dtUnknown,
			iDA_dtBool,
			iDA_dtShort,
			iDA_dtUShort,
			iDA_dtLong,
			iDA_dtULong,
			iDA_dtDouble,
			iDA_dtNumeric,
			iDA_dtDateTime,
			iDA_dtInterval,
			iDA_dtString,
			iDA_dtBytes,
			iDA_dtLongBinary,
			iDA_dtLongChar,
			iDA_dtBLob,
			iDA_dtCLob,
			iDA_dtCursor,
			iDA_dtSpecificToDBMS,
			_iDA_DataType_Reserved = (int)(((unsigned int)(-1))/2)
		}iDA_Data_t;

		typedef	enum
		{
			//! the default(unknown) auto-commit mode
			iDA_AutoCommitUnknown = -1,
			//! auto-commit mode is off
			iDA_AutoCommitOff,
			//! auto-commit mode is on
			iDA_AutoCommitOn,
			_iDA_AutoCommit_Reserved = (int)(((unsigned int)(-1))/2)
		} iDA_AutoCommit_t;

		class NullValue{};

	}//namespace iDA
}//namespace iPlature