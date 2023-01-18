



#pragma once 

#include "EvadeCancelReceiver.h"


using namespace Monitor;



EvadeCancelReceiver:: EvadeCancelReceiver()
{

}

EvadeCancelReceiver:: ~EvadeCancelReceiver()
{

}




void EvadeCancelReceiver ::receive(string myCraneNO, string sender,  string evadeDirection)
{


	string functionName = "EvadeCancelReceiver :: receive()";
	//LOG log(functionName, AUTO_CATCH_PID);

	LOG log(functionName);

	try
	{
		log.Debug()<<"myCraneNO="<<myCraneNO<<"   sender="<<sender<<"   evadeDirection="<<evadeDirection<<endl;

		
		//�ж�evadeDirection�Ƿ�Ϸ�
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
			log.Debug()<<"Ҫ��ȡ���ķ��򲻺Ϸ�������ȡ�������˳���"<<endl;
			return;
		}

		log.Debug()<<"׼����ȡ����="<<myCraneNO<<" ����ָ����е��ӵ�....."<<endl;
		CraneEvadeRequestBase  craneEvadeRequestOld;
		bool ret_DBRead=Adapter_UACS_CRANE_EVADE_REQUEST::GetData(myCraneNO, craneEvadeRequestOld);
		if(ret_DBRead==false)
		{
			log.Debug()<<"�޷���ȡ����= "<<myCraneNO<<" ����ָ����е��ӵ�������ȡ���˳���"<<endl;
			return;
		}

		bool sameSender=false;
		if(craneEvadeRequestOld.getSender()==sender)
		{
			sameSender=true;
		}
		bool sameOrigianlSender=false;
		if(craneEvadeRequestOld.getOriginalSender()==sender)
		{
			sameOrigianlSender=true;
		}
		bool sameDirection=false;
		if(craneEvadeRequestOld.getEvadeDirection()==evadeDirection)
		{
			sameDirection=true;
		}
		/*log.Debug()<<"sameSender="<<ACTION_COMMON_FUNCTION::TrueOrFlase(sameSender)<<endl;
		log.Debug()<<"sameOrigianlSender="<<ACTION_COMMON_FUNCTION::TrueOrFlase(sameOrigianlSender)<<endl;
		log.Debug()<<"sameDirection="<<ACTION_COMMON_FUNCTION::TrueOrFlase(sameDirection)<<endl;*/

		// �յ���ȡ��Ҫ���䷢�����뱾�г�����ָ��ķ����ߣ�����ԭʼ��������ͬ
		//����ȡ��Ҫ������ȷ��ȡ���ı��÷�������뱾�����ڵı���ָ���Ҳ��ͬ
		//��ô����ȡ��������ȡ����������ָ��  ���ۺ�ʱ����״̬
		if (sameSender == true && sameDirection == true)
		{
			log.Debug()<<"����="<<myCraneNO<<" ����ָ����е� Sender �� ָ��ȡ�������� Sender һ�£��� ȡ������һ�£�׼����ձ���ָ���......."<<endl;
			Adapter_UACS_CRANE_EVADE_REQUEST::Init(myCraneNO);
			log.Debug()<<"������...."<<endl;
		}		
		else if (sameOrigianlSender == true && sameDirection == true)
		{
			log.Debug()<<"����="<<myCraneNO<<" ����ָ����е� OrigianlSender �� ָ��ȡ�������� Sender һ�£��� ȡ������һ�£�׼����ձ���ָ���......."<<endl;
			Adapter_UACS_CRANE_EVADE_REQUEST::Init(myCraneNO);
			log.Debug()<<"������...."<<endl;
		}
		else
		{
			log.Debug()<<"����="<<myCraneNO<<" ����Ҫ��ձ���ָ���......"<<endl;
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



bool EvadeCancelReceiver::splitTag_EvadeCancel(string tagVal, string& theSender, string & theEvadeDirection)
{
	string functionName="EvadeCancelReceiver :: splitTag_EvadeCancel()";

	bool ret=true;

	//LOG log(functionName, AUTO_CATCH_PID);

	LOG log(functionName);


	try
	{
	
		log.Debug()<<"......"<<endl;
		log.Debug()<<".......................................................................................splitTag_EvadeCancel................................................................................................................."<<endl;
		log.Debug()<<"......."<<endl;

		log.Debug()<<"tagVal="<<tagVal<<endl;

		vector<string> vectorMessageItems;
		vectorMessageItems= StringHelper::ToVector<string>(tagVal, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

		if(vectorMessageItems.size()<2)
		{
					log.Debug()<<"tagVal data has error format"<<endl;
					return false;
		}
		theSender=vectorMessageItems[0];
		StringHelper::Trim(theSender);

		theEvadeDirection=vectorMessageItems[1];
		StringHelper::Trim(theEvadeDirection);
	

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





