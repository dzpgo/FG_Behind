#include "EventParkingHandler.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"


using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

const  string EventParkingHandler::EXTER_SYSTEM_BOF = "LG";//
const  string EventParkingHandler::EXTER_SYSTEM_EAF = "DL";//

const	long EventParkingHandler::MPE_WGT = 100;//单位 kg

EventParkingHandler::EventParkingHandler(void)
{
	
}

EventParkingHandler::~EventParkingHandler(void)
{

}

void EventParkingHandler::OrderCreateReqForL3EAFL2(string strValue, string logFileName)
{
	LOG log("EventParkingHandler::OrderCreateReq",logFileName);
	try
	{
		log.Info()<<"OrderCreateReq  start........."<<endl;

		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 4)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string workType = kValues[0];//作业类型
		string carType = kValues[1];//车类型
		string carNO = kValues[2];//车号
		string parkingNO = kValues[3];//停车位号 （装车就是放料位  卸料就是取料位）
		log.Info()<<"workType = "<<workType<<" , carType = "<<carType<<" , carNO = "<<carNO<<" , parkingNO = "<<parkingNO<<endl;

		//2.如果有车辆已经生成了指令，报警退出
		if (true == SQL4Order::CarOrderFlagExist(carNO, workType))
		{
			log.Info()<<"carNO = "<<carNO<<" has  ORDER   and  not finish yet,  return.................."<<endl;
			return;
		}

		//3.如果没有对应计划,报警退出
		CarPlanBandInfo carPlanBandInfoBase;
		if (false == SQL4Order::SelCarPlanBandInfo(carNO, workType, carPlanBandInfoBase))
		{
			log.Info()<<"carNO = "<<carNO<<" has  NO PLAN,  return.................."<<endl;
			return;
		}
		//打印获取到的车辆绑定信息
		carPlanBandInfoBase.logOutValues();

		//4.根据计划来源进入不同的指令生成逻辑
		OrderDataBase  matOrderDataBase;//for L3 电炉计划
		//L3计划
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_L3)
		{
			if (false == OrderCreateL3(carPlanBandInfoBase, parkingNO, matOrderDataBase))
			{
				log.Info()<<"OrderCreateL3  failed!  return............................."<<endl;
				return;
			}
		}
		//EAF计划
		else if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_EAF)
		{
			//if (false == OrderCreateEAFMap(carPlanBandInfoBase, parkingNO, mapOrderData))
			if (false == OrderCreateEAF(carPlanBandInfoBase, parkingNO, matOrderDataBase))
			{
				log.Info()<<"OrderCreateEAF  failed!  return............................."<<endl;
				return;
			}
		}
		//BOF计划
		else if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_BOF)
		{
			//对转炉装车,按照顺序将多种物料装车或RGV，因此1组指令的map里有多条指令
		}

		//5. 插入OrderData表数据 和 OrderQueue数据
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_L3 || carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_EAF)
		{
			SQL4Order::InsOrderDataBase(matOrderDataBase);
			OrderQueueBase matOrderQueue;
			GetOrderQueue(matOrderDataBase, matOrderQueue);
			SQL4Order::InsOrderQueueBase(matOrderQueue);
		}
		else if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_BOF)
		{
		}





		










	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
}


