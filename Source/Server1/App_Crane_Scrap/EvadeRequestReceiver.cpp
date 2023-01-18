
//�յ�һ������Ҫ��  ���������г���  �����г���   ��������г���  ����Ҫ��X������ʵ��X���ȴ����������÷��򣬱��ö������ͣ��ȴ�������
//����ʵ�ʱ���X  �����������ͣ��������û��ǹغ���ã��������г��ĵȼ���������

//��������ֶ�״̬����ô��ʲôҲ�������ˣ�����Ӧ�κα�������
//��������Զ�״̬����ô����ͼ�����������Ҫ��




//���ܱ��ö����Ĺ���
//						��ԭ����ѹ�뵯�еı���ָ����
//						���û�У���ô�ҽ��ⷢ�ӵ�ѹ�뵯�С�
//						�����������ԭ����һ���ֶ� ��ô
//								�µı���ָ����ϵı���ָ��ȼ��ߣ���ô���µı���ָ���ԭ���ϵı���ָ��
//								����±���ָ�����ϱ���ָ��ķ�����ͬ�������µı���ָ����õķ�Χ��������ô���±���ָ��Ϊ��ָ��



//���ö�����ִ��
//                     ���ݵ����ڵ��ӵ����
//						�ж��Ƿ񴥷��˽�ֹ���õ���������������ˣ���ôʲô������
//						���������ı���ȡ��ָ��г����Լ����÷���ķ�����					������������
//						����Ƿ��ڱ�����ǰҪ�ȶ�С���������Ҫ����ôָ��С����λ
//						��ͼִ�б���ָ��  ���ȼ����÷������Ƿ���ǰ��
//                              ��ͼ����
//								��������㶯����������ô��ǰ����������ָ��
//                       ʲôʱ��ѱ���ָ��ִ�����  ����Ѿ��ƶ�������λ����ôΪtrue ������ƶ������أ����ǲ�����Զ�ز���

//ʲôʱ�������������ָ�ʲôʱ�����������ָ���
//�������ı���ָ��״̬ΪtoDO
//ָ��action�� FINISH_JOB �������ɺ�����������ָ����ΪEXCUTING   ������ָ���� �غ�ִ��ָ��ų�ΪEXCUTING

