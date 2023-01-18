#pragma once
#include "ACTION_COMMON_FUNCTION.h"

#include "MsgUS01.h"
#include "MsgUS02.h"

using namespace Monitor;


//2018.7.1 zhangyuhong add
//定义WMS行车控制模块的报警tag点名称
//由于要区分行车号，所以只定义后缀部分，前缀部分由行车好填补
const string ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS = "_WMSCraneAlarm";

//2018.7.1 zhangyuhong add
//WMS行车控制的报警代码定义一览
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_0 = "0";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8003 = "8003";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8004 = "8004";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8005 = "8005";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8006 = "8006";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8007 = "8007";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8008 = "8008";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8009 = "8009";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8010 = "8010";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8011 = "8011";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8012 = "8012";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8013 = "8013";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8014 = "8014";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8015 = "8015";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8016 = "8016";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8017 = "8017";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8018 = "8018";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8019 = "8019";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8023 = "8023";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8024 = "8024";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8025 = "8025";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8026 = "8026";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8027 = "8027";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8028 = "8028";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8029 = "8029";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8030 = "8030";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8031 = "8031";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8032 = "8032";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8033 = "8033";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8034 = "8034";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8035 = "8035";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8036 = "8036";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8037 = "8037";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8038 = "8038";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8039 = "8039";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8040 = "8040";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8041 = "8041";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8042 = "8042";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8043 = "8043";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8044 = "8044";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8045 = "8045";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8046 = "8046";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8047 = "8047";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8048 = "8048";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8049 = "8049";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8050 = "8050";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8051 = "8051";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8052 = "8052";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8053 = "8053";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8054 = "8054";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8055 = "8055";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8056 = "8056";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8057 = "8057";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8058 = "8058";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8101 = "8101";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8102 = "8102";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8103 = "8103";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8104 = "8104";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8105 = "8105";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8106 = "8106";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8107 = "8107";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8108 = "8108";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8109 = "8109";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8110 = "8110";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8111 = "8111";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8112 = "8112";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8113 = "8113";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8114 = "8114";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8115 = "8115";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8116 = "8116";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8117 = "8117";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8118 = "8118";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8201 = "8201";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8202 = "8202";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8203 = "8203";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8204 = "8204";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8205 = "8205";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8206 = "8206";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8207 = "8207";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8301 = "8301";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8302 = "8302";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8303 = "8303";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8304 = "8304";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8305 = "8305";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8306 = "8306";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8307 = "8307";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8308 = "8308";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8121 = "8121";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8122 = "8122";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8123 = "8123";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8124 = "8124";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8125 = "8125";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8126 = "8126";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8127 = "8127";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8128 = "8128";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8129 = "8129";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8130 = "8130";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8131 = "8131";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8132 = "8132";

const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8401 = "8401";
const string ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8402 = "8402";


ACTION_COMMON_FUNCTION :: ACTION_COMMON_FUNCTION(void)
{

}



ACTION_COMMON_FUNCTION :: ~ACTION_COMMON_FUNCTION(void)
{
	


}




bool ACTION_COMMON_FUNCTION :: CustomOfficer_ForAllActions_1	(string craneNO,
																																string bayNO,
																																OrderCurrentBase orderCurrent, 
																																CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: customOfficer_ForAllActions_1()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		
		if( cranePLCStatus.getCraneNO() != craneNO    || 
			orderCurrent.getCraneNO() != craneNO ||
			orderCurrent.getBayNO() != bayNO  )
		{

			log.Error()<<"  craneNo或BayNo与当前不匹配！不能执行指令 ！！！返回false！"<<endl;
			ret=false;
			return  ret;
		}
		else
		{
			log.Debug()<<" craneNo或BayNo与当前匹配！可执行指令 ！！！返回true！"<<endl;
			ret=true;
			return ret;
		}
	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;
			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}
		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return ret;
}


//
bool ACTION_COMMON_FUNCTION :: CustomOfficer_ForAllActions_2	(string craneNO,
																													string bayNO,
																													CraneEvadeRequestBase craneEvadeRequest, 
																													CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: CustomOfficer_ForAllActions_2()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		if( cranePLCStatus.getCraneNO() != craneNO    || 
			craneEvadeRequest.getTargetCraneNO() != craneNO
			)
		{

			log.Error()<<"  craneNo与当前不匹配！不能执行指令 ！！！返回false！"<<endl;
			ret=false;
			return  ret;
		}
		else
		{
			log.Debug()<<" craneNo与当前匹配！可执行指令 ！！！返回true！"<<endl;
			ret=true;
			return ret;
		}

		
	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}




//custom offiecer------ to check auto mode and ready
bool ACTION_COMMON_FUNCTION :: CustomOffice_Is_Auto_Ready_AskPlan	(string craneNO,
																																CranePLCStatusBase cranePLCStatus)
{
	bool ret=true;

	string functionName="ACTION_COMMON_FUNCTION :: CustomOffice_Is_Auto_Ready_AskPlan()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
			log.Debug()<<"----------------------------------- check crane status  ---------------------------------"<<endl;
			long  controlMode = cranePLCStatus.getControlMode();
			long  ready = cranePLCStatus.getReady();
			long  askPlan = cranePLCStatus.getAskPlan();

			log.Debug()<<"controlMode = "<<controlMode;
			if(controlMode==CranePLCStatusBase::CONTROL_MODE_REMOTE_CONTROL)
			{
				log.Debug()<<"\t REMOTE_CONTROL";
			}
			if(controlMode==CranePLCStatusBase::CONTROL_MODE_DRIVER_CONTROL)
			{
				log.Debug()<<"\t DRIVER_CONTROL";
			}
			if(controlMode==CranePLCStatusBase::CONTROL_MODE_HALF_AUTO)
			{
				log.Debug()<<"\t HALF_AUTO";
			}
			if(controlMode==CranePLCStatusBase::CONTROL_MODE_AUTO)
			{
				log.Debug()<<"\t AUTO";
			}

			log.Debug()<<"\t  ready = "<<ready;
			log.Debug()<<"\t  askPlan = "<<askPlan<<endl;

			//检查顺序：自动模式===>准备好与否===>是否处于请求计划
			if(controlMode!=CranePLCStatusBase::CONTROL_MODE_AUTO)
			{
				ret=false;
			}
			//1：准备好   0：没有准备好
			if(ready!=1)
			{
				ret=false;
			}
			//1：请求计划    0：不请求计划
			if(askPlan!=1)
			{
				ret=false;
			}
			//add bayNo filter
			if(ret==true)
			{
				log.Debug()<<"海关检查通过！返回true！"<<endl;
			}
			else
			{
				log.Debug()<<"海关检查不通过！返回false！"<<endl;
			}
			return ret;
			
	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}


bool ACTION_COMMON_FUNCTION :: Assistant_Is_ZValueArrived(long zCurrent, long zTarget)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_ZValueArrived()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		if (zCurrent >= zTarget)
		{
			ret=true;
		}
		else 
		{
			ret=false;
		}
		return ret;

	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}



//2017.10.1 zhangyuhong add
bool ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceClampArrived(long zCurrnet, long zTarget, string coilUpDown)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceClampArrived()";
	LOG log(functionName, AUTO_CATCH_PID);
	long deltaDistance=100;
	try
	{
		//log.Debug()<<"----------------------------------- Assistant_Is_PlaceClampArrived  ---------------------------------"<<endl;

		if (coilUpDown == "CoilUp")
		{
			deltaDistance = 500;
		}
		else 
		{
			deltaDistance = 1000;
		}
		if( abs(zCurrnet-zTarget) <= deltaDistance) 
		{
			ret=true;
		}
		else 
		{
			ret=false;
		}
		return ret;

	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}



//assistant helper------ to check whether i have arrived the target point
bool ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived	(long xCurrent, long yCurrent, long xTarget, long yTarget)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived()";
	LOG log(functionName, AUTO_CATCH_PID);
    long deltaDistance=100;
	try
	{
			//log.Debug()<<"----------------------------------- Assistant_Is_PlaceArrived  ---------------------------------"<<endl;
			
			if( abs(xCurrent-xTarget) <= deltaDistance  && abs(yCurrent-yTarget) <= deltaDistance ) 
			{
				ret=true;
			}
			else 
			{
				ret=false;
			}
			return ret;
			
	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}


//assistant helper------ to check whether i have arrived the target point
bool ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_By_Distance(long xCurrent, long yCurrent, long xTarget, long yTarget, long xDistance, long yDistance)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_By_Distance()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		if( abs(xCurrent-xTarget) <= xDistance  && abs(yCurrent-yTarget) <= yDistance ) 
		{
			ret=true;
		}
		else 
		{
			ret=false;
		}
		return ret;

	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}

//assistant helper------ to check whether i have arrived the target point
//bool ACTION_COMMON_FUNCTION :: Assistant_Is_PLC_UpGoal_Is_Order_UpGoal(CranePLCStatusBase cranePLCStatusCurrent, CraneOrderCurrentBase craneOrderCurrent)
//{
//	bool ret=false;
//
//	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_PLC_UpGoal_Is_Order_UpGoal()";
//	LOG log(functionName, AUTO_CATCH_PID);
//	long deltaDistance = 30;
//	try
//	{
//		if( abs( cranePLCStatusCurrent.getPlanUpX() - craneOrderCurrent.getPlanUpX() ) <= deltaDistance  && 
//			abs(cranePLCStatusCurrent.getPlanUpY() - craneOrderCurrent.getPlanUpY()) <= deltaDistance ) 
//		{
//			ret=true;
//		}
//		else 
//		{
//			ret=false;
//		}
//		return ret;
//
//	}
//	catch(iDA::Exception &x)
//	{
//		try
//		{
//			ret=false;
//
//			CDataAccess::GetInstance()->m_DBCon.Rollback();
//		}
//		catch(iDA::Exception &)
//		{
//		}
//
//		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
//	}
//	catch (std::exception& stdex)
//	{
//		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
//	}
//	catch (...)
//	{
//		ret=false;
//
//		log.Debug()<<functionName<<"   error:"<<endl;
//	}
//
//	return ret;
//}

