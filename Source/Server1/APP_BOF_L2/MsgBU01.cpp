#include "MsgBU01.h"
#include <climits>
#include <iXcomTCP2.h>
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;
using namespace std;
using namespace iXcomTCP2;



MsgBU01*  MsgBU01::m_pMsgBU01 = NULL;


MsgBU01::MsgBU01() 
{
	msgId="BU01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}



MsgBU01 :: ~MsgBU01(void)
{

	delete m_pMsgBU01;


}

MsgBU01* MsgBU01::getInstance(void)
{
	if (m_pMsgBU01 == NULL)
	{
		m_pMsgBU01 = new MsgBU01;
	}
	return m_pMsgBU01;
}

ByteSeq MsgBU01::HandleMessage(const ByteSeq& ParamBuffer)
{
	string functionName="MsgBU01 :: HandleMessage()";

	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{

		// 读取powertrans电文结构
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgId);
			readSmartDataSuccessed=true;
		}


		//读取原始字节流
		sd.readFrom(ParamBuffer);
		log.Info()<<"........................................................................................log of samrt data..................................................................................................................."<<endl;

		//需要注意应用头还有2个字段，需要注意在t_bm_msgitem配进去


		//log.Info()<<"INT_MIN = "<<INT_MIN<<endl;

		//1		钢号
		log.Info()<<"\t\t STEEL_NO="<<sd["STEEL_NO"].toInt();
		//2		计划类型
		log.Info()<<"\t\t PLAN_TYPE="<<sd["PLAN_TYPE"].toInt();//1-常规计划（RGV装车）  2-备用计划（汽车备用槽装车）
		//3		计划标记
		log.Info()<<"\t\t PLAN_FLAG="<<sd["PLAN_FLAG"].toInt()<<endl;//1-新增  2-修改  3-删除		
		//以下循环体
		for (int index = 0; index < 20; index++)
		{
			//废钢代码
			log.Info()<<"\t\t SCRAP_CODE："<<sd["BU01_DETAIL"][index]["SCRAP_CODE"].toInt();
			//废钢需求量
			log.Info()<<"\t\t REQ_WEIGHT："<<sd["BU01_DETAIL"][index]["REQ_WEIGHT"].toInt()<<endl;		
		}

		ByteSeq data;
		sd.writeTo(data);
		DealData dealdata = DealData();
		//明码电文
		string dataStr = dealdata.DumpValue(sd,",");
		//获取最大ID号
		int ID = dealdata.GetMaxIDRcv();
		//最大ID号加1
		ID += 1; 
		//将数据存到发送表中
		dealdata.InsertRcvData(msgId,dataStr,data,ID);

		//写入数据库
		HandleDataIntoDB(sd);

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

void MsgBU01::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgBU01 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string steelNO = sd["STEEL_NO"].toString();//钢号 （计划号）
		string planType = sd["PLAN_TYPE"].toString();//计划类型  1-常规计划（RGV装车）  2-备用计划（汽车备用槽装车）
		string planFlag = sd["PLAN_FLAG"].toString();//计划标记 1-新增  2-修改  3-删除

		//数据库中是否已存在计划
		string planStatus = "";
		bool planExist = SQL4BOF::BOFL2PlanExist(steelNO, planStatus);
		if ( planExist == false )//不存在，直接写入
		{
			log.Info()<<"New plan , insert ..................."<<endl;
			SQL4BOF::InsertBOFL2PlanMain(sd);
			SQL4BOF::InsertBOFL2PlanDetail(sd);
			return;
		}

		//以下是计划存在的情况判断
		log.Info()<<"Old plan , update..................."<<endl;
		log.Info()<<"planStatus = "<<planStatus<<" （1：未开始  2：已开始  3：已完成）...................."<<endl;
		//直接更新主表
		SQL4BOF::UpdatePlanMain(steelNO, planType, planFlag);
		//1. 还未开始装车 ，直接更新主表  更新子表（更新子表办法：先删除子表内容，再插入新配料计划）
		if ( planStatus == "1")
		{
			//如果计划是删除，更新主子表的planValid为 2-非法
			if (planType == "3")
			{
				log.Info()<<"planType = "<<planType<<" , Update plan detail planValid to 2..........."<<endl;
				//更新主表  子表 的 planValid =2
				SQL4BOF::UpdatePlanMainPlanValid(steelNO, planType, planFlag);
				SQL4BOF::UpdatePlanDetailPlanValid(steelNO);
				return;
			}
			//如果计划是新增或修改  更新子表（更新子表办法：先删除子表内容，再插入新配料计划）
			if (planType == "1" || planType == "2")
			{
				log.Info()<<"planType = "<<planType<<" , Update plan detail : first-del old; second-insert new..........."<<endl;
				SQL4BOF::DelPlanDetail(steelNO);
				SQL4BOF::InsertBOFL2PlanDetail(sd);
				return;
			}
		}

		//2. 已经开始装车或装车完成
		if (planStatus == "2" || planStatus == "3")
		{
			//更新主表，同时更新主表中的planValid字段  表明此计划已经非法  因为此计划已经开始装车  此信息可以在画面上展示供主操人工操作
			//SQL4BOF::UpdatePlanMainPlanValid(steelNO, planType, planFlag);
			//如果计划是删除，更新子表的planValid为 2-非法
			if (planType == "3")
			{
				log.Info()<<"planType = "<<planType<<" , Update plan detail planValid to 2..........."<<endl;
				SQL4BOF::UpdatePlanMainPlanValid(steelNO, planType, planFlag);
				SQL4BOF::UpdatePlanDetailPlanValid(steelNO);
				return;
			}
			//如果计划是新增或修改  更新子表（更新子表办法：保留2套配料计划, 老计划和新计划,具体操作为: 先更新老计划planValid，再插入新配料计划）
			if (planType == "1" || planType == "2")
			{
				//如果电文和已存表的配方一样(物料代码和物料重量一致)，则不做修改
				map<string, long> mapMatDetail;
				bool matDetailExist = SQL4BOF::SelectPlanDetailMatWgt(steelNO, mapMatDetail);
				if (true == matDetailSame2SD(mapMatDetail, sd))
				{
					log.Info()<<"mapMatDetail = sd...............no need to update............."<<endl;
					return;
				}

				log.Info()<<"planType = "<<planType<<" , Update plan detail : first-update old planValid; second-insert new..........."<<endl;
				SQL4BOF::UpdatePlanDetailPlanValid(steelNO);
				SQL4BOF::InsertBOFL2PlanDetail(sd);
				return;
			}
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


bool MsgBU01::matDetailSame2SD(map<string, long> matDetail, SmartData sd)
{
	string functionName="MsgBU01 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool ret = false;

	try
	{
		
		map<string, long> matDetailSD;
		int scrID = 0;
		int scrWeight = 0;
		for (int index = 0; index < 20; index++)
		{
			scrID = sd["BU01_DETAIL"][index]["SCRAP_CODE"].toInt();
			if (scrID == INT_MIN)
			{
				log.Info()<<"BU01_DETAIL, index = "<<index<<", scrID = "<<scrID<<",  is not need to treat.........."<<endl;
				continue;
			}
			string strScrID = StringHelper::ToString(scrID);
			scrWeight = sd["BU01_DETAIL"][index]["REQ_WEIGHT"].toInt();
			if (scrWeight == INT_MIN)
			{
				log.Info()<<"BU01_DETAIL, index = "<<index<<", scrWeight = "<<scrWeight<<", ready to set scrWeight=0.........."<<endl;
				scrWeight = 0;
			}
			long lScrWeight = (long)scrWeight;
			matDetailSD.insert(map<string, long>::value_type(strScrID, lScrWeight));
		}

		bool sameSize = ( matDetail.size() == matDetailSD.size() );
		if (sameSize == false)
		{
			log.Info()<<"matDetail.size() <> matDetailSD.size(), return false.................."<<endl;
			ret = false;
			return ret;
		}

		bool sameMatAndWgt = true;
		map<string, long>::iterator itor;
		for (itor = matDetail.begin(); itor != matDetail.end(); itor++)
		{
			string matCode = itor->first;
			long matWgt = itor->second;
			map<string, long>::iterator itor1;
			itor1 = matDetailSD.find(matCode);
			if (itor1 != matDetailSD.end() && itor1->second == matWgt)
			{
				log.Info()<<"matCode = "<<matCode<<" , matWgt="<<matWgt<<" .......FIND in matDetail and matDetailSD.......ok!"<<endl;
			}
			else
			{
				log.Info()<<"matCode = "<<matCode<<" , matWgt="<<matWgt<<" .........FIND in matDetail but NOT FIND in matDetailSD..OR Weight is not SAME...not ok!"<<endl;
				sameMatAndWgt = false;
				break;
			}
		}
		if (sameMatAndWgt == false)
		{
			ret = false;
			return ret;
		}
		ret = true;
		return ret;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
		return ret;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
		return ret;
	}
	return ret;

}



