/*********************************************************************
 *		
 *  文      件:    CranePLCStatusPhototAlbum.h   		
 *
 *
 *  概述：
 *        ：CranePLCStatusPhtotAlbum 非单例类
 *        ：储存行车PLC送来的完整状态信息的照片，一共两张，为新照片和老照片
 *  版本历史		
 *      2017年04月建立
*********************************************************************/
#pragma once
#ifndef _CranePLCStatusPhototAlbum_
#define _CranePLCStatusPhototAlbum_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "CranePLCStatusBase.h"

namespace Monitor
{



		class CranePLCStatusPhototAlbum
		{


		public:
				CranePLCStatusPhototAlbum(void);

				~CranePLCStatusPhototAlbum(void);

		private:
			//行车号
			string craneNO;
		public:
			string getCraneNO();
			void setCraneNO(string theVal);

		private:
			//老照片就绪标志位
			bool oldPhotoOK;
			//新照片就绪标志位
			bool newPhotoOK;
			//整个相册就绪标志位
			bool PhtotAlbumOK;
		public:
			//获得整个相册就绪标志位的方法
			bool getPhtotAlbumOK();

		private:
			//新照片
			CranePLCStatusBase cranePLCStatusNew;
			//老照片
			CranePLCStatusBase cranePLCStatusOld;

		public:
			//获得新照片的方法
			CranePLCStatusBase getCranePLCStatusNew();
			//获得老照片的方法
			CranePLCStatusBase getCranePLCStatusOld();

			//从外部接收新照片的入口
			//外部赋值两次后，相册就绪
			void inputPLCStatus(CranePLCStatusBase cranePLCStatusBase);



		};




}
#endif