#pragma once 

#include "CraneEvadeLimitDefine.h"


using namespace Monitor;


//4_4 ������X������ã������˿չ� �ع� ����X�������
const bool CraneEvadeLimitDefine::CRANE_4_4_CAN_EVADE_TO_X_INC=true;
const bool CraneEvadeLimitDefine::CRANE_4_4_CAN_EVADE_TO_X_DES=false;

const long CraneEvadeLimitDefine::CRANE_4_4_X_MAX_HAS_COIL=420000;	//4-4�����ü�������
const long CraneEvadeLimitDefine::CRANE_4_4_X_MAX_NO_COIL=420000;		//4-4�����ü�������


//4_5 ����˫�����
const bool CraneEvadeLimitDefine::CRANE_4_5_CAN_EVADE_TO_X_INC=true;
const bool CraneEvadeLimitDefine::CRANE_4_5_CAN_EVADE_TO_X_DES=true;

const long CraneEvadeLimitDefine::CRANE_4_5_X_MAX_HAS_COIL=398000;    //4-5�����ü������꣺4-4�����ü������� - 22��
const long CraneEvadeLimitDefine::CRANE_4_5_X_MAX_NO_COIL=398000;	  //4-5�����ü������꣺4-4�����ü������� - 22��

const long CraneEvadeLimitDefine::CRANE_4_5_X_MIN_HAS_COIL=52000;     //4-5��С���ü������꣺4-6��С���ü������� + 22��
const long CraneEvadeLimitDefine::CRANE_4_5_X_MIN_NO_COIL=52000;      //4-5��С���ü������꣺4-6��С���ü������� + 22��

//4-6 ����˫�����
const bool CraneEvadeLimitDefine::CRANE_4_6_CAN_EVADE_TO_X_INC=true;
const bool CraneEvadeLimitDefine::CRANE_4_6_CAN_EVADE_TO_X_DES=true;

const long CraneEvadeLimitDefine::CRANE_4_6_X_MAX_HAS_COIL=376000;    //4-6�����ü������꣺4-5�����ü������� - 22��
const long CraneEvadeLimitDefine::CRANE_4_6_X_MAX_NO_COIL=376000;	  //4-6�����ü������꣺4-5�����ü������� - 22��

const long CraneEvadeLimitDefine::CRANE_4_6_X_MIN_HAS_COIL=25500;     //4-6��С���ü������꣺4-7��С���ü������� + 22��
const long CraneEvadeLimitDefine::CRANE_4_6_X_MIN_NO_COIL=25500;      //4-6��С���ü������꣺4-7��С���ü������� + 22��

//4-7 ֻ����С�������
const bool CraneEvadeLimitDefine::CRANE_4_7_CAN_EVADE_TO_X_INC=false;
const bool CraneEvadeLimitDefine::CRANE_4_7_CAN_EVADE_TO_X_DES=true;

const long CraneEvadeLimitDefine::CRANE_4_7_X_MIN_HAS_COIL=3500;     //4-7��С���ü�������
const long CraneEvadeLimitDefine::CRANE_4_7_X_MIN_NO_COIL=3500;      //4-7��С���ü�������

CraneEvadeLimitDefine:: CraneEvadeLimitDefine()
{

}

CraneEvadeLimitDefine:: ~CraneEvadeLimitDefine()
{

}




