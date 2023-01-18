#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"

using namespace Monitor;



Adapter_UACS_CRANE_ORDER_CURRENT::Adapter_UACS_CRANE_ORDER_CURRENT(void)
{
}



Adapter_UACS_CRANE_ORDER_CURRENT::~Adapter_UACS_CRANE_ORDER_CURRENT(void)
{



}


//1 初始化状态表中的所有信息，在执行完成指令或者取消指令时候使用
bool Adapter_UACS_CRANE_ORDER_CURRENT:: initialise(string craneNO  )
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: initialise()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		string strSql="";
		strSql="UPDATE  UACS_CRANE_ORDER_CURRENT SET ";
		strSql+=" ORDER_NO=null, ";
		strSql+=" BAY_NO=null, ";
		strSql+=" MAT_CODE=null, ";
		strSql+=" COMP_CODE=null, ";
		strSql+=" MAT_TYPE=null, ";
		strSql+=" MAT_REQ_WGT=null, ";
		strSql+=" MAT_ACT_WGT=null, ";
		strSql+=" MAT_CUR_WGT=null, ";
		strSql+=" ORDER_TYPE=null, ";
		strSql+=" ORDER_PRIORITY=null, ";
		strSql+=" FROM_STOCK_NO=null, ";
		strSql+=" TO_STOCK_NO=null, ";
		strSql+=" CMD_STATUS=null, ";
		strSql+=" CMD_SEQ=null, ";
		strSql+=" CAR_SCAN_NO=null, ";
		strSql+=" MAT_UP_SCAN_NO=null, ";
		strSql+=" PLAN_UP_X=null, ";
		strSql+=" PLAN_UP_Y=null, ";
		strSql+=" PLAN_UP_Z=null, ";
		strSql+=" UP_ROTATE_ANGLE_SET=null, ";
		strSql+=" MAT_DOWN_SCAN_NO=null, ";
		strSql+=" PLAN_DOWN_X=null, ";
		strSql+=" PLAN_DOWN_Y=null, ";
		strSql+=" PLAN_DOWN_Z=null, ";
		strSql+=" DOWN_ROTATE_ANGLESET=null  ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CRANE_NO") =craneNO;					

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"........... success CRANE_NO="<<craneNO<<endl;


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



//2 向状态表里面写UACS指令信息，在接收推来的指令或者自己找到新的指令时使用
bool Adapter_UACS_CRANE_ORDER_CURRENT::  update_UACS_Crane_Order_Info( string	craneNO,  
																	  long		orderNO,
																	  string	bayNO,  
																	  string	matNO, 
																	  long		orderType, 
																	  long		orderPriority, 
																	  string    fromStockNO,
																	  string	toStockNO,
																	  string    cmdStatus
																	  )
{

	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: update_UACS_Crane_Order_Info()";

	bool ret=false;
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"\t orderNO="<<orderNO<<"\t bayNO="<<bayNO<<"\t matNO="<<matNO<<"\t orderType"<<orderType<<"\t orderPriority="<<orderPriority<<"\t fromStockNO="<<fromStockNO<<"\t toStockNO="<<toStockNO<<"\t cmdStatus="<<cmdStatus<<endl;
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+=" ORDER_NO=:p_ORDER_NO , ";
		strSql+=" BAY_NO=:p_BAY_NO , ";
		strSql+=" MAT_NO=:p_MAT_NO , ";
		strSql+=" ORDER_TYPE=:p_ORDER_TYPE , ";
		strSql+=" ORDER_PRIORITY=:p_ORDER_PRIORITY , ";
		strSql+=" FROM_STOCK_NO=:p_FROM_STOCK_NO , ";
		strSql+=" TO_STOCK_NO=:p_TO_STOCK_NO , ";
		strSql+=" CMD_STATUS=:p_CMD_STATUS ";

		strSql+="  WHERE  CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_NO") =orderNO;
		cmd.Param("p_BAY_NO") =bayNO;
		cmd.Param("p_MAT_NO") =matNO;
		cmd.Param("p_ORDER_TYPE") =orderType;
		cmd.Param("p_ORDER_PRIORITY") =orderPriority;
		cmd.Param("p_FROM_STOCK_NO") =fromStockNO;
		cmd.Param("p_TO_STOCK_NO") =toStockNO;
		cmd.Param("p_CMD_STATUS") =cmdStatus;
		cmd.Param("p_CRANE_NO") =craneNO;


		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<".................successed"<<endl;


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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		ret=false;

		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;

}





//3 更新钢卷尺寸信息
bool Adapter_UACS_CRANE_ORDER_CURRENT:: update_CoilSize_Info(		string craneNO,
															 long coilWidth,
															 long coilWeight,
															 long coilOutDia,
															 long coilInDia
															 )
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: update_CoilSize_Info()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		log.Debug()<<"craneNO<<"<<craneNO<<"\t coilWidth="<<coilWidth<<"\t coilWeight="<<coilWeight<<"\t coilOutDia"<<coilOutDia<<endl;
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+=" COIL_WIDTH=:p_COIL_WIDTH, ";
		strSql+=" COIL_WEIGHT=:p_COIL_WEIGHT, ";
		strSql+=" COIL_OUT_DIA=:p_COIL_OUT_DIA,";
		strSql+=" COIL_IN_DIA=:p_COIL_IN_DIA";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_COIL_WIDTH") =coilWidth;					
		cmd.Param("p_COIL_WEIGHT") =coilWeight;					
		cmd.Param("p_COIL_OUT_DIA") =coilOutDia;			
		cmd.Param("p_COIL_IN_DIA") =coilInDia;	
		cmd.Param("p_CRANE_NO") =craneNO;					

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"................. successed CRANE_NO="<<craneNO<<endl;


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

// 更新指令类型和落关参数
bool Adapter_UACS_CRANE_ORDER_CURRENT:: update_Order_Type_Down_Info(
																										string		craneNO, 
																										string		orderType, 
																										string		toStockNO,
																										long		planDownX,
																										long		planDownY,
																										long		planDownZ,
																										long		downRotateAngleSet,
																										long      floorUpZ,
																										long      flagSmallCoil,
																										long      floorDownZ)
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: update_Order_Type_Down_Info()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"\t planDownX="<<planDownX<<"\t planDownZ="<<planDownZ<<"\t downRotateAngleSet="<<downRotateAngleSet<<endl;
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+=" ORDER_TYPE=:p_ORDER_TYPE, ";
		strSql+=" TO_STOCK_NO=:p_TO_STOCK_NO, ";
		strSql+=" PLAN_DOWN_X=:p_PLAN_DOWN_X, ";
		strSql+=" PLAN_DOWN_Y=:p_PLAN_DOWN_Y, ";
		strSql+=" PLAN_DOWN_Z=:p_PLAN_DOWN_Z, ";
		strSql+=" DOWN_ROTATE_ANGLESET=:p_DOWN_ROTATE_ANGLESET, ";
		strSql+=" FLOOR_UP_Z=:p_FLOOR_UP_Z, ";
		strSql+=" FLAG_SMALL_COIL=:p_FLAG_SMALL_COIL, ";
		strSql+=" FLOOR_DOWN_Z=:p_FLOOR_DOWN_Z  ";

		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_TYPE") = orderType;
		cmd.Param("p_TO_STOCK_NO") = toStockNO;
		cmd.Param("p_PLAN_DOWN_X") =planDownX;				
		cmd.Param("p_PLAN_DOWN_Y") =planDownY;			
		cmd.Param("p_PLAN_DOWN_Z") =planDownZ;			
		cmd.Param("p_DOWN_ROTATE_ANGLESET") =downRotateAngleSet;			
		cmd.Param("p_FLOOR_UP_Z") =floorUpZ;
		cmd.Param("p_FLAG_SMALL_COIL") =flagSmallCoil;
		cmd.Param("p_FLOOR_DOWN_Z") =floorDownZ;

		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......update_Order_Type_Down_Info成功更新指令下半关 CRANE_NO="<<craneNO<<endl;


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







