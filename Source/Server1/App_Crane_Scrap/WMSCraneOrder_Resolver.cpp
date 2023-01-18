#include "WMSCraneOrder_Resolver.h"
#include "ACTION_COMMON_FUNCTION.h"

using  namespace  Monitor;


WMSCraneOrder_Resolver::WMSCraneOrder_Resolver()
{

}
WMSCraneOrder_Resolver::~WMSCraneOrder_Resolver()
{

}

bool WMSCraneOrder_Resolver::resolver_WMSCraneOrder(OrderQueueBase orderQueueData, OrderCurrentBase & orderCurrentData)
{
	bool ret = true;
	string functionName = "WMSCraneOrder_Resolver :: resolver_WMSCraneOrder()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		log.Debug() << "resolver_WMSCraneOrder.....start.............................................................................................." << endl;

		long orderNO = orderQueueData.getOrderNO();
		orderCurrentData.setOrderNO(orderNO);
		log.Info()<<"1......orderNO = "<<orderNO<<" , set success"<<endl;

		string bayNO = orderQueueData.getBayNO();
		orderCurrentData.setBayNO(bayNO);
		log.Info()<<"2......bayNO = "<<bayNO<<" , set success"<<endl;

		string matCode = orderQueueData.getMatCode();
		orderCurrentData.setMatCode(matCode);
		log.Info()<<"3......matCode = "<<matCode<<" , set success"<<endl;

		string compCode = orderQueueData.getCompCode();
		orderCurrentData.setCompCode(compCode);
		log.Info()<<"4......compCode = "<<compCode<<" , set success"<<endl;

		string matType = "";
		if (false == WMSCraneOrder_Resolver::SelMatType(matCode, compCode, matType))
		{
			log.Info()<<"5......matType,  set failed....return false.............."<<endl;
			ret = false;
			return ret;
		}
		orderCurrentData.setMatType(matType);
		log.Info()<<"5......matType = "<<matType<<" , set success"<<endl;

		long matReqWgt = orderQueueData.getReqWeight();
		orderCurrentData.setMatReqWgt(matReqWgt);
		log.Info()<<"6......matReqWgt = "<<matReqWgt<<" , set success"<<endl;

		long matActWgt = orderQueueData.getActWeight();
		orderCurrentData.setMatActWgt(matActWgt);
		log.Info()<<"7......matActWgt = "<<matActWgt<<" , set success"<<endl;

		//行车都是在空载情况下获取指令，重载情况下不会丢失指令，
		//因此,当次作业重量可以设定为0 
		//当然 ，如果是先手动起吊后，然后重载升起，再切了自动，然后自动获取指令，
		//此时,如果能跟踪到指令queue里的指令,则获取此条指令
		//long matCurWgt = 0;
		long matCurWgt = orderQueueData.getCurWeight();
		orderCurrentData.setMatCurWgt(matCurWgt);
		log.Info()<<"8......matCurWgt = "<<matCurWgt<<" , set success"<<endl;

		string orderType = orderQueueData.getOrderType();
		orderCurrentData.setOrderType(orderType);
		log.Info()<<"9......orderType = "<<orderType<<" , set success"<<endl;

		long orderPriority = orderQueueData.getOrderPriority();
		orderCurrentData.setOrderPriority(orderPriority);
		log.Info()<<"10......orderPriority = "<<orderPriority<<" , set success"<<endl;

		string fromStockNO = orderQueueData.getFromStockNO();
		orderCurrentData.setFromStockNO(fromStockNO);
		log.Info()<<"11......fromStockNO = "<<fromStockNO<<" , set success"<<endl;

		string toStockNO = orderQueueData.getToStockNO();
		orderCurrentData.setToStockNO(toStockNO);
		log.Info()<<"12......toStockNO = "<<toStockNO<<" , set success"<<endl;

		string cmdStatus = OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_ORDER_INIT;
		orderCurrentData.setCmdStatus(cmdStatus);
		log.Info()<<"13......cmdStatus = "<<cmdStatus<<" , set success"<<endl;

		//第几次吊运还是需要从orderQueue中获取
		//long cmdSeq = 1;//获取指令后，属于第1次吊运
		long cmdSeq = orderQueueData.getCmdSeq();
		orderCurrentData.setCmdSeq(cmdSeq);
		log.Info()<<"14......cmdSeq = "<<cmdSeq<<" , set success"<<endl;

		string craneNO = orderQueueData.getCraneNO();
		orderCurrentData.setCraneNO(craneNO);
		log.Info()<<"15......craneNO = "<<craneNO<<" , set success"<<endl;

		//车辆激光扫描号  初始设置成 null
		string carScanNO = "";
		//从表 UACS_PARKING_SRS_CAR_INFO 中获取车辆激光扫描号，如果没有，则返回false；有，则返回true
		WMSCraneOrder_Resolver::SelCarScanNO(orderCurrentData.getOrderNO(), carScanNO);
		orderCurrentData.setCarScanNO(carScanNO);
		log.Info()<<"16......carScanNO = "<<carScanNO<<" , set success"<<endl;

		//物料取料激光扫描号 置为空 null 
		//因为:自动第一次获取指令时,肯定是null
		//         切了手动 再切自动  获取指令时, 认为也要重新扫描, 所以也是null
		string matUpScanNO = "";
		orderCurrentData.setMatUpScanNO(matUpScanNO);
		log.Info()<<"17......matUpScanNO = "<<matUpScanNO<<" , set success"<<endl;

		orderCurrentData.setPlanUpX(DB_INT_NULL);
		log.Info()<<"18......setPlanUpX = "<<DB_INT_NULL<<" , set success"<<endl;

		orderCurrentData.setPlanUpY(DB_INT_NULL);
		log.Info()<<"19......setPlanUpY = "<<DB_INT_NULL<<" , set success"<<endl;

		orderCurrentData.setPlanUpZ(DB_INT_NULL);
		log.Info()<<"20......setPlanUpZ = "<<DB_INT_NULL<<" , set success"<<endl;

		orderCurrentData.setUpRotateAngle(DB_INT_NULL);
		log.Info()<<"21......setUpRotateAngle = "<<DB_INT_NULL<<" , set success"<<endl;

		//物料放料激光扫描号 置为空 null 
		//因为:自动第一次获取指令时,肯定是null
		//         切了手动 再切自动  获取指令时, 认为也要重新扫描, 所以也是null
		string matDownScanNO = "";
		orderCurrentData.setMatDownScanNO(matDownScanNO);
		log.Info()<<"22......matDownScanNO = "<<matDownScanNO<<" , set success"<<endl;

		orderCurrentData.setPlanDownX(DB_INT_NULL);
		log.Info()<<"23......setPlanDownX = "<<DB_INT_NULL<<" , set success"<<endl;

		orderCurrentData.setPlanDownY(DB_INT_NULL);
		log.Info()<<"24......setPlanDownY = "<<DB_INT_NULL<<" , set success"<<endl;

		orderCurrentData.setPlanDownZ(DB_INT_NULL);
		log.Info()<<"25......setPlanDownZ = "<<DB_INT_NULL<<" , set success"<<endl;

		orderCurrentData.setDownRotateAngle(DB_INT_NULL);
		log.Info()<<"26......setDownRotateAngle = "<<DB_INT_NULL<<" , set success"<<endl;		


		log.Debug() << "........................................................................................................................................................................................................... " << endl;
		log.Debug() << "....................................................All order data is ready, continue to insert into Uacs_Crane_Order_Current................... " << endl;
		log.Debug() << "............................................................................................................................................................................................................ " << endl;

		Adapter_UACS_CRANE_ORDER_CURRENT::  receive_A_NewCraneOrder( orderCurrentData.getOrderNO(), 
																																		   orderCurrentData.getBayNO(), 
																																		   orderCurrentData.getMatCode(), 
																																		   orderCurrentData.getCompCode(), 
																																		   orderCurrentData.getMatType(), 
																																		   orderCurrentData.getMatReqWgt(), 
																																		   orderCurrentData.getMatActWgt(), 
																																		   orderCurrentData.getMatCurWgt(), 
																																		   orderCurrentData.getOrderType(), 
																																		   orderCurrentData.getOrderPriority(), 
																																		   orderCurrentData.getFromStockNO(), 
																																		   orderCurrentData.getToStockNO(), 
																																		   orderCurrentData.getCmdStatus(), 
																																		   orderCurrentData.getCmdSeq(), 
																																		   orderCurrentData.getCraneNO(), 
																																		   orderCurrentData.getCarScanNO(),
																																		   orderCurrentData.getMatUpScanNO(), 
																																		   orderCurrentData.getPlanUpX(), 
																																		   orderCurrentData.getPlanUpY(), 
																																		   orderCurrentData.getPlanUpZ(), 
																																		   orderCurrentData.getUpRotateAngle(), 
																																		   orderCurrentData.getMatDownScanNO(), 
																																		   orderCurrentData.getPlanDownX(), 
																																		   orderCurrentData.getPlanDownY(), 
																																		   orderCurrentData.getPlanDownZ(), 
																																		   orderCurrentData.getDownRotateAngle() );

		//清空报警
		ACTION_COMMON_FUNCTION::SetTagValue(craneNO, 
																							ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS, 
																							ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_0);		

		//2018.7.16 zhangyuhong add
		//行车自动模式下拿到指令时刻 搓 EV tag点 通知指令模块
		//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
		//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
		//指令状态（）
		string tagName = "EV_CRANE_ORDER_CMD_STATUS";
		string tagValue = StringHelper::ToString(orderCurrentData.getOrderNO()) + "," + StringHelper::ToString(orderCurrentData.getCmdSeq());
		tagValue += "," + OrderQueueBase::CMD_STATUS_START_1 + StringHelper::ToString(orderQueueData.getCurWeight());
		ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);


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

