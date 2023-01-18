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



void EvadeRequestSender ::senderByMovingAction(string craneNO, long orderNO, long currentX,  long targetX)//�����г��г��ţ���������
{
	string functionName = "EvadeRequestSender :: senderByMovingAction()";
	//LOG log(functionName, AUTO_CATCH_PID);
	LOG log(functionName);

	try
	{
		log.Debug()<<"craneNO="<<craneNO<<"   currentX="<<currentX<<"   targetX="<<targetX<<endl;		

		//**********************************************************************************************************************************
		//*
		//*						1���ж��г������Ƿ�Ϸ�
		//*
		//***********************************************************************************************************************************
		//����г�Ҫ���еķ���
		string movingDirection=MOVING_DIR::getDirection(craneNO, currentX, targetX);		
		log.Debug()<<"movingDirection="<<movingDirection<<endl;

		//�ж�movingDirection�Ƿ�Ϸ�
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
			log.Debug()<<"�г����򲻺Ϸ��������˳������ͱ�������ʧ�ܣ�"<<endl;
			return;
		}

		//**********************************************************************************************************************************
		//*
		//*						2���жϱ��������ϵ��ڳ���
		//*
		//***********************************************************************************************************************************
		string neightborCraneNO=NEIGHBOR_AHEAD::getCraneNO(craneNO,movingDirection);
		log.Debug()<<"����="<<craneNO<<" �����ϵ��ڳ�="<<neightborCraneNO<<endl;
		
		//ǰ�����г�������Ҫ������һ���ж��ˣ�����true���г����н�����ȫ��
		if(neightborCraneNO==NEIGHBOR_AHEAD::NOBODY)
		{
			log.Debug()<<"�ڳ�==NOBODY  �����жϷ��أ� "<<endl;
			return ;
		}

		//�г��Ų�����˵���б��г���ʧ���ˣ���ô��������Χfalse
		if(neightborCraneNO==NEIGHBOR_AHEAD::UNKNOW)
		{
			log.Debug()<<"�ڳ�==UNKNOW �����жϷ��أ� "<<endl;
			return ;
		}

		//**********************************************************************************************************************************
		//*
		//*						3���ж��������Ҫ���ǳ���һ��WMSָ��ǳ���һ������ָ��
		//*							  �ж�Ŀ�ģ�����Ǳ���ָ���Ϊ�˵õ�ԭʼ�����ߣ�origianlSender
		//*												 �����WMSָ���ԭʼ�����߲����ڣ��� DB_STR_NULL
		//*
		//***********************************************************************************************************************************
		//���origianlSender��Ϊ������֯������׼��
		string origianlSender=DB_STR_NULL;//��������ԭʼ������

		//�ж��������Ҫ���ǳ���ָ����һ��WMSָ��ǳ���һ������ָ��
		if(orderNO==CraneEvadeRequestBase::ORDER_NO_EVADE)
		{
				log.Debug()<<"���η���������õ��г�����������ָ��.....��ȡ�����ı���ָ����е�����....."<<endl;
				CraneEvadeRequestBase  craneEvadeRequest;
				bool ret_DBRead=Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO, craneEvadeRequest);
				//if(ret_DBRead==false)
				if(ret_DBRead==true)
				{
					//2018.10.19 zhangyuhong add
					//Ӧ���Ǳ����� Sender ��Ϊ�ڳ��� origianlSender
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
		
		//�Է��г��Ƿ����Զ�״̬��
		log.Debug()<<"׼����ȡ�ڳ�="<<neightborCraneNO<<" ��ʵʱ״̬  neightborCranePLCStatusBase ....."<<endl;
		CranePLCStatusBase  neightborCranePLCStatusBase;
		bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(neightborCraneNO, neightborCranePLCStatusBase);
		if(ret_getPLCStatus==false)
		{
				log.Debug()<<"��ȡ�ڳ�="<<neightborCraneNO<<" ��ʵʱ״̬  neightborCranePLCStatusBase ....ʧ�ܣ����ͱ�������ʧ�ܣ����̷��أ� "<<endl;
				return ;
		}
		log.Debug()<<"�ڳ�="<<neightborCraneNO<<" �� XAct="<<neightborCranePLCStatusBase.getXAct()<<endl;

		//���������⹤���£�������������
		if (true == EvadeRequestSenderException::satifyException(craneNO, neightborCraneNO, movingDirection))
		{
			log.Debug()<<"�����⹤�����ڣ������ͱ������󣡷��أ�"<<endl;
			return;
		}


		//��������Զ�����ô������������
		if(neightborCranePLCStatusBase.getControlMode()==CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			//�ϴη����ı���Ҫ����ָ����뱾�β�ͬ���� �ϴεı���λ���뱾�β�ͬ
			if(orderNO_LastSentOut!=orderNO  ||  evadeXRequest_LastSentOut!=evadeXRequest)
			{
				//������������
				wirteEvadeRequestTag(neightborCraneNO, craneNO, origianlSender , evadeXRequest, movingDirection, orderNO);
				count=0;
				//����ֵ
				orderNO_LastSentOut=orderNO;
				evadeXRequest_LastSentOut=evadeXRequest;
			}
			//�ϴη����ı���Ҫ��ͱ�������ͬ�ģ���ô���һ������֮���ٷ���
			else
			{
					count++;
					if(count>=EvadeRequestSender::MaxCount)
					{
						//������������
						wirteEvadeRequestTag(neightborCraneNO, craneNO, origianlSender , evadeXRequest, movingDirection, orderNO);
						count=0;
						//����ֵ
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





