#include "MsgP4HC12.h"
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;

MsgP4HC12*  MsgP4HC12::m_pMsgP4HC12 = NULL;


MsgP4HC12::MsgP4HC12() 
{
	msgId="P4HC12";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgP4HC12 :: ~MsgP4HC12(void)
{

	delete m_pMsgP4HC12;


}

MsgP4HC12* MsgP4HC12::getInstance(void)
{
	if (m_pMsgP4HC12 == NULL)
	{
		m_pMsgP4HC12 = new MsgP4HC12;
	}
	return m_pMsgP4HC12;
}

ByteSeq MsgP4HC12::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgP4HC12 :: HandleMessage()";
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
		log.Info()<<"..................................................................log of samrt data......................................................"<<endl;
		string temp = "";

		//1		������־
		temp = sd["OPERATE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["OPERATE_FLAG"] = temp;
		log.Info()<<"OPERATE_FLAG="<<sdTrim["OPERATE_FLAG"].toString()<<endl;

		//2		��ˮ��
		temp = sd["WORK_SEQ_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["WORK_SEQ_NO"] = temp;
		log.Info()<<"WORK_SEQ_NO="<<sdTrim["WORK_SEQ_NO"].toString()<<endl;

		//3		�����г���ˮ��
		temp = sd["HC_WORK_SEQ_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["HC_WORK_SEQ_NO"] = temp;
		log.Info()<<"HC_WORK_SEQ_NO="<<sdTrim["HC_WORK_SEQ_NO"].toString()<<endl;

		//4		����
		temp = sd["CAR_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["CAR_NO"] = temp;
		log.Info()<<"CAR_NO="<<sdTrim["CAR_NO"].toString()<<endl;

		//5		���������
		temp = sd["WEIGH_APP_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGH_APP_NO"] = temp;
		log.Info()<<"WEIGH_APP_NO="<<sdTrim["WEIGH_APP_NO"].toString()<<endl;

		//6		��������ʱ��
		temp = sd["WEIGH_APP_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGH_APP_TIME"] = temp;
		log.Info()<<"WEIGH_APP_TIME="<<sdTrim["WEIGH_APP_TIME"].toString()<<endl;

		//7		������
		temp = sd["REC_CREATOR"].toString();
		StringHelper::Trim(temp);
		sdTrim["REC_CREATOR"] = temp;
		log.Info()<<"REC_CREATOR="<<sdTrim["REC_CREATOR"].toString()<<endl;

		//8		������
		temp = sd["WEIGH_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGH_NO"] = temp;
		log.Info()<<"WEIGH_NO="<<sdTrim["WEIGH_NO"].toString()<<endl;

		//9		ë��
		temp = sd["GROSS_WGT"].toString();
		StringHelper::Trim(temp);
		sdTrim["GROSS_WGT"] = temp;
		log.Info()<<"GROSS_WGT="<<sdTrim["GROSS_WGT"].toInt()<<endl;

		//10		Ƥ��
		temp = sd["TARE_WGT"].toString();
		StringHelper::Trim(temp);
		sdTrim["TARE_WGT"] = temp;
		log.Info()<<"TARE_WGT="<<sdTrim["TARE_WGT"].toInt()<<endl;

		//11		����
		temp = sd["NET_WGT"].toString();
		StringHelper::Trim(temp);
		sdTrim["NET_WGT"] = temp;
		log.Info()<<"NET_WGT="<<sdTrim["NET_WGT"].toInt()<<endl;

		//12		ë��ʱ��
		temp = sd["GROSS_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["GROSS_TIME"] = temp;
		log.Info()<<"GROSS_TIME="<<sdTrim["GROSS_TIME"].toString()<<endl;

		//13		Ƥ��ʱ��
		temp = sd["TARE_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["TARE_TIME"] = temp;
		log.Info()<<"TARE_TIME="<<sdTrim["TARE_TIME"].toString()<<endl;

		//14		����ʱ��
		temp = sd["WEIGH_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGH_TIME"] = temp;
		log.Info()<<"WEIGH_TIME="<<sdTrim["WEIGH_TIME"].toString()<<endl;

		//15 	Դ��������
		temp = sd["SRC_STOCK_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["SRC_STOCK_CODE"] = temp;
		log.Info()<<"SRC_STOCK_CODE="<<sdTrim["SRC_STOCK_CODE"].toString()<<endl;

		//16		Դ��λ����
		temp = sd["SRC_LOC_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["SRC_LOC_CODE"] = temp;
		log.Info()<<"SRC_LOC_CODE="<<sdTrim["SRC_LOC_CODE"].toString()<<endl;

		//17		�������ϴ���
		temp = sd["SRC_MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["SRC_MAT_CODE"] = temp;
		log.Info()<<"SRC_MAT_CODE="<<sdTrim["SRC_MAT_CODE"].toString()<<endl;

		//18		�������ƴ���
		temp = sd["SRC_COMP_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["SRC_COMP_CODE"] = temp;
		log.Info()<<"SRC_COMP_CODE="<<sdTrim["SRC_COMP_CODE"].toString()<<endl;

		//19		Ŀ�Ŀ�������
		temp = sd["DST_STOCK_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["DST_STOCK_CODE"] = temp;
		log.Info()<<"DST_STOCK_CODE="<<sdTrim["DST_STOCK_CODE"].toString()<<endl;

		//20		Ŀ�Ŀ�λ����
		temp = sd["DST_LOC_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["DST_LOC_CODE"] = temp;
		log.Info()<<"DST_LOC_CODE="<<sdTrim["DST_LOC_CODE"].toString()<<endl;

		//21		�շ����ϴ���
		temp = sd["DST_MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["DST_MAT_CODE"] = temp;
		log.Info()<<"DST_MAT_CODE="<<sdTrim["DST_MAT_CODE"].toString()<<endl;

		//22		�շ����ƴ���
		temp = sd["DST_COMP_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["DST_COMP_CODE"] = temp;
		log.Info()<<"DST_COMP_CODE="<<sdTrim["DST_COMP_CODE"].toString()<<endl;

		//23		BACK1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//24		BACK2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//25		BACK3
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//26		BACK4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//27		BACK5
		//log.Info()<<"\t\t BACK5="<<sd["BACK5"].toString();

		//28		ѭ������
		temp = sd["LOOP_COUNT"].toString();
		StringHelper::Trim(temp);
		sdTrim["LOOP_COUNT"] = temp;
		log.Info()<<"LOOP_COUNT="<<sdTrim["LOOP_COUNT"].toInt()<<endl;
		log.Info()<<"LOOP_COUNT1="<<sd["LOOP_COUNT"].toInt()<<endl;



		int loopCount = sdTrim["LOOP_COUNT"].toInt();
		for (int i = 0; i < loopCount; ++i)
		{
			log.Info()<<"\t Index In Loop = "<<i<<" : ";
			//��λ/�ϸ��
			temp = sd["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"].toString();
			StringHelper::Trim(temp);
			sdTrim["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"] = temp;
			log.Info()<<" STOCK_PLACE_CODE = "<<sdTrim["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"].toString();	

			//���ϴ���
			temp = sd["P4HC12_DETAIL"][i]["MAT_CODE"].toString();
			StringHelper::Trim(temp);
			sdTrim["P4HC12_DETAIL"][i]["MAT_CODE"] = temp;
			log.Info()<<" MAT_CODE = "<<sdTrim["P4HC12_DETAIL"][i]["MAT_CODE"].toString();

			//���ƴ���
			temp = sd["P4HC12_DETAIL"][i]["COMP_CODE"].toString();
			StringHelper::Trim(temp);
			sdTrim["P4HC12_DETAIL"][i]["COMP_CODE"] = temp;
			log.Info()<<" COMP_CODE = "<<sdTrim["P4HC12_DETAIL"][i]["COMP_CODE"].toString();

			//��̯����
			temp = sd["P4HC12_DETAIL"][i]["WGT"].toString();
			StringHelper::Trim(temp);
			sdTrim["P4HC12_DETAIL"][i]["WGT"] = temp;
			log.Info()<<" WGT = "<<sdTrim["P4HC12_DETAIL"][i]["WGT"].toInt()<<endl;
		}

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

		L3ZCWgtNotify(sdTrim);
		

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


void MsgP4HC12::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgP4HC12 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//������� I-����  D-ɾ��
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//��ˮ��
		string hcWorkSeqNO= sd["HC_WORK_SEQ_NO"].toString();//�����г���ˮ��
		string carNO = sd["CAR_NO"].toString();//����
		string weighAppNo = sd["WEIGH_APP_NO"].toString();//���������
		string weighAppTime = sd["WEIGH_APP_TIME"].toString();//��������ʱ��
		string recCreator = sd["REC_CREATOR"].toString();//������
		string weighNO = sd["WEIGH_NO"].toString();//������
		int grossWgt = sd["GROSS_WGT"].toInt();//ë��
		int tareWgt = sd["TARE_WGT"].toInt();//Ƥ��
		int netWgt = sd["NET_WGT"].toInt();//����
		string grossTime = sd["GROSS_TIME"].toString();//ë��ʱ��
		string tareTime = sd["TARE_TIME"].toString();//Ƥ��ʱ��
		string weighTime = sd["WEIGH_TIME"].toString();//����ʱ��
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//Դ��������
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//Դ��λ����
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//�������ϴ���
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//�������ƴ���
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//Ŀ�Ŀ�������
		string dstLocCode = sd["DST_LOC_CODE"].toString();//Ŀ�Ŀ�λ����
		string dstMatCode = sd["DST_MAT_CODE"].toString();//�շ����ϴ���
		string dstCompCode = sd["DST_COMP_CODE"].toString();//�շ����ƴ���

		int loopCount = sd["LOOP_COUNT"].toInt();//rgv����װ��ѭ������

		//�Ƿ���ڼ�¼�������ڣ���ֱ�Ӹ��²����¼�¼
		if (false == SQL4L3::MatWeightInfoExist(workSeqNO))
		{
			log.Info()<<"workSeqNO = "<<workSeqNO<<" , no record in table , insert into .........return.........."<<endl;
			SQL4L3::InsertMatWeightTable(sd);
			return;
		}

		//���ڼ�¼�������
		log.Info()<<"workSeqNO = "<<workSeqNO<<" , have record in table ....update......"<<endl;
		//1.ֱ�Ӹ��³�������
		SQL4L3::UpdateMatWeightInfo(sd);
		//2. ���loopCountΪ0  ��ɾ��rgv�ӱ� ; �����Ϊ0  ����ɾ���ӱ�,�ٲ����ӱ�
		if (loopCount > 0)
		{
			log.Info()<<"loopCount = "<<loopCount<<" ,  DelMatWeightRGVInfo,   then   InsertMatWeightRGVInfo...........return........"<<endl;
			SQL4L3::DelMatWeightRGVInfo(workSeqNO);
			SQL4L3::InsertMatWeightRGVInfo(sd);			
			return;
		}
		else
		{
			log.Info()<<"loopCount = "<<loopCount<<" , DelMatWeightRGVInfo ..return........"<<endl;
			SQL4L3::DelMatWeightRGVInfo(workSeqNO);
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


bool MsgP4HC12::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgP4HC12 :: EVTagSnd()";
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


void MsgP4HC12::L3ZCWgtNotify(SmartData sd)
{
	string functionName="MsgP4HC12 :: L3ZCWgtNotify()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		//������ˮ�� �����г���ˮ�� ֪ͨ��Ӧģ����������װ��ʵ��
		string tagName = "";
		string tagValue = "";
		string seqNO = sd["WORK_SEQ_NO"].toString();
		string hcSeqNO = sd["HC_WORK_SEQ_NO"].toString();
		string netWgt = sd["NET_WGT"].toString();

		string strLoop = sd["LOOP_COUNT"].toString();

		if (netWgt.empty())
		{
			log.Info()<<"netWgt is empty, return..........."<<endl;
			return;
		}

		//���ڵ�¯װ����������:
		//1. ֪ͨ��¯L2ģ�����ʵ�������͸���¯L2���³�����Ϣ
		//2. �ɵ�¯ģ��ָ֪ͨ��ģ��У���ϸ�����
		if (hcSeqNO.find("DL") != string::npos)
		{
			log.Info()<<"this is  EAF ZC WGT from L3..............."<<endl;
			tagName = "EV_L3_EAF_ZC_WGT";
			tagValue = hcSeqNO + "," + netWgt;

			log.Info()<<"EV_L3_EAF_ZC_WGT  tagValue = "<<tagValue<<endl;
		}


		//����ת¯װ����������:
		//1. ֪ͨת¯L2ģ�����ʵ�����ٴη��͸�ת¯L2
		//2. ָ֪ͨ��ģ������ϸ�����Ϣ
		else if (hcSeqNO.find("LG") != string::npos)
		{
			log.Info()<<"this is  BOF ZC WGT from L3..............."<<endl;
			tagName = "EV_L3_BOF_ZC_WGT";
			tagValue = hcSeqNO + "," + netWgt;

			if (strLoop.empty() || strLoop == "0")
			{
				log.Info()<<"loop count is empty or = 0, return.........."<<endl;
				return;
			}

			//��֯rgv����������̯���ݣ� �ϸ��,���ϴ���,���ƴ���,��̯����
			string rgvPartMsg = GetRgvMatInfo(sd);
			tagValue += "," + rgvPartMsg;

			log.Info()<<"EV_L3_BOF_ZC_WGT  tagValue = "<<tagValue<<endl;
			
		}
		//����L3װ��ʵ��
		else
		{
			log.Info()<<"this is  L3 ZC WGT from L3..............."<<endl;
			tagName = "EV_L3_ZC_WGT";
			tagValue = seqNO + "," + netWgt;

			log.Info()<<"EV_L3_ZC_WGT  tagValue = "<<tagValue<<endl;
		}

		//�·�֪ͨ
		EVTagSnd(tagName, tagValue);

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

string MsgP4HC12::GetRgvMatInfo(SmartData sd)
{
	string functionName="MsgP4HC12 :: L3ZCWgtNotify()";
	LOG log(functionName, AUTO_CATCH_PID);

	string rgvPartMsg = "";

	try
	{
		int loopCount = sd["LOOP_COUNT"].toInt();
		for (int i = 0; i < loopCount; ++i)
		{
			if (i > 0)
			{
				rgvPartMsg += ",";
			}
			//��λ/�ϸ��
			string temp1 = sd["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"].toString();
			StringHelper::Trim(temp1);

			//���ϴ���
			string temp2 = sd["P4HC12_DETAIL"][i]["MAT_CODE"].toString();
			StringHelper::Trim(temp2);

			//���ƴ���
			string temp3 = sd["P4HC12_DETAIL"][i]["COMP_CODE"].toString();
			StringHelper::Trim(temp3);

			//��̯����
			string temp4 = sd["P4HC12_DETAIL"][i]["WGT"].toString();
			StringHelper::Trim(temp4);

			rgvPartMsg += temp1 + "#" + temp2 + "#" + temp3 + "#" + temp4;


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

	return rgvPartMsg;

}