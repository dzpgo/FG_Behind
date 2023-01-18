#include "CLOSE_TO_STATIC_WALL.h"



using namespace Monitor;





CLOSE_TO_STATIC_WALL :: CLOSE_TO_STATIC_WALL(void)
{


}



CLOSE_TO_STATIC_WALL :: ~CLOSE_TO_STATIC_WALL(void)
{



}




bool CLOSE_TO_STATIC_WALL ::closeToWall(string craneNO, string direction,long currentX, long wallX, long& XlimitToTheWall)
{
	string functionName = "CLOSE_TO_STATIC_WALL :: getCraneNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�����ǲ��ܶ�����
	bool  retCanMove=false;
	XlimitToTheWall=currentX;
	try
	{
		log.Info()<<"......................................................................................����***��̬ǽ***�����߼�����........................................................................................................"<<endl;
		log.Debug()<<"����="<<craneNO<<"  �ƶ�����="<<direction<<"  ��ǰ��X="<<currentX<<" ǽX wallX="<<wallX<<endl;
		if(direction==MOVING_DIR::DIR_X_INC)
		{
			log.Debug()<<"��̬ǽ�������ҷ��г��ƶ�����ΪX����......(-)------Current-----------target--------------------WALL--------------->(+)"<<endl;
			//ǰ������ΪX����  
			//(-)------Current-----------target--------------------WALL--------------->(+)
			XlimitToTheWall=wallX 
							- RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES 
							- RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE;
			log.Debug()<<"��ȡ��ǽ��X����λ�� XlimitToTheWall="<<XlimitToTheWall<<endl;
			if(XlimitToTheWall>currentX)
			{
				log.Debug()<<"��ǽ��X����λ�� > �����ĵ�ǰλ�� ����������£��г������ƶ������̷���true......"<<endl;
				retCanMove=true;
			}
			else
			{
				log.Debug()<<"��ǽ��X����λ�� < �����ĵ�ǰλ�� ����������£��г������ƶ������̷���false�� ���� ��ǽ��X����λ�� ����Ϊ �����ĵ�ǰλ��......"<<endl;
				XlimitToTheWall=currentX;
				retCanMove=false;
			}
		}
		else if(direction==MOVING_DIR::DIR_X_DES)
		{
			log.Debug()<<"��̬ǽ�������ҷ��г��ƶ�����ΪX��С......(-)<-----WALL------------target------------------Current-----------------(+)"<<endl;
			//ǰ������ΪXС����  
			// (-)<-----WALL------------target------------------Current-----------------(+)
			XlimitToTheWall=wallX
							+RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES
							+RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE;
			log.Debug()<<"��ȡ��ǽ��X����λ�� XlimitToTheWall="<<XlimitToTheWall<<endl;
			if(XlimitToTheWall < currentX)
			{
				log.Debug()<<"��ǽ��X����λ�� < �����ĵ�ǰλ�� ����������£��г������ƶ������̷���true......"<<endl;
				retCanMove=true;
			}
			else
			{
				log.Debug()<<"��ǽ��X����λ�� > �����ĵ�ǰλ�� ����������£��г������ƶ������̷���false�� XlimitToTheWall��ֵ��ΪcurrentX"<<endl;
				XlimitToTheWall=currentX;
				retCanMove=false;
			}
		}
		log.Debug()<<"�������ƶ����� ="<<direction<<endl;
		log.Debug()<<"������ǰXλ������ ="<<currentX<<endl;
		log.Debug()<<"���������ƶ�����ǽX���꼫��λ�� ="<<XlimitToTheWall<<endl;
		log.Debug()<<"�����Ƿ�����ƶ�����ֵ ="<<retCanMove<<"  returned"<<endl;
		return retCanMove;
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
