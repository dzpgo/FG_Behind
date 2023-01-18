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


				//1 初始化状态表中的所有信息，在执行完成指令或者取消指令时候使用
	           static bool initialise(string craneNO  );

			   //2 向状态表里面写UACS指令信息，在接收推来的指令或者自己找到新的指令时使用
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
			   //3 更新钢卷尺寸信息
				static bool update_CoilSize_Info(		string craneNO,
																long coilWidth,
																long coilWeight,
																long coilOutDia,
																long coilInDia
															);
				//2018.8.15 zhangyuhong add
				//框架入库变框架上料用
				//更新指令类型和落关参数
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


			   //4 更新起吊参数
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

			   //4.1 更改起吊参数2
			   static bool update_Up_Info_2(
													   string		craneNO,
													   string    fromStockNO,
													   long		planUpX,
													   long		planUpY,
													   long		planUpZ);

				//5 更新落关参数
			   static bool update_Down_Info(string	craneNO,
															string		toStockNO,
															long		planDownX,
															long		planDownY,
															long		planDownZ,
															long		downRotateAngleSet,
															long      floorUpZ,
															long      flagSmallCoil,
															long      floorDownZ);  

				//6 更新指令状态
				static bool update_CMDStatus( string craneNO,string cmdStatus);

				static bool InitPlanUpXYZMatUpScanNO(	string craneNO);
				static bool InitPlanDownXYZMatDownScanNO(	string craneNO);

				//cmdSeq+1
				static bool Update_CmdSeq_Add_1(string craneNO);

				//更新当前重量
				static bool UpdMatCurWgt(string craneNO, long matCurWgt);

				//更新累加重量
				static bool UpdMatActWgt(string craneNO, long matCurWgt);

				static bool Init_ScanDownInfo(	string craneNO);

			   //7 更新材料号，在手动作业时使用，针对遥控模式和司机模式
			   static bool update_MatNO_WhenManu(string craneNO,  string matNO);

			   //8 更新一个新的完整的指令
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


			   //8 查询函数  按照行车号，获得行车当前的指令信息
			   static OrderCurrentBase getData(string craneNO);

			   //2019.4.24 zhangyuhong add
			   //通过写指令方式回登车位
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

			   //20220721 获取扫描起始范围 startXY endXY
			   static bool GetScanAreaXY(string areaType, string areaNO, long& startX, long& endX, long& startY, long& endY);

			   //20220721 更新行车当前指令表中 发送扫描标记 
			   static bool UpdScanSndFlag(string craneNO, string flagName, long flagValue);//flagName: UP-取料点扫描请求 DOWN-放料点扫描请求 RGV-RGV整车扫描请求

			   //更新行车当前指令表中 发送标记 = 0  . 结果标记 = 2  准备再次发送
			   static bool UpdUpSndRcvFlag(string craneNO, long upSndFlag, long upRcvFlag);

			   //插入行车实绩表 uacs_order_oper
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

			   //查询uacs_parking_srs_mat_info 扫描结果
			   static bool SelSRSMatInfoScanResult(long orderNO, 
																					string actionType, 
																					string& scanResult);

			   //查询uacs_parking_srs_car_info  返回车辆扫描数据
			   static bool SelSRSCarInfo(string scanNO, vector<long> vecCarPoint);//vecCarPoint 按顺序放 X1 Y1 Z1 X2 Y2 Z2 X3 Y3 Z3 X4 Y14 Z4  

			   //查询uacs_parking_srs_car_info 扫描结果
			   static bool SelSRSCarInfoScanResult(long orderNO, string& scanResult);

			   //获取停车位定义数据
			   static bool SelParkingInfoDefine(string parkingNO, long& xStart, long& xEnd, long& yStart, long& yEnd);

			   //获取激光设备IP
			   static bool SelCraneSrsIPConfig(string craneNO, string& srsIP);

			   //获取到UL01evtag后，更新起料  放料 扫描号和 起料放料点
			   static bool UpdOrderCurrentUpScanNOAndPoint(string craneNO, string matUpScanNO, long planUpX, long planUpY, long planUpZ);
			   static bool UpdOrderCurrentDownScanNOAndPoint(string craneNO, string matDownScanNO, long planDownX, long planDownY, long planDownZ);

			   //获取到UL02evtag后，更新carScanNO
			   static bool UpdOrderCurrentCarScanNO(string craneNO, string carScanNO);

			   //根据指令号获取UACS_CAR_SCAN_ORDER_REC 相关数据
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

			   //更新 UACS_CAR_SCAN_ORDER_REC 中SCAN_ACTION_FLAG
			   static bool UpdScanActionFlag(long orderNO, string scanActionFlag);


			   //更新 UACS_CAR_SCAN_ORDER_REC 中actStartX actStartY=DB_INT_NULL
			   static bool InitActStartXYInCarScanOrderRec(long orderNO);

			   //更新UACS_CAR_SCAN_ORDER_REC中的 actstartXY
			   static bool UpdActStartXYInCarScanOrderRec(long orderNO, long actStartX, long actStartY);

			   //更新UACS_CAR_SCAN_ORDER_REC中的 actendXY
			   static bool UpdActEndXYInCarScanOrderRec(long orderNO, long actEndX, long actEndY);

			   //根据orderNO删除记录在UACS_CAR_SCAN_ORDER_REC
			   static bool DelCarScanOrderRecByOrderNO(long orderNO);

			   //根据orderNO获取scanActionFlag 在UACS_CAR_SCAN_ORDER_REC
			   static bool SelFlagInCarScanOrderRec(long orderNO, string& scanActionFlag);

			   //插入记录到 UACS_CAR_SCAN_ORDER_REC
			   static bool InsCarScanOrderRec(long orderNO, string parkingNO, long planStartX, long planStartY, long planEndX, long planEndY, string moveDir);
 
		};




}
#endif