bool ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_X_By_Distance	(long xCurrent, long xTarget, long xDistance)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_X_By_Distance()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		if( abs(xCurrent-xTarget) <= xDistance ) 
		{
			ret=true;
		}
		else 
		{
			ret=false;
		}
		return ret;

	}	
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return ret;
}

bool ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_Y_By_Distance	(long yCurrent, long yTarget, long yDistance)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_Y_By_Distance()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		if( abs(yCurrent-yTarget) <= yDistance ) 
		{
			ret=true;
		}
		else 
		{
			ret=false;
		}
		return ret;

	}	
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return ret;
}



bool ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_X	(long xCurrent, long xTarget)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_X()";
	LOG log(functionName, AUTO_CATCH_PID);
	long deltaDistance=100;
	try
	{
		if( abs(xCurrent-xTarget) <= deltaDistance ) 
		{
			ret=true;
		}
		else 
		{
			ret=false;
		}
		return ret;

	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}


bool ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_Y	(long yCurrent, long yTarget)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_Is_PlaceArrived_Y()";
	LOG log(functionName, AUTO_CATCH_PID);
	long deltaDistance=100;
	try
	{
		if( abs(yCurrent-yTarget) <= deltaDistance ) 
		{
			ret=true;
		}
		else 
		{
			ret=false;
		}
		return ret;

	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}






