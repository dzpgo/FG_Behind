/*********************************************************************
*		
*  文      件:    ACTION_COMMON_FUNCTION.h   		
*
*
*  概述：
*        ：行车ACTION动作所调用的公共函数库

*
*  版本历史		
*      2017年04月建立
*********************************************************************/
#pragma once
#ifndef  _ACTION_COMMON_FUNCTION_
#define  _ACTION_COMMON_FUNCTION_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "CraneOrderCurrentBase.h"
#include "OrderCurrentBase.h"
#include "OrderQueueBase.h"
#include "CranePLCStatusBase.h"

#include "CranePLCOrderBase.h"
#include "RouteStepPointBase.h"
#include "SafetyArea_Bay.h"

#include "MsgEUCR01.h"

#include "JUDGE_BEFORE_MOVING.h"
#include "EvadeCancelSender.h"
#include "EvadeRequestSender.h"

#include "SafteyAreaBase.h"

#include "Adapter_UACS_CRANE_MOVEORDER_MSG.h"
#include "Adapter_UACS_YARDMAP_STOCK_INFO.h"

#include "CraneEvadeRequestBase.h"

namespace Monitor
{



	class ACTION_COMMON_FUNCTION
	{

	public:
		ACTION_COMMON_FUNCTION(void );
		~ACTION_COMMON_FUNCTION(void );

		typedef map<long, vector<long> > mapTurnCarPosXYZ;

	public:
		
	
		//2018.7.1 zhangyuhong add
		//定义WMS行车控制模块的报警tag点名称
		//由于要区分行车号，所以只定义后缀部分，前缀部分由行车好填补
		const static string TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS;

		//2018.7.1 zhangyuhong add
		//WMS行车控制的报警代码定义一览
		const static string WMS_CRANE_ALARM_CODE_0;	
		const static string WMS_CRANE_ALARM_CODE_8003;
		const static string WMS_CRANE_ALARM_CODE_8004;
		const static string WMS_CRANE_ALARM_CODE_8005;
		const static string WMS_CRANE_ALARM_CODE_8006;
		const static string WMS_CRANE_ALARM_CODE_8007;
		const static string WMS_CRANE_ALARM_CODE_8008;
		const static string WMS_CRANE_ALARM_CODE_8009;
		const static string WMS_CRANE_ALARM_CODE_8010;
		const static string WMS_CRANE_ALARM_CODE_8011;
		const static string WMS_CRANE_ALARM_CODE_8012;
		const static string WMS_CRANE_ALARM_CODE_8013;
		const static string WMS_CRANE_ALARM_CODE_8014;
		const static string WMS_CRANE_ALARM_CODE_8015;
		const static string WMS_CRANE_ALARM_CODE_8016;
		const static string WMS_CRANE_ALARM_CODE_8017;
		const static string WMS_CRANE_ALARM_CODE_8018;
		const static string WMS_CRANE_ALARM_CODE_8019;


		const static string WMS_CRANE_ALARM_CODE_8023;
		const static string WMS_CRANE_ALARM_CODE_8024;
		const static string WMS_CRANE_ALARM_CODE_8025;
		const static string WMS_CRANE_ALARM_CODE_8026;
		const static string WMS_CRANE_ALARM_CODE_8027;
		const static string WMS_CRANE_ALARM_CODE_8028;
		const static string WMS_CRANE_ALARM_CODE_8029;
		const static string WMS_CRANE_ALARM_CODE_8030;
		const static string WMS_CRANE_ALARM_CODE_8031;
		const static string WMS_CRANE_ALARM_CODE_8032;
		const static string WMS_CRANE_ALARM_CODE_8033;
		const static string WMS_CRANE_ALARM_CODE_8034;
		const static string WMS_CRANE_ALARM_CODE_8035;
		const static string WMS_CRANE_ALARM_CODE_8036;
		const static string WMS_CRANE_ALARM_CODE_8037;
		const static string WMS_CRANE_ALARM_CODE_8038;
		const static string WMS_CRANE_ALARM_CODE_8039;
		const static string WMS_CRANE_ALARM_CODE_8040;
		const static string WMS_CRANE_ALARM_CODE_8041;
		const static string WMS_CRANE_ALARM_CODE_8042;
		const static string WMS_CRANE_ALARM_CODE_8043;
		const static string WMS_CRANE_ALARM_CODE_8044;
		const static string WMS_CRANE_ALARM_CODE_8045;
		const static string WMS_CRANE_ALARM_CODE_8046;
		const static string WMS_CRANE_ALARM_CODE_8047;
		const static string WMS_CRANE_ALARM_CODE_8048;
		const static string WMS_CRANE_ALARM_CODE_8049;
		const static string WMS_CRANE_ALARM_CODE_8050;
		const static string WMS_CRANE_ALARM_CODE_8051;
		const static string WMS_CRANE_ALARM_CODE_8052;
		const static string WMS_CRANE_ALARM_CODE_8053;
		const static string WMS_CRANE_ALARM_CODE_8054;
		const static string WMS_CRANE_ALARM_CODE_8055;
		const static string WMS_CRANE_ALARM_CODE_8056;
		const static string WMS_CRANE_ALARM_CODE_8057;
		const static string WMS_CRANE_ALARM_CODE_8058;
		

