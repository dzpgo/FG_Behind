#include "MsgGW01.h"
#include "SQL4Parking.h"

using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;

MsgGW01*  MsgGW01::m_pMsgGW01 = NULL;

MsgGW01::MsgGW01() 
{

}

MsgGW01 :: ~MsgGW01(void)
{
	delete m_pMsgGW01;
}

MsgGW01* MsgGW01::getInstance(void)
{
	if (m_pMsgGW01 == NULL)
	{
		m_pMsgGW01 = new MsgGW01;
	}
	return m_pMsgGW01;
}

string MsgGW01 :: getMsgID()
{
	return m_strMsgId;
}
void MsgGW01 :: setMsgID(string theVal)
{
	m_strMsgId = theVal;
}


ByteSeq MsgGW01::HandleMessage(const SmartData& sd)
{
	string functionName = "MsgGW01 :: HandleMessage()";
	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{
		string msgID = sd["MSGID"].toString();
		string parkingNO = sd["PARKING_NO"].toString();
		string truckNO = sd["TRUCK_NO"].toString();
		string flag = sd["FLAG"].toString();

		log.Info()<<"MsgID = "<<msgID<<" , ParkingNO = "<<parkingNO<<" , TruckNO = "<<truckNO<<" , Flag = "<<flag<<endl;
		
		//�����ݽ������ݿ�����
		HandleData(sd);


	}
	catch(iDA::Exception &x)
	{
		try
		{
			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage = stdex.what();
		string msg = functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;
}

void MsgGW01::HandleData(SmartData sd)
{
	string functionName="MsgGW01 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string parkingNO = sd["PARKING_NO"].toString();//ͣ��λ��/��̨��
		string truckNO = sd["TRUCK_NO"].toString();//������
		string flag = sd["FLAG"].toString();//����/�뿪���    1������    2���뿪

		string workType = "";
		string carType = "";
		string planSrc = "";
		string planNO = "";
		long planDetailID = 0;
		//���� ������ ���ﻹ���뿪 ���벻ͬ��ҵ���߼�����
		if (flag == "1")//��������
		{			
			if (false == CarArriveParking(parkingNO, truckNO, workType, carType, planSrc, planNO))
			{
				log.Info()<<"CarArriveParking  FAILED, parkingNO = "<<parkingNO<<" , truckNO = "<<truckNO<<" , return ...................."<<endl;
				return;
			}
			//����EV֪ͨ��ָ��ģ��:EVname=EV_PARKING_CAR_ARRIVE_PK  ��ʽ=��ҵ����,������,����,ͣ��λ��
			string tagName = "EV_PARKING_CAR_ARRIVE_PK";
			string tagValue = workType + "," + carType + "," + truckNO + "," + parkingNO;
			EVTagSnd(tagName, tagValue);

			if (planSrc == "L3")
			{
				//����EV֪ͨL3���� HCP411 
				string tagName = "EV_L3MSG_SND_HCP411";
				string tagValue = "I," + planNO + "," + workTypeConvert(workType) + ",2," + iDA::DateTime::Now().ToString();
				EVTagSnd(tagName, tagValue);
			}
			
		}

		if (flag == "2")//�����뿪
		{
			if (false == CarLeaveParking(parkingNO, truckNO, workType, carType, planSrc, planNO, planDetailID))
			{
				log.Info()<<"CarLeaveParking  FAILED, parkingNO = "<<parkingNO<<" , truckNO = "<<truckNO<<" , return ...................."<<endl;
				return;
			}
			string strPlanDetailID = StringHelper::ToString(planDetailID);
			//����EV֪ͨ��ָ��ģ��:EVname=EV_PARKING_CAR_ARRIVE_PK  ��ʽ=�ƻ���Դ,�ƻ���,�Ӽƻ��ţ�L3�����ڣ�,��ҵ����,������,����,ͣ��λ��
			string tagName = "EV_PARKING_CAR_LEAVE_PK";
			string tagValue = planSrc + "," + planNO + "," + strPlanDetailID + "," + workType + "," + carType + "," + truckNO + "," + parkingNO;
			EVTagSnd(tagName, tagValue);		

			if (planSrc == "L3")
			{
				//����EV֪ͨL3���� HCP411 
				string tagName = "EV_L3MSG_SND_HCP411";
				string tagValue = "I," + planNO + "," + workTypeConvert(workType) + ",3," + iDA::DateTime::Now().ToString();
				EVTagSnd(tagName, tagValue);
			}

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


bool MsgGW01::CarArriveParking(string parkingNO, string truckNO, string& workType, string& carType, string& planSrc, string& planNO)
{
	string functionName="MsgGW01 :: CarArriveParking()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		//�Ƿ���ָ����Ŀ���ϸ�Ŷ�Ӧ��ͣ��λ
		//���ݳ����źͽ����Ǵӳ����ƻ�����Ϣ���л�ȡ��Ŀ��ͣ��λ��
		string targetPakringNO = "";
		string tempWorkType = "";
		string tempCarType = "";
		string tempPlanSrc = "";
		string tempPlanNO = "";
		long tempPlanDetailID = 0;
		if (false == SQL4Parking::SelParkingNOByCarNOFlag(truckNO, 
																										CarPlanBandInfo::ENTER_YARD_2_YES, 
																										targetPakringNO, 
																										tempWorkType, 
																										tempCarType, 
																										tempPlanSrc, 
																										tempPlanNO, 
																										tempPlanDetailID) )
		{
			log.Info()<<"SelParkingNOByCarNOFlag  error..................return............."<<endl;
			return ret;
		}

		workType = tempWorkType;
		carType = tempCarType;
		planSrc = tempPlanSrc;
		planNO = tempPlanNO;

		log.Info()<<"SelParkingNOByCarNOFlag  ok, targetPakringNO = "<<targetPakringNO<<endl;
		if (parkingNO != targetPakringNO)
		{
			//����ָ��ͣ��λ�� �˳�
			log.Info()<<"parkingNO = "<<parkingNO<<", targetParkingNO =  "<<targetPakringNO<<", not SAME, error..................return............."<<endl;
			return ret;
		}
		//ͣ��λ�Ƿ����
		string workStatus = "";
		string pkWorkType = "";
		string pkCarNO = "";
		if (false == SQL4Parking::SelStatusByParkingNO(parkingNO, workStatus, pkWorkType, pkCarNO))
		{
			log.Info()<<"parkingNO = "<<parkingNO<<",  not FIND , SelStatusByParkingNO  error..................return............."<<endl;
			return ret;
		}
		log.Info()<<"parkingNO = "<<parkingNO<<"  , pkWorkType = "<<pkWorkType<<" , pkCarNO = "<<pkCarNO<<endl;

		bool bFlag = (pkWorkType == workType && pkCarNO == truckNO);
		if (bFlag == false)
		{
			log.Info()<<"parkingNO = "<<parkingNO<<" not ready for this worktype or this car ........return....."<<endl;
			return ret;
		}
		//����ͣ��λ״̬����ͣ��λ״̬����Ϊ�������Ҫ������װ������  ����  ж�ϳ�����
		workStatus = GetWorkStatusByWorkType(tempWorkType);
		SQL4Parking::UpdParkingStatus(parkingNO, workStatus);
		ret = true;
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
	return ret;
}

//��Ҫ������װ���뿪����ж���뿪�����״̬��ͣ��λ״̬���л�ȡ
//�����װ���뿪,����³�λ״̬Ϊ���У�ָ֪ͨ��ģ��,  ɾ�������ƻ�����Ϣ��  ����UACS_PARKING_MAT_INFO ������ �е� FINISH_FLAGΪ 2�������
//�����ж���뿪������³�λ״̬Ϊж�ϳ��뿪��ָ֪ͨ��ģ�飨ָ��ģ���յ�����L3����״̬����,L3���ؿ��Թ���źź�,������ָ��������ѣ�
bool MsgGW01::CarLeaveParking(string parkingNO, string truckNO, string& workType, string& carType, string& planSrc, string& planNO, long& planDetailID)
{
	string functionName="MsgGW01 :: CarLeaveParking()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		string treatmentNO = "";
		string workStatus = "";
		string wmsWorkType = "";
		string wmsCarNO = "";
		string wmsCarType = "";
		if (false == SQL4Parking::SelAllFromParkingWorkStatus(parkingNO, treatmentNO, workStatus, wmsWorkType, wmsCarNO, wmsCarType))
		{
			log.Info()<<"SelAllFromParkingWorkStatus  error..................return............."<<endl;
			return ret;
		}
		//���ͣ��λ������ǿ���״̬����ʱ�ĳ��뿪��Ч��������ʾ
		if (workStatus == "100")
		{
			log.Info()<<"last  workStatus == 100��car leave parking is   error..................return............."<<endl;
			return ret;
		}
		//����յ��ĳ��뿪�ź��еĳ��ź�֮ǰ��ĳ��Ų�һ�£��������뿪��������ʾ
		if (truckNO != wmsCarNO)
		{
			log.Info()<<"truckNO != wmsCarNO, truckNO ="<<truckNO<<" , wmsCarNO = "<<wmsCarNO<<" ,   error..................return............."<<endl;
			return ret;
		}

		//�ӳ����󶨱��л�ȡ�ƻ��� �ƻ���Դ
		SQL4Parking::SelParkingNOByCarNOFlag(truckNO, CarPlanBandInfo::ENTER_YARD_2_YES, parkingNO, workType, carType, planSrc, planNO, planDetailID);

		workType = wmsWorkType;
		carType = wmsCarType;
		//�����װ������뿪��
		if (workType == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//����ͣ��λ״̬��Ϊ����
			SQL4Parking::InitParkingWorkStauts(parkingNO);
			//ɾ�������ƻ�����Ϣ���еļ�¼
			SQL4Parking::DelCarPlanInfoByCarNO(truckNO, carType, workType);
			//����UACS_PARKING_MAT_INFO������FINISH_FLAGΪ����� =2 
			SQL4Parking::UpdParkingMatInfoFinish(treatmentNO);
			ret = true;
			return ret;
		}

		//�����ж����ɳ��뿪
		if (workType == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//����ͣ��λ״̬��Ϊ ж����ɳ��뿪
			SQL4Parking::UpdParkingStatusByValue(parkingNO, "303");
			//���³����ƻ�����Ϣ���м�¼Ϊ  enterFlag = 3  ж����ɳ��뿪
			SQL4Parking::UpdEnterFlag2XLLeave(truckNO, carType, workType, "2", "3");
			//�� UACS_PARKING_MAT_INFO ������ �������� ��Ϊ��ʱֻ��ж����ɣ���û����ɹ�����  �����ҵ�������
			ret = true;
			return ret;
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
	return ret;
}

string MsgGW01::GetWorkStatusByWorkType(string workType)
{
	string functionName="MsgGW01 :: GetWorkStatusByWorkType()";
	LOG log(functionName, AUTO_CATCH_PID);
	string workStatus = "";

	try
	{		
		if (workType == "ZC")
		{
			workStatus = "202";
		}
		if (workType == "XL")
		{
			workStatus = "302";
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


bool MsgGW01::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgGW01 :: EVTagSnd()";
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


string MsgGW01::workTypeConvert(string workType)
{
	string functionName="MsgGW01 :: workTypeConvert()";
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