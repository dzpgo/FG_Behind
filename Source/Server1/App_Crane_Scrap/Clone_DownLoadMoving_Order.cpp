#pragma once
#include "Clone_DownLoadMoving_Order.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"


using namespace Monitor;

Clone_DownLoadMoving_Order :: Clone_DownLoadMoving_Order(void)
{
}



Clone_DownLoadMoving_Order :: ~Clone_DownLoadMoving_Order(void)
{
}


bool Clone_DownLoadMoving_Order :: go	(  string bayNO, 
																				    string craneNO, 
																					long orderNO, 
																					long currentX, 
																					long currentY, 
																					long targetX, 
																					long targetY, 
																					long hasCoil, 
																					long downRotateAngle, 
																					long upRotateAngle, 
																					long shortCmd )
{
	bool ret=false;

	string functionName="Clone_DownLoadMoving_Order :: go()";
	LOG log(functionName, AUTO_CATCH_PID);
    long deltaDistance=50;
	try
	{		
			CranePLCOrderBase  msg01_CranePLC_Order;
			
			//2017.11.22 zhangyuhong add
			//19  设置短指令 0：不执行   1：执行
			//由于改了UC01的通信接口，增加了短指令字段，所以添加短指令初始值
			//msg01_CranePLC_Order.setShortCmd(1);
			//2018.8.1 zhangyuhong add 
			//新增中间点指令状态  2-中间点  1-最终目标点
			msg01_CranePLC_Order.setShortCmd(shortCmd);


			//1.行车号
			msg01_CranePLC_Order.setCraneNO( craneNO );
			//2.指令号
			msg01_CranePLC_Order.setOrderID( orderNO );	
			//3.取料量
			//msg01_CranePLC_Order.setMatWeight(matWeight);
			//4.取料类型
			//msg01_CranePLC_Order.setMatType(matType);

			////落关转角
			//msg01_CranePLC_Order.setDownRotateAngleSet(downRotateAngle);

			//起卷转角
			//msg01_CranePLC_Order.setUpRptateAngleSet(upRotateAngle);

			long canReachX=CranePLCOrderBase::PLC_INT_NULL;

			log.Info()<<"1--------避让靠近逻辑计算出 targetX---------------------------------------"<<endl;
			//后续添加逻辑,计算出targetX
			canReachX = targetX;			


			//以下先注释-----20230108-----yezhiwei
			//log.Debug()<<"......................开始进行路径规划算法实施 ArrangeRoute.........................."<<endl;

			////arrange the route from current pos to special point
			//vector<RouteStepPointBase> vectorRoutePoints;
			//log.Debug()<<"  ..... 调用路径规划算法 arrangeRoute ......" <<endl;

			//bool startInRed = false;
			//SafetyArea_Bay::getInstance()->arrangeRoute(currentX, currentY,  canReachX , targetY, vectorRoutePoints, startInRed);

			////2019.7.22 zhangyuhong add
			//if (startInRed == true)
			//{
			//		string tagValue = ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8040;
			//		ACTION_COMMON_FUNCTION::SetTagValue(craneNO, 
			//																							ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS, 
			//																							tagValue);
			//		ret = false;
			//		return ret;
			//}
			//else
			//{
			//		string tagValue = ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_0;
			//		ACTION_COMMON_FUNCTION::SetTagValue(craneNO, 
			//																							ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS, 
			//																							tagValue);
			//}

			//log.Debug()<<"调用完毕，计算vectorRoutePoints.size="<< vectorRoutePoints.size() <<endl;
			//log.Debug()<<"---------------移动到鞍座位置的第1步点 -------------- "<<endl;
			//log.Debug()<<"路径起始点X Route Start X = "<< vectorRoutePoints[0].getX();
			//log.Debug()<<"\t 路径起始点Y Route Start Y = "<< vectorRoutePoints[0].getY() <<endl;
			//log.Debug()<<"----------------------------------------------------------- "<<endl;


		 //  //the first one is the current point and then there are route steps.
			//if (vectorRoutePoints.size() >= 2    )
			//{

			//	log.Debug()<<"第1步点X first step Point_X = "<< vectorRoutePoints[1].getX() ;
			//	log.Debug()<<"\t 第1步点Y first step Point_Y = "<< vectorRoutePoints[1].getY() ;

			//	if(hasCoil == 0)
			//	{
			//		msg01_CranePLC_Order.setPlanUpX( vectorRoutePoints[1].getX() );
			//		msg01_CranePLC_Order.setPlanUpY( vectorRoutePoints[1].getY() );					
			//	} 


			//	if(hasCoil != 0)
			//	{
			//		msg01_CranePLC_Order.setPlanDownX( vectorRoutePoints[1].getX() );
			//		msg01_CranePLC_Order.setPlanDownY( vectorRoutePoints[1].getY() );					
			//	}

			//	log.Debug()<<"安全起见，对PlanUpZ/PlanDownZ封9...."<<endl;
			//	msg01_CranePLC_Order.setPlanUpZ( CranePLCOrderBase::PLC_INT_NULL );
			//	msg01_CranePLC_Order.setPlanDownZ( CranePLCOrderBase::PLC_INT_NULL );

			//}
			//else				
			//{
			//			log.Error()<<"路径规划算法计算失败：vectorRoutePoints.size<2. 无法获取第1步点位置..对行车的PlanDownXYZ/PlanUpXYZ做封9处理.............. ";
			//			log.Info()<<"现在改成不再下发封9指令了，直接返回false......"<<endl;
			//			ret = false;
			//			return ret;	 
			//}	

			//log.Info()<<"2--------根据 targetX, targetY 计算出 中间点-------------------------------"<<endl;
			////后续添加计算中间点逻辑：
			////1.要么在ACTION_COMMON中添加
			////2.要么调用产品化路径计算模块
			//map<long, map<string, long> > mapMidPointList;
			//mapMidPointList = msg01_CranePLC_Order.getMapMidPointList();
			//
			//if ( true == ACTION_COMMON_FUNCTION::CalMidPointList(bayNO, currentX, currentY, targetX, targetY, mapMidPointList) )
			//{
			//	log.Info()<<"CalMidPointList  has  result.................."<<endl;
			//	msg01_CranePLC_Order.setMapMidPointList(mapMidPointList);
			//}	

			OrderCurrentBase orderCurrent;
			orderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);
			

			if(hasCoil == 0)
			{
				msg01_CranePLC_Order.setPlanUpX( targetX );
				msg01_CranePLC_Order.setPlanUpY( targetY );	
				msg01_CranePLC_Order.setMatYard( orderCurrent.getFromStockNO().substr(1,2) );
			} 
			if(hasCoil != 0)
			{
				msg01_CranePLC_Order.setPlanDownX( targetX );
				msg01_CranePLC_Order.setPlanDownY( targetY );	
				msg01_CranePLC_Order.setMatYard( orderCurrent.getToStockNO().substr(1,2) );
			}
			msg01_CranePLC_Order.setMatType( long(1) );
			msg01_CranePLC_Order.setMatWeight( orderCurrent.getMatReqWgt() );
			msg01_CranePLC_Order.setSpace( long(1) );
			msg01_CranePLC_Order.setCrc( long(0) );

			
			log.Debug()<<".................. log out craneOrderCurrent ..................."<<endl;
			msg01_CranePLC_Order.logOutValues();			
			log.Debug()<<".......................................开始向行车PLC下达指令..... MsgEUCR01::getInstance()->SendOutMessage........................................"<<endl;

			if( MsgEUCR01::getInstance()->SendOutMessage_III(msg01_CranePLC_Order) )  /***********/  
			{
				log.Debug()<<"..................... 下达指令成功！  OK !"<<endl;
			}
			else 
			{
				log.Error()<<"..................... sending message ERROR !"<<endl;
			}        
			return ret;
			
	}
	catch(iDA::Exception &x)
	{
		try
		{

			ret=false;

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
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}


