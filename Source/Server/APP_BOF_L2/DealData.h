//********************************************************************
//** Copyright (c) 2016 �������
//** �����ˣ�½����
//** ������\�ļ�����MsgEUKDW2.cpp
//** �๦�ܣ�����������
//** �������������������
//** �������ڣ�2016-12-30
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#pragma once
#include <pace/pace.h>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"


using namespace iPlature;
using namespace std;
using namespace Monitor;


class DealData
{
	public:
		string DumpValue(SmartData& sd,const string& ident);

		//����ǰ������ϸ����L3_Send��
		void InsertSendData(std::string msgId,std::string dataStr,ByteSeq data,int id);

		void InsertRcvData(std::string msgId,std::string dataStr,ByteSeq data,int id);

		int GetMaxIDRcv();

		//��ȡL3_Send��ǰ�������ID
		int GetMaxId();

		//���ĵ�ǰ���ͱ��
		void UpdateSendDataFlag(int id);
};
