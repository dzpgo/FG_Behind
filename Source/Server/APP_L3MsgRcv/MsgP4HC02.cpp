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
		
		//堆场废钢品名与厂内品名对照关系电文

		//1		操作标志
		temp = sd["OPERATE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["OPERATE_FLAG"] = temp;
		log.Info()<<"OPERATE_FLAG="<<sdTrim["OPERATE_FLAG"].toString()<<endl;//I:新增 D:删除

		//2		外部系统
		temp = sd["EXTER_SYSTEM"].toString();
		StringHelper::Trim(temp);
		sdTrim["EXTER_SYSTEM"] = temp;
		log.Info()<<"EXTER_SYSTEM="<<sdTrim["EXTER_SYSTEM"].toString()<<endl;//LG:废钢与炼钢废钢对照关系；DL:废钢与电炉废钢对照关系

		//3		物料代码
		temp = sd["MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE"] = temp;
		log.Info()<<"MAT_CODE="<<sdTrim["MAT_CODE"].toString()<<endl;

		//4		废钢钢制码集合
		temp = sd["COMP_CODE_SET"].toString();
		StringHelper::Trim(temp);
		sdTrim["COMP_CODE_SET"] = temp;
		log.Info()<<"COMP_CODE_SET="<<sdTrim["COMP_CODE_SET"].toString()<<endl;//20220520 改动 这个值为一个集合，由逗号,分隔 如  05,12,15,20

		//5		对应物料代码
		temp = sd["MAT_CODE_RELATE1"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE_RELATE1"] = temp;
		log.Info()<<"MAT_CODE_RELATE1="<<sdTrim["MAT_CODE_RELATE1"].toString()<<endl;

		//6		备注1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//7		备注2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//8		备注3
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//9		备注4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//10		备注5
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


void MsgP4HC02::HandleDataIntoDB(SmartData sd, string logFileName)
{
	string functionName="MsgP4HC02 :: HandleDataIntoDB()";
	LOG log(functionName, logFileName);

	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string exterSystem = sd["EXTER_SYSTEM"].toString();//外部系统（LG:废钢与炼钢废钢对照关系；DL:废钢与电炉废钢对照关系 ）
		string matCode = sd["MAT_CODE"].toString();//物料代码
		string compCodeSet = sd["COMP_CODE_SET"].toString();//钢制代码集合
		string matCodeRelate1 = sd["MAT_CODE_RELATE1"].toString();//外部系统物料代码  ：  物料代码+钢制代码 对应 外部系统物料代码

		//将 compCode 集合转换成vector 方便后续处理
		vector<string> vecCompCode;
		vecCompCode = StringHelper::ToVector<string>(compCodeSet, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

		//删除标记，则直接删除
		if (operateFlag == "D")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
			DelMatCodeCompCode(matCode, vecCompCode, matCodeRelate1);
			return;
		}

		if (operateFlag == "I")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , insert or update.........return.........."<<endl;
			//先删除，再插入，不再做是否原先存在的判断了
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

