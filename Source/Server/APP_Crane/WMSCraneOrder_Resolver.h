#pragma  once
#ifndef   _WMSCRANEORDER_RESOLVER_
#define   _WMSCRANEORDER_RESOLVER_

#include <pace/SmartData.h>
#include <pace/SmartBuffer.h>
#include "DataAccess.h"
#include "CraneOrderCurrentBase.h"
#include "OrderCurrentBase.h"
#include "CranePLCStatusBase.h"
#include "OrderQueueBase.h"

#include "log4cplus/LOG.h"
#include "CranePLCOrderBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"



namespace Monitor
{

	class   WMSCraneOrder_Resolver
	{

	public:

		WMSCraneOrder_Resolver();

		~WMSCraneOrder_Resolver();


	public:
		const static long OUT_DIA_MAX_LIMIT_SAMLL_COIL;
		const static long X_MIN_CRANE_CAN_RUN_4000;
		const static long X_MAX_CRANE_CAN_RUN_428000;
		const static long Y_MIN_CRANE_CAN_RUN_3000;
		const static long Y_MAX_CRANE_CAN_RUN_30000;
	public:

		

       //计算行车指令数据  
       //static bool resolver_WMSCraneOrder(WMSCraneOrderBase wmsCraneOrder, CraneOrderCurrentBase & craneOrderCurrent);

	   static bool resolver_WMSCraneOrder(OrderQueueBase orderQueueData, OrderCurrentBase & orderCurrent);

		//2019.4.24 zhangyuhong add
		//通过写指令方式来回登车位
		static bool		resolver_BoardingCraneOrder(string craneNO, CranePLCStatusBase cranePLCStatusCurrent);

		 //20220621 zhangyuhong add
		 //获取废钢指令
		 static bool SelCraneOrder(string craneNO, OrderQueueBase& orderQueueData);

		 //获取物料matType 轻废 中废  重废
		 static bool SelMatType(string matCode, string compCode, string& matType);

		 //获取料格 卸料位（卸车时） 停车位（装车时） 中心点坐标  目前卸料位和停车位是共用的，同一时刻只允许一种业务作业
		 //只取 X Y 坐标  ，Z坐标不关心
		 static bool SelStockPosData(string orderType, string fromStockNO, string toStockNO, vector<long>& vecFromStockPos, vector<long>& vecToStockPos);	

		 //20221008 zhangyuhong add
		 //根据指令号获取时间上最近的车辆激光扫描号，一定是扫描成功的
		 static bool SelCarScanNO(long orderNO, string& carScanNO);
	
      

	};
}

#endif

