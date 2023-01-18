/*********************************************************************
 *		
 *  ��      ��:    MsgUS02.h   		
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
#ifndef _MsgUS02_
#define _MsgUS02_

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
		class MsgUS02
		{
			public:
					MsgUS02();
					~MsgUS02(void);
			private:
					string msgId;

			private:
					static MsgUS02*	m_pMsgUS02;

			public:
					static  MsgUS02*  getInstance(void);

			public:

					bool SendOutMessage(vector <string> vecLineName , string craneNO, string itemValue);


			
		};
}

#endif