//2018.8.7 zhangyuhong add
bool WMSCraneOrder_Resolver::resolver_BoardingCraneOrder(string craneNO, CranePLCStatusBase cranePLCStatusCurrent)
{
	string functionName="WMSCraneOrder_Resolver :: resolver_BoardingCraneOrder()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		//找不到登车位配置表坐标
		long pointXBoardingPos = DB_INT_NULL;
		long pointYBoardingPos = DB_INT_NULL;
		/*if(false == Test_Evade_Move::getBoardPointByCraneNO(craneNO, pointXBoardingPos, pointYBoardingPos) )
		{
			ret = false;
			return ret;
		}*/

		//如果当前已经是登车位位置，则不再写指令表
		if ( true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatusCurrent.getXAct(), cranePLCStatusCurrent.getYAct(), pointXBoardingPos, pointYBoardingPos) )
		{
			log.Info()<<"行车已经到达登车位！不再写登车位指令到指令表！返回false！"<<endl;
			ret = false;
			return ret;
		}

		//获取当前指令表，如果已经是回登车位指令，则不再更新
		OrderCurrentBase orderCurrent;
		orderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);
		if (orderCurrent.getOrderType() == "X1")
		{
			log.Info()<<"指令类型="<<orderCurrent.getOrderType()<<",  当前指令表里已经是回登车位指令！返回false！"<<endl;
			ret = false;
			return ret;
		}

		

		//----------------------------------------------------------------------------------------------------------------------------
		long orderNO = 115;
		string	 bayNO = "C2A-1";
		string matNO = DB_STR_NULL;
		string orderType = "X1";
		long orderPriority = 5;
		string fromStockNO = DB_STR_NULL;
		string toStockNO = DB_STR_NULL;
		string cmdStatus = CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS;
		long planUpX = pointXBoardingPos;
		long planUpY = pointYBoardingPos;
		long planUpZ = DB_INT_NULL;
		long upRotateAngleSet = DB_INT_NULL;
		long clampWidthSet = DB_INT_NULL;
		long planDownX = DB_INT_NULL;
		long planDownY= DB_INT_NULL;
		long planDownZ = DB_INT_NULL;
		long downRotateAngleSet = DB_INT_NULL;
		long coilWidth = DB_INT_NULL;
		long coilWeight = DB_INT_NULL;
		long coilOutDia= DB_INT_NULL;
		long coilInDia = DB_INT_NULL;
		long  floorUpZ = DB_INT_NULL;
		long  flagSmallCoil = DB_INT_NULL;
		long   floorDownZ = DB_INT_NULL;

		Adapter_UACS_CRANE_ORDER_CURRENT::receive_BoardingCraneOrder(craneNO,  
																																			orderNO,
																																			bayNO,  
																																			matNO, 
																																			orderType, 
																																			orderPriority, 
																																			fromStockNO,
																																			toStockNO,
																																			cmdStatus,
																																			planUpX,
																																			planUpY,
																																			planUpZ,
																																			upRotateAngleSet,
																																			clampWidthSet,
																																			planDownX,
																																			planDownY,
																																			planDownZ,
																																			downRotateAngleSet,
																																			coilWidth,
																																			coilWeight,
																																			coilOutDia,
																																			coilInDia,
																																			floorUpZ,
																																			flagSmallCoil,
																																			floorDownZ);
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







