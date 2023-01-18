#pragma once
#ifndef _Adapter_UACS_CRANE_ORDER_CURRENT_
#define _Adapter_UACS_CRANE_ORDER_CURRENT_

#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "OrderCurrentBase.h"
#include "ACTION_COMMON_FUNCTION.h"

namespace Monitor
{


		class Adapter_UACS_CRANE_ORDER_CURRENT
		{


		public:
				Adapter_UACS_CRANE_ORDER_CURRENT(void);

				~Adapter_UACS_CRANE_ORDER_CURRENT(void);

				typedef map<int, vector<string> > mapOrderQueue;


				//1 ��ʼ��״̬���е�������Ϣ����ִ�����ָ�����ȡ��ָ��ʱ��ʹ��
	           static bool initialise(string craneNO  );

			   //2 ��״̬������дUACSָ����Ϣ���ڽ���������ָ������Լ��ҵ��µ�ָ��ʱʹ��
	           static bool update_UACS_Crane_Order_Info( string	craneNO,  
																								long orderNO,
																								string	bayNO,  
																								string	matNO, 
																								long orderType, 
																								long orderPriority, 
																								string  fromStockNO,
																								string	toStockNO,
																								string  cmdStatus
																					  );
			   //3 ���¸־�ߴ���Ϣ
				static bool update_CoilSize_Info(		string craneNO,
																long coilWidth,
																long coilWeight,
																long coilOutDia,
																long coilInDia
															);
				//2018.8.15 zhangyuhong add
				//���������������
				//����ָ�����ͺ���ز���
				static bool update_Order_Type_Down_Info(
																								string		craneNO, 
																								string		orderType, 
																								string		toStockNO,
																								long		planDownX,
																								long		planDownY,
																								long		planDownZ,
																								long		downRotateAngleSet,
																								long      floorUpZ,
																								long      flagSmallCoil,
																								long      floorDownZ);


			   //4 �����������
			   static bool update_Up_Info(
														string		craneNO,
														string    fromStockNO,
														long		planUpX,
														long		planUpY,
														long		planUpZ,
														long		upRotateAngleSet,
														long		clampWidthSet,
														long      coilWidth,
														long      coilOutDia,
														long      coilInDia,
														long      floorUpZ,
														long      flagSmallCoil,
														long      floorDownZ);

			   //4.1 �����������2
			   static bool update_Up_Info_2(
													   string		craneNO,
													   string    fromStockNO,
													   long		planUpX,
													   long		planUpY,
													   long		planUpZ);

				//5 ������ز���
			   static bool update_Down_Info(string	craneNO,
															string		toStockNO,
															long		planDownX,
															long		planDownY,
															long		planDownZ,
															long		downRotateAngleSet,
															long      floorUpZ,
															long      flagSmallCoil,
															long      floorDownZ);  

				//6 ����ָ��״̬
				static bool update_CMDStatus( string craneNO,string cmdStatus);

				static bool InitPlanUpXYZMatUpScanNO(	string craneNO);
				static bool InitPlanDownXYZMatDownScanNO(	string craneNO);

				//cmdSeq+1
				static bool Update_CmdSeq_Add_1(string craneNO);

				//���µ�ǰ����
				static bool UpdMatCurWgt(string craneNO, long matCurWgt);

				//�����ۼ�����
				static bool UpdMatActWgt(string craneNO, long matCurWgt);

				static bool Init_ScanDownInfo(	string craneNO);

			   //7 ���²��Ϻţ����ֶ���ҵʱʹ�ã����ң��ģʽ��˾��ģʽ
			   static bool update_MatNO_WhenManu(string craneNO,  string matNO);

			   //8 ����һ���µ�������ָ��
			   static bool receive_A_NewCraneOrder(long orderNO, 
																					   string bayNO, 
																					   string matCode, 
																					   string compCode, 
																					   string matType, 
																					   long matReqWgt, 
																					   long matActWgt, 
																					   long matCurWgt, 
																					   string orderType, 
																					   long orderPriority, 
																					   string fromStockNO, 
																					   string toStockNO, 
																					   string cmdStatus, 
																					   long cmdSeq, 
																					   string craneNO, 
																					   string carScanNO, 
																					   string matUpScanNO, 
																					   long planUpX, 
																					   long planUpY, 
																					   long planUpZ, 
																					   long upRotateAngle, 
																					   string matDownScanNO, 
																					   long planDownX, 
																					   long planDownY, 
																					   long planDownZ, 
																					   long downRotateAngle);


			   //8 ��ѯ����  �����г��ţ�����г���ǰ��ָ����Ϣ
			   static OrderCurrentBase getData(string craneNO);

			   //2019.4.24 zhangyuhong add
			   //ͨ��дָ�ʽ�صǳ�λ
			   static bool receive_BoardingCraneOrder(string	craneNO,  
																					   long		orderNO,
																					   string	bayNO,  
																					   string	matNO, 
																					   string	orderType, 
																					   long		orderPriority, 
																					   string    fromStockNO,
																					   string	toStockNO,
																					   string    cmdStatus,
																					   long		planUpX,
																					   long		planUpY,
																					   long		planUpZ,
																					   long		upRotateAngleSet,
																					   long		clampWidthSet,
																					   long		planDownX,
																					   long		planDownY,
																					   long		planDownZ,
																					   long		downRotateAngleSet,
																					   long		 coilWidth,
																					   long			coilWeight,
																					   long			coilOutDia,
																					   long			coilInDia,
																					   long      floorUpZ,
																					   long      flagSmallCoil,
																					   long      floorDownZ);


