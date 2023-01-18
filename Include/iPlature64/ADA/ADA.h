/*********************************************************************
*		
*  ��      ��:    ADA.h   		
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������
*
*  �汾��ʷ		
*      1.0    2009-08-10    lumengyi    ����
*     
*********************************************************************/
#include <ADA/IConnection.hpp>
#include <ADA/IStatement.hpp>
#include <ADA/IResultSet.hpp>

//����Ϊֹ��֧�ֵ����ݿ�������
#include <ADA/ADAOracle.h>
#include <ADA/ADASqlserver.h>

//��ǰ��ʹ�����ݿ�����
#define ORACLE_DB

//��ǰ��ʹ�����ݿ���ļ�
#ifdef WIN32
	#ifdef ORACLE_DB
		#ifdef _DEBUG
			#pragma comment(lib,"oralib.lib")
		#else
			#pragma comment(lib,"oralibR.lib")
		#endif
	#endif
	#ifdef SQLSERVER_DB
		#pragma comment(lib,"sqlserver.lib")
	#endif
#endif