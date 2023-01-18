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
		// 读取powertrans电文结构
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			sdTrim = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			readSmartDataSuccessed=true;
		}

		//读取原始字节流
		sd.readFrom(ParamBuffer);
		log.Info()<<"..................................................................log of samrt data......................................................"<<endl;
		string temp = "";

		//1		操作标志
		temp = sd["OPERATE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["OPERATE_FLAG"] = temp;
		log.Info()<<"OPERATE_FLAG="<<sdTrim["OPERATE_FLAG"].toString()<<endl;

		//2		流水号
		temp = sd["WORK_SEQ_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["WORK_SEQ_NO"] = temp;
		log.Info()<<"WORK_SEQ_NO="<<sdTrim["WORK_SEQ_NO"].toString()<<endl;

		//3		智能行车流水号
		temp = sd["HC_WORK_SEQ_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["HC_WORK_SEQ_NO"] = temp;
		log.Info()<<"HC_WORK_SEQ_NO="<<sdTrim["HC_WORK_SEQ_NO"].toString()<<endl;

		//4		车号
		temp = sd["CAR_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["CAR_NO"] = temp;
		log.Info()<<"CAR_NO="<<sdTrim["CAR_NO"].toString()<<endl;

		//5		计量申请号
		temp = sd["WEIGH_APP_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGH_APP_NO"] = temp;
		log.Info()<<"WEIGH_APP_NO="<<sdTrim["WEIGH_APP_NO"].toString()<<endl;

		//6		计量申请时刻
		temp = sd["WEIGH_APP_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGH_APP_TIME"] = temp;
		log.Info()<<"WEIGH_APP_TIME="<<sdTrim["WEIGH_APP_TIME"].toString()<<endl;

		//7		操作者
		temp = sd["REC_CREATOR"].toString();
		StringHelper::Trim(temp);
		sdTrim["REC_CREATOR"] = temp;
		log.Info()<<"REC_CREATOR="<<sdTrim["REC_CREATOR"].toString()<<endl;

		//8		磅单号
		temp = sd["WEIGH_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGH_NO"] = temp;
		log.Info()<<"WEIGH_NO="<<sdTrim["WEIGH_NO"].toString()<<endl;

		//9		毛重
		temp = sd["GROSS_WGT"].toString();
		StringHelper::Trim(temp);
		sdTrim["GROSS_WGT"] = temp;
		log.Info()<<"GROSS_WGT="<<sdTrim["GROSS_WGT"].toInt()<<endl;

		//10		皮重
		temp = sd["TARE_WGT"].toString();
		StringHelper::Trim(temp);
		sdTrim["TARE_WGT"] = temp;
		log.Info()<<"TARE_WGT="<<sdTrim["TARE_WGT"].toInt()<<endl;

		//11		净重
		temp = sd["NET_WGT"].toString();
		StringHelper::Trim(temp);
		sdTrim["NET_WGT"] = temp;
		log.Info()<<"NET_WGT="<<sdTrim["NET_WGT"].toInt()<<endl;

		//12		毛重时刻
		temp = sd["GROSS_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["GROSS_TIME"] = temp;
		log.Info()<<"GROSS_TIME="<<sdTrim["GROSS_TIME"].toString()<<endl;

		//13		皮重时刻
		temp = sd["TARE_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["TARE_TIME"] = temp;
		log.Info()<<"TARE_TIME="<<sdTrim["TARE_TIME"].toString()<<endl;

		//14		称重时刻
		temp = sd["WEIGH_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["WEIGH_TIME"] = temp;
		log.Info()<<"WEIGH_TIME="<<sdTrim["WEIGH_TIME"].toString()<<endl;

		//15 	源库区代码
		temp = sd["SRC_STOCK_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["SRC_STOCK_CODE"] = temp;
		log.Info()<<"SRC_STOCK_CODE="<<sdTrim["SRC_STOCK_CODE"].toString()<<endl;

		//16		源库位代码
		temp = sd["SRC_LOC_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["SRC_LOC_CODE"] = temp;
		log.Info()<<"SRC_LOC_CODE="<<sdTrim["SRC_LOC_CODE"].toString()<<endl;

		//17		发方物料代码
		temp = sd["SRC_MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["SRC_MAT_CODE"] = temp;
		log.Info()<<"SRC_MAT_CODE="<<sdTrim["SRC_MAT_CODE"].toString()<<endl;

		//18		发方钢制代码
		temp = sd["SRC_COMP_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["SRC_COMP_CODE"] = temp;
		log.Info()<<"SRC_COMP_CODE="<<sdTrim["SRC_COMP_CODE"].toString()<<endl;

		//19		目的库区代码
		temp = sd["DST_STOCK_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["DST_STOCK_CODE"] = temp;
		log.Info()<<"DST_STOCK_CODE="<<sdTrim["DST_STOCK_CODE"].toString()<<endl;

		//20		目的库位代码
		temp = sd["DST_LOC_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["DST_LOC_CODE"] = temp;
		log.Info()<<"DST_LOC_CODE="<<sdTrim["DST_LOC_CODE"].toString()<<endl;

		//21		收方物料代码
		temp = sd["DST_MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["DST_MAT_CODE"] = temp;
		log.Info()<<"DST_MAT_CODE="<<sdTrim["DST_MAT_CODE"].toString()<<endl;

		//22		收方钢制代码
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

		//28		循环次数
		temp = sd["LOOP_COUNT"].toString();
		StringHelper::Trim(temp);
		sdTrim["LOOP_COUNT"] = temp;
		log.Info()<<"LOOP_COUNT="<<sdTrim["LOOP_COUNT"].toInt()<<endl;
		log.Info()<<"LOOP_COUNT1="<<sd["LOOP_COUNT"].toInt()<<endl;



		int loopCount = sdTrim["LOOP_COUNT"].toInt();
		for (int i = 0; i < loopCount; ++i)
		{
			log.Info()<<"\t Index In Loop = "<<i<<" : ";
			//库位/料格号
			temp = sd["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"].toString();
			StringHelper::Trim(temp);
			sdTrim["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"] = temp;
			log.Info()<<" STOCK_PLACE_CODE = "<<sdTrim["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"].toString();	

			//物料代码
			temp = sd["P4HC12_DETAIL"][i]["MAT_CODE"].toString();
			StringHelper::Trim(temp);
			sdTrim["P4HC12_DETAIL"][i]["MAT_CODE"] = temp;
			log.Info()<<" MAT_CODE = "<<sdTrim["P4HC12_DETAIL"][i]["MAT_CODE"].toString();

			//钢制代码
			temp = sd["P4HC12_DETAIL"][i]["COMP_CODE"].toString();
			StringHelper::Trim(temp);
			sdTrim["P4HC12_DETAIL"][i]["COMP_CODE"] = temp;
			log.Info()<<" COMP_CODE = "<<sdTrim["P4HC12_DETAIL"][i]["COMP_CODE"].toString();

			//分摊重量
			temp = sd["P4HC12_DETAIL"][i]["WGT"].toString();
			StringHelper::Trim(temp);
			sdTrim["P4HC12_DETAIL"][i]["WGT"] = temp;
			log.Info()<<" WGT = "<<sdTrim["P4HC12_DETAIL"][i]["WGT"].toInt()<<endl;
		}

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
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//流水号
		string hcWorkSeqNO= sd["HC_WORK_SEQ_NO"].toString();//智能行车流水号
		string carNO = sd["CAR_NO"].toString();//车号
		string weighAppNo = sd["WEIGH_APP_NO"].toString();//计量申请号
		string weighAppTime = sd["WEIGH_APP_TIME"].toString();//计量申请时刻
		string recCreator = sd["REC_CREATOR"].toString();//操作者
		string weighNO = sd["WEIGH_NO"].toString();//磅单号
		int grossWgt = sd["GROSS_WGT"].toInt();//毛重
		int tareWgt = sd["TARE_WGT"].toInt();//皮重
		int netWgt = sd["NET_WGT"].toInt();//净重
		string grossTime = sd["GROSS_TIME"].toString();//毛重时刻
		string tareTime = sd["TARE_TIME"].toString();//皮重时刻
		string weighTime = sd["WEIGH_TIME"].toString();//称重时刻
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//源库位代码
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//发方物料代码
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//发方钢制代码
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		string dstLocCode = sd["DST_LOC_CODE"].toString();//目的库位代码
		string dstMatCode = sd["DST_MAT_CODE"].toString();//收方物料代码
		string dstCompCode = sd["DST_COMP_CODE"].toString();//收方钢制代码

		int loopCount = sd["LOOP_COUNT"].toInt();//rgv车辆装料循环次数

		//是否存在记录，不存在，则直接更新插入新纪录
		if (false == SQL4L3::MatWeightInfoExist(workSeqNO))
		{
			log.Info()<<"workSeqNO = "<<workSeqNO<<" , no record in table , insert into .........return.........."<<endl;
			SQL4L3::InsertMatWeightTable(sd);
			return;
		}

		//存在记录的情况下
		log.Info()<<"workSeqNO = "<<workSeqNO<<" , have record in table ....update......"<<endl;
		//1.直接更新称重主表
		SQL4L3::UpdateMatWeightInfo(sd);
		//2. 如果loopCount为0  则删除rgv子表 ; 如果不为0  则先删除子表,再插入子表
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
		//根据流水号 智能行车流水号 通知相应模块重新整理装车实绩
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

		//属于电炉装车过磅数据:
		//1. 通知电炉L2模块更新实绩，发送给电炉L2最新称量信息
		//2. 由电炉模块通知指令模块校正料格重量
		if (hcSeqNO.find("DL") != string::npos)
		{
			log.Info()<<"this is  EAF ZC WGT from L3..............."<<endl;
			tagName = "EV_L3_EAF_ZC_WGT";
			tagValue = hcSeqNO + "," + netWgt;

			log.Info()<<"EV_L3_EAF_ZC_WGT  tagValue = "<<tagValue<<endl;
		}


		//属于转炉装车过磅数据:
		//1. 通知转炉L2模块更新实绩，再次发送给转炉L2
		//2. 通知指令模块更新料格库存信息
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

			//组织rgv车辆重量分摊数据： 料格号,物料代码,钢制代码,分摊重量
			string rgvPartMsg = GetRgvMatInfo(sd);
			tagValue += "," + rgvPartMsg;

			log.Info()<<"EV_L3_BOF_ZC_WGT  tagValue = "<<tagValue<<endl;
			
		}
		//属于L3装车实绩
		else
		{
			log.Info()<<"this is  L3 ZC WGT from L3..............."<<endl;
			tagName = "EV_L3_ZC_WGT";
			tagValue = seqNO + "," + netWgt;

			log.Info()<<"EV_L3_ZC_WGT  tagValue = "<<tagValue<<endl;
		}

		//下发通知
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
			//库位/料格号
			string temp1 = sd["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"].toString();
			StringHelper::Trim(temp1);

			//物料代码
			string temp2 = sd["P4HC12_DETAIL"][i]["MAT_CODE"].toString();
			StringHelper::Trim(temp2);

			//钢制代码
			string temp3 = sd["P4HC12_DETAIL"][i]["COMP_CODE"].toString();
			StringHelper::Trim(temp3);

			//分摊重量
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