bool WMSCraneOrder_Resolver::SelCraneOrder(string craneNO, OrderQueueBase& orderQueueData)
{
	bool ret = false;
	string functionName="WMSCraneOrder_Resolver :: SelCraneOrder()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string orderType = "";
		//根据优先级降序，生成时刻升序 获取第一条状态是 0 -初始化的 指令
		string strSql = "";
		strSql = "SELECT * FROM UACS_ORDER_QUEUE WHERE ";
		strSql += " CRANE_NO= :p_CRANE_NO ";
		strSql += " AND ORDER_STATUS = '0' ";
		strSql += " AND EXE_ENABLE = '1' ";//获取可吊的指令
		strSql += " ORDER BY PRIORITY DESC, REC_TIME ASC ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_CRANE_NO") = craneNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			ret = true;
			//1
			if ( !cmd.Field("ORDER_NO").IsNull() )
			{
				orderQueueData.setOrderNO(cmd.Field("ORDER_NO").AsLong());
			}
			//2
			if ( !cmd.Field("ORDER_GROUP_NO").IsNull() )
			{
				orderQueueData.setOrderGroupNO(cmd.Field("ORDER_GROUP_NO").AsLong());
			}
			//3
			if ( !cmd.Field("EXE_SEQ").IsNull() )
			{
				orderQueueData.setExeSeq(cmd.Field("EXE_SEQ").AsLong());
			}
			//4
			if ( !cmd.Field("ORDER_TYPE").IsNull() )
			{
				orderQueueData.setOrderType(cmd.Field("ORDER_TYPE").AsString());
			}	
			//5
			if ( !cmd.Field("ORDER_PRIORITY").IsNull() )
			{
				orderQueueData.setOrderPriority(cmd.Field("ORDER_PRIORITY").AsLong());
			}
			//6
			if ( !cmd.Field("EXE_ENABLE").IsNull() )
			{
				orderQueueData.setExeEnable(cmd.Field("EXE_ENABLE").AsString());
			}
			//7
			if ( !cmd.Field("CRANE_NO").IsNull() )
			{
				orderQueueData.setCraneNO(cmd.Field("CRANE_NO").AsString());
			}
			//8
			if ( !cmd.Field("CMD_STATUS").IsNull() )
			{
				orderQueueData.setCmdStatus(cmd.Field("CMD_STATUS").AsString());
			}
			//9
			if ( !cmd.Field("CMD_SEQ").IsNull() )
			{
				orderQueueData.setCmdSeq(cmd.Field("CMD_SEQ").AsLong());
			}
			//10
			if ( !cmd.Field("PLAN_SRC").IsNull() )
			{
				orderQueueData.setPlanSrc(cmd.Field("PLAN_SRC").AsString());
			}
			//11
			if ( !cmd.Field("PLAN_NO").IsNull() )
			{
				orderQueueData.setPlanNO(cmd.Field("PLAN_NO").AsString());
			}
			//12
			if ( !cmd.Field("PLAN_DETAIL_ID").IsNull() )
			{
				orderQueueData.setPlanDetailID(cmd.Field("PLAN_DETAIL_ID").AsLong());
			}
			//13
			if ( !cmd.Field("SCRAP_CODE").IsNull() )
			{
				orderQueueData.setScrapCode(cmd.Field("SCRAP_CODE").AsString());
			}
			//14
			if ( !cmd.Field("REQ_WEIGHT").IsNull() )
			{
				orderQueueData.setReqWeight(cmd.Field("REQ_WEIGHT").AsLong());
			}
			//15
			if ( !cmd.Field("CAR_NO").IsNull() )
			{
				orderQueueData.setCarNO(cmd.Field("CAR_NO").AsString());
			}
			//16
			if ( !cmd.Field("CAR_TYPE").IsNull() )
			{
				orderQueueData.setCarType(cmd.Field("CAR_TYPE").AsString());
			}
			//17
			if ( !cmd.Field("BAY_NO").IsNull() )
			{
				orderQueueData.setBayNO(cmd.Field("BAY_NO").AsString());
			}
			//18
			if ( !cmd.Field("MAT_CODE").IsNull() )
			{
				orderQueueData.setMatCode(cmd.Field("MAT_CODE").AsString());
			}
			//19
			if ( !cmd.Field("COMP_CODE").IsNull() )
			{
				orderQueueData.setCompCode(cmd.Field("COMP_CODE").AsString());
			}
			//20
			if ( !cmd.Field("CAL_WEIGHT").IsNull() )
			{
				orderQueueData.setCalWeight(cmd.Field("CAL_WEIGHT").AsLong());
			}
			//21
			if ( !cmd.Field("ACT_WEIGHT").IsNull() )
			{
				orderQueueData.setActWeight(cmd.Field("ACT_WEIGHT").AsLong());
			}
			//22
			if ( !cmd.Field("FROM_STOCK_NO").IsNull() )
			{
				orderQueueData.setFromStockNO(cmd.Field("FROM_STOCK_NO").AsString());
			}
			//23
			if ( !cmd.Field("TO_STOCK_NO").IsNull() )
			{
				orderQueueData.setToStockNO(cmd.Field("TO_STOCK_NO").AsString());
			}
			//24
			if ( !cmd.Field("DOWN_POS_SEQ").IsNull() )
			{
				orderQueueData.setDownPosSeq(cmd.Field("DOWN_POS_SEQ").AsLong());
			}
		}
		
		if (ret == true)
		{
			//是否是RGV指令，包括那种装料槽车
			if (orderQueueData.getOrderType() == OrderQueueBase::ORDER_TYPE_BOF_YARD_TO_RGV_23 || 
				orderQueueData.getOrderType() == OrderQueueBase::ORDER_TYPE_BOF_YARD_TO_CAR_24)
			{
				log.Info()<<"This is RGV order................................"<<endl;
				//根据组号再获取exeSeq，取升序排列的第一条记录
				string strSql2 = "";
				strSql2 = "SELECT * FROM UACS_ORDER_QUEUE WHERE ";
				strSql2 += " CRANE_NO= :p_CRANE_NO ";
				strSql2 += " AND ORDER_STATUS = '0'  ";
				strSql2 += " AND ORDER_GROUP_NO = :p_ORDER_GROUP_NO  ";
				strSql2 += " ORDER BY EXE_NO  ASC ";
				iDA::Command cmd2(&CDataAccess::GetInstance()->m_DBCon, strSql2);    // command object
				cmd2.Param("p_CRANE_NO") = craneNO;
				cmd2.Param("p_ORDER_GROUP_NO") = orderQueueData.getOrderGroupNO();
				cmd2.Execute();

				if (cmd2.FetchNext())
				{
					//1
					if ( !cmd2.Field("ORDER_NO").IsNull() )
					{
						orderQueueData.setOrderNO(cmd.Field("ORDER_NO").AsLong());
					}
					//2
					if ( !cmd2.Field("ORDER_GROUP_NO").IsNull() )
					{
						orderQueueData.setOrderGroupNO(cmd.Field("ORDER_GROUP_NO").AsLong());
					}
					//3
					if ( !cmd2.Field("EXE_SEQ").IsNull() )
					{
						orderQueueData.setExeSeq(cmd.Field("EXE_SEQ").AsLong());
					}
					//4
					if ( !cmd2.Field("ORDER_TYPE").IsNull() )
					{
						orderQueueData.setOrderType(cmd.Field("ORDER_TYPE").AsString());
					}	
					//5
					if ( !cmd2.Field("ORDER_PRIORITY").IsNull() )
					{
						orderQueueData.setOrderPriority(cmd.Field("ORDER_PRIORITY").AsLong());
					}
					//6
					if ( !cmd2.Field("EXE_ENABLE").IsNull() )
					{
						orderQueueData.setExeEnable(cmd.Field("EXE_ENABLE").AsString());
					}
					//7
					if ( !cmd2.Field("CRANE_NO").IsNull() )
					{
						orderQueueData.setCraneNO(cmd.Field("CRANE_NO").AsString());
					}
					//8
					if ( !cmd2.Field("CMD_STATUS").IsNull() )
					{
						orderQueueData.setCmdStatus(cmd.Field("CMD_STATUS").AsString());
					}
					//9
					if ( !cmd2.Field("CMD_SEQ").IsNull() )
					{
						orderQueueData.setCmdSeq(cmd.Field("CMD_SEQ").AsLong());
					}
					//10
					if ( !cmd2.Field("PLAN_SRC").IsNull() )
					{
						orderQueueData.setPlanSrc(cmd.Field("PLAN_SRC").AsString());
					}
					//11
					if ( !cmd2.Field("PLAN_NO").IsNull() )
					{
						orderQueueData.setPlanNO(cmd.Field("PLAN_NO").AsString());
					}
					//12
					if ( !cmd2.Field("PLAN_DETAIL_ID").IsNull() )
					{
						orderQueueData.setPlanDetailID(cmd.Field("PLAN_DETAIL_ID").AsLong());
					}
					//13
					if ( !cmd2.Field("SCRAP_CODE").IsNull() )
					{
						orderQueueData.setScrapCode(cmd.Field("SCRAP_CODE").AsString());
					}
					//14
					if ( !cmd2.Field("REQ_WEIGHT").IsNull() )
					{
						orderQueueData.setReqWeight(cmd.Field("REQ_WEIGHT").AsLong());
					}
					//15
					if ( !cmd2.Field("CAR_NO").IsNull() )
					{
						orderQueueData.setCarNO(cmd.Field("CAR_NO").AsString());
					}
					//16
					if ( !cmd2.Field("CAR_TYPE").IsNull() )
					{
						orderQueueData.setCarType(cmd.Field("CAR_TYPE").AsString());
					}
					//17
					if ( !cmd2.Field("BAY_NO").IsNull() )
					{
						orderQueueData.setBayNO(cmd.Field("BAY_NO").AsString());
					}
					//18
					if ( !cmd2.Field("MAT_CODE").IsNull() )
					{
						orderQueueData.setMatCode(cmd.Field("MAT_CODE").AsString());
					}
					//19
					if ( !cmd2.Field("COMP_CODE").IsNull() )
					{
						orderQueueData.setCompCode(cmd.Field("COMP_CODE").AsString());
					}
					//20
					if ( !cmd2.Field("CAL_WEIGHT").IsNull() )
					{
						orderQueueData.setCalWeight(cmd.Field("CAL_WEIGHT").AsLong());
					}
					//21
					if ( !cmd2.Field("ACT_WEIGHT").IsNull() )
					{
						orderQueueData.setActWeight(cmd.Field("ACT_WEIGHT").AsLong());
					}
					//22
					if ( !cmd2.Field("FROM_STOCK_NO").IsNull() )
					{
						orderQueueData.setFromStockNO(cmd.Field("FROM_STOCK_NO").AsString());
					}
					//23
					if ( !cmd2.Field("TO_STOCK_NO").IsNull() )
					{
						orderQueueData.setToStockNO(cmd.Field("TO_STOCK_NO").AsString());
					}
					//24
					if ( !cmd2.Field("DOWN_POS_SEQ").IsNull() )
					{
						orderQueueData.setDownPosSeq(cmd.Field("DOWN_POS_SEQ").AsLong());
					}
			}//  if (cmd2.FetchNext())
		}//   if (orderQueueData.getOrderType() 
		else
		{
			log.Info()<<"This is not RGV order......................."<<endl;
		}
	}// if(ret = true)

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

