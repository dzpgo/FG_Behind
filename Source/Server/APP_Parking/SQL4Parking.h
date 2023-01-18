#pragma once
#ifndef _SQL4Parking_
#define _SQL4Parking_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "CarPlanBandInfo.h"
#include "EventGateHandler.h"


namespace Monitor
{
	class SQL4Parking
	{
	public:
		SQL4Parking(void);
		~SQL4Parking(void);		

		//查询车辆计划绑定信息
		static bool SelCarPlanBandInfo(string carNO, CarPlanBandInfo& carPlanBandInfoBase);

		//根据车牌号查询车辆计划绑定表中ENTER_FLAG=2的记录，如果有，返回true
		static bool CarEnterYardExist(string carNO);

		//查询L3计划中自带的废钢代码和要求重量(如果是卸料，reqWgt无意义)
		static bool SelScrapCodeReqWgtFormL3(string planNO, 
																					string workType, //L3是卸料XL还是装车ZC
																					string& locCode, //L3给出的料格号
																					string& scrapCode, //物料代码
																					string& compCode, //钢制代码  物料+钢制 唯一确定一个物料
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

		//根据所给料格号获取对应的跨号和道闸号
		static bool SelBayNOGateNOByGridNO(string gridNO, string& bayNO, string& gateNO);

		//更新车辆计划绑定表中的目的料格号 道闸号 根据车号、计划号
		static bool InitGateGridParking(string carNO, string planNO);

		//更新车辆计划绑定表中的目的料格号 道闸号 根据车号、计划号、子计划号
		static bool UpdGridGateByCarNOPlanNOPlanDetailID(string carNO, 
																										string planNO, 
																										long planDetailID, 
																										string targetGridNO, 
																										string gateNO, 
																										string targetParkingNO);

		//获取跨内物料是否满足scrapCode要求量的料格号,按照库存量从大到小排列
		static bool SelGridNOMatchScrapCode(string bayNO, string scrapCode, long reqWgt, string scrapType, string& maxStockGridNO);
		//只获取唯一个满足需求量的料格号，按照库存量从大到小排列获取到的料格号
		//还需要判断料格对应的停车位是否空闲
		//falseReson 1:  无空闲停车位  2：库存不足
		static bool SelGridNOMatchScrapCode2(string bayNO, 
																					string scrapCode, 
																					long reqWgt, 
																					string scrapType, 
																					string& targetGridNO, 
																					string& parkingNO, 
																					long& falseReason);

		//根据道闸号获取所在跨号
		static bool SelBayNOByGateNO(string gateNO, string& bayNO);

		//根据车号道闸号获取没有进入库区的记录
		static bool SelTargetGridNO(string carNO, 
															string gateNO, 
															string& carType, 
															string& targetGridNO, 
															string& targetParkingNO, 
															string& workType,
															string& planNO, 
															string& planSrc, 
															long& planDetailID);

		//更新进入标志=2
		static bool UpdEnterFlag2Enter(string carNO, string gateNO);

		//根据车号和进入标记获取目的停车位号
		static bool SelParkingNOByCarNOFlag(string carNO, 
																			string enterFlag, 
																			string& parkingNO, 
																			string& workType, 
																			string& carType,
																			string& planSrc, 
																			string& planNO, 
																			long& planDetailID);

		//根据停车位号获取停车位状态
		static bool SelStatusByParkingNO(string parkingNO, string& workStatus, string& workType, string& carNO);

		//根据停车位号获取对应车号
		static bool SelCarNOByParkingNO(string parkingNO, string& carNO);

		//更新停车位状态表
		static bool UpdParkingStatus(string parkingNO, string workStatus);

		//获取料格对应物料代码和钢制码
		static bool SelGridInfoByGridNO(string gridNO, string& matCode, string& compCode, long& matWgt);

		//根据料格号获取对应停车位状态
		static bool SelPKStatusByGridNO(string gridNO, string& parkingNO, string& workStatus);

		//更新车辆计划绑定表中 道闸号 ,目的料格号,目的停车位号
		static bool UpdGateGridPKByCarPlan(string carNO, string planNO, string gateNO, string gridNO, string parkingNO);

		//获取停车位处理号(数据库序列方式获取,从100000开始,处理号为 ZC+序列号  或者  XL+序列号)
		static bool SelParkingTM(long& parkingTM);

		//更新停车位状态表
		static bool UpdParkingWorkStautsInfo(string parkingNO, 
																				string treatmentNO, 
																				string workStatus, 
																				string workType, 
																				string carNO,
																				string carType );

		//插入装车卸车物料信息表（履历表） UACS_PARKING_MAT_INFO 
		//处理号，停车位号，车号，计划来源，计划号，子计划号，物料代码，钢制码，作业类型，是否完成=1（未完成）
		static bool InsParkingMatInfo(string treatmentNO, 
																string parkingNO, 
																string carNO, 
																string planSrc, 
																string planNO, 
																long planDetailID, 
																string matCode, 
																string compCode, 
																string workType, 
																string fromPlace, 
																string toPlace, 
																string finishFlag);

		//根据停车位号获取停车位状态表中的所有数据
		static bool SelAllFromParkingWorkStatus(string parkingNO, 
																					string& treatmentNO, 
																					string& workStauts, 
																					string& workType, 
																					string& carNO, 
																					string& carType );

		//初始化停车位状态
		static bool InitParkingWorkStauts(string parkingNO);

		//根据车号,进入标志=2,作业类型=ZC条件  删除车辆信息绑定表
		static bool DelCarPlanInfoByCarNO(string carNO, string carType, string workType);

		//更新UACS_PARKING_MAT_INFO履历表  FINISH_FLAG=2
		static bool UpdParkingMatInfoFinish(string treatmentNO);

		//更新停车位状态
		static bool UpdParkingStatusByValue(string pakringNO, string workStatus);

		//根据车号，进入标志=2 作业类型=XL，更新车辆信息绑定表中的进入标志=3 卸料离开  
		static bool UpdEnterFlag2XLLeave(string carNO, 
																		string carType, 
																		string workType, 
																		string lastEnterFlag, 
																		string nowEnterFlag);

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
																		long pointZ, 
																		long& orderNO);

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
																	string scanIP, 
																	string scanRGVFlag);

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
																	  long pointX, 
																	  long pointY, 
																	  long pointZ, 
																	  long& orderNO, 
																	  string& scanRGVFlag, 
																	  string& parkingNO);

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

