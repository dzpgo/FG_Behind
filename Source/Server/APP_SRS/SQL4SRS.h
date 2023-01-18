#pragma once
#ifndef _SQL4SRS_
#define _SQL4SRS_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"


namespace Monitor
{
	class SQL4SRS
	{
	public:
		SQL4SRS(void);
		~SQL4SRS(void);		

		//获取扫描处理号
		static bool SelScanNO4Mat(string& scanNO);

		//获取扫描处理号
		static bool SelScanNO4Car(string& scanNO);

		//获取激光模块通信回线号
		static bool SelComLineNO(string module, int& lineNO);

		//插入激光料堆扫描表
		static bool InsParkingSRSMatInfo(string scanNO, //扫描处理号
																	string areaType, //被扫区域类型
																	string areaNO, //被扫区域名称
																	long orderNO, //当前指令号
																	string scanMessageNO, //扫描事件号
																	string scanCraneNO, //扫描行车号
																	string scanType, //扫描类型 0-取料 1-放料
																	long startX, //扫描区域起始X
																	long endX, //扫描区域结束X
																	long startY, //扫描区域起始Y
																	long endY, //扫描区域结束Y
																	long actX, //行车当前X
																	long actY);//行车当前Y

		static bool InsParkingSRSMatInfo2(string scanNO, //扫描处理号
																		string areaType, //被扫区域类型
																		string areaNO, //被扫区域名称
																		long orderNO, //当前指令号
																		string scanMessageNO, //扫描事件号
																		string scanCraneNO, //扫描行车号
																		string scanType, //扫描类型 0-取料 1-放料
																		long carPointX1, //车辆框架X1
																		long carPointY1, //车辆框架X1
																		long carPointZ1, //车辆框架X1
																		long carPointX2, //车辆框架X1
																		long carPointY2, //车辆框架X1
																		long carPointZ2, //车辆框架X1
																		long carPointX3, //车辆框架X1
																		long carPointY3, //车辆框架X1
																		long carPointZ3, //车辆框架X1
																		long carPointX4, //车辆框架X1
																		long carPointY4, //车辆框架X1
																		long carPointZ4, //车辆框架X1	
																		long actX, //行车当前X
																		long actY);//行车当前Y

		//更新激光料堆扫描表,同时获取对应指令号orderNO
		static bool UpdParkingSRSMatInfo(string scanNO, 
																		string scanResult, 
																		long pointX, 
																		long pointY, 
																		long pointZ);

		//更新激光料堆扫描表,同时获取对应指令号orderNO
		static bool SelOrderNOByMatScanNO(string matScanNO, long& orderNO);

		//插入车辆激光扫描信息表
		static bool InsParkingSRSCarInfo(string scanNO, 
																	string treatmentNO, 
																	string parkingNO, 
																	string carNO, 
																	string carType, 
																	string matType, 
																	string loadFlag, 
																	string scanMode, 
																	long orderNO, 
																	string scanMessageNO, 
																	string scanCraneNO, 
																	long startPoint, 
																	long endPoint, 
																	long scanCount, 
																	string scanIP );

		//更新车辆激光扫描表，同时获取对应指令号
		static bool UpdParkingSRSCarInfo(string scanNO, 
																		string scanResult, 
																		long pointX1, 
																		long pointY1, 
																		long pointZ1, 
																		long pointX2, 
																		long pointY2, 
																		long pointZ2, 
																		long pointX3, 
																		long pointY3, 
																		long pointZ3, 
																		long pointX4, 
																		long pointY4, 
																		long pointZ4,
																		long pointXMax,
																		long pointXMin, 
																		long pointYMax,
																		long pointYMin,
																		long centerX,
																		long centerY
																		);

		//根据carscanNO获取指令号
		static bool SelOrderNOByCarScanNO(string carScanNO, long& orderNO);

		//获取卡车停车位上处理号、车号
		static bool SelParkingTreatmentNOCarNO(string parkingNO, string& parkingTreatmentNO, string& carNO);

		//获取RGV停车位上车号
		static bool SelRGVNO(string parkingNO, string& rgvNO);

		//更新UACS_PARKING_RGV_STATUS
		static bool UpdParkingRGVStatusSRS(string parkingNO, 
																			long pointXMin, 
																			long pointXMax, 
																			long pointYMin, 
																			long pointYMax);





	};
}

#endif