		//行车紧停的报警情况代码
		const static string WMS_CRANE_ALARM_CODE_8101;
		const static string WMS_CRANE_ALARM_CODE_8102;
		const static string WMS_CRANE_ALARM_CODE_8103;
		const static string WMS_CRANE_ALARM_CODE_8104;
		const static string WMS_CRANE_ALARM_CODE_8105;
		const static string WMS_CRANE_ALARM_CODE_8106;
		//----新增
		const static string WMS_CRANE_ALARM_CODE_8107;
		const static string WMS_CRANE_ALARM_CODE_8108;
		const static string WMS_CRANE_ALARM_CODE_8109;
		const static string WMS_CRANE_ALARM_CODE_8110;
		const static string WMS_CRANE_ALARM_CODE_8111;
		const static string WMS_CRANE_ALARM_CODE_8112;
		const static string WMS_CRANE_ALARM_CODE_8113;
		const static string WMS_CRANE_ALARM_CODE_8114;
		const static string WMS_CRANE_ALARM_CODE_8115;
		const static string WMS_CRANE_ALARM_CODE_8116;

		const static string WMS_CRANE_ALARM_CODE_8117;
		const static string WMS_CRANE_ALARM_CODE_8118;

		const static string WMS_CRANE_ALARM_CODE_8121;
		const static string WMS_CRANE_ALARM_CODE_8122;

		const static string WMS_CRANE_ALARM_CODE_8123;
		const static string WMS_CRANE_ALARM_CODE_8124;

		const static string WMS_CRANE_ALARM_CODE_8125;
		const static string WMS_CRANE_ALARM_CODE_8126;
		const static string WMS_CRANE_ALARM_CODE_8127;

		const static string WMS_CRANE_ALARM_CODE_8128;
		const static string WMS_CRANE_ALARM_CODE_8129;

		const static string WMS_CRANE_ALARM_CODE_8130;

		const static string WMS_CRANE_ALARM_CODE_8131;
		const static string WMS_CRANE_ALARM_CODE_8132;

		//机组检修模式故障代码
		const static string WMS_CRANE_ALARM_CODE_8201;
		const static string WMS_CRANE_ALARM_CODE_8202;
		const static string WMS_CRANE_ALARM_CODE_8203;
		const static string WMS_CRANE_ALARM_CODE_8204;
		const static string WMS_CRANE_ALARM_CODE_8205;
		const static string WMS_CRANE_ALARM_CODE_8206;
		const static string WMS_CRANE_ALARM_CODE_8207;

		//靠近围栏的库区库位校验
		const static string WMS_CRANE_ALARM_CODE_8301;
		const static string WMS_CRANE_ALARM_CODE_8302;
		const static string WMS_CRANE_ALARM_CODE_8303;
		const static string WMS_CRANE_ALARM_CODE_8304;
		const static string WMS_CRANE_ALARM_CODE_8305;
		const static string WMS_CRANE_ALARM_CODE_8306;
		const static string WMS_CRANE_ALARM_CODE_8307;
		const static string WMS_CRANE_ALARM_CODE_8308;

		const static string WMS_CRANE_ALARM_CODE_8401;
		const static string WMS_CRANE_ALARM_CODE_8402;

	public:

		static bool CustomOfficer_ForAllActions_1(string craneNO,
																						string bayNO,
																						OrderCurrentBase orderCurrent, 
																						CranePLCStatusBase cranePLCStatus);

		//2018.2.28 zhangyuhong add
		//执行避让指令时的检查：检查当前避让指令表中的行车号和当前行车号是否一致
		static bool CustomOfficer_ForAllActions_2(string craneNO,
																		string bayNO,
																		CraneEvadeRequestBase craneEvadeRequest, 
																		CranePLCStatusBase cranePLCStatus);

		//custom offiecer------ to check auto mode and ready
		static bool CustomOffice_Is_Auto_Ready_AskPlan(string craneNO,
																					CranePLCStatusBase cranePLCStatus);

		//assistant helper------ to check whether i have arrived the target point
		static bool Assistant_Is_PlaceArrived(long xCurrent, long yCurrent, long xTarget, long yTarget);

		//2019.7.1 zhangyuhohng add
		static bool Assistant_Is_PlaceArrived_By_Distance(long xCurrent, long yCurrent, long xTarget, long yTarget, long xDistance, long yDistance);

		//20200427 zhangyuhong add
		static bool Assistant_Is_PlaceArrived_X_By_Distance(long xCurrent, long xTarget, long xDistance);

		//20200427 zhangyuhong add
		static bool Assistant_Is_PlaceArrived_Y_By_Distance(long yCurrent, long yTarget, long xDistance);

		//2018.10.23 zhangyuhong add
		static bool Assistant_Is_PlaceArrived_X(long xCurrent, long xTarget);

		//2019.6.15 zhangyuhong add
		static bool Assistant_Is_PlaceArrived_Y(long yCurrent, long yTarget);

