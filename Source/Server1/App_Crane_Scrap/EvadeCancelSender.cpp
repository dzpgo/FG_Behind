



#pragma once 

#include "EvadeCancelSender.h"


using namespace Monitor;



EvadeCancelSender:: EvadeCancelSender()
{

}

EvadeCancelSender:: ~EvadeCancelSender()
{

}




void EvadeCancelSender ::senderByMovingAction(string sender,  long currentX,  long targetX)
{


	string functionName = "EvadeCancelSender :: senderByMovingAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	//LOG log(functionName);

	try
	{
		log.Debug()<<"sender="<<sender<<"   currentX="<<currentX<<"   targetX="<<targetX<<endl;
		
		//����г�Ҫ���еķ���
		string movingDirection=MOVING_DIR::getDirection(sender, currentX, targetX);
		
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
			log.Debug()<<"wrong direction format the process will stop and return"<<endl;
			return;
		}

		//ȡ�÷�����
		string oppositeDirection;
		if(movingDirection==MOVING_DIR::DIR_X_DES) //��С�˶�
		{
			oppositeDirection=MOVING_DIR::DIR_X_INC;  //����Ϊ���
		}
		if(movingDirection==MOVING_DIR::DIR_X_INC)  //����˶�
		{
			oppositeDirection=MOVING_DIR::DIR_X_DES;  //����Ϊ��С
		}

		//�����÷����ϵģ����г��ı���Ҫ��ȡ��ָ��
		wirteEvadeCancelTag(sender, oppositeDirection);


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





void EvadeCancelSender ::senderByManuAutoSwitch(string sender)
{


	string functionName = "EvadeCancelSender :: senderByMovingAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	//LOG log(functionName);

	try
	{
		log.Debug()<<"sender="<<sender<<endl;
		

		//�������г��ı���Ҫ��ȡ��ָ�˫��ȡ��
		wirteEvadeCancelTag(sender, MOVING_DIR::DIR_X_DES);
		wirteEvadeCancelTag(sender, MOVING_DIR::DIR_X_INC);


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



bool EvadeCancelSender:: wirteEvadeCancelTag( string theSender, string  theCancelDirection)
{
	string functionName="EvadeCancelSender :: wirteEvadeCancel()";

	bool ret=true;

	LOG log(functionName, AUTO_CATCH_PID);

	//LOG log(functionName);


	try
	{
	
		iPlature::TAGVALUEMAP tagPairs;
		
		//theSender
		string tagValue=theSender+",";

		//theCancelDirection
		tagValue+=theCancelDirection;

		string tagName=Evade_Tag_Define::getTagName_Evade_Cancel(theSender);

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