//assistant helper------ to create and download a crane moving order 
bool ACTION_COMMON_FUNCTION :: Assistant_DownLoad_Moving_Order	(string craneNO, long orderNO, long currentX, long currentY, long targetX, long targetY, long hasCoil)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_DownLoad_Moving_Order()";
	LOG log(functionName, AUTO_CATCH_PID);
    long deltaDistance=50;
	try
	{
			CranePLCOrderBase  msg01_CranePLC_Order;
			//2017.11.22 zhangyuhong add
			//19  设置短指令 0：不执行   1：执行
			//由于改了UC01的通信接口，增加了短指令字段，所以添加短指令初始值
			msg01_CranePLC_Order.setShortCmd(1);


			//1.行车号
			msg01_CranePLC_Order.setCraneNO( craneNO );
			//2.指令号
			msg01_CranePLC_Order.setOrderID( orderNO );	
			
			
			long canReachX=CranePLCOrderBase::PLC_INT_NULL;

			
			bool judgeBeforeMoving=JUDGE_BEFORE_MOVING::judge(orderNO, craneNO, currentX , targetX ,  canReachX);

			if(judgeBeforeMoving==false)
			{
				log.Debug()<<"judgeBeforeMoving = false！避让请求（Evade Request）在此情况下需要发送！......"<<endl;
				EvadeRequestSender::getInstance()->senderByMovingAction(craneNO,orderNO,currentX, targetX);
				log.Debug()<<"避让请求（Evade Request）已经发送完毕！......"<<endl;
				log.Debug()<<"移动条件还不具备（Not OK），进程返回false...行车当前静止不动（无移动指令下发）..."<<endl;
				ret=false;
				return ret;
			}
			if(judgeBeforeMoving==true)
			{
				log.Debug()<<"judgeBeforeMoving = true！移动条件具备（Is OK）！进程将进行路径规划（Arrange Route）！"<<endl;
				log.Debug()<<"canReachX="<<canReachX<<endl;
				log.Debug()<<"行车在路径规划前已经做好移动准备, 现在需要准备在相反方向发送行车避让取消命令（写相关Tag点）......"<<endl;
				log.Debug()<<"craneNO="<<craneNO<<" currentX="<<currentX<<" targetX="<<canReachX<<endl;
				EvadeCancelSender::senderByMovingAction(craneNO,currentX,canReachX);
				log.Debug()<<"避让取消命令发送成功！EvadeCancelSender::senderByMovingAction(craneNO,currentX,canReachX)......"<<endl;

				if(canReachX!=targetX)
				{
					log.Debug()<<"judgeBeforeMoving==true ==> canReachX!=targetX  行车还不能到达目标点，避让请求需要发送........"<<endl;
					EvadeRequestSender::getInstance()->senderByMovingAction(craneNO,orderNO,currentX, targetX);
					log.Debug()<<"避让请求需要发送成功！........."<<endl;
				}
			}

			


			
			//log.Debug()<<"........................................................................................now begin to arrange the route..................................................................................................................."<<endl;
			log.Debug()<<"........................................................................................开始进行路径规划（Arrange Route）..................................................................................................................."<<endl;

			//arrange the route from current pos to special point
			vector<RouteStepPointBase> vectorRoutePoints;
			log.Debug()<<"  ..... 调用路径规划算法：SafetyArea_Bay::getInstance()->arrangeRoute() ......" <<endl;

			bool startInRed = false;
			SafetyArea_Bay::getInstance()->arrangeRoute(currentX, currentY,  canReachX , targetY, vectorRoutePoints, startInRed);
			log.Debug()<<"路径规划算法计算完成............." <<endl;
			log.Debug()<<"计算出的路径点数量：vectorRoutePoints.size  = "<< vectorRoutePoints.size() <<endl;

			//log.Debug()<<"--------------- move to saddle position first step point -------------- "<<endl;
			log.Debug()<<"--------------- 移动到鞍座位置的起始 Step Point -------------- "<<endl;
			log.Debug()<<"Route Start X = "<< vectorRoutePoints[0].getX();
			log.Debug()<<"\t Route Start Y = "<< vectorRoutePoints[0].getY() <<endl;
			log.Debug()<<"------------------------------- -------------- "<<endl;

			

//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************

			

		   //the first one is the current point and then there are route steps.

			//2017.9.19  简化版。直接将指令里的目标X/Y坐标作为到达坐标

			/*
			vector<RouteStepPointBase> vectorRoutePoints;

			RouteStepPointBase stepPoint1;
			stepPoint1.setX(currentX);
			stepPoint1.setY(currentY);
			stepPoint1.setFlagReachFinalTarget(false);
			vectorRoutePoints.push_back(stepPoint1);
			
			RouteStepPointBase stepPoint2;
			stepPoint2.setX(targetX);
			stepPoint2.setY(targetY);
			stepPoint2.setFlagReachFinalTarget(true);
			vectorRoutePoints.push_back(stepPoint2);		
			*/

			if (vectorRoutePoints.size() >= 2    )
			{
				log.Debug()<<".......................下一步的移动 Step Point.........................."<<endl ;
				log.Debug()<<"first step Point_X = "<< vectorRoutePoints[1].getX() ;
				log.Debug()<<"\t first step Point_Y = "<< vectorRoutePoints[1].getY() ;
				log.Debug()<<"\t first step FlagReachFinalTarget = "<< vectorRoutePoints[1].getFlagReachFinalTarget() <<endl;

				if(hasCoil==0)
				{
					msg01_CranePLC_Order.setPlanUpX( vectorRoutePoints[1].getX() );
					msg01_CranePLC_Order.setPlanUpY( vectorRoutePoints[1].getY() );

					
				}
				if(hasCoil==1)
				{
					msg01_CranePLC_Order.setPlanDownX( vectorRoutePoints[1].getX() );
					msg01_CranePLC_Order.setPlanDownY( vectorRoutePoints[1].getY() );

					//
				}
				log.Debug()<<"安全起见，对PlanUpZ  和   PlanDownZ  进行封9处理！"<<endl;
				msg01_CranePLC_Order.setPlanUpZ( CranePLCOrderBase::PLC_INT_NULL );
				msg01_CranePLC_Order.setPlanDownZ( CranePLCOrderBase::PLC_INT_NULL );
			}
			else				//route calcute failed
			{
						//log.Error()<<"can not get the first step so freeze the crane................................ ";
						log.Error()<<"路径规划未能找到下一步 Step Point！对PlanDownX/Y/Z PlanUpX/Y/Z 做封9处理！........................... ";
	                
						msg01_CranePLC_Order.setPlanDownX( CranePLCOrderBase::PLC_INT_NULL );
						msg01_CranePLC_Order.setPlanDownY( CranePLCOrderBase::PLC_INT_NULL );
						msg01_CranePLC_Order.setPlanDownZ( CranePLCOrderBase::PLC_INT_NULL );

						msg01_CranePLC_Order.setPlanUpX( CranePLCOrderBase::PLC_INT_NULL );
						msg01_CranePLC_Order.setPlanUpY( CranePLCOrderBase::PLC_INT_NULL );
						msg01_CranePLC_Order.setPlanUpZ( CranePLCOrderBase::PLC_INT_NULL );

						log.Debug()<<"     craneOrderCurrent 设置  999999  OK！   "<<endl;
			}	

			log.Debug()<<".................. log out craneOrderCurrent ..................."<<endl;

			msg01_CranePLC_Order.logOutValues();   

			// now need to send out the message
			log.Debug()<<"...................................................................."<<endl;
			log.Debug()<<"starting send out the message to crane PLC......................";

			if( MsgEUCR01::getInstance()->SendOutMessage(msg01_CranePLC_Order) )  /***********/  
			{
				log.Debug()<<"..................... sending message  OK !"<<endl;
			}
			else 
			{
				log.Error()<<"..................... sending message ERROR !"<<endl;
			}                   

			//  now out put route result to tag system
			//string tagVal_RoutePoints="";

			//for(vector<RouteStepPointBase>::size_type i=0; i<vectorRoutePoints.size(); i++)
			//{
			//	tagVal_RoutePoints += StringHelper::ToString( vectorRoutePoints[i].getX() );
			//	tagVal_RoutePoints += ",";
			//	tagVal_RoutePoints += StringHelper::ToString( vectorRoutePoints[i].getY() );
			//	tagVal_RoutePoints += ",";
			//	tagVal_RoutePoints += StringHelper::ToString( vectorRoutePoints[i].getFlagReachFinalTarget() );
			//	tagVal_RoutePoints += "|";
			//}
			//log.Debug()<< "  tagVal_RoutePoints = "<<tagVal_RoutePoints <<endl;


			////write tag
			//TAGVALUEMAP Tags;
			//string TagName="";
			//string TagValue="";

			//TagName=craneNO+"_ROUTE_POINTS";
			//TagValue=tagVal_RoutePoints;

			//log.Debug()<< "  tagName = "<<TagName <<endl;
			//log.Debug()<< "  tagVal = "<<TagValue <<endl;
			//
			//log.Debug()<<"write ROUTE_POINTS to tag ......................";

			//Tags.insert( map<string,string>::value_type( TagName , TagValue ) );

			//TAGVALUEMAP TagTimeStamp;
			//Tag::GetInst().MDPut(TagTimeStamp,Tags);	


			//log.Debug()<<"writing tag finished.."<<endl;
			return ret;
			
	}
	catch(iDA::Exception &x)
	{
		try
		{

			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}



//assistant helper------to create and download a coil up order on the sopt
bool ACTION_COMMON_FUNCTION :: Assistant_DownLoad_Coil_Up_Order_On_Spot	(string craneNO, 
																																							 long orderID, 
																																							 long matWeight, 
																																							 long matType, 
																																							 long planUpX, 
																																							 long planUpY, 
																																							 long planUpZ, 
																																							 long upRotateAngleSet)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_DownLoad_Coil_Up_Order_On_Spot()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{

		CranePLCOrderBase  msg01_CranePLC_Order;
		
		//2017.11.22 zhangyuhong add
		//19  设置短指令 0：不执行   1：执行
		//由于改了UC01的通信接口，增加了短指令字段，所以添加短指令初始值
		msg01_CranePLC_Order.setShortCmd(1);

		//1.行车号
		msg01_CranePLC_Order.setCraneNO( craneNO );
		//2.指令号
		msg01_CranePLC_Order.setOrderID( orderID );	

		//物料重量
		msg01_CranePLC_Order.setMatWeight(matWeight);

		//物料类型
		msg01_CranePLC_Order.setMatType(matType);

		log.Debug()<<"........................................................................................now begin to send the message to PLC..................................................................................................................."<<endl;

		//8.起卷X
		msg01_CranePLC_Order.setPlanUpX( planUpX );
		//9.起卷Y
		msg01_CranePLC_Order.setPlanUpY( planUpY );
		//10.起卷Z
		msg01_CranePLC_Order.setPlanUpZ( planUpZ );

		//11.起卷夹钳角度
		msg01_CranePLC_Order.setUpRptateAngleSet( upRotateAngleSet );

		//输出 CranePLCOrderBase 日志
		msg01_CranePLC_Order.logOutValues();	
		
		log.Debug()<<".................starting send out the message......................"<<endl;

		if( MsgEUCR01::getInstance()->SendOutMessage(msg01_CranePLC_Order) )  /* ********* */  
		{
			log.Debug()<<"..................... send out the message  OK ................"<<endl;
		}
		else 
		{
			log.Error()<<"..................... send out the message ERROR ................"<<endl;
		}
			
			return ret;
			
	}
	catch(iDA::Exception &x)
	{
		try
		{

			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}




//assistant helper------to create and download a coil down order on the spot
bool ACTION_COMMON_FUNCTION :: Assistant_DownLoad_Coil_Down_Order_On_Spot	(string craneNO, 
																																								 long orderID, 
																																								 long matWeight, 
																																								 long matType, 
																																								 long planDownX, 
																																								 long planDownY, 
																																								 long planDownZ, 
																																								 long downRotateAngleSet)
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Assistant_DownLoad_Coil_Down_Order_On_Spot()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
			CranePLCOrderBase  msg01_CranePLC_Order;

			//2017.11.22 zhangyuhong add
			//19  设置短指令 0：不执行   1：执行
			//由于改了UC01的通信接口，增加了短指令字段，所以添加短指令初始值
			msg01_CranePLC_Order.setShortCmd(1);


			//1.行车号
			msg01_CranePLC_Order.setCraneNO( craneNO );
			//2.指令号
			msg01_CranePLC_Order.setOrderID(orderID );	

			msg01_CranePLC_Order.setMatWeight(matWeight);

			msg01_CranePLC_Order.setMatType(matType);

			//8.落卷X
			msg01_CranePLC_Order.setPlanDownX( planDownX );
			//9.落卷Y
			msg01_CranePLC_Order.setPlanDownY( planDownY );
			//10.落卷Z
			msg01_CranePLC_Order.setPlanDownZ( planDownZ );

			//11.落关夹钳角度
			msg01_CranePLC_Order.setDownRotateAngleSet( downRotateAngleSet );

			//输出日志
			msg01_CranePLC_Order.logOutValues();


			// now need to send out the message
			log.Debug()<<"...................................................................."<<endl;
			log.Debug()<<".................starting send out the message......................"<<endl;

			if( MsgEUCR01::getInstance()->SendOutMessage(msg01_CranePLC_Order) )  /* ********* */  
			{
				log.Debug()<<"..................... send out the message  OK ................"<<endl;
			}
			else 
			{
				log.Error()<<"..................... send out the message ERROR ................"<<endl;
			}
			
			ret=false;
			return ret;

			
	}
	catch(iDA::Exception &x)
	{
		try
		{

			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}



//Actions list output
bool ACTION_COMMON_FUNCTION :: Action_OutPut_Actions(string craneNO, string tagValue  )
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Action_OutPut_Actions";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		TAGVALUEMAP Tags;
		string TagName=craneNO+"_ACTIONS_LIST";
		Tags.insert(map<string,string>::value_type( TagName , tagValue ) );
		TAGVALUEMAP TagTimeStamp;
		Tag::GetInst().MDPut(TagTimeStamp,Tags);
	}
	catch(iDA::Exception &x)
	{
		try
		{

			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}




//Actions successed list output
bool ACTION_COMMON_FUNCTION :: Action_OutPut_ActionsSuccessed(string craneNO, string tagValue  )
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Action_OutPut_ActionsSuccessed";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		TAGVALUEMAP Tags;

		string TagName=craneNO+"_ACTIONS_SUCCESSED";

		log.Debug()<<"TagName ="<<TagName<<"   tagValue="<<tagValue<<endl;
		Tags.insert(map<string,string>::value_type( TagName , tagValue ) );


		TAGVALUEMAP TagTimeStamp;

		Tag::GetInst().MDPut(TagTimeStamp,Tags);	



			
	}
	catch(iDA::Exception &x)
	{
		try
		{

			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}



//Action stop result output
bool ACTION_COMMON_FUNCTION :: Action_OutPut_StopResult(string craneNO, string tagValue  )
{
	bool ret=false;

	string functionName="ACTION_COMMON_FUNCTION :: Action_OutPut_StopResult";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		TAGVALUEMAP Tags;

		string TagName=craneNO+"_ACTIONS_STOP_RESULT";

		Tags.insert(map<string,string>::value_type( TagName , tagValue ) );


		TAGVALUEMAP TagTimeStamp;

		Tag::GetInst().MDPut(TagTimeStamp,Tags);	



			
	}
	catch(iDA::Exception &x)
	{
		try
		{

			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}


bool ACTION_COMMON_FUNCTION::SetTagValue(string craneNO, string tagNamePart, string tagValue)
{
	bool ret=false;
	string functionName="ACTION_COMMON_FUNCTION::SetTagValue";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		TAGVALUEMAP mapTagValue;
		//TAGNAMEARRAY arryTagName;
		string tagName = craneNO + tagNamePart;
		mapTagValue.insert(map<string,string>::value_type( tagName , tagValue ) );
		TAGVALUEMAP TagTimeStamp;
		Tag::GetInst().MDPut(TagTimeStamp,mapTagValue);	
		ret = true;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return ret;
}

string ACTION_COMMON_FUNCTION::GetTagValue(string craneNO, string tagNamePart)
{
	bool ret=false;
	string functionName="ACTION_COMMON_FUNCTION::GetTagValue";
	LOG log(functionName, AUTO_CATCH_PID);
	string tagValue="";
	try
	{		
		TAGVALUEMAP mapTagValue;
		TAGNAMEARRAY arryTagName;
		string tagName = craneNO + tagNamePart;
		arryTagName.push_back(tagName);
		Tag::GetInst().GetActual(arryTagName, mapTagValue);
		TAGVALUEMAP::iterator key = mapTagValue.find(tagName);
		if(key != mapTagValue.end())  
		{  
			tagValue = key->second;
		}  		
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return tagValue;
}


string ACTION_COMMON_FUNCTION::getTagValue(string tagName)
{
	string functionName = "ACTION_COMMON_FUNCTION :: getTagValue()";
	LOG log(functionName, AUTO_CATCH_PID);
	string tagValue="";
	try
	{
		TAGVALUEMAP mapTagValue;
		TAGNAMEARRAY arryTagName;
		arryTagName.push_back(tagName);
		Tag::GetInst().GetActual(arryTagName, mapTagValue);
		TAGVALUEMAP::iterator key = mapTagValue.find(tagName);
		if(key != mapTagValue.end())  
		{  
			tagValue = key->second;
		}  		
	}
	catch (std::exception& stdex)
	{
		tagValue="";
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		tagValue="";
		log.Debug()<<functionName<<"   error:"<<endl;
	}	
	return tagValue;
}

bool ACTION_COMMON_FUNCTION::setTagValue(string tagName, string tagValue)
{
	bool ret=false;
	string functionName="ACTION_COMMON_FUNCTION::setTagValue";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		TAGVALUEMAP mapTagValue;		
		mapTagValue.insert(map<string,string>::value_type( tagName , tagValue ) );
		TAGVALUEMAP TagTimeStamp;
		Tag::GetInst().MDPut(TagTimeStamp,mapTagValue);	
		ret = true;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		ret=false;
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return ret;
}


bool ACTION_COMMON_FUNCTION::setEVTag(string tagName, string tagValue)
{
	string functionName="ACTION_COMMON_FUNCTION :: setEVTag()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = true;
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
		log.Debug()<<"error..........."<<endl;
	}
	return ret;
}

bool ACTION_COMMON_FUNCTION::setEVTagWithCraneNO(string craneNO, string tagNamePart, string tagValue)
{
	string functionName="ACTION_COMMON_FUNCTION :: setEVTagWithCraneNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = true;
	try
	{
		iPlature::TAGVALUEMAP tagPairs;

		string tagNameWithCraneNO = craneNO + tagNamePart;

		log.Info()<<"eventPut tagName="<<tagNameWithCraneNO<<"    tagValue="<<tagValue<<endl;

		Tag::GetInst().EventPut(tagPairs,tagNameWithCraneNO,tagValue);

		ret=true;
		return ret;
	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return ret;
}


string ACTION_COMMON_FUNCTION::getNeighborCrane( CranePLCStatusBase cranePLCStatusCurrent, long targetX)
{
	string functionName="ACTION_COMMON_FUNCTION :: getNeighborCrane()";
	LOG log(functionName, AUTO_CATCH_PID);
	string neighborCraneNO = DB_STR_NULL;
	try
	{
		string myCraneNO = cranePLCStatusCurrent.getCraneNO();
		//大车X只动 100 以内  认为没动  
		if ( abs( targetX - cranePLCStatusCurrent.getXAct() ) <= 100 )
		{
			neighborCraneNO = DB_STR_NULL;
			return neighborCraneNO;
		}
		if (myCraneNO == "4_7")
		{
			if (targetX > cranePLCStatusCurrent.getXAct())
			{
				neighborCraneNO = "4_6";
			}
			else if (targetX < cranePLCStatusCurrent.getXAct())
			{
			}
		}
		else if (myCraneNO == "4_6")
		{
			if (targetX > cranePLCStatusCurrent.getXAct())
			{
				neighborCraneNO = "4_5";
			}
			else if (targetX < cranePLCStatusCurrent.getXAct())
			{
				neighborCraneNO = "4_7";
			}
		}
		else if (myCraneNO == "4_5")
		{
			if (targetX > cranePLCStatusCurrent.getXAct())
			{
				neighborCraneNO = "4_4";
			}
			else if (targetX < cranePLCStatusCurrent.getXAct())
			{
				neighborCraneNO = "4_6";
			}
		}
		else if (myCraneNO == "4_4")
		{
			if (targetX > cranePLCStatusCurrent.getXAct())
			{
			}
			else if (targetX < cranePLCStatusCurrent.getXAct())
			{
				neighborCraneNO = "4_5";
			}
		}
	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return neighborCraneNO;
}


bool ACTION_COMMON_FUNCTION::canSendMoveAtLastStep(CranePLCStatusBase cranePLCStatusCurrent, long targetX, string neighborCraneNO)
{
	string functionName="ACTION_COMMON_FUNCTION :: canSendMoveAtLastStep()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool  ret = false;

	long safeDistance_19000 = 19000;
	try
	{

		log.Info()<<"myCrane="<<cranePLCStatusCurrent.getCraneNO()<<endl;
		log.Info()<<"cranePLCStatus.getXAct()="<<cranePLCStatusCurrent.getXAct()<<endl;
		log.Info()<<"cranePLCStatus.getYAct()="<<cranePLCStatusCurrent.getYAct()<<endl;
		log.Info()<<"myTargetX = "<<targetX<<endl;
		log.Info()<<"------------------------------------------------------------------------------------------------------------"<<endl;



		//设定每部行车的开行区域，超过此区域直接返回false

		//20191220 zhangyuhong add
		//如果没邻车，说明此车肯定是4-7  或者  4-4 正在靠边 ...........................  而4-7是大车的小坐标方向  暂时不考虑   只考虑4-4可能发出大的坐标
		if (cranePLCStatusCurrent.getCraneNO() == "4_4"  )  //4-4不能发出 > 428000的指令
		{
			if (targetX > 428000 || targetX < 240000)//如果目标位 < 176入口  不执行
			{
				log.Info()<<"4-4 targetX = "<<targetX<<"   >  428000, or  < 240000,  invalid  , not pass, return false..."<<endl;
				ret =false;
				return ret;
			}				
		}
		if (cranePLCStatusCurrent.getCraneNO() == "4_5"  )  //
		{
			if (targetX > 406000 || targetX < 138000)//如果目标位 > C2A的1排 或者 < 175出口  不执行
			{
				log.Info()<<"4-5 targetX = "<<targetX<<"   >  428000, or  < 240000,  invalid  , not pass, return false..."<<endl;
				ret =false;
				return ret;
			}				
		}
		if (cranePLCStatusCurrent.getCraneNO() == "4_6"  )  //
		{
			//对于4-6  重钩情况下不过2号龙门吊的判断
			if (cranePLCStatusCurrent.getHasCoil() == 1)
			{
				if (cranePLCStatusCurrent.getXAct() > 138000 && targetX < 138000 )
				{
					log.Info()<<"4-6 targetX = "<<targetX<<"   <  138000, and xAct > 138000 and hascoil = 1, full clamp pass to PA2 longmendiao  , not pass, return false..."<<endl;
					ret =false;
					return ret;
				}
				if (cranePLCStatusCurrent.getXAct() < 91500 && targetX > 91500 )
				{
					log.Info()<<"4-6 targetX = "<<targetX<<"   <  91500, and xAct > 91500 and hascoil = 1, full clamp pass to PA2 longmendiao  , not pass, return false..."<<endl;
					ret =false;
					return ret;
				}
				if (cranePLCStatusCurrent.getXAct() >= 91500 && cranePLCStatusCurrent.getXAct() <= 138000 )
				{
					log.Info()<<"4-6 xAct  = "<<cranePLCStatusCurrent.getXAct()<<"   >  91500, and xAct < 138000 and hascoil = 1, full clamp in  PA2 longmendiao  , not pass, return false..."<<endl;
					ret =false;
					return ret;
				}
			}
			if (targetX > 326000 || targetX < 25000)//如果目标位 > 1C的7排 或者 < 2C 的 17排  不执行
			{
				log.Info()<<"4-6 targetX = "<<targetX<<"   >  326000, or  < 25000,  invalid  , not pass, return false..."<<endl;
				ret =false;
				return ret;
			}				
		}
		if (cranePLCStatusCurrent.getCraneNO() == "4_7"  )
		{
			if (targetX > 91500 || targetX < 4500)
			{
				log.Info()<<"4-7 targetX = "<<targetX<<"   <  4500, or  > 91500  invalid  , not pass, return false..."<<endl;
				ret =false;
				return ret;					
			}				
		}
		
		if (neighborCraneNO == DB_STR_NULL)
		{
			log.Info()<<"no neighbor crane, return true .... pass"<<endl;
			ret = true;
			return ret;
		}


		//获取相邻车的PLC类 和 其 目标位
		CranePLCStatusBase neighborCranePLCStatus;
		CraneMonitor::getInstance()->getNeighborPLCStatus(neighborCraneNO, neighborCranePLCStatus);
		long neighborTargetX = DB_INT_NULL;

		string tagNameTargetPos = neighborCraneNO + "_TargetPos";
		string tagNameTargetPosRV = neighborCraneNO + "_TargetPosRV";


		string tagvalueNeighborTargetX = ACTION_COMMON_FUNCTION::getTagValue(tagNameTargetPos);
		vector<string> vecTargetPos;
		vecTargetPos= StringHelper::ToVector<string>(tagvalueNeighborTargetX, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		neighborTargetX = StringHelper::ToNumber<long>(vecTargetPos[0]);

		//如果目标封9 且 是自动模式，则取targetPosRV作为目标值
		if (neighborTargetX == DB_INT_NULL && neighborCranePLCStatus.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Info()<<"......neighborTargetX 封9了 = "<<neighborTargetX<<"  ，且是自动模式，准备取tagNameTargetPosRV"<<endl;
			string valueTargetPosCraneNORV = ACTION_COMMON_FUNCTION::getTagValue(tagNameTargetPosRV);
			vector<string> vecTargetPosCraneNORV;
			vecTargetPosCraneNORV= StringHelper::ToVector<string>(valueTargetPosCraneNORV, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
			long nTargetPosCraneNORV = StringHelper::ToNumber<long>(vecTargetPosCraneNORV[0]);
			neighborTargetX = nTargetPosCraneNORV;
			//nTargetPosCraneNO = cranePLCStatusCurrent.getXAct();
			log.Info()<<"......neighborTargetX = "<<neighborTargetX<<endl;

			//neighborTargetX = neighborCranePLCStatus.getXAct();
		}

		if (neighborCranePLCStatus.getControlMode() != CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Info()<<"......邻车非自动 取xAct "<<endl;
			neighborTargetX = neighborCranePLCStatus.getXAct();
			log.Info()<<"......neighborTargetX = "<<neighborTargetX<<endl;
		}

		log.Info()<<"------------------------------------------------------------------------------------------------------------"<<endl;
		log.Info()<<"neighborCraneNO()="<<neighborCranePLCStatus.getCraneNO()<<endl;
		log.Info()<<"neighborCranePLCStatus.getXAct()="<<neighborCranePLCStatus.getXAct()<<endl;
		log.Info()<<"neighborCranePLCStatus.getYAct()="<<neighborCranePLCStatus.getYAct()<<endl;
		log.Info()<<"neighborTargetX="<<neighborTargetX<<endl;

		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-7 you are 4-6 
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_7" && neighborCraneNO == "4_6")
		{
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (targetX >= neighborTargetX)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 going to 4-7, my targetX >= your targetX, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX < neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 going to 4-7, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (targetX >= neighborTargetX)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 going to 4-5, my targetX >= your targetX, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX < neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 going to 4-5, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (targetX >= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 X is not move, my targetX >= your xAct, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX < neighborCranePLCStatus.getXAct() && abs(targetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 X is not move, my targetX < your xAct, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
		}


		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-6 you are 4-7
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_6" && neighborCraneNO == "4_7")
		{
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (targetX <= neighborTargetX)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 going to board, my targetX < your targetX, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX > neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 going to board, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (targetX <= neighborTargetX)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 going to 4-6, my targetX < your targetX, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX > neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 going to 4-6, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (targetX <= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 X is not move, my targetX <= your xAct, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX > neighborCranePLCStatus.getXAct() && abs(targetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 X is not move, my targetX > your xAct, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
		}

		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-6 you are 4-5
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_6" && neighborCraneNO == "4_5")
		{
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (targetX >= neighborTargetX)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 going to 4-6, my targetX > your targetX, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX < neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 going to 4-6, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (targetX >= neighborTargetX)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 going to 4-4, my targetX > your targetX, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX < neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 going to 4-4, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (targetX >= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 X is not move, my targetX >= your xAct, not pass......"<<endl;
					ret = false;
					return ret;
				}
				else if (targetX < neighborCranePLCStatus.getXAct() && abs(targetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 X is not move, my targetX < your xAct, but distance < 19000,  not pass......"<<endl;
					ret = false;
					return ret;
				}
			}
		}

		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-5 you are 4-6
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (cranePLCStatusCurrent.getCraneNO() == "4_5" && neighborCraneNO == "4_6")
			{
				if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
				{
					if (targetX <= neighborTargetX)
					{
						log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 going to 4-7, my targetX < your targetX, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX > neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
					{
						log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 going to 4-7, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
				if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
				{
					if (targetX <= neighborTargetX)
					{
						log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 going to 4-5, my targetX < your targetX, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX > neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
					{
						log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 going to 4-5, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
				if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
				{
					if (targetX <= neighborCranePLCStatus.getXAct())
					{
						log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 X is not move, my targetX <= your xAct, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX > neighborCranePLCStatus.getXAct() && abs(targetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
					{
						log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 X is not move, my targetX > your xAct, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
			}

			//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			//
			//														i am 4-5 you are 4-4
			//
			//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (cranePLCStatusCurrent.getCraneNO() == "4_5" && neighborCraneNO == "4_4")
			{
				if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
				{
					if (targetX >= neighborTargetX)
					{
						log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 going to 4-5, my targetX > your targetX, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX < neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
					{
						log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 going to 4-5, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
				if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
				{
					if (targetX >= neighborTargetX)
					{
						log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 going to board, my targetX > your targetX, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX < neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
					{
						log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 going to board, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
				if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
				{
					if (targetX >= neighborCranePLCStatus.getXAct())
					{
						log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 X is not move, my targetX >= your xAct, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX < neighborCranePLCStatus.getXAct() && abs(targetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
					{
						log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 X is not move, my targetX < your xAct, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
			}

			//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			//
			//														i am 4-4 you are 4-5
			//
			//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (cranePLCStatusCurrent.getCraneNO() == "4_4" && neighborCraneNO == "4_5")
			{
				if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
				{
					if (targetX <= neighborTargetX)
					{
						log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 going to 4-6, my targetX < your targetX, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX > neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
					{
						log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 going to 4-6, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
				if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
				{
					if (targetX <= neighborTargetX)
					{
						log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 going to 4-4, my targetX < your targetX, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX > neighborTargetX && abs(targetX - neighborTargetX) < safeDistance_19000)
					{
						log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 going to 4-4, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
				if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
				{
					if (targetX <= neighborCranePLCStatus.getXAct())
					{
						log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 X is not move, my targetX <= your xAct, not pass......"<<endl;
						ret = false;
						return ret;
					}
					else if (targetX > neighborCranePLCStatus.getXAct() && abs(targetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
					{
						log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 X is not move, my targetX > your xAct, but distance < 19000,  not pass......"<<endl;
						ret = false;
						return ret;
					}
				}
			}

			ret = true;
			return ret;

	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return ret;
}

bool ACTION_COMMON_FUNCTION::findNeighborCrane(CranePLCStatusBase cranePLCStatusCurrent, CranePLCStatusBase cranePLCStatusLast,  string& neighborCraneNO)
{
	string functionName="ACTION_COMMON_FUNCTION :: findNeighborCrane()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{		

		string myCrane = cranePLCStatusCurrent.getCraneNO();
		long XDirectPositive_Current = cranePLCStatusCurrent.getXDirectPositive();
		long XDirectNegative_Current = cranePLCStatusCurrent.getXDirectNegative();

		long XDirectPositive_Last = cranePLCStatusLast.getXDirectPositive();
		long XDirectNegative_Last = cranePLCStatusLast.getXDirectNegative();

		log.Info()<<"XDirectPositive_Current = "<<XDirectPositive_Current<<"		,		XDirectPositive_Last = "<<XDirectPositive_Last<<endl;
		log.Info()<<"XDirectNegative_Current = "<<XDirectNegative_Current<<"		,		XDirectNegative_Last = "<<XDirectNegative_Last<<endl;

		//4-7的邻车查找
		if ( myCrane == "4_7" )
		{
			if (XDirectPositive_Current == 0 && XDirectNegative_Current == 0)//双向都是0 则行车不动  无邻车
			{
				ret = false;
				return ret;
			}
			////20200914 zhangyuhong add
			//增加 上一个状态判断，如果last=1 &&  current=1 才是真正的有方向
			else if (XDirectPositive_Current ==1 && XDirectPositive_Last == 1 &&  XDirectNegative_Current == 0)//4-7正向移动，邻车是4-6
			{
				neighborCraneNO = "4_6";
				ret = true;
				return ret;
			}
			else if (XDirectPositive_Current == 0 && XDirectNegative_Current == 1)//4-7负向移动，无邻车
			{
				ret = false;
				return ret;
			}
		}

		//4-6的邻车查找
		if ( myCrane == "4_6")
		{
			if (XDirectPositive_Current == 0 && XDirectNegative_Current == 0)//双向都是0 则行车不动  无邻车
			{
				ret = false;
				return ret;
			}
			////20200914 zhangyuhong add
			//增加 上一个状态判断，如果last=1 &&  current=1 才是真正的有方向
			else if (XDirectPositive_Current ==1 && XDirectPositive_Last == 1 && XDirectNegative_Current == 0)//4-6正向移动，邻车是4-5
			{
				neighborCraneNO = "4_5";
				ret = true;
				return ret;
			}
			////20200914 zhangyuhong add
			//增加 上一个状态判断，如果last=1 &&  current=1 才是真正的有方向
			else if (XDirectPositive_Current == 0 && XDirectNegative_Current == 1 && XDirectNegative_Last == 1)//4-6负向移动，邻车是4-7
			{
				neighborCraneNO = "4_7";
				ret = true;
				return ret;
			}
		}

		//4-5的邻车查找
		if ( myCrane == "4_5")
		{
			if (XDirectPositive_Current == 0 && XDirectNegative_Current == 0)//双向都是0 则行车不动  无邻车
			{
				ret = false;
				return ret;
			}
			////20200914 zhangyuhong add
			//增加 上一个状态判断，如果last=1 &&  current=1 才是真正的有方向
			else if (XDirectPositive_Current ==1 && XDirectPositive_Last ==1 && XDirectNegative_Current == 0)//4-5正向移动，邻车是4-4
			{
				neighborCraneNO = "4_4";
				ret = true;
				return ret;
			}
			////20200914 zhangyuhong add
			//增加 上一个状态判断，如果last=1 &&  current=1 才是真正的有方向
			else if (XDirectPositive_Current == 0 && XDirectNegative_Current == 1 && XDirectNegative_Last == 1)//4-5负向移动，邻车是4-6
			{
				neighborCraneNO = "4_6";
				ret = true;
				return ret;
			}
		}

		//4-4的邻车查找
		if ( myCrane == "4_4")
		{
			if (XDirectPositive_Current == 0 && XDirectNegative_Current == 0)//双向都是0 则行车不动  无邻车
			{
				ret = false;
				return ret;
			}
			else if (XDirectPositive_Current ==1 && XDirectNegative_Current == 0)//4-4正向移动，无邻车
			{
				ret = false;
				return ret;
			}
			else if (XDirectPositive_Current == 0 && XDirectNegative_Current == 1 && XDirectNegative_Last == 1)//4-4负向移动，邻车是4-5
			{
				neighborCraneNO = "4_5";
				ret = true;
				return ret;
			}
		}
	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return ret;
}




long ACTION_COMMON_FUNCTION::getXdirValue(long xPDir, long xNDir) 
{
	string functionName="ACTION_COMMON_FUNCTION :: getXdirValue()";
	LOG log(functionName, AUTO_CATCH_PID);
	long xDir = DB_INT_NULL;
	try
	{		
		//正向
		if (xPDir == 1 && xNDir == 0)
		{
			xDir = 1;
			return xDir;
		}
		//负向
		else if (xPDir == 0 && xNDir == 1)
		{
			xDir = 2;
			return xDir;
		}
		//不动
		else if (xPDir == 0 && xNDir == 0)
		{
			xDir = 0;
			return xDir;
		}
		else
		{
			return xDir;
		}

	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return xDir;
}




long ACTION_COMMON_FUNCTION::targetXByCraneNO(CranePLCStatusBase cranePLCStatusCurrent)
{
	string functionName="ACTION_COMMON_FUNCTION :: targetXByCraneNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	long targetX = DB_INT_NULL;	
	try
	{
		string craneNO = cranePLCStatusCurrent.getCraneNO();
		

		string tagTargetPosCraneNO = craneNO + "_TargetPos";
		string tagTargetPosCraneNORV = craneNO + "_TargetPosRV";
		
		string valueTargetPosCraneNO = ACTION_COMMON_FUNCTION::getTagValue(tagTargetPosCraneNO);
		vector<string> vecTargetPosCraneNO;
		vecTargetPosCraneNO= StringHelper::ToVector<string>(valueTargetPosCraneNO, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		long nTargetPosCraneNO = StringHelper::ToNumber<long>(vecTargetPosCraneNO[0]);

		log.Info()<<"craneNO = "<<craneNO<<"		nTargetPosCraneNO = "<<nTargetPosCraneNO<<endl;

		//如果自动状态，但是目标targetPos是封9 的 ，说明可能按过复位或自动或停止
		if (nTargetPosCraneNO == DB_INT_NULL && cranePLCStatusCurrent.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Info()<<"......nTargetPosCraneNO 封9了 = "<<nTargetPosCraneNO<<"， 且是自动模式，准备取targetPosRV"<<endl;
			string valueTargetPosCraneNORV = ACTION_COMMON_FUNCTION::getTagValue(tagTargetPosCraneNORV);
			vector<string> vecTargetPosCraneNORV;
			vecTargetPosCraneNORV= StringHelper::ToVector<string>(valueTargetPosCraneNORV, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
			long nTargetPosCraneNORV = StringHelper::ToNumber<long>(vecTargetPosCraneNORV[0]);
			nTargetPosCraneNO = nTargetPosCraneNORV;
			//nTargetPosCraneNO = cranePLCStatusCurrent.getXAct();
			log.Info()<<"......nTargetPosCraneNO = "<<nTargetPosCraneNO<<endl;
		}

		if (cranePLCStatusCurrent.getControlMode() != CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Info()<<"......非自动 取xAct "<<endl;
			nTargetPosCraneNO = cranePLCStatusCurrent.getXAct();
			log.Info()<<"......nTargetPosCraneNO = "<<nTargetPosCraneNO<<endl;
		}

		targetX = nTargetPosCraneNO;


	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return targetX;
}

//20200914 zhangyuhong add
//增加 cranePLCStatusLast 参数
bool ACTION_COMMON_FUNCTION::craneWillCrash(CranePLCStatusBase cranePLCStatusCurrent, CranePLCStatusBase cranePLCStatusLast, long& wrongXDirFlag)
{
	string functionName="ACTION_COMMON_FUNCTION :: craneWillCrash()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	long safeDistance_19000 = 19000;
	wrongXDirFlag = 0;
	try
	{		
		//非自动模式，直接返回false，过滤掉
		if ( cranePLCStatusCurrent.getControlMode() != CranePLCStatusBase::CONTROL_MODE_AUTO )
		{
			log.Info()<<"非自动，不监控，返回false..."<<endl;
			ret = false;
			return ret;
		}

		string neighborCraneNO = DB_STR_NULL;
		bool canFindNeighborCrane = ACTION_COMMON_FUNCTION::findNeighborCrane(cranePLCStatusCurrent, cranePLCStatusLast, neighborCraneNO);

		//没有邻车的，也过滤，返回false
		if ( canFindNeighborCrane == false )
		{
			log.Info()<<"无邻车，不监控，返回false..."<<endl;
			ret = false;
			return ret;
		}

		//以下就是有邻车的情况了  ，说明我车在动，找出我车的目的X  和邻车的 目的X 如果邻车手动，则取其当前xAct
		//邻车的PLC类
		log.Info()<<"进入  craneWillCrash  监控......"<<endl;
		log.Info()<<"my crane is "<<cranePLCStatusCurrent.getCraneNO()<<"		your crane is "<<neighborCraneNO<<endl;
		CranePLCStatusBase neighborCranePLCStatus;
		CraneMonitor::getInstance()->getNeighborPLCStatus(neighborCraneNO, neighborCranePLCStatus);

		long myCraneTargetX = ACTION_COMMON_FUNCTION::targetXByCraneNO(cranePLCStatusCurrent);
		long neighborCraneTargetX = ACTION_COMMON_FUNCTION::targetXByCraneNO(neighborCranePLCStatus);

		log.Info()<<"my crane targetX "<<myCraneTargetX<<"		your crane targetX is "<<neighborCraneTargetX<<endl;

		//20191221 zhangyuhong add
		//如果大车运动方向 与 当前坐标到 目标位 坐标不符 
		//举例：大车正向运动    但是xAct = 100000，  targertX = 80000，这个肯定是错误的

		//目标X 比 实际X 大，但是方向是负向，说明行车还在执行旧的指令  需要切手动干预
		if (myCraneTargetX - cranePLCStatusCurrent.getXAct() > 500 && cranePLCStatusCurrent.getXDirectNegative() == 1)
		{
			log.Info()<<"myCraneTargetX - xAct > 500, but XDirectNegative == 1, return true..."<<endl;
			wrongXDirFlag = 1;
			ret  = true;
			return ret;
		}

		//实际X 比 目标X 大，但是方向是正向，说明行车还在执行旧的指令，发119 
		if ( cranePLCStatusCurrent.getXAct() - myCraneTargetX > 500 && cranePLCStatusCurrent.getXDirectPositive() == 1)
		{
			log.Info()<<"  xAct - myCraneTargetX > 500, but XDirectPositive == 1, return true..."<<endl;
			wrongXDirFlag = 1;
			ret  = true;
			return ret;
		}





		//20200101 zhangyuhong add
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-7 you are 4-6
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_7" && neighborCranePLCStatus.getCraneNO() == "4_6")
		{			
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (myCraneTargetX >= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 going to 4-7, my targetX >= your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 going to 4-7, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (myCraneTargetX >= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 going to 4-5, my targetX >= your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 going to 4-5, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (myCraneTargetX >= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 X is not move, my targetX >= your xAct, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCranePLCStatus.getXAct() && abs(myCraneTargetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-7 going to 4-6 , you are 4-6 X is not move, my targetX < your xAct, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}

			/*if (myCraneTargetX >= neighborCraneTargetX )
			{
				log.Info()<<"my crane 4-7 targetX  >=  your crane 4-6 targetX，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}
			else if ( myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) <= safeDistance_19000 )
			{
				log.Info()<<"my crane 4-7 targetX < your crane 4-6 targetX, but abs(distance) < 19000，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}*/
		}



		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-6 you are 4-7
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_6" && neighborCranePLCStatus.getCraneNO() == "4_7")
		{
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (myCraneTargetX <= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 going to board, my targetX < your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 going to board, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (myCraneTargetX <= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 going to 4-6, my targetX < your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 going to 4-6, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (myCraneTargetX <= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 X is not move, my targetX <= your xAct, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCranePLCStatus.getXAct() && abs(myCraneTargetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-7 , you are 4-7 X is not move, my targetX > your xAct, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}



			/*if (myCraneTargetX <= neighborCraneTargetX )
			{
				log.Info()<<"my crane 4-6 targetX  <=  your crane 4-7 targetX，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}
			else if ( myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) <= safeDistance_19000 )
			{
				log.Info()<<"my crane 4-6 targetX > your crane 4-7 targetX, but abs(distance) < 19000，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}*/
		}

		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-6 you are 4-5
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_6" && neighborCranePLCStatus.getCraneNO() == "4_5")
		{
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (myCraneTargetX >= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 going to 4-6, my targetX > your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 going to 4-6, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (myCraneTargetX >= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 going to 4-4, my targetX > your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 going to 4-4, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (myCraneTargetX >= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 X is not move, my targetX >= your xAct, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCranePLCStatus.getXAct() && abs(myCraneTargetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-6 going to 4-5 , you are 4-5 X is not move, my targetX < your xAct, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}



			/*if (myCraneTargetX >= neighborCraneTargetX )
			{
				log.Info()<<"my crane 4-6 targetX  >=  your crane 4-5 targetX，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}
			else if ( myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) <= safeDistance_19000 )
			{
				log.Info()<<"my crane 4-6 targetX < your crane 4-5 targetX, but abs(distance) < 19000，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}*/
		}

		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-5 you are 4-6
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_5" && neighborCranePLCStatus.getCraneNO() == "4_6")
		{
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (myCraneTargetX <= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 going to 4-7, my targetX < your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 going to 4-7, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (myCraneTargetX <= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 going to 4-5, my targetX < your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 going to 4-5, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (myCraneTargetX <= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 X is not move, my targetX <= your xAct, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCranePLCStatus.getXAct() && abs(myCraneTargetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-5 going to 4-6 , you are 4-6 X is not move, my targetX > your xAct, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}



			/*if (myCraneTargetX <= neighborCraneTargetX )
			{
				log.Info()<<"my crane 4-5 targetX  <=  your crane 4-6 targetX，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}
			else if ( myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) <= safeDistance_19000 )
			{
				log.Info()<<"my crane 4-5 targetX > your crane 4-6 targetX, but abs(distance) < 19000，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}*/
		}

		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-5 you are 4-4
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_5" && neighborCranePLCStatus.getCraneNO() == "4_4")
		{
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (myCraneTargetX >= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 going to 4-5, my targetX > your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 going to 4-5, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (myCraneTargetX >= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 going to board, my targetX > your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 going to board, my targetX < your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (myCraneTargetX >= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 X is not move, my targetX >= your xAct, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX < neighborCranePLCStatus.getXAct() && abs(myCraneTargetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-5 going to 4-4 , you are 4-4 X is not move, my targetX < your xAct, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}




			/*if (myCraneTargetX >= neighborCraneTargetX )
			{
				log.Info()<<"my crane 4-5 targetX  >=  your crane 4-4 targetX，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}
			else if ( myCraneTargetX < neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) <= safeDistance_19000 )
			{
				log.Info()<<"my crane 4-5 targetX < your crane 4-4 targetX, but abs(distance) < 19000，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}*/
		}

		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//
		//														i am 4-4 you are 4-5
		//
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (cranePLCStatusCurrent.getCraneNO() == "4_4" && neighborCranePLCStatus.getCraneNO() == "4_5")
		{
			if (neighborCranePLCStatus.getXDirectPositive() == 0 && neighborCranePLCStatus.getXDirectNegative() == 1)
			{
				if (myCraneTargetX <= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 going to 4-6, my targetX < your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 going to 4-6, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectPositive() == 1 && neighborCranePLCStatus.getXDirectNegative() == 0)
			{
				if (myCraneTargetX <= neighborCraneTargetX)
				{
					log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 going to 4-4, my targetX < your targetX, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) < safeDistance_19000)
				{
					log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 going to 4-4, my targetX > your targetX, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}
			if (neighborCranePLCStatus.getXDirectNegative() == 0 && neighborCranePLCStatus.getXDirectPositive() == 0)
			{
				if (myCraneTargetX <= neighborCranePLCStatus.getXAct())
				{
					log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 X is not move, my targetX <= your xAct, not pass......"<<endl;
					ret = true;
					return ret;
				}
				else if (myCraneTargetX > neighborCranePLCStatus.getXAct() && abs(myCraneTargetX - neighborCranePLCStatus.getXAct()) < safeDistance_19000)
				{
					log.Info()<<"i am 4-4 going to 4-5 , you are 4-5 X is not move, my targetX > your xAct, but distance < 19000,  not pass......"<<endl;
					ret = true;
					return ret;
				}
			}





			/*if (myCraneTargetX <= neighborCraneTargetX )
			{
				log.Info()<<"my crane 4-4 targetX  <=  your crane 4-5 targetX，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}
			else if ( myCraneTargetX > neighborCraneTargetX && abs(myCraneTargetX - neighborCraneTargetX) <= safeDistance_19000 )
			{
				log.Info()<<"my crane 4-4 targetX > your crane 4-5 targetX, but abs(distance) < 19000，will crash ret = true..."<<endl;
				ret = true;
				return ret;
			}*/
		}
	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return ret;
}



void	ACTION_COMMON_FUNCTION::sendStopMsg2CraneCycle(string craneNO, long orderNO, long nCycle)
{
	string functionName="ACTION_COMMON_FUNCTION :: sendStopMsg2CraneCycle()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		CranePLCOrderBase driveCranePLCOrder;
		driveCranePLCOrder.setCraneNO(craneNO);
		driveCranePLCOrder.setOrderID(orderNO);
		driveCranePLCOrder.setShortCmd(100);

		long nCount = 1;
		while(nCount <= nCycle)
		{
			nCount++;
			MsgEUCR01::getInstance()->SendOutMessage(driveCranePLCOrder);
#ifdef WIN32
			Sleep(1000);
#else
			sleep(1);
#endif				
		}		
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}

}


void	ACTION_COMMON_FUNCTION::tryToSendResetMsg(string craneNO)
{
	string functionName="ACTION_COMMON_FUNCTION :: tryToSendResetMsg()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		CranePLCOrderBase resetCranePLCOrder;
		resetCranePLCOrder.setCraneNO(craneNO);
		resetCranePLCOrder.setOrderID(170);
		resetCranePLCOrder.setShortCmd(300);		
		MsgEUCR01::getInstance()->SendOutMessage(resetCranePLCOrder);
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}

}


bool ACTION_COMMON_FUNCTION::SrsScanReqTag4UL01(string orderType, 
																											string craneNO,  
																											string updownFlag, 
																											long scanStartX, 
																											long scanEndX, 
																											long scanStartY, 
																											long scanEndY, 
																											long orderNO, 
																											string areaNO, 
																											CranePLCStatusBase cranePLCStatus, 
																											string& EVTagName, 
																											string& EVTagValue)
{
	string functionName="ACTION_COMMON_FUNCTION :: SrsScanReqTag4UL01()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		EVTagName = "EV_CRANE_UL01";

		string areaType = "";//1-卸料区  2-料格

		//tagvalue格式
		//KEY_MessageNo,KEY_CraneNo,KEY_ActionType,KEY_AreaStartX,KEY_AreaEndX,KEY_AreaStartY,KEY_AreaEndY,KEY_CraneTravel,KEY_CraneTrolley,orderNO,areaType,areaNO
		//设置事件号
		string KEY_MessageNo = "";
		//设置行车号
		string KEY_CraneNo = craneNO;
		//设置取料/放料标记0-取料 1-放料
		string KEY_ActionType = "";
		if (orderType == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 || orderType == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21)
		{
			if (updownFlag == "UP")
			{
				KEY_MessageNo = "1001";//车辆上料：SRS车辆扫描完成后，WMS请求车辆装车的库区取料目标点计算
				KEY_ActionType = "0";//取料
				orderType = "2";//料格
			}
		}
		if (orderType == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			if (updownFlag == "UP")
			{
				KEY_MessageNo = "1003";//库区倒料
				KEY_ActionType = "0";
				orderType = "1";//卸料区
			}
			if (updownFlag == "DOWN")
			{
				KEY_MessageNo = "1003";//库区倒料
				KEY_ActionType = "1";
				orderType = "2";//料格
			}			
		}
		string KEY_AreaStartX = StringHelper::ToString(scanStartX);
		string KEY_AreaEndX = StringHelper::ToString(scanEndX);
		string KEY_AreaStartY = StringHelper::ToString(scanStartY);
		string KEY_AreaEndY = StringHelper::ToString(scanEndY);

		string KEY_CraneTravel = StringHelper::ToString(cranePLCStatus.getXAct());
		string KEY_CraneTrolley = StringHelper::ToString(cranePLCStatus.getYAct());

		string strOrderNO = StringHelper::ToString(orderNO);

		//检查数据是否齐全合法
		if (KEY_MessageNo.empty() || KEY_CraneNo.empty() || KEY_ActionType.empty() || KEY_AreaStartX.empty() || KEY_AreaEndX.empty() || 
			KEY_AreaStartY.empty() || KEY_AreaEndY.empty() || KEY_CraneTravel.empty() || KEY_CraneTrolley.empty() ||strOrderNO.empty() || areaType.empty() || areaNO.empty() )
		{
			log.Info()<<"获取EV_CRANE_UL01的数据组织不合法，return false.................."<<endl;
			ret = false;
			return ret;
		}

		EVTagValue = KEY_MessageNo + ",";
		EVTagValue += KEY_CraneNo + ",";
		EVTagValue += KEY_ActionType + ",";
		EVTagValue += KEY_AreaStartX + ",";
		EVTagValue += KEY_AreaEndX + ",";
		EVTagValue += KEY_AreaStartY + ",";
		EVTagValue += KEY_AreaEndY + ",";
		EVTagValue += KEY_CraneTravel + ",";
		EVTagValue += KEY_CraneTrolley + ",";
		EVTagValue += strOrderNO + ",";
		EVTagValue += areaType + ",";
		EVTagValue += areaNO;

	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return ret;
}


bool ACTION_COMMON_FUNCTION::CalMidPointList(string bayNO, 
																								 long currentX, 
																								 long currentY, 
																								 long targetX, 
																								 long targetY, 
																								 map<long, map<string, long> >& mapMidPointList)
{
	string functionName="ACTION_COMMON_FUNCTION :: CalMidPointList()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		map<string, long> mapMidPoint;

		long xLimitMax = 0;
		long xLimitMin = 0;
		long ySplit = 0;
		if ( false == Adapter_UACS_CRANE_MOVEORDER_MSG::SelXMaxXMinYSplit(targetX, targetY, xLimitMax, xLimitMin, ySplit) )
		{
			log.Info()<<"1. SelXMaxXMinYSplit  is no result....................return false........"<<endl;
			ret = false;
			return ret;
		}	

		long xLimitMax1 = 0;
		long xLimitMin1 = 0;
		long ySplit1 = 0;
		if ( false == Adapter_UACS_CRANE_MOVEORDER_MSG::SelXMaxXMinYSplit(currentX, currentY, xLimitMax1, xLimitMin1, ySplit1) )
		{
			log.Info()<<"2. SelXMaxXMinYSplit  is no result....................return false........"<<endl;
			ret = false;
			return ret;
		}

		long yMid = 0;

		if (bayNO == "F" )
		{
			yMid = ySplit + 3000;
		}
		else if (bayNO == "E")
		{
			yMid = ySplit - 3000;
		}
		else
		{
			log.Info()<<"BayNO is ERROR, return false.............."<<endl;
			ret = false;
			return ret;
		}

		//1..................................................................................................................................................
		if (targetY > ySplit && currentY > ySplit)
		{
			log.Info()<<"1. No MidPointList  Cal................................return false..........."<<endl;
			ret = false;
			return ret;
		}
		//2..................................................................................................................................................
		if (targetY > ySplit && currentY < ySplit)
		{
			if (currentX > xLimitMin && currentX < xLimitMax)
			{
				log.Info()<<"2. No MidPointList  Cal................................return false..........."<<endl;
				ret = false;
				return ret;
			}
			else if (currentX < xLimitMin)
			{
				if ( abs(xLimitMax1 - xLimitMin) <100 )//2个料格是相邻的 无中间点
				{
					log.Info()<<"3. No MidPointList  Cal................................return false..........."<<endl;
					ret = false;
					return ret;
				}
				else//不相邻
				{						
					long midX = xLimitMax1;
					long midY = yMid;
					mapMidPoint.insert( make_pair<string, long>("X", midX)); 
					mapMidPoint.insert( make_pair<string, long>("Y", midY)); 
					mapMidPointList[1] = mapMidPoint;
					log.Info()<<"4. MidPointList  Cal result is 1 point: midX="<<midX<<" , midY= "<<midY<<".............return true..........."<<endl;
					ret = true;
					return ret;
				}
			}
			else if (currentX > xLimitMax)
			{
				if ( abs(xLimitMin1 - xLimitMax) <100 )//2个料格是相邻的 无中间点
				{
					log.Info()<<"5. No MidPointList  Cal................................return false..........."<<endl;
					ret = false;
					return ret;
				}
				else//不相邻
				{						
					long midX = xLimitMin1;
					long midY = yMid;
					mapMidPoint.insert( make_pair<string, long>("X", midX)); 
					mapMidPoint.insert( make_pair<string, long>("Y", midY)); 
					mapMidPointList[1] = mapMidPoint;
					log.Info()<<"6. MidPointList  Cal result is 1 point: midX="<<midX<<" , midY= "<<midY<<".............return true..........."<<endl;
					ret = true;
					return ret;
				}
			}
		}
		//3..................................................................................................................................................
		if (targetY < ySplit && currentY > ySplit)
		{
			if (currentX > xLimitMin && currentX < xLimitMax)
			{
				log.Info()<<"7. No MidPointList  Cal................................return false..........."<<endl;
				ret = false;
				return ret;
			}
			else if (currentX < xLimitMin)
			{
				if ( abs(xLimitMax1 - xLimitMin) <100 )//2个料格是相邻的 无中间点
				{
					log.Info()<<"8. No MidPointList  Cal................................return false..........."<<endl;
					ret = false;
					return ret;
				}
				else//不相邻
				{						
					long midX = xLimitMax1;
					long midY = yMid;
					mapMidPoint.insert( make_pair<string, long>("X", midX)); 
					mapMidPoint.insert( make_pair<string, long>("Y", midY)); 
					mapMidPointList[1] = mapMidPoint;
					log.Info()<<"9. MidPointList  Cal result is 1 point: midX="<<midX<<" , midY= "<<midY<<".............return true..........."<<endl;
					ret = true;
					return ret;
				}
			}
			else if (currentX > xLimitMax)
			{
				if ( abs(xLimitMin1 - xLimitMax) <100 )//2个料格是相邻的 无中间点
				{
					log.Info()<<"10. No MidPointList  Cal................................return false..........."<<endl;
					ret = false;
					return ret;
				}
				else//不相邻
				{						
					long midX = xLimitMin1;
					long midY = yMid;
					mapMidPoint.insert( make_pair<string, long>("X", midX)); 
					mapMidPoint.insert( make_pair<string, long>("Y", midY)); 
					mapMidPointList[1] = mapMidPoint;
					log.Info()<<"11. MidPointList  Cal result is 1 point: midX="<<midX<<" , midY= "<<midY<<".............return true..........."<<endl;
					ret = true;
					return ret;
				}
			}
		}
		//4..................................................................................................................................................
		if (targetY < ySplit && currentY < ySplit)
		{
			if (currentX > xLimitMin && currentX < xLimitMax)
			{
				log.Info()<<"12. No MidPointList  Cal................................return false..........."<<endl;
				ret = false;
				return ret;
			}
			else if (currentX < xLimitMin)
			{
				if ( abs(xLimitMax1 - xLimitMin) <100 )//2个料格是相邻的 无中间点
				{
					log.Info()<<"13. No MidPointList  Cal................................return false..........."<<endl;
					ret = false;
					return ret;
				}
				else//不相邻
				{						
					long midX = xLimitMax1;
					long midY = yMid;
					mapMidPoint.insert( make_pair<string, long>("X", midX)); 
					mapMidPoint.insert( make_pair<string, long>("Y", midY)); 
					mapMidPointList[1] = mapMidPoint;
					log.Info()<<"14. MidPointList  Cal result is 2 point: 1st point --midX="<<midX<<" , midY= "<<midY<<".............return true..........."<<endl;

					midX = xLimitMin;
					midY = yMid;
					mapMidPoint.clear();
					mapMidPoint.insert( make_pair<string, long>("X", midX)); 
					mapMidPoint.insert( make_pair<string, long>("Y", midY)); 
					mapMidPointList[2] = mapMidPoint;
					log.Info()<<"14. MidPointList  Cal result is 2 point: 2nd point --midX="<<midX<<" , midY= "<<midY<<".............return true..........."<<endl;

					ret = true;
					return ret;
				}
			}
			else if (currentX > xLimitMax)
			{
				if ( abs(xLimitMin1 - xLimitMax) <100 )//2个料格是相邻的 无中间点
				{
					log.Info()<<"15. No MidPointList  Cal................................return false..........."<<endl;
					ret = false;
					return ret;
				}
				else//不相邻
				{	
					long midX = xLimitMin1;
					long midY = yMid;
					mapMidPoint.insert( make_pair<string, long>("X", midX)); 
					mapMidPoint.insert( make_pair<string, long>("Y", midY)); 
					mapMidPointList[1] = mapMidPoint;
					log.Info()<<"16. MidPointList  Cal result is 2 point: 1st point --midX="<<midX<<" , midY= "<<midY<<".............return true..........."<<endl;

					midX = xLimitMax;
					midY = yMid;
					mapMidPoint.clear();
					mapMidPoint.insert( make_pair<string, long>("X", midX)); 
					mapMidPoint.insert( make_pair<string, long>("Y", midY)); 
					mapMidPointList[2] = mapMidPoint;
					log.Info()<<"16. MidPointList  Cal result is 2 point: 2nd point --midX="<<midX<<" , midY= "<<midY<<".............return true..........."<<endl;

					ret = true;
					return ret;
				}
			}
		}

	}
	catch(...)
	{
		log.Debug()<<"error..........."<<endl;
	}
	return ret;
}


bool ACTION_COMMON_FUNCTION :: GetCarScanStartEndP(string parkingNO, 
																											long& planStartX, 
																											long& planStartY, 
																											long& planEndX, 
																											long& planEndY, 
																											string& moveDir)
{

	string functionName="ACTION_COMMON_FUNCTION :: getCarScanStartEndP()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool ret = false;

	try
	{
		long xStart = DB_INT_NULL;
		long xEnd = DB_INT_NULL;
		long xCenter = DB_INT_NULL;
		long yStart  =DB_INT_NULL;
		long yEnd = DB_INT_NULL;
		long yCenter = DB_INT_NULL;
		string scanDir = "";

		if (false == Adapter_UACS_YARDMAP_STOCK_INFO::SelParkingInfo(parkingNO, xStart, xEnd, xCenter, yStart, yEnd, yCenter, scanDir ))
		{
			log.Info()<<"No ParkingNO rec IN parking info define table..........return false............................................."<<endl;
			ret = false; 
			return ret;
		}

		if ( xStart == DB_INT_NULL || xEnd == DB_INT_NULL || xCenter == DB_INT_NULL || 
			yStart == DB_INT_NULL || yEnd == DB_INT_NULL || yCenter == DB_INT_NULL )
		{
			log.Info()<<"ParkingNO info define data IS INVALID IN parking info define table..........return false............................................."<<endl;
			ret = false; 
			return ret;
		}

		if (scanDir != "X" && scanDir != "Y")
		{
			log.Info()<<"scanDir IS INVALID,  not X and not Y..........return false............................................."<<endl;
			ret = false;
			return ret;
		}

		if (scanDir == "X")
		{
			planStartX = xStart;
			planStartY = yCenter;

			planEndX = xEnd;
			planEndY = yCenter;
		}
		if (scanDir == "Y")
		{
			planStartX = xCenter;
			planStartY = yStart;

			planEndX = xCenter;
			planEndY = yEnd;
		}

		moveDir = scanDir;

		ret = true;
		return ret;

	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}


bool ACTION_COMMON_FUNCTION :: CoilDownIsOverInFinishJob(CranePLCStatusBase cranePLCStatus, OrderCurrentBase orderCurrent)
{

	string functionName="ACTION_COMMON_FUNCTION :: CoilDownIsOverInFinishJob()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool ret = false;

	try
	{
		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			log.Info()<<"Order Is Car to Yard, Order is not over, return false.................."<<endl;
			ret = false;
			return ret;
		}

		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
			orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
		{
			log.Info()<<"MatReqWgt = "<<orderCurrent.getMatReqWgt()<<" , MatActWgt = "<<orderCurrent.getMatActWgt()<<endl;
			if ( abs( orderCurrent.getMatReqWgt() - orderCurrent.getMatActWgt() ) < 500 || 
				  orderCurrent.getMatActWgt() > orderCurrent.getMatReqWgt() )//装车完毕
			{
				log.Info()<<"Order is Yard to Car, Mat Wgt is enough, order is over, return true..........................."<<endl;
				ret = true;
				return ret;
			}
			else
			{
				log.Info()<<"Order is Yard to Car, Mat Wgt is NOT enough, order is NOT over, return false..........................."<<endl;
				ret = false;
				return ret;
			}
		}
		//其它情况  ret = true
		ret = true;
		return ret;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}