bool EventParkingHandler::OrderCreateL3(CarPlanBandInfo carPlanBandInfoBase, string parkingNO, OrderDataBase& orderDataBaseL3)
{
	string functionName = "EventParkingHandler::OrderCreateL3";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		log.Info()<<"OrderCreateL3 start.............................................................................................."<<endl;
		//OrderDataBase orderDataBaseL3;
		
		//1. 获取指令组号
		long orderGroupNO = 0;
		if (false == SQL4Order::SelOrderGroupNO(orderGroupNO))
		{
			log.Info()<<"1. orderGroupNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseL3.setOrderGroupNO(orderGroupNO);
		log.Info()<<"1. OrderGroupNO  set Success........................... "<<endl;

		//2.获取指令组内执行顺序号：对于卸料而言 目前设定只有1条指令  所谓区分指令是否为1条还是多条，不是仅根据吊运对象来确定，还要根据起始位和目标位是否有变化而定
		//L3的装车或卸料指令  废钢L2的装车指令   因为都是卡车装车，只能停到指定料格位，由一个料格吊运出料或入料，所以只有一条指令，但这个指令可能被执行多次，因为一次不一定能完成指定重量的吊运 
		//炼钢L2的装车指令，可能会有一个物料对应多个料格吊运的情况出现，所以会有多条指令  
		orderDataBaseL3.setExeSeq(1);
		log.Info()<<"2. ExeSeq  set Success........................... "<<endl;

		//3.设定指令类型
		string orderType = GetOrderType(carPlanBandInfoBase.getPlanSrc(), carPlanBandInfoBase.getWorkType());
		orderDataBaseL3.setOrderType(orderType);
		log.Info()<<"3. OrderType  set Success........................... "<<endl;

		//4.设定指令优先级
		long orderPriority = 0;
		if (false == SQL4Order::SelOrderPriority(orderDataBaseL3.getOrderType(), orderPriority) )
		{
			log.Info()<<"4. orderPriority  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseL3.setOrderPriority(orderPriority);
		log.Info()<<"4. OrderPriority  set Success........................... "<<endl;

		//5.设定指令状态
		orderDataBaseL3.setOrderStatus(OrderDataBase::ORDER_STATUS_NOT_START_1);
		log.Info()<<"5. OrderStatus  set Success........................... "<<endl;

		//6.设定指令删除标志
		orderDataBaseL3.setOrderDelFlag(OrderDataBase::ORDER_DEL_FLAG_NOT_DEL_1);
		log.Info()<<"6. OrderDelFlag  set Success........................... "<<endl;

		//7.设定对应计划来源
		orderDataBaseL3.setPlanSrc(carPlanBandInfoBase.getPlanSrc());
		log.Info()<<"7. PlanSrc  set Success........................... "<<endl;

		//8.设定计划号
		orderDataBaseL3.setPlanNO(carPlanBandInfoBase.getPlanNO());
		log.Info()<<"8. PlanNO  set Success........................... "<<endl;

		//9.设定对应计划子ID
		orderDataBaseL3.setPlanDetailID(carPlanBandInfoBase.getPlanDetailID());
		log.Info()<<"9. PlanDetailID  set Success........................... "<<endl;

		//10.设定外部系统废钢代码
		string locCode = "";
		string scrapCode = "";
		string compCode = "";
		long reqWgt = DF_INT_NULL;
		if ( false == GetScrapCodeReqWgt(carPlanBandInfoBase, locCode, scrapCode, compCode, reqWgt))
		{
			log.Info()<<"10. scrapCode  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseL3.setScrapCode(scrapCode);
		log.Info()<<"10. ScrapCode  set Success........................... "<<endl;		

		//11.设定外部系统废钢要求重量
		orderDataBaseL3.setReqWeight(reqWgt);
		log.Info()<<"11. ReqWgt  set Success........................... "<<endl;

		//12. 设定车号（装车车号/卸料车号/RGV车号）
		orderDataBaseL3.setCarNO(carPlanBandInfoBase.getCarNO());
		log.Info()<<"12. CarNO  set Success........................... "<<endl;

		//13.设定车辆类型
		orderDataBaseL3.setCarType(carPlanBandInfoBase.getCarType());
		log.Info()<<"13. CarType  set Success........................... "<<endl;

		//14.设定跨号
		//根据parkingNO获取对应跨号BayNO
		string bayNO = DF_STR_NULL;
		if (false == SQL4Order::SelBayNOByParkingNO(parkingNO, bayNO))
		{
			log.Info()<<"14. bayNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseL3.setBayNO(bayNO);
		log.Info()<<"14. BayNO  set Success........................... "<<endl;

		//15.设定WMS系统物料代码
		//L3计划中，scrapCode就是matCode,无需再转换
		//如果L3所给料格代码与WMS系统中料格代码中的物料代码不匹配，报警返回
		string matCode = DF_STR_NULL;
		string wmsCompCode = DF_STR_NULL;
		long stockWgt = DF_INT_NULL;
		if (false == SQL4Order::SelMatStockInfoByGridNO(locCode, matCode, wmsCompCode, stockWgt))
		{
			log.Info()<<"15. matCode  get failed: NO locCode IN WMS system.........return.................. "<<endl;
			return ret;
		}
		if (matCode != scrapCode || wmsCompCode != compCode)
		{
			log.Info()<<"15. matCode  get failed: L3 give  scrapCode/compCode  is not SAME to matCode/wmsCompCode  in WMS system...........return................ "<<endl;
			return ret;
		}		
		orderDataBaseL3.setMatCode(matCode);
		log.Info()<<"15. MatCode  set Success........................... "<<endl;

		//16. 设定compCode
		orderDataBaseL3.setCompCode(compCode);
		log.Info()<<"16. CompCode  set Success........................... "<<endl;

		//17.设定理论作业重量,只有在装车时有值  如果是卸料,值为0
		//如果是装车，L3指定的料格内物料存量不够,报警返回
		long calWgt = 0;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			if (stockWgt < reqWgt && abs(stockWgt - reqWgt) > EventParkingHandler::MPE_WGT)
			{
				log.Info()<<"17. calWgt  get failed:  ZC, L3 give  reqWgt   <  stockWgt  in WMS system...........return................ "<<endl;
				return ret;
			}
			calWgt = reqWgt;
		}
		orderDataBaseL3.setCalWeight(calWgt);
		log.Info()<<"17. CalWgt  set Success........................... "<<endl;

		//18.设定实际作业量
		//指令生成阶段，统一设定为0
		long actWgt = 0;
		orderDataBaseL3.setActWeight(actWgt);
		log.Info()<<"18. ActWgt  set Success........................... "<<endl;

		//19.设定取料位
		string fromStockNO = DF_STR_NULL;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//对于卸料，取料位就是停车位
			fromStockNO = parkingNO;
		}
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//对于装车,取料位就是料格号
			fromStockNO = locCode;
		}
		orderDataBaseL3.setFromStockNO(fromStockNO);
		log.Info()<<"19. FromStockNO  set Success........................... "<<endl;

		//20.设定放料位
		string toStockNO = DF_STR_NULL;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//对于卸料，放料位就是料格
			toStockNO = locCode;
		}
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//对于装车,放料位就是停车位
			toStockNO = parkingNO;
		}
		orderDataBaseL3.setToStockNO(toStockNO);
		log.Info()<<"20. ToStockNO  set Success........................... "<<endl;

		//21.落关位位置内顺序 对L3计划无意义 设置为0
		long downPosSeq = 0;
		orderDataBaseL3.setDownPosSeq(downPosSeq);
		log.Info()<<"21. DownPosSeq  set Success........................... "<<endl;

		//22. 是否需要卸料质检
		string qcFlag = "";
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			SQL4Order::SelQCFlag(orderDataBaseL3.getPlanNO(), qcFlag);
		}
		orderDataBaseL3.setQCFlag(qcFlag);
		log.Info()<<"22. QCFlag  set Success........................... "<<endl;

		//mapOrderData.insert(MapOrderDataBase::value_type(1,orderDataBaseL3));
		//最后生成指令号
		long orderNO = 0;
		if (false == SQL4Order::SelOrderNO(orderNO))
		{
			log.Info()<<"orderNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseL3.setOrderNO(orderNO);
		log.Info()<<" orderNO  set Success........................... "<<endl;

		log.Info()<<"......................................................Current L3 Order Info: orderNO = "<<orderNO<<"  ................................................................... "<<endl;

		ret = true;
		return ret;

	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return ret;
}


