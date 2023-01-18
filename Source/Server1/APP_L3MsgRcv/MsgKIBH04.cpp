#include "MsgKIBH04.h"
#include "L3PlanInfo.h"
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;

MsgKIBH04*  MsgKIBH04::m_pMsgKIBH04 = NULL;


MsgKIBH04::MsgKIBH04() 
{
	msgId="KIBH04";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgKIBH04 :: ~MsgKIBH04(void)
{

	delete m_pMsgKIBH04;


}

MsgKIBH04* MsgKIBH04::getInstance(void)
{
	if (m_pMsgKIBH04 == NULL)
	{
		m_pMsgKIBH04 = new MsgKIBH04;
	}
	return m_pMsgKIBH04;
}

ByteSeq MsgKIBH04::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgKIBH04 :: HandleMessage()";
	ByteSeq ret;
	LOG log(functionName, LogFileName);	

	try
	{
		// ��ȡpowertrans���Ľṹ
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			sdTrim = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			readSmartDataSuccessed=true;
		}

		//��ȡԭʼ�ֽ���
		sd.readFrom(ParamBuffer);
		log.Info()<<"....................................................log of samrt data..................................................."<<endl;
		string temp = "";

		//1		�ƻ���
		temp = sd["PLAN_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["PLAN_NO"] = temp;
		log.Info()<<"PLAN_NO="<<sdTrim["PLAN_NO"].toString()<<endl;

		//2		�ϲۺ�
		temp = sd["HOPPER_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["HOPPER_NO"] = temp;
		log.Info()<<"HOPPER_NO="<<sdTrim["HOPPER_NO"].toString()<<endl;

		//3		ʵ�ʳ�������
		temp = sd["MAT_NET_WT"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_NET_WT"] = temp;
		log.Info()<<"MAT_NET_WT="<<sdTrim["MAT_NET_WT"].toInt()<<endl;

		////4		���������
		//temp = sd["WEIGH_APP_NO"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["WEIGH_APP_NO"] = temp;
		//log.Info()<<" WEIGH_APP_NO="<<sdTrim["WEIGH_APP_NO"].toString()<<endl;

		////5		��������ʱ��
		//temp = sd["WEIGH_APP_TIME"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["WEIGH_APP_TIME"] = temp;
		//log.Info()<<"WEIGH_APP_TIME="<<sdTrim["WEIGH_APP_TIME"].toString()<<endl;

		////6		������
		//temp = sd["REC_CREATOR"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["REC_CREATOR"] = temp;
		//log.Info()<<"REC_CREATOR="<<sdTrim["REC_CREATOR"].toString()<<endl;

		////7		Դ��������
		//temp = sd["SRC_STOCK_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["SRC_STOCK_CODE"] = temp;
		//log.Info()<<"SRC_STOCK_CODE="<<sdTrim["SRC_STOCK_CODE"].toString()<<endl;

		////8		Դ��λ����
		//temp = sd["SRC_LOC_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["SRC_LOC_CODE"] = temp;
		//log.Info()<<"SRC_LOC_CODE="<<sdTrim["SRC_LOC_CODE"].toString()<<endl;

		////9		�������ϴ���
		//temp = sd["SRC_MAT_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["SRC_MAT_CODE"] = temp;
		//log.Info()<<"SRC_MAT_CODE="<<sdTrim["SRC_MAT_CODE"].toString()<<endl;

		////10		�������ƴ���
		//temp = sd["SRC_COMP_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["SRC_COMP_CODE"] = temp;
		//log.Info()<<"SRC_COMP_CODE="<<sdTrim["SRC_COMP_CODE"].toString()<<endl;

		////11		Ŀ�Ŀ�������
		//temp = sd["DST_STOCK_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["DST_STOCK_CODE"] = temp;
		//log.Info()<<"DST_STOCK_CODE="<<sdTrim["DST_STOCK_CODE"].toString()<<endl;

		////12		Ŀ�Ŀ�λ����
		//temp = sd["DST_LOC_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["DST_LOC_CODE"] = temp;
		//log.Info()<<"DST_LOC_CODE="<<sdTrim["DST_LOC_CODE"].toString()<<endl;

		////13		�շ����ϴ���
		//temp = sd["DST_MAT_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["DST_MAT_CODE"] = temp;
		//log.Info()<<"DST_MAT_CODE="<<sdTrim["DST_MAT_CODE"].toString()<<endl;

		////14		�շ����ƴ���
		//temp = sd["DST_COMP_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["DST_COMP_CODE"] = temp;
		//log.Info()<<"DST_COMP_CODE="<<sdTrim["DST_COMP_CODE"].toString()<<endl;

		////15		��������������װ�����������壩
		//temp = sd["ESTIMATE_WGT"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["ESTIMATE_WGT"] = temp;
		//log.Info()<<"ESTIMATE_WGT="<<sdTrim["ESTIMATE_WGT"].toInt()<<endl;

		////16		�����ѱ�־
		//temp = sd["START_FLAG"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["START_FLAG"] = temp;
		//log.Info()<<"START_FLAG="<<sdTrim["START_FLAG"].toString()<<endl;//G:������  C:ȡ�����

		////17		�Ƿ���Ҫ�ʼ��־
		//temp = sd["QC_FLAG"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["QC_FLAG"] = temp;
		//log.Info()<<"QC_FLAG="<<sdTrim["QC_FLAG"].toString()<<endl;//1:��Ҫ  0������Ҫ

		//18 	��ע1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//19		��ע2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//20		��ע3
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//21		��ע4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//22		��ע5
		//log.Info()<<"\t\t BACK5="<<sd["BACK5"].toString();

		//		����ʱ��
		log.Info()<<"RCV_TIME="<<iDA::DateTime::Now().ToShortTimeString()<<endl;

		ByteSeq data;
		sdTrim.writeTo(data);
		DealData dealdata = DealData();
		//�������
		string dataStr = dealdata.DumpValue(sdTrim,",");
		//��ȡ���ID��
		int ID = dealdata.GetMaxIDRcv();
		//���ID�ż�1
		ID += 1; 
		//�����ݴ浽���ͱ���
		dealdata.InsertRcvData(msgId,dataStr,data,ID);

		//������д�����ݿ��
		HandleDataIntoDB(sdTrim);

		////����ж�Ϲ��֪ͨ
		//CanXLStartNotify(sdTrim);

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


void MsgKIBH04::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgKIBH04 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string planNO = sd["PLAN_NO"].toString();//�ƻ���
		string hopperNO = sd["HOPPER_NO"].toString();//�ϲۺ�
		int netWeight = sd["MAT_NET_WT"].toInt();//ʵ�ʳ�������


		//�������ϼƻ���
		SQL4L3::UpdateMatOutInfo_WT(planNO, hopperNO, netWeight);
		log.Info()<<"planNO = "<<planNO<<" , UpdateMatCarRelationInfo.........return.........."<<endl;
		return;


		////20220714 zhangyuhong add
		////�ж�ԭ Ŀ�Ŀ����Ƿ��Ƕ����� ���Ƕ����ֶѳ��� ֱ�ӷ��ر���
		//string srcStockCode = sd["SRC_STOCK_CODE"].toString();//Դ��������
		//string dstStockCode = sd["DST_STOCK_CODE"].toString();//Ŀ�Ŀ�������
		//if (srcStockCode != SCRAP_YARD_NAME && dstStockCode != SCRAP_YARD_NAME)
		//{
		//	log.Info()<<"srcStockCode or dstStockCode are not SCRAP_YARD_NAME, L3 plan is error .........return.........."<<endl;
		//	return;
		//}
		//
		//ԭ�Ȳ����ڼ�¼������£���ֱ�Ӳ����¼�¼
//		L3PlanInfo planInfo;
//		if (false == SQL4L3::SelL3PlanInfo(workSeqNO, planInfo))
//		{
//			log.Info()<<"workSeqNO = "<<workSeqNO<<" , no record in table , insert into .........return.........."<<endl;
//			string planType = GetL3PlanType(sd);
//			SQL4L3::InsertMatInOutInfo(sd, planType);
//			//�󶨳����ƻ���Ϣ��
//			BandCarPlanInfo(sd, planInfo, "0", "");
//			return;
//		}
//
////=========================================================================================
//		log.Info()<<"workSeqNO = "<<workSeqNO<<" , have record in table , need to judge something........."<<endl;
//		//���ڼ�¼�������
//		string wmsOperateFlag = planInfo.getOperateFlag();
//		string wmsPlanType = planInfo.getPlanType();
//		string wmsPlanValid = planInfo.getPlanValid();
//		
//		//���ԭ�ȼ�¼��ɾ����ǣ�����ɾ�����ٲ���
//		if (wmsOperateFlag == L3PlanInfo::OPERATE_FLAG_D)
//		{
//			log.Info()<<"wmsOperateFlag = D.........."<<endl;
//			SQL4L3::DelMatInOutInfo(workSeqNO);
//			string planType = GetL3PlanType(sd);
//			SQL4L3::InsertMatInOutInfo(sd, planType);
//
//			if (wmsPlanValid == L3PlanInfo::PLAN_VALID_YES)//ԭ���ǺϷ���,���԰󶨳����ƻ���
//			{
//				log.Info()<<"wmsPlanValid = 1  valid.........."<<endl;
//				//�󶨳����ƻ���Ϣ��
//				BandCarPlanInfo(sd, planInfo, "0", "");
//				return;
//			}
//
//			if (wmsPlanValid == L3PlanInfo::PLAN_VALID_NO)//ԭ���ǷǷ��ģ�˵���˼ƻ�֮ǰ�Ѿ��й������������ҵ���,  ��˻��ǷǷ��ģ����ٰ󶨳����ƻ�����Ҫ��workSeqNO��
//			{
//				log.Info()<<"wmsPlanValid = 2  invalid.........."<<endl;
//				SQL4L3::UpdL3PlanInfoPlanVlaid(workSeqNO, wmsPlanValid);
//				return;
//			}
//		}
////=========================================================================================
//
////=========================================================================================
//		//���ԭ�ȼ�¼���������  ,�յ���¼��ɾ�����
//		if (wmsOperateFlag == L3PlanInfo::OPERATE_FLAG_I && operateFlag == L3PlanInfo::OPERATE_FLAG_D)
//		{
//			//�Լƻ�����в���
//			SQL4L3::DelMatInOutInfo(planInfo.getWorkSeqNO());
//			string sdPlanType = GetL3PlanType(sd);
//			SQL4L3::InsertMatInOutInfo(sd, sdPlanType);
//
//			log.Info()<<"wmsOperateFlag == I && operateFlag == D ....................................."<<endl;
//			string planValid = L3PlanInfo::PLAN_VALID_YES;
//
//			//1.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC...................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC)//���ԭ����װ��,����ȡ����
//			{
//				log.Info()<<"planInfo.getPlanType() = ZC   .............."<<endl;
//				CheckWorkProg(planInfo, "ZC", planValid);
//			}
//
//			//2.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_XL..................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_XL)//���ԭ����ж�ϣ�����ȡ����
//			{
//				log.Info()<<"planInfo.getPlanType() = XL................."<<endl;
//				CheckWorkProg(planInfo, "XL", planValid);
//			}
//
//			//3.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC_XL..................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC_XL)//���ԭ����װ��+ж��
//			{
//				log.Info()<<"planInfo.getPlanType() = ZC_XL.........."<<endl;
//				//���װ����ҵ����
//				string zcPlanValid = L3PlanInfo::PLAN_VALID_YES;
//				CheckWorkProg(planInfo, "ZC", zcPlanValid);
//				log.Info()<<"zcPlanValid = "<<zcPlanValid<<endl;
//
//				//���ж����ҵ����
//				string xlPlanValid = L3PlanInfo::PLAN_VALID_YES;
//				CheckWorkProg(planInfo, "XL", xlPlanValid);
//				log.Info()<<"xlPlanValid = "<<xlPlanValid<<endl;
//
//				//ת����ж�� ��һ���ǷǷ� ���ǷǷ�
//				if (zcPlanValid == L3PlanInfo::PLAN_VALID_NO || xlPlanValid == L3PlanInfo::PLAN_VALID_NO)
//				{
//					planValid = L3PlanInfo::PLAN_VALID_NO;
//				}
//			}			
//			SQL4L3::UpdL3PlanInfoPlanVlaid(planInfo.getWorkSeqNO(), planValid);
//			return;
//		}
////=========================================================================================
//
////=========================================================================================
//		if (wmsOperateFlag == L3PlanInfo::OPERATE_FLAG_I && operateFlag == L3PlanInfo::OPERATE_FLAG_I)
//		{
//			//�Լƻ�����в���
//			SQL4L3::DelMatInOutInfo(planInfo.getWorkSeqNO());
//			string sdPlanType = GetL3PlanType(sd);
//			SQL4L3::InsertMatInOutInfo(sd, sdPlanType);
//
//			log.Info()<<"wmsOperateFlag == I && operateFlag == I ....................................."<<endl;
//			string planValid = L3PlanInfo::PLAN_VALID_YES;			
//
////1.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC...................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC)//���ԭ����װ��
//			{
//				log.Info()<<"planInfo.getPlanType() = ZC.........."<<endl;
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC )//���»���װ��
//				{
//					log.Info()<<"sdPlanType = ZC .............."<<endl;
//					CheckZCSrcInfo(planInfo, sd, planValid);
//				}
//
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_XL)//����ֻ��ж����   ȡ����װ��
//				{
//					log.Info()<<"sdPlanType = XL   only.............."<<endl;
//					CheckWorkProg(planInfo, "ZC", planValid);
//					//ȡ����װ��,������ж�ϣ����ԭ�� planValid=1 �Ϸ� �����������ж����ҵ�� ���� �ƻ��󶨱�
//					if (planValid == L3PlanInfo::PLAN_VALID_YES)
//					{
//						BandCarPlanInfo(sd, planInfo, "1", "XL");
//					}					
//				}
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC_XL)
//				{
//					log.Info()<<"sdPlanType = ZC_XL .............."<<endl;
//					CheckZCSrcInfo(planInfo, sd, planValid);
//					//������ж�ϣ����ԭ�� planValid=1 �Ϸ� �����������ж����ҵ�� ���� �ƻ��󶨱�
//					if (planValid == L3PlanInfo::PLAN_VALID_YES)
//					{
//						BandCarPlanInfo(sd, planInfo, "1", "XL");
//					}			
//				}
//			}
//
////2.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_XL...................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_XL)//���ԭ����ж��
//			{
//				log.Info()<<"planInfo.getPlanType() = XL.........."<<endl;
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_XL) //������ж��
//				{
//					log.Info()<<"sdPlanType = XL.............."<<endl;
//					CheckXLDstInfo(planInfo, sd, planValid);
//				}
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC)//������װ��   ȡ����ж��
//				{
//					log.Info()<<"sdPlanType = ZC   only.............."<<endl;
//					CheckWorkProg(planInfo, "XL", planValid);
//					//ȡ����ж�ϣ�������װ�������ԭ�� planValid=1 �Ϸ� �����������װ���� ���� �ƻ��󶨱�
//					if (planValid == L3PlanInfo::PLAN_VALID_YES)
//					{
//						BandCarPlanInfo(sd, planInfo, "1", "ZC");
//					}		
//				}
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC_XL)
//				{
//					log.Info()<<"sdPlanType = ZC_XL .............."<<endl;
//					CheckXLDstInfo(planInfo, sd, planValid);
//					//������װ�������ԭ�� planValid=1 �Ϸ� �����������װ����ҵ�� ���� �ƻ��󶨱�
//					if (planValid == L3PlanInfo::PLAN_VALID_YES)
//					{
//						BandCarPlanInfo(sd, planInfo, "1", "ZC");
//					}			
//				}
//			}
//
//
////3.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC_XL...................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC_XL)//���ԭ����װ��+ж��
//			{
//				log.Info()<<"planInfo.getPlanType() = ZC_XL.........."<<endl;
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC )//������װ��,  ȡ����ж��
//				{
//					log.Info()<<"sdPlanType = ZC only.............."<<endl;
//					//���ZC��Ϣ�Ƿ�仯
//					string zcPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckZCSrcInfo(planInfo, sd, zcPlanValid);
//
//					//��ȡж����ҵ����
//					string xlPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckWorkProg(planInfo, "XL", xlPlanValid);		
//					
//					if (zcPlanValid == L3PlanInfo::PLAN_VALID_NO || xlPlanValid == L3PlanInfo::PLAN_VALID_NO)
//					{
//						planValid = L3PlanInfo::PLAN_VALID_NO;
//					}
//				}
//
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_XL)//������ж�ϣ�ȡ����װ��
//				{
//					log.Info()<<"sdPlanType = XL only.............."<<endl;
//					//���XL��Ϣ�Ƿ�仯
//					string xlPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckXLDstInfo(planInfo, sd, xlPlanValid);
//
//					//��ȡװ����ҵ����
//					string zcPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckWorkProg(planInfo, "ZC", zcPlanValid);	
//
//					if (xlPlanValid == L3PlanInfo::PLAN_VALID_NO || zcPlanValid == L3PlanInfo::PLAN_VALID_NO)
//					{
//						planValid = L3PlanInfo::PLAN_VALID_NO;
//					}
//				}
//
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC_XL)
//				{
//					log.Info()<<"sdPlanType = ZC_XL .............."<<endl;
//					//���ZC  XL��Ϣ�Ƿ�仯
//					string zcPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckZCSrcInfo(planInfo, sd, zcPlanValid);
//
//					string xlPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckXLDstInfo(planInfo, sd, xlPlanValid);
//
//					if (xlPlanValid == L3PlanInfo::PLAN_VALID_NO || zcPlanValid == L3PlanInfo::PLAN_VALID_NO)
//					{
//						planValid = L3PlanInfo::PLAN_VALID_NO;
//					}
//				}
//			}
//			
//			SQL4L3::UpdL3PlanInfoPlanVlaid(planInfo.getWorkSeqNO(), planValid);
			
		//}//end of  wmsOperateFlag = I  operateFlag = I

		
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


