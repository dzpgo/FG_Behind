#include "JUDGE_BEFORE_MOVING.h"
#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"



using namespace Monitor;



JUDGE_BEFORE_MOVING :: JUDGE_BEFORE_MOVING(void)
{
}



JUDGE_BEFORE_MOVING :: ~JUDGE_BEFORE_MOVING(void)
{
}



//����false����ζ�Ų��ܶ���
//����true��ζ���ܶ��������ʱ��Ҫ���ܹ������X
bool JUDGE_BEFORE_MOVING ::judge(long orderNO, string craneNO, long currentX , long targetX, long& canReachX)
{


	string functionName = "MOVING_DIR :: judge()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�ٶ��ǲ��ܶ����� ��ȥ�ĵط����ǵ�ǰλ��
	bool retCanMove=false;
	canReachX=currentX;

	try
	{
		log.Debug()<<"-----------------------------JUDGE START----------------------------------------------------------------------"<<endl;
		log.Debug()<<"��ʼ���г��ƶ�ǰ�����ж� JUDGE_BEFORE_MOVING ::judge ��������4���ж�................"<<endl;

		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp1 ����˶��ķ���
		//*
		//*********************************************************************************************************************************************************************************************
		log.Debug()<<" Step1����鵱ǰ�г��Ĵ�(X)�ƶ�����...."<<endl;
		string movingDirection = MOVING_DIR::getDirection(craneNO, currentX, targetX);		
		log.Debug()<<"�ƶ����� movingDirection="<<movingDirection<<endl;
		//������˶������ж�Ϊԭ�ص㣬��ôֱ�ӷ���true����ֻ��С���ǿ��Ե�
		//2018.3.14 zhangyuhong add
		if(movingDirection==MOVING_DIR::DIR_X_ON_SPOT)
		{
			log.Debug()<<"�ƶ����� movingDirection==DIR_X_ON_SPOT  �г��Ĵ��ƶ�����Ϊԭ�ص㣬Judge����true...."<<endl;
			log.Debug()<<"canReachX="<<canReachX<<endl;
			log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
			retCanMove=true;
			return retCanMove;
		}

		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp2 �����˶��ķ�����ǰ��������г���
		//*
		//*********************************************************************************************************************************************************************************************
		log.Debug()<<"Step2��׼����ȡ�����г���..."<<endl;
		string neightborCraneNO=NEIGHBOR_AHEAD::getCraneNO(craneNO,movingDirection);
		log.Debug()<<"�����г��� neightborCraneNO="<<neightborCraneNO<<endl;		
		//ǰ�����г�������Ҫ������һ���ж��ˣ�����true���г����н�����ȫ��
		if(neightborCraneNO==NEIGHBOR_AHEAD::NOBODY)
		{
			log.Debug()<<"�����г��� neightborCraneNO==NOBODY  �������г�����������true���г�����ֱ���ƶ���Ŀ��targetX���ǿ��ƶ�canReachX"<<endl;
			canReachX=targetX;
			log.Debug()<<"canReachX="<<canReachX<<endl;
			log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
			retCanMove=true;
			return retCanMove;
		}
		//�г��Ų�����˵���б��г���ʧ���ˣ���ô��������Χfalse
		if(neightborCraneNO==NEIGHBOR_AHEAD::UNKNOW)
		{
			log.Debug()<<"�����г��� neightborCraneNO==UNKNOW �����г���δ֪����������false���г������ƶ�....."<<endl;
			log.Debug()<<"canReachX="<<canReachX<<endl;
			log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
			retCanMove=false;
			return retCanMove;
		}


		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp 3����ȡ�������ٽ��г���PLC״̬
		//*
		//*********************************************************************************************************************************************************************************************
		//��Ŀǰλ�����µĴ���������ǰ���������г���
		log.Debug()<<"setp 3��׼����ȡ�������ٽ��г���PLC״̬......"<<endl;
		log.Debug()<<"�ڵ�ǰ�г��Ĵ��ƶ�����X��·�����������г����г���="<<neightborCraneNO<<endl;
		
		//setp 4��ñ������ٽ��г���PLC״̬
		log.Debug()<<"׼����ȡ  ��ǰ�г�="<<craneNO<<"  ��  �����г�="<<neightborCraneNO<<"  ��PLCʵʱ״̬..."<<endl;

		CranePLCStatusBase  neightborCranePLCStatusBase;
		bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(neightborCraneNO, neightborCranePLCStatusBase);
		//log.Debug()<<"��ȡ�����г���PLCʵʱ״̬���� getNeighborPLCStatus �ķ���ֵ��bool���ͣ�="<<ACTION_COMMON_FUNCTION::TrueOrFlase(ret_getPLCStatus)<<endl;
		if(ret_getPLCStatus==false)
		{
				log.Debug()<<"��ȡ�����г���PLCʵʱ״̬ʧ�ܣ�����������false���г������ƶ�......"<<endl;
				log.Debug()<<"canReachX="<<canReachX<<endl;
				log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
				retCanMove=false;
				return retCanMove;
		}
		log.Debug()<<"�����г���="<<neightborCraneNO<<"  ���ʵʱ���� X="<<neightborCranePLCStatusBase.getXAct()<<endl;

		//��ñ������г�PLC״̬
		CranePLCStatusBase  cranePLCStatusBase;
		ret_getPLCStatus=CraneMonitor::getInstance()->getPLCStatus(cranePLCStatusBase);
		//log.Debug()<<"��ȡ��ǰ�г���PLCʵʱ״̬���� getPLCStatus �ķ���ֵ��bool���ͣ�="<<ACTION_COMMON_FUNCTION::TrueOrFlase(ret_getPLCStatus)<<endl;		
		if(ret_getPLCStatus==false)
		{
				log.Debug()<<"��ȡ�൱ǰ����PLCʵʱ״̬ʧ�ܣ�����������false���г������ƶ�......"<<endl;
				log.Debug()<<"canReachX="<<canReachX<<endl;
				log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
				retCanMove=false;
				return retCanMove;
		}
		log.Debug()<<"��ǰ�г���="<<craneNO<<"  ���ʵʱ���� X="<<cranePLCStatusBase.getXAct()<<endl;

		
		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp 4�������ڳ�������ģʽ-�Զ���������Ӧ�߼�����
		//*
		//*********************************************************************************************************************************************************************************************
		//setp 4 �����ڳ�������ģʽ�����߼�����		
		if(neightborCranePLCStatusBase.getControlMode()==CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
					log.Debug()<<"----------------------------Step4�������ڳ����Զ���ģʽ���߼�����------------------------------------------------"<<endl;
					log.Debug()<<"ǰ�������г���="<<neightborCraneNO<<"�Ŀ���ģʽΪ AUTO..........."<<endl;
					
					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.1�����Ŀ�������Ƿ����ڳ�
					//*
					//*********************************************************************************************************************************************************************************************
					//step4.1 ���Ŀ�������Ƿ����ڳ�
					log.Debug()<<"-----------------------------Step4.1�����Ŀ�������Ƿ����ڳ�----START---------------------------------------------------"<<endl;
					bool ret_Target_Area_Is_Clean=CONDITION_TARGET_AREA_IS_CLEAN::judge(craneNO, movingDirection, currentX, targetX, neightborCranePLCStatusBase);					
					//log.Debug()<<"ret_Target_Area_Is_Clean = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(ret_Target_Area_Is_Clean)<<endl;
					log.Debug()<<"-----------------------------Step4.1�����Ŀ�������Ƿ����ڳ�----END------------------------------------------------------"<<endl;

					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.2������ڳ��Ƿ�Ҫ����Ŀ������
					//*
					//*********************************************************************************************************************************************************************************************
					//step4.2 ����ڳ��Ƿ�Ҫ����Ŀ������
					log.Debug()<<"-----------------------------Step4.2������ڳ��Ƿ�Ҫ����Ŀ������----START--------------------------------------------------"<<endl;
					bool ret_Nobody_is_Moving_To_TargetArea=CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA::judge(craneNO, movingDirection, currentX, targetX, neightborCranePLCStatusBase);					
					//log.Debug()<<"����ڳ��Ƿ�Ҫ����Ŀ��������(true=Ŀ���������ڳ�Ҫ����)��"<<ACTION_COMMON_FUNCTION::TrueOrFlase(ret_Nobody_is_Moving_To_TargetArea)<<endl;
					log.Debug()<<"-----------------------------Step4.2������ڳ��Ƿ�Ҫ����Ŀ������----END-----------------------------------------------------"<<endl;

					//2018.12.22 zhangyuhong add
					//������ǵͼ�������ô��Զ�����˳��������ڵ�����дΪΣ�ռ�false
					if(CranePrivilegeInterpreter::compareByCrane(craneNO,neightborCraneNO)==CranePrivilegeInterpreter::COMPARE_RESULT_LOW)
					{
						log.Info()<<"����="<<craneNO<<" �� �ڳ�="<<neightborCraneNO<<" �ȼ��ͣ���Զ�� ret_Nobody_is_Moving_To_TargetArea = false��"<<endl;
						ret_Nobody_is_Moving_To_TargetArea=false;
					}


					if(ret_Target_Area_Is_Clean==true && ret_Nobody_is_Moving_To_TargetArea==true)
					{
						log.Debug()<<"�����г��� AUTO ģʽ��Ŀ�����������״̬�����������г����ڽ���Ŀ�����򣬴���������true���г�����ֱ���ƶ���Ŀ���targetX���ɵ����canReachX"<<endl;
						canReachX=targetX;
						log.Debug()<<"canReachX="<<canReachX<<endl;
						retCanMove=true;
						log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
						return retCanMove;
					}

					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.3��Ŀ���������ڳ����ڳ�Ҫ����Ŀ������
					//*
					//*********************************************************************************************************************************************************************************************
					//step4.3 Ŀ���������ڳ����ڳ�Ҫ����Ŀ������	

					log.Debug()<<"-------------------------setp 4.3��Ŀ���������ڳ����ڳ�Ҫ����Ŀ������------START------------------------------"<<endl;
					log.Debug()<<"Step 4.3��Ŀ���������ڳ����ڳ�Ҫ����Ŀ�������г������ƶ���׼���������жϴ���......"<<endl;
					
					string priorityCraneVsNeighborCrane = CranePrivilegeInterpreter::COMPARE_RESULT_UNKNOW;					

					//2018.12.20 ZHANGYUHONG ADD 
					//����һ�㣬ֱ�����г��������ȼ���Ϊ����
					//���������������߳���
					priorityCraneVsNeighborCrane = CranePrivilegeInterpreter::compareByCrane(craneNO, neightborCraneNO);

					//�����ҵļ���ļ���������					
					if (priorityCraneVsNeighborCrane == CranePrivilegeInterpreter::COMPARE_RESULT_LOW)
					{
						OrderCurrentBase myCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

						//----------1��������ǵͼ��������ǿ���׷�����߼�����Ŀ��λ���������ҵļ���
						if ( true == if_Facing_Auto_Car_Low_Level(craneNO, currentX, targetX, movingDirection, cranePLCStatusBase, 
																						neightborCraneNO, neightborCranePLCStatusBase, canReachX) )
						{
							log.Info()<<"1������������ҳ��ȼ���"<<endl;
							priorityCraneVsNeighborCrane = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
						}
						//----------2��������ǵͼ���������4-5���ҵ�ָ���ǿչ�ȥPA1���ϣ����ҵ�ǰ��tagetX��PA1�����ϰ���X���������ҵļ���
						if ( true == FollowException_4_5::satifyException(craneNO, targetX, cranePLCStatusBase, myCraneOrderCurrent, neightborCraneNO, neightborCranePLCStatusBase))
						{
							log.Info()<<"2������4-5 PA1���ϣ������ȼ���"<<endl;
							priorityCraneVsNeighborCrane = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
						}
					}

					
					


					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.3.4���������ȼ� > �ڳ����ȼ�������===> ��Եͼ��������߼�
					//*
					//*********************************************************************************************************************************************************************************************
					//����� ===> ��������  
					if(priorityCraneVsNeighborCrane ==CranePrivilegeInterpreter::COMPARE_RESULT_HIGH)
					{
						log.Debug()<<"----------setp 4.3.4���������ȼ� > �ڳ����ȼ�������===> ��Եͼ��������߼�------START------------------------------"<<endl;
						log.Debug()<<"Step 4.3.4��������ָ�����ȼ� > �ڳ���ָ�����ȼ� ......"<<endl;
						log.Debug()<<"׼������ judge_Facing_Auto_Car_Low_Level() ���̴��� ......"<<endl;
						retCanMove=judge_Facing_Auto_Car_Low_Level(craneNO , currentX , targetX , movingDirection , cranePLCStatusBase, 
																												neightborCraneNO,  neightborCranePLCStatusBase,
																												canReachX);
						//2018.12.22 zhangyuhong add
						//�ϲ����´���
						//return retCanMove;
					}

					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.3.5���������ȼ� < �ڳ����ȼ�������===>��Ը߼��������߼�
					//*
					//*********************************************************************************************************************************************************************************************
					//�����===>�ಽ����
					else if(priorityCraneVsNeighborCrane==CranePrivilegeInterpreter::COMPARE_RESULT_LOW)
					{
						log.Debug()<<"----------setp 4.3.5���������ȼ� < �ڳ����ȼ�������===>��Ը߼��������߼�------START------------------------------"<<endl;
						log.Debug()<<"Step 4.3.5��������ָ�����ȼ� < �ڳ���ָ�����ȼ� ......"<<endl;
						log.Debug()<<"׼������ judge_Facing_Auto_Car_High_Level() ���̴��� ......"<<endl;
						retCanMove=judge_Facing_Auto_Car_High_Level(craneNO , currentX , targetX , movingDirection , cranePLCStatusBase, 
																neightborCraneNO,  neightborCranePLCStatusBase,
																canReachX);
						//2018.12.22 zhangyuhong add
						//�ϲ����´���
						//return retCanMove;
					}

					//20171117   -----------------------targetX--------------------canReachX----->
					if(movingDirection==MOVING_DIR::DIR_X_INC)
					{
						if(targetX<canReachX)
						{
							canReachX=targetX;
						}
					}
					//20171117   <------------------canReachX-------------------------targetX-----
					if(movingDirection==MOVING_DIR::DIR_X_DES)
					{
						if(targetX>canReachX)
						{
							canReachX=targetX;
						}
					}
					log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
					//20171117
					return retCanMove;  //20171117

		}//�Զ��г��жϽ���

		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp 5�������ڳ�������ģʽ-���Զ���������Ӧ�߼�����
		//*
		//*********************************************************************************************************************************************************************************************
		//setp 5 ǰ���������ֶ���
		//ǰ���������ֶ���  �����ֶ� ң�� �ȴ���һ��״̬		
		if(neightborCranePLCStatusBase.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Debug()<<"Step 5�������г��Ŀ���ģʽΪ  ���Զ�ģʽ  ......׼������judge_Facing_Manu_Car()����......"<<endl;
			retCanMove=judge_Facing_Manu_Car(craneNO , currentX , targetX , movingDirection , cranePLCStatusBase, 
																neightborCraneNO,  neightborCranePLCStatusBase,
																canReachX);
			return retCanMove;
		}
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





 //�����ǰ���Զ����ͼ�����ж�
bool JUDGE_BEFORE_MOVING ::judge_Facing_Auto_Car_Low_Level(string craneNO , long currentX , long targetX , string movingDirection , CranePLCStatusBase  cranePLCStatusBase,
																												 string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase ,
																												 long& canReachX)
{


	string functionName = "JUDGE_BEFORE_MOVING :: judge_Facing_Auto_Car_Low_Level()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�ٶ��ǲ��ܶ����� 
	bool retCanMove=false;
	canReachX=currentX;

	try
	{
					//����ǿ�ƣ��Է����ƣ���ô��ͼ��ǰ�ƽ���������ô��õ�ǰ������ǽ��
					long wallX;
					long wallType;

					//�Է������˶�
					bool neighborCarIsMoving=false;
					//�Է��������
					bool neighborCarIsLiftCoil=false;
					//�Է��������
					bool neighborCarIsDownCoil=false;	
					//�Է�����ֻ��С��
					//bool neighborCarIsOnlyYMoving=false;

					//**************************************************************************************************************************************************************
					//*
					//*															1.��ȡ�г�״̬��ֹͣ��������
					//*
					//***************************************************************************************************************************************************************
					//�жϴ��Ƿ��ڶ�  �����󳵲�����ֻ��С���������
					if( isACraneStopped(neightborCranePLCStatusBase) == false)
					{
						neighborCarIsMoving = true;
					}

					OrderCurrentBase neighborCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(neightborCraneNO);
					//�ж��Ƿ������Ҫô�չ������½���Ҫô�ع���������					
					if (isACraneLiftCoilDown(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true || 
						isACraneLiftCoilUp(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true)
					{
						neighborCarIsLiftCoil = true;
					}

					//�ж��Ƿ��������Ҫô�ع������½���Ҫô�չ���������
					if (isACraneDownCoilDown(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true || 
						isACraneDownCoilUp(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true)
					{
						neighborCarIsDownCoil = true;
					}

					//�ж��Ƿ�����ֻ�ƶ�С�����󳵲��������������ʵ�����/������ƣ����Ի�ȡ����̬ǽ
					/*if (isACraneOnlyYMoving(neightborCranePLCStatusBase) == true)
					{
						neighborCarIsOnlyYMoving = true;
					}*/

					//��ӡ���
					log.Info()<<"�г�Ŀǰ״̬......"<<endl;
					/*log.Info()<<"neighborCarIsMoving = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(neighborCarIsMoving)<<endl;
					log.Info()<<"neighborCarIsLiftCoil = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(neighborCarIsLiftCoil)<<endl;
					log.Info()<<"neighborCarIsDownCoil = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(neighborCarIsDownCoil)<<endl;*/
					//log.Info()<<"neighborCarIsOnlyYMoving = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(neighborCarIsOnlyYMoving)<<endl;


					//**************************************************************************************************************************************************************
					//*
					//*															2.�����г�״̬����ȡ�������Դﵽ��ǽ����ǽ����
					//*
					//***************************************************************************************************************************************************************
					if (neighborCarIsMoving == true)
					{
						log.Info()<<"�ڳ�="<<neightborCraneNO<<" ���ڴ��ƶ���...���Ի�ȡ����ǽX"<<endl;
						WALL_SINGLE_STEP::getWall(craneNO, movingDirection, neightborCranePLCStatusBase, wallX, wallType);
					}
					else if (neighborCarIsLiftCoil == true)
					{
						log.Info()<<"�ڳ�="<<neightborCraneNO<<"  ���������....���Ի�ȡ��̬ǽX..."<<endl;
						wallType=WALL_SINGLE_STEP::WALL_STATIC;
						wallX=neightborCranePLCStatusBase.getXAct();
					}
					else if(neighborCarIsDownCoil == true)
					{
						log.Info()<<"�ڳ�="<<neightborCraneNO<<"  ���������...���Ի�ȡ��̬ǽX..."<<endl;
						wallType=WALL_SINGLE_STEP::WALL_STATIC;
						wallX=neightborCranePLCStatusBase.getXAct();
					}					
					else
					{
						log.Info()<<"�ڳ�="<<neightborCraneNO<<" Ŀǰ״̬����..."<<endl;
						retCanMove=false;
						return retCanMove;
					}

					//**************************************************************************************************************************************************************
					//*
					//*															3.����ǽ���ͣ���ȡ��ͬ�Ķ�������̬ǽ�о�̬ǽ�Ŀ�����������̬ǽ�ж�̬ǽ�Ŀ����취
					//*
					//***************************************************************************************************************************************************************
					//����Ǿ�̬��ǽ�ڣ���ô����ȥ
					if(wallType==WALL_SINGLE_STEP::WALL_STATIC)
					{
						retCanMove=CLOSE_TO_STATIC_WALL::closeToWall( craneNO,  movingDirection , currentX, wallX, canReachX);
						return retCanMove;
					}

					//����Ƕ�̬ǽ�ڣ��������ϸ�ĶԶ�̬ǽ�ڵ�����
					if(wallType==WALL_SINGLE_STEP::WALL_DYNAMIC)
					{
						retCanMove=CLOSE_TO_DYNAMIC_WALL::closeToWall(craneNO  ,  movingDirection,  targetX  ,  cranePLCStatusBase  ,  neightborCranePLCStatusBase,   canReachX);
						return retCanMove;
					}
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




//�����ǰ���Զ����߼�����ж�
//�������ƣ��ڳ�ǿ��   ��Ҫ���ڳ�����������
bool JUDGE_BEFORE_MOVING ::judge_Facing_Auto_Car_High_Level(string craneNO , long currentX , long targetX , string movingDirection , CranePLCStatusBase  cranePLCStatusBase,
																															string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase ,
																															long& canReachX)
{
	string functionName = "JUDGE_BEFORE_MOVING :: judge_Facing_Auto_Car_Hgihg_Level()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�ٶ��ǲ��ܶ����� ������ȥ�ĵط�����ԭ��
	bool retCanMove=false;
	canReachX=currentX;

	try
	{		
						//��ô������ص�ǽ��
						long wallX;
						long wallType;

						//2018.12.22 zhangyuhong add
						//�ϲ����´��� ����

						/*
						//�Է������˶�
						bool neighborCarIsMoving=false;
						//�Է��������
						bool neighborCarIsLiftCoil=false;
						//�Է��������
						bool neighborCarIsDownCoil=false;
						//�Է�����ֻ��С��
						bool neighborCarIsOnlyYMoving=false;

						//**************************************************************************************************************************************************************
						//*
						//*															1.��ȡ�ڳ�״̬��ֹͣ��������ֻС���ƶ�
						//*
						//***************************************************************************************************************************************************************
						log.Debug()<<"1.�ж��г�״̬................."<<endl;
						if( isACraneStopped(neightborCranePLCStatusBase) == true)
						{
							CraneOrderCurrentBase neighborCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(neightborCraneNO);
							//������
							if (isACraneLiftCoilDown(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true || 
								isACraneLiftCoilUp(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true)
							{
								neighborCarIsLiftCoil = true;
							}
							//������
							else if (isACraneDownCoilDown(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true || 
								isACraneDownCoilUp(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true)
							{
								neighborCarIsDownCoil = true;
							}
							else if (isACraneOnlyYMoving(neightborCranePLCStatusBase) == true)
							{
								neighborCarIsOnlyYMoving = true;
							}
						}
						//�������ֹͣ�ģ���ô�����˶���
						else
						{
							neighborCarIsMoving=true;
						}

						//��������ڶԷ�����������˶�״̬����ô�Է���һ����Σ�յ��Զ���ֹ�������ҳ�ѡ�񲻶��������ջ���һ���ȶ���Ϊ���ù�ͨ
						if(neighborCarIsMoving==false )
						{
							if(neighborCarIsLiftCoil==true || neighborCarIsDownCoil==true || neighborCarIsOnlyYMoving == true)
							{
							}
							else
							{
								log.Debug()<<"�ڳ�="<<neightborCraneNO<<" ��ǰ״̬���󳵾�ֹ�������Ҳ������Ҳ�������״̬����������false��"<<endl;
								retCanMove=false;	
								return retCanMove;
							}
						}

						*/

						//**************************************************************************************************************************************************************
						//*
						//*															2.�����ڳ�ָ�����ͽ�����Ӧ����
						//*
						//***************************************************************************************************************************************************************
						//����ָ��
						if( neightborCranePLCStatusBase.getOrderID() == CraneEvadeRequestBase::ORDER_NO_EVADE )
						{
							log.Debug()<<"�ڳ�="<<neightborCraneNO<<"ָ������ = ����.......׼����ȡ����="<<craneNO<<" �ĵ���ǽ WALL_SINGLE_STEP........"<<endl;
							WALL_SINGLE_STEP::getWall(craneNO, movingDirection, neightborCranePLCStatusBase, wallX, wallType);
							retCanMove=CLOSE_TO_DYNAMIC_WALL::closeToWall(craneNO  ,  movingDirection,  targetX  ,  cranePLCStatusBase  ,  neightborCranePLCStatusBase,   canReachX);
							return retCanMove;
						}

						//����ָ��
						if( neightborCranePLCStatusBase.getOrderID() == CraneEvadeRequestBase::ORDER_NO_BOARDING )
						{
							log.Debug()<<"�ڳ�="<<neightborCraneNO<<"ָ������ = ����.......׼����ȡ����="<<craneNO<<" �ĵ���ǽ WALL_SINGLE_STEP........"<<endl;
							WALL_SINGLE_STEP::getWall(craneNO, movingDirection, neightborCranePLCStatusBase, wallX, wallType);
							retCanMove=CLOSE_TO_DYNAMIC_WALL::closeToWall(craneNO  ,  movingDirection,  targetX  ,  cranePLCStatusBase  ,  neightborCranePLCStatusBase,   canReachX);
							return retCanMove;
						}

						//2019.3.6 zhangyuhong add
						//����ǵ��Ի������Զ��л������� ָ���=999999���������г����ٻ��淢�������Զ��л���ָ���=101 ���г����Ǿ�ֹ������
						//���Զ��л�ָ��
						if (neightborCranePLCStatusBase.getOrderID() == CraneEvadeRequestBase::ORDER_NO_MANU_AUTO_SWITCH || 
							neightborCranePLCStatusBase.getOrderID() == CraneEvadeRequestBase::ORDER_NO_MANU_AUTO_SWITCH_TEST)
						{
							log.Debug()<<"�ڳ�="<<neightborCraneNO<<"�ոս��й����Զ��л�101��999999��ǽ����Ϊ��̬ǽ........�߿�����̬ǽ�߼�..."<<endl;
							//wallType=WALL_SINGLE_STEP::WALL_STATIC;
							wallX=neightborCranePLCStatusBase.getXAct();
							retCanMove=CLOSE_TO_STATIC_WALL::closeToWall( craneNO,  movingDirection , currentX, wallX, canReachX);
							return retCanMove;
						}

						//�Է��г����˶��в��ҶԷ��г���ִ��WMSָ��
						//2019.3.6 zhangyuhong add
						//�޸��ж��Ƿ���WMSָ��ŵ��߼���5λ �Ҳ�Ϊ 999999��ָ��� ��Ϊ��WMSָ��
						//if(neightborCranePLCStatusBase.getOrderID()!=CraneEvadeRequestBase::ORDER_NO_EVADE)
						//WMSָ��
						if(neightborCranePLCStatusBase.getOrderID() > 9999 && neightborCranePLCStatusBase.getOrderID() != CraneEvadeRequestBase::ORDER_NO_MANU_AUTO_SWITCH_TEST)
						{
							log.Debug()<<"�ڳ�="<<neightborCraneNO<<"����ִ��WMSָ��.......׼����ȡ����="<<craneNO<<" ����ָ��ǽ WALL_WHOLE_ORDER........"<<endl;
							if(WALL_WHOLE_ORDER::getWall(craneNO, movingDirection, neightborCranePLCStatusBase, wallX, wallType)==false)
							{
								log.Debug()<<"WALL_WHOLE_ORDER::getWall  �޷���ȡ���ڳ���WMSָ��......���̷���false��"<<endl;
								retCanMove=false;
								return retCanMove;
							}

							if(wallType==WALL_SINGLE_STEP::WALL_STATIC   )
							{
								log.Debug()<<"--------------------ǽ����Ϊ WALL_STATIC--------------------ִ�п�����̬ǽ�߼�-----------------------------"<<endl;
								retCanMove=CLOSE_TO_STATIC_WALL::closeToWall( craneNO,  movingDirection ,currentX, wallX, canReachX);
								return retCanMove;

							}
							else if(wallType==WALL_SINGLE_STEP::WALL_DYNAMIC)
							{
								log.Debug()<<"--------------------ǽ����Ϊ WALL_DYNAMIC--------------------ִ�п�����̬ǽ�߼�-----------------------------"<<endl;
								retCanMove=CLOSE_TO_DYNAMIC_WALL::closeToWall(craneNO  ,  movingDirection,  targetX  ,  cranePLCStatusBase  ,  neightborCranePLCStatusBase,   canReachX);
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






 //�����ǰ���ֶ������ж�
bool JUDGE_BEFORE_MOVING ::judge_Facing_Manu_Car(string craneNO , long currentX , long targetX , string movingDirection , CranePLCStatusBase  cranePLCStatusBase,
																							 string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase ,
																							 long& canReachX)
{


	string functionName = "JUDGE_BEFORE_MOVING :: judge_Facing_Manu_Car()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�ٶ��ǲ��ܶ����� 
	bool retCanMove=false;
	canReachX=currentX;

	try
	{
		
		//ǰ���������ֶ���
		//ǰ���������ֶ���  �����ֶ� ң�� �ȴ���һ��״̬
		if(neightborCranePLCStatusBase.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
					log.Debug()<<"�����г��Ŀ���״̬Ϊ ���Զ�״̬........"<<endl;

					log.Debug()<<"���Ŀ�������Ƿ�ɾ���CONDITION_TARGET_AREA_IS_CLEAN::judge()"<<endl;

					bool ret_Target_Area_Is_Clean=CONDITION_TARGET_AREA_IS_CLEAN::judge(craneNO, movingDirection, currentX, targetX, neightborCranePLCStatusBase);

					log.Debug()<<"�������ret_Target_Area_Is_Clean="<<ret_Target_Area_Is_Clean<<endl;

					//ǰ�����ֶ��������������
					//��ô�Թ̶�������ǰǰ��
					if(ret_Target_Area_Is_Clean==true)
					{
						log.Debug()<<"�ҷ��г�Ŀ�������� �ɾ��ģ�canReachXֵ����targetXֵ���г����ƶ���־retCanMove=true�����̷���true��"<<endl;
						canReachX=targetX;
						log.Debug()<<"canReachX="<<canReachX<<endl;
						retCanMove=true;
						return retCanMove;
					}
					//ǰ�����ֶ����������򲻿յ����
					//��ôѡ�񲻶�
					if(ret_Target_Area_Is_Clean==false)
					{
						log.Debug()<<"�ҷ��г�Ŀ�������� ���ɾ��ģ�canReachXֵ����currentXֵ���г����ƶ���־retCanMove=false�����̷���false��"<<endl;
						log.Debug()<<"canReachX="<<canReachX<<endl;
						retCanMove=false;
						return retCanMove;
					}
		}
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







bool JUDGE_BEFORE_MOVING ::isACraneStopped(CranePLCStatusBase  cranePLCStatusBase)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneStopped()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�ٶ��ǲ��Ǿ�ֹ�� 
	bool isStopped=false;
	try
	{
		log.Debug()<<"getHasCoil="<<cranePLCStatusBase.getHasCoil()<<endl;
		log.Debug()<<"getXDirectNegative="<<cranePLCStatusBase.getXDirectNegative()<<endl;
		log.Debug()<<"getXDirectPositive="<<cranePLCStatusBase.getXDirectPositive()<<endl;
		log.Debug()<<"getPlanUpX="<<cranePLCStatusBase.getPlanUpX()<<endl;
		log.Debug()<<"getPlanDownX="<<cranePLCStatusBase.getPlanDownX()<<endl;

		if(cranePLCStatusBase.getXDirectNegative() == 0 && cranePLCStatusBase.getXDirectPositive() == 0 )
		{
			if(cranePLCStatusBase.getHasCoil()==0)
			{
				if(cranePLCStatusBase.getPlanUpX() == CranePLCOrderBase::PLC_INT_NULL)
				{					
					isStopped=true;
				}
				if(abs(cranePLCStatusBase.getPlanUpX() - cranePLCStatusBase.getXAct()) <= X_OFFSET_MAX)
				{
					isStopped=true;
				}
			}
			if(cranePLCStatusBase.getHasCoil()==1)
			{
				if(cranePLCStatusBase.getPlanDownX() == CranePLCOrderBase::PLC_INT_NULL)
				{
					isStopped=true;
				}
				if(abs(cranePLCStatusBase.getPlanDownX() - cranePLCStatusBase.getXAct()) <= X_OFFSET_MAX)
				{
					isStopped=true;
				}
			}
		}
		return isStopped;	
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
	return isStopped;
}


bool JUDGE_BEFORE_MOVING ::craneIsMoving(CranePLCStatusBase  cranePLCStatusBase)
{
	string functionName = "JUDGE_BEFORE_MOVING :: craneMoving()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�ٶ��ǲ��Ǿ�ֹ�� 
	bool isMoving=false;
	try
	{
		if(cranePLCStatusBase.getXDirectNegative() != 0 || cranePLCStatusBase.getXDirectPositive() !=0 )
		{
			isMoving = true;
		}
		return isMoving;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return isMoving;
}

bool JUDGE_BEFORE_MOVING::craneLiftCoilUpDown(CranePLCStatusBase  cranePLCStatusBase)
{
	string functionName = "JUDGE_BEFORE_MOVING :: craneLiftCoilUpDown()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�ٶ��ǲ��Ǿ�ֹ�� 
	bool isLiftCoilUpDown=false;
	try
	{
		if(cranePLCStatusBase.getZDirectNegative() != 0 || cranePLCStatusBase.getZDirectPositive() !=0 )
		{
			isLiftCoilUpDown = true;
		}
		return isLiftCoilUpDown;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return isLiftCoilUpDown;
}





double JUDGE_BEFORE_MOVING ::get_Crane_Order_Priority(string  craneNO)
{
	string functionName = "JUDGE_BEFORE_MOVING :: get_Crane_Order_Priority()";
	LOG log(functionName, AUTO_CATCH_PID);
	double priority = 0;
	try
	{
		//1.����б���ָ������ָ�����ȼ���Ϊָ�����ȼ�
		//2.���û����ָ���WMSָ�����ȼ���Ϊָ�����ȼ�
		CraneEvadeRequestBase craneEvadeOrder;
		Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO, craneEvadeOrder);	
		 OrderCurrentBase craneOrderCurrent;
		craneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);
		if (craneEvadeOrder.getStatus() != CraneEvadeRequestBase::STATUS_EMPTY)
		{
			priority = craneEvadeOrder.getPriority();
		}
		else if (craneOrderCurrent.getCmdStatus() != CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			priority = craneOrderCurrent.getOrderPriority();
		}
		else
		{
			priority = 0; 
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
	return priority;
}

//�չ�����½���COIL_UP_PROCESS�����ء���ǯ��������
bool JUDGE_BEFORE_MOVING ::isACraneLiftCoilDown(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneLiftCoilDown()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�ٶ��ǲ��ǵ�ǰ���״̬ 
	bool isJustStatus=false;
	try
	{
		//COIL_UP_PROCESS�����ء���ǯ��������
		if (craneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && 
			 cranePLCStatusBase.getHasCoil() == 0 && 
			 cranePLCStatusBase.getZDirectNegative() == 1 && 
			 cranePLCStatusBase.getZDirectPositive() == 0)
		{
			isJustStatus = true;
		}
		
		return isJustStatus;	
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
	return isJustStatus;
}

//�ع����������COIL_UP_PROCESS�����ء���ǯ��������
bool JUDGE_BEFORE_MOVING ::isACraneLiftCoilUp(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneLiftCoilUp()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�ٶ��ǲ��ǵ�ǰ���״̬ 
	bool isJustStatus=false;
	try
	{
		//COIL_UP_PROCESS�����ء���ǯ��������
		if (craneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && 
			cranePLCStatusBase.getHasCoil() == 1 && 
			cranePLCStatusBase.getZDirectNegative() == 0 && 
			cranePLCStatusBase.getZDirectPositive() == 1)
		{
			isJustStatus = true;
		}

		return isJustStatus;	
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
	return isJustStatus;
}

//�ع�����½���COIL_DOWN_PROCESS�����ء���ǯ��������
bool JUDGE_BEFORE_MOVING ::isACraneDownCoilDown(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneDownCoilDown()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�ٶ��ǲ��ǵ�ǰ���״̬ 
	bool isJustStatus=false;
	try
	{
		//COIL_DOWN_PROCESS�����ء���ǯ��������
		if (craneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS && 
			cranePLCStatusBase.getHasCoil() == 1 && 
			cranePLCStatusBase.getZDirectNegative() == 1 && 
			cranePLCStatusBase.getZDirectPositive() == 0)
		{
			isJustStatus = true;
		}

		return isJustStatus;	
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
	return isJustStatus;
}

//�չ����������COIL_DOWN_PROCESS�����ء���ǯ��������
bool JUDGE_BEFORE_MOVING ::isACraneDownCoilUp(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneDownCoilUp()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�ٶ��ǲ��ǵ�ǰ���״̬ 
	bool isJustStatus=false;
	try
	{
		//COIL_DOWN_PROCESS�����ء���ǯ��������
		if (craneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS && 
			cranePLCStatusBase.getHasCoil() == 0 && 
			cranePLCStatusBase.getZDirectNegative() == 0 && 
			cranePLCStatusBase.getZDirectPositive() == 1)
		{
			isJustStatus = true;
		}

		return isJustStatus;	
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
	return isJustStatus;
}


//�󳵵�λ��С���ڶ�
bool JUDGE_BEFORE_MOVING ::isACraneOnlyYMoving(CranePLCStatusBase  cranePLCStatusBase)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneOnlyYMoving()";
	LOG log(functionName, AUTO_CATCH_PID);
	//�ٶ��ǲ��ǵ�ǰ���״̬ 
	bool isJustStatus=false;

	bool YIsMoving = false;//����Yû�ж�
	bool XIsMoving = true;//����X�ڶ�
	try
	{
		//Y��2���������ź�
		if ( (cranePLCStatusBase.getYDirectNegative() == 0 &&  cranePLCStatusBase.getYDirectPositive() == 1) || 
			  (cranePLCStatusBase.getYDirectNegative() == 1 && cranePLCStatusBase.getYDirectPositive() == 0) )
		{
			YIsMoving = true;
		}

		//X��2������û�ź�
		if ( (cranePLCStatusBase.getXDirectNegative() == 0 &&  cranePLCStatusBase.getXDirectPositive() == 0) )
		{
			XIsMoving = false;
		}

		if (YIsMoving == true && XIsMoving == false)
		{
			isJustStatus = true;
		}

		return isJustStatus;	
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
	return isJustStatus;
}



 //���㣺��ʹ�Է��Ǹ߼������ȼ���Է��ǵͼ��������Ƿ����ȵ�Ŀ��λ���ܵ��� �ӶԷ�Ϊ�ͼ��������ܵ�����ȡ������
bool JUDGE_BEFORE_MOVING ::if_Facing_Auto_Car_Low_Level(string craneNO , long currentX , long targetX , string movingDirection , CranePLCStatusBase  cranePLCStatusBase,
																												 string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase ,
																												 long& canReachX)
{


	string functionName = "JUDGE_BEFORE_MOVING :: if_Facing_Auto_Car_Low_Level()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool canChangeLowToHigh = false;
	bool retCanMove=false;
	canReachX=currentX;

	try
	{
		retCanMove = JUDGE_BEFORE_MOVING::judge_Facing_Auto_Car_Low_Level(craneNO, currentX, targetX, movingDirection, cranePLCStatusBase, 
																																					neightborCraneNO, neightborCranePLCStatusBase, 
																																					canReachX);
		//20171117   -----------------------targetX--------------------canReachX----->
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			if(targetX<canReachX)
			{
				canReachX=targetX;
			}
		}
		//20171117   <------------------canReachX-------------------------targetX-----
		if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			if(targetX>canReachX)
			{
				canReachX=targetX;
			}
		}
		//���豾���߼����Գ��ͼ�ʱ������������Կ���XĿ��λ����ı䱾���ӵͼ���߼�
		if (retCanMove == true && abs(canReachX - targetX) <= X_REACH_MAX)
		{
			canChangeLowToHigh = true;
			return canChangeLowToHigh;
		}
		return canChangeLowToHigh;
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
	return canChangeLowToHigh;
}