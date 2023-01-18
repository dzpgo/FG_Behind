#include "WALL_WHOLE_ORDER.h"



using namespace Monitor;


WALL_WHOLE_ORDER :: WALL_WHOLE_ORDER(void)
{


}



WALL_WHOLE_ORDER :: ~WALL_WHOLE_ORDER(void)
{



}





bool WALL_WHOLE_ORDER ::getWall(string craneNO, string movingDirection, CranePLCStatusBase  neightborCranePLCStatusBase , long& wallX, long& wallType)
{
	string functionName = "WALL_WHOLE_STEP :: getWall()";
	LOG log(functionName, AUTO_CATCH_PID);

	//���費�ܻ��
	bool ret=false;

	try
	{
		log.Debug()<<"����="<<craneNO<<"   ��������="<<movingDirection<<endl;
		log.Debug()<<"�ڳ�="<<neightborCranePLCStatusBase.getCraneNO()<<"  �ڳ���ǰX����="<<neightborCranePLCStatusBase.getXAct()<<endl;

		//��ǰ�г��ĵ�ǰλ��
		long neighborCurrentX=neightborCranePLCStatusBase.getXAct();

		//�г��˶���Ŀ��λ��
		long neighborMoveingTarget=CranePLCOrderBase::PLC_INT_NULL;
		if(neightborCranePLCStatusBase.getHasCoil()==0)
		{
			neighborMoveingTarget=neightborCranePLCStatusBase.getPlanUpX();
		}
		else if(neightborCranePLCStatusBase.getHasCoil()==1)
		{
			neighborMoveingTarget=neightborCranePLCStatusBase.getPlanDownX();
		}


		log.Debug()<<"׼����ȡ�ڳ���WMSָ��....... "<<endl;

		long neighborX_Min;
		long wallType_X_Min;

		long neighborX_Max;
		long wallType_X_Max;

		OrderCurrentBase  neightborCraneOrderCurrent;
		neightborCraneOrderCurrent=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neightborCranePLCStatusBase.getCraneNO());
		if(neightborCraneOrderCurrent.getOrderNO()==DB_INT_NULL)
		{
			log.Debug()<<"�ڳ���ǰָ����е�ָ���=999999�����г���ǰX�滻ָ���е�planUpX �� planDownX......"<<endl;
			neightborCraneOrderCurrent.setPlanUpX( neightborCranePLCStatusBase.getXAct() );
			neightborCraneOrderCurrent.setPlanDownX( neightborCranePLCStatusBase.getXAct() );
		}
		if(neightborCraneOrderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			log.Debug()<<"�ڳ���ǰָ����е�ָ���=999999�����г���ǰX�滻ָ���е�planUpX �� planDownX......"<<endl;
			neightborCraneOrderCurrent.setPlanUpX( neightborCranePLCStatusBase.getXAct() );
			neightborCraneOrderCurrent.setPlanDownX( neightborCranePLCStatusBase.getXAct() );
		}

		//******************************************************************************************************************************
		//*
		//								ȡ�������г���ǰλ��  �г��ƻ����λ��  �г��ƻ����λ���� ��������С��
		//*
		//******************************************************************************************************************************
		

		neighborX_Min=neightborCranePLCStatusBase.getXAct();
		wallType_X_Min=WALL_SINGLE_STEP::WALL_DYNAMIC;

		if(neightborCranePLCStatusBase.getXDirectPositive()==1  || neightborCranePLCStatusBase.getXDirectNegative()==1)
		{
			wallType_X_Min=WALL_SINGLE_STEP::WALL_DYNAMIC;//20171117  ���ڶ����Ƕ�ǽ
		}
		if(neightborCranePLCStatusBase.getXDirectPositive()==0  && neightborCranePLCStatusBase.getXDirectNegative()==0)
		{
			wallType_X_Min=WALL_SINGLE_STEP::WALL_STATIC;//20171117  //��û�ж����Ǿ�ǽ
		}

		if(neighborX_Min>neightborCraneOrderCurrent.getPlanUpX()  &&  neightborCraneOrderCurrent.getPlanUpX() !=CranePLCOrderBase::PLC_INT_NULL && neightborCranePLCStatusBase.getHasCoil()==0)
		{
			log.Info()<<"1. ����neighborX_Min��......�Ƚ�planUpX"<<endl;
			neighborX_Min=neightborCraneOrderCurrent.getPlanUpX();
			wallType_X_Min=WALL_SINGLE_STEP::WALL_STATIC;
		}
		if(neighborX_Min>neightborCraneOrderCurrent.getPlanDownX()  && neightborCraneOrderCurrent.getPlanDownX() !=CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Info()<<"2. ����neighborX_Min��......�Ƚ�planDownX"<<endl;
			neighborX_Min=neightborCraneOrderCurrent.getPlanDownX();
			wallType_X_Min=WALL_SINGLE_STEP::WALL_STATIC;
		}
		if(neighborX_Min>neighborMoveingTarget &&neighborMoveingTarget !=CranePLCOrderBase::PLC_INT_NULL)
		{
			neighborX_Min=neighborMoveingTarget;
			wallType_X_Min=WALL_SINGLE_STEP::WALL_STATIC;
		}

		//--------------------------------------------------------------------------------------------------------------------------------

		neighborX_Max=neightborCranePLCStatusBase.getXAct();
		wallType_X_Max=WALL_SINGLE_STEP::WALL_DYNAMIC;

		if(neightborCranePLCStatusBase.getXDirectPositive()==1  || neightborCranePLCStatusBase.getXDirectNegative()==1)
		{
			wallType_X_Max=WALL_SINGLE_STEP::WALL_DYNAMIC;//20171117  ���ڶ����Ƕ�ǽ
		}
		if(neightborCranePLCStatusBase.getXDirectPositive()==0  && neightborCranePLCStatusBase.getXDirectNegative()==0)
		{
			wallType_X_Max=WALL_SINGLE_STEP::WALL_STATIC;//20171117  //��û�ж����Ǿ�ǽ
		}

		if(neighborX_Max<neightborCraneOrderCurrent.getPlanUpX()  &&  neightborCraneOrderCurrent.getPlanUpX() !=CranePLCOrderBase::PLC_INT_NULL && neightborCranePLCStatusBase.getHasCoil()==0)
		{
			log.Info()<<"1. ����neighborX_Max���ڳ��չ�......"<<endl;
			neighborX_Max=neightborCraneOrderCurrent.getPlanUpX();
			wallType_X_Max=WALL_SINGLE_STEP::WALL_STATIC;
		}
		if(neighborX_Max<neightborCraneOrderCurrent.getPlanDownX()  && neightborCraneOrderCurrent.getPlanDownX() !=CranePLCOrderBase::PLC_INT_NULL )
		{
			log.Info()<<"2. ����neighborX_Max���ڳ��ع�......"<<endl;
			neighborX_Max=neightborCraneOrderCurrent.getPlanDownX();
			wallType_X_Max=WALL_SINGLE_STEP::WALL_STATIC;
		}
		if(neighborX_Max<neighborMoveingTarget  && neighborMoveingTarget !=CranePLCOrderBase::PLC_INT_NULL)
		{
			neighborX_Max=neighborMoveingTarget;
			wallType_X_Max=WALL_SINGLE_STEP::WALL_STATIC;
		}

		log.Debug()<<"neighborX_Min = "<<neighborX_Min<<"��wallType_X_Min = "<<getWallTypeString(wallType_X_Min)<<endl;
		log.Debug()<<"neighborX_Max = "<<neighborX_Max<<"��wallType_X_Max = "<<getWallTypeString(wallType_X_Max)<<endl;

		//ǰ������ΪX���� 
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			//(-)------Current-----------------------------target-----------------NeighborCrane---->(+)
			//��ǰ����X�����˶�����ǰ���� ���X����СX  �бȽ�С����ǽ  �ǵ�ǰλ�õ� �Ƕ�̬ǽ����Ŀ��λ�õ��Ǿ�̬ǽ
			log.Debug()<<"��������Ϊ X_INC��(-)----Current-----target----NeighborCrane---->(+)��ȡ��Сֵ neighborX_Min ��ΪwallX"<<endl;
			wallX=neighborX_Min;
			wallType=wallType_X_Min;
			log.Debug()<<"wallX = "<<neighborX_Min<<"  wallType= "<<wallType_X_Min<<endl;
			log.Debug()<<"���̷���true......"<<endl;
			ret=true;
			return ret;

		}
		//ǰ������ΪXС����  
		//��ǰ����XС�����˶�����ǰ���е�ǰλ��  Ŀ��λ���бȽϴ����ǽ   �ǵ�ǰλ�õ� �Ƕ�̬ǽ   ��Ŀ��λ�õ��Ƕ�̬ǽ
		//  (-)<---NeighborCrane--------------target------------------Current-----------------(+)
		else if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			log.Debug()<<"��������Ϊ X_DES��(-)<---NeighborCrane-----target----Current-----(+)��ȡ�ϴ�ֵ neighborX_Max ��ΪwallX"<<endl;
			wallX=neighborX_Max;
			wallType=wallType_X_Max;
			log.Debug()<<"wallX = "<<neighborX_Max<<"  wallType= "<<wallType_X_Max<<endl;
			log.Debug()<<"���̷���true......"<<endl;
			ret=true;
			return ret;

		}

		log.Debug()<<"ret="<<ret<<"  returned"<<endl;

		return ret;

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

	return ret;
}



//2019.3.24 zhangyuhong add
string WALL_WHOLE_ORDER::getWallTypeString(long wallType)
{
	string functionName = "WALL_WHOLE_ORDER :: getWallTypeString()";
	LOG log(functionName, AUTO_CATCH_PID);

	//���費�ܻ��
	string wallTypeString="";

	try
	{
		if (wallType == 1)
		{
			wallTypeString = "WALL_DYNAMIC";
		}
		else if (wallType == 2)
		{
			wallTypeString = "WALL_STATIC";
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
	return wallTypeString;
}