void MsgKIBH04::BandCarPlanInfo(SmartData sd, L3PlanInfo planInfo, string assignFlag, string assignWorkType)
{
	string functionName="MsgKIBH04 :: BandCarPlan()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//������� I-����  D-ɾ��
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//Դ��������
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//Դ��λ����
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//�������ϴ���
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//�������ƴ���
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//Ŀ�Ŀ�������
		string dstLocCode = sd["DST_LOC_CODE"].toString();//Ŀ�Ŀ�λ����
		string dstMatCode = sd["DST_MAT_CODE"].toString();//�շ����ϴ���
		string dstCompCode = sd["DST_COMP_CODE"].toString();//�շ����ƴ���

		//��Ҫ�������µ������У�
		//����   ������   ��ҵ����    �ƻ��ţ���ˮ�ţ�  �ƻ���Դ   �Ƿ���������ǣ�1��   ����ָ����     ��ʱ��
		//
		string carNO = sd["CAR_NO"].toString();//����
		string carType = "1";
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//��ˮ��
		string planSrc = "L3";
		string enterFlag = "1";
		string orderFlag = "1";
		iDA::DateTime bandTime = iDA::DateTime::Now();
		iDA::DateTime bandTime1 = iDA::DateTime::Now();

		int bandTimeSec = bandTime.GetSecond();
		bandTime1.SetSecond(bandTimeSec - 1);

		string workType = "";

		if (operateFlag == "D")
		{
			//ִ��ɾ�������ƻ�����Ϣ��
			log.Info()<<"tel SD  operateFlag == D.........  no need do ...........return..."<<endl;
			return;
		}

		if (operateFlag == "I" && assignFlag == "0")//��ָ��
		{
			//���¾���ִ������ operateFlag=="I"�����
			//��DELETE Ȼ��INSERT
			//��ɾ��
			SQL4L3::DelCarPlanBandInfo(planInfo.getCarNO(), workSeqNO);
			//�������ƴ�������L3��������
			if  (srcStockCode == SCRAP_YARD_NAME && dstStockCode == SCRAP_YARD_NAME)//����L3��˵����¯EF������Ͷ�����ABC���������ͬһ������
			{			
				//����������� �ӵ�¯�ϸֿ����������ַϸֿ���  ����  �����ַϸֿ�������¯�ϸֿ���
				//������� ��ZC  ��XL  ��ˣ�Ŀ���ϸ�Ҳ����2��
				//��Ҫ����2����¼��װ����ж��  
				workType = "ZC";
				//���ͬʱ��װ����ж��,��װ���İ�ʱ��-1��,Ϊ���Ǻ�������ʱ��ASC��������ѡ��
				SQL4L3::InsCarPlanBandInfo(carNO, carType, workType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime1);
				workType = "XL";
				SQL4L3::InsCarPlanBandInfo(carNO, carType, workType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime);
				return;			
			}
			//����������ǣ�Ҫô srcStockCode��WMS��ҵ������Ҫô  dstStockCode ��WMS��ҵ����  ��������ͬʱ��WMS��ҵ����
			if (srcStockCode == SCRAP_YARD_NAME)
			{
				//Դ������WMS��������װ����ҵ
				workType = "ZC";
				SQL4L3::InsCarPlanBandInfo(carNO, carType, workType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime);
				return;
			}
			if (dstStockCode == SCRAP_YARD_NAME)
			{
				//Ŀ�Ŀ�����WMS��������ж����ҵ
				workType = "XL";
				SQL4L3::InsCarPlanBandInfo(carNO, carType, workType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime);
				return;
			}
		}

		if (operateFlag == "I" && assignFlag == "1") //ָ��
		{
			//���¾���ִ������ operateFlag=="I"�����
			//��DELETE Ȼ��INSERT
			SQL4L3::DelCarPlanBandInfoByWorkType(planInfo.getCarNO(), workSeqNO, assignWorkType);
			SQL4L3::InsCarPlanBandInfo(carNO, carType, assignWorkType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime);
			return;
		}
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


string MsgKIBH04::GetL3PlanType(SmartData sd)
{
	string functionName="MsgKIBH04 :: GetL3PlanType()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//Դ��������
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//Ŀ�Ŀ�������

		string planType = "";
		if  (srcStockCode == SCRAP_YARD_NAME && dstStockCode == SCRAP_YARD_NAME)//����L3��˵����¯EF������Ͷ�����ABC���������ͬһ������
		{
			planType = L3PlanInfo::PLAN_TYPE_ZC_XL;//����װ��  Ҳ��ж��
			return planType;
		}
		if (srcStockCode == SCRAP_YARD_NAME)
		{
			planType = L3PlanInfo::PLAN_TYPE_ZC;//װ�� 
			return planType;
		}
		if (dstStockCode == SCRAP_YARD_NAME)
		{
			planType = L3PlanInfo::PLAN_TYPE_XL;//ж��
			return planType;
		}
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


bool MsgKIBH04::SrcInfoNotChange(L3PlanInfo planInfo, SmartData sd)
{
	string functionName="MsgKIBH04 :: SrcInfoNotChange()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		string wmsSrcStockCode = planInfo.getSrcStockCode();
		string wmsSrcLocCode = planInfo.getSrcLocCode();
		string wmsSrcMatCode = planInfo.getSrcMatCode();
		string wmsSrcCompCode = planInfo.getSrcCompCode();

		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//Դ��������
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//Դ�ϸ����
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//Դ�ϸ����
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//Դ�ϸ����

		if (wmsSrcStockCode == SCRAP_YARD_NAME && srcStockCode == SCRAP_YARD_NAME)//
		{
			if (wmsSrcLocCode == srcLocCode && wmsSrcMatCode == srcMatCode && wmsSrcCompCode == srcCompCode)//����ϸ� ���ϴ��� ������ ��1����һ�� ����Ϊ���б仯
			{
				ret = true;
				return ret;
			}
			else
			{
				ret = false;
				return ret;
			}
		}		
		return ret;
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


bool MsgKIBH04::DstInfoNotChange(L3PlanInfo planInfo, SmartData sd)
{
	string functionName="MsgKIBH04 :: DstInfoNotChange()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		string wmsDstStockCode = planInfo.getDstStockCode();
		string wmsDstLocCode = planInfo.getDstLocCode();
		string wmsDstMatCode = planInfo.getDstMatCode();
		string wmsDstCompCode = planInfo.getDstCompCode();

		string dstStockCode = sd["DST_STOCK_CODE"].toString();//Ŀ�Ŀ�������
		string dstLocCode = sd["DST_LOC_CODE"].toString();//Ŀ���ϸ����
		string dstMatCode = sd["DST_MAT_CODE"].toString();//Ŀ���ϸ����
		string dstCompCode = sd["DST_COMP_CODE"].toString();//Ŀ���ϸ����

		if (wmsDstStockCode == SCRAP_YARD_NAME && dstStockCode == SCRAP_YARD_NAME)//
		{
			if (wmsDstLocCode == dstLocCode && wmsDstMatCode == dstMatCode && wmsDstCompCode == dstCompCode)//����ϸ� ���ϴ��� ������ ��1����һ�� ����Ϊ���б仯
			{
				ret = true;
				return ret;
			}
			else
			{
				ret = false;
				return ret;
			}
		}		
		return ret;
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

bool MsgKIBH04::CarNONotChange(L3PlanInfo planInfo, SmartData sd)
{
	string functionName="MsgKIBH04 :: CarNONotChange()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		string wmsCarNO = planInfo.getCarNO();//����
		string sdCarNO = sd["CAR_NO"].toString();//����
		if (wmsCarNO == sdCarNO)//
		{
			ret = true;
			return ret;
		}		
		return ret;
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


//����Ƿ���Ҫ���±༭ ������Ϣ�󶨱�
void MsgKIBH04::CheckZCSrcInfo(L3PlanInfo planInfo, SmartData sd, string& planValid)
{
	string functionName="MsgKIBH04 :: CheckZCSrcInfo()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		if (true == SrcInfoNotChange(planInfo, sd) && true == CarNONotChange(planInfo, sd))//Դ�ϸ���Ϣ���� ���Ų���
		{
			log.Info()<<" SrcInfoNotChange = true,  CarNONotChange = true........"<<endl;
			planValid = L3PlanInfo::PLAN_VALID_YES;//�Ϸ�
		}
		else//Դ�ϸ���Ϣ�仯�򳵺ű仯
		{
			//��ȡԭ�ȳ�������
			string enterFlag = "";
			if (false == SQL4L3::SelCarStatusByWokrType(planInfo.getCarNO(), planInfo.getWorkSeqNO(), "ZC", enterFlag))
			{
				//װ���Ѿ���ɣ��ѱ仯��Ϣ�϶��Ƿ�
				log.Info()<<" SelCarStatus  false, plan  not exist in carplanband table....................."<<endl;
				planValid = L3PlanInfo::PLAN_VALID_NO;//�Ƿ�
			}
			else	
			{
				if (enterFlag == "1")
				{
					log.Info()<<"enterFlag = 1, car not arrive in yard , can change carplanband table........."<<endl;
					BandCarPlanInfo(sd, planInfo, "1", "ZC");
					planValid = L3PlanInfo::PLAN_VALID_YES;
				}
				else
				{
					log.Info()<<"enterFlag != 1, car  in yard , can not  change carplanband table........."<<endl;
					planValid = L3PlanInfo::PLAN_VALID_NO;
				}				
			}
		}
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

//����Ƿ���Ҫ���±༭ ������Ϣ�󶨱�
void MsgKIBH04::CheckXLDstInfo(L3PlanInfo planInfo, SmartData sd, string& planValid)
{
	string functionName="MsgKIBH04 :: CheckXLDstInfo()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		if (true == DstInfoNotChange(planInfo, sd) && true == CarNONotChange(planInfo, sd))//Ŀ���ϸ���Ϣ���� ���Ų���
		{
			log.Info()<<" DstInfoNotChange = true,  CarNONotChange = true........"<<endl;
			planValid = "1";//�Ϸ�
		}
		else//Ŀ���ϸ���Ϣ�仯�򳵺ű仯
		{
			//��ȡԭ�ȳ�������
			string enterFlag = "";
			if (false == SQL4L3::SelCarStatusByWokrType(planInfo.getCarNO(), planInfo.getWorkSeqNO(), "XL", enterFlag))
			{
				//ж���Ѿ���ɣ��ѱ仯��Ϣ�϶��Ƿ�
				log.Info()<<" SelCarStatus  false, plan  not exist in carplanband table....................."<<endl;
				planValid = "2";//�Ƿ�
			}
			else	
			{
				if (enterFlag == "1")
				{
					log.Info()<<"enterFlag = 1, car not arrive in yard , can change carplanband table........."<<endl;
					BandCarPlanInfo(sd, planInfo, "1", "XL");
					planValid = "1";
				}
				else
				{
					log.Info()<<"enterFlag != 1, car  in yard , can not  change carplanband table........."<<endl;
					planValid = "2";
				}				
			}
		}
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

//����Ƿ���Ҫɾ�� �����ƻ���Ϣ�󶨱�
void MsgKIBH04::CheckWorkProg(L3PlanInfo planInfo, string workType, string& planValid)
{
	string functionName="MsgKIBH04 :: CheckWorkProg()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string enterFlag = "";
		if (false == SQL4L3::SelCarStatusByWokrType(planInfo.getCarNO(), planInfo.getWorkSeqNO(), workType, enterFlag))
		{
			//�Ѿ���ɣ��ѱ仯��Ϣ�϶��Ƿ�
			log.Info()<<" SelCarStatus  false, plan  not exist in carplanband table....................."<<endl;
			planValid = L3PlanInfo::PLAN_VALID_NO;//�Ƿ�
		}
		else	
		{
			if (enterFlag == "1")
			{
				log.Info()<<"enterFlag = 1, car not arrive in yard , can change carplanband table........."<<endl;//������û����ɾ������Ϣ
				SQL4L3::DelCarPlanBandInfoByWorkType(planInfo.getCarNO(), planInfo.getWorkSeqNO(), workType);
				planValid = L3PlanInfo::PLAN_VALID_YES;
			}
			else
			{
				log.Info()<<"enterFlag != 1, car  in yard , can not  change carplanband table........."<<endl;
				planValid = L3PlanInfo::PLAN_VALID_NO;
			}				
		}
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


//L3����������֪ͨ:����EVtag��֪ͨ
void MsgKIBH04::CanXLStartNotify(SmartData sd)
{
	string functionName="MsgKIBH04 :: CanXLStartNotify()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string workSeqNO = sd["WORK_SEQ_NO"].toString();
		string sdPlanType = GetL3PlanType(sd);
		if (sdPlanType == L3PlanInfo::PLAN_TYPE_XL || sdPlanType == L3PlanInfo::PLAN_TYPE_ZC_XL)
		{
			string canXLNotify = sd["START_FLAG"].toString();
			string tagName = "";
			string tagValue = workSeqNO;

			log.Info()<<"canXLNotify = "<<canXLNotify<<endl;
			if (canXLNotify == L3PlanInfo::START_FLAG_G)//����ж�Ϲ�ѱ�ʶ��G
			{
				tagName = "EV_L3_START_FLAG_G";//ж�Ϲ�ѱ��tag��
				EVTagSnd(tagName, tagValue);
				log.Info()<<"Send EV_L3_START_FLAG_G , workSeqNO = "<<workSeqNO<<endl;
			}
			if (canXLNotify == L3PlanInfo::START_FLAG_C)
			{
				tagName = "EV_L3_START_FLAG_C";//ж�Ϲ�ѱ��tag��
				EVTagSnd(tagName, tagValue);
				log.Info()<<"Send EV_L3_START_FLAG_C , workSeqNO = "<<workSeqNO<<endl;
			}
		}		
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


bool MsgKIBH04::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgKIBH04 :: EVTagSnd()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		iPlature::TAGVALUEMAP tagPairs;
		log.Info()<<"eventPut tagName="<<tagName<<"    tagValue="<<tagValue<<endl;
		Tag::GetInst().EventPut(tagPairs,tagName,tagValue);
		ret=true;
		return ret;
	}
	catch(...)
	{
		log.Debug()<<"EVTagSnd  error..........."<<endl;
	}
	return ret;
}