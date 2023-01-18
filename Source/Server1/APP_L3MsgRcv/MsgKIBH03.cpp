#include "MsgKIBH03.h"
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;

MsgKIBH03*  MsgKIBH03::m_pMsgKIBH03 = NULL;


MsgKIBH03::MsgKIBH03() 
{
	msgId="KIBH03";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgKIBH03 :: ~MsgKIBH03(void)
{

	delete m_pMsgKIBH03;


}

MsgKIBH03* MsgKIBH03::getInstance(void)
{
	if (m_pMsgKIBH03 == NULL)
	{
		m_pMsgKIBH03 = new MsgKIBH03;
	}
	return m_pMsgKIBH03;
}

ByteSeq MsgKIBH03::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgKIBH03 :: HandleMessage()";
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
		log.Info()<<"........................................................................................log of samrt data..................................................................................."<<endl;
		string temp = "";

		//1		������־
		temp = sd["OPERATE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["OPERATE_FLAG"] = temp;
		log.Info()<<"OPERATE_FLAG="<<sdTrim["OPERATE_FLAG"].toString()<<endl;

		//2		��������
		temp = sd["STOCK_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["STOCK_CODE"] = temp;
		log.Info()<<"STOCK_CODE="<<sdTrim["STOCK_CODE"].toString()<<endl;

		//3		�ϸ��
		temp = sd["STOCK_LOC_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["STOCK_LOC_CODE"] = temp;
		log.Info()<<"STOCK_LOC_CODE="<<sdTrim["STOCK_LOC_CODE"].toString()<<endl;

		//4		���ϴ���
		temp = sd["MAT_PROD_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_PROD_CODE"] = temp;
		log.Info()<<"MAT_PROD_CODE="<<sdTrim["MAT_PROD_CODE"].toString()<<endl;

		//5		��������
		temp = sd["MAT_PROD_CNAME"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_PROD_CNAME"] = temp;
		log.Info()<<"MAT_PROD_CNAME="<<sdTrim["MAT_PROD_CNAME"].toInt()<<endl;

		//6		�ϸֳɷ������
		temp = sd["COMP_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["COMP_CODE"] = temp;
		log.Info()<<"COMP_CODE="<<sdTrim["COMP_CODE"].toInt()<<endl;

		//7		��ǰ�����
		temp = sd["CUR_STOCK_WGT"].toString();
		StringHelper::Trim(temp);
		sdTrim["CUR_STOCK_WGT"] = temp;
		log.Info()<<"CUR_STOCK_WGT="<<sdTrim["CUR_STOCK_WGT"].toInt()<<endl;

		//8		���ñ��
		temp = sd["INHIIBT_USE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["INHIIBT_USE_FLAG"] = temp;
		log.Info()<<"INHIIBT_USE_FLAG="<<sdTrim["INHIIBT_USE_FLAG"].toString()<<endl;

		//9		�������
		temp = sd["PILE_DATE"].toString();
		StringHelper::Trim(temp);
		sdTrim["PILE_DATE"] = temp;
		log.Info()<<"PILE_DATE="<<sdTrim["PILE_DATE"].toString()<<endl;

		//10		��ע1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//11		��ע2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//12		��ע3
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//13		��ע4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//14		��ע5
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
		//�����ݴ浽���ձ���
		dealdata.InsertRcvData(msgId,dataStr,data,ID);

		HandleDataIntoDB(sdTrim);



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



void MsgKIBH03::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgKIBH03 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//������� I-����  D-ɾ��
		string stockCode = sd["STOCK_CODE"].toString();//��������
		string locCode = sd["STOCK_LOC_CODE"].toString();//�ϸ����
		string matCode = sd["MAT_PROD_CODE"].toString();//���ϴ���
		string matName = sd["MAT_PROD_CNAME"].toString();//��������
		string compCode = sd["COMP_CODE"].toString();//�ϸֳɷ������
		int curWt = sd["CUR_STOCK_WGT"].toInt();//��ǰ�����
		string iUFlag = sd["INHIIBT_USE_FLAG"].toString();//���ñ��
		string pileTime = sd["PILE_DATE"].toString();//���ʱ��


		//������д�����ݿ��
		//20220818 zhangyuhong add
		//�յ��˵��ĺ�, ���ϸ��ͼ����и���:
		//1. �����ϸ�Ÿ��¶�Ӧ���ϴ��롢������,��ͬʱ�Կ������������
		//2. �����ɾ����־,������ϸ�Ž����ϴ���\�������ÿ�,�Կ��������

		//ɾ����ǣ���ֱ��ɾ��
		//if (operateFlag == "D")
		//{
		//	log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
		//	SQL4L3::DelMatGridInfo(stockPlaceCode);

		//	//�Կ�ͼ������޸�
		//	SQL4L3::InitYardMapGridInfo(stockPlaceCode);

		//	return;
		//}

		if (operateFlag == "I")
		{
			stockCode=stockCode+"0";
			log.Info()<<"operateFlag =I, stockCode= "<<stockCode<<" , insert or update.........return.........."<<endl;
			//��ɾ��,�ٲ���
			//SQL4L3::DelMatGridInfo(stockPlaceCode);
			//SQL4L3::InsertMatGridInfo(stockCode, stockPlaceCode, stockLocCode, storermAddrMin, storermAddrMax, matCode, compCode, startTime);

			//�Կ�ͼ������޸�
			SQL4L3::UpdYardMapGridInfo(stockCode, matCode, compCode, curWt);

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