bool CraneEvadeLimitDefine ::isDirectionOK(string craneNO, string direction)
{


	string functionName = "CraneEvadeLimitDefine :: isDirectionOK()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�������������趨
	bool ret=false;

	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<endl;

		//4_7ֻ����XС�������
		if(craneNO=="4_7")
		{
			if(direction==MOVING_DIR::DIR_X_DES)
			{
				log.Debug()<<"����="<<craneNO<<" ���÷���Ϸ��Լ��ͨ��......"<<endl;
				ret=true;
				return ret;
			}
		}

		//4_6����˫�����
		if(craneNO=="4_6")
		{
			if(direction==MOVING_DIR::DIR_X_INC)
			{
				log.Debug()<<"����="<<craneNO<<" ���÷���Ϸ��Լ��ͨ��......"<<endl;
				ret=true;
				return ret;
			}
			if(direction==MOVING_DIR::DIR_X_DES)
			{
				log.Debug()<<"����="<<craneNO<<" ���÷���Ϸ��Լ��ͨ��......"<<endl;
				ret=true;
				return ret;
			}
		}
		//4_5����˫�����
		if(craneNO=="4_5")
		{
			if(direction==MOVING_DIR::DIR_X_INC)
			{
				log.Debug()<<"����="<<craneNO<<" ���÷���Ϸ��Լ��ͨ��......"<<endl;
				ret=true;
				return ret;
			}
			if(direction==MOVING_DIR::DIR_X_DES)
			{
				log.Debug()<<"����="<<craneNO<<" ���÷���Ϸ��Լ��ͨ��......"<<endl;
				ret=true;
				return ret;
			}
		}
		//4_4ֻ����������
		if(craneNO=="4_4")
		{
			if(direction==MOVING_DIR::DIR_X_INC)
			{
				log.Debug()<<"����="<<craneNO<<" ���÷���Ϸ��Լ��ͨ��......"<<endl;
				ret=true;
				return ret;
			}
		}
		
		if(ret == false)
		{
			log.Debug()<<"����="<<craneNO<<"���÷���="<<direction<<" ���÷���Ϸ��Լ��δ��ͨ����......"<<endl;
		}

		log.Debug()<<"final ret="<<ret<<endl;
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





bool CraneEvadeLimitDefine ::calEvadeXAct(string craneNO, string direction, long hasCoil , long evadeXRequest, long& evadeX)
{


	string functionName = "CraneEvadeLimitDefine :: isEvadeXRequestOK()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�������������趨
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;

	try
	{

		log.Debug()<<"����="<<craneNO<<"   ����="<<direction<<"    ��Ҫ����õ�X����="<<evadeXRequest<<endl;

		//4-4��ֻ��X�������
		if(craneNO=="4_4")
		{
			ret=calEvadeXAct_4_4(craneNO, direction, hasCoil , evadeXRequest, evadeX);
		}		

		//4-5������X˫�����
		if(craneNO=="4_5")
		{
			ret=calEvadeXAct_4_5(craneNO, direction, hasCoil , evadeXRequest, evadeX);
		}

		//4-6������˫�����
		if(craneNO=="4_6")
		{
			ret=calEvadeXAct_4_6(craneNO, direction, hasCoil , evadeXRequest, evadeX);
		}

		//4-7��ֻ����С�������
		if(craneNO=="4_7")
		{
			ret=calEvadeXAct_4_7(craneNO, direction, hasCoil , evadeXRequest, evadeX);
		}

		log.Debug()<<"final ret="<<ret<<endl;
		log.Debug()<<"���ռ���ó�ʵ�ʿ��Ա��� evadeX="<<evadeX<<endl;
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


bool CraneEvadeLimitDefine ::calEvadeXAct_4_5(string craneNO, string direction, long hasCoil , long evadeXRequest, long& evadeX)
{


	string functionName = "CraneEvadeLimitDefine :: calEvadeXAct_4_5()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�������������趨
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;
	log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<"    evadeXRequest="<<evadeXRequest<<endl;
	try
	{

		//4_5����˫�����   X�����  XҪС�ڵ��������  ���X��������� ��ôX���������
		//										 X��С����  XҪ���ڵ�����С����  ���XС����С���� ��ôX������С����
		if(craneNO=="4_5")
		{
							if(direction==MOVING_DIR::DIR_X_INC)
							{
											if(hasCoil==0)
											{
														if(evadeXRequest<=CRANE_4_5_X_MAX_NO_COIL)
														{
																		evadeX=evadeXRequest;
																		ret=true;
																		return ret;
														}
														else
														{
																		evadeX=CRANE_4_5_X_MAX_NO_COIL;
																		ret=true;
																		return ret;
														}
											}
											else if(hasCoil==1)
											{
														if(evadeXRequest<=CRANE_4_5_X_MAX_HAS_COIL)
														{
																		evadeX=evadeXRequest;
																		ret=true;
																		return ret;
														}
														else
														{
																		evadeX=CRANE_4_5_X_MAX_HAS_COIL;
																		ret=true;
																		return ret;
														}
											}
							}
							if(direction==MOVING_DIR::DIR_X_DES)
							{
												if(hasCoil==0)
												{
																	if(evadeXRequest>=CRANE_4_5_X_MIN_NO_COIL)
																	{
																					evadeX=evadeXRequest;
																					ret=true;
																					return ret;
																	}
																	else
																	{
																					evadeX=CRANE_4_5_X_MIN_NO_COIL;
																					ret=true;
																					return ret;
																	}
												}
												else if(hasCoil==1)
												{
																	if(evadeXRequest>=CRANE_4_5_X_MIN_HAS_COIL)
																	{
																					evadeX=evadeXRequest;
																					ret=true;
																					return ret;
																	}
																	else
																	{
																					evadeX=CRANE_4_5_X_MIN_HAS_COIL;
																					ret=true;
																					return ret;
																	}
												}		
							}
		}

	

		log.Debug()<<"final ret="<<ret<<endl;
		log.Debug()<<"final evadeX="<<evadeX<<endl;
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




bool CraneEvadeLimitDefine ::calEvadeXAct_4_6(string craneNO, string direction, long hasCoil , long evadeXRequest, long& evadeX)
{
	string functionName = "CraneEvadeLimitDefine :: calEvadeXAct_4_6()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�������������趨
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;
	log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<"    evadeXRequest="<<evadeXRequest<<endl;
	try
	{
		//4-6˫�����
		if(craneNO=="4_6")
		{
							if(direction==MOVING_DIR::DIR_X_INC)
							{
											if(hasCoil==0)
											{
																if(evadeXRequest<=CRANE_4_6_X_MAX_NO_COIL)
																{
																				evadeX=evadeXRequest;
																				ret=true;
																				return ret;
																}
																else
																{
																				evadeX=CRANE_4_6_X_MAX_NO_COIL;
																				ret=true;
																				return ret;
																}
											}
											else if(hasCoil==1)
											{
																if(evadeXRequest<=CRANE_4_6_X_MAX_HAS_COIL)
																{
																				evadeX=evadeXRequest;
																				ret=true;
																				return ret;
																}
																else
																{
																				evadeX=CRANE_4_6_X_MAX_HAS_COIL;
																				ret=true;
																				return ret;
																}
											}
							}
							if(direction==MOVING_DIR::DIR_X_DES)
							{
												if(hasCoil==0)
												{
																	if(evadeXRequest>=CRANE_4_6_X_MIN_NO_COIL)
																	{
																					evadeX=evadeXRequest;
																					ret=true;
																					return ret;
																	}
																	else
																	{
																					evadeX=CRANE_4_6_X_MIN_NO_COIL;
																					ret=true;
																					return ret;
																	}
												}
												else if(hasCoil==1)
												{
																	if(evadeXRequest>=CRANE_4_6_X_MIN_HAS_COIL)
																	{
																					evadeX=evadeXRequest;
																					ret=true;
																					return ret;
																	}
																	else
																	{
																					evadeX=CRANE_4_6_X_MIN_HAS_COIL;
																					ret=true;
																					return ret;
																	}
												}		
							}
		}	

		log.Debug()<<"final ret="<<ret<<endl;
		log.Debug()<<"final evadeX="<<evadeX<<endl;
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




bool CraneEvadeLimitDefine ::calEvadeXAct_4_4(string craneNO, string direction, long hasCoil , long evadeXRequest, long& evadeX)
{


	string functionName = "CraneEvadeLimitDefine :: calEvadeXAct_4_4()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�������������趨
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;
	log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<"    evadeXRequest="<<evadeXRequest<<endl;
	try
	{


		//4_4ֻ����������   X�����  XҪС�ڵ��������  ���X��������� ��ôX���������
		if(craneNO=="4_4")
		{
							if(direction==MOVING_DIR::DIR_X_INC)
							{
												if(hasCoil==0)
												{
																	if(evadeXRequest<=CRANE_4_4_X_MAX_NO_COIL)
																	{
																					evadeX=evadeXRequest;
																					ret=true;
																					return ret;
																	}
																	else
																	{
																					evadeX=CRANE_4_4_X_MAX_NO_COIL;
																					ret=true;
																					return ret;
																	}
												}
												else if(hasCoil==1)
												{
																	if(evadeXRequest<=CRANE_4_4_X_MAX_HAS_COIL)
																	{
																					evadeX=evadeXRequest;
																					ret=true;
																					return ret;
																	}
																	else
																	{
																					evadeX=CRANE_4_4_X_MAX_HAS_COIL;
																					ret=true;
																					return ret;
																	}
												}				
							}
		}

	

		log.Debug()<<"final ret="<<ret<<endl;
		log.Debug()<<"final evadeX="<<evadeX<<endl;
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




bool CraneEvadeLimitDefine ::calEvadeXAct_4_7(string craneNO, string direction, long hasCoil , long evadeXRequest, long& evadeX)
{


	string functionName = "CraneEvadeLimitDefine :: calEvadeXAct_4_7()";
	LOG log(functionName, AUTO_CATCH_PID);

	//�������������趨
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;
	log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<"    evadeXRequest="<<evadeXRequest<<endl;
	try
	{



		//4-7��ֻ����С�������
		if(craneNO=="4_7")
		{
							if(direction==MOVING_DIR::DIR_X_DES)
							{
												if(hasCoil==0)
												{
																	if(evadeXRequest>=CRANE_4_7_X_MIN_NO_COIL)
																	{
																					evadeX=evadeXRequest;
																					ret=true;
																					return ret;
																	}
																	else
																	{
																					evadeX=CRANE_4_7_X_MIN_NO_COIL;
																					ret=true;
																					return ret;
																	}
												}
												else if(hasCoil==1)
												{
																	if(evadeXRequest>=CRANE_4_7_X_MIN_HAS_COIL)
																	{
																					evadeX=evadeXRequest;
																					ret=true;
																					return ret;
																	}
																	else
																	{
																					evadeX=CRANE_4_7_X_MIN_HAS_COIL;
																					ret=true;
																					return ret;
																	}
												}				
							}
		}
	

		log.Debug()<<"final ret="<<ret<<endl;
		log.Debug()<<"final evadeX="<<evadeX<<endl;
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
