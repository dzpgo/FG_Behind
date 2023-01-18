#include "WatchEventHandlerI.h"
#include "MsgUS01.h"
#include "MsgUS02.h"




Monitor::CWatchEventHandlerI::CWatchEventHandlerI(string theCraneNO)
{
			craneNO=theCraneNO;

			eventTagName_Evade_Request=Evade_Tag_Define::getTagName_Evade_Request(craneNO);
			eventTagName_Evade_Cancel=Evade_Tag_Define::getTagName_Evade_Cancel(craneNO);
		
}

void Monitor::CWatchEventHandlerI::EventWatchWithData(const iPlature::TAGVALUEMAP& tagValueMap,
																										  const std::string& strEventName,
																										  const std::string& strValue,
																										  const Ice::Current&)
{
	// ������������ֵ
	IceUtil::Mutex::Lock lock(m_mutexValue);
	
	LOG::doConfigure("CWatchEventHandlerI_APP_Crane", BRANCH_CONFIG);
	LOG log(__FUNCTION__,"CWatchEventHandlerI_APP_Crane");

	try
	{
		//SRS���ⷴ������tag��
		//strEventName��ʽ�� EV_SRS_E1_LU01  EV_SRS_E1_LU02
		string srsTagNameLU01 = "EV_SRS_" + craneNO + "_LU01";
		string srsTagNameLU02 = "EV_SRS_" + craneNO + "_LU02";

		if (strEventName == srsTagNameLU01)
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			SrsMsgRcvHandler handler;
			handler.LU01Handler(strValue, craneNO);			
		}

		if (strEventName == srsTagNameLU02)
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			SrsMsgRcvHandler handler;
			handler.LU02Handler(strValue, craneNO);
		}



		
/*******************************************************************************************************************************************************************/

		//�յ����淢���Ķ�ָ��
		if (strEventName == craneNO+"_DownLoadShortCommand")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			MsgHMICRANE01::getInstance()->HandleMessage(craneNO,strValue);
		}

		//�յ����Ի��淢���Ķ�ָ�� ����ָ��
		if(strEventName == craneNO+"_DownLoadOrder")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			MsgHMICRANE02::getInstance()->HandleMessage(craneNO,strValue);
		}

/*******************************************************************************************************************************************************************/

		//��������
		if(strEventName==eventTagName_Evade_Request)
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Debug()<<"received_evade_request"<<endl;
			string theCraneNO;  
			string theSender;
			string theOrigianlSender;
			long theEvadeXRequest;
			string theEvadeDirection;
			//2018.11.29 zhangyuhong add
			long theEvadeRequestOrderNO;

			bool ret_split=EvadeRequestReceiver::splitTag_EvadeRequest(strValue, theCraneNO,theSender, theOrigianlSender, theEvadeXRequest, theEvadeDirection, theEvadeRequestOrderNO);

			log.Debug()<<"craneNO="<<craneNO<<endl;
			log.Debug()<<"theCraneNO="<<theCraneNO<<endl;
			log.Debug()<<"theSender="<<theSender<<endl;
			log.Debug()<<"theOrigianlSender="<<theOrigianlSender<<endl;
			log.Debug()<<"theEvadeXRequest="<<theEvadeXRequest<<endl;
			log.Debug()<<"theEvadeDirection="<<theEvadeDirection<<endl;
			log.Debug()<<"theEvadeRequestOrderNO="<<theEvadeRequestOrderNO<<endl;

			if(craneNO==theCraneNO)
			{
				EvadeRequestReceiver::receive(craneNO, theSender, theOrigianlSender , theEvadeXRequest, theEvadeDirection, theEvadeRequestOrderNO);
			}
		}
		//����ȡ��
		else if(strEventName==eventTagName_Evade_Cancel)
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Debug()<<"received_evade_cancel_request"<<endl;
			string theSender;
			string theEvadeDirection;

			bool ret_split=EvadeCancelReceiver::splitTag_EvadeCancel(strValue, theSender,  theEvadeDirection);

			log.Debug()<<"theSender="<<theSender<<endl;
			log.Debug()<<"theEvadeDirection="<<theEvadeDirection<<endl;

			EvadeCancelReceiver::receive(craneNO, theSender, theEvadeDirection);

		}

