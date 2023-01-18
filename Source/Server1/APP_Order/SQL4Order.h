#pragma once
#ifndef _SQL4Order_
#define _SQL4Order_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "CarPlanBandInfo.h"
#include "EventParkingHandler.h"

using namespace Monitor;

namespace Monitor
{

	//针对eaf计划设计的取料map类型 map<序号, vectro<料格号, 物料代码, 取料量>>
	typedef map< long, vector<string> > MapGridMatWgtEAF;


	class SQL4Order
	{
	public:
		SQL4Order(void);
		~SQL4Order(void);

		//查询命令组号 通过DB2序列sequence
		static bool SelOrderGroupNO(long& orderGroupNO);

		static bool SelOrderNO(long& orderNO);

		//查询指令类型定义的优先级
		static bool SelOrderPriority(string orderType, long& orderPriority);


		//查询车辆计划绑定信息
		static bool SelCarPlanBandInfo(string carNO, string workType, CarPlanBandInfo& carPlanBandInfoBase);

		//根据车牌号查询车辆计划绑定表中ENTER_FLAG=2的记录，如果有，返回true
		static bool CarEnterYardExist(string carNO);

		//根据车牌号查询车辆计划绑定表中ORDER_FLAG=2的记录，如果有，返回true
		static bool CarOrderFlagExist(string carNO, string workType);

		//查询L3计划中自带的废钢代码和要求重量(如果是卸料，reqWgt无意义)
		static bool SelScrapCodeReqWgtFormL3(string planNO, 
																					string workType, //L3是卸料XL还是装车ZC
																					string& locCode, //L3给出的料格号
																					string& scrapCode, 
																					string& compCode, 
																					long& reqWgt);

		//查询电炉L2计划中自带的废钢代码和要求重量
		static bool SelScrapCodeReqWgtFromEAF(string planNO, 
																						long planDetailID, 
																						string& scrapCode, 
																						long& reqWgt);

		//查询转炉L2计划中自带的废钢代码和要求重量
		static bool SelScrapCodeReqWgtFromBOF(string planNO, 
																						long planDetailID, 
																						string& scrapCode, 
																						long& reqWgt);

		//根据停车位号获取所在跨号
		static bool SelBayNOByParkingNO(string parkingNO, string& bayNO);

		//根据料格号获取对应物料存量
		static bool SelMatStockInfoByGridNO(string gridNO, string&matCode, string& compCode, long& stockWgt);

		//获取停车位所在跨号，X中心点坐标
		static bool SelBayXCenterByParkingNO(string parkingNO, string& bayNO, long& xCenter);

		//根据电炉废钢代码对应的wms物料代码，电炉废钢要求重量，获取wms中满足条件的料格号，物料代码   原则：按照大车坐标离装车位从近到远进行选择
		static bool SelMapGMWEAFData(string scrapCode, 
																	long reqWgt, 
																	string bayNO, 
																	long xCenterParking,  
																	MapGridMatWgtEAF& mapGridMatWgtEAFBase );

		//将orderdatabase数据插入表
		static bool InsOrderDataBase(OrderDataBase matOrderDataBase);
		//将orderqueue数据插入表
		static bool InsOrderQueueBase(OrderQueueBase matOrderQueueBase);

		//查询L3计划中的qcflag
		static bool SelQCFlag(string planNO, string& qcFlag);

		//获取指令号
		static bool SelOrderNO();

		//获取废钢对应的吊运方式 1:抓斗  2：吸盘  3：均可
		static bool SelLiftMode(string matCode, string compCode, string& liftMode);

		//根据跨别 吊运方式 获取对应行车号
		static bool SelCraneNOEAFBayByLfitMode(string bayNO, string liftMode, string& craneNO);

		//获取跨长
		static long SelBayLength(string bayNO);
		//获取跨内行车数量
		static long SelCraneNumInBay(string bayNO);
		//获取料格中心点坐标
		static long SelGridXCenter(string gridNO);

		//根据跨号 seqNO 获取行车号
		static bool SelCraneNOByBaySeq(string bayNO, long seqNO, string& craneNO);

		//==================================================================
		//行车通知相关
		//==================================================================
		static bool UpdOrderQueueCmdStatus(long orderNO, long cmdSeq, string cmdStauts, long curWgt);

		static bool UpdOrderDataStatus(long orderNO, string stauts);

		static bool UpdOrderQueueWgt(long orderNO, long curWgt);

		static bool UpdOrderDataWgt(long orderNO, long curWgt);

		static bool SelOrderQueueWgt(long orderNO, long& reqWgt,  long& actWgt);

		static bool SelOrderQueueInfo(long orderNO, OrderQueueBase& orderQueueInfo);

		static bool DelOrderQueue(long orderNO);

		static bool UpdYardMapMatWgt(string gridNO, long matWgt, string calChar);//calChar:运算符  + -

		static bool DelParkingCarBandInfo(string planNO);


	};
}

#endif

