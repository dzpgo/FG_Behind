#pragma once
#ifndef _Adapter_UACS_YARDMAP_STOCK_INFO_
#define _Adapter_UACS_YARDMAP_STOCK_INFO_

#include "log4cplus/LOG.h"

#include "DataAccess.h"

namespace Monitor
{


	class Adapter_UACS_YARDMAP_STOCK_INFO
	{
	public:
		Adapter_UACS_YARDMAP_STOCK_INFO(void);

		~Adapter_UACS_YARDMAP_STOCK_INFO(void);

		//根据X,Y查找所在stockno
		static bool SelStockNOByXY(string bayNO, long x, long y, string& stockNO);

		//根据stockNO 在 卸料区 查找X_START  X_END  X_CENTER   Y_START Y_END Y_CENTER  结果放入map<long>
		static bool SelXYZValueFromDumpingInfo(string stockNO, map<string, long>& mapXYZValue);

		//根据stockNO 在 料格区 查找X_START  X_END  X_CENTER   Y_START Y_END Y_CENTER  结果放入map<long>
		static bool SelXYZValueFromGridInfo(string stockNO, map<string, long>& mapXYZValue);

		//根据料格号获取料格定义表中物料代码和钢制码
		static bool SelMatCompCodeFromGridInfo(string stockNO, string& matCode, string& compCode);

		//根据车辆扫描号获取车辆扫描中心点（计算的）
		static bool SelCarCenterXY(string carScanNO, long& centerX, long& centerY);

		//根据toStockNO获取停车位定义表中的停车位号  X_START X_END X_CENTER Y_START Y_END  Y_CENTER  扫描方向
		static bool SelParkingInfo(string pakringNO, 
														long& xStart, 
														long& xEnd, 
														long& xCenter, 
														long& yStart, 
														long& yEnd, 
														long& yCenter, 
														string& scanDir);


	};
}



#endif