/*******************************************************************************************************************************************************************/
		//�г���ǯ�Ƕ�����
		if (strEventName == "EV_CRANE_CLAMP_ANGLE_INIT")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			if ( strValue == craneNO )
			{
				//���ͼ�ǯ�Ƕ��������
				CranePLCOrderBase craneClampAngleInitPLCOrder;
				craneClampAngleInitPLCOrder.setCraneNO(craneNO);
				craneClampAngleInitPLCOrder.setOrderID(105);
				craneClampAngleInitPLCOrder.setShortCmd(420);
				MsgEUCR01::getInstance()->SendOutMessage(craneClampAngleInitPLCOrder);
			}
		}

/*******************************************************************************************************************************************************************/
		//2018.1.25 zhangyuhong add
		//2018.4.4 zhangyuhong modify
		//������������HMI����-A6�е���ع��ܣ���̨ʵ�ֵ�һЩ����	
		//2.WMS����ģʽ-��ָ�����
		if (strEventName == craneNO + "_HMI_A6_WMS_MODE")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			//1-���͡��ֶ�����ָ��
			if (strValue == "1")
			{
				CranePLCOrderBase driveCranePLCOrder;
				driveCranePLCOrder.setCraneNO(craneNO);
				driveCranePLCOrder.setOrderID(105);
				driveCranePLCOrder.setShortCmd(500);
				MsgEUCR01::getInstance()->SendOutMessage(driveCranePLCOrder);
			}
			//2-���͡��Զ�����ָ��
			else if (strValue == "2")
			{
				CranePLCOrderBase autoCranePLCOrder;
				autoCranePLCOrder.setCraneNO(craneNO);
				autoCranePLCOrder.setOrderID(105);
				autoCranePLCOrder.setShortCmd(400);
				MsgEUCR01::getInstance()->SendOutMessage(autoCranePLCOrder);
			}
			//3-��ң�ء�����ʱ����δʵ�֣�
			else if(strValue == "3")
			{
			}
			//4-��ά�ޡ� û�ж�ָ����� ԭ�ȷ����3-1�г���ָ�ȫ�������3-2
			else if(strValue == "4")
			{
				//2018.11.28 zhangyuhong add
				//�������г����PLC�����л��г���ά��ģʽ����
				//��ָ����룺201  �л��г�Ϊά��ģʽ
				CranePLCOrderBase repairCranePLCOrder;
				repairCranePLCOrder.setCraneNO(craneNO);
				repairCranePLCOrder.setOrderID(105);
				repairCranePLCOrder.setShortCmd(201);
				MsgEUCR01::getInstance()->SendOutMessage(repairCranePLCOrder);
			}
		}
		// ��ָ��
		else if (strEventName == craneNO + "_HMI_A6_SHORTCMD" )			
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			//1����ͣ
			if (strValue == "1")
			{
				CranePLCOrderBase EMRGCranePLCOrder;
				EMRGCranePLCOrder.setCraneNO(craneNO);
				EMRGCranePLCOrder.setOrderID(105);
				EMRGCranePLCOrder.setShortCmd(200);
				MsgEUCR01::getInstance()->SendOutMessage(EMRGCranePLCOrder);
			}
			//2�����ԣ�ֹͣ��ָ�
			else if (strValue == "2")
			{
				CranePLCOrderBase ResetCranePLCOrder;
				ResetCranePLCOrder.setCraneNO(craneNO);
				ResetCranePLCOrder.setOrderID(105);
				ResetCranePLCOrder.setShortCmd(300);
				MsgEUCR01::getInstance()->SendOutMessage(ResetCranePLCOrder);
			}
			//3��ֹͣ���г��ֶ���
			else if (strValue == "3")
			{
				CranePLCOrderBase PauseCranePLCOrder;
				PauseCranePLCOrder.setCraneNO(craneNO);
				PauseCranePLCOrder.setOrderID(105);
				PauseCranePLCOrder.setShortCmd(500);
				MsgEUCR01::getInstance()->SendOutMessage(PauseCranePLCOrder);
			}
			//4���������г��Զ���
			else if (strValue == "4")
			{
				CranePLCOrderBase ContinueCranePLCOrder;
				ContinueCranePLCOrder.setCraneNO(craneNO);
				ContinueCranePLCOrder.setOrderID(105);
				ContinueCranePLCOrder.setShortCmd(400);
				MsgEUCR01::getInstance()->SendOutMessage(ContinueCranePLCOrder);
			}
			//5���صǳ�λ
			else if (strValue == "5")
			{
				//Test_Evade_Move::Test_BoardingMoving(craneNO);
			}	
		}
	}
	catch(...)
	{

	}
}

/*
* 
* ����
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}