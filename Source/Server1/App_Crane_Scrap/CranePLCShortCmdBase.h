/*********************************************************************
 *		
 *  ��      ��:    CranePLCShortCmdBase.h   		
 *
 *
 *  ������
 *        ��CranePLCShortCmdBase �ǵ�����
 *        �������´��г��ĵ����̿���ָ��
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/
#pragma once
#ifndef _CranePLCShortCmdBase_
#define _CranePLCShortCmdBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{



		class CranePLCShortCmdBase
		{


		public:
				CranePLCShortCmdBase(void);

				~CranePLCShortCmdBase(void);

		private:
			    void initValues();
	
		//1 CRANE_NO 
		private:
			string craneNO;
		public:
			string getCraneNO();
			void   setCraneNO(string theVal);

		//2 cmdCode
		private:
			long cmdCode;
		public:
			long getCmdCode();
			void setCmdCode(long theVal);

		public:
			void  logOutValues();

	
		public:
			//--------------------------------------------------�´�PLCϵͳ�ĳ�ʼֵ�趨----------------------------------------------------------------
			//����ͣ��
			const static  long SHORT_CMD_NORMAL_STOP;
			//��ͣ
			 const static  long SHORT_CMD_EMG_STOP;
			 //��λ
			 const static  long SHORT_CMD_RESET;
			 //Ҫ�������Զ�
			 const static long  SHORT_CMD_ASK_COMPUTER_AUTO;
			 //Ҫ��ȡ��������Զ�
			 const static long SHORT_CMD_CANCEL_COMPUTER_AUTO;
			
			 //---------------------------------------------------------------------------------------------------------------------------------------------------


		};




}
#endif