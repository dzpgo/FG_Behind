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
//��ʵ���ȼ��Ƚϵ�Ŀ����judeg���ǣ�
//1. COMPARE_RESULT_HIGH�����ҷ����ȶԷ����ߣ��������������������Է�����ǰλ�û�ǰĿ�ĵصİ�ȫ����
//2. COMPARE_RESULT_LOW�����ҷ����ȶԷ����ͣ��򱻶������������������öԷ�������ָ������Ƶİ�ȫ����
//���ԣ�����Ƚϵ��ǣ����ͷ��ı�������ָ��ͽ��շ�����ִ�е�ָ��˭����Ҫ

//2018.12.20 zhangyuhong add
//���ȼ��Ƚ���receive�е�Ŀ���ǣ�
//1. COMPARE_RESULT_HIGH�������շ�����ָ�����ڼ���WMSָ���after_job �غ�ִ��
//2. COMPARE_RESULT_LOW�������շ�����ָ�����ڼ���WMSָ���right_now ����ִ��
//���ԣ�����Ƚϵ��ǣ����շ���WMSָ��ͷ��ͷ��ı�������ָ��˭����Ҫ

//���ȼ��ȽϹ���

//1. �ҷ���������WMSָ�
//						���Է������κ�ָ����ҷ����ȼ��ߣ��Է����ȼ��ͣ�COMPARE_RESULT_HIGH
//						���Է�����Evadeָ���Ƚ�
//						���Է�����WMSָ���Ƚ�WMSָ�
//											���ҷ���WMS�ȶԷ���WMS�ߣ����ҷ����ȼ��ߣ��Է����ȼ��ͣ�COMPARE_RESULT_HIGH
//											���ҷ���WMS�ȶԷ���WMS�ͣ����ҷ����ȼ��ͣ��Է����ȼ��ߣ�COMPARE_RESULT_LOW
//											���ҷ���WMS�ͶԷ���WMS�ȼ�һ����
//																���ҷ�����ǰλ�����ҷ�Ŀ����� ���� �Է�����ǰλ����Է�Ŀ����룬���ҷ����ȼ��ͣ��Է����ȼ��ߣ�COMPARE_RESULT_LOW
//																���ҷ�����ǰλ�����ҷ�Ŀ����� С�� �Է�����ǰλ����Է�Ŀ����룬���ҷ����ȼ��ߣ��Է����ȼ��ͣ�COMPARE_RESULT_HIGH
//																���ҷ�����ǰλ�����ҷ�Ŀ����� ���� �Է�����ǰλ����Է�Ŀ����룬�����compareByCrane
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
//		//����ҷ���ִ��WMSָ��
//		if (orderNO != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116 && 
//			orderNO != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115 && 
//			orderNO != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130 && 
//			orderNO != DB_INT_NULL)
//		{
//					log.Info()<<"�ҷ���ִ��WMSָ��......"<<endl;
//					//�Է���ִ�б���ָ��
//					if (neighborCranePLCStatus.getOrderID() == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116)
//					{
//								log.Info()<<"�Է���ִ��Evadeָ��......"<<endl;
//								log.Info()<<"�ȽϽ����COMPARE_RESULT_LOW"<<endl;
//								result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//								return result;
//					}
//					//�Է���ִ�лصǳ�λָ��
//					if (neighborCranePLCStatus.getOrderID() == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115)
//					{
//								log.Info()<<"�Է���ִ�лصǳ�λָ��......"<<endl;
//								log.Info()<<"�ȽϽ����COMPARE_RESULT_LOW"<<endl;
//								result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//								return result;
//					}
//					//�Է���ִ�лط�ˮλָ��
//					if (neighborCranePLCStatus.getOrderID() == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130)
//					{
//								log.Info()<<"�Է���ִ�лصǳ�λָ��......"<<endl;
//								log.Info()<<"�ȽϽ����COMPARE_RESULT_LOW"<<endl;
//								result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//								return result;
//					}
//					//�Է���ִ��WMSָ��
//					if (neighborCranePLCStatus.getOrderID() != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116 && 
//						neighborCranePLCStatus.getOrderID() != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115 && 
//						neighborCranePLCStatus.getOrderID() != ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130 && 
//						neighborCranePLCStatus.getOrderID() != DB_INT_NULL)
//					{
//								log.Info()<<"�Է���ִ��WMSָ��......"<<endl;
//								CraneOrderCurrentBase craneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);
//								CraneOrderCurrentBase neighborCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
//								if (craneOrderCurrent.getOrderPriority() > neighborCraneOrderCurrent.getOrderPriority())
//								{
//											log.Info()<<"�ҷ���WMS���ȼ� > �Է���WMS���ȼ����ȽϽ����COMPARE_RESULT_HIGH"<<endl;
//											result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//											return result;
//								}
//								else if (craneOrderCurrent.getOrderPriority() < neighborCraneOrderCurrent.getOrderPriority())
//								{
//											log.Info()<<"�ҷ���WMS���ȼ� < �Է���WMS���ȼ����ȽϽ����COMPARE_RESULT_LOW"<<endl;
//											result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//											return result;
//								}
//								else if (craneOrderCurrent.getOrderPriority() == neighborCraneOrderCurrent.getOrderPriority())
//								{
//											log.Info()<<"�ҷ���WMS���ȼ� = �Է���WMS���ȼ�......�����г�����Ƚ�......"<<endl;
//											result = CranePrivilegeInterpreter::compareByCrane(craneNO, neighborCraneNO);
//											return result;
//								}
//					}
//		}
//
//		//����ҷ��г�ִ��Evade���صǳ�λ���ط�ˮλָ��
//		if (orderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116 || 
//			orderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115 || 
//			orderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130)
//		{
//					log.Info()<<"�ҷ���ִ�� Evade/�صǳ�λ/�ط�ˮλ ָ��......"<<endl;
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
//���ڽ��� receive ʱ
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
//		//��Ϊ���ձ�������ʱ�ж����ȼ���Ŀ�ģ��Ƕ�WMSָ����Ӧ�� ����ִ�У�RIGHT NOW������ �غ�ִ�У�AFTER JOB�����о�����
//		//���ԣ�ֻ��Խ��շ���WMSָ��������������жϾ�����
//		//���շ�������ָ�����ȼ��жϣ�����Ĭ�ϵ��г������жϷ����Ϳ�����
//		//������շ���WMSָ��
//		CraneOrderCurrentBase targetCraneOrderCurrent;
//		targetCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(targetCraneNO);
//		if (targetCraneOrderCurrent.getCMDStatus() != CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
//		{
//			log.Info()<<"���շ���ǰ��WMSָ��......��Ҫ�Ƚ�WMSָ�� �� ���ͷ��� ������������� ָ�� �� ���ȼ�"<<endl;
//			if (senderCraneOrderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_BOARDING_MOVING_115)
//			{
//				log.Info()<<"���ͳ������������ΪҪִ�У��صǳ�λ ָ��......���շ�����ߣ�"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//				return result;
//			}
//			if (senderCraneOrderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_ACWATER_MOVING_130)
//			{
//				log.Info()<<"���ͳ������������ΪҪִ�У�ȥ��ˮλ ָ��......���շ�����ߣ�"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//				return result;
//			}
//			if (senderCraneOrderNO == ACTION_COMMON_FUNCTION::ORDERNO_CRANE_EVADE_MOVING_116)
//			{
//				log.Info()<<"���ͳ������������ΪҪִ�У����� ָ��......��Ҫ �Ƚϣ����շ���WMSָ�����ȼ� �� ���ͷ���Evadeָ�����ȼ���"<<endl;
//				CraneEvadeRequestBase senderEvadeRequest;
//				long senderEvadeRequestPriority = 0;
//				if (true == Adapter_UACS_CRANE_EVADE_REQUEST::GetData(senderCraneNO, senderEvadeRequest))
//				{
//					senderEvadeRequestPriority = (long)senderEvadeRequest.getPriority();
//				}
//				log.Info()<<"senderEvadeRequestPriority = "<<senderEvadeRequestPriority<<endl;
//				log.Info()<<"craneOrderCurrent.getOrderPriority() = "<<targetCraneOrderCurrent.getOrderPriority()<<endl;
//				//������շ�WMSָ�����ȼ� > ���ͷ�����ָ�����ȼ�
//				if (targetCraneOrderCurrent.getOrderPriority() > senderEvadeRequestPriority)
//				{
//					log.Info()<<"���շ�WMSָ�����ȼ� > ���ͷ�����ָ�����ȼ�......���շ�����ߣ�"<<endl;
//					result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//					return result;
//				}
//				//������շ�WMSָ�����ȼ� < ���ͷ�����ָ�����ȼ�
//				if (targetCraneOrderCurrent.getOrderPriority() < senderEvadeRequestPriority)
//				{
//					log.Info()<<"���շ�WMSָ�����ȼ� < ���ͷ�����ָ�����ȼ�......���շ�����ͣ�"<<endl;
//					result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//					return result;
//				}
//				//������շ�WMSָ�����ȼ� = ���ͷ�����ָ�����ȼ�
//				if (targetCraneOrderCurrent.getOrderPriority() == senderEvadeRequestPriority)
//				{
//					log.Info()<<"���շ�WMSָ�����ȼ� = ���ͷ�����ָ�����ȼ�......��Ҫ�Ƚ�˭����Ŀ��󳵸�����˭���ȼ����ߣ�"<<endl;
//					//���շ�����ǰ����λ�ã������Ǿ�ֹ�ģ���λ��ǰλ�ã��������˶��ģ���ΪĿ��λ�ã�  ��    WMSָ�����Ŀ��λ�ľ���
//					long craneDistanceWMS = ACTION_COMMON_FUNCTION::getDistanceByWMS(targetCranePLCStatus, targetCraneOrderCurrent);
//
//					long senderDistanceEvade = DB_INT_NULL;
//					//��÷��ͷ���PLC״̬
//					CranePLCStatusBase  senderPLCStatusBase;
//					bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(senderCraneNO, senderPLCStatusBase);
//					if(ret_getPLCStatus==false)
//					{
//						log.Debug()<<"��ȡ���ͷ�= "<<senderCraneNO<<" ��PLC״̬��Ϣʧ��......Ϊ��ȫ��������ؽ��շ�����ͣ����շ���������Ϊ RIGHT_NOW��"<<endl;
//						result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//						return result;
//					}
//					senderDistanceEvade = ACTION_COMMON_FUNCTION::getDistanceByEvade(senderPLCStatusBase, senderEvadeRequest);
//
//					//��ʼ�Ƚ�   ���շ� ��ǰλ�õ�Ŀ�� �Ĵ󳵾���     ��    ���ͷ��� ��ǰλ�õ�Ŀ�� �Ĵ󳵾���  ��  ˭��   ˭ ����
//					if (craneDistanceWMS > senderDistanceEvade)
//					{
//						log.Info()<<"���շ����� > ���ͷ�����......���շ����ȼ��ͣ�"<<endl;
//						result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//						return result;
//					}
//					if (craneDistanceWMS < senderDistanceEvade)
//					{
//						log.Info()<<"���շ����� < ���ͷ�����......���շ����ȼ��ߣ�"<<endl;
//						result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//						return result;
//					}
//					if (craneDistanceWMS == senderDistanceEvade)
//					{
//						log.Info()<<"���շ����� == ���ͷ�����......�Ƚ��г��������ȼ���"<<endl;
//						result = CranePrivilegeInterpreter::compareByCrane(targetCraneNO, senderCraneNO);
//						return result;
//					}
//				}				
//			}
//			//�����ʣ�µĶ���WMSָ����ı�����
//			log.Info()<<"���ͳ������������ΪҪִ�У�WMS ָ��......��Ҫ ����ָ������ȼ� �� ���ܷ�WMSָ�����ȼ� ���бȽϣ�"<<endl;
//			//���շ��ľ���
//			long craneDistanceWMS = ACTION_COMMON_FUNCTION::getDistanceByWMS(targetCranePLCStatus, targetCraneOrderCurrent);
//
//			CranePLCStatusBase  senderPLCStatusBase;
//			bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(senderCraneNO, senderPLCStatusBase);
//			if(ret_getPLCStatus==false)
//			{
//				log.Debug()<<"��ȡ���ͷ�= "<<senderCraneNO<<" ��PLC״̬��Ϣʧ��......Ϊ��ȫ��������ؽ��շ�����ͣ����շ���������Ϊ RIGHT_NOW��"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//				return result;
//			}
//			CraneOrderCurrentBase senderOrderCurrent;
//			senderOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(senderCraneNO);
//			long senderDistanceWMS = ACTION_COMMON_FUNCTION::getDistanceByWMS(senderPLCStatusBase, senderOrderCurrent);
//
//			//��ʼ�Ƚ�
//			//��ʼ�Ƚ�   ���շ� ��ǰλ�õ�Ŀ�� �Ĵ󳵾���     ��    ���ͷ��� ��ǰλ�õ�Ŀ�� �Ĵ󳵾���  ��  ˭��   ˭ ����
//			if (craneDistanceWMS > senderDistanceWMS)
//			{
//				log.Info()<<"���շ����� > ���ͷ�����......���շ����ȼ��ͣ�"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_LOW;
//				return result;
//			}
//			if (craneDistanceWMS < senderDistanceWMS)
//			{
//				log.Info()<<"���շ����� < ���ͷ�����......���շ����ȼ��ߣ�"<<endl;
//				result = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
//				return result;
//			}
//			if (craneDistanceWMS == senderDistanceWMS)
//			{
//				log.Info()<<"���շ����� == ���ͷ�����......�Ƚ��г��������ȼ���"<<endl;
//				result = CranePrivilegeInterpreter::compareByCrane(targetCraneNO, senderCraneNO);
//				return result;
//			}
//		}
//		else
//		{
//			//û���⣬��ʱ������շ���ִ�б���ָ����������д����ã�
//			//���û��ִ���κ�ָ������д�����ָ��
//			log.Info()<<"���շ���ǰû��WMSָ��....�����г��������ȼ��Ƚ�......"<<endl;
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