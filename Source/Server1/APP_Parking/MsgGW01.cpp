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
		
		//对数据进行数据库表操作
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
		string parkingNO = sd["PARKING_NO"].toString();//停车位号/月台号
		string truckNO = sd["TRUCK_NO"].toString();//卡车号
		string flag = sd["FLAG"].toString();//到达/离开标记    1：到达    2：离开

		string workType = "";
		string carType = "";
		string planSrc = "";
		string planNO = "";
		long planDetailID = 0;
		//根据 车辆是 到达还是离开 进入不同的业务逻辑处理：
		if (flag == "1")//车辆到达
		{			
			if (false == CarArriveParking(parkingNO, truckNO, workType, carType, planSrc, planNO))
			{
				log.Info()<<"CarArriveParking  FAILED, parkingNO = "<<parkingNO<<" , truckNO = "<<truckNO<<" , return ...................."<<endl;
				return;
			}
			//发送EV通知给指令模块:EVname=EV_PARKING_CAR_ARRIVE_PK  格式=作业类型,车类型,车号,停车位号
			string tagName = "EV_PARKING_CAR_ARRIVE_PK";
			string tagValue = workType + "," + carType + "," + truckNO + "," + parkingNO;
			EVTagSnd(tagName, tagValue);

			if (planSrc == "L3")
			{
				//发送EV通知L3电文 HCP411 
				string tagName = "EV_L3MSG_SND_HCP411";
				string tagValue = "I," + planNO + "," + workTypeConvert(workType) + ",2," + iDA::DateTime::Now().ToString();
				EVTagSnd(tagName, tagValue);
			}
			
		}

		if (flag == "2")//车辆离开
		{
			if (false == CarLeaveParking(parkingNO, truckNO, workType, carType, planSrc, planNO, planDetailID))
			{
				log.Info()<<"CarLeaveParking  FAILED, parkingNO = "<<parkingNO<<" , truckNO = "<<truckNO<<" , return ...................."<<endl;
				return;
			}
			string strPlanDetailID = StringHelper::ToString(planDetailID);
			//发送EV通知给指令模块:EVname=EV_PARKING_CAR_ARRIVE_PK  格式=计划来源,计划号,子计划号（L3不存在）,作业类型,车类型,车号,停车位号
			string tagName = "EV_PARKING_CAR_LEAVE_PK";
			string tagValue = planSrc + "," + planNO + "," + strPlanDetailID + "," + workType + "," + carType + "," + truckNO + "," + parkingNO;
			EVTagSnd(tagName, tagValue);		

			if (planSrc == "L3")
			{
				//发送EV通知L3电文 HCP411 
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
		//是否是指定的目的料格号对应的停车位
		//根据车辆号和进入标记从车辆计划绑定信息表中获取的目的停车位号
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
			//不是指定停车位号 退出
			log.Info()<<"parkingNO = "<<parkingNO<<", targetParkingNO =  "<<targetPakringNO<<", not SAME, error..................return............."<<endl;
			return ret;
		}
		//停车位是否空闲
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
		//更新停车位状态表：将停车位状态更新为：车到达，要区分是装车到达  还是  卸料车到达
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

//需要区分是装车离开还是卸料离开，这个状态从停车位状态表中获取
//如果是装车离开,则更新车位状态为空闲，通知指令模块,  删除车辆计划绑定信息表  更新UACS_PARKING_MAT_INFO 履历表 中的 FINISH_FLAG为 2：已完成
//如果是卸料离开，则更新车位状态为卸料车离开，通知指令模块（指令模块收到后，向L3发送状态电文,L3返回可以归堆信号后,再生成指令启动归堆）
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
		//如果停车位本身就是空闲状态，此时的车离开无效，报警提示
		if (workStatus == "100")
		{
			log.Info()<<"last  workStatus == 100，car leave parking is   error..................return............."<<endl;
			return ret;
		}
		//如果收到的车离开信号中的车号和之前存的车号不一致，不允许车离开，报警提示
		if (truckNO != wmsCarNO)
		{
			log.Info()<<"truckNO != wmsCarNO, truckNO ="<<truckNO<<" , wmsCarNO = "<<wmsCarNO<<" ,   error..................return............."<<endl;
			return ret;
		}

		//从车辆绑定表中获取计划号 计划来源
		SQL4Parking::SelParkingNOByCarNOFlag(truckNO, CarPlanBandInfo::ENTER_YARD_2_YES, parkingNO, workType, carType, planSrc, planNO, planDetailID);

		workType = wmsWorkType;
		carType = wmsCarType;
		//如果是装车完成离开：
		if (workType == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			//更新停车位状态表为空闲
			SQL4Parking::InitParkingWorkStauts(parkingNO);
			//删除车辆计划绑定信息表中的记录
			SQL4Parking::DelCarPlanInfoByCarNO(truckNO, carType, workType);
			//更新UACS_PARKING_MAT_INFO履历表FINISH_FLAG为已完成 =2 
			SQL4Parking::UpdParkingMatInfoFinish(treatmentNO);
			ret = true;
			return ret;
		}

		//如果是卸料完成车离开
		if (workType == CarPlanBandInfo::WORK_TYPE_XL)
		{
			//更新停车位状态表为 卸料完成车离开
			SQL4Parking::UpdParkingStatusByValue(parkingNO, "303");
			//更新车辆计划绑定信息表中记录为  enterFlag = 3  卸料完成车离开
			SQL4Parking::UpdEnterFlag2XLLeave(truckNO, carType, workType, "2", "3");
			//对 UACS_PARKING_MAT_INFO 履历表 不做操作 因为此时只是卸料完成，还没有完成归堆入库  因此作业不算完成
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