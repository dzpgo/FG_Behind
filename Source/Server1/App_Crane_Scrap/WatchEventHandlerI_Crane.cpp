#include "WatchEventHandlerI_Crane.h"

WatchEventHandlerI_Crane::WatchEventHandlerI_Crane(string myCraneNO)
{
	craneNO=myCraneNO;
}

WatchEventHandlerI_Crane::~WatchEventHandlerI_Crane()
{
}

void
WatchEventHandlerI_Crane::CWatchEventHandlerI(const CranePLCStatusDesc& desc, const Ice::Current& current)
{
	string functionName="WatchEventHandlerI_Crane :: CWatchEventHandlerI()";

	LOG log(functionName);	

	try
	{
			log.Debug()<<"------------------------------the values in the CranePLCStatusDesc--------------------------------------"<<endl;
			//1
			log.Debug()<<"\t craneNO="<<desc.craneNO;
			//2
			log.Debug()<<"\t ready="<<desc.ready;
			//3
			log.Debug()<<"\t controlMode="<<desc.controlMode;
			//4
			log.Debug()<<"\t askPlan="<<desc.askPlan;
			//5
			log.Debug()<<"\t taskExcuting="<<desc.taskExcuting;
			//6
			log.Debug()<<"\t  xAct="<<desc.xAct;
			//7
			log.Debug()<<"\t yAct="<<desc.yAct;
			//8
			log.Debug()<<"\t zAct="<<desc.zAct;
			//9
			log.Debug()<<"\t xSpeed="<<desc.xSpeed;
			//10
			log.Debug()<<"\t ySpeed="<<desc.ySpeed;
			//11
			log.Debug()<<"\t zSpeed="<<desc.zSpeed;
			//12
			log.Debug()<<"\t xDirectPositive="<<desc.xDirectPositive;
			//13
			log.Debug()<<"\t xDirectNegative="<<desc.xDirectNegative;
			//14
			log.Debug()<<"\t yDirectPositive="<<desc.yDirectPositive;
			//15
			log.Debug()<<"\t yDirectNegative="<<desc.yDirectNegative;
			//16
			log.Debug()<<"\t zDirectPositive="<<desc.zDirectPositive;
			//17
			log.Debug()<<"\t zDirectNegative="<<desc.zDirectNegative;
			//18
			log.Debug()<<"\t hasCoil="<<desc.hasCoil;
			//19
			log.Debug()<<"\t weightLoaded="<<desc.weightLoaded;
			//20
			log.Debug()<<"\t dipAngleAct="<<desc.dipAngleAct;
			//21
			log.Debug()<<"\t emgStop="<<desc.emgStop;
			//22
			log.Debug()<<"\t orderID="<<desc.orderID;
			//23
			log.Debug()<<"\t planUpX="<<desc.planUpX;
			//24
			log.Debug()<<"\t planUpY="<<desc.planUpY;
			//25
			log.Debug()<<"\t planUpZ="<<desc.planUpZ;
			//26
			log.Debug()<<"\t planDownX="<<desc.planDownX;
			//27
			log.Debug()<<"\t planDownY="<<desc.planDownY;
			//28
			log.Debug()<<"\t planDownZ="<<desc.planDownZ;
			////29
			//log.Debug()<<"\t craneStatus="<<desc.craneStatus;
			////30
			//log.Debug()<<"\t craneAlarm="<<desc.craneAlarm;
			////31
			//log.Debug()<<"\t timeReceivet "<<desc.timeReceive<<endl;

			if(desc.craneNO!=craneNO)
			{
				log.Debug()<<" Now try to input the PLC Status to Crane Monitor Class(Other Crane In Same Bay)................................................"<<endl;
				CranePLCStatusBase cranePLCStatusBase=CranePLCStatusBase::TransFromStruct(desc);
				CraneMonitor::getInstance()->inputPLCStatus( cranePLCStatusBase );
			}

			log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;

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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
    catch (std::exception& stdex)
    {
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
    }
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

}