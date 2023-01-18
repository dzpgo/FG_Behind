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

const	long EventParkingHandler::MPE_WGT = 100;//��λ kg

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
		string workType = kValues[0];//��ҵ����
		string carType = kValues[1];//������
		string carNO = kValues[2];//����
		string parkingNO = kValues[3];//ͣ��λ�� ��װ�����Ƿ���λ  ж�Ͼ���ȡ��λ��
		log.Info()<<"workType = "<<workType<<" , carType = "<<carType<<" , carNO = "<<carNO<<" , parkingNO = "<<parkingNO<<endl;

		//2.����г����Ѿ�������ָ������˳�
		if (true == SQL4Order::CarOrderFlagExist(carNO, workType))
		{
			log.Info()<<"carNO = "<<carNO<<" has  ORDER   and  not finish yet,  return.................."<<endl;
			return;
		}

		//3.���û�ж�Ӧ�ƻ�,�����˳�
		CarPlanBandInfo carPlanBandInfoBase;
		if (false == SQL4Order::SelCarPlanBandInfo(carNO, workType, carPlanBandInfoBase))
		{
			log.Info()<<"carNO = "<<carNO<<" has  NO PLAN,  return.................."<<endl;
			return;
		}
		//��ӡ��ȡ���ĳ�������Ϣ
		carPlanBandInfoBase.logOutValues();

		//4.���ݼƻ���Դ���벻ͬ��ָ�������߼�
		OrderDataBase  matOrderDataBase;//for L3 ��¯�ƻ�
		//L3�ƻ�
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_L3)
		{
			if (false == OrderCreateL3(carPlanBandInfoBase, parkingNO, matOrderDataBase))
			{
				log.Info()<<"OrderCreateL3  failed!  return............................."<<endl;
				return;
			}
		}
		//EAF�ƻ�
		else if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_EAF)
		{
			//if (false == OrderCreateEAFMap(carPlanBandInfoBase, parkingNO, mapOrderData))
			if (false == OrderCreateEAF(carPlanBandInfoBase, parkingNO, matOrderDataBase))
			{
				log.Info()<<"OrderCreateEAF  failed!  return............................."<<endl;
				return;
			}
		}
		//BOF�ƻ�
		else if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_BOF)
		{
			//��ת¯װ��,����˳�򽫶�������װ����RGV�����1��ָ���map���ж���ָ��
		}

		//5. ����OrderData������ �� OrderQueue����
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
		
		//1. ��ȡָ�����
		long orderGroupNO = 0;
		if (false == SQL4Order::SelOrderGroupNO(orderGroupNO))
		{
			log.Info()<<"1. orderGroupNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseL3.setOrderGroupNO(orderGroupNO);
		log.Info()<<"1. OrderGroupNO  set Success........................... "<<endl;

		//2.��ȡָ������ִ��˳��ţ�����ж�϶��� Ŀǰ�趨ֻ��1��ָ��  ��ν����ָ���Ƿ�Ϊ1�����Ƕ��������ǽ����ݵ��˶�����ȷ������Ҫ������ʼλ��Ŀ��λ�Ƿ��б仯����
		//L3��װ����ж��ָ��  �ϸ�L2��װ��ָ��   ��Ϊ���ǿ���װ����ֻ��ͣ��ָ���ϸ�λ����һ���ϸ���˳��ϻ����ϣ�����ֻ��һ��ָ������ָ����ܱ�ִ�ж�Σ���Ϊһ�β�һ�������ָ�������ĵ��� 
		//����L2��װ��ָ����ܻ���һ�����϶�Ӧ����ϸ���˵�������֣����Ի��ж���ָ��  
		orderDataBaseL3.setExeSeq(1);
		log.Info()<<"2. ExeSeq  set Success........................... "<<endl;

		//3.�趨ָ������
		string orderType = GetOrderType(carPlanBandInfoBase.getPlanSrc(), carPlanBandInfoBase.getWorkType());
		orderDataBaseL3.setOrderType(orderType);
		log.Info()<<"3. OrderType  set Success........................... "<<endl;

		//4.�趨ָ�����ȼ�
		long orderPriority = 0;
		if (false == SQL4Order::SelOrderPriority(orderDataBaseL3.getOrderType(), orderPriority) )
		{
			log.Info()<<"4. orderPriority  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseL3.setOrderPriority(orderPriority);
		log.Info()<<"4. OrderPriority  set Success........................... "<<endl;

		//5.�趨ָ��״̬
		orderDataBaseL3.setOrderStatus(OrderDataBase::ORDER_STATUS_NOT_START_1);
		log.Info()<<"5. OrderStatus  set Success........................... "<<endl;

		//6.�趨ָ��ɾ����־
		orderDataBaseL3.setOrderDelFlag(OrderDataBase::ORDER_DEL_FLAG_NOT_DEL_1);
		log.Info()<<"6. OrderDelFlag  set Success........................... "<<endl;

		//7.�趨��Ӧ�ƻ���Դ
		orderDataBaseL3.setPlanSrc(carPlanBandInfoBase.getPlanSrc());
		log.Info()<<"7. PlanSrc  set Success........................... "<<endl;

		//8.�趨�ƻ���
		orderDataBaseL3.setPlanNO(carPlanBandInfoBase.getPlanNO());
		log.Info()<<"8. PlanNO  set Success........................... "<<endl;

		//9.�趨��Ӧ�ƻ���ID
		orderDataBaseL3.setPlanDetailID(carPlanBandInfoBase.getPlanDetailID());
		log.Info()<<"9. PlanDetailID  set Success........................... "<<endl;

		//10.�趨�ⲿϵͳ�ϸִ���
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

		//11.�趨�ⲿϵͳ�ϸ�Ҫ������
		orderDataBaseL3.setReqWeight(reqWgt);
		log.Info()<<"11. ReqWgt  set Success........................... "<<endl;

		//12. �趨���ţ�װ������/ж�ϳ���/RGV���ţ�
		orderDataBaseL3.setCarNO(carPlanBandInfoBase.getCarNO());
		log.Info()<<"12. CarNO  set Success........................... "<<endl;

		//13.�趨��������
		orderDataBaseL3.setCarType(carPlanBandInfoBase.getCarType());
		log.Info()<<"13. CarType  set Success........................... "<<endl;

		//14.�趨���
		//����parkingNO��ȡ��Ӧ���BayNO
		string bayNO = DF_STR_NULL;
		if (false == SQL4Order::SelBayNOByParkingNO(parkingNO, bayNO))
		{
			log.Info()<<"14. bayNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseL3.setBayNO(bayNO);
		log.Info()<<"14. BayNO  set Success........................... "<<endl;

		//15.�趨WMSϵͳ���ϴ���
		//L3�ƻ��У�scrapCode����matCode,������ת��
		//���L3�����ϸ������WMSϵͳ���ϸ�����е����ϴ��벻ƥ�䣬��������
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

		//16. �趨compCode
		orderDataBaseL3.setCompCode(compCode);
		log.Info()<<"16. CompCode  set Success........................... "<<endl;

		//17.�趨������ҵ����,ֻ����װ��ʱ��ֵ  �����ж��,ֵΪ0
		//�����װ����L3ָ�����ϸ������ϴ�������,��������
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

		//18.�趨ʵ����ҵ��
		//ָ�����ɽ׶Σ�ͳһ�趨Ϊ0
		long actWgt = 0;
		orderDataBaseL3.setActWeight(actWgt);
		log.Info()<<"18. ActWgt  set Success........................... "<<endl;

		//19.�趨ȡ��λ
		string fromStockNO = DF_STR_NULL;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//����ж�ϣ�ȡ��λ����ͣ��λ
			fromStockNO = parkingNO;
		}
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//����װ��,ȡ��λ�����ϸ��
			fromStockNO = locCode;
		}
		orderDataBaseL3.setFromStockNO(fromStockNO);
		log.Info()<<"19. FromStockNO  set Success........................... "<<endl;

		//20.�趨����λ
		string toStockNO = DF_STR_NULL;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//����ж�ϣ�����λ�����ϸ�
			toStockNO = locCode;
		}
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//����װ��,����λ����ͣ��λ
			toStockNO = parkingNO;
		}
		orderDataBaseL3.setToStockNO(toStockNO);
		log.Info()<<"20. ToStockNO  set Success........................... "<<endl;

		//21.���λλ����˳�� ��L3�ƻ������� ����Ϊ0
		long downPosSeq = 0;
		orderDataBaseL3.setDownPosSeq(downPosSeq);
		log.Info()<<"21. DownPosSeq  set Success........................... "<<endl;

		//22. �Ƿ���Ҫж���ʼ�
		string qcFlag = "";
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			SQL4Order::SelQCFlag(orderDataBaseL3.getPlanNO(), qcFlag);
		}
		orderDataBaseL3.setQCFlag(qcFlag);
		log.Info()<<"22. QCFlag  set Success........................... "<<endl;

		//mapOrderData.insert(MapOrderDataBase::value_type(1,orderDataBaseL3));
		//�������ָ���
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
		//1.���ݵ�¯�����ķϸִ����ȡwmsϵͳ�������Ӧ���ϴ����������ϸ���Ϣ
		//2.���ݵ�¯��װ������Ҫ��,��֯MapGridMatWgtEAF
		//3.����MapGridMatWgtEAF���ݣ���֯MapOrderDataBase
		
		//��ȡ�˴ε�¯�ϸ���װ������MapGridMatWgtEAF
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
		
		//��ʼ��ָ֯������
		log.Info()<<"OrderCreateEAF  REAL DATA start................................................................ "<<endl;

		//ͬһ��ָ��,ָ�������Ψһ��
		long orderGroupNO = 0;
		if (false == SQL4Order::SelOrderGroupNO(orderGroupNO))
		{
			log.Info()<<"orderGroupNO  get failed.........return "<<endl;
			return ret;
		}
		MapGridMatWgtEAF::iterator itor;
		for (itor = mapGridMatWgtEafBase.begin(); itor != mapGridMatWgtEafBase.end(); itor++)
		{
			//����ִ��˳���
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

		//1. ��ȡָ�����
		long orderGroupNO = 0;
		if (false == SQL4Order::SelOrderGroupNO(orderGroupNO))
		{
			log.Info()<<"1. orderGroupNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setOrderGroupNO(orderGroupNO);
		log.Info()<<"1. OrderGroupNO  set Success........................... "<<endl;

		//2.��ȡָ������ִ��˳��ţ�����ж�϶��� Ŀǰ�趨ֻ��1��ָ��  ��ν����ָ���Ƿ�Ϊ1�����Ƕ��������ǽ����ݵ��˶�����ȷ������Ҫ������ʼλ��Ŀ��λ�Ƿ��б仯����
		//L3��װ����ж��ָ��  �ϸ�L2��װ��ָ��   ��Ϊ���ǿ���װ����ֻ��ͣ��ָ���ϸ�λ����һ���ϸ���˳��ϻ����ϣ�����ֻ��һ��ָ������ָ����ܱ�ִ�ж�Σ���Ϊһ�β�һ�������ָ�������ĵ��� 
		//����L2��װ��ָ����ܻ���һ�����϶�Ӧ����ϸ���˵�������֣����Ի��ж���ָ��  
		orderDataBaseEAF.setExeSeq(1);
		log.Info()<<"2. ExeSeq  set Success........................... "<<endl;

		//3.�趨ָ������
		string orderType = GetOrderType(carPlanBandInfoBase.getPlanSrc(), carPlanBandInfoBase.getWorkType());
		orderDataBaseEAF.setOrderType(orderType);
		log.Info()<<"3. OrderType  set Success........................... "<<endl;

		//4.�趨ָ�����ȼ�
		long orderPriority = 0;
		if (false == SQL4Order::SelOrderPriority(orderDataBaseEAF.getOrderType(), orderPriority) )
		{
			log.Info()<<"4. orderPriority  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setOrderPriority(orderPriority);
		log.Info()<<"4. OrderPriority  set Success........................... "<<endl;

		//5.�趨ָ��״̬
		orderDataBaseEAF.setOrderStatus(OrderDataBase::ORDER_STATUS_NOT_START_1);
		log.Info()<<"5. OrderStatus  set Success........................... "<<endl;

		//6.�趨ָ��ɾ����־
		orderDataBaseEAF.setOrderDelFlag(OrderDataBase::ORDER_DEL_FLAG_NOT_DEL_1);
		log.Info()<<"6. OrderDelFlag  set Success........................... "<<endl;

		//7.�趨��Ӧ�ƻ���Դ
		orderDataBaseEAF.setPlanSrc(carPlanBandInfoBase.getPlanSrc());
		log.Info()<<"7. PlanSrc  set Success........................... "<<endl;

		//8.�趨�ƻ���
		orderDataBaseEAF.setPlanNO(carPlanBandInfoBase.getPlanNO());
		log.Info()<<"8. PlanNO  set Success........................... "<<endl;

		//9.�趨��Ӧ�ƻ���ID
		orderDataBaseEAF.setPlanDetailID(carPlanBandInfoBase.getPlanDetailID());
		log.Info()<<"9. PlanDetailID  set Success........................... "<<endl;

		//10.�趨�ⲿϵͳ�ϸִ���
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

		//11.�趨�ⲿϵͳ�ϸ�Ҫ������
		orderDataBaseEAF.setReqWeight(reqWgt);
		log.Info()<<"11. ReqWgt  set Success........................... "<<endl;

		//12. �趨���ţ�װ������/ж�ϳ���/RGV���ţ�
		orderDataBaseEAF.setCarNO(carPlanBandInfoBase.getCarNO());
		log.Info()<<"12. CarNO  set Success........................... "<<endl;

		//13.�趨��������
		orderDataBaseEAF.setCarType(carPlanBandInfoBase.getCarType());
		log.Info()<<"13. CarType  set Success........................... "<<endl;

		//14.�趨���
		//����parkingNO��ȡ��Ӧ���BayNO
		string bayNO = DF_STR_NULL;
		if (false == SQL4Order::SelBayNOByParkingNO(parkingNO, bayNO))
		{
			log.Info()<<"14. bayNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setBayNO(bayNO);
		log.Info()<<"14. BayNO  set Success........................... "<<endl;

		//15.�趨WMSϵͳ���ϴ���
		//�ϸ�L2�ƻ��У�scrapCode���ǵ�¯ϵͳ�ϸִ���, ��Ҫת����WMS�ϸִ���  
		//�ϸ���Ѿ�ȷ��������ͨ�������ƻ�����Ϣ���е�targetGridNO��ȡWMS�ϸִ���͸�����
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

		//16. �趨compCode
		orderDataBaseEAF.setCompCode(wmsCompCode);
		log.Info()<<"16. CompCode  set Success........................... "<<endl;

		//17.�趨������ҵ����,ֻ����װ��ʱ��ֵ  �����ж��,ֵΪ0
		//�����װ����L3ָ�����ϸ������ϴ�������,��������
		long calWgt = 0;
		if (stockWgt < reqWgt && abs(stockWgt - reqWgt) > EventParkingHandler::MPE_WGT)
		{
			log.Info()<<"17. calWgt  get failed:  ZC, L3 give  reqWgt   <  stockWgt  in WMS system...........return................ "<<endl;
			return ret;
		}
		calWgt = reqWgt;		
		orderDataBaseEAF.setCalWeight(calWgt);
		log.Info()<<"17. CalWgt  set Success........................... "<<endl;

		//18.�趨ʵ����ҵ��
		//ָ�����ɽ׶Σ�ͳһ�趨Ϊ0
		long actWgt = 0;
		orderDataBaseEAF.setActWeight(actWgt);
		log.Info()<<"18. ActWgt  set Success........................... "<<endl;

		//19.�趨ȡ��λ
		string fromStockNO = carPlanBandInfoBase.getTargetGridNO();
		orderDataBaseEAF.setFromStockNO(fromStockNO);
		log.Info()<<"19. FromStockNO  set Success........................... "<<endl;

		//20.�趨����λ
		string toStockNO = parkingNO;
		orderDataBaseEAF.setToStockNO(toStockNO);
		log.Info()<<"20. ToStockNO  set Success........................... "<<endl;

		//21.���λλ����˳�� ��L3�ƻ������� ����Ϊ0
		long downPosSeq = 0;
		orderDataBaseEAF.setDownPosSeq(downPosSeq);
		log.Info()<<"21. DownPosSeq  set Success........................... "<<endl;

		//22. �Ƿ���Ҫж���ʼ�:EAF�������ʼ�����
		string qcFlag = "";
		orderDataBaseEAF.setQCFlag(qcFlag);
		log.Info()<<"22. QCFlag  set Success........................... "<<endl;

		//����ָ��������ݾ߱����������ָ���
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
		//1. ��ȡָ�����
		orderDataBaseEAF.setOrderGroupNO(orderGroupNO);
		log.Info()<<"1. OrderGroupNO  set Success........................... "<<endl;

		//2.��ȡָ������ִ��˳���
		orderDataBaseEAF.setExeSeq(exeSeq);
		log.Info()<<"2. ExeSeq  set Success........................... "<<endl;

		//3.�趨ָ������
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

		//4.�趨ָ�����ȼ�
		long orderPriority = 0;
		if (false == SQL4Order::SelOrderPriority(orderDataBaseEAF.getOrderType(), orderPriority) )
		{
			log.Info()<<"4. orderPriority  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setOrderPriority(orderPriority);
		log.Info()<<"4. OrderPriority  set Success........................... "<<endl;

		//5.�趨ָ��״̬
		orderDataBaseEAF.setOrderStatus(OrderDataBase::ORDER_STATUS_NOT_START_1);
		log.Info()<<"5. OrderStatus  set Success........................... "<<endl;

		//6.�趨ָ��ɾ����־
		orderDataBaseEAF.setOrderDelFlag(OrderDataBase::ORDER_DEL_FLAG_NOT_DEL_1);
		log.Info()<<"6. OrderDelFlag  set Success........................... "<<endl;

		//7.�趨��Ӧ�ƻ���Դ
		orderDataBaseEAF.setPlanSrc(carPlanBandInfoBase.getPlanSrc());
		log.Info()<<"7. PlanSrc  set Success........................... "<<endl;

		//8.�趨�ƻ���
		orderDataBaseEAF.setPlanNO(carPlanBandInfoBase.getPlanNO());
		log.Info()<<"8. PlanNO  set Success........................... "<<endl;

		//9.�趨��Ӧ�ƻ���ID
		orderDataBaseEAF.setPlanDetailID(carPlanBandInfoBase.getPlanDetailID());
		log.Info()<<"9. PlanDetailID  set Success........................... "<<endl;

		//10.�趨�ⲿϵͳ�ϸִ���
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

		//11.�趨�ⲿϵͳ�ϸ�Ҫ������
		orderDataBaseEAF.setReqWeight(reqWgt);
		log.Info()<<"11. ReqWgt  set Success........................... "<<endl;

		//12. �趨���ţ�װ������/ж�ϳ���/RGV���ţ�
		orderDataBaseEAF.setCarNO(carPlanBandInfoBase.getCarNO());
		log.Info()<<"12. CarNO  set Success........................... "<<endl;

		//13.�趨��������
		orderDataBaseEAF.setCarType(carPlanBandInfoBase.getCarType());
		log.Info()<<"13. CarType  set Success........................... "<<endl;

		//14.�趨���
		//����parkingNO��ȡ��Ӧ���BayNO
		string bayNO = DF_STR_NULL;
		if (false == SQL4Order::SelBayNOByParkingNO(parkingNO, bayNO))
		{
			log.Info()<<"14. bayNO  get failed.........return "<<endl;
			return ret;
		}
		orderDataBaseEAF.setBayNO(bayNO);
		log.Info()<<"14. BayNO  set Success........................... "<<endl;

		//15.�趨WMSϵͳ���ϴ���
		//L3�ƻ��У�scrapCode����matCode,������ת��
		//���L3�����ϸ������WMSϵͳ���ϸ�����е����ϴ��벻ƥ�䣬��������
		orderDataBaseEAF.setMatCode(matCode);
		log.Info()<<"15. MatCode  set Success........................... "<<endl;

		//16.�趨������ҵ����,ֻ����װ��ʱ��ֵ  �����ж��,ֵΪ0
		//�����װ����L3ָ�����ϸ������ϴ�������,��������		
		orderDataBaseEAF.setCalWeight(calWgt);
		log.Info()<<"16. CalWgt  set Success........................... "<<endl;

		//17.�趨ʵ����ҵ��
		//ָ�����ɽ׶Σ�ͳһ�趨Ϊ0
		long actWgt = 0;
		orderDataBaseEAF.setActWeight(actWgt);
		log.Info()<<"17. ActWgt  set Success........................... "<<endl;

		//18.�趨ȡ��λ
		string fromStockNO = DF_STR_NULL;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//����ж�ϣ�ȡ��λ����ͣ��λ
			fromStockNO = parkingNO;
		}
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//����װ��,ȡ��λ�����ϸ��
			fromStockNO = gridNO;
		}
		orderDataBaseEAF.setFromStockNO(fromStockNO);
		log.Info()<<"18. FromStockNO  set Success........................... "<<endl;

		//19.�趨����λ
		string toStockNO = DF_STR_NULL;
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//����ж�ϣ�����λ�����ϸ�
			toStockNO = locCode;
		}
		if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//����װ��,����λ����ͣ��λ
			toStockNO = parkingNO;
		}
		orderDataBaseEAF.setToStockNO(toStockNO);
		log.Info()<<"19. ToStockNO  set Success........................... "<<endl;

		//20.���λλ����˳�� ��EAF�ƻ������� ����Ϊ0 
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


//locCode  compCodeΪL3Ҫ��
bool EventParkingHandler::GetScrapCodeReqWgt(CarPlanBandInfo carPlanBandInfoBase, string& locCode, string& scrapCode, string& compCode, long& reqWgt)
{
	string functionName = "EventParkingHandler::GetScrapCodeReqWgt";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_L3)
		{
			//��L3�ϸ����ϳ������л�ȡ����
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
			//��¯L2�ƻ��л�ȡ����
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
			//ת¯L2�ƻ��л�ȡ����
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

		//1. ָ���
		orderQueue.setOrderNO(orderData.getOrderNO());
		//2. ָ�����
		orderQueue.setOrderGroupNO(orderData.getOrderGroupNO());
		//3.ָ������ִ��˳���
		orderQueue.setExeSeq(orderData.getExeSeq());
		//4. ָ������
		orderQueue.setOrderType(orderData.getOrderType());
		//5. ָ�����ȼ�
		orderQueue.setOrderPriority(orderData.getOrderPriority());

		//6. �Ƿ�ɵ����:���� orderdata�е�qcflag���ж�  1����Ҫ�ʼ� �򲻿ɵ�,�ȴ�����L3֪ͨ  2������Ҫ�ʼ� ��ɵ�
		string exeEnable = "";
		if (orderData.getQCFlag() == OrderDataBase::ORDER_QC_FLAG_1)
		{
			exeEnable = OrderQueueBase::EXE_ENABLE_NO_2;
		}
		orderQueue.setExeEnable(exeEnable);
		//7. �г��ŷ���
		string craneNO = "";
		orderQueue.setCraneNO("");
		//8. ָ��״̬
		string cmdStatus = OrderQueueBase::CMD_STATUS_INIT_0;
		orderQueue.setCmdStatus(cmdStatus);
		//9.ָ�ǰִ�д���
		long seqNO = 0;
		orderQueue.setCmdSeq(seqNO);

		//10.�ƻ���Դ
		orderQueue.setPlanSrc(orderData.getPlanSrc());
		//11.�ƻ���
		orderQueue.setPlanNO(orderData.getPlanNO());
		//12.�Ӽƻ���
		orderQueue.setPlanDetailID(orderData.getPlanDetailID());
		//13.�ⲿϵͳ�ϸִ���
		orderQueue.setScrapCode(orderData.getScrapCode());
		//14.�ⲿϵͳҪ������
		orderQueue.setReqWeight(orderData.getReqWeight());
		//15.����
		orderQueue.setCarNO(orderData.getCarNO());
		//16.������
		orderQueue.setCarType(orderData.getCarType());
		//17.���
		orderQueue.setBayNO(orderData.getBayNO());
		//18.�ϸִ���
		orderQueue.setMatCode(orderData.getMatCode());
		//19.������
		orderQueue.setCompCode(orderData.getCompCode());
		//20.������ҵ����
		orderQueue.setCalWeight(orderData.getCalWeight());
		//21.ʵ����ҵ����
		orderQueue.setActWeight(orderData.getActWeight());
		//22.���λ
		orderQueue.setFromStockNO(orderData.getFromStockNO());
		//23.���λ
		orderQueue.setToStockNO(orderData.getToStockNO());
		//24.����λ��˳�� RGV
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
		//��ȡ�ϸֶ�Ӧ�ĵ��˷�ʽ
		string liftMode = "";
		if (false == SQL4Order::SelLiftMode(orderData.getMatCode(), orderData.getCompCode(), liftMode))
		{
			log.Info()<<"SelLiftMode is error, check UACS_L3_MAT_RELATION_INFO  must config liftmode ....return false...."<<endl;
			ret = false;
			return ret;
		}

		//���ݿ�����ִ���
		//��¯��
		if (orderData.getBayNO() == "EAF_E" || orderData.getBayNO() == "EAF_F")
		{
			if (liftMode == "1" || liftMode == "2")//ץ�������� ��ֱ�ӻ�ȡ�г���
			{
				if (false == SQL4Order::SelCraneNOEAFBayByLfitMode(orderData.getBayNO(), liftMode, recCraneNO))
				{
					log.Info()<<"SelCraneNOEAFBayByLfitMode is error, check UACS_CRANE_DEFINE  must config  ....return false...."<<endl;
					ret = false;
					return ret;
				}
			}
			if (liftMode == "3")//2�߾��� �����ȡ�����г��б� ��map��ʽ��ȡ<seq,craneno>
			{
				//��ȡ�糤
				//��ȡ�����г�����
				//�����ϸ�Xpos��ȡ�����ǵڼ��ȷ� ��С����  
				//���ݵڼ��ȷ֣���������Ƽ��г���
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



				//����г�������״̬, ���ڳ��Ƿ����,������ҵ��Χ��

				//����г��Զ���ָ����Ƽ����г�

				//����г��Զ���ָ��,���ڳ�,���Ҳ��ָ��,������г�;
				//���ûָ��,��ָ�����ϸ�xpos�Ƿ����ڳ�����ҵ����,�Ҿ��뱾������ҵ�ϸ�xpos�Ƿ��ǰ�ȫ���� �Ҵ��ڻ�С�ڱ�����ҵ�ϸ�xpos,��������ڳ�,�����㻹�Ǹ�����

				//����г��ֶ����Ƽ����г�


			}
			

			ret = true;
			return ret;
		}

		//������ת¯��
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