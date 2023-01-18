// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef APP_ORDER_MSG_DEF_H
#define APP_ORDER_MSG_DEF_H

#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>
#include <map>
#include <list>

namespace CLTS
{
	const string P99_ORDER_CREATE = "P99_ORDER_CREATE";
	const string P99_ORDER_REPONSE_RECOMMEND = "P99_ORDER_REPONSE_RECOMMEND";
	const string P99_ORDER_SELECT = "P99_ORDER_SELECT";
	const string P99_ORDER_CANCEL = "P99_ORDER_CANCEL";
	const string P99_ORDER_LIFT_UP = "P99_ORDER_LIFT_UP";
	const string P99_ORDER_LIFT_DOWN = "P99_ORDER_LIFT_DOWN";
	const string P99_ORDER_DISPATCH_ACK = "P99_ORDER_DISPATCH_ACK";

	// 指令创建输入
	struct STRU_P99_ORDER_CREATE
	{
		char szMatNo[32];
		int nOrderType;
		char szCraneNo[32];
		char szToStockNo[32];
	};

	// 指令推荐响应
	struct STRU_P99_ORDER_REPONSE_RECOMMEND
	{
		int requestId;		/*!< 推荐请求流水号 */
		char matNo[32];		/*!< 钢卷号 */
		int xCenter;		/*!< 推荐落卷中心点X (单位mm). */ 
		int yCenter;		/*!< 推荐落卷中心点Y (单位mm). */
		int zCenter;		/*!< 推荐落卷中心点Z (单位mm). */
		int layer;			/*!< 推荐落卷层号. */
		char szStockNo[32];/*!< 库位占用鞍座号 */
	};

	// 指令吊运实绩
	struct STRU_P99_ORDER_OPER
	{
		int nOrderNo;			/*!< 指令编号 */
		char szCraneNo[32];		/*!< 行车号 */
		char szUsername[32];	/*!< 操作者 */
		char szEquipNo[32];		/*!< 设备编号 */
		char szStockNo[32];		/*!< 操作库位 */
		int craneMode;			/*!< 行车模式 */
		int nXCranePos;			/*!< 实绩大车位置 */
		int nyCranePos;			/*!< 实绩小车位置 */
		int nZCranePos;			/*!< 实绩夹钳高度 */
		char szCmdStatus[32];	/*!< 实绩. (0:空闲R:执行S:吊起E:卸下C:取消) */
		int nFlagCheckPlan;		/*!< 与计划比对结果. (0:按计划一致 1:未按计划执行 2:无计划指令) */
	};
	
	// 指令调度应答
	struct STRU_P99_ORDER_DISPATCH_ACK
	{
		int nOrderNo;			/*!< 指令编号 */
		int nAckFlag;			/*!< 应答标记 */
		char szCraneNo[32];		/*!< 行车号 */
	};
};

#endif
