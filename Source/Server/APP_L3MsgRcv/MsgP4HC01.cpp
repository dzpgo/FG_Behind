#include "MsgP4HC01.h"
#include <iconv.h>
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;


MsgP4HC01*  MsgP4HC01::m_pMsgP4HC01 = NULL;


MsgP4HC01::MsgP4HC01() 
{
	msgId="P4HC01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgP4HC01 :: ~MsgP4HC01(void)
{

	delete m_pMsgP4HC01;


}

MsgP4HC01* MsgP4HC01::getInstance(void)
{
	if (m_pMsgP4HC01 == NULL)
	{
		m_pMsgP4HC01 = new MsgP4HC01;
	}
	return m_pMsgP4HC01;
}

ByteSeq MsgP4HC01::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgP4HC01 :: HandleMessage()";
	ByteSeq ret;
	LOG log(functionName, LogFileName);	

	try
	{
		// 读取powertrans电文结构
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			sdTrim = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			readSmartDataSuccessed=true;
		}

		//读取原始字节流
		sd.readFrom(ParamBuffer);
		log.Info()<<"........................................................................................log of samrt data..................................................................................."<<endl;
		string temp = "";

		//1		操作标志
		temp = sd["OPERATE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["OPERATE_FLAG"] = temp;
		log.Info()<<"OPERATE_FLAG="<<sdTrim["OPERATE_FLAG"].toString()<<endl;

		//2		物料类别
		temp = sd["BASE_RESOURCE"].toString();
		StringHelper::Trim(temp);
		sdTrim["BASE_RESOURCE"] = temp;
		log.Info()<<"BASE_RESOURCE="<<sdTrim["BASE_RESOURCE"].toString()<<endl;

		//3		物料代码
		temp = sd["MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE"] = temp;
		log.Info()<<"MAT_CODE="<<sdTrim["MAT_CODE"].toString()<<endl;

		//4		物料中文
		temp = sd["MAT_CNAME"].toString();
		StringHelper::Trim(temp);
		//string u2g = UTFtoGBK(temp.c_str());
		//sdTrim["MAT_CNAME"] = u2g;
		sdTrim["MAT_CNAME"] = temp;
		log.Info()<<"MAT_CNAME="<<sdTrim["MAT_CNAME"].toString()<<endl;

		//5		物料类型  1-重废  2-中废  3-轻废   L3定义
		temp = sd["MAT_TYPE"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_TYPE"] = temp;
		log.Info()<<"MAT_TYPE="<<sdTrim["MAT_TYPE"].toString()<<endl;

		

		//5		备注1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//6		备注2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//7		备注3
		//20220816  zhangyuhong add
		//用于物料类型
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//8		备注4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//9		备注5
		//log.Info()<<"\t\t BACK5="<<sd["BACK5"].toString();

		//		接收时刻
		log.Info()<<"RCV_TIME="<<iDA::DateTime::Now().ToShortTimeString()<<endl;

		ByteSeq data;
		sdTrim.writeTo(data);
		DealData dealdata = DealData();
		//明码电文
		string dataStr = dealdata.DumpValue(sdTrim,",");
		//获取最大ID号
		int ID = dealdata.GetMaxIDRcv();
		//最大ID号加1
		ID += 1; 
		//将数据存到发送表中
		dealdata.InsertRcvData(msgId,dataStr,data,ID);

		//将数据写入数据库表
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


void MsgP4HC01::HandleDataIntoDB(SmartData sd, string logFileName)
{
	string functionName="MsgP4HC01 :: HandleDataIntoDB()";
	LOG log(functionName, logFileName);

	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string baseResource= sd["BASE_RESOURCE"].toString();//物流类别  废钢；炼钢废钢；电炉废钢
		string matCode = sd["MAT_CODE"].toString();//物料代码
		string matCName = sd["MAT_CNAME"].toString();//物料中文名称
		string matType = sd["MAT_TYPE"].toString();//物料类型  1-重废 2-中废 3-轻废


		//utf-8转GBK
		//string u2g = UTFtoGBK(matCName.c_str());
		//string gu = GBKToUTF8(matCName.c_str());

		//log.Info()<<"1.......matCName = "<<UTFtoGBK(matCName.c_str())<<endl;
		//log.Info()<<"2.......matCName = "<<GBKToUTF8(matCName.c_str())<<endl;

		//删除标记，则直接删除
		if (operateFlag == "D")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
			SQL4L3::DelMatInfo(matCode);
			return;
		}

		if (operateFlag == "I")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , insert or update.........return.........."<<endl;
			//先删除 再插入
			SQL4L3::DelMatInfo(matCode);
			SQL4L3::InsertMatInfo(baseResource, matCode, matCName, matType);
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

int MsgP4HC01::code_convert(const char *from_charset, const char *to_charset, char *inbuf, size_t inlen,
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


int MsgP4HC01::u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}

int MsgP4HC01::g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return  code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

string MsgP4HC01::GBKToUTF8(const std::string& strGBK)
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

string MsgP4HC01::UTFtoGBK(const char* utf8)
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
