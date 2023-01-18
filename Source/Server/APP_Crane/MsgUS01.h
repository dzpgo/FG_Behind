/*********************************************************************
 *		
 *  ��      ��:    MsgUS01.h   		
 *
 *
 *  ������
 *        ��MsgUS01 Ϊ������
 *        ������һ���������г�����ָ���´ﵽ�г�PLC
 *		   ���������ݶ���μ� �г�PLC��UACSͨѶ�ӿ�
 *		   ���������ΪSendOutMessage  ���յĲ���Ϊ�������ݵ�һ���������г�����ָ�����
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/

#pragma once
#ifndef _MsgUS01_
#define _MsgUS01_

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
		class MsgUS01
		{
			public:
					MsgUS01();
					~MsgUS01(void);
			private:
					string msgId;

			private:
					static MsgUS01*	m_pMsgUS01;

			public:
					static  MsgUS01*  getInstance(void);

			public:

					bool SendOutMessage(vector <string> vecLineName , string craneNO);


			
		};
}

#endif
