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

	// ָ�������
	struct STRU_P99_ORDER_CREATE
	{
		char szMatNo[32];
		int nOrderType;
		char szCraneNo[32];
		char szToStockNo[32];
	};

	// ָ���Ƽ���Ӧ
	struct STRU_P99_ORDER_REPONSE_RECOMMEND
	{
		int requestId;		/*!< �Ƽ�������ˮ�� */
		char matNo[32];		/*!< �־�� */
		int xCenter;		/*!< �Ƽ�������ĵ�X (��λmm). */ 
		int yCenter;		/*!< �Ƽ�������ĵ�Y (��λmm). */
		int zCenter;		/*!< �Ƽ�������ĵ�Z (��λmm). */
		int layer;			/*!< �Ƽ������. */
		char szStockNo[32];/*!< ��λռ�ð����� */
	};

	// ָ�����ʵ��
	struct STRU_P99_ORDER_OPER
	{
		int nOrderNo;			/*!< ָ���� */
		char szCraneNo[32];		/*!< �г��� */
		char szUsername[32];	/*!< ������ */
		char szEquipNo[32];		/*!< �豸��� */
		char szStockNo[32];		/*!< ������λ */
		int craneMode;			/*!< �г�ģʽ */
		int nXCranePos;			/*!< ʵ����λ�� */
		int nyCranePos;			/*!< ʵ��С��λ�� */
		int nZCranePos;			/*!< ʵ����ǯ�߶� */
		char szCmdStatus[32];	/*!< ʵ��. (0:����R:ִ��S:����E:ж��C:ȡ��) */
		int nFlagCheckPlan;		/*!< ��ƻ��ȶԽ��. (0:���ƻ�һ�� 1:δ���ƻ�ִ�� 2:�޼ƻ�ָ��) */
	};
	
	// ָ�����Ӧ��
	struct STRU_P99_ORDER_DISPATCH_ACK
	{
		int nOrderNo;			/*!< ָ���� */
		int nAckFlag;			/*!< Ӧ���� */
		char szCraneNo[32];		/*!< �г��� */
	};
};

#endif
