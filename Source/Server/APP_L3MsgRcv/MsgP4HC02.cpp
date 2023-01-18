#include "MsgP4HC02.h"
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;

MsgP4HC02*  MsgP4HC02::m_pMsgP4HC02 = NULL;


MsgP4HC02::MsgP4HC02() 
{
	msgId="P4HC02";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgP4HC02 :: ~MsgP4HC02(void)
{

	delete m_pMsgP4HC02;


}

MsgP4HC02* MsgP4HC02::getInstance(void)
{
	if (m_pMsgP4HC02 == NULL)
	{
		m_pMsgP4HC02 = new MsgP4HC02;
	}
	return m_pMsgP4HC02;
}

ByteSeq MsgP4HC02::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgP4HC02 :: HandleMessage()";
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
		
		//�ѳ��ϸ�Ʒ���볧��Ʒ�����չ�ϵ����

		//1		������־
		temp = sd["OPERATE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["OPERATE_FLAG"] = temp;
		log.Info()<<"OPERATE_FLAG="<<sdTrim["OPERATE_FLAG"].toString()<<endl;//I:���� D:ɾ��

		//2		�ⲿϵͳ
		temp = sd["EXTER_SYSTEM"].toString();
		StringHelper::Trim(temp);
		sdTrim["EXTER_SYSTEM"] = temp;
		log.Info()<<"EXTER_SYSTEM="<<sdTrim["EXTER_SYSTEM"].toString()<<endl;//LG:�ϸ������ַϸֶ��չ�ϵ��DL:�ϸ����¯�ϸֶ��չ�ϵ

		//3		���ϴ���
		temp = sd["MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE"] = temp;
		log.Info()<<"MAT_CODE="<<sdTrim["MAT_CODE"].toString()<<endl;

		//4		�ϸָ����뼯��
		temp = sd["COMP_CODE_SET"].toString();
		StringHelper::Trim(temp);
		sdTrim["COMP_CODE_SET"] = temp;
		log.Info()<<"COMP_CODE_SET="<<sdTrim["COMP_CODE_SET"].toString()<<endl;//20220520 �Ķ� ���ֵΪһ�����ϣ��ɶ���,�ָ� ��  05,12,15,20

		//5		��Ӧ���ϴ���
		temp = sd["MAT_CODE_RELATE1"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_RELATE1"] = temp;
		log.Info()<<"MAT_CODE_RELATE1="<<sdTrim["MAT_CODE_RELATE1"].toString()<<endl;

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


void MsgP4HC02::HandleDataIntoDB(SmartData sd, string logFileName)
{
	string functionName="MsgP4HC02 :: HandleDataIntoDB()";
	LOG log(functionName, logFileName);

	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//������� I-����  D-ɾ��
		string exterSystem = sd["EXTER_SYSTEM"].toString();//�ⲿϵͳ��LG:�ϸ������ַϸֶ��չ�ϵ��DL:�ϸ����¯�ϸֶ��չ�ϵ ��
		string matCode = sd["MAT_CODE"].toString();//���ϴ���
		string compCodeSet = sd["COMP_CODE_SET"].toString();//���ƴ��뼯��
		string matCodeRelate1 = sd["MAT_CODE_RELATE1"].toString();//�ⲿϵͳ���ϴ���  ��  ���ϴ���+���ƴ��� ��Ӧ �ⲿϵͳ���ϴ���

		//�� compCode ����ת����vector �����������
		vector<string> vecCompCode;
		vecCompCode = StringHelper::ToVector<string>(compCodeSet, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

		//ɾ����ǣ���ֱ��ɾ��
		if (operateFlag == "D")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
			DelMatCodeCompCode(matCode, vecCompCode, matCodeRelate1);
			return;
		}

		if (operateFlag == "I")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , insert or update.........return.........."<<endl;
			//��ɾ�����ٲ��룬�������Ƿ�ԭ�ȴ��ڵ��ж���
			DelMatCodeCompCode(matCode, vecCompCode, matCodeRelate1);
			InsMatCodeCompCode(exterSystem, matCode, vecCompCode, matCodeRelate1);
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


void MsgP4HC02::DelMatCodeCompCode(string matCode, vector<string> vecCompCode, string matCodeRelate)
{
	string functionName="MsgP4HC02 :: DelMatCodeCompCode()";
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

void MsgP4HC02::InsMatCodeCompCode(string exterSystem, string matCode, vector<string> vecCompCode, string matCodeRelate)
{
	string functionName="MsgP4HC02 :: InsMatCodeCompCode()";
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