//4 更新起吊参数
bool Adapter_UACS_CRANE_ORDER_CURRENT::update_Up_Info(string	craneNO,
													  string    fromStockNO,
													  long		planUpX,
													  long		planUpY,
													  long		planUpZ,
													  long		upRotateAngleSet,
													  long		clampWidthSet,
													  long      coilWidth,
													  long      coilOutDia,
													  long      coilInDia,
													  long      floorUpZ,
													  long      flagSmallCoil,
													  long      floorDownZ)
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: update_Up_Info()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+=" FROM_STOCK_NO=:p_FROM_STOCK_NO, ";
		strSql+=" PLAN_UP_X=:p_PLAN_UP_X, ";
		strSql+=" PLAN_UP_Y=:p_PLAN_UP_Y, ";
		strSql+=" PLAN_UP_Z=:p_PLAN_UP_Z, ";
		strSql+=" UP_ROTATE_ANGLE_SET=:p_UP_ROTATE_ANGLE_SET, ";
		strSql+=" CLAMP_WIDTH_SET=:p_CLAMP_WIDTH_SET, ";
		strSql+=" COIL_WIDTH=:p_COIL_WIDTH, ";
		strSql+=" COIL_OUT_DIA=:p_COIL_OUT_DIA, ";
		strSql+=" COIL_IN_DIA=:p_COIL_IN_DIA, ";
		strSql+=" FLOOR_UP_Z=:p_FLOOR_UP_Z, ";
		strSql+=" FLAG_SMALL_COIL=:p_FLAG_SMALL_COIL, ";
		strSql+=" FLOOR_DOWN_Z=:p_FLOOR_DOWN_Z  ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_FROM_STOCK_NO") =fromStockNO;	
		cmd.Param("p_PLAN_UP_X") =planUpX;		
		cmd.Param("p_PLAN_UP_Y") =planUpY;		
		cmd.Param("p_PLAN_UP_Z") =planUpZ;		
		cmd.Param("p_UP_ROTATE_ANGLE_SET") =upRotateAngleSet;		
		cmd.Param("p_CLAMP_WIDTH_SET") =clampWidthSet;	
		cmd.Param("p_COIL_WIDTH") =coilWidth;		
		cmd.Param("p_COIL_OUT_DIA") =coilOutDia;	
		cmd.Param("p_COIL_IN_DIA") =coilInDia;
		cmd.Param("p_FLOOR_UP_Z") =floorUpZ;
		cmd.Param("p_FLAG_SMALL_COIL") =flagSmallCoil;
		cmd.Param("p_FLOOR_DOWN_Z") =floorDownZ;

		cmd.Param("p_CRANE_NO") =craneNO;					

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<".................successed CRANE_NO="<<craneNO<<endl;


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



//4.1 更新起吊参数2
bool Adapter_UACS_CRANE_ORDER_CURRENT::update_Up_Info_2( string		craneNO,
																													  string    fromStockNO,
																													  long		planUpX,
																													  long		planUpY,
																													  long		planUpZ)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: update_Up_Info_2()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+=" FROM_STOCK_NO=:p_FROM_STOCK_NO, ";
		strSql+=" PLAN_UP_X=:p_PLAN_UP_X, ";
		strSql+=" PLAN_UP_Y=:p_PLAN_UP_Y, ";
		strSql+=" PLAN_UP_Z=:p_PLAN_UP_Z  ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_FROM_STOCK_NO") =fromStockNO;	
		cmd.Param("p_PLAN_UP_X") =planUpX;		
		cmd.Param("p_PLAN_UP_Y") =planUpY;		
		cmd.Param("p_PLAN_UP_Z") =planUpZ;		

		cmd.Param("p_CRANE_NO") =craneNO;					

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<".................successed CRANE_NO="<<craneNO<<endl;


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





//5 更新落关参数
bool Adapter_UACS_CRANE_ORDER_CURRENT:: update_Down_Info(string	craneNO,
														 string		toStockNO,
														 long		planDownX,
														 long		planDownY,
														 long		planDownZ,
														 long		downRotateAngleSet,
														 long      floorUpZ,
														 long      flagSmallCoil,
														 long      floorDownZ)
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: update_Down_Info()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"\t planDownX="<<planDownX<<"\t planDownZ="<<planDownZ<<"\t downRotateAngleSet="<<downRotateAngleSet<<endl;
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+= "TO_STOCK_NO=:p_TO_STOCK_NO, ";
		strSql+=" PLAN_DOWN_X=:p_PLAN_DOWN_X, ";
		strSql+=" PLAN_DOWN_Y=:p_PLAN_DOWN_Y, ";
		strSql+=" PLAN_DOWN_Z=:p_PLAN_DOWN_Z, ";
		strSql+=" DOWN_ROTATE_ANGLESET=:p_DOWN_ROTATE_ANGLESET, ";
		strSql+=" FLOOR_UP_Z=:p_FLOOR_UP_Z, ";
		strSql+=" FLAG_SMALL_COIL=:p_FLAG_SMALL_COIL, ";
		strSql+=" FLOOR_DOWN_Z=:p_FLOOR_DOWN_Z  ";

		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_TO_STOCK_NO") = toStockNO;
		cmd.Param("p_PLAN_DOWN_X") =planDownX;				
		cmd.Param("p_PLAN_DOWN_Y") =planDownY;			
		cmd.Param("p_PLAN_DOWN_Z") =planDownZ;			
		cmd.Param("p_DOWN_ROTATE_ANGLESET") =downRotateAngleSet;			
		cmd.Param("p_FLOOR_UP_Z") =floorUpZ;
		cmd.Param("p_FLAG_SMALL_COIL") =flagSmallCoil;
		cmd.Param("p_FLOOR_DOWN_Z") =floorDownZ;

		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......update_Down_Info成功更新指令下半关 CRANE_NO="<<craneNO<<endl;


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




//6 更新指令状态
bool Adapter_UACS_CRANE_ORDER_CURRENT:: update_CMDStatus(string craneNO, string cmdStatus)
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: update_CMDStatus()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"\t cmdStatus="<<cmdStatus<<endl;
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+=" CMD_STATUS=:p_CMD_STATUS ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CMD_STATUS") =cmdStatus;					
		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<".................successed CRANE_NO="<<craneNO<<endl;


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

