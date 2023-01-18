#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>
#include "iDA/DataTime.h"
#include "utility/CDateTime.h"

namespace ZJCS
{
	namespace Common
	{
		const string cfEventValue="�¼�ֵ:";
		const string cfSuccess="�ɹ�";
		const string cfFail="ʧ��";

		typedef vector<string> ArrayString;


		//======================================================

		typedef struct OutOrder
		{
			string MAT_NO;
			string PLAN_NO;
			string REQUIRE_TIME;
		} dt_OutOrder;

		typedef struct UserInfo
		{
			string User_NO;
			string User_Name;
			string Password;
		} dt_UserInfo;

		typedef struct MaterialDetail
		{
			string  PLAN_NO;
			string  MANUFACT_UNIT_CODE;
			string	MAT_NO;
			string	OUT_MAT_NO;
			string	CONFIRM_NO;
			string	GOODS_CODE;
			string	GOODS_NAME;
			string	CONTRACT_ID;
			string	PONO;
			int	LENGTH;
			int	WIDTH;
			int	THICK;
			int	INTERNAL_DIAMETER;
			int	EXTERNAL_DIAMETER;
			int	NET_WEIGHT;
			int	GROSS_WEIGHT;
			string	PACKETCODE;
			string STORE_PLACE;
		} dt_MaterialDetail;		//������Ϣ

		typedef vector<MaterialDetail> dt_MATs;

		typedef struct InPlan
		{
			string PLAN_NO;
			string FLAG_STRAIGHT_FILLING;
			string MANUFACT_UNIT_CODE;
			string COMMIT_NO;
			string PLAN_TIME;
			string OUTSTORE_ID;
			string INSTORE_ID;
			int GROSS_WEIGHT;
			int NET_WEIGHT;
			int PIECE;
			string PLAN_TYPE;
			string MAT_TYPE;
			string SHIP_LOT_NUM;
			string SHIP_CNAME;
			string REMARK;
		} dt_InPlan;				//���ƻ�

		typedef struct InPlanDetail
		{
			string PLAN_NO;
			string	MANUFACT_UNIT_CODE;
			int	COUNT;
			dt_MATs MATs;

		} dt_InPlanDetail;			//���ƻ���ϸ

		typedef struct OutPlan
		{
			string PLAN_NO;
			string FLAG_STRAIGHT_FILLING;
			string MANUFACT_UNIT_CODE;
			string OUTSTORE_ID;
			string INSTORE_ID;
			string SHIP_LOT_NUM;
			string SHIP_CNAME;
			string HAVEN;
			string COMMIT_NO;
			string PLAN_TIME;
			int PIECE;
			int GROSS_WEIGHT;
			int NET_WEIGHT;
			string TRANS_TYPE;
			string MAT_TYPE;
		} dt_OutPlan;				//����ƻ�

		typedef struct OutPlanDetail
		{
			string PLAN_NO;
			string	MANUFACT_UNIT_CODE;
			int	COUNT;
			dt_MATs MATs;
		} dt_OutPlanDetail;			//����ƻ���ϸ

		typedef struct CarLoading
		{
			string	SYSTEM_CODE;
			string	FRAME_NO;
			string	Process_NO;		//��ˮ��
			string	Parking_NO;
			string	OUTSTORE_ID;
			string	INSTORE_ID;
			string	FINISH_TIME;
			string	UL_FLAG;

		} dt_CarLoading;		//��ܲ���

		typedef struct CarLoadingDetail
		{
			string	Process_NO;		//��ˮ��
			string	MAT_NO;
			string	INSTORE_ID;
			string	LAYER_NO;
			int	NET_WEIGHT;
			string	PLAN_NO;
			string	LABEL_NO;
			string	PLACE_NO;
			int	X_POINT;
			int	Y_POINT;
			string	RecommendSite;

		} dt_CarLoadingDetail;		//��ܲ�����ϸ

		//======================================================
		
		typedef struct PT_Common
		{
			string	Store_ID;
			string	PT_ID;
			string	Shift;
			string	Crew;
			string	Operator;
			string	Time_Oper;
		} dt_PTCommon;		//�ֳֻ������Ϣ

		typedef struct Unit
		{
			string	Store_ID;
			string	Location;
			string	BigArea_NO;
			string	Unit_No;
		} dt_Unit;			//��λ��Ϣ

