//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 创建人：张晓荣
//** 类名称\文件名：MsgSetting.h
//** 类功能：电文的处理设定
//** 描述：
//** 创建日期：2016-9-21
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#pragma once
#include <string>
#include <vector>

using namespace std;

namespace CLTS
{
	namespace MSG
	{
		/** 字段比对方式
		 *   
		 */
		enum COMMAND
		{
			IS,
			LIKE,
			NOT
		};
		
		/** 字段处理要求
		 *   
		 */
		struct FieldSetting
		{
			string field;	 // 字段名
			COMMAND commd; // 命令
			string value;	// 字段值
		};
		typedef vector<FieldSetting> SeqFieldSetting;
		
		/** 电文处理要求
		 *   
		 */
		struct MsgSetting
		{
			string msgid;					// 电文号
			SeqFieldSetting fieldSettings;  // 字段处理要求（可以为空，不设定对字段的要求）
			string decoder;					// 电文的解析程序
			string handler;					// 电文解析后的处理程序
			
		};
		typedef vector<MsgSetting> SeqMsgSetting;


		// 以下为XcomPCS头部
		//XCOM-PCS头部
		typedef struct stru_text                                             
		{
				short textlenth;
				short lineno;
				char ctextno[12];     
				char textbuf[4080];                           //决定了电文的长度，最长为4080
		} XCOMPCS_DATA;

		//---------------
		//Header type=湛江33号协议
		//---------------
		typedef struct
		{
			char   TelLen[7];                     /* 电文长度 */
			char   TelID[6];                      /* 电文号 */
			char   SendDate[8];                   /* 电文发送日期 */
			char   SendTime[6];                   /* 电文发送时间 */
			char   SendUnit[2];                   /* 发送端描述码 */
			char   RecvUnit[2];                   /* 接收端描述码 */
			char   SendSeqNo[1];             	  /* 传送功能码, 表示电文的目的，大写字母‘D’表示发送数据。 */
		} HEADER_TYPE3_T;
	};
};