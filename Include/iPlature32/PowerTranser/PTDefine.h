#ifndef __PT__DEFINE__
#define __PT__DEFINE__
//#include <db/_p.h>
//#include <db/oralib.h>

//using namespace oralib;
#include <string>

const std::string MSG_TABLE = "T_BM_MSG";
const std::string MSGITEM_TABLE = "T_BM_MSGITEM";
const std::string DBLINK_SETUP_TABLE = "T_BM_MSG_DBLINK";
const std::string SPLITMODE_TABLE = "T_BM_MSG_SPLITMODE";
const std::string TRANSER_PROGRAM = "PowerTranserAdmin";
const std::string XCOM_DBLINK_PROGRAM = "XCOM_DBLinkAdmin";
const std::string XCOM_PCS_PROGRAM = "iPlature/XCOMPCS_PT_AdapterOut";
const std::string HeaderString = "Header";

const int INT_SIZE = 4;
const int FLOAT_SIZE = 4;
const int DEFAULT_SIZE = 4;

enum COMMODE
{
	COMMODE_XCOM_PCS = 1,
	COMMODE_XCOM = 2,
	COMMODE_DBLINK = 3,
	COMMODE_DI = 4
};

enum PT_SPLITMODE
{
	SPLITMODE_DELIMITER = 1,  //���ݷָ����ָ�
	SPLITMODE_FIELD = 2,	  //���ָ��������ݿ�FIELDΪ׼
	SPLITMODE_SIZE = 3,       //���ݳ��ȷָ�
	SPLITMODE_BINARY = 4	  //���ݳ��ȷָ����������Ƕ����Ʒ�ʽ��
};
//namespace iPlature
//{
//	namespace PowerTranser
//	{
		const std::string PT_DT_INTEGER = "INTEGER";
		const std::string PT_DT_FLOAT = "FLOAT";
//	}
//}
#endif