		//2017.10.1 zhangyuhong add
		static bool Assistant_Is_PlaceClampArrived(long zCurrnet, long zTarget, string coilUpDown);

		//2017.12.6 zhangyuhong add
		//纯粹是为了区分有指令不按指令作业
		static bool Assistant_Is_ZValueArrived(long zCurrent, long zTarget);

		//assistant helper------ to create and download a crane moving order 
		static bool Assistant_DownLoad_Moving_Order(string craneNO, long orderNO, long currentX, long currentY, long targetX, long targetY, long hasCoil);

		//assistant helper------to create and download a coil up order on the sopt
		static bool Assistant_DownLoad_Coil_Up_Order_On_Spot(string craneNO, 
																												long orderID, 
																												long matWeight, 
																												long matType, 
																												long planUpX, 
																												long planUpY, 
																												long planUpZ, 
																												long upRotateAngleSet);

		//assistant helper------to create and download a coil down order on the spot
		static bool Assistant_DownLoad_Coil_Down_Order_On_Spot(string craneNO, 
																													long orderID, 
																													long matWeight, 
																													long matType, 
																													long planDownX, 
																													long planDownY, 
																													long planDownZ, 
																													long downRotateAngleSet);

		//Actions list output
		static bool Action_OutPut_Actions( string craneNO, string tagValue );

		//Actions successed list output
		static bool Action_OutPut_ActionsSuccessed( string craneNO, string tagValue );

		//Action stop result output
		static bool Action_OutPut_StopResult( string craneNO, string tagValue );		

		//zhangyuhong add
		//设置tag点
		static bool SetTagValue(string craneNO, string tagNamePart, string tagValue);

		//zhangyuhong add
		//获取tag点值
		static string GetTagValue(string craneNO, string tagNamePart);	

		 //根据tag点名称获取tag点的值
		 static string getTagValue(string tagName);

		 //根据tag点名称设置tag点的值
		 static bool setTagValue(string tagName, string tagValue);

		 //2019.6.11 zhangyuhong add
		 static bool setEVTag(string tagName, string tagValue); 
		 static bool setEVTagWithCraneNO(string craneNO, string tagNamePart, string tagValue);

		 //20191106 zhangyuhong add
		 static string getNeighborCrane( CranePLCStatusBase cranePLCStatusCurrent, long targetX);

		 static bool canSendMoveAtLastStep(CranePLCStatusBase cranePLCStatusCurrent, long targetX, string neighborCraneNO);

		 //20191122 zhangyuhong add
		 //return = false 没有邻车  ；  true  有邻车
		 static bool findNeighborCrane(CranePLCStatusBase cranePLCStatusCurrent, CranePLCStatusBase cranePLCStatusLast, string& neighborCraneNO);

		 //20201102 zhangyuhong add
		 //0-不动   1-正向  2-负向
		 static long getXdirValue(long xPDir, long xNDir);

		 //20191122 zhangyuhong add
		 //根据行车号读取行车当前的targetpos的tag点，获取行车当前目的位
		 static long targetXByCraneNO(CranePLCStatusBase cranePLCStatusCurrent);

		 //20191122 zhangyuhong add
		 //实时防范2车相撞
		 //ret = true  则存在撞车风险
		 //增加目标X与实际方向相反标记：wrongXDirFlag   0  正常 ；   1 相反
		 //2020914 zhangyuyhong add
		 //增加cranePLCStautsLast 参数
		 static bool craneWillCrash(CranePLCStatusBase cranePLCStatusCurrent, CranePLCStatusBase cranePLCStatusLast, long&  wrongXDirFlag);

		 //20200102 zhangyuhongadd
		 //循环nCycle周期，每个周期1秒，发送行车停止指令
		 static void sendStopMsg2CraneCycle(string craneNO, long orderNO, long nCycle);

		 //20200113 zhangyuhong add
		 //send reset msg
		 static void tryToSendResetMsg(string craneNO);

		 //20220721 zhangyuhong add
		 //获取发送激光扫描请求电文tag点
		 //场地扫描请求
		 static bool SrsScanReqTag4UL01(string orderType, 
																	string craneNO,  
																	string updownFlag, 
																	long scanStartX, 
																	long scanEndX, 
																	long scanStartY, 
																	long scanEndY, 
																	long orderNO, 
																	string areaNO, 
																	CranePLCStatusBase cranePLCStatus, 
																	string& EVTagName, 
																	string& EVTagValue);

		 //20220722 zhangyuhong add
		 //计算中间点
		 static bool CalMidPointList(string bayNO, 
															long currentX, 
															long currentY, 
															long targetX, 
															long targetY, 
															map<long, map<string, long> >& mapMidPointList);

		 static bool GetCarScanStartEndP(string parkingNO, 
																	long& planStartX, 
																	long& planStartY, 
																	long& planEndX, 
																	long& planEndY, 
																	string& moveDir );

		 //20220922 zhangyuhong add
		 //装车是否结束处理
		 static bool CoilDownIsOverInFinishJob(CranePLCStatusBase cranePLCStatus, OrderCurrentBase orderCurrent);
		 

		 


	};



}

#endif