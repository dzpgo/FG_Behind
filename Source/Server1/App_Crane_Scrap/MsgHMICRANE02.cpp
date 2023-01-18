#include "MsgHMICRANE02.h"
#include "SafetyArea_Bay.h"


using namespace Monitor;
using namespace iPlature;



MsgHMICRANE02*  MsgHMICRANE02::m_pMsgHMICRANE02 = NULL;



MsgHMICRANE02::MsgHMICRANE02() 
{
	
}


MsgHMICRANE02 :: ~MsgHMICRANE02(void)
{
	
	delete m_pMsgHMICRANE02;


}

 MsgHMICRANE02* MsgHMICRANE02::getInstance(void)
{
	if (m_pMsgHMICRANE02 == NULL)
	{
		m_pMsgHMICRANE02 = new MsgHMICRANE02;
	}
	return m_pMsgHMICRANE02;
}




bool MsgHMICRANE02::HandleMessage(string myCraneNO,string messageData)
{


	string functionName="MsgHMICRANE02 :: HandleMessage()";

	bool ret=true;

	LOG log(functionName, AUTO_CATCH_PID);


	AlarmWrapper _p("");

	try
	{
		log.Debug()<<"........................................................................................log of  data int the message HMICRANE02..................................................................................................................."<<endl;

		log.Debug()<<"messageData="<<messageData<<endl;

		vector<string> vectorMessageItems;
		vectorMessageItems= StringHelper::ToVector<string>(messageData, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

		if(vectorMessageItems.size() !=53 && vectorMessageItems.size() !=13)
		{
					log.Debug()<<"HMICRANE02 data has error format"<<endl;
					return false;
		}

		string craneNOInMessage=vectorMessageItems[0];
		StringHelper::Trim(craneNOInMessage);

		if(myCraneNO!=craneNOInMessage)
		{
					log.Debug()<<"HMICRANE02 include a wrong craneNO"<<endl;
					return false;
		}

	    CranePLCOrderBase cranePLCOrderBase;


		//1 CRANE_NO
		cranePLCOrderBase.setCraneNO( craneNOInMessage );

		log.Debug()<<"1......";
		//2 ORDER_Id
		cranePLCOrderBase.setOrderID(  StringHelper::ToNumber<long>(vectorMessageItems[1])  );
		log.Debug()<<"2......";
		//3 MAT_WEIGHT
		cranePLCOrderBase.setMatWeight(  StringHelper::ToNumber<long>(vectorMessageItems[2])  );
		log.Debug()<<"3......";
		//4 MAT_TYPE
		cranePLCOrderBase.setMatType(  StringHelper::ToNumber<long>(vectorMessageItems[3])  );
		log.Debug()<<"4......";
		//5 PLAN_UP_X
		cranePLCOrderBase.setPlanUpX(  StringHelper::ToNumber<long>(vectorMessageItems[4])  );
		log.Debug()<<"5......";
		//6 PLAN_UP_Y
		cranePLCOrderBase.setPlanUpY(  StringHelper::ToNumber<long>(vectorMessageItems[5])  );
		log.Debug()<<"6......";
		//7 PLAN_UP_Z
		cranePLCOrderBase.setPlanUpZ(  StringHelper::ToNumber<long>(vectorMessageItems[6])  );
		log.Debug()<<"7......";
		//8 UP_ROTATE_ANGLE_SET
		//cranePLCOrderBase.setUpRptateAngleSet(  StringHelper::ToNumber<long>(vectorMessageItems[7])  );
		log.Debug()<<"8......";
		//9 PLAN_DOWN_X
		cranePLCOrderBase.setPlanDownX(  StringHelper::ToNumber<long>(vectorMessageItems[8])  );
		log.Debug()<<"9......";
		//10 PLAN_DOWN_Y
		cranePLCOrderBase.setPlanDownY(  StringHelper::ToNumber<long>(vectorMessageItems[9])  );
		log.Debug()<<"10......";
		//11 PLAN_DOWN_Z
		cranePLCOrderBase.setPlanDownZ(  StringHelper::ToNumber<long>(vectorMessageItems[10])  );
		log.Debug()<<"11......";
		////12 DOWN_ROTATE_ANGLE_SET
		//cranePLCOrderBase.setDownRotateAngleSet(  StringHelper::ToNumber<long>(vectorMessageItems[11])  );
		//log.Debug()<<"12......";
		//13 shortCmd
		cranePLCOrderBase.setShortCmd(  StringHelper::ToNumber<long>(vectorMessageItems[12])  );
		log.Debug()<<"13......";

		//不是走行指令的话，就是手自动切换 复位等功能，直接发送电文
		if (cranePLCOrderBase.getShortCmd() != 1 && cranePLCOrderBase.getShortCmd() != 2)
		{
			map< long, map<string, long> > mapMidPointList;
			map<string , long> mapMidPoint;
			mapMidPoint.insert( make_pair<string, long>("X", CranePLCOrderBase::PLC_INT_NULL));
			mapMidPoint.insert( make_pair<string, long>("Y", CranePLCOrderBase::PLC_INT_NULL));
			for (int i=0; i < 20; i++)
			{
				mapMidPointList.insert( make_pair<long, map<string, long> >(i+1, mapMidPoint)); 
			}
			cranePLCOrderBase.setMapMidPointList(mapMidPointList);
			log.Debug()<<"14......53 MidPoint";

			cranePLCOrderBase.logOutValues();

			CraneMonitor::getInstance()->DownLoadCranePLCOrder(cranePLCOrderBase);

			log.Debug()<<"....................................................sending message to PLC finished.................................................................."<<endl;

			return ret;
		}

		//中间点设置
		map< long, map<string, long> > mapMidPointList;
		map<string , long> mapMidPoint;
		mapMidPoint.insert( make_pair<string, long>("X", CranePLCOrderBase::PLC_INT_NULL));
		mapMidPoint.insert( make_pair<string, long>("Y", CranePLCOrderBase::PLC_INT_NULL));
		for (int i=0; i < 20; i++)
		{
			mapMidPoint["X"] = StringHelper::ToNumber<long>(vectorMessageItems[i*2+13]);
			mapMidPoint["Y"] = StringHelper::ToNumber<long>(vectorMessageItems[i*2+14]);
			mapMidPointList.insert( make_pair<long, map<string, long> >(i+1, mapMidPoint)); 
		}
		//14 
		cranePLCOrderBase.setMapMidPointList(mapMidPointList);
		log.Debug()<<"14......53 MidPoint";

		

		//20220810 ZHANGYUHONG ADD
		if (cranePLCOrderBase.getPlanUpZ() != CranePLCOrderBase::PLC_INT_NULL || cranePLCOrderBase.getPlanDownZ() != CranePLCOrderBase::PLC_INT_NULL)
		{
			//是起升下降指令  不走路径规划  直接下发
			log.Info()<<"起升下降指令，直接下发.............................."<<endl;
			cranePLCOrderBase.logOutValues();

			CraneMonitor::getInstance()->DownLoadCranePLCOrder(cranePLCOrderBase);

			log.Debug()<<"........................................................................................sending message to PLC finished........................................................................................................................"<<endl;

			return ret;

		}

		

		

		log.Debug()<<"........................................................................................开始进行路径规划算法实施 ArrangeRoute..................................................................................................................."<<endl;
		vector<RouteStepPointBase> vectorRoutePoints;		

		CranePLCStatusBase cranePLCStatus;
		CraneMonitor::getInstance()->getPLCStatus(cranePLCStatus);

		//设定目标点
		long targetX = CranePLCOrderBase::PLC_INT_NULL;
		long targetY = CranePLCOrderBase::PLC_INT_NULL;
		//空钩时，目标点
		if (cranePLCStatus.getHasCoil() == 0)
		{
			targetX = cranePLCOrderBase.getPlanUpX();
			targetY = cranePLCOrderBase.getPlanUpY();
		}
		//重钩时，目标点
		if (cranePLCStatus.getHasCoil() != 0)
		{
			targetX = cranePLCOrderBase.getPlanDownX();
			targetY = cranePLCOrderBase.getPlanDownY();
		}

		
		//END----------------------------------------------------------------------------------------------------------------------------
		

		log.Debug()<<"  ..... 调用路径规划算法 arrangeRoute ......" <<endl;

		

		bool startInRed = false;
		SafetyArea_Bay::getInstance()->arrangeRoute(cranePLCStatus.getXAct(),
																							cranePLCStatus.getYAct(),
																							targetX, //cranePLCOrderBase.getPlanUpX(),
																							targetY, //cranePLCOrderBase.getPlanUpY(),
																							vectorRoutePoints, 
																							startInRed);

		log.Debug()<<"调用完毕，计算vectorRoutePoints.size="<< vectorRoutePoints.size() <<endl;

		string tagVal_RoutePoints="";
		for(int i=0;i<vectorRoutePoints.size();i++)
		{
			tagVal_RoutePoints+=StringHelper::ToString( vectorRoutePoints[i].getX() );
			tagVal_RoutePoints+=",";
			tagVal_RoutePoints+=StringHelper::ToString( vectorRoutePoints[i].getY() );
			tagVal_RoutePoints+=",";
			tagVal_RoutePoints+=StringHelper::ToString( vectorRoutePoints[i].getFlagReachFinalTarget() );
			tagVal_RoutePoints+="|";
		}

		TAGVALUEMAP Tags;
		string TagName="";
		string TagValue="";

		TagName=myCraneNO+"_routePoints";
		TagValue=tagVal_RoutePoints;
		Tags.insert(map<string,string>::value_type( TagName , TagValue ) );


		TAGVALUEMAP TagTimeStamp;
		Tag::GetInst().MDPut(TagTimeStamp,Tags);	

		log.Debug()<<"........................................................................................now begin to send the message to PLC..................................................................................................................."<<endl;

		//for other cranes do not use these code 
		if (vectorRoutePoints.size() >= 2    )
		{
				log.Debug()<<"第1步点X first step Point_X = "<< vectorRoutePoints[1].getX() ;
				log.Debug()<<"\t 第1步点Y first step Point_Y = "<< vectorRoutePoints[1].getY() ;
				//log.Debug()<<"\t 第1步点是否是目标点标记 FlagReachFinalTarget = "<< ACTION_COMMON_FUNCTION::TrueOrFlase( vectorRoutePoints[1].getFlagReachFinalTarget() )<<endl;

				if (cranePLCStatus.getHasCoil() == 0)
				{
					cranePLCOrderBase.setPlanUpX( vectorRoutePoints[1].getX() );
					cranePLCOrderBase.setPlanUpY( vectorRoutePoints[1].getY() );
					
				}
				if (cranePLCStatus.getHasCoil() == 1)
				{
					cranePLCOrderBase.setPlanDownX( vectorRoutePoints[1].getX() );
					cranePLCOrderBase.setPlanDownY( vectorRoutePoints[1].getY() );
					
				}				
		}
		else
		{
				log.Error()<<"路径规划算法计算失败：vectorRoutePoints.size<2. 无法获取第1步点位置..对行车的PlanDownXYZ/PlanUpXYZ做封9处理.............. ";

				if (cranePLCStatus.getHasCoil() == 0)
				{
					cranePLCOrderBase.setPlanUpX(CranePLCOrderBase::PLC_INT_NULL );
					cranePLCOrderBase.setPlanUpY( CranePLCOrderBase::PLC_INT_NULL );
				}
				if (cranePLCStatus.getHasCoil() == 1)
				{
					cranePLCOrderBase.setPlanDownX( CranePLCOrderBase::PLC_INT_NULL);
					cranePLCOrderBase.setPlanDownY( CranePLCOrderBase::PLC_INT_NULL );
				}

				ret = false;				
				return ret;
		}

		cranePLCOrderBase.logOutValues();

		CraneMonitor::getInstance()->DownLoadCranePLCOrder(cranePLCOrderBase);

		log.Debug()<<"........................................................................................sending message to PLC finished........................................................................................................................"<<endl;



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
	return ret;
}