		typedef struct MATOnSite
		{
			string Layer_NO;
			string MaterialNO;
		} dt_MATOnSite;

		typedef vector<dt_MATOnSite> SlabOnUnits;		//���϶�λ�����嵥		�����̿�ӿ�

		typedef struct ActPDetail
		{
			string	manufact_unit_code;
			string	plan_no;
			string	mat_no;
			string	place_no;
			int	layer_no;
			string	time;
			string	quality;
		} dt_ActPDetail;

		typedef vector<dt_ActPDetail> ActPDetails;

		typedef struct ActuralPerformance
		{
			string	machine_id;
			string	send_time;
			string	shiftid;
			string	shiftno;
			string	store_id;			//���ʱ�����𣬳����Ǳ�ʾ�����
			string	rec_creator;
			string	machine_no;
			string	sling_no3;
			string	sling_no4;
			string	sling_no;
			string	frame_no;
			string	ponchos1;
			string	ponchos2;
			string	flag;
			string	zzflag;
			int	count;
		} dt_ActP;

#pragma region ���ķ���
		typedef struct SendInfo
		{
			int nid;
			string cMsgid;
			string cMSGKey;
			string cCreateTime;
			int nStatus;			//1.�����ͣ�0.������ɣ�100.����ʧ��
		} dt_SendInfo;
		typedef vector<dt_SendInfo> SendInfos;

		typedef struct dt_CSKH53_DETAIL
		{	
			string cMANUFACT_UNIT_CODE;
			string cPLAN_NO;
			string cMAT_NO;
			string cQUALITY ;
			string cPLACE_NO;			//����λ
			string cTIME;
			int nLAYER_NO;				//���

		} dtCSKH53it;

		typedef vector<dtCSKH53it> vctCSKH53ITs;

		typedef struct dt_CSKH53
		{
			string cMACHINE_ID;
			string cSEND_TIME;
			string cSHIFTNO ;
			string cSHIFTID ;
			string cSTORE_ID ;
			string cREC_CREATOR ;
			string cMACHINE_NO ;
			string cSLING_NO3 ;
			string cSLING_NO4 ;
			string cSLING_NO ;
			string cFRAME_NO ;
			string cFLAG;
			int nCOUNT;
			vctCSKH53ITs vItems;
		} dtCSKH53;

		typedef struct dt_CSKH54_DETAIL
		{	
			string cMANUFACT_UNIT_CODE;
			string cPLAN_NO;
			string cMAT_NO;
			string cQUALITY ;
			string cPLACE_NO;
			string cTIME;
			int nLAYER_NO;

		} dtCSKH54it;

		typedef vector<dtCSKH54it> vctCSKH54ITs;

		typedef struct dt_CSKH54
		{
			string cMACHINE_ID;
			string cSEND_TIME;
			string cSHIFTNO ;
			string cSHIFTID ;
			string cSTORE_ID ;
			string cREC_CREATOR ;
			string cMACHINE_NO ;
			string cSLING_NO3 ;
			string cSLING_NO4 ;
			string cSLING_NO ;
			string cFRAME_NO ;
			string cPONCHOS1;
			string cPONCHOS2;
			string cFLAG;
			string SHIFTID;
			string ZZFLAG;
			int nCOUNT ;
			vctCSKH54ITs vItems;
		} dtCSKH54;

		typedef struct dt_CSKH58_DETAIL
		{
			string	MAT_NO;
			string	INSTORE_ID;
			string	LAYER_NO;
			int	NET_WEIGHT;
			string	PLAN_NO;
			string	LABEL_NO;
			string	PLACE_NO;
			int	X_POINT;
			int	Y_POINT;
			string OPERATOR;
			string OPER_TIME;
		} dtCSKH58it;		//��ܲ�����ϸ2L3

		typedef vector<dtCSKH58it> vctCSKH58ITs;

		typedef struct dt_CSKH58
		{
			string	SYSTEM_CODE;
			string	FRAME_NO;
			string	Parking_NO;
			string	OUTSTORE_ID;
			string	FINISH_TIME;
			string	UL_FLAG;
			vctCSKH58ITs vItems;
		} dtCSKH58;		//��ܲ���2L3



#pragma endregion ���ķ���



	}
}