bool EventParkingHandler::OrderCreateEAFMap(CarPlanBandInfo carPlanBandInfoBase, string parkingNO, MapOrderDataBase& mapOrderData)
{
	string functionName = "EventParkingHandler::OrderCreateEAF";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		log.Info()<<"OrderCreateEAF start.............................................................................................."<<endl;
		//1.根据电炉给定的废钢代码获取wms系统中满足对应物料代码条件的料格信息
		//2.根据电炉的装料重量要求,组织MapGridMatWgtEAF
		//3.根据MapGridMatWgtEAF内容，组织MapOrderDataBase
		
		//获取此次电炉废钢料装料数据MapGridMatWgtEAF
		MapGridMatWgtEAF mapGridMatWgtEafBase;
		string locCode = "";
		string scrapCode = "";
		string compCode = "";
		long reqWgt = DF_INT_NULL;
		if ( false == GetScrapCodeReqWgt(carPlanBandInfoBase, locCode, scrapCode, compCode, reqWgt))
		{
			log.Info()<<"GetScrapCodeReqWgt  failed.........return "<<endl;
			return ret;
		}
		string bayNO = "";
		long xCenterParking = DF_INT_NULL;
		if (false == SQL4Order::SelBayXCenterByParkingNO(parkingNO, bayNO, xCenterParking))
		{
			log.Info()<<"SelBayXCenterByParkingNO  failed.........return "<<endl;
			return ret;
		}

		if ( false == SQL4Order::SelMapGMWEAFData(scrapCode, reqWgt, bayNO, xCenterParking, mapGridMatWgtEafBase) )
		{
			log.Info()<<"SelMapGMWEAFData  failed.........return "<<endl;
			return ret;
		}
		
		//开始组织指令数据
		log.Info()<<"OrderCreateEAF  REAL DATA start................................................................ "<<endl;

		//同一组指令,指令组号用唯一的
		long orderGroupNO = 0;
		if (false == SQL4Order::SelOrderGroupNO(orderGroupNO))
		{
			log.Info()<<"orderGroupNO  get failed.........return "<<endl;
			return ret;
		}
		MapGridMatWgtEAF::iterator itor;
		for (itor = mapGridMatWgtEafBase.begin(); itor != mapGridMatWgtEafBase.end(); itor++)
		{
			//组内执行顺序号
			long exeSeq = itor->first;
			vector<string> vec = itor->second;
			string gridNO = vec[0];
			string matCode = vec[1];
			long calWgt = StringHelper::ToNumber<long>(vec[2]);
			
			OrderDataBase orderDataBaseEAF;
			if (false == MakeSingleOrderEAF(carPlanBandInfoBase, 
																		orderGroupNO, 
																		parkingNO, 
																		exeSeq, 
																		gridNO, 
																		matCode, 
																		calWgt , 
																		orderDataBaseEAF))
			{
				log.Info()<<"MakeSingleOrderEAF failed.........return................ "<<endl;
				return ret;
			}

			mapOrderData.insert(MapOrderDataBase::value_type(exeSeq, orderDataBaseEAF));

		}
		ret = true;
		return ret;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return ret;
}


