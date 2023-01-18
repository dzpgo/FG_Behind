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

		//3		料格号
		temp = sd["STOCK_LOC_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["STOCK_LOC_CODE"] = temp;
		log.Info()<<"STOCK_LOC_CODE="<<sdTrim["STOCK_LOC_CODE"].toString()<<endl;

		//4		物料代码
		temp = sd["MAT_PROD_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_PROD_CODE"] = temp;
		log.Info()<<"MAT_PROD_CODE="<<sdTrim["MAT_PROD_CODE"].toString()<<endl;

		//5		物料名称
		temp = sd["MAT_PROD_CNAME"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_PROD_CNAME"] = temp;
		log.Info()<<"MAT_PROD_CNAME="<<sdTrim["MAT_PROD_CNAME"].toInt()<<endl;

		//6		废钢成分类别码
		temp = sd["COMP_CODE"].toString();
		StringHelper::Trim(temp);
		sdTrim["COMP_CODE"] = temp;
		log.Info()<<"COMP_CODE="<<sdTrim["COMP_CODE"].toInt()<<endl;

		//7		当前库存量
		temp = sd["CUR_STOCK_WGT"].toString();
		StringHelper::Trim(temp);
		sdTrim["CUR_STOCK_WGT"] = temp;
		log.Info()<<"CUR_STOCK_WGT="<<sdTrim["CUR_STOCK_WGT"].toInt()<<endl;

		//8		禁用标记
		temp = sd["INHIIBT_USE_FLAG"].toString();
		StringHelper::Trim(temp);
		sdTrim["INHIIBT_USE_FLAG"] = temp;
		log.Info()<<"INHIIBT_USE_FLAG="<<sdTrim["INHIIBT_USE_FLAG"].toString()<<endl;

		//9		起堆日期
		temp = sd["PILE_DATE"].toString();
		StringHelper::Trim(temp);
		sdTrim["PILE_DATE"] = temp;
		log.Info()<<"PILE_DATE="<<sdTrim["PILE_DATE"].toString()<<endl;

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
		//将数据存到接收表中
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
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string stockCode = sd["STOCK_CODE"].toString();//库区代码
		string locCode = sd["STOCK_LOC_CODE"].toString();//料格代码
		string matCode = sd["MAT_PROD_CODE"].toString();//物料代码
		string matName = sd["MAT_PROD_CNAME"].toString();//物料名称
		string compCode = sd["COMP_CODE"].toString();//废钢成分类别码
		int curWt = sd["CUR_STOCK_WGT"].toInt();//当前库存量
		string iUFlag = sd["INHIIBT_USE_FLAG"].toString();//禁用标记
		string pileTime = sd["PILE_DATE"].toString();//起堆时间


		//将数据写入数据库表
		//20220818 zhangyuhong add
		//收到此电文后, 对料格库图表进行更新:
		//1. 根据料格号更新对应物料代码、钢制码,并同时对库存量进行清零
		//2. 如果是删除标志,则更新料格号将物料代码\钢制码置空,对库存量清零

		//删除标记，则直接删除
		//if (operateFlag == "D")
		//{
		//	log.Info()<<"operateFlag = "<<operateFlag<<" , del from table.........return.........."<<endl;
		//	SQL4L3::DelMatGridInfo(stockPlaceCode);

		//	//对库图表进行修改
		//	SQL4L3::InitYardMapGridInfo(stockPlaceCode);

		//	return;
		//}

		if (operateFlag == "I")
		{
			stockCode=stockCode+"0";
			log.Info()<<"operateFlag =I, stockCode= "<<stockCode<<" , insert or update.........return.........."<<endl;
			//先删除,再插入
			//SQL4L3::DelMatGridInfo(stockPlaceCode);
			//SQL4L3::InsertMatGridInfo(stockCode, stockPlaceCode, stockLocCode, storermAddrMin, storermAddrMax, matCode, compCode, startTime);

			//对库图表进行修改
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