//mainCycle����
//�����б���ָ��Ϊtodo  ��û�е���ָ���ô�ſ�����ָ��ΪEXCUTING
//�����б���ָ��ΪEXCUTING��������ִ��
//û�б���ָ��Ҫִ�е� ��ͼִ�е���ָ��



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

		//�ж�evadeXRequest �Ƿ�Ϊ��
		if(evadeXRequest<=0)
		{
			log.Debug()<<"�������X���� <= 0�����ձ����������˳���"<<endl;
			return;
		}
		if(evadeXRequest==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"�������X���� == 999999�����ձ����������˳���"<<endl;
			return;
		}
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
			log.Debug()<<"������÷���Ƿ������ձ����������˳���"<<endl;
			return;
		}

		//�ж�Ҫ��ı��÷����뱾�г����еı��÷����Ƿ����
		bool leagleDirection=CraneEvadeLimitDefine::isDirectionOK(craneNO,evadeDirection);
		if(leagleDirection==false)
		{
			log.Debug()<<"����= "<<craneNO<<" �ı��÷���= "<<evadeDirection<<" �Ϸ��Լ��δ��ͨ�������ձ����������˳���"<<endl;
			return;
		}
		else
		{
			log.Debug()<<"����= "<<craneNO<<" �ı��÷���= "<<evadeDirection<<" �Ϸ��Լ��ͨ�������ձ������������......"<<endl;
		}

		//��������г���PLC״̬
		CranePLCStatusBase  cranePLCStatusBase;
		bool ret_getPLCStatus=CraneMonitor::getInstance()->getNeighborPLCStatus(craneNO, cranePLCStatusBase);
		if(ret_getPLCStatus==false)
		{
				log.Debug()<<"��ȡ����= "<<craneNO<<" ��PLC״̬��Ϣʧ��......���ձ����������˳���"<<endl;
				return ;
		}
		log.Debug()<<"��ȡ����="<< craneNO<<" ��ʵʱX����= "<<cranePLCStatusBase.getXAct()<<endl;

		//�����ܹ����õ�ʵ��X
		log.Debug()<<" ��ʼ�����ܹ����õ�ʵ��X����...."<<endl;
		long evadeXAct=CranePLCOrderBase::PLC_INT_NULL;
		
		bool retCalEvadeXAct=CraneEvadeLimitDefine::calEvadeXAct(craneNO , evadeDirection , cranePLCStatusBase.getHasCoil() ,evadeXRequest  ,evadeXAct);
		if(retCalEvadeXAct==false)
		{
			log.Debug()<<"�����ܹ����õ�ʵ��X����ʧ�ܣ����̷��أ����ձ�������ʧ�ܣ�"<<endl;
			return;
		}
		log.Debug()<<"�������ʵ�ʱ���X���� evadeXAct="<<evadeXAct<<endl;

		//2018.11.30 zhangyuhong add
		//�ϲܵ�ԭ�ȵ����ȼ��Ƚ��߼���ֱ�ӱȽ��г���������ȼ�
		//��ʱ���Σ�
		//�������ö������������û��ǹغ����  ����ֻ�����г��������г����еȼ��Ƚϣ��������г������������֮��ĵȼ��Ƚ�
		/*string compareResult=CranePrivilegeInterpreter::compareByCrane(craneNO,sender);
		log.Debug()<<"�Ƚ� ����(���ձ�������) �� ���ų�(���ͱ�������) �ĵȼ��ߵ� ="<<compareResult<<endl;*/

		//2018.11.30 zhangyuhong add
		//����ָ�����ȼ��Ƚ�
		//string compareResult = CranePrivilegeInterpreter::VSByOrderWhenEvade(craneNO, cranePLCStatusBase, sender, evadeRequestOrderNO);


		//����һ�㣬ֱ�����г��������ȼ���Ϊ�ж����ݣ����������г����߳��ϲ������
		string compareResult = CranePrivilegeInterpreter::compareByCrane(craneNO, sender);
		log.Debug()<<"�Ƚ� ����(���ձ�������) ="<<craneNO<<"  ��   ���ų�(���ͱ�������)="<<sender<<" �ĵȼ��ߵ� Ϊ"<<compareResult<<endl;
		


		//���ö������ͣ��ȸ�ֵΪ���صĹغ����
		log.Debug()<<"��ʼ�趨���ö���...."<<endl;
		string actionType=CraneEvadeRequestBase::TYPE_AFTER_JOB;
		if(compareResult==CranePrivilegeInterpreter::COMPARE_RESULT_HIGH)
		{
			//�ұ������߸ߣ���ô�Ҿ��ùغ���õİ���ģʽ
			log.Debug()<<"���� �� ���ų� �ȼ���....���ùغ����......TYPE_AFTER_JOB......"<<endl;
			actionType=CraneEvadeRequestBase::TYPE_AFTER_JOB;
		}
		else if(compareResult==CranePrivilegeInterpreter::COMPARE_RESULT_LOW)
		{
			//�ұ������ߵף���ô�Ҿ����������õ�����ģʽ
			log.Debug()<<"���� �� ���ų� �ȼ���....������������......TYPE_RIGHT_NOW......"<<endl;
			actionType=CraneEvadeRequestBase::TYPE_RIGHT_NOW;
		}
		else 
		{
			log.Debug()<<"���� �� ���ų� �ȼ��ȽϽ���Ƿ����ȼ��Ƚ�ʧ�ܣ����̷��أ����ý���ʧ�ܣ�"<<endl;
			return;
		}
		log.Debug()<<"��˱��ö��� actionType="<<actionType<<endl;

		//���ñ���ָ�����ȼ�
		//double evadePriority = ACTION_COMMON_FUNCTION::getEvadePriority(sender, evadeRequestOrderNO);
		double evadePriority = 99;


		//����г�Ŀǰ�����Զ�״̬����ô�������κα���Ҫ���˳�
		if(cranePLCStatusBase.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Debug()<<"����="<<craneNO<<" ���� ���Զ� ģʽ���������˳������ٽ����κα���Ҫ�󣡣�"<<endl;
			return;
		}

		//���±��г������Զ�״̬
		log.Debug()<<"����="<<craneNO<<" ���� �Զ�ģʽ��׼������ָ����������ݣ�������д��......"<<endl;
		CraneEvadeRequestBase  craneEvadeRequestNew;
		craneEvadeRequestNew.setTargetCraneNO(craneNO);
		craneEvadeRequestNew.setSender(sender);
		craneEvadeRequestNew.setOriginalSender(origianlSender);
		craneEvadeRequestNew.setEvadeXRequest(evadeXRequest);
		craneEvadeRequestNew.setEvadeX(evadeXAct);
		craneEvadeRequestNew.setEvadeDirection(evadeDirection);
		craneEvadeRequestNew.setEvadeActionType(actionType);
		craneEvadeRequestNew.setStatus(CraneEvadeRequestBase::STATUS_INIT);
		craneEvadeRequestNew.setPriority(evadePriority);			//2018.11.30 zhangyuhong add ��������ָ�����ȼ�����
		craneEvadeRequestNew.logOutValues();

		//����ȷ�ϱ���ָ����е����
		//��Ϊ�������  ����Ϊ��  ״̬Ϊempty  ����Finished
		//								 ��������һ�������ӵ�  ״̬Ϊtodo
		//								 ��������һ������ִ�е��ӵ�  EXCUTING
		//�������Ϊ�գ���ôֱ��ѹ���ӵ�
		//����������ӵ�����ִ�У���ô�˳��������κδ���
		//�����������һ�������ӵ�
		//					����ɱ���ָ��ĵȼ������±���ָ���ô����ָ�����ָ��
		//					����ɱ���ָ��ĵȼ����±���ָ��ĵȼ���ͬ���ҷ�����ͬ
		//									����Ǵ������ ��ָ�����Ҫ��X������ô��ָ�����ָ��
		//									�����С������� ��ָ�����Ҫ��X��С����ô��ָ�����ָ��
	
		log.Debug()<<"����ָ������׼����ϣ�д��ǰ����Ҫ��ȡ����ָ���������ָ���ӵ�......"<<endl;
		CraneEvadeRequestBase  craneEvadeRequestOld;
		bool ret_DBRead=Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO, craneEvadeRequestOld);
		if(ret_DBRead==false)
		{
			log.Debug()<<"����= "<<craneNO<<"  ����ر���ָ���¼��ȡʧ�ܣ������˳������ձ�������ʧ�ܣ�"<<endl;
			return;
		}

		//***********************************************************************************************************
		//*
		//*						���1. ������û�б����ӵ���
		//*									STATUS_EMPTY��STATUS_FINISHED
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
			log.Debug()<<"����="<<craneNO<<" �ı���ָ�����û�б���ָ���ӵ���STATUS_EMPTY��STATUS_FINISHED������ֱ��ѹ���µı���ָ���ӵ���"<<endl;
			Adapter_UACS_CRANE_EVADE_REQUEST::Update(craneEvadeRequestNew);
			log.Debug()<<"�µı����ӵ����ųɹ���"<<endl;
		}

		//***********************************************************************************************************
		//*
		//*						���2. ���������ӵ����������ڴ�����ôʲôҲ�����˳�����
		//*									STATUS_EXCUTING
		//*
		//***********************************************************************************************************
		if(craneEvadeRequestOld.getStatus()==CraneEvadeRequestBase::STATUS_EXCUTING)
		{
			log.Debug()<<"����="<<craneNO<<" �����б����ӵ�����ִ���У�STATUS_EXCUTING������ѹ���µı����ӵ��������˳������ձ�������ʧ�ܣ�"<<endl;
			return;
		}

		//***********************************************************************************************************
		//*
		//*						���3. ���������ӵ������������ӵ����ǵȴ������״̬:
		//*									STATUS_INIT��STATUS_TO_DO
		//*
		//***********************************************************************************************************
		if(craneEvadeRequestOld.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
		{
						log.Debug()<<"����="<<craneNO<<" �����б����ӵ�������ʼ����׼��Ҫ����STATUS_INIT �� STATUS_TO_DO��"<<endl;
						//�����ָ��ĵȼ�������ָ��ĵȼ�����ô����
						if(craneEvadeRequestNew.getEvadeActionType()==CraneEvadeRequestBase::TYPE_RIGHT_NOW)
						{
									if(craneEvadeRequestOld.getEvadeActionType()==CraneEvadeRequestBase::TYPE_AFTER_JOB)
									{
											log.Debug()<<"����="<<craneNO<<" �����б����ӵ�����=AFTER_JOB���µı����ӵ�����=RIGHT_NOW���µı����ӵ����ǵ������ӵ���"<<endl;
											Adapter_UACS_CRANE_EVADE_REQUEST::Update(craneEvadeRequestNew);
											log.Debug()<<"�µı����ӵ����ųɹ���"<<endl;
									}
						}

						//�����ָ��Ķ����ȼ�����ָ��ĵȼ���ͬ���ҷ���Ҳ��ͬ
						if(craneEvadeRequestNew.getEvadeActionType()==craneEvadeRequestOld.getEvadeActionType())
						{
									log.Debug()<<"����="<<craneNO<<" �����б����ӵ�����="<<craneEvadeRequestOld.getEvadeActionType()<<"���µı����ӵ�����="<<craneEvadeRequestNew.getEvadeActionType()<<endl;
									log.Debug()<<"�¾ɱ����ӵ�����һ�£�"<<endl;

									if(craneEvadeRequestNew.getEvadeDirection()==craneEvadeRequestOld.getEvadeDirection())
									{
											log.Debug()<<"����="<<craneNO<<" �����б����ӵ�����="<<craneEvadeRequestOld.getEvadeDirection()<<"���µı����ӵ�����="<<craneEvadeRequestNew.getEvadeDirection()<<endl;
											log.Debug()<<"�¾ɱ����ӵ�����һ�£�"<<endl;
											//�¾ɱ���ָ���������ͬ���Ҷ��Ǵ������ָ��
											if(craneEvadeRequestNew.getEvadeDirection()==MOVING_DIR::DIR_X_INC)
											{
												if(craneEvadeRequestNew.getEvadeX()>craneEvadeRequestOld.getEvadeX())
												{
														log.Debug()<<"�¾ɱ����ӵ�������� X_INC���±����ӵ�ʵ�ʱ���X���� > �ɱ����ӵ�ʵ�ʱ���X���� ���µı����ӵ����ǵ������ӵ���"<<endl;
														Adapter_UACS_CRANE_EVADE_REQUEST::Update(craneEvadeRequestNew);
														log.Debug()<<"�µı����ӵ����ųɹ���"<<endl;
												}
											}
											//�¾ɱ���ָ���������ͬ���Ҷ���С�������ָ��
											if(craneEvadeRequestNew.getEvadeDirection()==MOVING_DIR::DIR_X_DES)
											{
													if(craneEvadeRequestNew.getEvadeX()<craneEvadeRequestOld.getEvadeX())
													{
															log.Debug()<<"�¾ɱ����ӵ�������� X_DES���±����ӵ�ʵ�ʱ���X���� < �ɱ����ӵ�ʵ�ʱ���X���� ���µı����ӵ����ǵ������ӵ���"<<endl;
															Adapter_UACS_CRANE_EVADE_REQUEST::Update(craneEvadeRequestNew);
															log.Debug()<<"�µı����ӵ����ųɹ���"<<endl;
													}
											}

									}
						}

						log.Debug()<<"���ձ��������߼�������󣺵�������һ��TO_DO�ı����ӵ����µı����ӵ�����ѹ�뵯�У�"<<endl;
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





