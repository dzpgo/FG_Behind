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
	// 加锁保护参数值
	IceUtil::Mutex::Lock lock(m_mutexValue);
	
	LOG::doConfigure("CWatchEventHandlerI_APP_Crane", BRANCH_CONFIG);
	LOG log(__FUNCTION__,"CWatchEventHandlerI_APP_Crane");

	try
	{
		//SRS激光反馈电文tag点
		//strEventName格式： EV_SRS_E1_LU01  EV_SRS_E1_LU02
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

		//收到画面发来的短指令
		if (strEventName == craneNO+"_DownLoadShortCommand")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			MsgHMICRANE01::getInstance()->HandleMessage(craneNO,strValue);
		}

		//收到调试画面发来的短指令 正常指令
		if(strEventName == craneNO+"_DownLoadOrder")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			MsgHMICRANE02::getInstance()->HandleMessage(craneNO,strValue);
		}

/*******************************************************************************************************************************************************************/

		//避让请求
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
		//避让取消
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
		//行车夹钳角度清零
		if (strEventName == "EV_CRANE_CLAMP_ANGLE_INIT")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			if ( strValue == craneNO )
			{
				//发送夹钳角度清零电文
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
		//配合张宇宏做的HMI画面-A6中的相关功能，后台实现的一些代码	
		//2.WMS驱动模式-短指令电文
		if (strEventName == craneNO + "_HMI_A6_WMS_MODE")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			//1-发送“手动”短指令
			if (strValue == "1")
			{
				CranePLCOrderBase driveCranePLCOrder;
				driveCranePLCOrder.setCraneNO(craneNO);
				driveCranePLCOrder.setOrderID(105);
				driveCranePLCOrder.setShortCmd(500);
				MsgEUCR01::getInstance()->SendOutMessage(driveCranePLCOrder);
			}
			//2-发送“自动”短指令
			else if (strValue == "2")
			{
				CranePLCOrderBase autoCranePLCOrder;
				autoCranePLCOrder.setCraneNO(craneNO);
				autoCranePLCOrder.setOrderID(105);
				autoCranePLCOrder.setShortCmd(400);
				MsgEUCR01::getInstance()->SendOutMessage(autoCranePLCOrder);
			}
			//3-“遥控”（暂时保留未实现）
			else if(strValue == "3")
			{
			}
			//4-“维修” 没有短指令电文 原先分配给3-1行车的指令，全部分配给3-2
			else if(strValue == "4")
			{
				//2018.11.28 zhangyuhong add
				//增加向行车电控PLC发送切换行车至维修模式电文
				//段指令代码：201  切换行车为维修模式
				CranePLCOrderBase repairCranePLCOrder;
				repairCranePLCOrder.setCraneNO(craneNO);
				repairCranePLCOrder.setOrderID(105);
				repairCranePLCOrder.setShortCmd(201);
				MsgEUCR01::getInstance()->SendOutMessage(repairCranePLCOrder);
			}
		}
		// 短指令
		else if (strEventName == craneNO + "_HMI_A6_SHORTCMD" )			
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			//1：急停
			if (strValue == "1")
			{
				CranePLCOrderBase EMRGCranePLCOrder;
				EMRGCranePLCOrder.setCraneNO(craneNO);
				EMRGCranePLCOrder.setOrderID(105);
				EMRGCranePLCOrder.setShortCmd(200);
				MsgEUCR01::getInstance()->SendOutMessage(EMRGCranePLCOrder);
			}
			//2：重试（停止短指令）
			else if (strValue == "2")
			{
				CranePLCOrderBase ResetCranePLCOrder;
				ResetCranePLCOrder.setCraneNO(craneNO);
				ResetCranePLCOrder.setOrderID(105);
				ResetCranePLCOrder.setShortCmd(300);
				MsgEUCR01::getInstance()->SendOutMessage(ResetCranePLCOrder);
			}
			//3：停止（切成手动）
			else if (strValue == "3")
			{
				CranePLCOrderBase PauseCranePLCOrder;
				PauseCranePLCOrder.setCraneNO(craneNO);
				PauseCranePLCOrder.setOrderID(105);
				PauseCranePLCOrder.setShortCmd(500);
				MsgEUCR01::getInstance()->SendOutMessage(PauseCranePLCOrder);
			}
			//4：继续（切成自动）
			else if (strValue == "4")
			{
				CranePLCOrderBase ContinueCranePLCOrder;
				ContinueCranePLCOrder.setCraneNO(craneNO);
				ContinueCranePLCOrder.setOrderID(105);
				ContinueCranePLCOrder.setShortCmd(400);
				MsgEUCR01::getInstance()->SendOutMessage(ContinueCranePLCOrder);
			}
			//5：回登车位
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
* 析构
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}