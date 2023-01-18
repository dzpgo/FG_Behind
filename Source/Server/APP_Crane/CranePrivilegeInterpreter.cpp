#include "CranePrivilegeInterpreter.h"



using namespace Monitor;

const string CranePrivilegeInterpreter::COMPARE_RESULT_HIGH = "HIGHT";

const string CranePrivilegeInterpreter::COMPARE_RESULT_LOW = "LOW";

const string CranePrivilegeInterpreter::COMPARE_RESULT_UNKNOW = "UNKNOW";

CranePrivilegeInterpreter :: CranePrivilegeInterpreter(void)
{


}



CranePrivilegeInterpreter :: ~CranePrivilegeInterpreter(void)
{



}



//1 getDirection
string CranePrivilegeInterpreter ::compareByCrane(string craneNO, string neighborCraneNO)
{


	string functionName = "CranePrivilegeInterpreter :: compare()";
	LOG log(functionName, AUTO_CATCH_PID);

	string result=CranePrivilegeInterpreter::COMPARE_RESULT_UNKNOW;

	try
	{
			log.Debug()<<"craneNO="<<craneNO<<"		neighborCraneNO="<<neighborCraneNO<<endl;
			if(craneNO=="4_4")
			{
				if(neighborCraneNO=="4_5")
				{
					result=CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
				}
			}

			if(craneNO=="4_5")
			{
				if(neighborCraneNO=="4_4")
				{
					result=CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
				}
			}

			if(craneNO=="4_5")
			{
				if(neighborCraneNO=="4_6")
				{
					result=CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
				}
			}
			if(craneNO=="4_6")
			{
				if(neighborCraneNO=="4_5")
				{
					result=CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
				}
			}

			if(craneNO=="4_6")
			{
				if(neighborCraneNO=="4_7")
				{
					result=CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
				}
			}

			if(craneNO=="4_7")
			{
				if(neighborCraneNO=="4_6")
				{
					result=CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
				}
			}	
			log.Debug()<<"Compare result="<<result<<endl;
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

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return result;
}


//2018.11.27 zhangyuhong add
//其实优先级比较的目的在judeg中是：
//1. COMPARE_RESULT_HIGH——我方车比对方车高，则主动靠近，靠近到对方车当前位置或当前目的地的安全距离
//2. COMPARE_RESULT_LOW——我方车比对方车低，则被动开进，靠近到可以让对方车整关指令不受限制的安全距离
//所以，这里比较的是，发送方的避让请求指令和接收方正在执行的指令谁更重要

//2018.12.20 zhangyuhong add
//优先级比较在receive中的目的是：
//1. COMPARE_RESULT_HIGH——接收方避让指令是在己方WMS指令的after_job 关后执行
//2. COMPARE_RESULT_LOW——接收方避让指令是在己方WMS指令的right_now 立即执行
//所以，这里比较的是，接收方的WMS指令和发送方的避让请求指令谁更重要

//优先级比较规则：

//1. 我方车正在做WMS指令，
//						若对方车无任何指令，则我方车等级高，对方车等级低：COMPARE_RESULT_HIGH
//						若对方车有Evade指令，则比较
//						若对方车有WMS指令，则比较WMS指令，
//											若我方车WMS比对方车WMS高，则我方车等级高，对方车等级低：COMPARE_RESULT_HIGH
//											若我方车WMS比对方车WMS低，则我方车等级低，对方车等级高：COMPARE_RESULT_LOW
//											若我方车WMS和对方车WMS等级一样，
//																若我方车当前位置离我方目标距离 大于 对方车当前位置离对方目标距离，则我方车等级低，对方车等级高：COMPARE_RESULT_LOW
//																若我方车当前位置离我方目标距离 小于 对方车当前位置离对方目标距离，则我方车等级高，对方车等级低：COMPARE_RESULT_HIGH
//																若我方车当前位置离我方目标距离 等于 对方车当前位置离对方目标距离，则进入compareByCrane
//string CranePrivilegeInterpreter ::VSByOrderWhenApproach(long orderNO, 
//																											  string craneNO, 
//																											  string neighborCraneNO, 
//																											  CranePLCStatusBase cranePLCStatus, 
//																											  CranePLCStatusBase neighborCranePLCStatus)
//{
//
//
//	string functionName = "CranePrivilegeInterpreter :: VSByOrderWhenApproach()";
//	LOG log(functionName, AUTO_CATCH_PID);
//
//	string result=CranePrivilegeInterpreter::COMPARE_RESULT_UNKNOW;
//
//	try
//	{
//		log.Debug()<<"orderNO="<<orderNO<<"			craneNO="<<craneNO<<"		neighborCraneNO="<<neighborCraneNO<<endl;
//		//如果我方车执行WMS指令
//		if (orderNO != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116 && 
//			orderNO != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115 && 
//			orderNO != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130 && 
//			orderNO != DB_INT_NULL)
//		{
//					log.Info()<<"我方车执行WMS指令......"<<endl;
//					//对方车执行避让指令
//					if (neighborCranePLCStatus.getOrderID() == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116)
//					{
//								log.Info()<<"对方车执行Evade指令......"<<endl;
//								log.Info()<<"比较结果：COMPARE_RESULT_LOW"<<endl;
//								result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//								return result;
//					}
//					//对方车执行回登车位指令
//					if (neighborCranePLCStatus.getOrderID() == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115)
//					{
//								log.Info()<<"对方车执行回登车位指令......"<<endl;
//								log.Info()<<"比较结果：COMPARE_RESULT_LOW"<<endl;
//								result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//								return result;
//					}
//					//对方车执行回放水位指令
//					if (neighborCranePLCStatus.getOrderID() == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130)
//					{
//								log.Info()<<"对方车执行回登车位指令......"<<endl;
//								log.Info()<<"比较结果：COMPARE_RESULT_LOW"<<endl;
//								result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//								return result;
//					}
//					//对方车执行WMS指令
//					if (neighborCranePLCStatus.getOrderID() != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116 && 
//						neighborCranePLCStatus.getOrderID() != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115 && 
//						neighborCranePLCStatus.getOrderID() != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130 && 
//						neighborCranePLCStatus.getOrderID() != DB_INT_NULL)
//					{
//								log.Info()<<"对方车执行WMS指令......"<<endl;
//								CraneOrderCurrentBase craneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);
//								CraneOrderCurrentBase neighborCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
//								if (craneOrderCurrent.getOrderPriority() > neighborCraneOrderCurrent.getOrderPriority())
//								{
//											log.Info()<<"我方车WMS优先级 > 对方车WMS优先级，比较结果：COMPARE_RESULT_HIGH"<<endl;
//											result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//											return result;
//								}
//								else if (craneOrderCurrent.getOrderPriority() < neighborCraneOrderCurrent.getOrderPriority())
//								{
//											log.Info()<<"我方车WMS优先级 < 对方车WMS优先级，比较结果：COMPARE_RESULT_LOW"<<endl;
//											result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//											return result;
//								}
//								else if (craneOrderCurrent.getOrderPriority() == neighborCraneOrderCurrent.getOrderPriority())
//								{
//											log.Info()<<"我方车WMS优先级 = 对方车WMS优先级......进入行车级别比较......"<<endl;
//											result = CranePrivilegeInterpreter::compareByCrane(craneNO, neighborCraneNO);
//											return result;
//								}
//					}
//		}
//
//		//如果我方行车执行Evade、回登车位、回放水位指令
//		if (orderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116 || 
//			orderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115 || 
//			orderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130)
//		{
//					log.Info()<<"我方车执行 Evade/回登车位/回放水位 指令......"<<endl;
//
//		}
//
//	}
//	catch(iDA::Exception &x)
//	{
//		try
//		{
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
//		log.Debug()<<functionName<<"   error:"<<endl;
//	}
//	return result;
//}


//2018.11.29 zhangyuhong add
//用于接收 receive 时
//string CranePrivilegeInterpreter ::VSByOrderWhenEvade(string targetCraneNO, CranePLCStatusBase targetCranePLCStatus, string senderCraneNO, long senderCraneOrderNO)
//{
//
//
//	string functionName = "CranePrivilegeInterpreter :: VSByOrderWhenEvade()";
//	LOG log(functionName, AUTO_CATCH_PID);
//
//	string result=CranePrivilegeInterpreter::COMPARE_RESULT_UNKNOW;
//
//	try
//	{
//		//因为接收避让请求时判断优先级的目的，是对WMS指令是应该 立即执行（RIGHT NOW）还是 关后执行（AFTER JOB）进行决定，
//		//所以，只针对接收方有WMS指令这种情况进行判断就行了
//		//接收方的其它指令优先级判断，就用默认的行车级别判断方法就可以了
//		//如果接收方有WMS指令
//		CraneOrderCurrentBase targetCraneOrderCurrent;
//		targetCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(targetCraneNO);
//		if (targetCraneOrderCurrent.getCMDStatus() != CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
//		{
//			log.Info()<<"接收方当前有WMS指令......需要比较WMS指令 与 发送方的 避让请求过来的 指令 的 优先级"<<endl;
//			if (senderCraneOrderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115)
//			{
//				log.Info()<<"发送车请求避让是因为要执行：回登车位 指令......接收方级别高！"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//				return result;
//			}
//			if (senderCraneOrderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130)
//			{
//				log.Info()<<"发送车请求避让是因为要执行：去防水位 指令......接收方级别高！"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//				return result;
//			}
//			if (senderCraneOrderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116)
//			{
//				log.Info()<<"发送车请求避让是因为要执行：避让 指令......需要 比较：接收方的WMS指令优先级 和 发送方的Evade指令优先级！"<<endl;
//				CraneEvadeRequestBase senderEvadeRequest;
//				long senderEvadeRequestPriority = 0;
//				if (true == Adapter_UACS_CRANE_EVADE_REQUEST::GetData(senderCraneNO, senderEvadeRequest))
//				{
//					senderEvadeRequestPriority = (long)senderEvadeRequest.getPriority();
//				}
//				log.Info()<<"senderEvadeRequestPriority = "<<senderEvadeRequestPriority<<endl;
//				log.Info()<<"craneOrderCurrent.getOrderPriority() = "<<targetCraneOrderCurrent.getOrderPriority()<<endl;
//				//如果接收方WMS指令优先级 > 发送方避让指令优先级
//				if (targetCraneOrderCurrent.getOrderPriority() > senderEvadeRequestPriority)
//				{
//					log.Info()<<"接收方WMS指令优先级 > 发送方避让指令优先级......接收方级别高！"<<endl;
//					result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//					return result;
//				}
//				//如果接收方WMS指令优先级 < 发送方避让指令优先级
//				if (targetCraneOrderCurrent.getOrderPriority() < senderEvadeRequestPriority)
//				{
//					log.Info()<<"接收方WMS指令优先级 < 发送方避让指令优先级......接收方级别低！"<<endl;
//					result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//					return result;
//				}
//				//如果接收方WMS指令优先级 = 发送方避让指令优先级
//				if (targetCraneOrderCurrent.getOrderPriority() == senderEvadeRequestPriority)
//				{
//					log.Info()<<"接收方WMS指令优先级 = 发送方避让指令优先级......需要比较谁大车离目标大车更近，谁优先级更高！"<<endl;
//					//接收方“当前”大车位置（可能是静止的，则位当前位置；可能是运动的，则为目标位置）  与    WMS指令表中目标位的距离
//					long craneDistanceWMS = ACTION_COMMON_FUNCTION::getDistanceByWMS(targetCranePLCStatus, targetCraneOrderCurrent);
//
//					long senderDistanceEvade = DB_INT_NULL;
//					//获得发送方的PLC状态
//					CranePLCStatusBase  senderPLCStatusBase;
//					bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(senderCraneNO, senderPLCStatusBase);
//					if(ret_getPLCStatus==false)
//					{
//						log.Debug()<<"获取发送方= "<<senderCraneNO<<" 的PLC状态信息失败......为安全起见，返回接收方级别低：接收方避让类型为 RIGHT_NOW！"<<endl;
//						result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//						return result;
//					}
//					senderDistanceEvade = ACTION_COMMON_FUNCTION::getDistanceByEvade(senderPLCStatusBase, senderEvadeRequest);
//
//					//开始比较   接收方 当前位置到目标 的大车距离     和    发送方的 当前位置到目标 的大车距离  ：  谁近   谁 优先
//					if (craneDistanceWMS > senderDistanceEvade)
//					{
//						log.Info()<<"接收方距离 > 发送方距离......接收方优先级低！"<<endl;
//						result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//						return result;
//					}
//					if (craneDistanceWMS < senderDistanceEvade)
//					{
//						log.Info()<<"接收方距离 < 发送方距离......接收方优先级高！"<<endl;
//						result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//						return result;
//					}
//					if (craneDistanceWMS == senderDistanceEvade)
//					{
//						log.Info()<<"接收方距离 == 发送方距离......比较行车本体优先级！"<<endl;
//						result = CranePrivilegeInterpreter::compareByCrane(targetCraneNO, senderCraneNO);
//						return result;
//					}
//				}				
//			}
//			//到这里，剩下的都是WMS指令发出的避让了
//			log.Info()<<"发送车请求避让是因为要执行：WMS 指令......需要 避让指令的优先级 和 接受方WMS指令优先级 进行比较！"<<endl;
//			//接收方的距离
//			long craneDistanceWMS = ACTION_COMMON_FUNCTION::getDistanceByWMS(targetCranePLCStatus, targetCraneOrderCurrent);
//
//			CranePLCStatusBase  senderPLCStatusBase;
//			bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(senderCraneNO, senderPLCStatusBase);
//			if(ret_getPLCStatus==false)
//			{
//				log.Debug()<<"获取发送方= "<<senderCraneNO<<" 的PLC状态信息失败......为安全起见，返回接收方级别低：接收方避让类型为 RIGHT_NOW！"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//				return result;
//			}
//			CraneOrderCurrentBase senderOrderCurrent;
//			senderOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(senderCraneNO);
//			long senderDistanceWMS = ACTION_COMMON_FUNCTION::getDistanceByWMS(senderPLCStatusBase, senderOrderCurrent);
//
//			//开始比较
//			//开始比较   接收方 当前位置到目标 的大车距离     和    发送方的 当前位置到目标 的大车距离  ：  谁近   谁 优先
//			if (craneDistanceWMS > senderDistanceWMS)
//			{
//				log.Info()<<"接收方距离 > 发送方距离......接收方优先级低！"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//				return result;
//			}
//			if (craneDistanceWMS < senderDistanceWMS)
//			{
//				log.Info()<<"接收方距离 < 发送方距离......接收方优先级高！"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//				return result;
//			}
//			if (craneDistanceWMS == senderDistanceWMS)
//			{
//				log.Info()<<"接收方距离 == 发送方距离......比较行车本体优先级！"<<endl;
//				result = CranePrivilegeInterpreter::compareByCrane(targetCraneNO, senderCraneNO);
//				return result;
//			}
//		}
//		else
//		{
//			//没问题，此时如果接收方在执行避让指令，则后续不会写入避让，
//			//如果没有执行任何指令，则后续写入避让指令
//			log.Info()<<"接收方当前没有WMS指令....根据行车本体优先级比较......"<<endl;
//			result = CranePrivilegeInterpreter::compareByCrane(targetCraneNO, senderCraneNO);
//			return result;
//		}
//
//	}
//	catch(iDA::Exception &x)
//	{
//		try
//		{
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
//		log.Debug()<<functionName<<"   error:"<<endl;
//	}
//	return result;
//}