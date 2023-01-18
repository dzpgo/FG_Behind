/*********************************************************************
 *		
 *  ��      ��:    MsgHMICRANE01.h   		
 *
 *
 *  ������
 *        ��MsgHMICRANE01 Ϊ������
 *        �������ɻ��淢���Ķ�ָ��
 *		   ���������ݶ���μ� �г�PLC��UACSͨѶ�ӿ�
 *		   ���������ΪHandleMessage  ���յĲ���Ϊ�������ݵ�String
 *  �汾��ʷ		
 *      2017��04�½���
 *      �ڲ�����   ���ĺ�HMICRANE01
 *      ��������   �г��ţ�������
*********************************************************************/

#pragma once
#ifndef _MsgHMICRANE01_
#define _MsgHMICRANE01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "CranePLCShortCmdBase.h"

#include "CraneMonitor.h"


namespace Monitor
{
		class MsgHMICRANE01
		{
			public:
					MsgHMICRANE01();
					~MsgHMICRANE01(void);
		

			private:
					static MsgHMICRANE01*	m_pMsgHMICRANE01;

			public:
					static  MsgHMICRANE01*  getInstance(void);

			public:

					bool HandleMessage(string myCraneNO,string messageData);




		
		};
}

#endif