//
bool Adapter_UACS_CRANE_ORDER_CURRENT:: InitPlanUpXYZMatUpScanNO(string craneNO)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: InitPlanUpXYZMatUpScanNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="UPDATE   UACS_CRANE_ORDER_CURRENT SET  ";
		strSql+=" PLAN_UP_X = :p_PLAN_UP_X,  ";
		strSql+=" PLAN_UP_Y = :p_PLAN_UP_Y,  ";
		strSql+=" PLAN_UP_Z = :p_PLAN_UP_Z,  ";
		strSql+=" MAT_UP_SCAN_NO = NULL  ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_UP_X") =DB_INT_NULL;
		cmd.Param("p_PLAN_UP_Y") =DB_INT_NULL;
		cmd.Param("p_PLAN_UP_Z") =DB_INT_NULL;
		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret=true;
		log.Debug()<<__FUNCTION__<<".................successed CRANE_NO="<<craneNO<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: InitPlanDownXYZMatDownScanNO(string craneNO)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: InitPlanDownXYZMatDownScanNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="UPDATE   UACS_CRANE_ORDER_CURRENT SET  ";
		strSql+=" PLAN_DOWN_X = :p_PLAN_DOWN_X,  ";
		strSql+=" PLAN_DOWN_Y = :p_PLAN_DOWN_Y,  ";
		strSql+=" PLAN_DOWN_Z = :p_PLAN_DOWN_Z,  ";
		strSql+=" MAT_DOWN_SCAN_NO = NULL  ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_DOWN_X") =DB_INT_NULL;
		cmd.Param("p_PLAN_DOWN_Y") =DB_INT_NULL;
		cmd.Param("p_PLAN_DOWN_Z") =DB_INT_NULL;
		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret=true;
		log.Debug()<<__FUNCTION__<<".................successed CRANE_NO="<<craneNO<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: Update_CmdSeq_Add_1(string craneNO)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: Update_CmdSeq_Add_1()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="UPDATE   UACS_CRANE_ORDER_CURRENT SET  ";
		strSql+=" CMD_SEQ = CMD_SEQ + 1 ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CRANE_NO") =craneNO;	
		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret=true;
		log.Debug()<<__FUNCTION__<<".................successed Update_CmdSeq_Add_1="<<endl;

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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdMatCurWgt(string craneNO, long matCurWgt)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdMatCurWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="UPDATE   UACS_CRANE_ORDER_CURRENT SET  ";
		strSql+=" MAT_CUR_WGT = :p_MAT_CUR_WGT ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_MAT_CUR_WGT") =matCurWgt;
		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret=true;
		log.Debug()<<__FUNCTION__<<".................successed UpdMatCurWgt"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdMatActWgt(string craneNO, long matCurWgt)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdMatActWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="UPDATE   UACS_CRANE_ORDER_CURRENT SET  ";
		strSql+=" MAT_ACT_WGT = MAT_ACT_WGT + :p_MAT_CUR_WGT ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_MAT_CUR_WGT") =matCurWgt;
		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret=true;
		log.Debug()<<__FUNCTION__<<".................successed UpdMatActWgt"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: Init_ScanDownInfo(	string craneNO)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: Init_ScanDownInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="UPDATE   UACS_CRANE_ORDER_CURRENT SET  ";
		strSql+=" PLAN_DOWN_X = :p_PLAN_DOWN_X,  ";
		strSql+=" PLAN_DOWN_X = :p_PLAN_DOWN_Y,  ";
		strSql+=" PLAN_DOWN_X = :p_PLAN_DOWN_Z,  ";
		strSql+=" SCAN_DOWN_SND_FLAG = :p_SCAN_DOWN_SND_FLAG,  ";
		strSql+=" SCAN_DOWN_RCV_FLAG = :p_SCAN_DOWN_RCV_FLAG  ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		long scanDownSndFlag = 0;
		long scanDownRcvFlag = 2;

		cmd.Param("p_PLAN_DOWN_X") =DB_INT_NULL;
		cmd.Param("p_PLAN_DOWN_Y") =DB_INT_NULL;
		cmd.Param("p_PLAN_DOWN_Z") =DB_INT_NULL;
		cmd.Param("p_SCAN_DOWN_SND_FLAG") =scanDownSndFlag;
		cmd.Param("p_SCAN_DOWN_RCV_FLAG") =scanDownRcvFlag;
		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret=true;
		log.Debug()<<__FUNCTION__<<".................successed CRANE_NO="<<craneNO<<endl;


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




//7 更新材料号，在手动作业时使用，针对遥控模式和司机模式
bool Adapter_UACS_CRANE_ORDER_CURRENT:: update_MatNO_WhenManu(string craneNO,
															  string matNO)
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: update_MatNO_WhenManu()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"\t matNO="<<matNO<<endl;
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+=" MAT_NO=:p_MAT_NO ";
		strSql+=" WHERE CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_MAT_NO") =matNO;					
		cmd.Param("p_CRANE_NO") =craneNO;			

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"................. successed CRANE_NO="<<craneNO<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT::receive_A_NewCraneOrder(long orderNO, 
																																	   string bayNO, 
																																	   string matCode, 
																																	   string compCode, 
																																	   string matType, 
																																	   long matReqWgt, 
																																	   long matActWgt, 
																																	   long matCurWgt, 
																																	   string orderType, 
																																	   long orderPriority, 
																																	   string fromStockNO, 
																																	   string toStockNO, 
																																	   string cmdStatus, 
																																	   long cmdSeq, 
																																	   string craneNO, 
																																	   string carScanNO, 
																																	   string matUpScanNO, 
																																	   long planUpX, 
																																	   long planUpY, 
																																	   long planUpZ, 
																																	   long upRotateAngle, 
																																	   string matDownScanNO, 
																																	   long planDownX, 
																																	   long planDownY, 
																																	   long planDownZ, 
																																	   long downRotateAngle
																																	   )
{

	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: receive_A_NewCraneOrder()";

	bool ret=false;
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql=" UPDATE  UACS_CRANE_ORDER_CURRENT SET ";
		strSql+=" ORDER_NO=:p_ORDER_NO , ";
		strSql+=" BAY_NO=:p_BAY_NO , ";

		strSql+=" MAT_CODE=:p_MAT_CODE , ";		
		strSql+=" COMP_CODE=:p_COMP_CODE , ";
		strSql+=" MAT_TYPE=:p_MAT_TYPE , ";

		strSql+=" MAT_REQ_WGT=:p_MAT_REQ_WGT , ";
		strSql+=" MAT_ACT_WGT=:p_MAT_ACT_WGT , ";
		strSql+=" MAT_CUR_WGT=:p_MAT_CUR_WGT , ";
		
		strSql+=" ORDER_TYPE=:p_ORDER_TYPE , ";
		strSql+=" ORDER_PRIORITY=:p_ORDER_PRIORITY , ";

		strSql+=" FROM_STOCK_NO=:p_FROM_STOCK_NO , ";
		strSql+=" TO_STOCK_NO=:p_TO_STOCK_NO , ";

		strSql+=" CMD_STATUS=:p_CMD_STATUS, ";
		strSql+=" CMD_SEQ=:p_CMD_SEQ, ";

		strSql+=" CAR_SCAN_NO=:p_CAR_SCAN_NO, ";

		strSql+=" MAT_UP_SCAN_NO=:p_MAT_UP_SCAN_NO, ";
		strSql+=" PLAN_UP_X=:p_PLAN_UP_X, ";
		strSql+=" PLAN_UP_Y=:p_PLAN_UP_Y, ";
		strSql+=" PLAN_UP_Z=:p_PLAN_UP_Z, ";
		strSql+=" UP_ROTATE_ANGLE=:p_UP_ROTATE_ANGLE, ";			

		strSql+=" MAT_UP_SCAN_NO=:p_MAT_UP_SCAN_NO, ";
		strSql+=" PLAN_DOWN_X=:p_PLAN_DOWN_X, ";
		strSql+=" PLAN_DOWN_Y=:p_PLAN_DOWN_Y, ";
		strSql+=" PLAN_DOWN_Z=:p_PLAN_DOWN_Z, ";
		strSql+=" DOWN_ROTATE_ANGLE=:p_DOWN_ROTATE_ANGLE  ";

		strSql+="  WHERE  CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_NO") =orderNO;
		cmd.Param("p_BAY_NO") =bayNO;

		cmd.Param("p_MAT_CODE") =matCode;
		cmd.Param("p_COMP_CODE") =compCode;
		cmd.Param("p_MAT_TYPE") =matType;

		cmd.Param("p_MAT_REQ_WGT") =matReqWgt;
		cmd.Param("p_MAT_ACT_WGT") =matActWgt;
		cmd.Param("p_MAT_CUR_WGT") =matCurWgt;

		cmd.Param("p_ORDER_TYPE") =orderType;
		cmd.Param("p_ORDER_PRIORITY") =orderPriority;

		cmd.Param("p_FROM_STOCK_NO") =fromStockNO;
		cmd.Param("p_TO_STOCK_NO") =toStockNO;

		cmd.Param("p_CMD_STATUS") =cmdStatus;
		cmd.Param("p_CMD_SEQ") =cmdSeq;

		cmd.Param("p_CAR_SCAN_NO") =carScanNO;

		cmd.Param("p_MAT_UP_SCAN_NO") =matUpScanNO;
		cmd.Param("p_PLAN_UP_X") =planUpX;		
		cmd.Param("p_PLAN_UP_Y") =planUpY;		
		cmd.Param("p_PLAN_UP_Z") =planUpZ;		
		cmd.Param("p_UP_ROTATE_ANGLE") =upRotateAngle;			

		cmd.Param("p_MAT_DOWN_SCAN_NO") =matDownScanNO;
		cmd.Param("p_PLAN_DOWN_X") =planDownX;				
		cmd.Param("p_PLAN_DOWN_Y") =planDownY;			
		cmd.Param("p_PLAN_DOWN_Z") =planDownZ;			
		cmd.Param("p_DOWN_ROTATE_ANGLE") =downRotateAngle;

		cmd.Param("p_CRANE_NO") =craneNO;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<".................successed"<<endl;

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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		ret=false;

		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;

}