bool EventParkingHandler::OrderCreateEAF(CarPlanBandInfo carPlanBandInfoBase, string parkingNO, OrderDataBase& orderDataBaseEAF)
{
	string functionName = "EventParkingHandler::OrderCreateEAF";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		log.Info()<<"OrderCreateEAF start.............................................................................................."<<endl;

		//1. 获取指令组号
		long orderGroupNO = 0;
		if (false == SQL4Order::SelOrderGroupNO(orderGroupNO))
		{
			log.Info()<<"1. orderGroupNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setOrderGroupNO(orderGroupNO);
		log.Info()<<"1. OrderGroupNO  set Success........................... "<<endl;

		//2.获取指令组内执行顺序号：对于卸料而言 目前设定只有1条指令  所谓区分指令是否为1条还是多条，不是仅根据吊运对象来确定，还要根据起始位和目标位是否有变化而定
		//L3的装车或卸料指令  废钢L2的装车指令   因为都是卡车装车，只能停到指定料格位，由一个料格吊运出料或入料，所以只有一条指令，但这个指令可能被执行多次，因为一次不一定能完成指定重量的吊运 
		//炼钢L2的装车指令，可能会有一个物料对应多个料格吊运的情况出现，所以会有多条指令  
		orderDataBaseEAF.setExeSeq(1);
		log.Info()<<"2. ExeSeq  set Success........................... "<<endl;

		//3.设定指令类型
		string orderType = GetOrderType(carPlanBandInfoBase.getPlanSrc(), carPlanBandInfoBase.getWorkType());
		orderDataBaseEAF.setOrderType(orderType);
		log.Info()<<"3. OrderType  set Success........................... "<<endl;

		//4.设定指令优先级
		long orderPriority = 0;
		if (false == SQL4Order::SelOrderPriority(orderDataBaseEAF.getOrderType(), orderPriority) )
		{
			log.Info()<<"4. orderPriority  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setOrderPriority(orderPriority);
		log.Info()<<"4. OrderPriority  set Success........................... "<<endl;

		//5.设定指令状态
		orderDataBaseEAF.setOrderStatus(OrderDataBase::ORDER_STATUS_NOT_START_1);
		log.Info()<<"5. OrderStatus  set Success........................... "<<endl;

		//6.设定指令删除标志
		orderDataBaseEAF.setOrderDelFlag(OrderDataBase::ORDER_DEL_FLAG_NOT_DEL_1);
		log.Info()<<"6. OrderDelFlag  set Success........................... "<<endl;

		//7.设定对应计划来源
		orderDataBaseEAF.setPlanSrc(carPlanBandInfoBase.getPlanSrc());
		log.Info()<<"7. PlanSrc  set Success........................... "<<endl;

		//8.设定计划号
		orderDataBaseEAF.setPlanNO(carPlanBandInfoBase.getPlanNO());
		log.Info()<<"8. PlanNO  set Success........................... "<<endl;

		//9.设定对应计划子ID
		orderDataBaseEAF.setPlanDetailID(carPlanBandInfoBase.getPlanDetailID());
		log.Info()<<"9. PlanDetailID  set Success........................... "<<endl;

		//10.设定外部系统废钢代码
		string locCode = "";
		string scrapCode = "";
		string compCode = "";
		long reqWgt = DF_INT_NULL;
		if ( false == GetScrapCodeReqWgt(carPlanBandInfoBase, locCode, scrapCode, compCode, reqWgt))
		{
			log.Info()<<"10. scrapCode  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setScrapCode(scrapCode);
		log.Info()<<"10. ScrapCode  set Success........................... "<<endl;		

		//11.设定外部系统废钢要求重量
		orderDataBaseEAF.setReqWeight(reqWgt);
		log.Info()<<"11. ReqWgt  set Success........................... "<<endl;

		//12. 设定车号（装车车号/卸料车号/RGV车号）
		orderDataBaseEAF.setCarNO(carPlanBandInfoBase.getCarNO());
		log.Info()<<"12. CarNO  set Success........................... "<<endl;

		//13.设定车辆类型
		orderDataBaseEAF.setCarType(carPlanBandInfoBase.getCarType());
		log.Info()<<"13. CarType  set Success........................... "<<endl;

		//14.设定跨号
		//根据parkingNO获取对应跨号BayNO
		string bayNO = DF_STR_NULL;
		if (false == SQL4Order::SelBayNOByParkingNO(parkingNO, bayNO))
		{
			log.Info()<<"14. bayNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setBayNO(bayNO);
		log.Info()<<"14. BayNO  set Success........................... "<<endl;

		//15.设定WMS系统物料代码
		//废钢L2计划中，scrapCode就是电炉系统废钢代码, 需要转换成WMS废钢代码  
		//料格号已经确定，可以通过车辆计划绑定信息表中的targetGridNO获取WMS废钢代码和钢制码
		string matCode = DF_STR_NULL;
		string wmsCompCode = DF_STR_NULL;
		long stockWgt = DF_INT_NULL;
		if (false == SQL4Order::SelMatStockInfoByGridNO(carPlanBandInfoBase.getTargetGridNO(), matCode, wmsCompCode, stockWgt))
		{
			log.Info()<<"15. matCode  get failed: NO locCode IN WMS system.........return.................. "<<endl;
			return ret;
		}
		orderDataBaseEAF.setMatCode(matCode);
		log.Info()<<"15. MatCode  set Success........................... "<<endl;

		//16. 设定compCode
		orderDataBaseEAF.setCompCode(wmsCompCode);
		log.Info()<<"16. CompCode  set Success........................... "<<endl;

		//17.设定理论作业重量,只有在装车时有值  如果是卸料,值为0
		//如果是装车，L3指定的料格内物料存量不够,报警返回
		long calWgt = 0;
		if (stockWgt < reqWgt && abs(stockWgt - reqWgt) > EventParkingHandler::MPE_WGT)
		{
			log.Info()<<"17. calWgt  get failed:  ZC, L3 give  reqWgt   <  stockWgt  in WMS system...........return................ "<<endl;
			return ret;
		}
		calWgt = reqWgt;		
		orderDataBaseEAF.setCalWeight(calWgt);
		log.Info()<<"17. CalWgt  set Success........................... "<<endl;

		//18.设定实际作业量
		//指令生成阶段，统一设定为0
		long actWgt = 0;
		orderDataBaseEAF.setActWeight(actWgt);
		log.Info()<<"18. ActWgt  set Success........................... "<<endl;

		//19.设定取料位
		string fromStockNO = carPlanBandInfoBase.getTargetGridNO();
		orderDataBaseEAF.setFromStockNO(fromStockNO);
		log.Info()<<"19. FromStockNO  set Success........................... "<<endl;

		//20.设定放料位
		string toStockNO = parkingNO;
		orderDataBaseEAF.setToStockNO(toStockNO);
		log.Info()<<"20. ToStockNO  set Success........................... "<<endl;

		//21.落关位位置内顺序 对L3计划无意义 设置为0
		long downPosSeq = 0;
		orderDataBaseEAF.setDownPosSeq(downPosSeq);
		log.Info()<<"21. DownPosSeq  set Success........................... "<<endl;

		//22. 是否需要卸料质检:EAF不存在质检需求
		string qcFlag = "";
		orderDataBaseEAF.setQCFlag(qcFlag);
		log.Info()<<"22. QCFlag  set Success........................... "<<endl;

		//所有指令基础数据具备，最后生成指令号
		long orderNO = 0;
		if (false == SQL4Order::SelOrderNO(orderNO))
		{
			log.Info()<<"orderNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setOrderNO(orderNO);
		log.Info()<<" orderNO  set Success........................... "<<endl;

		log.Info()<<"......................................................Current EAF Order Info: orderNO = "<<orderNO<<"  ................................................................... "<<endl;
		
		ret = true;
		return ret;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return ret;
}



bool EventParkingHandler::MakeSingleOrderEAF(CarPlanBandInfo  carPlanBandInfoBase, 
																						long orderGroupNO, 
																						string parkingNO, 
																						long exeSeq, 
																						string gridNO, 
																						string matCode, 
																						long calWgt, 
																						OrderDataBase& orderDataBaseEAF)
{
	string functionName = "EventParkingHandler::MakeSingleOrderEAF";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		log.Info()<<"ExeSeq = "<<exeSeq<<" , MakeSingleOrderEAF start.............................................................................................."<<endl;
		//1. 获取指令组号
		orderDataBaseEAF.setOrderGroupNO(orderGroupNO);
		log.Info()<<"1. OrderGroupNO  set Success........................... "<<endl;

		//2.获取指令组内执行顺序号
		orderDataBaseEAF.setExeSeq(exeSeq);
		log.Info()<<"2. ExeSeq  set Success........................... "<<endl;

		//3.设定指令类型
		string orderType = "";
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			orderType = OrderDataBase::ORDER_TYPE_EAF_YARD_TO_CAR_22;
		}
		else
		{
			orderType = OrderDataBase::ORDER_TYPE_L3_CAR_TO_YARD_11;
		}
		orderDataBaseEAF.setOrderType(orderType);
		log.Info()<<"3. OrderType  set Success........................... "<<endl;

		//4.设定指令优先级
		long orderPriority = 0;
		if (false == SQL4Order::SelOrderPriority(orderDataBaseEAF.getOrderType(), orderPriority) )
		{
			log.Info()<<"4. orderPriority  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setOrderPriority(orderPriority);
		log.Info()<<"4. OrderPriority  set Success........................... "<<endl;

		//5.设定指令状态
		orderDataBaseEAF.setOrderStatus(OrderDataBase::ORDER_STATUS_NOT_START_1);
		log.Info()<<"5. OrderStatus  set Success........................... "<<endl;

		//6.设定指令删除标志
		orderDataBaseEAF.setOrderDelFlag(OrderDataBase::ORDER_DEL_FLAG_NOT_DEL_1);
		log.Info()<<"6. OrderDelFlag  set Success........................... "<<endl;

		//7.设定对应计划来源
		orderDataBaseEAF.setPlanSrc(carPlanBandInfoBase.getPlanSrc());
		log.Info()<<"7. PlanSrc  set Success........................... "<<endl;

		//8.设定计划号
		orderDataBaseEAF.setPlanNO(carPlanBandInfoBase.getPlanNO());
		log.Info()<<"8. PlanNO  set Success........................... "<<endl;

		//9.设定对应计划子ID
		orderDataBaseEAF.setPlanDetailID(carPlanBandInfoBase.getPlanDetailID());
		log.Info()<<"9. PlanDetailID  set Success........................... "<<endl;

		//10.设定外部系统废钢代码
		string locCode = "";
		string scrapCode = "";
		string compCode = "";
		long reqWgt = DF_INT_NULL;
		if ( false == GetScrapCodeReqWgt(carPlanBandInfoBase, locCode, scrapCode, compCode, reqWgt))
		{
			log.Info()<<"10. scrapCode  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setScrapCode(scrapCode);
		log.Info()<<"10. ScrapCode  set Success........................... "<<endl;		

		//11.设定外部系统废钢要求重量
		orderDataBaseEAF.setReqWeight(reqWgt);
		log.Info()<<"11. ReqWgt  set Success........................... "<<endl;

		//12. 设定车号（装车车号/卸料车号/RGV车号）
		orderDataBaseEAF.setCarNO(carPlanBandInfoBase.getCarNO());
		log.Info()<<"12. CarNO  set Success........................... "<<endl;

		//13.设定车辆类型
		orderDataBaseEAF.setCarType(carPlanBandInfoBase.getCarType());
		log.Info()<<"13. CarType  set Success........................... "<<endl;

		//14.设定跨号
		//根据parkingNO获取对应跨号BayNO
		string bayNO = DF_STR_NULL;
		if (false == SQL4Order::SelBayNOByParkingNO(parkingNO, bayNO))
		{
			log.Info()<<"14. bayNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setBayNO(bayNO);
		log.Info()<<"14. BayNO  set Success........................... "<<endl;

		//15.设定WMS系统物料代码
		//L3计划中，scrapCode就是matCode,无需再转换
		//如果L3所给料格代码与WMS系统中料格代码中的物料代码不匹配，报警返回
		orderDataBaseEAF.setMatCode(matCode);
		log.Info()<<"15. MatCode  set Success........................... "<<endl;

		//16.设定理论作业重量,只有在装车时有值  如果是卸料,值为0
		//如果是装车，L3指定的料格内物料存量不够,报警返回		
		orderDataBaseEAF.setCalWeight(calWgt);
		log.Info()<<"16. CalWgt  set Success........................... "<<endl;

		//17.设定实际作业量
		//指令生成阶段，统一设定为0
		long actWgt = 0;
		orderDataBaseEAF.setActWeight(actWgt);
		log.Info()<<"17. ActWgt  set Success........................... "<<endl;

		//18.设定取料位
		string fromStockNO = DF_STR_NULL;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//对于卸料，取料位就是停车位
			fromStockNO = parkingNO;
		}
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//对于装车,取料位就是料格号
			fromStockNO = gridNO;
		}
		orderDataBaseEAF.setFromStockNO(fromStockNO);
		log.Info()<<"18. FromStockNO  set Success........................... "<<endl;

		//19.设定放料位
		string toStockNO = DF_STR_NULL;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//对于卸料，放料位就是料格
			toStockNO = locCode;
		}
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//对于装车,放料位就是停车位
			toStockNO = parkingNO;
		}
		orderDataBaseEAF.setToStockNO(toStockNO);
		log.Info()<<"19. ToStockNO  set Success........................... "<<endl;

		//20.落关位位置内顺序 对EAF计划无意义 设置为0 
		long downPosSeq = 0;
		orderDataBaseEAF.setDownPosSeq(downPosSeq);
		log.Info()<<"20. DownPosSeq  set Success........................... "<<endl;

		ret = true;
		return ret;

	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return ret;
}


//locCode  compCode为L3要求
bool EventParkingHandler::GetScrapCodeReqWgt(CarPlanBandInfo carPlanBandInfoBase, string& locCode, string& scrapCode, string& compCode, long& reqWgt)
{
	string functionName = "EventParkingHandler::GetScrapCodeReqWgt";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_L3)
		{
			//从L3废钢物料出入库表中获取数据
			if (false == SQL4Order::SelScrapCodeReqWgtFormL3(carPlanBandInfoBase.getPlanNO(), carPlanBandInfoBase.getWorkType(), locCode, scrapCode, compCode, reqWgt))
			{
				log.Info()<<"SelScrapCodeReqWgtFormL3    FAILED................return..............."<<endl;
				return ret;
			}
			ret = true;
			return ret;
		}
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_EAF)
		{
			//电炉L2计划中获取数据
			if (false == SQL4Order::SelScrapCodeReqWgtFromEAF(carPlanBandInfoBase.getPlanNO(), carPlanBandInfoBase.getPlanDetailID(), scrapCode, reqWgt))
			{
				log.Info()<<"SelScrapCodeReqWgtFromEAF    FAILED................return..............."<<endl;
				return ret;
			}
			ret = true;
			return ret;
		}
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_BOF)
		{
			//转炉L2计划中获取数据
			if (false == SQL4Order::SelScrapCodeReqWgtFromBOF(carPlanBandInfoBase.getPlanNO(), carPlanBandInfoBase.getPlanDetailID(), scrapCode, reqWgt))
			{
				log.Info()<<"SelScrapCodeReqWgtFromBOF    FAILED................return..............."<<endl;
				return ret;
			}
			ret = true;
			return ret;
		}
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return ret;
}

