#include "CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA.h"



using namespace Monitor;



CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA :: CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA(void)
{


}



CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA :: ~CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA(void)
{



}




bool CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA ::judge(string craneNO, string movingDirection, long currentX , long targetX, CranePLCStatusBase  neightborCranePLCStatusBase)
{


	string functionName = "CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA :: judge()";
	LOG log(functionName, AUTO_CATCH_PID);

	//��������ҪҪ��������
	bool ret=false;

	try
	{

		long neighborTargetX=CranePLCOrderBase::PLC_INT_NULL;

		if(neightborCranePLCStatusBase.getHasCoil()==0)
		{
			log.Debug()<<"�����г�Ŀǰ�޾���Ŀ��λ��Ϊ���X���꣺neightborCranePLCStatusBase.getPlanUpX()"<<endl;
			neighborTargetX=neightborCranePLCStatusBase.getPlanUpX();
		}
		if(neightborCranePLCStatusBase.getHasCoil()==1)
		{
			log.Debug()<<"�����г�Ŀǰ�о���Ŀ��λ��Ϊ���X���꣺neightborCranePLCStatusBase.getPlanDownX()"<<endl;
			neighborTargetX=neightborCranePLCStatusBase.getPlanDownX();
		}

		//���neighborTargetX ��9 ��ô�Ե�ǰλ�����
		if(neighborTargetX==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"�����г���Ŀ��λ��X�����Ƿ�9������Ŀ��λ���趨Ϊ��ǰXλ�ã�neightborCranePLCStatusBase.getXAct()"<<endl;
			neighborTargetX=neightborCranePLCStatusBase.getXAct();
		}

		//�ж��ٳ��Ƿ�����ͼҪ���뱾��
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			//2018.10.16 zhangyuhong add
			//���1...........................
			//---Current---target---NeighborCrneTarget--->
			if ( neighborTargetX - targetX <= RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES && neighborTargetX > targetX)
			{
				log.Debug()<<"�ƶ�����ΪX������(-)---Current---target---NeighborCrneTarget--->(+)   NeighborCrneTarget��target���С�ڰ�ȫ���룬���̷���false......"<<endl;
				ret=false;
				return ret;
			}
			//���2...........................
			//---Current---NeighborCrneTarget---target--->
			if ( neighborTargetX >= currentX && neighborTargetX <= targetX)
			{
				log.Debug()<<"�ƶ�����ΪX������(-)---Current---NeighborCrneTarget---target--->(+)   NeighborCrneTargetλ��currentX��targetX֮�䣬���̷���false......"<<endl;
				ret=false;
				return ret;
			}
			//���3...........................
			//---NeighborCrneTarget---Current---target--->
			if ( neighborTargetX < currentX)
			{
				log.Debug()<<"�ƶ�����ΪX������(-)---NeighborCrneTarget---Current---target--->(+)   NeighborCrneTargetС��currentX�����̷���false......"<<endl;
				ret=false;
				return ret;
			}
			log.Debug()<<"�ƶ�����ΪX�������г������ƶ������̷���true......"<<endl;
			ret=true;
			return ret;			
		}
		else if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			//2018.10.16 zhangyuhong add
			//���1...........................
			//<---NeighborCraneTarget---target---Current---
			if (targetX - neighborTargetX <= RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES && targetX > neighborTargetX)
			{
				log.Debug()<<"�ƶ�����ΪX��С����(-)<---NeighborCraneTarget---target---Current---(+)   NeighborCrneTargetX��targetX���С�ڰ�ȫ���룬���̷���false......"<<endl;
				ret=false;
				return ret;
			}
			//���2...........................
			//<---target---NeighborCraneTarget---Current---
			if (neighborTargetX >= targetX && neighborTargetX <= currentX)
			{
				log.Debug()<<"�ƶ�����ΪX��С����(-)<---target---NeighborCraneTarget---Current---(+)   NeighborCrneTargetXλ��targetX��currentX֮�䣬���̷���false......"<<endl;
				ret=false;
				return ret;
			}
			//���3...........................
			//<---target---Current---NeighborCraneTarget---
			if (neighborTargetX > currentX)
			{
				log.Debug()<<"�ƶ�����ΪX��С����(-)<---target---Current---NeighborCraneTarget---(+)   NeighborCrneTargetX����currentX�����̷���false......"<<endl;
				ret=false;
				return ret;
			}
			log.Debug()<<"�ƶ�����ΪX��С�����г������ƶ������̷���true......"<<endl;
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
