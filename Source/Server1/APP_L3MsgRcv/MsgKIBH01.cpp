#include "MsgKIBH01.h"
#include <iconv.h>
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;


MsgKIBH01*  MsgKIBH01::m_pMsgKIBH01 = NULL;


MsgKIBH01::MsgKIBH01() 
{
	msgId="KIBH01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgKIBH01 :: ~MsgKIBH01(void)
{

	delete m_pMsgKIBH01;


}

MsgKIBH01* MsgKIBH01::getInstance(void)
{
	if (m_pMsgKIBH01 == NULL)
	{
		m_pMsgKIBH01 = new MsgKIBH01;
	}
	return m_pMsgKIBH01;
}

ByteSeq MsgKIBH01::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgKIBH01 :: HandleMessage()";
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
		temp = sd["OPER_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["OPER_FLAG"] = temp;
		log.Info()<<"OPER_FLAG="<<sdTrim["OPER_FLAG"].toString()<<endl;

		//2		�ƻ���
		temp = sd["PLAN_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["PLAN_NO"] = temp;
		log.Info()<<"PLAN_NO="<<sdTrim["PLAN_NO"].toString()<<endl;

		//3		¯��
		temp = sd["BOF_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["BOF_NO"] = temp;
		log.Info()<<"BOF_NO="<<sdTrim["BOF_NO"].toString()<<endl;

		//4		ѭ������
		temp = sd["CYCLE_COUNT"].toString();
		StringHelper::Trim(temp);
		//string u2g = UTFtoGBK(temp.c_str());
		//sdTrim["MAT_CNAME"] = u2g;
		sdTrim["CYCLE_COUNT"] = temp;
		log.Info()<<"CYCLE_COUNT="<<sdTrim["CYCLE_COUNT"].toInt()<<endl;

		//5		���ϱ��
		temp = sd["MAT_CODE_1"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_1"] = temp;
		log.Info()<<"MAT_CODE_1="<<sdTrim["MAT_CODE_1"].toString()<<endl;

		//6		��������
		temp = sd["WEIGHT_1"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_1"] = temp;
		log.Info()<<"WEIGHT_1="<<sdTrim["WEIGHT_1"].toInt()<<endl;

		//5		���ϱ��2
		temp = sd["MAT_CODE_2"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_2"] = temp;
		log.Info()<<"MAT_CODE_2="<<sdTrim["MAT_CODE_2"].toString()<<endl;

		//6		��������2
		temp = sd["WEIGHT_2"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_2"] = temp;
		log.Info()<<"WEIGHT_2="<<sdTrim["WEIGHT_2"].toInt()<<endl;

		//5		���ϱ��3
		temp = sd["MAT_CODE_3"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_3"] = temp;
		log.Info()<<"MAT_CODE_3="<<sdTrim["MAT_CODE_3"].toString()<<endl;

		//6		��������3
		temp = sd["WEIGHT_3"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_3"] = temp;
		log.Info()<<"WEIGHT_3="<<sdTrim["WEIGHT_3"].toInt()<<endl;

		//5		���ϱ��4
		temp = sd["MAT_CODE_4"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_4"] = temp;
		log.Info()<<"MAT_CODE_4="<<sdTrim["MAT_CODE_4"].toString()<<endl;

		//6		��������4
		temp = sd["WEIGHT_4"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_4"] = temp;
		log.Info()<<"WEIGHT_4="<<sdTrim["WEIGHT_4"].toInt()<<endl;

		//5		���ϱ��5
		temp = sd["MAT_CODE_5"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_5"] = temp;
		log.Info()<<"MAT_CODE_5="<<sdTrim["MAT_CODE_5"].toString()<<endl;

		//6		��������5
		temp = sd["WEIGHT_5"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_5"] = temp;
		log.Info()<<"WEIGHT_5="<<sdTrim["WEIGHT_5"].toInt()<<endl;

		//5		���ϱ��6
		temp = sd["MAT_CODE_6"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_6"] = temp;
		log.Info()<<"MAT_CODE_6="<<sdTrim["MAT_CODE_6"].toString()<<endl;

		//6		��������6
		temp = sd["WEIGHT_6"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_6"] = temp;
		log.Info()<<"WEIGHT_6="<<sdTrim["WEIGHT_6"].toInt()<<endl;

		//5		���ϱ��7
		temp = sd["MAT_CODE_7"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_7"] = temp;
		log.Info()<<"MAT_CODE_7="<<sdTrim["MAT_CODE_7"].toString()<<endl;

		//6		��������7
		temp = sd["WEIGHT_7"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_7"] = temp;
		log.Info()<<"WEIGHT_7="<<sdTrim["WEIGHT_7"].toInt()<<endl;

		//5		���ϱ��8
		temp = sd["MAT_CODE_8"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_8"] = temp;
		log.Info()<<"MAT_CODE_8="<<sdTrim["MAT_CODE_8"].toString()<<endl;

		//6		��������8
		temp = sd["WEIGHT_8"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_8"] = temp;
		log.Info()<<"WEIGHT_8="<<sdTrim["WEIGHT_8"].toInt()<<endl;

		//5		���ϱ��9
		temp = sd["MAT_CODE_9"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_9"] = temp;
		log.Info()<<"MAT_CODE_9="<<sdTrim["MAT_CODE_9"].toString()<<endl;

		//6		��������9
		temp = sd["WEIGHT_9"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_9"] = temp;
		log.Info()<<"WEIGHT_9="<<sdTrim["WEIGHT_9"].toInt()<<endl;

		//5		���ϱ��10
		temp = sd["MAT_CODE_10"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_10"] = temp;
		log.Info()<<"MAT_CODE_10="<<sdTrim["MAT_CODE_10"].toString()<<endl;

		//6		��������10
		temp = sd["WEIGHT_10"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGHT_10"] = temp;
		log.Info()<<"WEIGHT_10="<<sdTrim["WEIGHT_10"].toInt()<<endl;
		

		//5		��ע1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//6		��ע2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//7		��ע3
		//20220816  zhangyuhong add
		//������������
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//8		��ע4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//9		��ע5
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


void MsgKIBH01::HandleDataIntoDB(SmartData sd, string logFileName)
{
	string functionName="MsgKIBH01 :: HandleDataIntoDB()";
	LOG log(functionName, logFileName);

	try
	{
		string operateFlag = sd["OPER_FLAG"].toString();//������� 1-����  2-ɾ��
		string planNO= sd["PLAN_NO"].toString();//�ƻ���
		string bofNO = sd["BOF_NO"].toString();//¯��
		int count = sd["CYCLE_COUNT"].toInt();//ѭ������
		string matCode_1 = sd["MAT_CODE_1"].toString();//���ϱ��1
		int weight_1 = sd["WEIGHT_1"].toInt();//��������1
		string matCode_2 = sd["MAT_CODE_2"].toString();//���ϱ��2
		int weight_2 = sd["WEIGHT_2"].toInt();//��������2
		string matCode_3 = sd["MAT_CODE_3"].toString();//���ϱ��3
		int weight_3 = sd["WEIGHT_3"].toInt();//��������3
		string matCode_4 = sd["MAT_CODE_4"].toString();//���ϱ��4
		int weight_4 = sd["WEIGHT_4"].toInt();//��������4
		string matCode_5 = sd["MAT_CODE_5"].toString();//���ϱ��5
		int weight_5 = sd["WEIGHT_5"].toInt();//��������5
		string matCode_6 = sd["MAT_CODE_6"].toString();//���ϱ��6
		int weight_6 = sd["WEIGHT_6"].toInt();//��������6
		string matCode_7 = sd["MAT_CODE_7"].toString();//���ϱ��7
		int weight_7 = sd["WEIGHT_7"].toInt();//��������7
		string matCode_8 = sd["MAT_CODE_8"].toString();//���ϱ��8
		int weight_8 = sd["WEIGHT_8"].toInt();//��������8
		string matCode_9 = sd["MAT_CODE_9"].toString();//���ϱ��9
		int weight_9 = sd["WEIGHT_9"].toInt();//��������9
		string matCode_10 = sd["MAT_CODE_10"].toString();//���ϱ��10
		int weight_10 = sd["WEIGHT_10"].toInt();//��������10


		//utf-8תGBK
		//string u2g = UTFtoGBK(matCName.c_str());
		//string gu = GBKToUTF8(matCName.c_str());

		//log.Info()<<"1.......matCName = "<<UTFtoGBK(matCName.c_str())<<endl;
		//log.Info()<<"2.......matCName = "<<GBKToUTF8(matCName.c_str())<<endl;

		//ɾ����ǣ���ֱ��ɾ��
		if (operateFlag == "2")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
			SQL4L3::DelMatOutInfo(planNO);
			return;
		}

		if (operateFlag == "1")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , insert or update.........return.........."<<endl;
			//��ɾ�� �ٲ���
			SQL4L3::DelMatOutInfo(planNO);
			SQL4L3::InsertMatOutInfo(operateFlag, planNO, bofNO, count, matCode_1, weight_1, matCode_2, weight_2, matCode_3, weight_3, matCode_4, weight_4, matCode_5, weight_5, matCode_6, weight_6, matCode_7, weight_7, matCode_8, weight_8, matCode_9, weight_9, matCode_10, weight_10);
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

int MsgKIBH01::code_convert(const char *from_charset, const char *to_charset, char *inbuf, size_t inlen,
							char *outbuf, size_t outlen)
{
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;

	memset(outbuf, 0, outlen);

	if ((int)iconv(cd, pin, &inlen, pout, &outlen) == -1)
	{
		iconv_close(cd);
		return -1;
	}
	iconv_close(cd);
	*pout = '\0';

	return 0;
}


int MsgKIBH01::u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}

int MsgKIBH01::g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return  code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

string MsgKIBH01::GBKToUTF8(const std::string& strGBK)
{
	int length = strGBK.size()*2+1;

	char *temp = (char*)malloc(sizeof(char)*length);

	if(g2u((char*)strGBK.c_str(),strGBK.size(),temp,length) >= 0)
	{
		std::string str_result;
		str_result.append(temp);
		free(temp);
		return str_result;
	}else
	{
		free(temp);
		return "";
	}
}

string MsgKIBH01::UTFtoGBK(const char* utf8)
{
	int length = strlen(utf8);

	char *temp = (char*)malloc(sizeof(char)*length);

	if(u2g((char*)utf8,length,temp,length) >= 0)
	{
		std::string str_result;
		str_result.append(temp);
		free(temp);

		return str_result;
	}else
	{
		free(temp);
		return "";
	}
}
