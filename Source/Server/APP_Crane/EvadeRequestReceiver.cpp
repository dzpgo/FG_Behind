
//收到一个避让要求  包括接收行车号  发出行车号   最初发出行车号  避让要求X，避让实际X（等待解析）避让方向，避让动作类型（等待解析）
//解析实际避让X  解析动作类型（立即避让还是关后避让，这依据行车的等级来决定）

//如果我在手动状态，那么我什么也不能做了，不响应任何避让请求
//如果我在自动状态，那么我试图接受这个避让要求




//接受避让动作的过程
//						我原来有压入弹夹的避让指令吗？
//						如果没有，那么我将这发子弹压入弹夹。
//						如果弹夹里面原来有一发字段 那么
//								新的避让指令比老的避让指令等级高，那么用新的避让指令覆盖原来老的避让指令
//								如果新避让指令与老避让指令的方向相同，并且新的避让指令避让的范围更长，那么更新避让指令为新指令



//避让动作的执行
//                     根据弹夹内的子弹情况
//						判断是否触发了禁止避让的条件，如果触发了，那么什么都不做
//						发出本车的避让取消指令（行车号以及避让方向的反方向）					！！！！！！
//						检查是否在避让起步前要先动小车，如果需要，那么指令小车到位
//						试图执行避让指令  首先检查避让方向上是否有前车
//                              试图动车
//								如果不满足动车条件，那么向前车发出避让指令
//                       什么时候把避让指令执行完成  如果已经移动到避让位置那么为true ，如果移动不到呢？？是不是永远关不掉

//什么时候决定做做避让指令，什么时候决定做吊运指令？？
//收下来的避让指令状态为toDO
//指令action的 FINISH_JOB 在起卷完成后会把立即避让指令变更为EXCUTING   落卷完成指令会把 关后执行指令放出为EXCUTING

//mainCycle周期
//发现有避让指令为todo  而没有吊运指令，那么放开避让指令为EXCUTING
//发现有避让指令为EXCUTING的无条件执行
//没有避让指令要执行的 试图执行吊运指令



#pragma once 

#include "EvadeRequestReceiver.h"


using namespace Monitor;



EvadeRequestReceiver:: EvadeRequestReceiver()
{

}

EvadeRequestReceiver:: ~EvadeRequestReceiver()
{

}




