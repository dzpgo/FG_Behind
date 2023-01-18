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
			//19  ���ö�ָ�� 0����ִ��   1��ִ��
			//���ڸ���UC01��ͨ�Žӿڣ������˶�ָ���ֶΣ�������Ӷ�ָ���ʼֵ
			//msg01_CranePLC_Order.setShortCmd(1);
			//2018.8.1 zhangyuhong add 
			//�����м��ָ��״̬  2-�м��  1-����Ŀ���
			msg01_CranePLC_Order.setShortCmd(shortCmd);


			//1.�г���
			msg01_CranePLC_Order.setCraneNO( craneNO );
			//2.ָ���
			msg01_CranePLC_Order.setOrderID( orderNO );	
			//3.ȡ����
			//msg01_CranePLC_Order.setMatWeight(matWeight);
			//4.ȡ������
			//msg01_CranePLC_Order.setMatType(matType);

			////���ת��
			//msg01_CranePLC_Order.setDownRotateAngleSet(downRotateAngle);

			//���ת��
			//msg01_CranePLC_Order.setUpRptateAngleSet(upRotateAngle);

			long canReachX=CranePLCOrderBase::PLC_INT_NULL;

			log.Info()<<"1--------���ÿ����߼������ targetX---------------------------------------"<<endl;
			//��������߼�,�����targetX
			canReachX = targetX;			


			//������ע��-----20230108-----yezhiwei
			//log.Debug()<<"......................��ʼ����·���滮�㷨ʵʩ ArrangeRoute.........................."<<endl;

			////arrange the route from current pos to special point
			//vector<RouteStepPointBase> vectorRoutePoints;
			//log.Debug()<<"  ..... ����·���滮�㷨 arrangeRoute ......" <<endl;

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

			//log.Debug()<<"������ϣ�����vectorRoutePoints.size="<< vectorRoutePoints.size() <<endl;
			//log.Debug()<<"---------------�ƶ�������λ�õĵ�1���� -------------- "<<endl;
			//log.Debug()<<"·����ʼ��X Route Start X = "<< vectorRoutePoints[0].getX();
			//log.Debug()<<"\t ·����ʼ��Y Route Start Y = "<< vectorRoutePoints[0].getY() <<endl;
			//log.Debug()<<"----------------------------------------------------------- "<<endl;


		 //  //the first one is the current point and then there are route steps.
			//if (vectorRoutePoints.size() >= 2    )
			//{

			//	log.Debug()<<"��1����X first step Point_X = "<< vectorRoutePoints[1].getX() ;
			//	log.Debug()<<"\t ��1����Y first step Point_Y = "<< vectorRoutePoints[1].getY() ;

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

			//	log.Debug()<<"��ȫ�������PlanUpZ/PlanDownZ��9...."<<endl;
			//	msg01_CranePLC_Order.setPlanUpZ( CranePLCOrderBase::PLC_INT_NULL );
			//	msg01_CranePLC_Order.setPlanDownZ( CranePLCOrderBase::PLC_INT_NULL );

			//}
			//else				
			//{
			//			log.Error()<<"·���滮�㷨����ʧ�ܣ�vectorRoutePoints.size<2. �޷���ȡ��1����λ��..���г���PlanDownXYZ/PlanUpXYZ����9����.............. ";
			//			log.Info()<<"���ڸĳɲ����·���9ָ���ˣ�ֱ�ӷ���false......"<<endl;
			//			ret = false;
			//			return ret;	 
			//}	

			//log.Info()<<"2--------���� targetX, targetY ����� �м��-------------------------------"<<endl;
			////������Ӽ����м���߼���
			////1.Ҫô��ACTION_COMMON�����
			////2.Ҫô���ò�Ʒ��·������ģ��
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
			log.Debug()<<".......................................��ʼ���г�PLC�´�ָ��..... MsgEUCR01::getInstance()->SendOutMessage........................................"<<endl;

			if( MsgEUCR01::getInstance()->SendOutMessage_III(msg01_CranePLC_Order) )  /***********/  
			{
				log.Debug()<<"..................... �´�ָ��ɹ���  OK !"<<endl;
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


