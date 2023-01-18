#include "JUDGE_BEFORE_MOVING.h"
#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"



using namespace Monitor;



JUDGE_BEFORE_MOVING :: JUDGE_BEFORE_MOVING(void)
{
}



JUDGE_BEFORE_MOVING :: ~JUDGE_BEFORE_MOVING(void)
{
}



//返回false就意味着不能动车
//返回true意味着能动车，这个时候还要看能够到达的X
bool JUDGE_BEFORE_MOVING ::judge(long orderNO, string craneNO, long currentX , long targetX, long& canReachX)
{


	string functionName = "MOVING_DIR :: judge()";
	LOG log(functionName, AUTO_CATCH_PID);

	//假定是不能动车的 能去的地方就是当前位置
	bool retCanMove=false;
	canReachX=currentX;

	try
	{
		log.Debug()<<"-----------------------------JUDGE START----------------------------------------------------------------------"<<endl;
		log.Debug()<<"开始在行车移动前进行判断 JUDGE_BEFORE_MOVING ::judge ：共进行4步判断................"<<endl;

		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp1 获得运动的方向
		//*
		//*********************************************************************************************************************************************************************************************
		log.Debug()<<" Step1：检查当前行车的大车(X)移动方向...."<<endl;
		string movingDirection = MOVING_DIR::getDirection(craneNO, currentX, targetX);		
		log.Debug()<<"移动方向 movingDirection="<<movingDirection<<endl;
		//如果大车运动方向判定为原地点，那么直接返回true，即只动小车是可以的
		//2018.3.14 zhangyuhong add
		if(movingDirection==MOVING_DIR::DIR_X_ON_SPOT)
		{
			log.Debug()<<"移动方向 movingDirection==DIR_X_ON_SPOT  行车的大车移动方向为原地点，Judge返回true...."<<endl;
			log.Debug()<<"canReachX="<<canReachX<<endl;
			log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
			retCanMove=true;
			return retCanMove;
		}

		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp2 按照运动的方向获得前进方向的行车号
		//*
		//*********************************************************************************************************************************************************************************************
		log.Debug()<<"Step2：准备获取相邻行车号..."<<endl;
		string neightborCraneNO=NEIGHBOR_AHEAD::getCraneNO(craneNO,movingDirection);
		log.Debug()<<"相邻行车号 neightborCraneNO="<<neightborCraneNO<<endl;		
		//前方无行车，则不需要进行下一步判断了，返回true，行车走行交给安全区
		if(neightborCraneNO==NEIGHBOR_AHEAD::NOBODY)
		{
			log.Debug()<<"相邻行车号 neightborCraneNO==NOBODY  无相邻行车！处理将返回true，行车可以直接移动，目标targetX就是可移动canReachX"<<endl;
			canReachX=targetX;
			log.Debug()<<"canReachX="<<canReachX<<endl;
			log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
			retCanMove=true;
			return retCanMove;
		}
		//行车号不明，说明判别行车号失败了，那么无条件范围false
		if(neightborCraneNO==NEIGHBOR_AHEAD::UNKNOW)
		{
			log.Debug()<<"相邻行车号 neightborCraneNO==UNKNOW 相邻行车号未知！处理将返回false，行车不能移动....."<<endl;
			log.Debug()<<"canReachX="<<canReachX<<endl;
			log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
			retCanMove=false;
			return retCanMove;
		}


		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp 3：获取本车和临近行车的PLC状态
		//*
		//*********************************************************************************************************************************************************************************************
		//到目前位置以下的代码就是针对前方有相邻行车的
		log.Debug()<<"setp 3：准备获取本车和临近行车的PLC状态......"<<endl;
		log.Debug()<<"在当前行车的大车移动方向（X）路径上有相邻行车，行车号="<<neightborCraneNO<<endl;
		
		//setp 4获得本车和临近行车的PLC状态
		log.Debug()<<"准备获取  当前行车="<<craneNO<<"  和  相邻行车="<<neightborCraneNO<<"  的PLC实时状态..."<<endl;

		CranePLCStatusBase  neightborCranePLCStatusBase;
		bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(neightborCraneNO, neightborCranePLCStatusBase);
		//log.Debug()<<"获取相邻行车的PLC实时状态函数 getNeighborPLCStatus 的返回值（bool类型）="<<ACTION_COMMON_FUNCTION::TrueOrFlase(ret_getPLCStatus)<<endl;
		if(ret_getPLCStatus==false)
		{
				log.Debug()<<"获取相邻行车的PLC实时状态失败！处理即将返回false，行车不能移动......"<<endl;
				log.Debug()<<"canReachX="<<canReachX<<endl;
				log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
				retCanMove=false;
				return retCanMove;
		}
		log.Debug()<<"相邻行车号="<<neightborCraneNO<<"  其大车实时坐标 X="<<neightborCranePLCStatusBase.getXAct()<<endl;

		//获得本车的行车PLC状态
		CranePLCStatusBase  cranePLCStatusBase;
		ret_getPLCStatus=CraneMonitor::getInstance()->getPLCStatus(cranePLCStatusBase);
		//log.Debug()<<"获取当前行车的PLC实时状态函数 getPLCStatus 的返回值（bool类型）="<<ACTION_COMMON_FUNCTION::TrueOrFlase(ret_getPLCStatus)<<endl;		
		if(ret_getPLCStatus==false)
		{
				log.Debug()<<"获取相当前车的PLC实时状态失败！处理即将返回false，行车不能移动......"<<endl;
				log.Debug()<<"canReachX="<<canReachX<<endl;
				log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
				retCanMove=false;
				return retCanMove;
		}
		log.Debug()<<"当前行车号="<<craneNO<<"  其大车实时坐标 X="<<cranePLCStatusBase.getXAct()<<endl;

		
		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp 4：根据邻车的运行模式-自动，进入相应逻辑处理
		//*
		//*********************************************************************************************************************************************************************************************
		//setp 4 根据邻车的运行模式进行逻辑处理		
		if(neightborCranePLCStatusBase.getControlMode()==CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
					log.Debug()<<"----------------------------Step4：进入邻车是自动内模式的逻辑处理------------------------------------------------"<<endl;
					log.Debug()<<"前方相邻行车号="<<neightborCraneNO<<"的控制模式为 AUTO..........."<<endl;
					
					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.1：检查目标区域是否有邻车
					//*
					//*********************************************************************************************************************************************************************************************
					//step4.1 检查目标区域是否有邻车
					log.Debug()<<"-----------------------------Step4.1：检查目标区域是否有邻车----START---------------------------------------------------"<<endl;
					bool ret_Target_Area_Is_Clean=CONDITION_TARGET_AREA_IS_CLEAN::judge(craneNO, movingDirection, currentX, targetX, neightborCranePLCStatusBase);					
					//log.Debug()<<"ret_Target_Area_Is_Clean = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(ret_Target_Area_Is_Clean)<<endl;
					log.Debug()<<"-----------------------------Step4.1：检查目标区域是否有邻车----END------------------------------------------------------"<<endl;

					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.2：检查邻车是否要冲入目标区域
					//*
					//*********************************************************************************************************************************************************************************************
					//step4.2 检查邻车是否要冲入目标区域
					log.Debug()<<"-----------------------------Step4.2：检查邻车是否要冲入目标区域----START--------------------------------------------------"<<endl;
					bool ret_Nobody_is_Moving_To_TargetArea=CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA::judge(craneNO, movingDirection, currentX, targetX, neightborCranePLCStatusBase);					
					//log.Debug()<<"检查邻车是否要冲入目标区域结果(true=目标区域无邻车要冲入)："<<ACTION_COMMON_FUNCTION::TrueOrFlase(ret_Nobody_is_Moving_To_TargetArea)<<endl;
					log.Debug()<<"-----------------------------Step4.2：检查邻车是否要冲入目标区域----END-----------------------------------------------------"<<endl;

					//2018.12.22 zhangyuhong add
					//如果我是低级车，那么永远将无人冲向我区内的条件写为危险即false
					if(CranePrivilegeInterpreter::compareByCrane(craneNO,neightborCraneNO)==CranePrivilegeInterpreter::COMPARE_RESULT_LOW)
					{
						log.Info()<<"本车="<<craneNO<<" 比 邻车="<<neightborCraneNO<<" 等级低！永远置 ret_Nobody_is_Moving_To_TargetArea = false！"<<endl;
						ret_Nobody_is_Moving_To_TargetArea=false;
					}


					if(ret_Target_Area_Is_Clean==true && ret_Nobody_is_Moving_To_TargetArea==true)
					{
						log.Debug()<<"相邻行车是 AUTO 模式，目标区域处于清空状态，且无其它行车正在进入目标区域，处理即将返回true，行车可以直接移动，目标点targetX即可到达点canReachX"<<endl;
						canReachX=targetX;
						log.Debug()<<"canReachX="<<canReachX<<endl;
						retCanMove=true;
						log.Debug()<<"-----------------------------JUDGE END----------------------------------------------------------------------"<<endl;
						return retCanMove;
					}

					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.3：目标区域有邻车或邻车要冲入目标区域
					//*
					//*********************************************************************************************************************************************************************************************
					//step4.3 目标区域有邻车或邻车要冲入目标区域	

					log.Debug()<<"-------------------------setp 4.3：目标区域有邻车或邻车要冲入目标区域------START------------------------------"<<endl;
					log.Debug()<<"Step 4.3：目标区域有邻车或邻车要冲入目标区域，行车不能移动，准备做如下判断处理......"<<endl;
					
					string priorityCraneVsNeighborCrane = CranePrivilegeInterpreter::COMPARE_RESULT_UNKNOW;					

					//2018.12.20 ZHANGYUHONG ADD 
					//暴力一点，直接用行车本地优先级作为优先
					//其它特例放在主线程里
					priorityCraneVsNeighborCrane = CranePrivilegeInterpreter::compareByCrane(craneNO, neightborCraneNO);

					//提升我的级别的几种特例：					
					if (priorityCraneVsNeighborCrane == CranePrivilegeInterpreter::COMPARE_RESULT_LOW)
					{
						OrderCurrentBase myCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

						//----------1：如果我是低级车，但是可以追随对面高级车到目标位，则提升我的级别
						if ( true == if_Facing_Auto_Car_Low_Level(craneNO, currentX, targetX, movingDirection, cranePLCStatusBase, 
																						neightborCraneNO, neightborCranePLCStatusBase, canReachX) )
						{
							log.Info()<<"1：试算后，提升我车等级！"<<endl;
							priorityCraneVsNeighborCrane = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
						}
						//----------2：如果我是低级车，我是4-5，我的指令是空钩去PA1收料，且我当前的tagetX是PA1的收料鞍座X，则提升我的级别
						if ( true == FollowException_4_5::satifyException(craneNO, targetX, cranePLCStatusBase, myCraneOrderCurrent, neightborCraneNO, neightborCranePLCStatusBase))
						{
							log.Info()<<"2：我是4-5 PA1收料！提升等级！"<<endl;
							priorityCraneVsNeighborCrane = CranePrivilegeInterpreter::COMPARE_RESULT_HIGH;
						}
					}

					
					


					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.3.4：本车优先级 > 邻车优先级：进入===> 面对低级车处理逻辑
					//*
					//*********************************************************************************************************************************************************************************************
					//这个是 ===> 步步紧逼  
					if(priorityCraneVsNeighborCrane ==CranePrivilegeInterpreter::COMPARE_RESULT_HIGH)
					{
						log.Debug()<<"----------setp 4.3.4：本车优先级 > 邻车优先级：进入===> 面对低级车处理逻辑------START------------------------------"<<endl;
						log.Debug()<<"Step 4.3.4：本车的指令优先级 > 邻车的指令优先级 ......"<<endl;
						log.Debug()<<"准备进入 judge_Facing_Auto_Car_Low_Level() 过程处理 ......"<<endl;
						retCanMove=judge_Facing_Auto_Car_Low_Level(craneNO , currentX , targetX , movingDirection , cranePLCStatusBase, 
																												neightborCraneNO,  neightborCranePLCStatusBase,
																												canReachX);
						//2018.12.22 zhangyuhong add
						//老曹最新代码
						//return retCanMove;
					}

					//*********************************************************************************************************************************************************************************************
					//*
					//*													setp 4.3.5：本车优先级 < 邻车优先级：进入===>面对高级车处理逻辑
					//*
					//*********************************************************************************************************************************************************************************************
					//这个是===>亦步亦趋
					else if(priorityCraneVsNeighborCrane==CranePrivilegeInterpreter::COMPARE_RESULT_LOW)
					{
						log.Debug()<<"----------setp 4.3.5：本车优先级 < 邻车优先级：进入===>面对高级车处理逻辑------START------------------------------"<<endl;
						log.Debug()<<"Step 4.3.5：本车的指令优先级 < 邻车的指令优先级 ......"<<endl;
						log.Debug()<<"准备进入 judge_Facing_Auto_Car_High_Level() 过程处理 ......"<<endl;
						retCanMove=judge_Facing_Auto_Car_High_Level(craneNO , currentX , targetX , movingDirection , cranePLCStatusBase, 
																neightborCraneNO,  neightborCranePLCStatusBase,
																canReachX);
						//2018.12.22 zhangyuhong add
						//老曹最新代码
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

		}//自动行车判断结束

		//*********************************************************************************************************************************************************************************************
		//*
		//*													setp 5：根据邻车的运行模式-非自动，进入相应逻辑处理
		//*
		//*********************************************************************************************************************************************************************************************
		//setp 5 前方车辆是手动车
		//前方车辆是手动车  包括手动 遥控 等待等一切状态		
		if(neightborCranePLCStatusBase.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Debug()<<"Step 5：相邻行车的控制模式为  非自动模式  ......准备进入judge_Facing_Manu_Car()处理......"<<endl;
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





 //针对面前是自动车低级别的判断
bool JUDGE_BEFORE_MOVING ::judge_Facing_Auto_Car_Low_Level(string craneNO , long currentX , long targetX , string movingDirection , CranePLCStatusBase  cranePLCStatusBase,
																												 string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase ,
																												 long& canReachX)
{


	string functionName = "JUDGE_BEFORE_MOVING :: judge_Facing_Auto_Car_Low_Level()";
	LOG log(functionName, AUTO_CATCH_PID);

	//假定是不能动车的 
	bool retCanMove=false;
	canReachX=currentX;

	try
	{
					//本车强势，对方弱势，那么试图向前逼近，首先那么获得当前单步的墙壁
					long wallX;
					long wallType;

					//对方车在运动
					bool neighborCarIsMoving=false;
					//对方车在起卷
					bool neighborCarIsLiftCoil=false;
					//对方车在落卷
					bool neighborCarIsDownCoil=false;	
					//对方车在只动小车
					//bool neighborCarIsOnlyYMoving=false;

					//**************************************************************************************************************************************************************
					//*
					//*															1.获取行车状态：停止、起卷、落卷
					//*
					//***************************************************************************************************************************************************************
					//判断大车是否在动  包括大车不动，只动小车这种情况
					if( isACraneStopped(neightborCranePLCStatusBase) == false)
					{
						neighborCarIsMoving = true;
					}

					OrderCurrentBase neighborCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(neightborCraneNO);
					//判断是否在起卷：要么空钩正在下降，要么重钩正在升起					
					if (isACraneLiftCoilDown(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true || 
						isACraneLiftCoilUp(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true)
					{
						neighborCarIsLiftCoil = true;
					}

					//判断是否正在落卷：要么重钩正在下降，要么空钩正在升起
					if (isACraneDownCoilDown(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true || 
						isACraneDownCoilUp(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true)
					{
						neighborCarIsDownCoil = true;
					}

					//判断是否正在只移动小车，大车不动。这种情况其实和起卷/落卷类似，可以获取到静态墙
					/*if (isACraneOnlyYMoving(neightborCranePLCStatusBase) == true)
					{
						neighborCarIsOnlyYMoving = true;
					}*/

					//打印结果
					log.Info()<<"行车目前状态......"<<endl;
					/*log.Info()<<"neighborCarIsMoving = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(neighborCarIsMoving)<<endl;
					log.Info()<<"neighborCarIsLiftCoil = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(neighborCarIsLiftCoil)<<endl;
					log.Info()<<"neighborCarIsDownCoil = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(neighborCarIsDownCoil)<<endl;*/
					//log.Info()<<"neighborCarIsOnlyYMoving = "<<ACTION_COMMON_FUNCTION::TrueOrFlase(neighborCarIsOnlyYMoving)<<endl;


					//**************************************************************************************************************************************************************
					//*
					//*															2.根据行车状态，获取本车可以达到的墙，及墙类型
					//*
					//***************************************************************************************************************************************************************
					if (neighborCarIsMoving == true)
					{
						log.Info()<<"邻车="<<neightborCraneNO<<" 正在大车移动中...可以获取单步墙X"<<endl;
						WALL_SINGLE_STEP::getWall(craneNO, movingDirection, neightborCranePLCStatusBase, wallX, wallType);
					}
					else if (neighborCarIsLiftCoil == true)
					{
						log.Info()<<"邻车="<<neightborCraneNO<<"  正在起卷中....可以获取静态墙X..."<<endl;
						wallType=WALL_SINGLE_STEP::WALL_STATIC;
						wallX=neightborCranePLCStatusBase.getXAct();
					}
					else if(neighborCarIsDownCoil == true)
					{
						log.Info()<<"邻车="<<neightborCraneNO<<"  正在落卷中...可以获取静态墙X..."<<endl;
						wallType=WALL_SINGLE_STEP::WALL_STATIC;
						wallX=neightborCranePLCStatusBase.getXAct();
					}					
					else
					{
						log.Info()<<"邻车="<<neightborCraneNO<<" 目前状态不明..."<<endl;
						retCanMove=false;
						return retCanMove;
					}

					//**************************************************************************************************************************************************************
					//*
					//*															3.根据墙类型，采取不同的动作：静态墙有静态墙的靠近方法，动态墙有动态墙的靠近办法
					//*
					//***************************************************************************************************************************************************************
					//如果是静态的墙壁，那么靠上去
					if(wallType==WALL_SINGLE_STEP::WALL_STATIC)
					{
						retCanMove=CLOSE_TO_STATIC_WALL::closeToWall( craneNO,  movingDirection , currentX, wallX, canReachX);
						return retCanMove;
					}

					//如果是动态墙壁，采用最严格的对动态墙壁的做法
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




//针对面前是自动车高级别的判断
//本车弱势，邻车强势   需要让邻车先行做动作
bool JUDGE_BEFORE_MOVING ::judge_Facing_Auto_Car_High_Level(string craneNO , long currentX , long targetX , string movingDirection , CranePLCStatusBase  cranePLCStatusBase,
																															string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase ,
																															long& canReachX)
{
	string functionName = "JUDGE_BEFORE_MOVING :: judge_Facing_Auto_Car_Hgihg_Level()";
	LOG log(functionName, AUTO_CATCH_PID);

	//假定是不能动车的 假设能去的地方就是原地
	bool retCanMove=false;
	canReachX=currentX;

	try
	{		
						//那么获得整关的墙壁
						long wallX;
						long wallType;

						//2018.12.22 zhangyuhong add
						//老曹最新代码 屏蔽

						/*
						//对方车在运动
						bool neighborCarIsMoving=false;
						//对方车在起卷
						bool neighborCarIsLiftCoil=false;
						//对方车在落卷
						bool neighborCarIsDownCoil=false;
						//对方车在只动小车
						bool neighborCarIsOnlyYMoving=false;

						//**************************************************************************************************************************************************************
						//*
						//*															1.获取邻车状态：停止、起卷、落卷、只小车移动
						//*
						//***************************************************************************************************************************************************************
						log.Debug()<<"1.判断行车状态................."<<endl;
						if( isACraneStopped(neightborCranePLCStatusBase) == true)
						{
							CraneOrderCurrentBase neighborCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(neightborCraneNO);
							//起卷过程
							if (isACraneLiftCoilDown(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true || 
								isACraneLiftCoilUp(neightborCranePLCStatusBase, neighborCraneOrderCurrent) == true)
							{
								neighborCarIsLiftCoil = true;
							}
							//落卷过程
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
						//如果不是停止的，那么就是运动的
						else
						{
							neighborCarIsMoving=true;
						}

						//如果不属于对方在起卷落卷或运动状态，那么对方是一辆最危险的自动静止车，那我车选择不动，两车终会有一个先动因为避让沟通
						if(neighborCarIsMoving==false )
						{
							if(neighborCarIsLiftCoil==true || neighborCarIsDownCoil==true || neighborCarIsOnlyYMoving == true)
							{
							}
							else
							{
								log.Debug()<<"邻车="<<neightborCraneNO<<" 当前状态：大车静止不动，且不是起卷也不是落卷！状态不明，返回false！"<<endl;
								retCanMove=false;	
								return retCanMove;
							}
						}

						*/

						//**************************************************************************************************************************************************************
						//*
						//*															2.根据邻车指令类型进行相应处理
						//*
						//***************************************************************************************************************************************************************
						//避让指令
						if( neightborCranePLCStatusBase.getOrderID() == CraneEvadeRequestBase::ORDER_NO_EVADE )
						{
							log.Debug()<<"邻车="<<neightborCraneNO<<"指令类型 = 避让.......准备获取本车="<<craneNO<<" 的单步墙 WALL_SINGLE_STEP........"<<endl;
							WALL_SINGLE_STEP::getWall(craneNO, movingDirection, neightborCranePLCStatusBase, wallX, wallType);
							retCanMove=CLOSE_TO_DYNAMIC_WALL::closeToWall(craneNO  ,  movingDirection,  targetX  ,  cranePLCStatusBase  ,  neightborCranePLCStatusBase,   canReachX);
							return retCanMove;
						}

						//靠边指令
						if( neightborCranePLCStatusBase.getOrderID() == CraneEvadeRequestBase::ORDER_NO_BOARDING )
						{
							log.Debug()<<"邻车="<<neightborCraneNO<<"指令类型 = 靠边.......准备获取本车="<<craneNO<<" 的单步墙 WALL_SINGLE_STEP........"<<endl;
							WALL_SINGLE_STEP::getWall(craneNO, movingDirection, neightborCranePLCStatusBase, wallX, wallType);
							retCanMove=CLOSE_TO_DYNAMIC_WALL::closeToWall(craneNO  ,  movingDirection,  targetX  ,  cranePLCStatusBase  ,  neightborCranePLCStatusBase,   canReachX);
							return retCanMove;
						}

						//2019.3.6 zhangyuhong add
						//如果是调试画面手自动切换发出的 指令号=999999，或者是行车主操画面发出的手自动切换的指令号=101 则行车都是静止不动的
						//手自动切换指令
						if (neightborCranePLCStatusBase.getOrderID() == CraneEvadeRequestBase::ORDER_NO_MANU_AUTO_SWITCH || 
							neightborCranePLCStatusBase.getOrderID() == CraneEvadeRequestBase::ORDER_NO_MANU_AUTO_SWITCH_TEST)
						{
							log.Debug()<<"邻车="<<neightborCraneNO<<"刚刚进行过手自动切换101或999999，墙类型为静态墙........走靠近静态墙逻辑..."<<endl;
							//wallType=WALL_SINGLE_STEP::WALL_STATIC;
							wallX=neightborCranePLCStatusBase.getXAct();
							retCanMove=CLOSE_TO_STATIC_WALL::closeToWall( craneNO,  movingDirection , currentX, wallX, canReachX);
							return retCanMove;
						}

						//对方行车在运动中并且对方行车在执行WMS指令
						//2019.3.6 zhangyuhong add
						//修改判定是否是WMS指令号的逻辑：5位 且不为 999999的指令号 认为是WMS指令
						//if(neightborCranePLCStatusBase.getOrderID()!=CraneEvadeRequestBase::ORDER_NO_EVADE)
						//WMS指令
						if(neightborCranePLCStatusBase.getOrderID() > 9999 && neightborCranePLCStatusBase.getOrderID() != CraneEvadeRequestBase::ORDER_NO_MANU_AUTO_SWITCH_TEST)
						{
							log.Debug()<<"邻车="<<neightborCraneNO<<"正在执行WMS指令.......准备获取本车="<<craneNO<<" 的整指令墙 WALL_WHOLE_ORDER........"<<endl;
							if(WALL_WHOLE_ORDER::getWall(craneNO, movingDirection, neightborCranePLCStatusBase, wallX, wallType)==false)
							{
								log.Debug()<<"WALL_WHOLE_ORDER::getWall  无法获取到邻车的WMS指令......进程返回false！"<<endl;
								retCanMove=false;
								return retCanMove;
							}

							if(wallType==WALL_SINGLE_STEP::WALL_STATIC   )
							{
								log.Debug()<<"--------------------墙类型为 WALL_STATIC--------------------执行靠近静态墙逻辑-----------------------------"<<endl;
								retCanMove=CLOSE_TO_STATIC_WALL::closeToWall( craneNO,  movingDirection ,currentX, wallX, canReachX);
								return retCanMove;

							}
							else if(wallType==WALL_SINGLE_STEP::WALL_DYNAMIC)
							{
								log.Debug()<<"--------------------墙类型为 WALL_DYNAMIC--------------------执行靠近动态墙逻辑-----------------------------"<<endl;
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






 //针对面前是手动车的判断
bool JUDGE_BEFORE_MOVING ::judge_Facing_Manu_Car(string craneNO , long currentX , long targetX , string movingDirection , CranePLCStatusBase  cranePLCStatusBase,
																							 string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase ,
																							 long& canReachX)
{


	string functionName = "JUDGE_BEFORE_MOVING :: judge_Facing_Manu_Car()";
	LOG log(functionName, AUTO_CATCH_PID);

	//假定是不能动车的 
	bool retCanMove=false;
	canReachX=currentX;

	try
	{
		
		//前方车辆是手动车
		//前方车辆是手动车  包括手动 遥控 等待等一切状态
		if(neightborCranePLCStatusBase.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
					log.Debug()<<"相邻行车的控制状态为 非自动状态........"<<endl;

					log.Debug()<<"检查目标区域是否干净：CONDITION_TARGET_AREA_IS_CLEAN::judge()"<<endl;

					bool ret_Target_Area_Is_Clean=CONDITION_TARGET_AREA_IS_CLEAN::judge(craneNO, movingDirection, currentX, targetX, neightborCranePLCStatusBase);

					log.Debug()<<"检查结果：ret_Target_Area_Is_Clean="<<ret_Target_Area_Is_Clean<<endl;

					//前方是手动车并且区域清空
					//那么以固定步长向前前进
					if(ret_Target_Area_Is_Clean==true)
					{
						log.Debug()<<"我方行车目标区域是 干净的，canReachX值等于targetX值，行车可移动标志retCanMove=true，进程返回true！"<<endl;
						canReachX=targetX;
						log.Debug()<<"canReachX="<<canReachX<<endl;
						retCanMove=true;
						return retCanMove;
					}
					//前方是手动车并且区域不空的情况
					//那么选择不动
					if(ret_Target_Area_Is_Clean==false)
					{
						log.Debug()<<"我方行车目标区域是 不干净的，canReachX值等于currentX值，行车可移动标志retCanMove=false，进程返回false！"<<endl;
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
	//假定是不是静止的 
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
	//假定是不是静止的 
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
	//假定是不是静止的 
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
		//1.如果有避让指令，则避让指令优先级作为指令优先级
		//2.如果没避让指令，则WMS指令优先级作为指令优先级
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

//空钩起卷下降：COIL_UP_PROCESS、空载、夹钳升降负向
bool JUDGE_BEFORE_MOVING ::isACraneLiftCoilDown(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneLiftCoilDown()";
	LOG log(functionName, AUTO_CATCH_PID);
	//假定是不是当前这个状态 
	bool isJustStatus=false;
	try
	{
		//COIL_UP_PROCESS、空载、夹钳升降负向
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

//重钩起卷上升：COIL_UP_PROCESS、重载、夹钳升降正向
bool JUDGE_BEFORE_MOVING ::isACraneLiftCoilUp(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneLiftCoilUp()";
	LOG log(functionName, AUTO_CATCH_PID);
	//假定是不是当前这个状态 
	bool isJustStatus=false;
	try
	{
		//COIL_UP_PROCESS、重载、夹钳升降正向
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

//重钩落卷下降：COIL_DOWN_PROCESS、重载、夹钳升降负向
bool JUDGE_BEFORE_MOVING ::isACraneDownCoilDown(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneDownCoilDown()";
	LOG log(functionName, AUTO_CATCH_PID);
	//假定是不是当前这个状态 
	bool isJustStatus=false;
	try
	{
		//COIL_DOWN_PROCESS、重载、夹钳升降负向
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

//空钩落卷上升：COIL_DOWN_PROCESS、空载、夹钳升降正向
bool JUDGE_BEFORE_MOVING ::isACraneDownCoilUp(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneDownCoilUp()";
	LOG log(functionName, AUTO_CATCH_PID);
	//假定是不是当前这个状态 
	bool isJustStatus=false;
	try
	{
		//COIL_DOWN_PROCESS、空载、夹钳升降正向
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


//大车到位，小车在动
bool JUDGE_BEFORE_MOVING ::isACraneOnlyYMoving(CranePLCStatusBase  cranePLCStatusBase)
{
	string functionName = "JUDGE_BEFORE_MOVING :: isACraneOnlyYMoving()";
	LOG log(functionName, AUTO_CATCH_PID);
	//假定是不是当前这个状态 
	bool isJustStatus=false;

	bool YIsMoving = false;//假设Y没有动
	bool XIsMoving = true;//假设X在动
	try
	{
		//Y的2个方向都有信号
		if ( (cranePLCStatusBase.getYDirectNegative() == 0 &&  cranePLCStatusBase.getYDirectPositive() == 1) || 
			  (cranePLCStatusBase.getYDirectNegative() == 1 && cranePLCStatusBase.getYDirectPositive() == 0) )
		{
			YIsMoving = true;
		}

		//X的2个方向都没信号
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



 //试算：即使对方是高级车，先假设对方是低级车，看是否能先到目标位，能到就 视对方为低级车；不能到，就取消假设
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
		//假设本车高级，对车低级时，如果本车可以开到X目标位，则改变本车从低级变高级
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