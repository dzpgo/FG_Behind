#include "CLOSE_TO_DYNAMIC_WALL.h"



using namespace Monitor;





CLOSE_TO_DYNAMIC_WALL :: CLOSE_TO_DYNAMIC_WALL(void)
{


}



CLOSE_TO_DYNAMIC_WALL :: ~CLOSE_TO_DYNAMIC_WALL(void)
{



}



//����Ƕ�̬��ǽ�ڣ��������Է�����Զȥ�����ҶԷ���Ŀ��Զ���ҵ�Ŀ�� �����Ѿ�������һ���ľ��룬��ô����ȥ��ȥĿ��λ��
//����Ƕ�̬��ǽ�ڣ��������Է�����Զȥ�����ҶԷ���Ŀ������ҵ�Ŀ�꣬�����Ѿ�������һ���ľ��룬��ô����ȥ������ǰ������
bool CLOSE_TO_DYNAMIC_WALL ::closeToWall(string craneNO, string direction, long targetX,CranePLCStatusBase  cranePLCStatusBase, CranePLCStatusBase  neightborCranePLCStatusBase , long& XWallLimit)
{
	string functionName = "CLOSE_TO_DYNAMIC_WALL :: closeToWall()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�����������������ܶ�������ȥ�ĵط���ԭ��
	XWallLimit=cranePLCStatusBase.getXAct();
	bool  retCanMove=false;

	try
	{
		log.Info()<<"......................................................................................����***��̬ǽ***�����߼�����........................................................................................................"<<endl;
		string neighborCraneNO = neightborCranePLCStatusBase.getCraneNO();
		//**************************************************************************************************************************************************************
		//*
		//*												step1. �жϱ������ڳ������Ƿ�����  �жϱ�׼����С����������趨Ϊ 22��
		//*
		//**************************************************************************************************************************************************************
		long distanceBetweenCranes=abs(cranePLCStatusBase.getXAct()-neightborCranePLCStatusBase.getXAct());
		log.Debug()<<"step 1 �ж����������Ƿ�����......"<<endl;
		log.Debug()<<"����="<<craneNO<<"���ڳ�="<<neighborCraneNO<<" ��ǰ���� ="<<distanceBetweenCranes<<endl;

		if(distanceBetweenCranes < RED_LINE_BASIC_DATA::FOLLOW_MIN_DISTANCE)
		{
			log.Debug()<<"Ŀǰ�˾��� <  ׷����С�������루27000��   ���̷���false���г������ƶ���"<<endl;
			retCanMove=false;
			return retCanMove;
		}
		else
		{
			log.Debug()<<"Ŀǰ�˾��� >  ׷����С�������루27000��   ������"<<endl;
		}

		//**************************************************************************************************************************************************************
		//*
		//*												step2. �жϱ����������ڳ������Ƿ�һ��
		//*
		//**************************************************************************************************************************************************************
		log.Debug()<<"step 2 �жϱ����������ڳ������Ƿ�һ��......"<<endl;
		if( direction==MOVING_DIR::DIR_X_INC  && neightborCranePLCStatusBase.getXDirectPositive()==1 )
		{
			log.Debug()<<"����="<<craneNO<<" ����Ϊ�����ڳ�="<<neighborCraneNO<<" ����Ϊ���򣡱������ڳ��˶�����ͬΪ��X������ DIR_X_INC....."<<endl;
		}
		else if( direction==MOVING_DIR::DIR_X_DES  && neightborCranePLCStatusBase.getXDirectNegative()==1 )
		{
			log.Debug()<<"����="<<craneNO<<" ����Ϊ�����ڳ�="<<neighborCraneNO<<" ����Ϊ���򣡱������ڳ��˶�����ͬΪ��X��С���� DIR_X_DES....."<<endl;
		}
		else
		{
			//������ʵ�Ѿ��ų���2������������ֻ�ܿ�����ͬ�����������Ա������ܶ�
			log.Debug()<<"����="<<craneNO<<"���ڳ�="<<neighborCraneNO<<"  2������һ�£����̷���false�������ɿ����ļ���ǽλ������Ϊ��ǰ�г�λ�ã�"<<endl;
			log.Debug()<<"XWallLimit="<<XWallLimit<<endl;
			retCanMove=false;
			return retCanMove;
		}

		//**************************************************************************************************************************************************************
		//*
		//*												step3. �ж�ǰ����Ŀ���Ƿ�Զ�ڱ�����Ŀ��
		//*
		//**************************************************************************************************************************************************************
		log.Debug()<<"step 3 �ж��ڳ���Ŀ���Ƿ�Զ�ڱ�����Ŀ��......"<<endl;
		log.Debug()<<"�ڳ����Ƿ��о��� HasCoil="<<neightborCranePLCStatusBase.getHasCoil()<<endl;

		//�����ڳ��ĵ�ǰX����Ϊ�ڳ���Ŀ��X�����ʼֵ
		long targetXNeighbor=neightborCranePLCStatusBase.getXAct();
		if(neightborCranePLCStatusBase.getHasCoil()==0)
		{
			log.Info()<<"�ڳ�="<<neighborCraneNO<<" �չ�...................."<<endl;
			targetXNeighbor=neightborCranePLCStatusBase.getPlanUpX();
		}
		else if(neightborCranePLCStatusBase.getHasCoil()==1)
		{	
			log.Info()<<"�ڳ�="<<neighborCraneNO<<" �ع�...................."<<endl;
			targetXNeighbor=neightborCranePLCStatusBase.getPlanDownX();
		}
		log.Debug()<<"����ڳ�="<<neighborCraneNO<<" ��Ŀ��X���� targetXNeighbor="<<targetXNeighbor<<endl;

		if(targetXNeighbor==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"�ڳ���Ŀ��λ��X���� targetXNeighbor==PLC_INT_NULL ��9��׼����currentX ���� �滻 targetXNeighbor"<<endl;
			targetXNeighbor=neightborCranePLCStatusBase.getXAct();
			log.Debug()<<"��currentX ���� �滻��� targetXNeighbor="<<targetXNeighbor<<endl;
		}


		//**************************************************************************************************************************************************************
		//*
		//*												step3. �ж�ǰ����Ŀ���Ƿ�Զ�ڱ�����Ŀ��
		//*												���һ��(-)-------------mytarget-----------------neighborTarget---->(+)
		//*
		//**************************************************************************************************************************************************************
		if(direction==MOVING_DIR::DIR_X_INC)
		{
			log.Debug()<<"���һ��(-)------myTarget-------neighborTarget---->(+)�������ƶ���X_INC"<<endl;
			if(targetXNeighbor - targetX > RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES + RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE  )
			{
				log.Debug()<<"����="<<craneNO<<"��Ŀ��X="<<targetX<<"���ڳ�="<<neighborCraneNO<<"��Ŀ��X="<<targetXNeighbor<<"��2�߾���>��ȫ���루25000+100��......"<<endl;
				log.Debug()<<"����="<<craneNO<<"���Կ�ʼ�ƶ������̴����� true������ֱ���ƶ����ҷ�Ŀ��λ��......ǽ����λ��XWallLimit��Ϊ����Ŀ��targetX"<<endl;
				log.Debug()<<"XWallLimit=targetX"<<endl;
				XWallLimit=targetX;
				log.Debug()<<"XWallLimit="<<XWallLimit<<endl;
				retCanMove=true;
				return retCanMove;
			}
			else
			{
				log.Debug()<<"����="<<craneNO<<"��Ŀ��X="<<targetX<<"���ڳ�="<<neighborCraneNO<<"��Ŀ��X="<<targetXNeighbor<<"��2�߾���<��ȫ���루25000+100��......"<<endl;
				log.Debug()<<"�������Կ�ʼ�ƶ������̴�����true��������ֱ���ƶ����ҷ�Ŀ��λ�ã���Ҫ�ƶ���......XWallLimit"<<endl;
				log.Debug()<<"XWallLimit=�ڳ���Ŀ��X���� - ��ȫ���루25000+100��"<<endl;
				XWallLimit=targetXNeighbor  -  (RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES + RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE);
				log.Debug()<<"�����õ���XWallLimit="<<XWallLimit<<endl;
				retCanMove=true;
				return retCanMove;
			}
		}

		//**************************************************************************************************************************************************************
		//*
		//*												step3. �ж�ǰ����Ŀ���Ƿ�Զ�ڱ�����Ŀ��
		//*												�������(-)<---------neighborTarget--------------------mytarget---(+)
		//*
		//**************************************************************************************************************************************************************
		if(direction==MOVING_DIR::DIR_X_DES)
		{
			log.Debug()<<"�������(-)<-------neighborTarget---------mytarget---(+)�������ƶ���X_DES"<<endl;
			if(targetX - targetXNeighbor>RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES  +  RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE  )
			{
				log.Debug()<<"����="<<craneNO<<"��Ŀ��X="<<targetX<<"���ڳ�="<<neighborCraneNO<<"��Ŀ��X="<<targetXNeighbor<<"��2�߾���>��ȫ���루25000+100��......"<<endl;
				log.Debug()<<"����="<<craneNO<<"���Կ�ʼ�ƶ������̴����� true������ֱ���ƶ����ҷ�Ŀ��λ��......ǽ����λ��XWallLimit��Ϊ����Ŀ��targetX"<<endl;
				log.Debug()<<"XWallLimit=targetX"<<endl;
				XWallLimit=targetX;
				log.Debug()<<"XWallLimit="<<XWallLimit<<endl;
				retCanMove=true;
				return retCanMove;
			}
			else
			{
				log.Debug()<<"����="<<craneNO<<"��Ŀ��X="<<targetX<<"���ڳ�="<<neighborCraneNO<<"��Ŀ��X="<<targetXNeighbor<<"��2�߾���<��ȫ���루25000+100��......"<<endl;
				log.Debug()<<"�������Կ�ʼ�ƶ������̴�����true��������ֱ���ƶ����ҷ�Ŀ��λ�ã���Ҫ�ƶ���......XWallLimit"<<endl;
				log.Debug()<<"XWallLimit=�ڳ���Ŀ��X���� + ��ȫ���루25000+100��"<<endl;
				XWallLimit=targetXNeighbor  +  (RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES + RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE);
				log.Debug()<<"�����õ���XWallLimit="<<XWallLimit<<endl;
				retCanMove=true;
				return retCanMove;
			}
		}	
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
	return retCanMove;
}
