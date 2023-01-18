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

		//2		库区代码
		temp = sd["STOCK_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["STOCK_CODE"] = temp;
		log.Info()<<"STOCK_CODE="<<sdTrim["STOCK_CODE"].toString()<<endl;

		//3		料格代码
		temp = sd["STOCK_PLACE_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["STOCK_PLACE_CODE"] = temp;
		log.Info()<<"STOCK_PLACE_CODE="<<sdTrim["STOCK_PLACE_CODE"].toString()<<endl;

		//4		料条/垮代码
		temp = sd["STOCK_LOC_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["STOCK_LOC_CODE"] = temp;
		log.Info()<<"STOCK_LOC_CODE="<<sdTrim["STOCK_LOC_CODE"].toString()<<endl;

		//5		料条/垮起点地址
		temp = sd["STORERM_ADDR_MIN"].toString();
		StringHelper::Trim(temp);
		sdTrim["STORERM_ADDR_MIN"] = temp;
		log.Info()<<"STORERM_ADDR_MIN="<<sdTrim["STORERM_ADDR_MIN"].toInt()<<endl;

		//6		料条/垮终点地址
		temp = sd["STORERM_ADDR_MAX"].toString();
		StringHelper::Trim(temp);
		sdTrim["STORERM_ADDR_MAX"] = temp;
		log.Info()<<"STORERM_ADDR_MAX="<<sdTrim["STORERM_ADDR_MAX"].toInt()<<endl;

		//7		物料代码
		temp = sd["MAT_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_CODE"] = temp;
		log.Info()<<"MAT_CODE="<<sdTrim["MAT_CODE"].toString()<<endl;

		//8		废钢钢制码
		temp = sd["COMP_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["COMP_CODE"] = temp;
		log.Info()<<"COMP_CODE="<<sdTrim["COMP_CODE"].toString()<<endl;

		//9		开始时刻
		temp = sd["START_TIME"].toString();
		StringHelper::Trim(temp);
		sdTrim["START_TIME"] = temp;
		log.Info()<<"START_TIME="<<sdTrim["START_TIME"].toString()<<endl;

		//10		备注1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//11		备注2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//12		备注3
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//13		备注4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//14		备注5
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
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string stockCode = sd["STOCK_CODE"].toString();//库区代码
		string stockPlaceCode = sd["STOCK_PLACE_CODE"].toString();//料格代码
		string stockLocCode = sd["STOCK_LOC_CODE"].toString();//料条/跨代码
		long storermAddrMin = sd["STORERM_ADDR_MIN"].toInt();//料条/跨起始地址
		long storermAddrMax = sd["STORERM_ADDR_MAX"].toInt();//料条/跨终点地址
		string matCode = sd["MAT_CODE"].toString();//物料代码
		string compCode = sd["COMP_CODE"].toString();//钢制代码
		string startTime = sd["START_TIME"].toString();//开始时间


		//将数据写入数据库表
		//20220818 zhangyuhong add
		//收到此电文后, 对料格库图表进行更新:
		//1. 根据料格号更新对应物料代码、钢制码,并同时对库存量进行清零
		//2. 如果是删除标志,则更新料格号将物料代码\钢制码置空,对库存量清零

		//删除标记，则直接删除
		if (operateFlag == "D")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
			SQL4L3::DelMatGridInfo(stockPlaceCode);

			//对库图表进行修改
			SQL4L3::InitYardMapGridInfo(stockPlaceCode);

			return;
		}

		if (operateFlag == "I")
		{
			log.Info()<<"operateFlag = "<<operateFlag<<" , insert or update.........return.........."<<endl;
			//先删除,再插入
			SQL4L3::DelMatGridInfo(stockPlaceCode);
			SQL4L3::InsertMatGridInfo(stockCode, stockPlaceCode, stockLocCode, storermAddrMin, storermAddrMax, matCode, compCode, startTime);

			//对库图表进行修改
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