string EventParkingHandler::GetOrderType(string planSrc, string workType)
{
	string functionName = "EventParkingHandler::GetOrderType";
	LOG log(functionName, AUTO_CATCH_PID);
	string orderType = "";
	try
	{
		if (planSrc == CarPlanBandInfo::PLAN_SRC_L3)
		{
			if (workType == CarPlanBandInfo::WORK_TYPE_ZC)
			{
				orderType = OrderDataBase::ORDER_TYPE_L3_YARD_TO_CAR_21;
			}
			else
			{
				orderType = OrderDataBase::ORDER_TYPE_L3_CAR_TO_YARD_11;
			}
		}
		else if (planSrc == CarPlanBandInfo::PLAN_SRC_EAF)
		{
			orderType == OrderDataBase::ORDER_TYPE_EAF_YARD_TO_CAR_22;
		}
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return orderType;
}


bool EventParkingHandler::GetOrderQueue(OrderDataBase orderData, OrderQueueBase& orderQueue)
{
	string functionName = "EventParkingHandler::GetOrderQueue";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		log.Info()<<"OrderCreateL3 start.............................................................................................."<<endl;
		//OrderDataBase orderDataBaseL3;

		//1. 指令号
		orderQueue.setOrderNO(orderData.getOrderNO());
		//2. 指令组号
		orderQueue.setOrderGroupNO(orderData.getOrderGroupNO());
		//3.指令组内执行顺序号
		orderQueue.setExeSeq(orderData.getExeSeq());
		//4. 指令类型
		orderQueue.setOrderType(orderData.getOrderType());
		//5. 指令优先级
		orderQueue.setOrderPriority(orderData.getOrderPriority());

		//6. 是否可吊标记:根据 orderdata中的qcflag来判断  1：需要质检 则不可吊,等待后续L3通知  2：不需要质检 则可吊
		string exeEnable = "";
		if (orderData.getQCFlag() == OrderDataBase::ORDER_QC_FLAG_1)
		{
			exeEnable = OrderQueueBase::EXE_ENABLE_NO_2;
		}
		orderQueue.setExeEnable(exeEnable);
		//7. 行车号分配
		string craneNO = "";
		orderQueue.setCraneNO("");
		//8. 指令状态
		string cmdStatus = OrderQueueBase::CMD_STATUS_INIT_0;
		orderQueue.setCmdStatus(cmdStatus);
		//9.指令当前执行次数
		long seqNO = 0;
		orderQueue.setCmdSeq(seqNO);

		//10.计划来源
		orderQueue.setPlanSrc(orderData.getPlanSrc());
		//11.计划号
		orderQueue.setPlanNO(orderData.getPlanNO());
		//12.子计划号
		orderQueue.setPlanDetailID(orderData.getPlanDetailID());
		//13.外部系统废钢代码
		orderQueue.setScrapCode(orderData.getScrapCode());
		//14.外部系统要求重量
		orderQueue.setReqWeight(orderData.getReqWeight());
		//15.车号
		orderQueue.setCarNO(orderData.getCarNO());
		//16.车类型
		orderQueue.setCarType(orderData.getCarType());
		//17.跨号
		orderQueue.setBayNO(orderData.getBayNO());
		//18.废钢代码
		orderQueue.setMatCode(orderData.getMatCode());
		//19.钢制码
		orderQueue.setCompCode(orderData.getCompCode());
		//20.理论作业重量
		orderQueue.setCalWeight(orderData.getCalWeight());
		//21.实际作业重量
		orderQueue.setActWeight(orderData.getActWeight());
		//22.起吊位
		orderQueue.setFromStockNO(orderData.getFromStockNO());
		//23.落关位
		orderQueue.setToStockNO(orderData.getToStockNO());
		//24.车内位置顺序 RGV
		orderQueue.setDownPosSeq(orderData.getDownPosSeq());

		
		ret = true;
		return ret;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return ret;
}


bool EventParkingHandler::GetRecCraneNO(OrderDataBase orderData, string& recCraneNO)
{
	string functionName = "EventParkingHandler::GetRecCraneNO";
	LOG log(functionName, AUTO_CATCH_PID);
	bool  ret = false;
	try
	{
		//获取废钢对应的吊运方式
		string liftMode = "";
		if (false == SQL4Order::SelLiftMode(orderData.getMatCode(), orderData.getCompCode(), liftMode))
		{
			log.Info()<<"SelLiftMode is error, check UACS_L3_MAT_RELATION_INFO  must config liftmode ....return false...."<<endl;
			ret = false;
			return ret;
		}

		//根据跨号区分处理
		//电炉跨
		if (orderData.getBayNO() == "EAF_E" || orderData.getBayNO() == "EAF_F")
		{
			if (liftMode == "1" || liftMode == "2")//抓斗或吸盘 则直接获取行车号
			{
				if (false == SQL4Order::SelCraneNOEAFBayByLfitMode(orderData.getBayNO(), liftMode, recCraneNO))
				{
					log.Info()<<"SelCraneNOEAFBayByLfitMode is error, check UACS_CRANE_DEFINE  must config  ....return false...."<<endl;
					ret = false;
					return ret;
				}
			}
			if (liftMode == "3")//2者均可 ，则获取跨中行车列表 以map形式获取<seq,craneno>
			{
				//获取跨长
				//获取跨内行车数量
				//根据料格Xpos获取跨内是第几等分 从小到大  
				//根据第几等分，初步获得推荐行车号
				long bayLength = SQL4Order::SelBayLength(orderData.getBayNO());
				long craneNum = SQL4Order::SelCraneNumInBay(orderData.getBayNO());
				string gridNO = GetGridNOByOrderType(orderData);
				long xPos = SQL4Order::SelGridXCenter(gridNO);
				if (bayLength <= 0 || craneNum <= 0 || xPos <= 0)
				{
					ret = false;
					return ret;
				}
				long seqNO = GetXPosSeqInBayDivide(bayLength, craneNum, xPos);
				if (false == SQL4Order::SelCraneNOByBaySeq(orderData.getBayNO(), seqNO, recCraneNO))
				{
					log.Info()<<"SelCraneNOByBaySeq is error, check UACS_CRANE_DEFINE  must config  ....return false...."<<endl;
					ret = false;
					return ret;
				}



				//如果行车是离线状态, 则看邻车是否可用,根据作业范围来

				//如果行车自动无指令，则推荐此行车

				//如果行车自动有指令,则看邻车,如果也有指令,则给本行车;
				//如果没指令,看指令中料格xpos是否在邻车的作业区间,且距离本车的作业料格xpos是否是安全距离 且大于或小于本车作业料格xpos,满足则给邻车,不满足还是给本车

				//如果行车手动，推荐此行车


			}
			

			ret = true;
			return ret;
		}

		//二炼钢转炉跨
		if (orderData.getBayNO() == "BOF_A" || orderData.getBayNO() == "BOF_B" || orderData.getBayNO() == "BOF_C")
		{
		}


	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return ret;
}


long EventParkingHandler::GetXPosSeqInBayDivide(long bayLength, long divideNum, long xPos)
{
	string functionName = "EventParkingHandler::GetXPosSeqInBayDivide";
	LOG log(functionName, AUTO_CATCH_PID);
	long seqNO = 0;
	try
	{
		long divideEqual = bayLength/divideNum;
		for (long i = 1; i <= divideNum; i++)
		{
			long currentLengthMax =  divideEqual*i;
			if (xPos < currentLengthMax)
			{
				seqNO = i;
				break;
			}
		}		
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return seqNO;
}


string EventParkingHandler::GetGridNOByOrderType(OrderDataBase orderData)
{
	string functionName = "EventParkingHandler::GetGridNOByOrderType";
	LOG log(functionName, AUTO_CATCH_PID);
	string gridNO = "";
	try
	{
		string orderType = orderData.getOrderType();
		if (orderType == OrderDataBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			gridNO = orderData.getToStockNO();
		}
		if (orderType == OrderDataBase::ORDER_TYPE_L3_YARD_TO_CAR_21)
		{
			gridNO = orderData.getFromStockNO();
		}
		if (orderType == OrderDataBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
		{
			gridNO = orderData.getFromStockNO();
		}
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return gridNO;
}