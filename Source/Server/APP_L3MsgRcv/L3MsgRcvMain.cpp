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
#include "MsgP4HC01.h"
#include "MsgP4HC02.h"
#include "MsgP4HC03.h"
#include "MsgP4HC11.h"
#include "MsgP4HC12.h"

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

		logFileNameP4HC01 = "P4HC01";
		logFileNameP4HC02 = "P4HC02";
		logFileNameP4HC03 = "P4HC03";
		logFileNameP4HC11 = "P4HC11";
		logFileNameP4HC12 = "P4HC12";

		//�趨����L3������־��
		string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";		
		LOG::doConfigure( logFileNameP4HC01,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameP4HC02,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameP4HC03,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameP4HC11,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameP4HC12,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
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
			if (msgID == "P4HC01")
			{
				MsgP4HC01::getInstance()->HandleMessage(receiver, logFileNameP4HC01);
			}
			//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����
			else if (msgID == "P4HC02")
			{
				MsgP4HC02::getInstance()->HandleMessage(receiver, logFileNameP4HC02);
			}
			//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����
			else if (msgID == "P4HC03")
			{
				MsgP4HC03::getInstance()->HandleMessage(receiver, logFileNameP4HC03);
			}
			//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����
			else if (msgID == "P4HC11")
			{
				MsgP4HC11::getInstance()->HandleMessage(receiver, logFileNameP4HC11);
			}
			//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����
			else if (msgID == "P4HC12")
			{
				MsgP4HC12::getInstance()->HandleMessage(receiver, logFileNameP4HC12);
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
		arry.push_back("P4HC01");
		arry.push_back("P4HC02");
		arry.push_back("P4HC03");
		arry.push_back("P4HC11");
		arry.push_back("P4HC12");


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
		string logFileNameP4HC01;
		string logFileNameP4HC02;
		string logFileNameP4HC03;
		string logFileNameP4HC11;
		string logFileNameP4HC12;

};

PACE_SERVER_INSTALL(APP_L3MsgRcv);