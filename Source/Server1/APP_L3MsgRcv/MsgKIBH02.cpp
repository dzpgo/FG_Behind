#include "MsgKIBH02.h"
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;

MsgKIBH02*  MsgKIBH02::m_pMsgKIBH02 = NULL;


MsgKIBH02::MsgKIBH02() 
{
	msgId="KIBH02";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgKIBH02 :: ~MsgKIBH02(void)
{

	delete m_pMsgKIBH02;


}

MsgKIBH02* MsgKIBH02::getInstance(void)
{
	if (m_pMsgKIBH02 == NULL)
	{
		m_pMsgKIBH02 = new MsgKIBH02;
	}
	return m_pMsgKIBH02;
}

ByteSeq MsgKIBH02::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgKIBH02 :: HandleMessage()";
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
		
		//���ϼ���϶��빤λ����

		//1		������/���뿪
		temp = sd["ARRIVE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["ARRIVE_FLAG"] = temp;
		log.Info()<<"ARRIVE_FLAG="<<sdTrim["ARRIVE_FLAG"].toString()<<endl;

		//2		�϶���
		temp = sd["HOPPER_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["HOPPER_NO"] = temp;
		log.Info()<<"HOPPER_NO="<<sdTrim["HOPPER_NO"].toString()<<endl;

		//3		��λ��
		temp = sd["POSITION_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["POSITION_NO"] = temp;
		log.Info()<<"POSITION_NO="<<sdTrim["POSITION_NO"].toString()<<endl;

		//4		����/�ն�
		temp = sd["LOAD_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["LOAD_FLAG"] = temp;
		log.Info()<<"LOAD_FLAG="<<sdTrim["LOAD_FLAG"].toString()<<endl;

		////5		��Ӧ���ϴ���
		//temp = sd["MAT_CODE_RELATE1"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["MAT_CODE_RELATE1"] = temp;
		//log.Info()<<"MAT_CODE_RELATE1="<<sdTrim["MAT_CODE_RELATE1"].toString()<<endl;

		//6		��ע1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//7		��ע2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//8		��ע3
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//9		��ע4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//10		��ע5
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
		HandleDataIntoDB(sdTrim, LogFileName);

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


void MsgKIBH02::HandleDataIntoDB(SmartData sd, string logFileName)
{
	string functionName="MsgKIBH02 :: HandleDataIntoDB()";
	LOG log(functionName, logFileName);

	try
	{
		string arriveFlag = sd["ARRIVE_FLAG"].toString();//������/���뿪
		string hopperNO = sd["HOPPER_NO"].toString();//�϶���
		string positionNO = sd["POSITION_NO"].toString();//��λ��
		string loadFlag = sd["LOAD_FLAG"].toString();//����/�ն�
		

		//���¹�λ���ձ�����
		SQL4L3::UpdateMatCarRelationInfo(arriveFlag, hopperNO, positionNO, loadFlag);
		log.Info()<<"positionNO = "<<positionNO<<" , UpdateMatCarRelationInfo.........return.........."<<endl;
		return;
		//�� compCode ����ת����vector �����������
		//vector<string> vecCompCode;
		//vecCompCode = StringHelper::ToVector<string>(compCodeSet, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

		////ɾ����ǣ���ֱ��ɾ��
		//if (operateFlag == "D")
		//{
		//	log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
		//	DelMatCodeCompCode(matCode, vecCompCode, matCodeRelate1);
		//	return;
		//}

		//if (operateFlag == "I")
		//{
		//	log.Info()<<"operateFlag = "<<operateFlag<<" , insert or update.........return.........."<<endl;
		//	//��ɾ�����ٲ��룬�������Ƿ�ԭ�ȴ��ڵ��ж���
		//	DelMatCodeCompCode(matCode, vecCompCode, matCodeRelate1);
		//	InsMatCodeCompCode(exterSystem, matCode, vecCompCode, matCodeRelate1);
		//	return;
		//}	
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


void MsgKIBH02::DelMatCodeCompCode(string matCode, vector<string> vecCompCode, string matCodeRelate)
{
	string functionName="MsgKIBH02 :: DelMatCodeCompCode()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		vector<string>::iterator itor;
		for (itor = vecCompCode.begin(); itor != vecCompCode.end(); itor++)
		{
			string compCode = *itor;
			SQL4L3::DelMatRelationInfo(matCode, compCode, matCodeRelate);
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

void MsgKIBH02::InsMatCodeCompCode(string exterSystem, string matCode, vector<string> vecCompCode, string matCodeRelate)
{
	string functionName="MsgKIBH02 :: InsMatCodeCompCode()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		vector<string>::iterator itor;
		for (itor = vecCompCode.begin(); itor != vecCompCode.end(); itor++)
		{
			string compCode = *itor;
			SQL4L3::InsertMatRelationInfo(exterSystem, matCode, compCode, matCodeRelate);
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

