/*********************************************************************
 *		
 *  ��      ��:    MsgUS04.h   		
 *
 *
 *  ������
 *        ��MsgUS04 Ϊ������
 *        ���г�����·���ϵİ�ȫ��֪ͨ����
 *		   ���������ݶ���μ� �г�PLC��UACSͨѶ�ӿ�
 *		   ���������ΪSendOutMessage  ���յĲ���Ϊ�������ݵ�һ���������г�����ָ�����
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/

#pragma once
#ifndef _MsgUS04_
#define _MsgUS04_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include <iXcomTCP2.h>

#include "DataAccess.h"


namespace Monitor
{
		class MsgUS04
		{
			public:
					MsgUS04();
					~MsgUS04(void);
			private:
					string msgId;

			private:
					static MsgUS04*	m_pMsgUS04;

			public:
					static  MsgUS04*  getInstance(void);

			public:

					bool SendOutMessage(vector <long> vecSafeDoorID );


			
		};
}

#endif