OrderCurrentBase Adapter_UACS_CRANE_ORDER_CURRENT :: getData(string craneNO)
{

	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: getData()";
	LOG log(functionName, AUTO_CATCH_PID);

	OrderCurrentBase orderCurrentBase;

	try
	{
		string strSql="SELECT * FROM UACS_CRANE_ORDER_CURRENT WHERE CRANE_NO = :p_CRANE_NO ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CRANE_NO")=craneNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{	
			//1 ORDER_NO
			if(!cmd.Field("ORDER_NO").IsNull())
			{
				orderCurrentBase.setOrderNO(cmd.Field("ORDER_NO").AsLong());
			}
			//2 BAY_NO
			if(!cmd.Field("BAY_NO").IsNull())
			{
				orderCurrentBase.setBayNO( cmd.Field("BAY_NO").AsString()  );
			}
			//3  MAT_CODE
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				orderCurrentBase.setMatCode( cmd.Field("MAT_CODE").AsString()  );
			}
			//4  COMP_CODE
			if(!cmd.Field("COMP_CODE").IsNull())
			{
				orderCurrentBase.setCompCode( cmd.Field("COMP_CODE").AsString()  );
			}
			//5  MAT_TYPE
			if(!cmd.Field("MAT_TYPE").IsNull())
			{
				orderCurrentBase.setMatType( cmd.Field("MAT_TYPE").AsString()  );
			}
			//6  MAT_REQ_WGT
			if(!cmd.Field("MAT_REQ_WGT").IsNull())
			{
				orderCurrentBase.setMatReqWgt( cmd.Field("MAT_REQ_WGT").AsLong()  );
			}
			//7  MAT_ACT_WGT
			if(!cmd.Field("MAT_ACT_WGT").IsNull())
			{
				orderCurrentBase.setMatActWgt( cmd.Field("MAT_ACT_WGT").AsLong()  );
			}
			//8  MAT_CUR_WGT
			if(!cmd.Field("MAT_CUR_WGT").IsNull())
			{
				orderCurrentBase.setMatCurWgt( cmd.Field("MAT_CUR_WGT").AsLong()  );
			}
			//9  ORDER_TYPE
			if(!cmd.Field("ORDER_TYPE").IsNull())
			{
				orderCurrentBase.setOrderType( cmd.Field("ORDER_TYPE").AsString()  );
			}
			//10  ORDER_PRIORITY
			if(!cmd.Field("ORDER_PRIORITY").IsNull())
			{
				orderCurrentBase.setOrderPriority( cmd.Field("ORDER_PRIORITY").AsLong()  );
			}
			//11  FROM_STOCK_NO
			if(!cmd.Field("FROM_STOCK_NO").IsNull())
			{
				orderCurrentBase.setFromStockNO( cmd.Field("FROM_STOCK_NO").AsString()  );
			}
			//12  TO_STOCK_NO
			if(!cmd.Field("TO_STOCK_NO").IsNull())
			{
				orderCurrentBase.setToStockNO( cmd.Field("TO_STOCK_NO").AsString()  );
			}
			//13  CMD_STATUS
			if(!cmd.Field("CMD_STATUS").IsNull())
			{
				orderCurrentBase.setCmdStatus( cmd.Field("CMD_STATUS").AsString()  );
			}
			//14  CMD_SEQ
			if(!cmd.Field("CMD_SEQ").IsNull())
			{
				orderCurrentBase.setCmdSeq( cmd.Field("CMD_SEQ").AsLong()  );
			}
			//15  CRANE_NO
			if(!cmd.Field("CRANE_NO").IsNull())
			{
				orderCurrentBase.setCraneNO( cmd.Field("CRANE_NO").AsString()  );
			}
			//16  CAR_SCAN_NO
			if(!cmd.Field("CAR_SCAN_NO").IsNull())
			{
				orderCurrentBase.setCarScanNO( cmd.Field("CAR_SCAN_NO").AsString()  );
			}
			//17  MAT_UP_SCAN_NO
			if(!cmd.Field("MAT_UP_SCAN_NO").IsNull())
			{
				orderCurrentBase.setMatUpScanNO( cmd.Field("MAT_UP_SCAN_NO").AsString()  );
			}
			//18  PLAN_UP_X
			if(!cmd.Field("PLAN_UP_X").IsNull())
			{
				orderCurrentBase.setPlanUpX( cmd.Field("PLAN_UP_X").AsLong()  );
			}
			//19 PLAN_UP_Y
			if(!cmd.Field("PLAN_UP_Y").IsNull())
			{
				orderCurrentBase.setPlanUpY( cmd.Field("PLAN_UP_Y").AsLong()  );
			}
			//20 PLAN_UP_Z
			if(!cmd.Field("PLAN_UP_Z").IsNull())
			{
				orderCurrentBase.setPlanUpZ( cmd.Field("PLAN_UP_Z").AsLong()  );
			}
			//21 UP_ROTATE_ANGLE
			if(!cmd.Field("UP_ROTATE_ANGLE").IsNull())
			{
				orderCurrentBase.setUpRotateAngle( cmd.Field("UP_ROTATE_ANGLE").AsLong()  );
			}
			//22  MAT_DOWN_SCAN_NO
			if(!cmd.Field("MAT_DOWN_SCAN_NO").IsNull())
			{
				orderCurrentBase.setMatDownScanNO( cmd.Field("MAT_DOWN_SCAN_NO").AsString()  );
			}
			//23 PLAN_DOWN_X
			if(!cmd.Field("PLAN_DOWN_X").IsNull())
			{
				orderCurrentBase.setPlanDownX( cmd.Field("PLAN_DOWN_X").AsLong()  );
			}
			//24 PLAN_DOWN_Y
			if(!cmd.Field("PLAN_DOWN_Y").IsNull())
			{
				orderCurrentBase.setPlanDownY( cmd.Field("PLAN_DOWN_Y").AsLong()  );
			}
			//25 PLAN_DOWN_Z
			if(!cmd.Field("PLAN_DOWN_Z").IsNull())
			{
				orderCurrentBase.setPlanDownZ( cmd.Field("PLAN_DOWN_Z").AsLong()  );
			}
			//26 DOWN_ROTATE_ANGLE
			if(!cmd.Field("DOWN_ROTATE_ANGLE").IsNull())
			{
				orderCurrentBase.setDownRotateAngle( cmd.Field("DOWN_ROTATE_ANGLE").AsLong()  );
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return orderCurrentBase;

}


//1 初始化状态表中的所有信息，在执行完成指令或者取消指令时候使用
bool Adapter_UACS_CRANE_ORDER_CURRENT::receive_BoardingCraneOrder(string		craneNO,  
																																			  long		orderNO,
																																			  string	bayNO,  
																																			  string	matNO, 
																																			  string	orderType, 
																																			  long		orderPriority, 
																																			  string    fromStockNO,
																																			  string	toStockNO,
																																			  string    cmdStatus,
																																			  long		planUpX,
																																			  long		planUpY,
																																			  long		planUpZ,
																																			  long		upRotateAngleSet,
																																			  long		clampWidthSet,
																																			  long		planDownX,
																																			  long		planDownY,
																																			  long		planDownZ,
																																			  long		downRotateAngleSet,
																																			  long		coilWidth,
																																			  long		coilWeight,
																																			  long		coilOutDia,
																																			  long		coilInDia,
																																			  long      floorUpZ,
																																			  long      flagSmallCoil,
																																			  long      floorDownZ)
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: receive_BoardingCraneOrder()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		string strSql="";
		strSql="Update  UACS_CRANE_ORDER_CURRENT set ";
		strSql+=" ORDER_NO=:p_ORDER_NO , ";
		strSql+=" BAY_NO=:p_BAY_NO , ";
		strSql+=" MAT_NO=:p_MAT_NO , ";
		strSql+=" ORDER_TYPE=:p_ORDER_TYPE , ";
		strSql+=" ORDER_PRIORITY=:p_ORDER_PRIORITY , ";
		strSql+=" FROM_STOCK_NO=:p_FROM_STOCK_NO , ";
		strSql+=" TO_STOCK_NO=:p_TO_STOCK_NO , ";
		strSql+=" CMD_STATUS=:p_CMD_STATUS, ";

		strSql+=" PLAN_UP_X=:p_PLAN_UP_X, ";
		strSql+=" PLAN_UP_Y=:p_PLAN_UP_Y, ";
		strSql+=" PLAN_UP_Z=:p_PLAN_UP_Z, ";
		strSql+=" UP_ROTATE_ANGLE_SET=:p_UP_ROTATE_ANGLE_SET, ";
		strSql+=" CLAMP_WIDTH_SET=:p_CLAMP_WIDTH_SET, ";					

		strSql+=" PLAN_DOWN_X=:p_PLAN_DOWN_X, ";
		strSql+=" PLAN_DOWN_Y=:p_PLAN_DOWN_Y, ";
		strSql+=" PLAN_DOWN_Z=:p_PLAN_DOWN_Z, ";
		strSql+=" DOWN_ROTATE_ANGLESET=:p_DOWN_ROTATE_ANGLESET, ";

		strSql+=" COIL_WIDTH=:p_COIL_WIDTH, ";
		strSql+=" COIL_WEIGHT=:p_COIL_WEIGHT, ";
		strSql+=" COIL_OUT_DIA=:p_COIL_OUT_DIA,";
		strSql+=" COIL_IN_DIA=:p_COIL_IN_DIA, ";

		strSql+=" FLOOR_UP_Z=:p_FLOOR_UP_Z, ";
		strSql+=" FLAG_SMALL_COIL=:p_FLAG_SMALL_COIL, ";
		strSql+=" FLOOR_DOWN_Z=:p_FLOOR_DOWN_Z  ";

		strSql+="  WHERE  CRANE_NO=:p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_NO") =orderNO;
		cmd.Param("p_BAY_NO") =bayNO;
		cmd.Param("p_MAT_NO") =matNO;
		cmd.Param("p_ORDER_TYPE") =orderType;
		cmd.Param("p_ORDER_PRIORITY") =orderPriority;
		cmd.Param("p_FROM_STOCK_NO") =fromStockNO;
		cmd.Param("p_TO_STOCK_NO") =toStockNO;
		cmd.Param("p_CMD_STATUS") =cmdStatus;

		cmd.Param("p_PLAN_UP_X") =planUpX;		
		cmd.Param("p_PLAN_UP_Y") =planUpY;		
		cmd.Param("p_PLAN_UP_Z") =planUpZ;		
		cmd.Param("p_UP_ROTATE_ANGLE_SET") =upRotateAngleSet;		
		cmd.Param("p_CLAMP_WIDTH_SET") =clampWidthSet;	


		cmd.Param("p_PLAN_DOWN_X") =planDownX;				
		cmd.Param("p_PLAN_DOWN_Y") =planDownY;			
		cmd.Param("p_PLAN_DOWN_Z") =planDownZ;			
		cmd.Param("p_DOWN_ROTATE_ANGLESET") =downRotateAngleSet;			


		cmd.Param("p_COIL_WIDTH") =coilWidth;					
		cmd.Param("p_COIL_WEIGHT") =coilWeight;					
		cmd.Param("p_COIL_OUT_DIA") =coilOutDia;			
		cmd.Param("p_COIL_IN_DIA") =coilInDia;	

		cmd.Param("p_FLOOR_UP_Z") =floorUpZ;
		cmd.Param("p_FLAG_SMALL_COIL") =flagSmallCoil;
		cmd.Param("p_FLOOR_DOWN_Z") =floorDownZ;

		cmd.Param("p_CRANE_NO") =craneNO;


		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<".................successed"<<endl;

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


