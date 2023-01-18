#pragma once 

#include "CraneEvadeLimitDefine.h"


using namespace Monitor;


//4_4 可以向X大方向避让，设置了空钩 重钩 避让X的最大极限
const bool CraneEvadeLimitDefine::CRANE_4_4_CAN_EVADE_TO_X_INC=true;
const bool CraneEvadeLimitDefine::CRANE_4_4_CAN_EVADE_TO_X_DES=false;

const long CraneEvadeLimitDefine::CRANE_4_4_X_MAX_HAS_COIL=420000;	//4-4最大避让极限坐标
const long CraneEvadeLimitDefine::CRANE_4_4_X_MAX_NO_COIL=420000;		//4-4最大避让极限坐标


//4_5 可以双向避让
const bool CraneEvadeLimitDefine::CRANE_4_5_CAN_EVADE_TO_X_INC=true;
const bool CraneEvadeLimitDefine::CRANE_4_5_CAN_EVADE_TO_X_DES=true;

const long CraneEvadeLimitDefine::CRANE_4_5_X_MAX_HAS_COIL=398000;    //4-5最大避让极限坐标：4-4最大避让极限坐标 - 22米
const long CraneEvadeLimitDefine::CRANE_4_5_X_MAX_NO_COIL=398000;	  //4-5最大避让极限坐标：4-4最大避让极限坐标 - 22米

const long CraneEvadeLimitDefine::CRANE_4_5_X_MIN_HAS_COIL=52000;     //4-5最小避让极限坐标：4-6最小避让极限坐标 + 22米
const long CraneEvadeLimitDefine::CRANE_4_5_X_MIN_NO_COIL=52000;      //4-5最小避让极限坐标：4-6最小避让极限坐标 + 22米

//4-6 可以双向避让
const bool CraneEvadeLimitDefine::CRANE_4_6_CAN_EVADE_TO_X_INC=true;
const bool CraneEvadeLimitDefine::CRANE_4_6_CAN_EVADE_TO_X_DES=true;

const long CraneEvadeLimitDefine::CRANE_4_6_X_MAX_HAS_COIL=376000;    //4-6最大避让极限坐标：4-5最大避让极限坐标 - 22米
const long CraneEvadeLimitDefine::CRANE_4_6_X_MAX_NO_COIL=376000;	  //4-6最大避让极限坐标：4-5最大避让极限坐标 - 22米

const long CraneEvadeLimitDefine::CRANE_4_6_X_MIN_HAS_COIL=25500;     //4-6最小避让极限坐标：4-7最小避让极限坐标 + 22米
const long CraneEvadeLimitDefine::CRANE_4_6_X_MIN_NO_COIL=25500;      //4-6最小避让极限坐标：4-7最小避让极限坐标 + 22米

//4-7 只能向小方向避让
const bool CraneEvadeLimitDefine::CRANE_4_7_CAN_EVADE_TO_X_INC=false;
const bool CraneEvadeLimitDefine::CRANE_4_7_CAN_EVADE_TO_X_DES=true;

const long CraneEvadeLimitDefine::CRANE_4_7_X_MIN_HAS_COIL=3500;     //4-7最小避让极限坐标
const long CraneEvadeLimitDefine::CRANE_4_7_X_MIN_NO_COIL=3500;      //4-7最小避让极限坐标

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

	//按照最差情况下设定
	bool ret=false;

	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<endl;

		//4_7只能向X小方向避让
		if(craneNO=="4_7")
		{
			if(direction==MOVING_DIR::DIR_X_DES)
			{
				log.Debug()<<"本车="<<craneNO<<" 避让方向合法性检查通过......"<<endl;
				ret=true;
				return ret;
			}
		}

		//4_6可以双向避让
		if(craneNO=="4_6")
		{
			if(direction==MOVING_DIR::DIR_X_INC)
			{
				log.Debug()<<"本车="<<craneNO<<" 避让方向合法性检查通过......"<<endl;
				ret=true;
				return ret;
			}
			if(direction==MOVING_DIR::DIR_X_DES)
			{
				log.Debug()<<"本车="<<craneNO<<" 避让方向合法性检查通过......"<<endl;
				ret=true;
				return ret;
			}
		}
		//4_5可以双向避让
		if(craneNO=="4_5")
		{
			if(direction==MOVING_DIR::DIR_X_INC)
			{
				log.Debug()<<"本车="<<craneNO<<" 避让方向合法性检查通过......"<<endl;
				ret=true;
				return ret;
			}
			if(direction==MOVING_DIR::DIR_X_DES)
			{
				log.Debug()<<"本车="<<craneNO<<" 避让方向合法性检查通过......"<<endl;
				ret=true;
				return ret;
			}
		}
		//4_4只能向大方向避让
		if(craneNO=="4_4")
		{
			if(direction==MOVING_DIR::DIR_X_INC)
			{
				log.Debug()<<"本车="<<craneNO<<" 避让方向合法性检查通过......"<<endl;
				ret=true;
				return ret;
			}
		}
		
		if(ret == false)
		{
			log.Debug()<<"本车="<<craneNO<<"避让方向="<<direction<<" 避让方向合法性检查未能通过！......"<<endl;
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

	//按照最差情况下设定
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;

	try
	{

		log.Debug()<<"本车="<<craneNO<<"   方向="<<direction<<"    被要求避让的X距离="<<evadeXRequest<<endl;

		//4-4：只向X大方向避让
		if(craneNO=="4_4")
		{
			ret=calEvadeXAct_4_4(craneNO, direction, hasCoil , evadeXRequest, evadeX);
		}		

		//4-5：可以X双向避让
		if(craneNO=="4_5")
		{
			ret=calEvadeXAct_4_5(craneNO, direction, hasCoil , evadeXRequest, evadeX);
		}

		//4-6：可以双向避让
		if(craneNO=="4_6")
		{
			ret=calEvadeXAct_4_6(craneNO, direction, hasCoil , evadeXRequest, evadeX);
		}

		//4-7：只能向小方向避让
		if(craneNO=="4_7")
		{
			ret=calEvadeXAct_4_7(craneNO, direction, hasCoil , evadeXRequest, evadeX);
		}

		log.Debug()<<"final ret="<<ret<<endl;
		log.Debug()<<"最终计算得出实际可以避让 evadeX="<<evadeX<<endl;
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

	//按照最差情况下设定
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;
	log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<"    evadeXRequest="<<evadeXRequest<<endl;
	try
	{

		//4_5可以双向避让   X向大方向  X要小于等于最大极限  如果X大于最大极限 那么X等于最大极限
		//										 X向小方向  X要大于等于最小极限  如果X小于最小极限 那么X等于最小极限
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

	//按照最差情况下设定
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;
	log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<"    evadeXRequest="<<evadeXRequest<<endl;
	try
	{
		//4-6双向避让
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

	//按照最差情况下设定
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;
	log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<"    evadeXRequest="<<evadeXRequest<<endl;
	try
	{


		//4_4只能向大方向避让   X向大方向  X要小于等于最大极限  如果X大于最大极限 那么X等于最大极限
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

	//按照最差情况下设定
	bool ret=false;
	evadeX=CranePLCOrderBase::PLC_INT_NULL;
	log.Debug()<<"craneNO="<<craneNO<<"   direction="<<direction<<"    evadeXRequest="<<evadeXRequest<<endl;
	try
	{



		//4-7：只能向小方向避让
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
