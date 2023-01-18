//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 创建人：陆永钰
//** 类名称\文件名：MsgEUKDW2.cpp
//** 类功能：材料清库电文
//** 描述：处理材料清库电文
//** 创建日期：2016-12-30
//** 修改人：
//** 修改日期：
//** 整理日期：
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

		//将当前发送详细插入L3_Send表
		void InsertSendData(std::string msgId,std::string dataStr,ByteSeq data,int id);

		void InsertRcvData(std::string msgId,std::string dataStr,ByteSeq data,int id);

		int GetMaxIDRcv();

		//获取L3_Send表当前最大主键ID
		int GetMaxId();

		//更改当前发送标记
		void UpdateSendDataFlag(int id);
};
