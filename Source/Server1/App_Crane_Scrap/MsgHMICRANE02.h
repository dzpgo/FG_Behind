/*********************************************************************
 *		
 *  ��      ��:    MsgHMICRANE02.h   		
 *
 *
 *  ������
 *        ��MsgHMICRANE02 Ϊ������
 *        �������ɻ��淢�����г�����ָ��
 *		   ���������ݶ���μ� �г�PLC��UACSͨѶ�ӿ�
 *		   ���������ΪHandleMessage  ���յĲ���Ϊ�������ݵ�String
 *  �汾��ʷ		
 *      2017��04�½���
 *      �ڲ�����   ���ĺ�HMICRANE02
 *      ��������   ���г�ָ�������ͬ
*********************************************************************/

#pragma once
#ifndef _MsgHMICRANE02_
#define _MsgHMICRANE02_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "CranePLCOrderBase.h"

#include "CraneMonitor.h"



namespace Monitor
{
		class MsgHMICRANE02
		{
			public:
					MsgHMICRANE02();
					~MsgHMICRANE02(void);
		

			private:
					static MsgHMICRANE02*	m_pMsgHMICRANE02;

			public:
					static  MsgHMICRANE02*  getInstance(void);

			public:

					bool HandleMessage(string myCraneNO,string messageData);




		
		};
}

#endif
