#include "MsgP4HC03.h"
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;

MsgP4HC03*  MsgP4HC03::m_pMsgP4HC03 = NULL;


MsgP4HC03::MsgP4HC03() 
{
	msgId="P4HC03";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgP4HC03 :: ~MsgP4HC03(void)
{

	delete m_pMsgP4HC03;


}

MsgP4HC03* MsgP4HC03::getInstance(void)
{
	if (m_pMsgP4HC03 == NULL)
	{
		m_pMsgP4HC03 = new MsgP4HC03;
	}
	return m_pMsgP4HC03;
}

ByteSeq MsgP4HC03::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgP4HC03 :: HandleMessage()";
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

		//3		�ϸ����
		temp = sd["STOCK_PLACE_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["STOCK_PLACE_CODE"] = temp;
		log.Info()<<"STOCK_PLACE_CODE="<<sdTrim["STOCK_PLACE_CODE"].toString()<<endl;

		//4		����/�����
		temp = sd["STOCK_LOC_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["STOCK_LOC_CODE"] = temp;
		log.Info()<<"STOCK_LOC_CODE="<<sdTrim["STOCK_LOC_CODE"].toString()<<endl;

		//5		����/������ַ
		temp = sd["STORERM_ADDR_MIN"].toString();
		StringHelper::Trim(temp);
		sdTrim["STORERM_ADDR_MIN"] = temp;
		log.Info()<<"STORERM_ADDR_MIN="<<sdTrim["STORERM_ADDR_MIN"].toInt()<<endl;

		//6		����/���յ��ַ
		temp = sd["STORERM_ADDR_MAX"].toString();
		StringHelper::Trim(temp);
		sdTrim["STORERM_ADDR_MAX"] = temp;
		log.Info()<<"STORERM_ADDR_MAX="<<sdTrim["STORERM_ADDR_MAX"].toInt()<<endl;

		//7		���ϴ���
		temp = sd["MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE"] = temp;
		log.Info()<<"MAT_CODE="<<sdTrim["MAT_CODE"].toString()<<endl;

		//8		�ϸָ�����
		temp = sd["COMP_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["COMP_CODE"] = temp;
		log.Info()<<"COMP_CODE="<<sdTrim["COMP_CODE"].toString()<<endl;

		//9		��ʼʱ��
		temp = sd["START_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["START_TIME"] = temp;
		log.Info()<<"START_TIME="<<sdTrim["START_TIME"].toString()<<endl;

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
		//�����ݴ浽���ͱ���
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



void MsgP4HC03::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgP4HC03 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//������� I-����  D-ɾ��
		string stockCode = sd["STOCK_CODE"].toString();//��������
		string stockPlaceCode = sd["STOCK_PLACE_CODE"].toString();//�ϸ����
		string stockLocCode = sd["STOCK_LOC_CODE"].toString();//����/�����
		long storermAddrMin = sd["STORERM_ADDR_MIN"].toInt();//����/����ʼ��ַ
		long storermAddrMax = sd["STORERM_ADDR_MAX"].toInt();//����/���յ��ַ
		string matCode = sd["MAT_CODE"].toString();//���ϴ���
		string compCode = sd["COMP_CODE"].toString();//���ƴ���
		string startTime = sd["START_TIME"].toString();//��ʼʱ��


		//������д�����ݿ��
		//20220818 zhangyuhong add
		//�յ��˵��ĺ�, ���ϸ��ͼ����и���:
		//1. �����ϸ�Ÿ��¶�Ӧ���ϴ��롢������,��ͬʱ�Կ������������
		//2. �����ɾ����־,������ϸ�Ž����ϴ���\�������ÿ�,�Կ��������

		//ɾ����ǣ���ֱ��ɾ��
		if (operateFlag == "D")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
			SQL4L3::DelMatGridInfo(stockPlaceCode);

			//�Կ�ͼ������޸�
			SQL4L3::InitYardMapGridInfo(stockPlaceCode);

			return;
		}

		if (operateFlag == "I")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , insert or update.........return.........."<<endl;
			//��ɾ��,�ٲ���
			SQL4L3::DelMatGridInfo(stockPlaceCode);
			SQL4L3::InsertMatGridInfo(stockCode, stockPlaceCode, stockLocCode, storermAddrMin, storermAddrMax, matCode, compCode, startTime);

			//�Կ�ͼ������޸�
			SQL4L3::UpdYardMapGridInfo(stockPlaceCode, matCode, compCode);

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