bool  Adapter_UACS_CRANE_ORDER_CURRENT::getStautsNot1Order( string craneNO)
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: getStautsNot1Order()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	long nCount = DB_INT_NULL;
	try
	{		
		string strSql="SELECT *  FROM UACS_ORDER_QUEUE WHERE CRANE_NO = :p_CRANE_NO ";
		strSql += " AND CMD_STATUS <> '0' ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CRANE_NO") = craneNO;
		cmd.Execute();
		if (cmd.FetchNext())
		{	
			ret = true;
			return ret;
		}
		ret = false;
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}

bool  Adapter_UACS_CRANE_ORDER_CURRENT::GetScanAreaXY(string areaType, string areaNO, long& startX, long& endX, long& startY, long& endY)
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: GetScanAreaXY()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	long nCount = DB_INT_NULL;
	try
	{
		string strSql="";
		//areaType = 1-卸料区  2-料格  3-停车位
		if (areaType == "1")//卸料区 
		{
			strSql = "SELECT * FROM UACS_DUMPING_INFO_DEFINE WHERE DUMPING_NO = :p_AREA_NO ";
		}
		else if (areaType == "2")//料格
		{
			strSql = "SELECT * FROM UACS_YARDMAP_GRID_DEFINE WHERE GRID_NO = :p_AREA_NO ";
		}
		else if (areaType == "3")//停车位 
		{
			strSql = "SELECT * FROM UACS_PARKING_INFO_DEFINE WHERE PARKING_NO = :p_AREA_NO ";
		}
		else
		{
			log.Info()<<"GetScanAreaXY ERROR: areaType is invalid, return false...................."<<endl;
			ret = false;
			return ret;
		}

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_AREA_NO") = areaNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{	
			if(!cmd.Field("X_START").IsNull())
			{
				startX = cmd.Field("X_START").AsLong();
			}
			if(!cmd.Field("X_END").IsNull())
			{
				endX = cmd.Field("X_END").AsLong();
			}
			if(!cmd.Field("Y_START").IsNull())
			{
				startY = cmd.Field("Y_START").AsLong();
			}
			if(!cmd.Field("Y_END").IsNull())
			{
				endY = cmd.Field("Y_END").AsLong();
			}
		}
		ret = true;
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}

bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdScanSndFlag(string craneNO, string flagName, long flagValue)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdScanSndFlag()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";

		if (flagName == "UP")
		{
			strSql = " UPDATE  UACS_CRANE_ORDER_CURRENT SET SCAN_UP_SND_FLAG = :p_FLAG_VALUE ";
			strSql += " WHERE  CRANE_NO = :p_CRANE_NO ";
		}
		else if (flagName == "DOWN")
		{
			strSql = " UPDATE  UACS_CRANE_ORDER_CURRENT SET SCAN_DOWN_SND_FLAG = :p_FLAG_VALUE ";
			strSql += " WHERE  CRANE_NO = :p_CRANE_NO ";
		}		

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_FLAG_VALUE") = flagValue;
		cmd.Param("p_CRANE_NO") =craneNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......UpdScanSndFlag success!"<<endl;


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

bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdUpSndRcvFlag(string craneNO, long upSndFlag, long upRcvFlag)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdUpSndRcvFlag()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " UPDATE UACS_CRANE_ORDER_CURRENT  SET ";
		strSql += " SCAN_UP_SND_FLAG = :p_SCAN_UP_SND_FLAG,  ";
		strSql += " SCAN_UP_RCV_FLAG = :p_SCAN_UP_RCV_FLAG  ";
		strSql += " WHERE  CRANE_NO = :p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_SCAN_UP_SND_FLAG") = upSndFlag;
		cmd.Param("p_SCAN_UP_RCV_FLAG") = upRcvFlag;
		cmd.Param("p_CRANE_NO") =craneNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......UpdUpSndRcvFlag success!"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: InsOrderOper(long orderNO, 
																												 string orderType, 
																												 string bayNO, 
																												 string matCode, 
																												 string compCode, 
																												 string matType, 
																												 long matReqWgt, 
																												 long matCurWgt, 
																												 long hasCoilWgt, 
																												 string fromStockNO, 
																												 string toStockNO, 
																												 string stockNO, 
																												 string cmdStatus, 
																												 long cmdSeq, 
																												 long planX, 
																												 long planY, 
																												 long planZ, 
																												 long actX, 
																												 long actY, 
																												 long actZ, 
																												 string craneMode )
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: InsOrderOper()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " INSERT  INTO  UACS_ORDER_OPER(  ";
		strSql += " ORDER_NO, ";
		strSql += " ORDER_TYPE, ";
		strSql += " BAY_NO, ";
		strSql += " MAT_CODE, ";
		strSql += " COMP_CODE, ";
		strSql += " MAT_TYPE, ";
		strSql += " MAT_REQ_WGT, ";
		strSql += " MAT_CUR_WGT, ";
		strSql += " HAS_COIL_WGT, ";
		strSql += " FROM_STOCK_NO, ";
		strSql += " TO_STOCK_NO, ";
		strSql += " STOCK_NO, ";
		strSql += " CMD_STATUS, ";
		strSql += " CMD_SEQ, ";
		strSql += " PLAN_X, ";
		strSql += " PLAN_Y, ";
		strSql += " PLAN_Z, ";
		strSql += " ACT_X, ";
		strSql += " ACT_Y, ";
		strSql += " ACT_Z, ";
		strSql += " CRANE_MODE, ";
		strSql += " REC_TIME ) ";

		strSql += " VALUES(  ";
		strSql += " :p_ORDER_NO, ";
		strSql += " :p_ORDER_TYPE, ";
		strSql += " :p_BAY_NO, ";
		strSql += " :p_MAT_CODE, ";
		strSql += " :p_COMP_CODE, ";
		strSql += " :p_MAT_TYPE, ";
		strSql += " :p_MAT_REQ_WGT, ";
		strSql += " :p_MAT_CUR_WGT, ";
		strSql += " :p_HAS_COIL_WGT, ";
		strSql += " :p_FROM_STOCK_NO, ";
		strSql += " :p_TO_STOCK_NO, ";
		strSql += " :p_STOCK_NO, ";
		strSql += " :p_CMD_STATUS, ";
		strSql += " :p_CMD_SEQ, ";
		strSql += " :p_PLAN_X, ";
		strSql += " :p_PLAN_Y, ";
		strSql += " :p_PLAN_Z, ";
		strSql += " :p_ACT_X, ";
		strSql += " :p_ACT_Y, ";
		strSql += " :p_ACT_Z, ";
		strSql += " :p_CRANE_MODE, ";
		strSql += " :p_REC_TIME ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Param("p_ORDER_TYPE") = orderType;
		cmd.Param("p_BAY_NO") =bayNO;
		cmd.Param("p_MAT_CODE") =matCode;		
		cmd.Param("p_COMP_CODE") =compCode;		
		cmd.Param("p_MAT_TYPE") =matType;		
		cmd.Param("p_MAT_REQ_WGT") =matReqWgt;		
		cmd.Param("p_MAT_CUR_WGT") =matCurWgt;
		cmd.Param("p_HAS_COIL_WGT") =hasCoilWgt;
		cmd.Param("p_FROM_STOCK_NO") =fromStockNO;		
		cmd.Param("p_TO_STOCK_NO") =toStockNO;		
		cmd.Param("p_STOCK_NO") =stockNO;		
		cmd.Param("p_CMD_STATUS") =cmdStatus;		
		cmd.Param("p_CMD_SEQ") =cmdSeq;		
		cmd.Param("p_PLAN_X") =planX;		
		cmd.Param("p_PLAN_Y") =planY;		
		cmd.Param("p_PLAN_Z") =planZ;		
		cmd.Param("p_ACT_X") =actX;		
		cmd.Param("p_ACT_Y") =actY;		
		cmd.Param("p_ACT_Z") =actZ;		
		cmd.Param("p_CRANE_MODE") =craneMode;		
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();		

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......InsOrderOper success!"<<endl;


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


bool  Adapter_UACS_CRANE_ORDER_CURRENT::SelSRSMatInfoScanResult(long orderNO, 
																																		string actionType, 
																																		string& scanResult)
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: SelSRSMatInfoScanResult()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		string strSql="SELECT * FROM UACS_PARKING_SRS_MAT_INFO WHERE ";
		strSql += " ORDER_NO = :p_ORDER_NO  AND ";
		strSql += " SCAN_TYPE = :p_SCAN_TYPE ";
		strSql += " ORDER BY  REC_TIME DESC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Param("p_SCAN_TYPE") = actionType;
		cmd.Execute();

		if (cmd.FetchNext())
		{	
			if(!cmd.Field("SCAN_RESULT").IsNull())
			{
				scanResult = cmd.Field("SCAN_RESULT").AsString();
			}
		}
		ret = true;
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}


