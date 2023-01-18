



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
			log.Debug()<<"要求取消的方向不合法，避让取消处理退出！"<<endl;
			return;
		}

		log.Debug()<<"准备读取本车="<<myCraneNO<<" 避让指令表中的子弹....."<<endl;
		CraneEvadeRequestBase  craneEvadeRequestOld;
		bool ret_DBRead=Adapter_UACS_CRANE_EVADE_REQUEST::GetData(myCraneNO, craneEvadeRequestOld);
		if(ret_DBRead==false)
		{
			log.Debug()<<"无法读取本车= "<<myCraneNO<<" 避让指令表中的子弹！避让取消退出！"<<endl;
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

		// 收到的取消要求，其发送者与本行车避让指令的发送者，或者原始发送者相同
		//并且取消要求中明确了取消的避让方向，如果与本车现在的避让指令方向也相同
		//那么满足取消条件，取消本车避让指令  不论何时何种状态
		if (sameSender == true && sameDirection == true)
		{
			log.Debug()<<"本车="<<myCraneNO<<" 避让指令表中的 Sender 和 指令取消发起者 Sender 一致，且 取消方向一致，准备清空避让指令表......."<<endl;
			Adapter_UACS_CRANE_EVADE_REQUEST::Init(myCraneNO);
			log.Debug()<<"清空完毕...."<<endl;
		}		
		else if (sameOrigianlSender == true && sameDirection == true)
		{
			log.Debug()<<"本车="<<myCraneNO<<" 避让指令表中的 OrigianlSender 和 指令取消发起者 Sender 一致，且 取消方向一致，准备清空避让指令表......."<<endl;
			Adapter_UACS_CRANE_EVADE_REQUEST::Init(myCraneNO);
			log.Debug()<<"清空完毕...."<<endl;
		}
		else
		{
			log.Debug()<<"本车="<<myCraneNO<<" 不需要清空避让指令表......"<<endl;
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





