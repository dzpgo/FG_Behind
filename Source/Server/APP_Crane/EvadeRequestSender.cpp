#include "EvadeRequestSender.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;


const long EvadeRequestSender::MaxCount=30;

EvadeRequestSender*  EvadeRequestSender::m_pEvadeRequestSender = NULL;

EvadeRequestSender::EvadeRequestSender() 
{
	orderNO_LastSentOut=DB_INT_NULL;
	evadeXRequest_LastSentOut=DB_INT_NULL;
	count=0;

}


EvadeRequestSender :: ~EvadeRequestSender(void)
{
	
	delete m_pEvadeRequestSender;


}

 EvadeRequestSender* EvadeRequestSender::getInstance(void)
{
	if (m_pEvadeRequestSender == NULL)
	{
		m_pEvadeRequestSender = new EvadeRequestSender;
	}
	return m_pEvadeRequestSender;
}



void EvadeRequestSender ::senderByMovingAction(string craneNO, long orderNO, long currentX,  long targetX)//走行行车行车号，即发出者
{
	string functionName = "EvadeRequestSender :: senderByMovingAction()";
	//LOG log(functionName, AUTO_CATCH_PID);
	LOG log(functionName);

	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"   currentX="<<currentX<<"   targetX="<<targetX<<endl;		

		//**********************************************************************************************************************************
		//*
		//*						1、判断行车方向是否合法
		//*
		//***********************************************************************************************************************************
		//获得行车要走行的方向
		string movingDirection=MOVING_DIR::getDirection(craneNO, currentX, targetX);		
		log.Debug()<<"movingDirection="<<movingDirection<<endl;

		//判断movingDirection是否合法
		bool directionWrongDefing=true;
		if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			directionWrongDefing=false;
		}
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			directionWrongDefing=false;
		}
		if(directionWrongDefing==true)
		{
			log.Debug()<<"行车方向不合法！处理退出！发送避让请求失败！"<<endl;
			return;
		}

		//**********************************************************************************************************************************
		//*
		//*						2、判断本车方向上的邻车号
		//*
		//***********************************************************************************************************************************
		string neightborCraneNO=NEIGHBOR_AHEAD::getCraneNO(craneNO,movingDirection);
		log.Debug()<<"本车="<<craneNO<<" 方向上的邻车="<<neightborCraneNO<<endl;
		
		//前方无行车，则不需要进行下一步判断了，返回true，行车走行交给安全区
		if(neightborCraneNO==NEIGHBOR_AHEAD::NOBODY)
		{
			log.Debug()<<"邻车==NOBODY  处理中断返回！ "<<endl;
			return ;
		}

		//行车号不明，说明判别行车号失败了，那么无条件范围false
		if(neightborCraneNO==NEIGHBOR_AHEAD::UNKNOW)
		{
			log.Debug()<<"邻车==UNKNOW 处理中断返回！ "<<endl;
			return ;
		}

		//**********************************************************************************************************************************
		//*
		//*						3、判断这个避让要求是出自一个WMS指令还是出自一个避让指令
		//*							  判断目的：如果是避让指令，是为了得到原始发出者：origianlSender
		//*												 如果是WMS指令，则原始发出者不存在，即 DB_STR_NULL
		//*
		//***********************************************************************************************************************************
		//获得origianlSender，为后面组织数据做准备
		string origianlSender=DB_STR_NULL;//避让请求原始发出者

		//判断这个避让要求是出自指令是一个WMS指令还是出自一个避让指令
		if(orderNO==CraneEvadeRequestBase::ORDER_NO_EVADE)
		{
				log.Debug()<<"本次发出请求避让的行车正在做避让指令.....读取本车的避让指令表中的数据....."<<endl;
				CraneEvadeRequestBase  craneEvadeRequest;
				bool ret_DBRead=Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO, craneEvadeRequest);
				//if(ret_DBRead==false)
				if(ret_DBRead==true)
				{
					//2018.10.19 zhangyuhong add
					//应该是本车的 Sender 作为邻车的 origianlSender
					//origianlSender=craneEvadeRequest.getOriginalSender();
					origianlSender=craneEvadeRequest.getSender();
				}
		}
	
		long evadeXRequest;
		// (-)-------crane-------targetX-------neighborCrane--->(+)
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			evadeXRequest=targetX  +  
									   RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES   +  
									   RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE ;
		}
		// (-)<---neighborCrane----targetX--------crane-----(+)
		if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
				evadeXRequest=targetX  -  
									   RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES   -  
									   RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE ;
		}
		
		//对方行车是否在自动状态下
		log.Debug()<<"准备获取邻车="<<neightborCraneNO<<" 的实时状态  neightborCranePLCStatusBase ....."<<endl;
		CranePLCStatusBase  neightborCranePLCStatusBase;
		bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(neightborCraneNO, neightborCranePLCStatusBase);
		if(ret_getPLCStatus==false)
		{
				log.Debug()<<"获取邻车="<<neightborCraneNO<<" 的实时状态  neightborCranePLCStatusBase ....失败！发送避让请求失败！进程返回！ "<<endl;
				return ;
		}
		log.Debug()<<"邻车="<<neightborCraneNO<<" 的 XAct="<<neightborCranePLCStatusBase.getXAct()<<endl;

		//以下是特殊工况下，不发避让请求
		if (true == EvadeRequestSenderException::satifyException(craneNO, neightborCraneNO, movingDirection))
		{
			log.Debug()<<"有特殊工况存在！不发送避让请求！返回！"<<endl;
			return;
		}


		//如果是在自动，那么发出避让请求
		if(neightborCranePLCStatusBase.getControlMode()==CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			//上次发出的避让要求，其指令号与本次不同或者 上次的避让位置与本次不同
			if(orderNO_LastSentOut!=orderNO  ||  evadeXRequest_LastSentOut!=evadeXRequest)
			{
				//发出避让请求
				wirteEvadeRequestTag(neightborCraneNO, craneNO, origianlSender , evadeXRequest, movingDirection, orderNO);
				count=0;
				//更新值
				orderNO_LastSentOut=orderNO;
				evadeXRequest_LastSentOut=evadeXRequest;
			}
			//上次发出的避让要求和本次是相同的，那么间隔一定周期之后再发送
			else
			{
					count++;
					if(count>=EvadeRequestSender::MaxCount)
					{
						//发出避让请求
						wirteEvadeRequestTag(neightborCraneNO, craneNO, origianlSender , evadeXRequest, movingDirection, orderNO);
						count=0;
						//更新值
						orderNO_LastSentOut=orderNO;
						evadeXRequest_LastSentOut=evadeXRequest;
					}
			}
		}
		return;
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