bool  Adapter_UACS_CRANE_ORDER_CURRENT::SelSRSCarInfo(string scanNO, vector<long> vecCarPoint)
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: SelSRSCarInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		long pointValue = 0;

		string strSql="SELECT * FROM UACS_PARKING_SRS_CAR_INFO WHERE ";
		strSql += " SCAN_NO = :p_SCAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_SCAN_NO") = scanNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("POINT_X_1").IsNull())
			{
				pointValue = cmd.Field("POINT_X_1").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			if(!cmd.Field("POINT_Y_1").IsNull())
			{
				pointValue = cmd.Field("POINT_Y_1").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			if(!cmd.Field("POINT_Z_1").IsNull())
			{
				pointValue = cmd.Field("POINT_Z_1").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			//----------------------------------------------------------

			if(!cmd.Field("POINT_X_2").IsNull())
			{
				pointValue = cmd.Field("POINT_X_2").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			if(!cmd.Field("POINT_Y_2").IsNull())
			{
				pointValue = cmd.Field("POINT_Y_2").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			if(!cmd.Field("POINT_Z_2").IsNull())
			{
				pointValue = cmd.Field("POINT_Z_2").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			//----------------------------------------------------------

			if(!cmd.Field("POINT_X_3").IsNull())
			{
				pointValue = cmd.Field("POINT_X_3").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			if(!cmd.Field("POINT_Y_3").IsNull())
			{
				pointValue = cmd.Field("POINT_Y_3").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			if(!cmd.Field("POINT_Z_3").IsNull())
			{
				pointValue = cmd.Field("POINT_Z_3").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			//----------------------------------------------------------

			if(!cmd.Field("POINT_X_4").IsNull())
			{
				pointValue = cmd.Field("POINT_X_4").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			if(!cmd.Field("POINT_Y_4").IsNull())
			{
				pointValue = cmd.Field("POINT_Y_4").AsLong();
				vecCarPoint.push_back(pointValue);
			}
			if(!cmd.Field("POINT_Z_4").IsNull())
			{
				pointValue = cmd.Field("POINT_Z_4").AsLong();
				vecCarPoint.push_back(pointValue);
			}

			ret = true;
		}
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}


bool  Adapter_UACS_CRANE_ORDER_CURRENT::SelSRSCarInfoScanResult(long orderNO, string& scanResult)
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: SelSRSCarInfoScanResult()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		string strSql="SELECT * FROM UACS_PARKING_SRS_CAR_INFO WHERE ";
		strSql += " ORDER_NO = :p_ORDER_NO ";
		strSql += " ORDER BY  REC_TIME DESC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{	
			if(!cmd.Field("SCAN_RESULT").IsNull())
			{
				scanResult = cmd.Field("SCAN_RESULT").AsString();
			}
		}
		ret = true;
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}


bool  Adapter_UACS_CRANE_ORDER_CURRENT::SelParkingInfoDefine(string parkingNO, long& xStart, long& xEnd, long& yStart, long& yEnd)
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: SelParkingInfoDefine()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		string strSql="SELECT * FROM  UACS_PARKING_INFO_DEFINE  WHERE ";
		strSql += " PARKING_NO = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_PARKING_NO") = parkingNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{	
			if(!cmd.Field("X_START").IsNull())
			{
				xStart = cmd.Field("X_START").AsLong();
			}
			if(!cmd.Field("X_END").IsNull())
			{
				xEnd = cmd.Field("X_END").AsLong();
			}
			if(!cmd.Field("Y_START").IsNull())
			{
				yStart = cmd.Field("Y_START").AsLong();
			}
			if(!cmd.Field("Y_END").IsNull())
			{
				yEnd = cmd.Field("Y_END").AsLong();
			}
		}
		ret = true;
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}


bool  Adapter_UACS_CRANE_ORDER_CURRENT::SelCraneSrsIPConfig(string craneNO, string& srsIP)
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: SelCraneSrsIPConfig()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		string strSql="SELECT * FROM  UACS_CRANE_SRS_IP_CONFIG  WHERE ";
		strSql += " CRANE_NO = :p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_CRANE_NO") = craneNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{	
			if(!cmd.Field("SRS_IP").IsNull())
			{
				srsIP = cmd.Field("SRS_IP").AsString();
			}
		}
		ret = true;
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}


bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdOrderCurrentUpScanNOAndPoint(string craneNO, string matUpScanNO, long planUpX, long planUpY, long planUpZ)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdOrderCurrentUpScanNOAndPoint()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " UPDATE UACS_CRANE_ORDER_CURRENT  SET ";
		strSql += " MAT_UP_SCAN_NO = :p_MAT_UP_SCAN_NO,  ";
		strSql += " PLAN_UP_X = :p_PLAN_UP_X,   ";
		strSql += " PLAN_UP_Y = :p_PLAN_UP_Y,   ";
		strSql += " PLAN_UP_Z = :p_PLAN_UP_Z   ";
		strSql += " WHERE  CRANE_NO = :p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_MAT_UP_SCAN_NO") = matUpScanNO;
		cmd.Param("p_PLAN_UP_X") = planUpX;
		cmd.Param("p_PLAN_UP_Y") = planUpY;
		cmd.Param("p_PLAN_UP_Z") = planUpZ;
		cmd.Param("p_CRANE_NO") =craneNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......UpdOrderCurrentUpScanNOAndPoint success!"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdOrderCurrentDownScanNOAndPoint(string craneNO, string matDownScanNO, long planDownX, long planDownY, long planDownZ)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdOrderCurrentDownScanNOAndPoint()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " UPDATE UACS_CRANE_ORDER_CURRENT  SET ";
		strSql += " MAT_DOWN_SCAN_NO = :p_MAT_DOWN_SCAN_NO,  ";
		strSql += " PLAN_DOWN_X = :p_PLAN_DOWN_X,   ";
		strSql += " PLAN_DOWN_Y = :p_PLAN_DOWN_Y,   ";
		strSql += " PLAN_DOWN_Z = :p_PLAN_DOWN_Z   ";
		strSql += " WHERE  CRANE_NO = :p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_MAT_DOWN_SCAN_NO") = matDownScanNO;
		cmd.Param("p_PLAN_DOWN_X") = planDownX;
		cmd.Param("p_PLAN_DOWN_Y") = planDownY;
		cmd.Param("p_PLAN_DOWN_Z") = planDownZ;
		cmd.Param("p_CRANE_NO") =craneNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......UpdOrderCurrentDownScanNOAndPoint success!"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdOrderCurrentCarScanNO(string craneNO, string carScanNO)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdOrderCurrentCarScanNO()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " UPDATE UACS_CRANE_ORDER_CURRENT  SET ";
		strSql += " CAR_SCAN_NO = :p_CAR_SCAN_NO  ";
		strSql += " WHERE  CRANE_NO = :p_CRANE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_CAR_SCAN_NO") = carScanNO;
		cmd.Param("p_CRANE_NO") =craneNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......UpdOrderCurrentCarScanNO success!"<<endl;


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