bool WMSCraneOrder_Resolver::SelMatType(string matCode, string compCode, string& matType)
{
	bool ret = false;
	string functionName="WMSCraneOrder_Resolver :: SelMatType()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql = "";
		strSql = "SELECT * FROM UACS_L3_MAT_RELATION_INFO WHERE ";
		strSql += " MAT_CODE= :p_MAT_CODE AND ";
		strSql += " COMP_CODE = :p_COMP_CODE ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_MAT_CODE") = matCode;
		cmd.Param("p_COMP_CODE") = compCode;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			ret = true;
			if ( !cmd.Field("MAT_TYPE").IsNull() )
			{
				matType = cmd.Field("MAT_TYPE").AsString();
			}
		}
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

bool WMSCraneOrder_Resolver::SelStockPosData(string orderType, string fromStockNO, string toStockNO, vector<long>& vecFromStockPos, vector<long>& vecToStockPos)
{
	bool ret = false;
	string functionName="WMSCraneOrder_Resolver :: SelStockPosData()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSqlFromStock = "";
		string strSqlToStock = "";
		
		if ( orderType == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || orderType == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 || 
			 orderType == OrderQueueBase::ORDER_TYPE_BOF_YARD_TO_RGV_23 || orderType == OrderQueueBase::ORDER_TYPE_BOF_YARD_TO_CAR_24 )
		{
			//起始点为料格，放下点为停车位
			ret = true;
			strSqlFromStock = "SELECT  * FROM UACS_YARDMAP_GRID_DEFINE WHERE GRID_NO = :p_FROM_STOCK_NO";
			strSqlToStock = "SELECT  * FROM UACS_PARKING_INFO_DEFINE WHERE PARKING_NO = :p_TO_STOCK_NO";
		}

		if (orderType == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			//起始点为停车位，放下点为料格
			ret = true;
			strSqlFromStock = "SELECT  * FROM UACS_PARKING_INFO_DEFINE WHERE PARKING_NO = :p_FROM_STOCK_NO";
			strSqlToStock = "SELECT  * FROM UACS_YARDMAP_GRID_DEFINE WHERE GRID_NO = :p_TO_STOCK_NO";
		}

		if (ret == false)
		{
			log.Info()<<"orderType is error, return false.................................."<<endl;
			return ret;
		}

		long xCenter = DB_INT_NULL;
		long yCenter = DB_INT_NULL;

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSqlFromStock);    // command object
		cmd.Param("p_FROM_STOCK_NO") = fromStockNO;
		cmd.Execute();
		if (cmd.FetchNext())
		{
			if ( !cmd.Field("X_CENTER").IsNull() )
			{
				xCenter = cmd.Field("X_CENTER").AsLong();
			}
			if ( !cmd.Field("Y_CENTER").IsNull() )
			{
				yCenter = cmd.Field("Y_CENTER").AsLong();
			}
			vecFromStockPos.push_back(xCenter);
			vecFromStockPos.push_back(yCenter);
		}
		else
		{
			log.Info()<<"FromStockNO is not find in table....................return false................."<<endl;
			ret = false;
			return ret;
		}

		iDA::Command cmd2(&CDataAccess::GetInstance()->m_DBCon, strSqlToStock);    // command object
		cmd2.Param("p_TO_STOCK_NO") = toStockNO;
		cmd2.Execute();
		if (cmd2.FetchNext())
		{
			if ( !cmd2.Field("X_CENTER").IsNull() )
			{
				xCenter = cmd2.Field("X_CENTER").AsLong();
			}
			if ( !cmd.Field("Y_CENTER").IsNull() )
			{
				yCenter = cmd2.Field("Y_CENTER").AsLong();
			}
			vecToStockPos.push_back(xCenter);
			vecToStockPos.push_back(yCenter);
		}
		else
		{
			log.Info()<<"ToStockNO is not find in table....................return false................."<<endl;
			ret = false;
			return ret;
		}

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


bool WMSCraneOrder_Resolver::SelCarScanNO(long orderNO, string& carScanNO)
{
	bool ret = false;
	string functionName="WMSCraneOrder_Resolver :: SelCarScanNO()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string strSql = "";

		strSql = "SELECT  SCAN_NO  FROM UACS_PARKING_SRS_CAR_INFO  WHERE ORDER_NO = :p_ORDER_NO  ORDER BY REC_TIME  DESC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Execute();
		if (cmd.FetchNext())
		{
			if ( !cmd.Field("SCAN_NO").IsNull() )
			{
				carScanNO = cmd.Field("SCAN_NO").AsString();
			}
			ret = true;
			return ret;
		}

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