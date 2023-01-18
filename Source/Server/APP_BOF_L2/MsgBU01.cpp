#include "MsgBU01.h"
#include <climits>
#include <iXcomTCP2.h>
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;
using namespace std;
using namespace iXcomTCP2;



MsgBU01*  MsgBU01::m_pMsgBU01 = NULL;


MsgBU01::MsgBU01() 
{
	msgId="BU01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}



MsgBU01 :: ~MsgBU01(void)
{

	delete m_pMsgBU01;


}

MsgBU01* MsgBU01::getInstance(void)
{
	if (m_pMsgBU01 == NULL)
	{
		m_pMsgBU01 = new MsgBU01;
	}
	return m_pMsgBU01;
}

ByteSeq MsgBU01::HandleMessage(const ByteSeq& ParamBuffer)
{
	string functionName="MsgBU01 :: HandleMessage()";

	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{

		// ��ȡpowertrans���Ľṹ
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			readSmartDataSuccessed=true;
		}


		//��ȡԭʼ�ֽ���
		sd.readFrom(ParamBuffer);
		log.Info()<<"........................................................................................log of samrt data..................................................................................................................."<<endl;

		//��Ҫע��Ӧ��ͷ����2���ֶΣ���Ҫע����t_bm_msgitem���ȥ


		//log.Info()<<"INT_MIN = "<<INT_MIN<<endl;

		//1		�ֺ�
		log.Info()<<"\t\t STEEL_NO="<<sd["STEEL_NO"].toInt();
		//2		�ƻ�����
		log.Info()<<"\t\t PLAN_TYPE="<<sd["PLAN_TYPE"].toInt();//1-����ƻ���RGVװ����  2-���üƻ����������ò�װ����
		//3		�ƻ����
		log.Info()<<"\t\t PLAN_FLAG="<<sd["PLAN_FLAG"].toInt()<<endl;//1-����  2-�޸�  3-ɾ��		
		//����ѭ����
		for (int index = 0; index < 20; index++)
		{
			//�ϸִ���
			log.Info()<<"\t\t SCRAP_CODE��"<<sd["BU01_DETAIL"][index]["SCRAP_CODE"].toInt();
			//�ϸ�������
			log.Info()<<"\t\t REQ_WEIGHT��"<<sd["BU01_DETAIL"][index]["REQ_WEIGHT"].toInt()<<endl;		
		}

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
		dealdata.InsertRcvData(msgId,dataStr,data,ID);

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

void MsgBU01::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgBU01 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string steelNO = sd["STEEL_NO"].toString();//�ֺ� ���ƻ��ţ�
		string planType = sd["PLAN_TYPE"].toString();//�ƻ�����  1-����ƻ���RGVװ����  2-���üƻ����������ò�װ����
		string planFlag = sd["PLAN_FLAG"].toString();//�ƻ���� 1-����  2-�޸�  3-ɾ��

		//���ݿ����Ƿ��Ѵ��ڼƻ�
		string planStatus = "";
		bool planExist = SQL4BOF::BOFL2PlanExist(steelNO, planStatus);
		if ( planExist == false )//�����ڣ�ֱ��д��
		{
			log.Info()<<"New plan , insert ..................."<<endl;
			SQL4BOF::InsertBOFL2PlanMain(sd);
			SQL4BOF::InsertBOFL2PlanDetail(sd);
			return;
		}

		//�����Ǽƻ����ڵ�����ж�
		log.Info()<<"Old plan , update..................."<<endl;
		log.Info()<<"planStatus = "<<planStatus<<" ��1��δ��ʼ  2���ѿ�ʼ  3������ɣ�...................."<<endl;
		//ֱ�Ӹ�������
		SQL4BOF::UpdatePlanMain(steelNO, planType, planFlag);
		//1. ��δ��ʼװ�� ��ֱ�Ӹ�������  �����ӱ������ӱ�취����ɾ���ӱ����ݣ��ٲ��������ϼƻ���
		if ( planStatus == "1")
		{
			//����ƻ���ɾ�����������ӱ��planValidΪ 2-�Ƿ�
			if (planType == "3")
			{
				log.Info()<<"planType = "<<planType<<" , Update plan detail planValid to 2..........."<<endl;
				//��������  �ӱ� �� planValid =2
				SQL4BOF::UpdatePlanMainPlanValid(steelNO, planType, planFlag);
				SQL4BOF::UpdatePlanDetailPlanValid(steelNO);
				return;
			}
			//����ƻ����������޸�  �����ӱ������ӱ�취����ɾ���ӱ����ݣ��ٲ��������ϼƻ���
			if (planType == "1" || planType == "2")
			{
				log.Info()<<"planType = "<<planType<<" , Update plan detail : first-del old; second-insert new..........."<<endl;
				SQL4BOF::DelPlanDetail(steelNO);
				SQL4BOF::InsertBOFL2PlanDetail(sd);
				return;
			}
		}

		//2. �Ѿ���ʼװ����װ�����
		if (planStatus == "2" || planStatus == "3")
		{
			//��������ͬʱ���������е�planValid�ֶ�  �����˼ƻ��Ѿ��Ƿ�  ��Ϊ�˼ƻ��Ѿ���ʼװ��  ����Ϣ�����ڻ�����չʾ�������˹�����
			//SQL4BOF::UpdatePlanMainPlanValid(steelNO, planType, planFlag);
			//����ƻ���ɾ���������ӱ��planValidΪ 2-�Ƿ�
			if (planType == "3")
			{
				log.Info()<<"planType = "<<planType<<" , Update plan detail planValid to 2..........."<<endl;
				SQL4BOF::UpdatePlanMainPlanValid(steelNO, planType, planFlag);
				SQL4BOF::UpdatePlanDetailPlanValid(steelNO);
				return;
			}
			//����ƻ����������޸�  �����ӱ������ӱ�취������2�����ϼƻ�, �ϼƻ����¼ƻ�,�������Ϊ: �ȸ����ϼƻ�planValid���ٲ��������ϼƻ���
			if (planType == "1" || planType == "2")
			{
				//������ĺ��Ѵ����䷽һ��(���ϴ������������һ��)�������޸�
				map<string, long> mapMatDetail;
				bool matDetailExist = SQL4BOF::SelectPlanDetailMatWgt(steelNO, mapMatDetail);
				if (true == matDetailSame2SD(mapMatDetail, sd))
				{
					log.Info()<<"mapMatDetail = sd...............no need to update............."<<endl;
					return;
				}

				log.Info()<<"planType = "<<planType<<" , Update plan detail : first-update old planValid; second-insert new..........."<<endl;
				SQL4BOF::UpdatePlanDetailPlanValid(steelNO);
				SQL4BOF::InsertBOFL2PlanDetail(sd);
				return;
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


bool MsgBU01::matDetailSame2SD(map<string, long> matDetail, SmartData sd)
{
	string functionName="MsgBU01 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool ret = false;

	try
	{
		
		map<string, long> matDetailSD;
		int scrID = 0;
		int scrWeight = 0;
		for (int index = 0; index < 20; index++)
		{
			scrID = sd["BU01_DETAIL"][index]["SCRAP_CODE"].toInt();
			if (scrID == INT_MIN)
			{
				log.Info()<<"BU01_DETAIL, index = "<<index<<", scrID = "<<scrID<<",  is not need to treat.........."<<endl;
				continue;
			}
			string strScrID = StringHelper::ToString(scrID);
			scrWeight = sd["BU01_DETAIL"][index]["REQ_WEIGHT"].toInt();
			if (scrWeight == INT_MIN)
			{
				log.Info()<<"BU01_DETAIL, index = "<<index<<", scrWeight = "<<scrWeight<<", ready to set scrWeight=0.........."<<endl;
				scrWeight = 0;
			}
			long lScrWeight = (long)scrWeight;
			matDetailSD.insert(map<string, long>::value_type(strScrID, lScrWeight));
		}

		bool sameSize = ( matDetail.size() == matDetailSD.size() );
		if (sameSize == false)
		{
			log.Info()<<"matDetail.size() <> matDetailSD.size(), return false.................."<<endl;
			ret = false;
			return ret;
		}

		bool sameMatAndWgt = true;
		map<string, long>::iterator itor;
		for (itor = matDetail.begin(); itor != matDetail.end(); itor++)
		{
			string matCode = itor->first;
			long matWgt = itor->second;
			map<string, long>::iterator itor1;
			itor1 = matDetailSD.find(matCode);
			if (itor1 != matDetailSD.end() && itor1->second == matWgt)
			{
				log.Info()<<"matCode = "<<matCode<<" , matWgt="<<matWgt<<" .......FIND in matDetail and matDetailSD.......ok!"<<endl;
			}
			else
			{
				log.Info()<<"matCode = "<<matCode<<" , matWgt="<<matWgt<<" .........FIND in matDetail but NOT FIND in matDetailSD..OR Weight is not SAME...not ok!"<<endl;
				sameMatAndWgt = false;
				break;
			}
		}
		if (sameMatAndWgt == false)
		{
			ret = false;
			return ret;
		}
		ret = true;
		return ret;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
		return ret;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
		return ret;
	}
	return ret;

}



