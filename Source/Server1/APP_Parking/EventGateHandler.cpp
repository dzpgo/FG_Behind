#include "EventGateHandler.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "MsgWG01.h"


using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

const  string EventGateHandler::EXTER_SYSTEM_BOF = "LG";//
const  string EventGateHandler::EXTER_SYSTEM_EAF = "DL";//

const  long EventGateHandler::MPE_WGT = 100;//

EventGateHandler::EventGateHandler(void)
{
}

EventGateHandler::~EventGateHandler(void)
{
}

//��բʶ���ƺŴ���
void EventGateHandler::CarArriveGateHandler(string strValue, string logFileName)
{
	LOG log("EventGateHandler::CarArriveGateHandler",logFileName);
	try
	{
		log.Info()<<"start........."<<endl;
		//1.����tagֵ�ַ���
		//EV��ʽ������,��բ���
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string carNO = kValues[0];//����
		string gateNO = kValues[1];//��բ�� 
		log.Info()<<" carNO = "<<carNO<<" , gateNO = "<<gateNO<<endl;

		//1.����г����Ѿ��ڿ�������ҵ�������˳�
		if (true == SQL4Parking::CarEnterYardExist(carNO))
		{
			log.Info()<<"carNO = "<<carNO<<" has  ENTER into yard  and  not leave yet,  return.................."<<endl;
			//��֯������ʾ��Ϣ������բled��
			//�������ݣ�����XXX���Ѿ��ڿ�����
			//httpsЭ��ӿڣ�����ʵ�ַ�ʽ����
			return;
		}

		//2.���û�ж�Ӧ�ƻ�,�����˳�
		CarPlanBandInfo carPlanBandInfoBase;
		//ѡ�����:
		//���ճ���ѡ��, ����bandtime���絽������,ѡ��һ��
		if (false == SQL4Parking::SelCarPlanBandInfo(carNO, carPlanBandInfoBase))
		{
			log.Info()<<"carNO = "<<carNO<<" has  NO PLAN,  return.................."<<endl;
			//��֯������ʾ��Ϣ������բled��
			//��������:����XXX��û�мƻ���
			//httpsЭ��ӿڣ�����ʵ�ַ�ʽ����
			return;
		}
		//��ӡ��ȡ���ĳ�������Ϣ
		carPlanBandInfoBase.logOutValues();

		//��ʼ�������ƻ�����Ϣ����Ŀ���ϸ�ŵ�բ��ͣ��λ�ŵ���Ϣ
		SQL4Parking::InitGateGridParking(carNO, carPlanBandInfoBase.getPlanNO());
		
		//L3�ƻ�
		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_L3)
		{
			//1.��L3�ƻ���˵,��ȡȡ���ϸ�  �� �����ϸ���  
			//2.���ݴ��ϸ��Ż�ȡ��Ӧ��� 
			//3.�����ź͵�բ��Ӧ���һ��  �������ҵ���Ӧ����ͣ��λ�����մ󳵾���ӽ���Զ���еĿ��г�λ�������У����³����ƻ���Ϣ�󶨱��е� ��բ�� ������Ŀ���ϸ��
			//4.�����ź͵�բ��һ��, ������ʾ:  Ӧ��ȥXX�磬��ǰ��ΪXXX  ���´˼�¼��բ��  ��Ŀ���ϸ��Ϊ��
			//5.������һ��,����û�п���ͣ��λ, ������ʾ: ��ǰ���޿���ͣ��λ  
			string locCode = "";
			string matCode = "";
			string compCode = "";
			long reqWgt = DF_INT_NULL;
			//==================���Ƿ��мƻ��ж�==================================================
			if (false == SQL4Parking::SelScrapCodeReqWgtFormL3(carPlanBandInfoBase.getPlanNO(), 
																												carPlanBandInfoBase.getWorkType(), 
																												locCode, 
																												matCode, 
																												compCode, 
																												reqWgt))
			{
				//L3û�мƻ����˳�
				log.Info()<<"carNO = "<<carNO<<" ,  SelScrapCodeReqWgtFormL3   error,  return.................."<<endl;
				//���͵�բLED�����ݣ�����XXX���޼ƻ�
				//todo
				return;
			}
			log.Info()<<"locCode = "<<locCode<<" , matCode = "<<matCode<<" , compCode = "<<compCode<<" , reqWgt = "<<reqWgt<<endl;
			//================================================================================

			//================�Ե�բ�ͼƻ��е�բ�Ƿ�һ���ж�============================================
			string bayNO = "";
			string tempGateNO = "";
			if (false == SQL4Parking::SelBayNOGateNOByGridNO(locCode, bayNO, tempGateNO))
			{
				//û�е�բ�Ϳ��Ӧ��ϵ �˳�
				log.Info()<<"carNO = "<<carNO<<" ,  SelBayNOGateNOByGridNO   error,  return.................."<<endl;
				return;
			}
			if (gateNO != tempGateNO)
			{
				//��ǰ��բ�ͼƻ���Ҫȥ���ϸ��բ�������˳�
				log.Info()<<"carNO = "<<carNO<<" ,  gateNO != tempGateNO   error,  return.................."<<endl;
				//���͵�բLED�����ݣ�����XXX��ӦȥXX�磬��ǰΪXX��
				//todo
				return;
			}
			//================================================================================

			//=================��L3�����ϸ���Ϣ��Ӧ�����Ϻ� WMSϵͳ���ϸ���Ϣ��Ӧ�����Ƿ�һ�½����жϣ�����������======
			string wmsMatCode = "";
			string wmsCompCode = "";
			long wmsMatWgt = DF_INT_NULL;
			if (false == SQL4Parking::SelGridInfoByGridNO(locCode, wmsMatCode, wmsCompCode, wmsMatWgt))
			{
				//Ҫȥ���ϸ���WMS�в����ڣ��˳�
				log.Info()<<"SelMatCompCodeByGridNO   error,  return.................."<<endl;
				return;
			}
			if (matCode  == wmsMatCode && compCode == wmsCompCode)
			{
			}
			else
			{
				//Ҫȥ���ϸ���WMS���������Ϻ͸�������L3�Ĳ������˳�
				log.Info()<<"matCode = "<<matCode<<" ,  wmsMatCode = "<<wmsMatCode<<" ;  compCode = "<<compCode<<" ,wmsCompCode = "<<wmsCompCode<<" ,  return.................."<<endl;
				//���͵�բLED�����ݣ�����XXX��ӦȥXX�ϸ񣬴��ϸ��������Ϻ�L3����
				//todo
				return;
			}
			//================================================================================

			//================�����װ�������п���Ƿ��㹻�ж�==========================================
			if (carPlanBandInfoBase.getWorkType() == CarPlanBandInfo::WORK_TYPE_ZC && wmsMatWgt < reqWgt && abs(wmsMatWgt - reqWgt) > 100)
			{
				//Ҫȥ���ϸ���WMS������������������L3Ҫ��װ�������˳�
				log.Info()<<"gridNO = "<<locCode<<" ,  wmsMatWgt = "<<wmsMatWgt<<" , reqWgt = "<<reqWgt<<" ,  NOT  REACHE L3 NEED REQWGT,  return.................."<<endl;
				//���͵�բLED�����ݣ�����XXX����ȥXX�ϸ񣬴��ϸ����ϴ�����������ҵ����
				//todo
			}
			//================================================================================

			//===========================��Ҫȥ�ϸ��Ӧ��ͣ��λ�Ƿ���н����ж�===========================
			string workStatus = "";
			string parkingNO = "";
			if (false == SQL4Parking::SelPKStatusByGridNO(locCode, parkingNO, workStatus))
			{
				//Ҫȥ���ϸ��Ӧͣ��λ��WMS�в����ڣ��˳�
				log.Info()<<"SelPKStatusByGridNO   error,  return.................."<<endl;
				return;
			}
			if (workStatus != "100")
			{
				log.Info()<<"workStatus = "<<workStatus<<"  ,  NOT FREE,  return.................."<<endl;
				//���͵�բLED�����ݣ�����XXX����ȥ�ϸ��Ӧͣ��λ������ҵ�����ɽ���
				//todo
				return;
			}
			//===============================================================================

			//�����ǿ��Խ��봦��
			//1.���³����ƻ��󶨱�:��բ��,Ŀ���ϸ��,Ŀ��ͣ��λ��
			SQL4Parking::UpdGateGridPKByCarPlan(carNO, carPlanBandInfoBase.getPlanNO(), gateNO, locCode, parkingNO);


			//��L3���͵���HCP411 ����Ʒ�ַϸֽ��������ַϸֶѳ�װж��Ϣ
			//	������ǣ�I:����  D:ɾ��),��ˮ��(Ҳ����L3�ƻ���) ,����(1:װ��  2:ж��)����ҵ״̬(1:�����볡;2:�����ϸ�;3:���뿪;4:��ѿ�ʼ;5:��ѽ���;)����ҵʱ��(yyyymmddhh24miss)
			iDA::DateTime dtNow = iDA::DateTime::Now();
			string tagName = "EV_L3MSG_SND_HCP411";
			string tagValue = "I," + carPlanBandInfoBase.getPlanNO() + "," + workTypeConvert(carPlanBandInfoBase.getWorkType()) + ",1," + dtNow.ToShortTimeString();
			EVTagSnd(tagName, tagValue);



			//���բϵͳ����ͬ������źţ�׼����룬
			//todo
			//���͵�բLED�����ݣ�����XXX��ȥ�ϸ�XXִ��װ��/ж����ҵ
			//todo

			log.Info()<<"CAR = "<<carNO<<" is arrive gate success..............................................."<<endl;
			return;
		}

		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_EAF)
		{
			//1.�Ե�¯�ƻ���˵����ȡ��¯�ƻ��ӱ�Ķ�Ӧ��scrapCode
			//2.���ݴ˵�բ��Ż�ȡ��Ӧ���
			//3.���ݴ˿���ҳ��Ƿ�˿��ڵ�matCode�����ɷ����㣨�����ϸ�����Ӵ�С���У���������㣬���У��ҳ����������ϸ���ΪĿ���ϸ�
			//4.��������㣬���յ�¯���ϼ���һ�����ѯ����matCode�����Ƿ�����(�����ϸ�����Ӵ�С����), �������, ��ʾ:Ӧ��ȥXX�磬��ǰ��ΪXXX���ϸִ�������  ����������㣬��ʾ��������ϸִ���������
			//5.�����������£����´˼�¼��բ��  ��Ŀ���ϸ��Ϊ��
			string scrapCode = "";
			long reqWgt = DF_INT_NULL;
			if (false == SQL4Parking::SelScrapCodeReqWgtFromEAF(carPlanBandInfoBase.getPlanNO(), carPlanBandInfoBase.getPlanDetailID(), scrapCode, reqWgt))
			{
				log.Info()<<"carNO = "<<carNO<<" ,  SelScrapCodeReqWgtFromEAF   error,  return.................."<<endl;
				return;
			}
			string bayNO = "";
			if (false == SQL4Parking::SelBayNOByGateNO(gateNO, bayNO))
			{
				log.Info()<<"carNO = "<<carNO<<" ,  SelBayNOByGateNO   error,  return.................."<<endl;
				return;
			}
			string targetGridNO = "";
			long falseReason = 0;
			string targetParkingNO = "";
			if (false == SQL4Parking::SelGridNOMatchScrapCode2(bayNO, scrapCode, reqWgt, EventGateHandler::EXTER_SYSTEM_EAF, targetGridNO, targetParkingNO, falseReason))
			{
				log.Info()<<"carNO = "<<carNO<<" ,  SelGridNOMatchScrapCode2   error, falseReason = "<<falseReason<<" , return.................."<<endl;		
				if (falseReason == 1)
				{
					//��ʾ�����Ӧ�޿���ͣ��λ��
					//������ʾ��LED��:  ����XXX���޿���ͣ��λ
					//todo
				}
				if (falseReason == 2)
				{
					//��ʾ�����Ӧ���Ͽ�治�㣬
					//������ʾ��LED��:  ����XXX������ҵ���ϱ����治��
					//todo
				}				
				return;
			}

			//ͨ����飬���Խ���
			//���³����ƻ��󶨱��е� Ŀ���ϸ�ź� ��բ��
			SQL4Parking::UpdGridGateByCarNOPlanNOPlanDetailID(carNO, carPlanBandInfoBase.getPlanNO(), carPlanBandInfoBase.getPlanDetailID(), targetGridNO, gateNO, targetParkingNO);

			//20220520 zhangyuhong add
			//���ӣ����¯L2���͡�����װ���������ġ�tag��
			//tag�����ƣ�EV_EAFL2_PARKING_CAR_ARRIVE
			//��ʽ : PONO,DETAIL_ID
			string tagName = "EV_EAFL2_PARKING_CAR_ARRIVE";
			string tagValue = carPlanBandInfoBase.getPlanNO() + "," + StringHelper::ToString(carPlanBandInfoBase.getPlanDetailID());
			EVTagSnd(tagName, tagValue);


			//���բϵͳLED�����ͣ�
			//����XXX��ȥ�ϸ�XXX����װ����ҵ
			//todo

			//���բϵͳ����ͬ������źţ�׼����룬ȥ�ϸ�ţ�locCode  
			//todo

		}

		if (carPlanBandInfoBase.getPlanSrc() == CarPlanBandInfo::PLAN_SRC_BOF)
		{
			//1.��ת¯�ƻ���˵��������û�г����ƻ��󶨵ģ�������Ҫ�Ȱ󶨼ƻ�  ��������ƻ�һ���ǹ̶��ı��üƻ� 
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


//��բ̧�˴���
void EventGateHandler::CarEnterGateHandler(string strValue, string logFileName)
{
	LOG log("EventGateHandler::CarEnterGateHandler",logFileName);
	try
	{
		log.Info()<<"start........."<<endl;
		//1.����tagֵ�ַ���
		//EV��ʽ������,��բ���
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string carNO = kValues[0];//����
		string gateNO = kValues[1];//��բ�� 
		log.Info()<<" carNO = "<<carNO<<" , gateNO = "<<gateNO<<endl;
		
		//���ݳ��ţ���բ��  ��ȡָ����¼,���û��¼,�����˳�(û�м�¼�Ŀ�����, ��բʶ��ɹ�,��WMS���Է��У����ǵ�բû��ͣ���ʱ��������һ�����բ����ʱ�Ͳ�ͨ���ˣ�Ȼ��ͻ���յ�բ��)
		//����м�¼�����ݰ󶨸���ENTER_FLAG=2 ˵���Ѿ�����
		//�ӳ����ƻ�����Ϣ���У���ȡĿ���ϸ���,֪ͨ�ϸ����ϵͳ
		string carType = "";
		string targetGridNO = "";
		string targetParkingNO = "";
		string workType = "";
		string planNO = "";
		string planSrc = "";
		long planDetailID = DF_INT_NULL;
		if (false == SQL4Parking::SelTargetGridNO(carNO, 
																					gateNO, 
																					carType, 
																					targetGridNO, 
																					targetParkingNO, 
																					workType, 
																					planNO, 
																					planSrc, 
																					planDetailID))
		{
			log.Info()<<"carNO = "<<carNO<<" SelTargetGridNO ERROR  , return.................."<<endl;
			return;
		}

		//����׼��������ر�

		//1.���³����ƻ��󶨱�UACS_PARKING_CAR_PLAN_INFO   �����־=2 
		SQL4Parking::UpdEnterFlag2Enter(carNO, gateNO);

		//2.����ͣ��λ״̬��UACS_PARKING_WORK_STATUS  ����ţ�workstatus�� worktype��carno
		long parkingTM = DF_INT_NULL;
		if (false == SQL4Parking::SelParkingTM(parkingTM))
		{
			log.Info()<<"carNO = "<<carNO<<" SelParkingTM ERROR  , return.................."<<endl;
			return;
		}
		string treatment1 = workType;
		string treatment2 = StringHelper::ToString(parkingTM);
		string treatment = treatment1 + treatment2;//����Ÿ�ʽ��ZC+����  ����  XL+����
		string workStatus = GetArriveStatusByWorkType(workType);
		SQL4Parking::UpdParkingWorkStautsInfo(targetParkingNO, treatment, workStatus, workType, carNO, carType);
		
		//3.����װ��ж��������Ϣ�������� UACS_PARKING_MAT_INFO  
		//����ţ�ͣ��λ�ţ����ţ��ƻ���Դ���ƻ��ţ��Ӽƻ��ţ����ϴ��룬�����룬��ҵ���ͣ����λ�ã�����λ�ã��Ƿ����=1��δ��ɣ�
		//�����ϸ�Ż�ȡ�����ϴ���͸�����
		string matCode = "";
		string compCode = "";
		long matWgt = DF_INT_NULL;
		if (false == SQL4Parking::SelGridInfoByGridNO(targetGridNO, matCode, compCode, matWgt))
		{
			log.Info()<<"carNO = "<<carNO<<" SelGridInfoByGridNO is ERROR  , return.................."<<endl;
			return;
		}
		string fromPlace = "";
		string toPlace = "";
		string finishFlag = "1";
		GetFromToPlaceByWorkType(workType, targetGridNO, targetParkingNO, fromPlace, toPlace);
		//�����UACS_PARKING_MAT_INFO
		SQL4Parking::InsParkingMatInfo(treatment, 
																	targetParkingNO, 
																	carNO, 
																	planSrc, 
																	planNO, 
																	planDetailID, 
																	matCode, 
																	compCode, 
																	workType, 
																	fromPlace, 
																	toPlace, 
																	finishFlag);

		//֪ͨ�ϸ����ϵͳ��Ϣ�� ���ţ�Ŀ���ϸ�� , ��ҵ���ͣ�worktype��
		//���ϸ����ϵͳ���ͳ�������Ŀ���ϸ����
		string msgData = carNO + "," + targetGridNO + "," + workType;
		MsgWG01 handler;
		handler.HandleMessage(msgData);

		


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

string EventGateHandler::GetArriveStatusByWorkType(string workType)
{
	string functionName="EventGateHandler :: GetArriveStatusByWorkType()";
	LOG log(functionName, AUTO_CATCH_PID);
	string workStatus = "";

	try
	{		
		if (workType == "ZC")
		{
			workStatus = "201";
		}
		if (workType == "XL")
		{
			workStatus = "301";
		}
		return workStatus;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return workStatus;
}

void EventGateHandler::GetFromToPlaceByWorkType(string workType, string gridNO, string parkingNO, string& fromPlace, string& toPlace)
{
	string functionName="EventGateHandler :: GetFromToPlaceByWorkType()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{		
		if (workType == "ZC")
		{
			fromPlace = gridNO;
			toPlace = parkingNO;
		}
		if (workType == "XL")
		{
			fromPlace = parkingNO;
			toPlace = gridNO;
		}
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
}

bool EventGateHandler::EVTagSnd(string tagName, string tagValue)
{
	string functionName="EventGateHandler :: EVTagSnd()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		iPlature::TAGVALUEMAP tagPairs;
		log.Info()<<"eventPut tagName="<<tagName<<"    tagValue="<<tagValue<<endl;
		Tag::GetInst().EventPut(tagPairs,tagName,tagValue);
		ret=true;
		return ret;
	}
	catch(...)
	{
		log.Debug()<<"EVTagSnd  error..........."<<endl;
	}
	return ret;
}

string EventGateHandler::workTypeConvert(string workType)
{
	string functionName="EventGateHandler :: workTypeConvert()";
	LOG log(functionName, AUTO_CATCH_PID);

	string workTypeL3 = "";
	try
	{
		if (workType == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			workTypeL3 = "1";
		}
		else if (workType == CarPlanBandInfo::WORK_TYPE_XL)
		{
			workTypeL3 = "2";
		}		
	}
	catch(...)
	{
		log.Debug()<<"workTypeConvert  error..........."<<endl;
	}
	return workTypeL3;
}