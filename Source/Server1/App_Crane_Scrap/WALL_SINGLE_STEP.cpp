#include "WALL_SINGLE_STEP.h"



using namespace Monitor;


const long WALL_SINGLE_STEP::WALL_DYNAMIC=1;
const long WALL_SINGLE_STEP::WALL_STATIC=2;

WALL_SINGLE_STEP :: WALL_SINGLE_STEP(void)
{


}



WALL_SINGLE_STEP :: ~WALL_SINGLE_STEP(void)
{



}





bool WALL_SINGLE_STEP ::getWall(string craneNO, string movingDirection,  CranePLCStatusBase  neightborCranePLCStatusBase, long& wallX, long& wallType)
{


	string functionName = "WALL_SINGLE_STEP :: getWall()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool ret=false;
	
	try
	{
		log.Debug()<<"����="<<craneNO<<"   �ƶ�����="<<movingDirection<<endl;
		log.Debug()<<"�ڳ�="<<neightborCranePLCStatusBase.getCraneNO()<<"  �ڳ���ǰ��X="<<neightborCranePLCStatusBase.getXAct()<<endl;

		ret=true;
		//��ǰ�г��ĵ�ǰλ��
		long neighborCurrentX=neightborCranePLCStatusBase.getXAct();
		log.Debug()<<"�ڳ���ǰX���� neighborCurrentX="<<neighborCurrentX<<endl;
		log.Debug()<<"�ڳ���ǰ�о��� getHasCoil() ="<<neightborCranePLCStatusBase.getHasCoil()<<endl;

		//��ǰ�г���Ŀ��λ��
		long neighborTargetX=CranePLCOrderBase::PLC_INT_NULL;

		if(neightborCranePLCStatusBase.getHasCoil()==0)
		{
			//�չ����Ŀ��λ��Ϊ���Ŀ��λ��X
			neighborTargetX=neightborCranePLCStatusBase.getPlanUpX();
		}
		if(neightborCranePLCStatusBase.getHasCoil()==1)
		{
			//�ع����Ŀ��λ��Ϊ���Ŀ��λ��X
			neighborTargetX=neightborCranePLCStatusBase.getPlanDownX();
		}

		log.Debug()<<"�ڳ���Ŀ���X���꣺targetX="<<neighborTargetX<<endl;

		//����г���Ŀ��λ�÷�9 ˵���г���ǰ���Զ������г��г�ͣ��ԭ��
		if(neighborTargetX==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"�ڳ���Ŀ���X���� targetX=PLC_INT_NULL ��9���õ�ǰ����X currentX�滻...."<<endl;
			neighborTargetX=neightborCranePLCStatusBase.getXAct();
			log.Debug()<<"�ڳ���Ŀ���X���꣨getXAct�� targetX="<<neighborTargetX<<endl;
		}
		//ǰ������ΪX���� 
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			log.Debug()<<"������ǰ������ΪX������ movingDirection="<<movingDirection<<endl;
			//(-)------Current-----------------------------target-----------------NeighborCrane-->(+)
			//��ǰ����X�����˶�����ǰ���е�ǰλ��  Ŀ��λ���бȽ�С����ǽ  �ǵ�ǰλ�õ� �Ƕ�̬ǽ����Ŀ��λ�õ��Ǿ�̬ǽ
			

			if(abs(neighborCurrentX-neighborTargetX)<=100)
			{
				log.Debug()<<"�ڳ���λ......"<<endl;
				wallX=neighborTargetX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"ǽ���� wallType is WALL_STATIC ��̬�ģ�����ǽ����ӦΪ�����г���Ŀ��Xλ������ wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}

			//���һ��------NeighborCrane------neighborTargetX----->
			if(  neighborCurrentX< neighborTargetX)
			{
				log.Debug()<<"�ڳ��ĵ�ǰXλ������ < �ڳ���Ŀ��Xλ������......"<<endl;
				wallX=neighborCurrentX;
				wallType=WALL_SINGLE_STEP::WALL_DYNAMIC;
				log.Debug()<<"ǽ���� wallType is WALL_DYNAMIC ��̬�ģ� ����ǽ����ӦΪ�ڳ��ĵ�ǰXλ������ wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
			//�������------neighborTargetX------NeighborCrane----->
			else if(neighborCurrentX>neighborTargetX)
			{
				log.Debug()<<"�ڳ��ĵ�ǰXλ������ > �ڳ���Ŀ��Xλ������......"<<endl;
				wallX=neighborTargetX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"ǽ���� wallType is WALL_STATIC ��̬�ģ�����ǽ����ӦΪ�����г���Ŀ��Xλ������ wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
			//����������
			else if(neighborCurrentX==neighborTargetX)
			{
				log.Debug()<<"�ڳ��ĵ�ǰXλ������ = �ڳ���Ŀ��Xλ������......"<<endl;
				wallX=neighborCurrentX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"ǽ���� wallType is WALL_STATIC ��̬�ģ�����ǽ����ӦΪ�����г��ĵ�ǰXλ�ã�=Ŀ��Xλ�ã����� wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
		}
		//ǰ������ΪXС����  
		//��ǰ����XС�����˶�����ǰ���е�ǰλ��  Ŀ��λ���бȽϴ����ǽ   �ǵ�ǰλ�õ� �Ƕ�̬ǽ   ��Ŀ��λ�õ��Ƕ�̬ǽ
		//  (-)<---NeighborCrane--------------target------------------Current-----------------(+)
		else if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			log.Debug()<<"������ǰ������ΪX��С���� movingDirection="<<movingDirection<<endl;

			if(abs(neighborCurrentX-neighborTargetX)<30)
			{
				log.Debug()<<"�ڳ���λ......"<<endl;
				wallX=neighborTargetX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"ǽ���� wallType is WALL_STATIC ��̬�ģ�����ǽ����ӦΪ�����г���Ŀ��Xλ������ wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}

			//���һ��(-)<------neighborTargetX------NeighborCrane-----(+)
			if(neighborCurrentX> neighborTargetX)
			{
				log.Debug()<<"�ڳ��ĵ�ǰXλ������ > �����г���Ŀ��Xλ������......"<<endl;
				wallX=neighborCurrentX;
				wallType=WALL_SINGLE_STEP::WALL_DYNAMIC;
				log.Debug()<<"ǽ���� wallType is WALL_DYNAMIC ��̬�ģ� ����ǽ����ӦΪ�����г��ĵ�ǰXλ������ wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
			//�������(-)<------NeighborCrane------neighborTargetX-----(+)
			else if(neighborCurrentX<neighborTargetX)
			{
				log.Debug()<<"�����г��ĵ�ǰXλ������ < �����г���Ŀ��Xλ������......"<<endl;
				wallX=neighborTargetX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"ǽ���� wallType is WALL_STATIC ��̬�ģ� ����ǽ����ӦΪ�����г���Ŀ��Xλ������ wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
			//����������
			else if(neighborCurrentX==neighborTargetX)
			{
				log.Debug()<<"�����г��ĵ�ǰXλ������ = �����г���Ŀ��Xλ������......"<<endl;
				wallX=neighborCurrentX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"ǽ���� wallType is WALL_STATIC ��̬�ģ� ����ǽ����ӦΪ�����г��ĵ�ǰXλ�ã�=Ŀ��Xλ�ã����� wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
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
