#include "MsgEU01.h"
#include "DealData.h"


using namespace Monitor;
using namespace iPlature;



MsgEU01*  MsgEU01::m_pMsgEU01 = NULL;


MsgEU01::MsgEU01() 
{
	msgId="EU01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgEU01 :: ~MsgEU01(void)
{
	
	delete m_pMsgEU01;


}

 MsgEU01* MsgEU01::getInstance(void)
{
	if (m_pMsgEU01 == NULL)
	{
		m_pMsgEU01 = new MsgEU01;
	}
	return m_pMsgEU01;
}

ByteSeq MsgEU01::HandleMessage(const ByteSeq& ParamBuffer, string msgIDInTrans)
{
	string functionName="MsgEU01 :: HandleMessage()";

	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{
		// ��ȡpowertrans���Ľṹ
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgIDInTrans);
			readSmartDataSuccessed=true;
		}

		//��ȡԭʼ�ֽ���
		sd.readFrom(ParamBuffer);

		log.Info()<<"......"<<endl;
		log.Info()<<"........................................................................................log of samrt data..................................................................................................................."<<endl;
		log.Info()<<"......."<<endl;

		//1		���������
		log.Info()<<"\t\t PONO="<<sd["PONO"].toString();

		//2		�ֺ�
		log.Info()<<"\t\t HTNO="<<sd["HTNO"].toString();

		//3		�䷽����
		log.Info()<<"\t\t RECIPE_TYPE="<<sd["RECIPE_TYPE"].toString();//1������  2���޸�  3��ɾ��

		//4		���ּǺ�
		log.Info()<<"\t\t STEELGRADE="<<sd["STEELGRADE"].toString();

		//5		����ʱ��
		log.Info()<<"\t\t TAP_TIME="<<sd["TAP_TIME"].toString();

		//6		�ƻ���Դ�� 1���µ�¯  2���ϵ�¯
		log.Info()<<"\t\t PLAN_SRC="<<sd["PLAN_SRC"].toString()<<endl;

		//7		����ѭ���壺������-�Ӻ�-�ϸִ���1-�ϸ���1...�ϸִ���20-�ϸ���20
		for (int index = 0; index < 3; index++)
		{
			//������
			log.Info()<<"\t\t B_SEQ_NUM"<<index+1<<":  "<<sd["EAF_PLAN_DETAIL"][index]["B_SEQ_NUM"].toString();
			//��λ��
			log.Info()<<"\t\t PIT_NUM"<<index+1<<":  "<<sd["EAF_PLAN_DETAIL"][index]["PIT_NUM"].toString()<<endl;

			//�ϸֺ�1
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_1:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_1"].toString();
			//�ϸ���1
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_1:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_1"].toString()<<endl;

			//�ϸֺ�2
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_2:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_2"].toString();
			//�ϸ���2
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_2:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_2"].toString()<<endl;

			//�ϸֺ�3
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_3:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_3"].toString();
			//�ϸ���3
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_3:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_3"].toString()<<endl;

			//�ϸֺ�4
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_4:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_4"].toString();
			//�ϸ���4
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_4:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_4"].toString()<<endl;

			//�ϸֺ�5
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_5:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_5"].toString();
			//�ϸ���5
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_5:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_5"].toString()<<endl;

			//�ϸֺ�6
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_6:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_6"].toString();
			//�ϸ���6
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_6:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_6"].toString()<<endl;
			
			//�ϸֺ�7
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_7:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_7"].toString();
			//�ϸ���7
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_7:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_7"].toString()<<endl;

			//�ϸֺ�8
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_8:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_8"].toString();
			//�ϸ���8
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_8:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_8"].toString()<<endl;

			//�ϸֺ�9
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_9:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_9"].toString();
			//�ϸ���9
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_9:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_9"].toString()<<endl;

			//�ϸֺ�10
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_10:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_10"].toString();
			//�ϸ���10
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_10:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_10"].toString()<<endl;

			//�ϸֺ�11
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_11:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_11"].toString();
			//�ϸ���11
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_11:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_11"].toString()<<endl;

			//�ϸֺ�12
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_12:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_12"].toString();
			//�ϸ���12
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_12:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_12"].toString()<<endl;

			//�ϸֺ�13
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_13:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_13"].toString();
			//�ϸ���13
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_13:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_13"].toString()<<endl;

			//�ϸֺ�14
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_14:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_14"].toString();
			//�ϸ���14
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_14:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_14"].toString()<<endl;

			//�ϸֺ�15
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_15:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_15"].toString();
			//�ϸ���15
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_15:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_15"].toString()<<endl;

			//�ϸֺ�16
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_16:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_16"].toString();
			//�ϸ���16
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_16:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_16"].toString()<<endl;

			//�ϸֺ�17
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_17:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_17"].toString();
			//�ϸ���17
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_17:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_17"].toString()<<endl;

			//�ϸֺ�18
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_18:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_18"].toString();
			//�ϸ���18
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_18:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_18"].toString()<<endl;

			//�ϸֺ�19
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_19:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_19"].toString();
			//�ϸ���19
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_19:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_19"].toString()<<endl;

			//�ϸֺ�20
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_20:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_20"].toString();
			//�ϸ���20
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_20:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_20"].toString()<<endl;			
		}
		//7		����ʱ��
		log.Info()<<"\t\t RCV_TIME="<<iDA::DateTime::Now().ToShortTimeString()<<endl;

		ByteSeq data;
		sd.writeTo(data);
		DealData dealdata = DealData();
		//�������
		string dataStr = dealdata.DumpValue(sd,",");
		//��ȡ���ID��
		int ID = dealdata.GetMaxIDRcv();
		//���ID�ż�1
		ID += 1; 
		//�����ݴ浽���ͱ���
		dealdata.InsertRcvData(msgIDInTrans,dataStr,data,ID);



		//д�����ݿ�
		HandleDataIntoDB(sd);

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

void MsgEU01::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgEU01 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string pono = sd["PONO"].toString();
		string htno = sd["HTNO"].toString();
		string recipeType = sd["RECIPE_TYPE"].toString();
		string steelGrade = sd["STEELGRADE"].toString();
		string tapTime = sd["TAP_TIME"].toString();
		string planSrc = sd["PLAN_SRC"].toString();

//=============1. ���ݿ��в��������ƻ�==============================================
		EAFPlanInfoMain planInfoMain;
		if ( false == SQL4EAF::SelEAFPlanInfoMain(pono, planInfoMain) )//�����ڣ�ֱ��д��
		{
			log.Info()<<"New plan , no record in databse,  insert ..................."<<endl;
			SQL4EAF::InsEAFL2PlanMain(sd);
			InsEAFL2PlanDetail(sd);
			return;
		}

//=============2. ���ݿ��д������ƻ�================================================
		log.Info()<<"Old plan , have record in databse,  ..................."<<endl;		
		//��ȡ�ӱ��������
		vector<EAFPlanInfoDetail> vecPlanInfoDetail;
		//����ӱ����ݲ�����,ֱ�Ӹ�������,�����ӱ�
		if ( false == SQL4EAF::SelEAFPlanInfoDetail(pono, vecPlanInfoDetail) )//vecPlanInfoDetail  ֻ��ȡlayValid=1 �� ��Ҳ���ǺϷ�������
		{
			log.Info()<<" no DETAIL record in databse,  insert ..................."<<endl;
			SQL4EAF::UpdatePlanMain(pono, htno, recipeType, steelGrade, tapTime, planSrc);	
			InsEAFL2PlanDetail(sd);
			return;
		}

//=============3. ���ݿ��д������ƻ����Ӽƻ�==========================================
//1. ���sd�ƻ���ɾ��������Ա��ӱ�������(���ù���sd����,��Ϊ����sd�Ѿ���ɾ��״̬),����ӱ�������:
//		1.1û���䳵:��������
//		1.2�Ѿ��䳵(car�ֶ�),����δ��ʼ(status�ֶ�): ���� pono, detailID ɾ����������Ϣ��������; 
//		1.3�Ѿ��䳵�Ѿ�����: ����pono , detailID���ӱ��¼���� layValid=2 �Ƿ� 
		if (recipeType == EAFPlanInfoMain::RECIPE_TYPE_DELETE)
		{
			log.Info()<<"recipeType == RECIPE_TYPE_DELETE ..................."<<endl;
			SQL4EAF::UpdatePlanMain(pono, htno, recipeType, steelGrade, tapTime, planSrc);//��������������

			vector<EAFPlanInfoDetail>::iterator itor;
			for (itor = vecPlanInfoDetail.begin(); itor != vecPlanInfoDetail.end(); itor++)
			{
				EAFPlanInfoDetail planDetail = *itor;
				HandlePlanDetailDel(planDetail);
			}
			return;
		}


//2. ���sd�ƻ����������޸ģ�����Ƚ�sd���ݺ��ӱ�������,����ӱ�������:
//		2.1����ӱ�����sd�Ķ�Ӧ��������, ��������
//		2.2����ӱ�����sd�Ķ�Ӧ��������
//          2.2.1�����������û�б仯(�ϸִ��벻������������),��������
//			 2.2.2������������б仯(�ϸִ���ı�������ı�):
//					2.2.2.1û���䳵:ֱ�Ӹ���(����detailID)
//					2.2.2.2�Ѿ��䳵(car�ֶ�),����δ��ʼ(status�ֶ�): ֱ�Ӹ���(����detailID)  
//					2.2.2.3�Ѿ��䳵�Ѿ�����: ����pono , detailID���ӱ��¼���� layValid=2 �Ƿ� ;ͬʱ������������(������ͬһ�����ݶ�Ӧ2����¼,û��ϵ,��detailID��������)
//		2.3����ӱ�����sdû�еĲ�������
//			 2.3.1û���䳵��ֱ��ɾ��
//			 2.3.2�Ѿ��䳵(car�ֶ�),����δ��ʼ(status�ֶ�)��ֱ��ɾ���ӱ�˲��¼��ɾ����������Ϣ���ж�Ӧ��¼������pono��detailID��
//			 2.3.1�Ѿ��䳵�Ѿ�����������pono , detailID���ӱ��¼���� layValid=2 �Ƿ�
		if (recipeType == EAFPlanInfoMain::RECIPE_TYPE_ADD || recipeType == EAFPlanInfoMain::RECIPE_TYPE_MODIFY)
		{
			log.Info()<<"recipeType == RECIPE_TYPE_ADD  OR  RECIPE_TYPE_MODIFY ..................."<<endl;
			SQL4EAF::UpdatePlanMain(pono, htno, recipeType, steelGrade, tapTime, planSrc);//��������������

			//׼��vec��ÿ��detailID ����map, Ĭ��Ϊtrue  ���������������
			map<long, bool> mapDetailID = Vec2Map1(vecPlanInfoDetail);
			map<long, EAFPlanInfoDetail> mapPlanInfoDetail = Vec2Map2(vecPlanInfoDetail);
			
			for (int index = 0; index < 3; index++)
			{
				log.Info()<<"sd recycle: EAF_PLAN_DETAIL , index = "<<index<<endl;
				string basketID = sd["EAF_PLAN_DETAIL"][index]["B_SEQ_NUM"].toString();
				string pitNO = sd["EAF_PLAN_DETAIL"][index]["PIT_NUM"].toString();
				//������Ϊ�յ������˵��������û���䷽
				if (basketID.empty())
				{
					log.Info()<<" B_SEQ_NUM  is empty......."<<endl;
					continue;
				}

				for (int i = 1; i <=20; i++)
				{
					log.Info()<<"basketID = "<<basketID<<" recycle:  i = "<<i<<endl;
					string scrIDName = "SCR_ID_" + StringHelper::ToString(i);
					string scrWeightName = "SCR_WEIGHT_" + StringHelper::ToString(i);
					long layNO = i;
					//���� �� ��Ӧ�ľ����䷽�ϸִ������������
					string scrID = sd["EAF_PLAN_DETAIL"][index][scrIDName].toString();
					long scrWeight = Str2Num(sd["EAF_PLAN_DETAIL"][index][scrWeightName].toString());

					if (scrID.empty())
					{
						log.Info()<<" SCR_ID_  is empty......."<<endl;
						continue;
					}

					//pono basketid layno scrid scrweight ������  ���� vecPlanInfoDetail  �����ݽ��бȽ�
					HandleSDVecPlanDetail(pono, basketID, pitNO, layNO, scrID, scrWeight, vecPlanInfoDetail, mapDetailID);

				}
			}

			//��mapDetailID���б���������false�� ���ʹӱ����ж�ɾ����������valid=2
			//		2.3����ӱ�����sdû�еĲ�������
			//			 2.3.1û���䳵��ֱ��ɾ��
			//			 2.3.2�Ѿ��䳵(car�ֶ�),����δ��ʼ(status�ֶ�)��ֱ��ɾ���ӱ�˲��¼��ɾ����������Ϣ���ж�Ӧ��¼������pono��detailID��
			//			 2.3.1�Ѿ��䳵�Ѿ�����������pono , detailID���ӱ��¼���� layValid=2 �Ƿ�
			HandleMapDetailID(mapDetailID, mapPlanInfoDetail);
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


void MsgEU01::HandlePlanDetailDel(EAFPlanInfoDetail planInfoDetail)
{
	string functionName="MsgEU01 :: HandlePlanDetail1()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string carNO = planInfoDetail.getCarNO();
		string status = planInfoDetail.getStatus();
		if (carNO.empty())
		{
			//û���䳵 ����������
			return;
		}
		//�������Ѿ��䳵��
		//��δ��ʼ=1��˵����δ����
		if (status == EAFPlanInfoDetail::STATUS_NOT_START)
		{
			//����pono  detailIDɾ��������Ϣ�ƻ���������
			SQL4EAF::DelCarPlanBandByDetailID(planInfoDetail.getDetailID());
			return;
		}
		//�������Ѿ��䳵���Ѿ�����
		//����pono , detailID���ӱ��¼���� layValid=2 �Ƿ� 
		SQL4EAF::UpdDetailInvalidByDetailID(planInfoDetail.getDetailID());
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


long MsgEU01::Str2Num(string strNum)
{
	string functionName="MsgEU01 :: Str2Num()";
	LOG log(functionName, AUTO_CATCH_PID);
	long num = 0;

	try
	{
		if (strNum.empty())
		{
			num = 0;
		}
		else
		{
			num = StringHelper::ToNumber<long>(strNum);
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
	return num;
}

//		2.1����ӱ�����sd�Ķ�Ӧ��������, ��������
//		2.2����ӱ�����sd�Ķ�Ӧ��������
//          2.2.1�����������û�б仯(�ϸִ��벻������������),��������
//			 2.2.2������������б仯(�ϸִ���ı�������ı�):
//					2.2.2.1û���䳵:ֱ�Ӹ���(����detailID)
//					2.2.2.2�Ѿ��䳵(car�ֶ�),����δ��ʼ(status�ֶ�): ֱ�Ӹ���(����detailID)  
//					2.2.2.3�Ѿ��䳵�Ѿ�����: ����pono , detailID���ӱ��¼���� layValid=2 �Ƿ� ;ͬʱ������������(������ͬһ�����ݶ�Ӧ2����¼,û��ϵ,��detailID��������)
//		2.3����ӱ�����sdû�еĲ�������
//			 2.3.1û���䳵��ֱ��ɾ��
//			 2.3.2�Ѿ��䳵(car�ֶ�),����δ��ʼ(status�ֶ�)��ֱ��ɾ���ӱ�˲��¼��ɾ����������Ϣ���ж�Ӧ��¼������pono��detailID��
//			 2.3.1�Ѿ��䳵�Ѿ�����������pono , detailID���ӱ��¼���� layValid=2 �Ƿ�
void MsgEU01::HandleSDVecPlanDetail(string pono, 
																		string basketID, 
																		string pitNO, 
																		long layNO, 
																		string scrID, 
																		long scrWeight, 
																		vector<EAFPlanInfoDetail> vecPlanInfoDetail,
																		map<long, bool>& mapDetailID)
{
	string functionName="MsgEU01 :: HandleSDVecPlanDetail()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		//�ӱ����ޣ� sd��
		bool bFlag = false;
		vector<EAFPlanInfoDetail>::iterator itor;
		for (itor = vecPlanInfoDetail.begin(); itor != vecPlanInfoDetail.end(); itor++)
		{
			EAFPlanInfoDetail planInfoDetail = *itor;
			if (basketID == planInfoDetail.getBSeqNum() && layNO == planInfoDetail.getLayNO())//ԭ��������sd�Ķ�Ӧ�����Ͳ�������
			{
				bFlag = true;
				//��mapDetailID�е�detailID ��valud�ó�true
				mapDetailID[planInfoDetail.getDetailID()] = true;

				//����ϸִ�������������䣬��������
				if (scrID == planInfoDetail.getScrID() && scrWeight == planInfoDetail.getScrWeight())
				{
					log.Info()<<"  scrID == planInfoDetail.getScrID() && scrWeight == planInfoDetail.getScrWeight() , NO change , no need to handle............."<<endl;					
				}
				//����ϸִ�����������б仯
				else
				{
					log.Info()<<"  scrID != planInfoDetail.getScrID()  or  scrWeight != planInfoDetail.getScrWeight()  ,  need to handle............."<<endl;
					string carNO = planInfoDetail.getCarNO();
					string status = planInfoDetail.getStatus();
					if (carNO.empty())
					{
						log.Info()<<"  carNO is empty, just to update............."<<endl;
						SQL4EAF::UpdPlanDetailByDetailID(planInfoDetail.getDetailID(), scrID, scrWeight);
					}
					if (!carNO.empty() && status == EAFPlanInfoDetail::STATUS_NOT_START)
					{
						log.Info()<<"  carNO is not empty, status is STATUS_NOT_START,  just to update............."<<endl;
						SQL4EAF::UpdPlanDetailByDetailID(planInfoDetail.getDetailID(), scrID, scrWeight);
					}
					if (!carNO.empty() && status != EAFPlanInfoDetail::STATUS_NOT_START)
					{
						log.Info()<<"  carNO is not empty, status is STATUS_START or STATUS_FINISH,  update invalid and insert new............."<<endl;
						//�ȸ���ԭ�ȼ�¼ valid=2
						SQL4EAF::UpdPlanDetailInvalidByDetailID(planInfoDetail.getDetailID());
						//Ȼ������¼�¼
						string tempLayValid = EAFPlanInfoDetail::LAY_VALID_YES;
						string tempStatus = EAFPlanInfoDetail::STATUS_NOT_START;
						SQL4EAF::InsEAFL2PlanDetailSingle(pono, basketID, pitNO, layNO, scrID, scrWeight, tempLayValid, tempStatus);
					}
				}
				break;
			}
		}

		if (bFlag == false)//ԭ������û��sd��Ӧ�������Ͳ������ݣ�����ֱ�Ӳ����ӱ�
		{
			log.Info()<<"basketID = "<<basketID<<", layNO = "<<layNO<<", no record  in tabledetail, ready to insert..........."<<endl;
			string layValid = EAFPlanInfoDetail::LAY_VALID_YES;
			string status = EAFPlanInfoDetail::STATUS_NOT_START;
			SQL4EAF::InsEAFL2PlanDetailSingle(pono, basketID, pitNO, layNO, scrID, scrWeight, layValid, status);
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



map<long, bool> MsgEU01::Vec2Map1(vector<EAFPlanInfoDetail> vecPlanInfoDetail)
{
	string functionName="MsgEU01 :: Vec2Map()";
	LOG log(functionName, AUTO_CATCH_PID);

	map<long, bool> mapPlanInfoDetail;

	try
	{
		vector<EAFPlanInfoDetail>::iterator itor;
		for (itor = vecPlanInfoDetail.begin(); itor != vecPlanInfoDetail.end(); itor++)
		{
			EAFPlanInfoDetail	 planInfoDetail = *itor;
			mapPlanInfoDetail.insert(pair<long, bool>(planInfoDetail.getDetailID(), false));
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
	return mapPlanInfoDetail;
}

map<long, EAFPlanInfoDetail> MsgEU01::Vec2Map2(vector<EAFPlanInfoDetail> vecPlanInfoDetail)
{
	string functionName="MsgEU01 :: Vec2Map2()";
	LOG log(functionName, AUTO_CATCH_PID);

	map<long, EAFPlanInfoDetail> mapPlanInfoDetail;

	try
	{
		vector<EAFPlanInfoDetail>::iterator itor;
		for (itor = vecPlanInfoDetail.begin(); itor != vecPlanInfoDetail.end(); itor++)
		{
			EAFPlanInfoDetail	 planInfoDetail = *itor;
			mapPlanInfoDetail.insert(pair<long, EAFPlanInfoDetail>(planInfoDetail.getDetailID(), planInfoDetail));
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
	return mapPlanInfoDetail;
}


void MsgEU01::HandleMapDetailID(map<long, bool> mapDetailID, map<long, EAFPlanInfoDetail> mapPlanInfoDetail)
{
	string functionName="MsgEU01 :: HandleMapDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		map<long, bool>::iterator itor;
		for (itor = mapDetailID.begin(); itor != mapDetailID.end(); itor++)
		{
			long detalID = itor->first;
			bool bFlag = itor->second;
			if (bFlag == false)//SD�в����ڵĲ��
			{
				EAFPlanInfoDetail planInfoDetail = mapPlanInfoDetail[detalID];
				string carNO = planInfoDetail.getCarNO();
				string status = planInfoDetail.getStatus();

				long detailID = planInfoDetail.getDetailID();

				log.Info()<<"this DetailID = "<<detailID<<"  in database  plan is FALSE...means this database DetailID is not exist in TEL SD data ......"<<endl;
				if (carNO.empty())
				{
					log.Info()<<"car is empty , ready delete this deailID.........."<<endl;
					//û���䳵 ��ɾ��
					SQL4EAF::DelEAFPlanDetailByID(detailID);
					return;
				}
				//�������Ѿ��䳵��
				//��δ��ʼ=1��˵����δ����
				if (status == EAFPlanInfoDetail::STATUS_NOT_START)
				{
					log.Info()<<"car is not empty , but status is not start,  ready delete this detailID and CarPlanBand.........."<<endl;
					//����pono  detailIDɾ��������Ϣ�ƻ���������
					SQL4EAF::DelEAFPlanDetailByID(detailID);
					SQL4EAF::DelCarPlanBandByDetailID(detailID);
					return;
				}
				log.Info()<<"car is not empty , and status is start,  ready update this detailID to invalid ........."<<endl;
				//�������Ѿ��䳵���Ѿ�����
				//����pono , detailID���ӱ��¼���� layValid=2 �Ƿ� 
				SQL4EAF::UpdDetailInvalidByDetailID(detailID);
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


void MsgEU01::InsEAFL2PlanDetail(SmartData sd)
{
	string functionName="MsgEU01 :: InsEAFL2PlanDetail()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string pono = sd["PONO"].toString();	//���������
		string basketID;	//������
		string pitNO;		//��λ��
		string status = "1";
		string layValid= "1";

		for (int index = 0; index < 3; index++)
		{
			log.Info()<<"sd recycle: EAF_PLAN_DETAIL , index = "<<index<<endl;
			basketID = sd["EAF_PLAN_DETAIL"][index]["B_SEQ_NUM"].toString();
			pitNO = sd["EAF_PLAN_DETAIL"][index]["PIT_NUM"].toString();
			if (basketID.empty())
			{
				log.Info()<<"EAF_PLAN_DETAIL , index = "<<index<<", B_SEQ_NUM  is empty......."<<endl;
				continue;
			}

			for (int i = 1; i <=20; i++)
			{
				log.Info()<<"basketID = "<<basketID<<" recycle:  i = "<<i<<endl;
				string scrIDName = "SCR_ID_" + StringHelper::ToString(i);
				string scrWeightName = "SCR_WEIGHT_" + StringHelper::ToString(i);
				long layNO = i;
				//���� �� ��Ӧ�ľ����䷽�ϸִ������������
				string scrID = sd["EAF_PLAN_DETAIL"][index][scrIDName].toString();
				long scrWeight = Str2Num(sd["EAF_PLAN_DETAIL"][index][scrWeightName].toString());

				if (scrID.empty())
				{
					log.Info()<<" SCR_ID_  is empty......."<<endl;
					continue;
				}
				SQL4EAF::InsEAFL2PlanDetailSingle(pono, basketID, pitNO, layNO, scrID, scrWeight, layValid, status);
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