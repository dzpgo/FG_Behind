#include "ACTION_CAR_SCAN_IS_OK.h"

using namespace Monitor;

ACTION_CAR_SCAN_IS_OK :: ACTION_CAR_SCAN_IS_OK(void)
{
}



ACTION_CAR_SCAN_IS_OK :: ~ACTION_CAR_SCAN_IS_OK(void)
{
}



//1 doAction
bool ACTION_CAR_SCAN_IS_OK :: doAction(string craneNO, 
																				string bayNO,
																				OrderCurrentBase orderCurrent, 
																				CranePLCStatusBase cranePLCStatus)	
{
	bool ret=false;

	string functionName="ACTION_CAR_SCAN_IS_OK :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_CAR_SCAN_IS_OK----------------------- -----------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( !ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
		{
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getCmdStatus()"<<orderCurrent.getCmdStatus()<<endl;
		log.Debug()<<"cranePLCStatus.getHasCoil()"<<cranePLCStatus.getHasCoil()<<endl;

		if(orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && cranePLCStatus.getHasCoil() > 0)
		{
			log.Debug()<<"�г���ǰָ������CoilUp״̬�����г�hascoil > 0������true��"<<endl;
			ret=true;
			return ret;
		}

		//���carScanNo�Ƿ�Ϊ��
		if (!orderCurrent.getCarScanNO().empty())//�г�������ɨ��� ˵���Ѿ���ȡ������ɨ������
		{
			log.Info()<<"CarScanNO IS NOT EMPTY��Del rec from UACS_CAR_SCAN_ORDER_REC by orderno.........return true....................."<<endl;
			Adapter_UACS_CRANE_ORDER_CURRENT::DelCarScanOrderRecByOrderNO(orderCurrent.getOrderNO());
			ret = true;
			return ret;
		}

		//�����г�����������ɨ������ָ��
		//��ȡ��������ָ��·�����  �յ�
		long planStartX = DB_INT_NULL;
		long planStartY = DB_INT_NULL;
		long planEndX = DB_INT_NULL;
		long planEndY = DB_INT_NULL;
		string moveDir = "";
		if (false == ACTION_COMMON_FUNCTION::GetCarScanStartEndP(orderCurrent.getToStockNO(), planStartX, planStartY, planEndX, planEndY, moveDir))
		{
			//�޷���ȡɨ����ʼ��
			log.Info()<<"getCarScanStartEndP return false, .......................return false......................................"<<endl;
			ret = false;
			return ret;
		}

		//carScanNoΪ�����
		string scanActionFlag = "";
		if ( false == Adapter_UACS_CRANE_ORDER_CURRENT::SelFlagInCarScanOrderRec(orderCurrent.getOrderNO(), scanActionFlag) )//�޼�¼
		{
			//�Ƿ������ ������� ���� �����ָ�����ڣ����͵��յ�ָ��
			if ( false == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), cranePLCStatus.getYAct(), planStartX, planStartY, 100, 100))
			{
				//���͵����ָ��
				Clone_DownLoadMoving_Order::go(bayNO, 
																				craneNO, 
																				orderCurrent.getOrderNO(), 
																				cranePLCStatus.getXAct(), 
																				cranePLCStatus.getYAct(), 
																				planStartX, 
																				planStartY, 
																				cranePLCStatus.getHasCoil(), 
																				DB_INT_NULL, 
																				DB_INT_NULL, 
																				1);
				log.Info()<<"1.1 ���͵�ͣ��λɨ�����ָ��......................................................................."<<endl;
			}
			else
			{
				//���͵��յ�ָ��
				Clone_DownLoadMoving_Order::go(bayNO, 
																				craneNO, 
																				orderCurrent.getOrderNO(), 
																				cranePLCStatus.getXAct(), 
																				cranePLCStatus.getYAct(), 
																				planEndX, 
																				planEndY, 
																				cranePLCStatus.getHasCoil(), 
																				DB_INT_NULL, 
																				DB_INT_NULL, 
																				1);
				log.Info()<<"1.2 ���͵�ͣ��λɨ���յ�ָ��......................................................................."<<endl;
			}
			//�����¼��UACS_CAR_SCAN_ORDER_REC//orderNO, planstartXY planendXY  parkingNO  moveDir  rec_time
			Adapter_UACS_CRANE_ORDER_CURRENT::InsCarScanOrderRec(orderCurrent.getOrderNO(), 
																																orderCurrent.getToStockNO(), 
																																planStartX, 
																																planStartY, 
																																planEndX, 
																																planEndY, 
																																moveDir);
			log.Info()<<"�²����¼�� .....CarScanOrderRec table...........................return false......................................."<<endl;

			ret = false;
			return ret;
		}

		//�������м�¼��
		//carScan��Ϊ��
		if (scanActionFlag == "1")//�г��ĳ���ɨ�����ж����Ѿ����
		{
			log.Info()<<"scanActionFlag==1, means Crane Scan Car Action is FINISH...........wait scan result...............return false............... "<<endl;
			ret  =false;
			return ret;
		}

		//scanActionFlag��Ϊ1  ˵���г�ɨ�����ж���û�����
		//�������м䱻�ж���
		//���·����г�������ɨ������ָ��
		//�Ƿ������ ������� ���� �����ָ�����ڣ����͵��յ�ָ��
		if ( false == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), cranePLCStatus.getYAct(), planStartX, planStartY, 100, 100))
		{
			//���͵����ָ��
			Clone_DownLoadMoving_Order::go(bayNO, 
																				craneNO, 
																				orderCurrent.getOrderNO(), 
																				cranePLCStatus.getXAct(), 
																				cranePLCStatus.getYAct(), 
																				planStartX, 
																				planStartY, 
																				cranePLCStatus.getHasCoil(), 
																				DB_INT_NULL, 
																				DB_INT_NULL, 
																				1);
			log.Info()<<"2.1 ���͵�ͣ��λɨ�����ָ��......................................................................."<<endl;
		}
		else
		{
			//���͵��յ�ָ��
			Clone_DownLoadMoving_Order::go(bayNO, 
																				craneNO, 
																				orderCurrent.getOrderNO(), 
																				cranePLCStatus.getXAct(), 
																				cranePLCStatus.getYAct(), 
																				planEndX, 
																				planEndY, 
																				cranePLCStatus.getHasCoil(), 
																				DB_INT_NULL, 
																				DB_INT_NULL, 
																				1);
			log.Info()<<"2.2 ���͵�ͣ��λɨ����ָ��......................................................................."<<endl;
		}
		log.Info()<<"������ϣ�return false......................................................................."<<endl;
		ret = false;
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


