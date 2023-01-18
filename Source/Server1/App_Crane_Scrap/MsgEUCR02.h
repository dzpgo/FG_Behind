/*********************************************************************
 *		
 *  ��      ��:    MsgEUCR02.h   		
 *
 *
 *  ������
 *        ��MsgEUCR02 Ϊ������
 *        ������һ���������г��������´ﵽ�г�PLC���г���������� ģʽ�л���ͣ������ͣ����λ��
 *		   ���������ݶ���μ� �г�PLC��UACSͨѶ�ӿ�
 *		   ���������ΪSendOutMessage  ���յĲ���Ϊ�������ݵ�һ���г����������
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/

#pragma once
#ifndef _MsgEUCR02_
#define _MsgEUCR02_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include <iXcomTCP2.h>

#include "DataAccess.h"

#include "CranePLCShortCmdBase.h"

namespace Monitor
{
		class MsgEUCR02
		{
			public:
					MsgEUCR02();
					~MsgEUCR02(void);
			private:
					string msgId;

			private:
					static MsgEUCR02*	m_pMsgEUCR02;

			public:
					static  MsgEUCR02*  getInstance(void);

			public:

					bool SendOutMessage(CranePLCShortCmdBase cranePLCShortCmdBase);


			
		};
}

#endif
