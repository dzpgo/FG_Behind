//********************************************************************
//** Copyright (c) 2016 �������
//** �����ˣ�������
//** ������\�ļ�����MsgSetting.h
//** �๦�ܣ����ĵĴ����趨
//** ������
//** �������ڣ�2016-9-21
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#pragma once
#include <string>
#include <vector>

using namespace std;

namespace CLTS
{
	namespace MSG
	{
		/** �ֶαȶԷ�ʽ
		 *   
		 */
		enum COMMAND
		{
			IS,
			LIKE,
			NOT
		};
		
		/** �ֶδ���Ҫ��
		 *   
		 */
		struct FieldSetting
		{
			string field;	 // �ֶ���
			COMMAND commd; // ����
			string value;	// �ֶ�ֵ
		};
		typedef vector<FieldSetting> SeqFieldSetting;
		
		/** ���Ĵ���Ҫ��
		 *   
		 */
		struct MsgSetting
		{
			string msgid;					// ���ĺ�
			SeqFieldSetting fieldSettings;  // �ֶδ���Ҫ�󣨿���Ϊ�գ����趨���ֶε�Ҫ��
			string decoder;					// ���ĵĽ�������
			string handler;					// ���Ľ�����Ĵ������
			
		};
		typedef vector<MsgSetting> SeqMsgSetting;


		// ����ΪXcomPCSͷ��
		//XCOM-PCSͷ��
		typedef struct stru_text                                             
		{
				short textlenth;
				short lineno;
				char ctextno[12];     
				char textbuf[4080];                           //�����˵��ĵĳ��ȣ��Ϊ4080
		} XCOMPCS_DATA;

		//---------------
		//Header type=տ��33��Э��
		//---------------
		typedef struct
		{
			char   TelLen[7];                     /* ���ĳ��� */
			char   TelID[6];                      /* ���ĺ� */
			char   SendDate[8];                   /* ���ķ������� */
			char   SendTime[6];                   /* ���ķ���ʱ�� */
			char   SendUnit[2];                   /* ���Ͷ������� */
			char   RecvUnit[2];                   /* ���ն������� */
			char   SendSeqNo[1];             	  /* ���͹�����, ��ʾ���ĵ�Ŀ�ģ���д��ĸ��D����ʾ�������ݡ� */
		} HEADER_TYPE3_T;
	};
};