void EvadeRequestSender ::reset()
{


	string functionName = "EvadeRequestSender :: reset()";
	//LOG log(functionName, AUTO_CATCH_PID);

	LOG log(functionName);

	try
	{
		orderNO_LastSentOut=DB_INT_NULL;
		evadeXRequest_LastSentOut=DB_INT_NULL;
		count=0;


		return;
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












bool EvadeRequestSender:: wirteEvadeRequestTag(string targetCraneNO, string theSender, string origianlSender , long evadeXRequest, string  evadeDirection, long evadeRequestOrderNO)
{
	string functionName="EvadeRequestSender :: wirteEvadeRequestTag()";

	bool ret=true;

	//LOG log(functionName, AUTO_CATCH_PID);

	LOG log(functionName);


	try
	{
	
		iPlature::TAGVALUEMAP tagPairs;
		
		//targetCraneNO
		string tagValue=targetCraneNO+",";

		//theSender
		tagValue+=theSender+",";

		//origianlSender
		tagValue+=origianlSender+",";

		//evadeXRequest
		tagValue+=StringHelper::ToString(evadeXRequest)+",";

		//evadeDirection
		tagValue+=evadeDirection + ",";

		//2018.11.29 zhangyuhong add
		tagValue += StringHelper::ToString(evadeRequestOrderNO);

		string tagName=Evade_Tag_Define::getTagName_Evade_Request(theSender);

		log.Debug()<<"eventPut tagName="<<tagName<<"    tagValue="<<tagValue<<endl;

		Tag::GetInst().EventPut(tagPairs,tagName,tagValue);
			
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





