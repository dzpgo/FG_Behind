#include "CONDITION_TARGET_AREA_IS_CLEAN.h"



using namespace Monitor;



CONDITION_TARGET_AREA_IS_CLEAN :: CONDITION_TARGET_AREA_IS_CLEAN(void)
{


}



CONDITION_TARGET_AREA_IS_CLEAN :: ~CONDITION_TARGET_AREA_IS_CLEAN(void)
{



}




bool CONDITION_TARGET_AREA_IS_CLEAN ::judge(string craneNO, string movingDirection, long currentX , long targetX, CranePLCStatusBase  neightborCranePLCStatusBase)
{


	string functionName = "CONDITION_TARGET_AREA_IS_CLEAN :: judge()";
	LOG log(functionName, AUTO_CATCH_PID);
	
	//��������������
	bool ret=false;

	try
	{

		//�ж��ٽ��г��Ƿ��ڱ�����ҵ��Χ��
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			//2018.10.16 zhangyuhong add
			//���1.........................
			//---Current---target----NeighborCrane--->
			if( neightborCranePLCStatusBase.getXAct() - targetX <= RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES && neightborCranePLCStatusBase.getXAct() > targetX)
			{
				log.Debug()<<"�ƶ�����ΪX������(-)---Current---target----NeighborCrane--->(+)  NeighborCrane��target���С�ڰ�ȫ���룬���̷���false......"<<endl;
				ret=false;
				return ret;
			}
			//���2.........................
			//---Current---NeighborCrane---target--->
			if (neightborCranePLCStatusBase.getXAct() >= currentX && neightborCranePLCStatusBase.getXAct() <= targetX)
			{
				log.Debug()<<"�ƶ�����ΪX������(-)---Current---NeighborCrane---target--->(+)  NeighborCraneλ��currentX��targetX֮�䣬���̷���false......"<<endl;
				ret=false;
				return ret;
			}
			log.Debug()<<"�ƶ�����ΪX�������ڳ����ڱ�����ҵ��Χ�ڣ����̷���true......"<<endl;
			ret=true;
			return ret;
		}
		else if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			//2018.10.16 zhangyuhong add
			//���1.........................
			//<---NeighborCrane---target---Current---
			if ( targetX - neightborCranePLCStatusBase.getXAct() <= RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES && neightborCranePLCStatusBase.getXAct() < targetX )
			{
				log.Debug()<<"�ƶ�����ΪX��С����(-)<---NeighborCrane---target---Current---(+)  NeighborCrane��target���С�ڰ�ȫ���룬���̷���false......"<<endl;
				ret=false;
				return ret;
			}
			//���2.........................
			//<---target---NeighborCrane---Current---
			if ( neightborCranePLCStatusBase.getXAct() >= targetX && neightborCranePLCStatusBase.getXAct() <= currentX)
			{
				log.Debug()<<"�ƶ�����ΪX��С����(-)<---target---NeighborCrane---Current---(+)  NeighborCraneλ��currentX��targetX֮�䣬���̷���false......"<<endl;
				ret=false;
				return ret;
			}
			log.Debug()<<"�ƶ�����ΪX��С����(-)<---NeighborCrane---target---Current---(+)  �ڳ����ڱ�����ҵ��Χ�ڣ����̷���true......"<<endl;
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
