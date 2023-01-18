/*********************************************************************
 *		
 *  ��      ��:    CraneMonitor.h   		
 *
 *
 *  ������
 *        ��CraneMonitor Ϊ�����࣬һ̨�г�һ������
 *        ������Map<�г��ţ��г���Ƭ>����������г���Ƭ�������ڸ�Map��
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/
#pragma once
#ifndef _CraneMonitor_
#define _CraneMonitor_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "CranePLCStatusPhototAlbum.h"

#include "CranePLCOrderBase.h"
#include "CranePLCShortCmdBase.h"
#include "CranePLCAlarmBase.h"

#include "MsgEUCR01.h"
#include "MsgEUCR02.h"
namespace Monitor
{



		class CraneMonitor
		{


		public:
				//��������
				CraneMonitor(void);
				//��������
				~CraneMonitor(void);

		private:
				//��������ָ��
				static CraneMonitor*	m_pCraneMonitor;

		public:
				//���ָ��ķ���
				static  CraneMonitor*  getInstance(void);

		private:
			//�г���
			string craneNO;
		public:
			string getCraneNO();
			void setCraneNO(string theVal);


		private:
			//���������г����ݵ���ᣬ����а����Լ�������������
			map<string,CranePLCStatusPhototAlbum> mapCranePLCStatusPhototAlbum;


		private:
			CranePLCAlarmBase cranePLCAlarm;


		//initialiseϵ��
		public:
			void initialise_MapCranePLCStatusPhototAlbum( vector<string> vectorCraneNOList);

		public:
			void inputPLCStatus(CranePLCStatusBase cranePLCStatusBase);

			//����Լ��г���PLC״̬
			bool getPLCStatus(CranePLCStatusBase& cranePLCStatusBase);

			//����ھ��г���PLC״̬
			bool getNeighborPLCStatus(string neightborCraneNO, CranePLCStatusBase& cranePLCStatusBase);

		public:
			void inputPLCAlamrs(CranePLCAlarmBase theCranePLCAlarm);

			bool getPLCAlamrs(CranePLCAlarmBase& theCranePLCAlarm);

		public:
			void DownLoadCranePLCOrder(CranePLCOrderBase  cranePLCOrderBase);

			void DownLoadCranePLCShortCmd(CranePLCShortCmdBase  cranePLCShortCmdBase);



		};




}
#endif