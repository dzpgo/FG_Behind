/*********************************************************************
 *		
 *  文      件:    CraneMonitor.h   		
 *
 *
 *  概述：
 *        ：CraneMonitor 为单例类，一台行车一个对象
 *        ：包含Map<行车号，行车照片>对象，整跨的行车照片都储存在该Map中
 *  版本历史		
 *      2017年04月建立
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
				//构造行数
				CraneMonitor(void);
				//析构函数
				~CraneMonitor(void);

		private:
				//单例函数指针
				static CraneMonitor*	m_pCraneMonitor;

		public:
				//获得指针的方法
				static  CraneMonitor*  getInstance(void);

		private:
			//行车号
			string craneNO;
		public:
			string getCraneNO();
			void setCraneNO(string theVal);


		private:
			//保存整跨行车数据的相册，相册中包括自己，包括其他车
			map<string,CranePLCStatusPhototAlbum> mapCranePLCStatusPhototAlbum;


		private:
			CranePLCAlarmBase cranePLCAlarm;


		//initialise系列
		public:
			void initialise_MapCranePLCStatusPhototAlbum( vector<string> vectorCraneNOList);

		public:
			void inputPLCStatus(CranePLCStatusBase cranePLCStatusBase);

			//获得自己行车的PLC状态
			bool getPLCStatus(CranePLCStatusBase& cranePLCStatusBase);

			//获得邻居行车的PLC状态
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