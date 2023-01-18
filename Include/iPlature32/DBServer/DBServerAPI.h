#ifndef __IPLATURE_DBSERVERAPI_H__
#define __IPLATURE_DBSERVERAPI_H__

#ifdef _WIN32

#ifdef DBSERVERDLL_EXPORTS

#define DBSERVER_API  __declspec(dllexport)

#else

#define DBSERVER_API  __declspec(dllimport)

#endif

#else

#define DBSERVER_API

#endif

#define MAX_ARRAY_LENGTH 1024

typedef struct _ColumnField
{
	char szName[MAX_ARRAY_LENGTH];
	char szValue[MAX_ARRAY_LENGTH];
}ColumnField, *ColumnFieldPtr;

typedef struct _DBResult
{
	int ret;
	char msg[MAX_ARRAY_LENGTH];
}DBResult;

extern "C" DBSERVER_API DBResult CreateConnect(const char* dbname, void** cnn);

extern "C" DBSERVER_API DBResult CloseConnect(void* cnn);

extern "C" DBSERVER_API DBResult Commit(void* cnn);

extern "C" DBSERVER_API DBResult Rollback(void* cnn);

//extern "C" DBSERVER_API int ExecuteSQL(void* cnn, const char* sql, char* errmsg);

extern "C" DBSERVER_API DBResult ExecuteEx(void* cnn, const char* sql);

extern "C" DBSERVER_API DBResult FetchNext(void* cnn, bool* exist);

extern "C" DBSERVER_API DBResult FieldByIndex(void* cnn, int index, ColumnFieldPtr pField);

extern "C" DBSERVER_API DBResult FieldsByName(void* cnn, char* fieldname, ColumnFieldPtr pField);





#endif