bool  Adapter_UACS_CRANE_ORDER_CURRENT::SelCarScanOrderRec(long orderNO, 
																															   string& parkingNO, 
																															   long& planStartX, 
																															   long& planStartY, 
																															   long& planEndX, 
																															   long& planEndY,
																															   long& actStartX, 
																															   long& actStartY, 
																															   long& actEndX, 
																															   long& actEndY, 
																															   string& moveDir, 
																															   string& scanActionFlag )
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: SelCarScanOrderRec()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		string strSql="SELECT * FROM  UACS_CAR_SCAN_ORDER_REC  WHERE ";
		strSql += " ORDER_NO = :p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{	
			if(!cmd.Field("PARKING_NO").IsNull())
			{
				parkingNO = cmd.Field("PARKING_NO").AsString();
			}

			if(!cmd.Field("PLAN_START_X").IsNull())
			{
				planStartX = cmd.Field("PLAN_START_X").AsLong();
			}
			if(!cmd.Field("PLAN_START_Y").IsNull())
			{
				planStartY = cmd.Field("PLAN_START_Y").AsLong();
			}

			if(!cmd.Field("PLAN_END_X").IsNull())
			{
				planEndX = cmd.Field("PLAN_END_X").AsLong();
			}
			if(!cmd.Field("PLAN_END_Y").IsNull())
			{
				planEndY = cmd.Field("PLAN_END_Y").AsLong();
			}

			if(!cmd.Field("ACT_START_X").IsNull())
			{
				actStartX = cmd.Field("ACT_START_X").AsLong();
			}
			if(!cmd.Field("ACT_START_Y").IsNull())
			{
				actStartY = cmd.Field("ACT_START_Y").AsLong();
			}

			if(!cmd.Field("ACT_END_X").IsNull())
			{
				actEndX = cmd.Field("ACT_END_X").AsLong();
			}
			if(!cmd.Field("ACT_END_Y").IsNull())
			{
				actEndY = cmd.Field("ACT_END_Y").AsLong();
			}

			if(!cmd.Field("MOVE_DIR").IsNull())
			{
				moveDir = cmd.Field("MOVE_DIR").AsString();
			}

			if(!cmd.Field("SCAN_ACTION_FLAG").IsNull())
			{
				scanActionFlag = cmd.Field("SCAN_ACTION_FLAG").AsString();
			}
			ret = true;
			return ret;
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}


bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdScanActionFlag(long orderNO, string scanActionFlag)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdScanActionFlag()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " UPDATE UACS_CAR_SCAN_ORDER_REC  SET ";
		strSql += " SCAN_ACTION_FLAG = :p_SCAN_ACTION_FLAG  ";
		strSql += " WHERE  ORDER_NO = :p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_SCAN_ACTION_FLAG") = scanActionFlag;
		cmd.Param("p_ORDER_NO") =orderNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......UpdScanActionFlag success!"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: InitActStartXYInCarScanOrderRec(long orderNO)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: InitActStartXYInCarScanOrderRec()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " UPDATE UACS_CAR_SCAN_ORDER_REC  SET ";
		strSql += " ACT_START_X = :p_ACT_START_X, ";
		strSql += " ACT_START_Y = :p_ACT_START_Y  ";
		strSql += " WHERE  ORDER_NO = :p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ACT_START_X") = DB_INT_NULL;
		cmd.Param("p_ACT_START_Y") = DB_INT_NULL;
		cmd.Param("p_ORDER_NO") =orderNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......InitActStartXYInCarScanOrderRec success!"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdActStartXYInCarScanOrderRec(long orderNO, long actStartX, long actStartY)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdActStartXYInCarScanOrderRec()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " UPDATE UACS_CAR_SCAN_ORDER_REC  SET ";
		strSql += " ACT_START_X = :p_ACT_START_X, ";
		strSql += " ACT_START_Y = :p_ACT_START_Y  ";
		strSql += " WHERE  ORDER_NO = :p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ACT_START_X") = actStartX;
		cmd.Param("p_ACT_START_Y") = actStartY;
		cmd.Param("p_ORDER_NO") =orderNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......UpdActStartXYInCarScanOrderRec success!"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: UpdActEndXYInCarScanOrderRec(long orderNO, long actEndX, long actEndY)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: UpdActEndXYInCarScanOrderRec()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " UPDATE UACS_CAR_SCAN_ORDER_REC  SET ";
		strSql += " ACT_END_X = :p_ACT_END_X, ";
		strSql += " ACT_END_Y = :p_ACT_END_Y  ";
		strSql += " WHERE  ORDER_NO = :p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ACT_END_X") = actEndX;
		cmd.Param("p_ACT_END_Y") = actEndY;
		cmd.Param("p_ORDER_NO") =orderNO;		
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......UpdActEndXYInCarScanOrderRec success!"<<endl;


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


bool Adapter_UACS_CRANE_ORDER_CURRENT:: DelCarScanOrderRecByOrderNO(long orderNO)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: DelCarScanOrderRecByOrderNO()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " DELETE  FROM  UACS_CAR_SCAN_ORDER_REC  ";
		strSql += " WHERE  ORDER_NO = :p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......DelCarScanOrderRecByOrderNO success!"<<endl;


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


bool  Adapter_UACS_CRANE_ORDER_CURRENT::SelFlagInCarScanOrderRec(long orderNO, string& scanActionFlag)
{
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: SelFlagInCarScanOrderRec()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		string strSql="SELECT SCAN_ACTION_FLAG   FROM  UACS_CAR_SCAN_ORDER_REC  WHERE ";
		strSql += " ORDER_NO = :p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("SCAN_ACTION_FLAG").IsNull())
			{
				scanActionFlag = cmd.Field("SCAN_ACTION_FLAG").AsString();
			}
			ret = true;
			return ret;
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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

	return ret;
}

bool Adapter_UACS_CRANE_ORDER_CURRENT:: InsCarScanOrderRec(long orderNO, 
																															  string parkingNO, 
																															  long planStartX, 
																															  long planStartY, 
																															  long planEndX, 
																															  long planEndY, 
																															  string moveDir)
{
	bool ret=false;
	string functionName="Adapter_UACS_CRANE_ORDER_CURRENT :: InsCarScanOrderRec()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql="";
		strSql += " INSERT  INO  UACS_CAR_SCAN_ORDER_REC( ";
		strSql += " ORDER_NO, ";
		strSql += " PARKING_NO, ";
		strSql += " PLAN_START_X, ";
		strSql += " PLAN_START_Y, ";
		strSql += " PLAN_END_X, ";
		strSql += " PLAN_END_Y, ";
		strSql += " MOVE_DIR, ";
		strSql += " REC_TIME )  ";

		strSql += " VALUES( ";
		strSql += " :p_ORDER_NO, ";
		strSql += " :p_PARKING_NO, ";
		strSql += " :p_PLAN_START_X, ";
		strSql += " :p_PLAN_START_Y, ";
		strSql += " :p_PLAN_END_X, ";
		strSql += " :p_PLAN_END_Y, ";
		strSql += " :p_MOVE_DIR, ";
		strSql += " :p_REC_TIME ) ";		

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Param("p_PARKING_NO") = parkingNO;
		cmd.Param("p_PLAN_START_X") =planStartX;
		cmd.Param("p_PLAN_START_Y") =planStartY;
		cmd.Param("p_PLAN_END_X") =planEndX;
		cmd.Param("p_PLAN_END_Y") =planEndY;
		cmd.Param("p_MOVE_DIR") =moveDir;
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"......InsCarScanOrderRec success!"<<endl;


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