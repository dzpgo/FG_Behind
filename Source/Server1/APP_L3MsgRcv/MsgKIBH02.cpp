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
		
		//配料间空料斗与工位对照

		//1		车到达/车离开
		temp = sd["ARRIVE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["ARRIVE_FLAG"] = temp;
		log.Info()<<"ARRIVE_FLAG="<<sdTrim["ARRIVE_FLAG"].toString()<<endl;

		//2		料斗号
		temp = sd["HOPPER_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["HOPPER_NO"] = temp;
		log.Info()<<"HOPPER_NO="<<sdTrim["HOPPER_NO"].toString()<<endl;

		//3		工位号
		temp = sd["POSITION_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["POSITION_NO"] = temp;
		log.Info()<<"POSITION_NO="<<sdTrim["POSITION_NO"].toString()<<endl;

		//4		满斗/空斗
		temp = sd["LOAD_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["LOAD_FLAG"] = temp;
		log.Info()<<"LOAD_FLAG="<<sdTrim["LOAD_FLAG"].toString()<<endl;

		////5		对应物料代码
		//temp = sd["MAT_CODE_RELATE1"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["MAT_CODE_RELATE1"] = temp;
		//log.Info()<<"MAT_CODE_RELATE1="<<sdTrim["MAT_CODE_RELATE1"].toString()<<endl;

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


void MsgKIBH02::HandleDataIntoDB(SmartData sd, string logFileName)
{
	string functionName="MsgKIBH02 :: HandleDataIntoDB()";
	LOG log(functionName, logFileName);

	try
	{
		string arriveFlag = sd["ARRIVE_FLAG"].toString();//车到达/车离开
		string hopperNO = sd["HOPPER_NO"].toString();//料斗号
		string positionNO = sd["POSITION_NO"].toString();//工位号
		string loadFlag = sd["LOAD_FLAG"].toString();//满斗/空斗
		

		//更新工位对照表数据
		SQL4L3::UpdateMatCarRelationInfo(arriveFlag, hopperNO, positionNO, loadFlag);
		log.Info()<<"positionNO = "<<positionNO<<" , UpdateMatCarRelationInfo.........return.........."<<endl;
		return;
		//将 compCode 集合转换成vector 方便后续处理
		//vector<string> vecCompCode;
		//vecCompCode = StringHelper::ToVector<string>(compCodeSet, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

		////删除标记，则直接删除
		//if (operateFlag == "D")
		//{
		//	log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
		//	DelMatCodeCompCode(matCode, vecCompCode, matCodeRelate1);
		//	return;
		//}

		//if (operateFlag == "I")
		//{
		//	log.Info()<<"operateFlag = "<<operateFlag<<" , insert or update.........return.........."<<endl;
		//	//先删除，再插入，不再做是否原先存在的判断了
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

