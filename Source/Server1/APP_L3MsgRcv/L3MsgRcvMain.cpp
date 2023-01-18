/*********************************************************************
*		
*  ��      ��:    L3MsgRcv.cpp   		
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������L3���Ľ���
*
*  �汾��ʷ		
*      1.0    2017-06-07    Zhangyuhong    ����
*********************************************************************/
#include <pace/P99Component.h>
#include <iXcomTCP2.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
#include "DataAccess.h"
#include "MsgKIBH01.h"
#include "MsgKIBH02.h"
#include "MsgKIBH03.h"
#include "MsgKIBH04.h"
#include "MsgKIBH05.h"

using namespace iXcomTCP2;
using namespace iPlature;
using namespace Monitor;


class APP_L3MsgRcv:public iPlature::P99Component
{
	
public:
	/**********************************************************************
	*  ����: �������
	*  �������� PostInitCall 
	*  ����ֵ�� void	 	
	*  �����б�	��������    					ȡֵ��Χ     		    ����
	*
	*  �汾��ʷ		
	*       1.0    2017-06-07  LuYongyu    ����
	*  
	**********************************************************************/
	void PostInitCall()
	{
		LOG::doConfigure("APP_L3MsgRcv", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_L3MsgRcv");
		log.Info()<<"APP_L3MsgRcv:"<<endl;
		
		InitPowertranserData();

		//���ݿ�����
		CDataAccess::GetInstance()->Initialize();

		logFileNameKIBH01 = "KIBH01";
		logFileNameKIBH02 = "KIBH02";
		logFileNameKIBH03 = "KIBH03";
		logFileNameKIBH04 = "KIBH04";
		logFileNameKIBH05 = "KIBH05";

		//�趨����L3������־��
		string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";		
		LOG::doConfigure( logFileNameKIBH01,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameKIBH02,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameKIBH03,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameKIBH04,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameKIBH05,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
	}

	/**********************************************************************
	*  ����: ���յ��Ĳ���������
	*  �������� HandleMessage 
	*  ����ֵ�� Ice::ByteSeq	 	��������
	*  �����б�	��������    					ȡֵ��Χ     		    ����
	*    ParamBuffer  :    [IN/OUT] const ByteSeq &	     		  ���յ��ĵ���seq
	*
	*  �汾��ʷ		
	*       1.0    2017-06-07  LuYongyu    ����
	*  
	**********************************************************************/
	ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
	{
		LOG log(__FUNCTION__,"APP_L3MsgRcv");

		 string functionName="APP_L3MsgRcv::HandleMessage()";

		log.Info()<<"****************************************************************************************************************************."<<endl; 
		log.Info()<<"                                                                        data received                                                                                                                         "<<endl;
		log.Info()<<"****************************************************************************************************************************."<<endl; 		

		//pwת������
		ByteSeq receiver(ParamBuffer);
		string msgID;
		receiver>>msgID;
		log.Info()<<"msgID = "<<msgID<<endl;

		try
		{
			//�ϸ�Ʒ����Ϣ����
			if (msgID == "KIBH01")
			{
				MsgKIBH01::getInstance()->HandleMessage(receiver, logFileNameKIBH01);
			}
			//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����
			else if (msgID == "KIBH02")
			{
				MsgKIBH02::getInstance()->HandleMessage(receiver, logFileNameKIBH02);
			}
			//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����
			else if (msgID == "KIBH03")
			{
				MsgKIBH03::getInstance()->HandleMessage(receiver, logFileNameKIBH03);
			}
			//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����
			else if (msgID == "KIBH04")
			{
				MsgKIBH04::getInstance()->HandleMessage(receiver, logFileNameKIBH04);
			}
			//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����
			else if (msgID == "KIBH05")
			{
				MsgKIBH05::getInstance()->HandleMessage(receiver, logFileNameKIBH05);
			}
		
		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName+"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch (...)
		{

		}
		return	 receiver;
	}

	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		arry.push_back("KIBH01");
		arry.push_back("KIBH02");
		arry.push_back("KIBH03");
		arry.push_back("KIBH04");
		arry.push_back("KIBH05");


		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	/* ����*/
	virtual ~APP_L3MsgRcv()
	{
		try
		{
			//�Ͽ����ݿ�����
			CDataAccess::GetInstance()->UnInitialize();
		}
		catch(...)
		{
		}
	}

	private:
		//���Ķ�Ӧ�Ĵ�ӡ��־�ļ���
		string logFileNameKIBH01;
		string logFileNameKIBH02;
		string logFileNameKIBH03;
		string logFileNameKIBH04;
		string logFileNameKIBH05;

};

PACE_SERVER_INSTALL(APP_L3MsgRcv);