			   static bool getStautsNot1Order(string craneNO);

			   //20220721 ��ȡɨ����ʼ��Χ startXY endXY
			   static bool GetScanAreaXY(string areaType, string areaNO, long& startX, long& endX, long& startY, long& endY);

			   //20220721 �����г���ǰָ����� ����ɨ���� 
			   static bool UpdScanSndFlag(string craneNO, string flagName, long flagValue);//flagName: UP-ȡ�ϵ�ɨ������ DOWN-���ϵ�ɨ������ RGV-RGV����ɨ������

			   //�����г���ǰָ����� ���ͱ�� = 0  . ������ = 2  ׼���ٴη���
			   static bool UpdUpSndRcvFlag(string craneNO, long upSndFlag, long upRcvFlag);

			   //�����г�ʵ���� uacs_order_oper
			   static bool InsOrderOper(long orderNO, 
															  string orderType, 
															  string bayNO, 
															  string matCode, 
															  string compCode, 
															  string matType, 
															  long matReqWgt, 
															  long matCurWgt, 
															  long hasCoilWgt, 
															  string fromStockNO, 
															  string toStockNO, 
															  string stockNO, 
															  string cmdStatus, 
															  long cmdSeq, 
															  long planX, 
															  long planY, 
															  long planZ, 
															  long actX, 
															  long actY, 
															  long actZ, 
															  string craneMode );

			   //��ѯuacs_parking_srs_mat_info ɨ����
			   static bool SelSRSMatInfoScanResult(long orderNO, 
																					string actionType, 
																					string& scanResult);

			   //��ѯuacs_parking_srs_car_info  ���س���ɨ������
			   static bool SelSRSCarInfo(string scanNO, vector<long> vecCarPoint);//vecCarPoint ��˳��� X1 Y1 Z1 X2 Y2 Z2 X3 Y3 Z3 X4 Y14 Z4  

			   //��ѯuacs_parking_srs_car_info ɨ����
			   static bool SelSRSCarInfoScanResult(long orderNO, string& scanResult);

			   //��ȡͣ��λ��������
			   static bool SelParkingInfoDefine(string parkingNO, long& xStart, long& xEnd, long& yStart, long& yEnd);

			   //��ȡ�����豸IP
			   static bool SelCraneSrsIPConfig(string craneNO, string& srsIP);

			   //��ȡ��UL01evtag�󣬸�������  ���� ɨ��ź� ���Ϸ��ϵ�
			   static bool UpdOrderCurrentUpScanNOAndPoint(string craneNO, string matUpScanNO, long planUpX, long planUpY, long planUpZ);
			   static bool UpdOrderCurrentDownScanNOAndPoint(string craneNO, string matDownScanNO, long planDownX, long planDownY, long planDownZ);

			   //��ȡ��UL02evtag�󣬸���carScanNO
			   static bool UpdOrderCurrentCarScanNO(string craneNO, string carScanNO);

			   //����ָ��Ż�ȡUACS_CAR_SCAN_ORDER_REC �������
			   static bool SelCarScanOrderRec(long orderNO, 
																		   string& parkingNO, 
																		   long& planStartX, 
																		   long& planStartY, 
																		   long& planEndX, 
																		   long& planEndY, 
																		   long& actStartX, 
																		   long& actStartY, 
																		   long& actEndX, 
																		   long& actEndY, 
																		   string& moveDir, 
																		   string& scanActionFlag );

			   //���� UACS_CAR_SCAN_ORDER_REC ��SCAN_ACTION_FLAG
			   static bool UpdScanActionFlag(long orderNO, string scanActionFlag);


			   //���� UACS_CAR_SCAN_ORDER_REC ��actStartX actStartY=DB_INT_NULL
			   static bool InitActStartXYInCarScanOrderRec(long orderNO);

			   //����UACS_CAR_SCAN_ORDER_REC�е� actstartXY
			   static bool UpdActStartXYInCarScanOrderRec(long orderNO, long actStartX, long actStartY);

			   //����UACS_CAR_SCAN_ORDER_REC�е� actendXY
			   static bool UpdActEndXYInCarScanOrderRec(long orderNO, long actEndX, long actEndY);

			   //����orderNOɾ����¼��UACS_CAR_SCAN_ORDER_REC
			   static bool DelCarScanOrderRecByOrderNO(long orderNO);

			   //����orderNO��ȡscanActionFlag ��UACS_CAR_SCAN_ORDER_REC
			   static bool SelFlagInCarScanOrderRec(long orderNO, string& scanActionFlag);

			   //�����¼�� UACS_CAR_SCAN_ORDER_REC
			   static bool InsCarScanOrderRec(long orderNO, string parkingNO, long planStartX, long planStartY, long planEndX, long planEndY, string moveDir);
 
		};




}
#endif