void EvadeRequestReceiver ::receive(string craneNO, string sender, string origianlSender,  long evadeXRequest,  string evadeDirection, long evadeRequestOrderNO)
{


	string functionName = "EvadeRequestReceiver :: receive()";
	//LOG log(functionName, AUTO_CATCH_PID);


	//LOG::doConfigure("EvadeRequestReceiver", BRANCH_CONFIG);
	LOG log(__FUNCTION__,"EvadeRequestReceiver");

	//LOG log(functionName);

	try
	{

		log.Debug()<<"craneNO="<<craneNO<<"   sender="<<sender<<"   origianlSender="<<origianlSender<<"   evadeXRequest="<<evadeXRequest<<"   evadeDirection="<<evadeDirection<<"   evadeRequestOrderNO="<<evadeRequestOrderNO<<endl;

		//判断evadeXRequest 是否为空
		if(evadeXRequest<=0)
		{
			log.Debug()<<"请求避让X坐标 <= 0，接收避让请求处理退出！"<<endl;
			return;
		}
		if(evadeXRequest==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"请求避让X坐标 == 999999，接收避让请求处理退出！"<<endl;
			return;
		}
		//判断evadeDirection是否合法
		bool directionWrongDefing=true;
		if(evadeDirection==MOVING_DIR::DIR_X_DES)
		{
			directionWrongDefing=false;
		}
		if(evadeDirection==MOVING_DIR::DIR_X_INC)
		{
			directionWrongDefing=false;
		}
		if(directionWrongDefing==true)
		{
			log.Debug()<<"请求避让方向非法！接收避让请求处理退出！"<<endl;
			return;
		}

		//判断要求的避让方向与本行车可行的避让方向是否相符
		bool leagleDirection=CraneEvadeLimitDefine::isDirectionOK(craneNO,evadeDirection);
		if(leagleDirection==false)
		{
			log.Debug()<<"本车= "<<craneNO<<" 的避让方向= "<<evadeDirection<<" 合法性检查未能通过！接收避让请求处理退出！"<<endl;
			return;
		}
		else
		{
			log.Debug()<<"本车= "<<craneNO<<" 的避让方向= "<<evadeDirection<<" 合法性检查通过！接收避让请求处理继续......"<<endl;
		}

		//获得自身行车的PLC状态
		CranePLCStatusBase  cranePLCStatusBase;
		bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(craneNO, cranePLCStatusBase);
		if(ret_getPLCStatus==false)
		{
				log.Debug()<<"获取本车= "<<craneNO<<" 的PLC状态信息失败......接收避让请求处理退出！"<<endl;
				return ;
		}
		log.Debug()<<"获取本车="<< craneNO<<" 的实时X坐标= "<<cranePLCStatusBase.getXAct()<<endl;

		//解析能够避让的实际X
		log.Debug()<<" 开始计算能够避让的实际X坐标...."<<endl;
		long evadeXAct=CranePLCOrderBase::PLC_INT_NULL;
		
		bool retCalEvadeXAct=CraneEvadeLimitDefine::calEvadeXAct(craneNO , evadeDirection , cranePLCStatusBase.getHasCoil() ,evadeXRequest  ,evadeXAct);
		if(retCalEvadeXAct==false)
		{
			log.Debug()<<"计算能够避让的实际X坐标失败！进程返回！接收避让请求失败！"<<endl;
			return;
		}
		log.Debug()<<"计算出的实际避让X坐标 evadeXAct="<<evadeXAct<<endl;

		//2018.11.30 zhangyuhong add
		//老曹的原先的优先级比较逻辑：直接比较行车本体的优先级
		//暂时屏蔽！
		//解析避让动作是立即避让还是关后避让  这里只将本行车与送信行车进行等级比较，不做本行车与最初送信着之间的等级比较
		/*string compareResult=CranePrivilegeInterpreter::compareByCrane(craneNO,sender);
		log.Debug()<<"比较 本车(接收避让请求) 与 送信车(发送避让请求) 的等级高低 ="<<compareResult<<endl;*/

		//2018.11.30 zhangyuhong add
		//启用指令优先级比较
		//string compareResult = CranePrivilegeInterpreter::VSByOrderWhenEvade(craneNO, cranePLCStatusBase, sender, evadeRequestOrderNO);


		//暴力一点，直接用行车本体优先级作为判断依据，特例放在行车主线程上层代码里
		string compareResult = CranePrivilegeInterpreter::compareByCrane(craneNO, sender);
		log.Debug()<<"比较 本车(接收避让请求) ="<<craneNO<<"  与   送信车(发送避让请求)="<<sender<<" 的等级高低 为"<<compareResult<<endl;
		


		//避让动作类型，先赋值为保守的关后避让
		log.Debug()<<"开始设定避让动作...."<<endl;
		string actionType=CraneEvadeRequestBase::TYPE_AFTER_JOB;
		if(compareResult==CranePrivilegeInterpreter::COMPARE_RESULT_HIGH)
		{
			//我比请求者高，那么我就用关后避让的傲慢模式
			log.Debug()<<"本车 比 送信车 等级高....采用关后避让......TYPE_AFTER_JOB......"<<endl;
			actionType=CraneEvadeRequestBase::TYPE_AFTER_JOB;
		}
		else if(compareResult==CranePrivilegeInterpreter::COMPARE_RESULT_LOW)
		{
			//我比请求者底，那么我就用立即避让的殷切模式
			log.Debug()<<"本车 比 送信车 等级低....采用立即避让......TYPE_RIGHT_NOW......"<<endl;
			actionType=CraneEvadeRequestBase::TYPE_RIGHT_NOW;
		}
		else 
		{
			log.Debug()<<"本车 与 送信车 等级比较结果非法！等级比较失败！进程返回！避让接收失败！"<<endl;
			return;
		}
		log.Debug()<<"因此避让动作 actionType="<<actionType<<endl;

		//设置避让指令优先级
		//double evadePriority = ACTION_COMMON_FUNCTION::getEvadePriority(sender, evadeRequestOrderNO);
		double evadePriority = 99;


		//如果行车目前不在自动状态，那么不接收任何避让要求，退出
		if(cranePLCStatusBase.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Debug()<<"本车="<<craneNO<<" 处于 非自动 模式！！进程退出！不再接收任何避让要求！！"<<endl;
			return;
		}

		//以下本行车是在自动状态
		log.Debug()<<"本车="<<craneNO<<" 处于 自动模式！准备避让指令表的相关数据，并进行写表......"<<endl;
		CraneEvadeRequestBase  craneEvadeRequestNew;
		craneEvadeRequestNew.setTargetCraneNO(craneNO);
		craneEvadeRequestNew.setSender(sender);
		craneEvadeRequestNew.setOriginalSender(origianlSender);
		craneEvadeRequestNew.setEvadeXRequest(evadeXRequest);
		craneEvadeRequestNew.setEvadeX(evadeXAct);
		craneEvadeRequestNew.setEvadeDirection(evadeDirection);
		craneEvadeRequestNew.setEvadeActionType(actionType);
		craneEvadeRequestNew.setStatus(CraneEvadeRequestBase::STATUS_INIT);
		craneEvadeRequestNew.setPriority(evadePriority);			//2018.11.30 zhangyuhong add 新增避让指令优先级设置
		craneEvadeRequestNew.logOutValues();

		//首先确认避让指令弹夹中的情况
		//分为三种情况  弹夹为空  状态为empty  或者Finished
		//								 弹夹中有一发待发子弹  状态为todo
		//								 弹夹中有一发正在执行的子弹  EXCUTING
		//如果弹夹为空，那么直接压入子弹
		//如果弹夹内子弹正在执行，那么退出，不做任何处理
		//如果弹夹内有一发待发子弹
		//					如果旧避让指令的等级低于新避让指令，那么用新指令覆盖老指令
		//					如果旧避让指令的等级与新避让指令的等级相同，且方向相同
		//									如果是大方向避让 新指令避让要求X更大，那么新指令覆盖老指令
		//									如果是小方向避让 新指令避让要求X更小，那么新指令覆盖老指令
	
		log.Debug()<<"避让指令数据准备完毕！写入前，先要读取避让指令表中现有指令子弹......"<<endl;
		CraneEvadeRequestBase  craneEvadeRequestOld;
		bool ret_DBRead=Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO, craneEvadeRequestOld);
		if(ret_DBRead==false)
		{
			log.Debug()<<"本车= "<<craneNO<<"  的相关避让指令记录读取失败！进程退出！接收避让请求失败！"<<endl;
			return;
		}

		//***********************************************************************************************************
		//*
		//*						情况1. 弹夹内没有避让子弹：
		//*									STATUS_EMPTY、STATUS_FINISHED
		//*
		//***********************************************************************************************************
		bool noBullet=false;
		if(craneEvadeRequestOld.getStatus() ==CraneEvadeRequestBase::STATUS_EMPTY)
		{
			noBullet=true;
		}
		if(craneEvadeRequestOld.getStatus() ==CraneEvadeRequestBase::STATUS_FINISHED)
		{
			noBullet=true;
		}

		if(noBullet==true)
		{
			log.Debug()<<"本车="<<craneNO<<" 的避让指令表中没有避让指令子弹：STATUS_EMPTY或STATUS_FINISHED！可以直接压入新的避让指令子弹！"<<endl;
			Adapter_UACS_CRANE_EVADE_REQUEST::Update(craneEvadeRequestNew);
			log.Debug()<<"新的避让子弹上膛成功！"<<endl;
		}

		//***********************************************************************************************************
		//*
		//*						情况2. 弹夹内有子弹，并且正在处理，那么什么也不做退出程序：
		//*									STATUS_EXCUTING
		//*
		//***********************************************************************************************************
		if(craneEvadeRequestOld.getStatus()==CraneEvadeRequestBase::STATUS_EXCUTING)
		{
			log.Debug()<<"本车="<<craneNO<<" 弹夹中避让子弹正在执行中：STATUS_EXCUTING！不能压入新的避让子弹！进程退出！接收避让请求失败！"<<endl;
			return;
		}

		//***********************************************************************************************************
		//*
		//*						情况3. 弹夹内有子弹，弹夹内有子弹，是等待处理的状态:
		//*									STATUS_INIT、STATUS_TO_DO
		//*
		//***********************************************************************************************************
		if(craneEvadeRequestOld.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
		{
						log.Debug()<<"本车="<<craneNO<<" 弹夹中避让子弹创建初始化或准备要做：STATUS_INIT 或 STATUS_TO_DO！"<<endl;
						//如果新指令的等级高于老指令的等级，那么覆盖
						if(craneEvadeRequestNew.getEvadeActionType()==CraneEvadeRequestBase::TYPE_RIGHT_NOW)
						{
									if(craneEvadeRequestOld.getEvadeActionType()==CraneEvadeRequestBase::TYPE_AFTER_JOB)
									{
											log.Debug()<<"本车="<<craneNO<<" 弹夹中避让子弹类型=AFTER_JOB，新的避让子弹类型=RIGHT_NOW！新的避让子弹覆盖弹夹中子弹！"<<endl;
											Adapter_UACS_CRANE_EVADE_REQUEST::Update(craneEvadeRequestNew);
											log.Debug()<<"新的避让子弹上膛成功！"<<endl;
									}
						}

						//如果新指令的动作等级与老指令的等级相同，且方向也相同
						if(craneEvadeRequestNew.getEvadeActionType()==craneEvadeRequestOld.getEvadeActionType())
						{
									log.Debug()<<"本车="<<craneNO<<" 弹夹中避让子弹类型="<<craneEvadeRequestOld.getEvadeActionType()<<"，新的避让子弹类型="<<craneEvadeRequestNew.getEvadeActionType()<<endl;
									log.Debug()<<"新旧避让子弹类型一致！"<<endl;

									if(craneEvadeRequestNew.getEvadeDirection()==craneEvadeRequestOld.getEvadeDirection())
									{
											log.Debug()<<"本车="<<craneNO<<" 弹夹中避让子弹方向="<<craneEvadeRequestOld.getEvadeDirection()<<"，新的避让子弹方向="<<craneEvadeRequestNew.getEvadeDirection()<<endl;
											log.Debug()<<"新旧避让子弹方向一致！"<<endl;
											//新旧避让指令动作类型相同，且都是大方向避让指令
											if(craneEvadeRequestNew.getEvadeDirection()==MOVING_DIR::DIR_X_INC)
											{
												if(craneEvadeRequestNew.getEvadeX()>craneEvadeRequestOld.getEvadeX())
												{
														log.Debug()<<"新旧避让子弹方向均是 X_INC！新避让子弹实际避让X坐标 > 旧避让子弹实际避让X坐标 ！新的避让子弹覆盖弹夹中子弹！"<<endl;
														Adapter_UACS_CRANE_EVADE_REQUEST::Update(craneEvadeRequestNew);
														log.Debug()<<"新的避让子弹上膛成功！"<<endl;
												}
											}
											//新旧避让指令动作类型相同，且都是小方向避让指令
											if(craneEvadeRequestNew.getEvadeDirection()==MOVING_DIR::DIR_X_DES)
											{
													if(craneEvadeRequestNew.getEvadeX()<craneEvadeRequestOld.getEvadeX())
													{
															log.Debug()<<"新旧避让子弹方向均是 X_DES！新避让子弹实际避让X坐标 < 旧避让子弹实际避让X坐标 ！新的避让子弹覆盖弹夹中子弹！"<<endl;
															Adapter_UACS_CRANE_EVADE_REQUEST::Update(craneEvadeRequestNew);
															log.Debug()<<"新的避让子弹上膛成功！"<<endl;
													}
											}

									}
						}

						log.Debug()<<"接收避让请求逻辑处理最后：弹夹中有一条TO_DO的避让子弹，新的避让子弹不能压入弹夹！"<<endl;
						log.Debug()<<"this print means there is a bullet with status TO_DO and new evade request can not update it"<<endl;
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

}



bool EvadeRequestReceiver::splitTag_EvadeRequest(string tagVal, string& theCraneNO, string& theSender, string& theOrigianlSender, long& theEvadeXRequest, string & theEvadeDirection, long & theEvadeRequestOrderNO)
{
	string functionName="CraneEvadeLimitDefine :: splitTag_EvadeRequest()";

	bool ret=true;

	//LOG log(functionName, AUTO_CATCH_PID);

	LOG log(functionName);


	try
	{
	
		log.Debug()<<"......"<<endl;
		log.Debug()<<".......................................................................................splitTag_EvadeRequest................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;

		log.Debug()<<"tagVal="<<tagVal<<endl;

		vector<string> vectorMessageItems;
		vectorMessageItems= StringHelper::ToVector<string>(tagVal, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

		if(vectorMessageItems.size()<6)
		{
					log.Debug()<<"tagVal data has error format"<<endl;
					return false;
		}
		theCraneNO=vectorMessageItems[0];
		StringHelper::Trim(theCraneNO);

		theSender=vectorMessageItems[1];
		StringHelper::Trim(theSender);
	
		theOrigianlSender=vectorMessageItems[2];
		StringHelper::Trim(theOrigianlSender);

		theEvadeXRequest=StringHelper::ToNumber<long>(vectorMessageItems[3]);

		theEvadeDirection=vectorMessageItems[4];
		StringHelper::Trim(theEvadeDirection);

		theEvadeRequestOrderNO = StringHelper::ToNumber<long>(vectorMessageItems[5]);

		ret=true;
		return ret;





	}
	catch(iDA::Exception &x)
	{
		ret=false;
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
		ret=false;
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





