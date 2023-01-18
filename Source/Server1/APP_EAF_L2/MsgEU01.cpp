#include "MsgEU01.h"
#include "DealData.h"


using namespace Monitor;
using namespace iPlature;



MsgEU01*  MsgEU01::m_pMsgEU01 = NULL;


MsgEU01::MsgEU01() 
{
	msgId="EU01";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgEU01 :: ~MsgEU01(void)
{
	
	delete m_pMsgEU01;


}

 MsgEU01* MsgEU01::getInstance(void)
{
	if (m_pMsgEU01 == NULL)
	{
		m_pMsgEU01 = new MsgEU01;
	}
	return m_pMsgEU01;
}

ByteSeq MsgEU01::HandleMessage(const ByteSeq& ParamBuffer, string msgIDInTrans)
{
	string functionName="MsgEU01 :: HandleMessage()";

	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);
	AlarmWrapper _p("");

	try
	{
		// 读取powertrans电文结构
		if(readSmartDataSuccessed==false)
		{
			sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgIDInTrans);
			readSmartDataSuccessed=true;
		}

		//读取原始字节流
		sd.readFrom(ParamBuffer);

		log.Info()<<"......"<<endl;
		log.Info()<<"........................................................................................log of samrt data..................................................................................................................."<<endl;
		log.Info()<<"......."<<endl;

		//1		制造命令号
		log.Info()<<"\t\t PONO="<<sd["PONO"].toString();

		//2		钢号
		log.Info()<<"\t\t HTNO="<<sd["HTNO"].toString();

		//3		配方类型
		log.Info()<<"\t\t RECIPE_TYPE="<<sd["RECIPE_TYPE"].toString();//1：新增  2：修改  3：删除

		//4		出钢记号
		log.Info()<<"\t\t STEELGRADE="<<sd["STEELGRADE"].toString();

		//5		出钢时刻
		log.Info()<<"\t\t TAP_TIME="<<sd["TAP_TIME"].toString();

		//6		计划来源： 1：新电炉  2：老电炉
		log.Info()<<"\t\t PLAN_SRC="<<sd["PLAN_SRC"].toString()<<endl;

		//7		以下循环体：料篮号-坑号-废钢代码1-废钢量1...废钢代码20-废钢量20
		for (int index = 0; index < 3; index++)
		{
			//料篮号
			log.Info()<<"\t\t B_SEQ_NUM"<<index+1<<":  "<<sd["EAF_PLAN_DETAIL"][index]["B_SEQ_NUM"].toString();
			//坑位号
			log.Info()<<"\t\t PIT_NUM"<<index+1<<":  "<<sd["EAF_PLAN_DETAIL"][index]["PIT_NUM"].toString()<<endl;

			//废钢号1
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_1:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_1"].toString();
			//废钢量1
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_1:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_1"].toString()<<endl;

			//废钢号2
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_2:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_2"].toString();
			//废钢量2
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_2:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_2"].toString()<<endl;

			//废钢号3
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_3:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_3"].toString();
			//废钢量3
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_3:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_3"].toString()<<endl;

			//废钢号4
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_4:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_4"].toString();
			//废钢量4
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_4:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_4"].toString()<<endl;

			//废钢号5
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_5:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_5"].toString();
			//废钢量5
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_5:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_5"].toString()<<endl;

			//废钢号6
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_6:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_6"].toString();
			//废钢量6
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_6:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_6"].toString()<<endl;
			
			//废钢号7
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_7:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_7"].toString();
			//废钢量7
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_7:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_7"].toString()<<endl;

			//废钢号8
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_8:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_8"].toString();
			//废钢量8
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_8:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_8"].toString()<<endl;

			//废钢号9
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_9:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_9"].toString();
			//废钢量9
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_9:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_9"].toString()<<endl;

			//废钢号10
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_10:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_10"].toString();
			//废钢量10
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_10:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_10"].toString()<<endl;

			//废钢号11
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_11:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_11"].toString();
			//废钢量11
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_11:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_11"].toString()<<endl;

			//废钢号12
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_12:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_12"].toString();
			//废钢量12
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_12:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_12"].toString()<<endl;

			//废钢号13
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_13:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_13"].toString();
			//废钢量13
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_13:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_13"].toString()<<endl;

			//废钢号14
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_14:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_14"].toString();
			//废钢量14
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_14:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_14"].toString()<<endl;

			//废钢号15
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_15:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_15"].toString();
			//废钢量15
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_15:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_15"].toString()<<endl;

			//废钢号16
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_16:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_16"].toString();
			//废钢量16
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_16:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_16"].toString()<<endl;

			//废钢号17
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_17:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_17"].toString();
			//废钢量17
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_17:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_17"].toString()<<endl;

			//废钢号18
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_18:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_18"].toString();
			//废钢量18
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_18:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_18"].toString()<<endl;

			//废钢号19
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_19:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_19"].toString();
			//废钢量19
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_19:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_19"].toString()<<endl;

			//废钢号20
			log.Info()<<"\t\t SCR_ID"<<index+1<<"_20:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_ID_20"].toString();
			//废钢量20
			log.Info()<<"\t\t SCR_WEIGHT"<<index+1<<"_20:  "<<sd["EAF_PLAN_DETAIL"][index]["SCR_WEIGHT_20"].toString()<<endl;			
		}
		//7		接收时刻
		log.Info()<<"\t\t RCV_TIME="<<iDA::DateTime::Now().ToShortTimeString()<<endl;

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
		dealdata.InsertRcvData(msgIDInTrans,dataStr,data,ID);



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

void MsgEU01::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgEU01 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string pono = sd["PONO"].toString();
		string htno = sd["HTNO"].toString();
		string recipeType = sd["RECIPE_TYPE"].toString();
		string steelGrade = sd["STEELGRADE"].toString();
		string tapTime = sd["TAP_TIME"].toString();
		string planSrc = sd["PLAN_SRC"].toString();

//=============1. 数据库中不存在主计划==============================================
		EAFPlanInfoMain planInfoMain;
		if ( false == SQL4EAF::SelEAFPlanInfoMain(pono, planInfoMain) )//不存在，直接写入
		{
			log.Info()<<"New plan , no record in databse,  insert ..................."<<endl;
			SQL4EAF::InsEAFL2PlanMain(sd);
			InsEAFL2PlanDetail(sd);
			return;
		}

//=============2. 数据库中存在主计划================================================
		log.Info()<<"Old plan , have record in databse,  ..................."<<endl;		
		//获取子表相关数据
		vector<EAFPlanInfoDetail> vecPlanInfoDetail;
		//如果子表数据不存在,直接更新主表,插入子表
		if ( false == SQL4EAF::SelEAFPlanInfoDetail(pono, vecPlanInfoDetail) )//vecPlanInfoDetail  只获取layValid=1 的 ，也就是合法的数据
		{
			log.Info()<<" no DETAIL record in databse,  insert ..................."<<endl;
			SQL4EAF::UpdatePlanMain(pono, htno, recipeType, steelGrade, tapTime, planSrc);	
			InsEAFL2PlanDetail(sd);
			return;
		}

//=============3. 数据库中存在主计划和子计划==========================================
//1. 如果sd计划是删除，逐项对比子表中数据(不用关心sd数据,因为本身sd已经是删除状态),如果子表中数据:
//		1.1没有配车:不做处理
//		1.2已经配车(car字段),但还未开始(status字段): 根据 pono, detailID 删除车辆绑定信息表中数据; 
//		1.3已经配车已经进场: 根据pono , detailID对子表记录更新 layValid=2 非法 
		if (recipeType == EAFPlanInfoMain::RECIPE_TYPE_DELETE)
		{
			log.Info()<<"recipeType == RECIPE_TYPE_DELETE ..................."<<endl;
			SQL4EAF::UpdatePlanMain(pono, htno, recipeType, steelGrade, tapTime, planSrc);//无条件更新主表

			vector<EAFPlanInfoDetail>::iterator itor;
			for (itor = vecPlanInfoDetail.begin(); itor != vecPlanInfoDetail.end(); itor++)
			{
				EAFPlanInfoDetail planDetail = *itor;
				HandlePlanDetailDel(planDetail);
			}
			return;
		}


//2. 如果sd计划是新增或修改，逐项比较sd数据和子表中数据,如果子表中数据:
//		2.1如果子表中无sd的对应层数数据, 插入数据
//		2.2如果子表中有sd的对应层数数据
//          2.2.1如果层数数据没有变化(废钢代码不变且重量不变),不做处理
//			 2.2.2如果层数数据有变化(废钢代码改变或重量改变):
//					2.2.2.1没有配车:直接更新(根据detailID)
//					2.2.2.2已经配车(car字段),但还未开始(status字段): 直接更新(根据detailID)  
//					2.2.2.3已经配车已经进场: 根据pono , detailID对子表记录更新 layValid=2 非法 ;同时插入最新数据(可能是同一层数据对应2条记录,没关系,用detailID可以区分)
//		2.3如果子表中有sd没有的层数数据
//			 2.3.1没有配车：直接删除
//			 2.3.2已经配车(car字段),但还未开始(status字段)：直接删除子表此层记录；删除车辆绑定信息表中对应记录（根据pono，detailID）
//			 2.3.1已经配车已经进场：根据pono , detailID对子表记录更新 layValid=2 非法
		if (recipeType == EAFPlanInfoMain::RECIPE_TYPE_ADD || recipeType == EAFPlanInfoMain::RECIPE_TYPE_MODIFY)
		{
			log.Info()<<"recipeType == RECIPE_TYPE_ADD  OR  RECIPE_TYPE_MODIFY ..................."<<endl;
			SQL4EAF::UpdatePlanMain(pono, htno, recipeType, steelGrade, tapTime, planSrc);//无条件更新主表

			//准备vec中每个detailID 插入map, 默认为true  方便后续操作处理
			map<long, bool> mapDetailID = Vec2Map1(vecPlanInfoDetail);
			map<long, EAFPlanInfoDetail> mapPlanInfoDetail = Vec2Map2(vecPlanInfoDetail);
			
			for (int index = 0; index < 3; index++)
			{
				log.Info()<<"sd recycle: EAF_PLAN_DETAIL , index = "<<index<<endl;
				string basketID = sd["EAF_PLAN_DETAIL"][index]["B_SEQ_NUM"].toString();
				string pitNO = sd["EAF_PLAN_DETAIL"][index]["PIT_NUM"].toString();
				//料篮号为空的情况，说明此料蓝没有配方
				if (basketID.empty())
				{
					log.Info()<<" B_SEQ_NUM  is empty......."<<endl;
					continue;
				}

				for (int i = 1; i <=20; i++)
				{
					log.Info()<<"basketID = "<<basketID<<" recycle:  i = "<<i<<endl;
					string scrIDName = "SCR_ID_" + StringHelper::ToString(i);
					string scrWeightName = "SCR_WEIGHT_" + StringHelper::ToString(i);
					long layNO = i;
					//料篮 层 对应的具体配方废钢代码和需求重量
					string scrID = sd["EAF_PLAN_DETAIL"][index][scrIDName].toString();
					long scrWeight = Str2Num(sd["EAF_PLAN_DETAIL"][index][scrWeightName].toString());

					if (scrID.empty())
					{
						log.Info()<<" SCR_ID_  is empty......."<<endl;
						continue;
					}

					//pono basketid layno scrid scrweight 都有了  ，和 vecPlanInfoDetail  中数据进行比较
					HandleSDVecPlanDetail(pono, basketID, pitNO, layNO, scrID, scrWeight, vecPlanInfoDetail, mapDetailID);

				}
			}

			//对mapDetailID进行遍历，其中false的 ，就从表中判断删除或者设置valid=2
			//		2.3如果子表中有sd没有的层数数据
			//			 2.3.1没有配车：直接删除
			//			 2.3.2已经配车(car字段),但还未开始(status字段)：直接删除子表此层记录；删除车辆绑定信息表中对应记录（根据pono，detailID）
			//			 2.3.1已经配车已经进场：根据pono , detailID对子表记录更新 layValid=2 非法
			HandleMapDetailID(mapDetailID, mapPlanInfoDetail);
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


void MsgEU01::HandlePlanDetailDel(EAFPlanInfoDetail planInfoDetail)
{
	string functionName="MsgEU01 :: HandlePlanDetail1()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string carNO = planInfoDetail.getCarNO();
		string status = planInfoDetail.getStatus();
		if (carNO.empty())
		{
			//没有配车 ，不做处理
			return;
		}
		//以下是已经配车了
		//还未开始=1，说明还未进场
		if (status == EAFPlanInfoDetail::STATUS_NOT_START)
		{
			//根据pono  detailID删除车辆信息计划表中数据
			SQL4EAF::DelCarPlanBandByDetailID(planInfoDetail.getDetailID());
			return;
		}
		//以下是已经配车，已经进场
		//根据pono , detailID对子表记录更新 layValid=2 非法 
		SQL4EAF::UpdDetailInvalidByDetailID(planInfoDetail.getDetailID());
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


long MsgEU01::Str2Num(string strNum)
{
	string functionName="MsgEU01 :: Str2Num()";
	LOG log(functionName, AUTO_CATCH_PID);
	long num = 0;

	try
	{
		if (strNum.empty())
		{
			num = 0;
		}
		else
		{
			num = StringHelper::ToNumber<long>(strNum);
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
	return num;
}

//		2.1如果子表中无sd的对应层数数据, 插入数据
//		2.2如果子表中有sd的对应层数数据
//          2.2.1如果层数数据没有变化(废钢代码不变且重量不变),不做处理
//			 2.2.2如果层数数据有变化(废钢代码改变或重量改变):
//					2.2.2.1没有配车:直接更新(根据detailID)
//					2.2.2.2已经配车(car字段),但还未开始(status字段): 直接更新(根据detailID)  
//					2.2.2.3已经配车已经进场: 根据pono , detailID对子表记录更新 layValid=2 非法 ;同时插入最新数据(可能是同一层数据对应2条记录,没关系,用detailID可以区分)
//		2.3如果子表中有sd没有的层数数据
//			 2.3.1没有配车：直接删除
//			 2.3.2已经配车(car字段),但还未开始(status字段)：直接删除子表此层记录；删除车辆绑定信息表中对应记录（根据pono，detailID）
//			 2.3.1已经配车已经进场：根据pono , detailID对子表记录更新 layValid=2 非法
void MsgEU01::HandleSDVecPlanDetail(string pono, 
																		string basketID, 
																		string pitNO, 
																		long layNO, 
																		string scrID, 
																		long scrWeight, 
																		vector<EAFPlanInfoDetail> vecPlanInfoDetail,
																		map<long, bool>& mapDetailID)
{
	string functionName="MsgEU01 :: HandleSDVecPlanDetail()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		//子表中无， sd有
		bool bFlag = false;
		vector<EAFPlanInfoDetail>::iterator itor;
		for (itor = vecPlanInfoDetail.begin(); itor != vecPlanInfoDetail.end(); itor++)
		{
			EAFPlanInfoDetail planInfoDetail = *itor;
			if (basketID == planInfoDetail.getBSeqNum() && layNO == planInfoDetail.getLayNO())//原本表中有sd的对应料蓝和层数数据
			{
				bFlag = true;
				//对mapDetailID中的detailID 的valud置成true
				mapDetailID[planInfoDetail.getDetailID()] = true;

				//如果废钢代码和需求量不变，则不做处理
				if (scrID == planInfoDetail.getScrID() && scrWeight == planInfoDetail.getScrWeight())
				{
					log.Info()<<"  scrID == planInfoDetail.getScrID() && scrWeight == planInfoDetail.getScrWeight() , NO change , no need to handle............."<<endl;					
				}
				//如果废钢代码或需求量有变化
				else
				{
					log.Info()<<"  scrID != planInfoDetail.getScrID()  or  scrWeight != planInfoDetail.getScrWeight()  ,  need to handle............."<<endl;
					string carNO = planInfoDetail.getCarNO();
					string status = planInfoDetail.getStatus();
					if (carNO.empty())
					{
						log.Info()<<"  carNO is empty, just to update............."<<endl;
						SQL4EAF::UpdPlanDetailByDetailID(planInfoDetail.getDetailID(), scrID, scrWeight);
					}
					if (!carNO.empty() && status == EAFPlanInfoDetail::STATUS_NOT_START)
					{
						log.Info()<<"  carNO is not empty, status is STATUS_NOT_START,  just to update............."<<endl;
						SQL4EAF::UpdPlanDetailByDetailID(planInfoDetail.getDetailID(), scrID, scrWeight);
					}
					if (!carNO.empty() && status != EAFPlanInfoDetail::STATUS_NOT_START)
					{
						log.Info()<<"  carNO is not empty, status is STATUS_START or STATUS_FINISH,  update invalid and insert new............."<<endl;
						//先更新原先记录 valid=2
						SQL4EAF::UpdPlanDetailInvalidByDetailID(planInfoDetail.getDetailID());
						//然后插入新记录
						string tempLayValid = EAFPlanInfoDetail::LAY_VALID_YES;
						string tempStatus = EAFPlanInfoDetail::STATUS_NOT_START;
						SQL4EAF::InsEAFL2PlanDetailSingle(pono, basketID, pitNO, layNO, scrID, scrWeight, tempLayValid, tempStatus);
					}
				}
				break;
			}
		}

		if (bFlag == false)//原本表中没有sd对应的料篮和层数数据，可以直接插入子表
		{
			log.Info()<<"basketID = "<<basketID<<", layNO = "<<layNO<<", no record  in tabledetail, ready to insert..........."<<endl;
			string layValid = EAFPlanInfoDetail::LAY_VALID_YES;
			string status = EAFPlanInfoDetail::STATUS_NOT_START;
			SQL4EAF::InsEAFL2PlanDetailSingle(pono, basketID, pitNO, layNO, scrID, scrWeight, layValid, status);
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



map<long, bool> MsgEU01::Vec2Map1(vector<EAFPlanInfoDetail> vecPlanInfoDetail)
{
	string functionName="MsgEU01 :: Vec2Map()";
	LOG log(functionName, AUTO_CATCH_PID);

	map<long, bool> mapPlanInfoDetail;

	try
	{
		vector<EAFPlanInfoDetail>::iterator itor;
		for (itor = vecPlanInfoDetail.begin(); itor != vecPlanInfoDetail.end(); itor++)
		{
			EAFPlanInfoDetail	 planInfoDetail = *itor;
			mapPlanInfoDetail.insert(pair<long, bool>(planInfoDetail.getDetailID(), false));
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
	return mapPlanInfoDetail;
}

map<long, EAFPlanInfoDetail> MsgEU01::Vec2Map2(vector<EAFPlanInfoDetail> vecPlanInfoDetail)
{
	string functionName="MsgEU01 :: Vec2Map2()";
	LOG log(functionName, AUTO_CATCH_PID);

	map<long, EAFPlanInfoDetail> mapPlanInfoDetail;

	try
	{
		vector<EAFPlanInfoDetail>::iterator itor;
		for (itor = vecPlanInfoDetail.begin(); itor != vecPlanInfoDetail.end(); itor++)
		{
			EAFPlanInfoDetail	 planInfoDetail = *itor;
			mapPlanInfoDetail.insert(pair<long, EAFPlanInfoDetail>(planInfoDetail.getDetailID(), planInfoDetail));
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
	return mapPlanInfoDetail;
}


void MsgEU01::HandleMapDetailID(map<long, bool> mapDetailID, map<long, EAFPlanInfoDetail> mapPlanInfoDetail)
{
	string functionName="MsgEU01 :: HandleMapDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		map<long, bool>::iterator itor;
		for (itor = mapDetailID.begin(); itor != mapDetailID.end(); itor++)
		{
			long detalID = itor->first;
			bool bFlag = itor->second;
			if (bFlag == false)//SD中不存在的层号
			{
				EAFPlanInfoDetail planInfoDetail = mapPlanInfoDetail[detalID];
				string carNO = planInfoDetail.getCarNO();
				string status = planInfoDetail.getStatus();

				long detailID = planInfoDetail.getDetailID();

				log.Info()<<"this DetailID = "<<detailID<<"  in database  plan is FALSE...means this database DetailID is not exist in TEL SD data ......"<<endl;
				if (carNO.empty())
				{
					log.Info()<<"car is empty , ready delete this deailID.........."<<endl;
					//没有配车 ，删除
					SQL4EAF::DelEAFPlanDetailByID(detailID);
					return;
				}
				//以下是已经配车了
				//还未开始=1，说明还未进场
				if (status == EAFPlanInfoDetail::STATUS_NOT_START)
				{
					log.Info()<<"car is not empty , but status is not start,  ready delete this detailID and CarPlanBand.........."<<endl;
					//根据pono  detailID删除车辆信息计划表中数据
					SQL4EAF::DelEAFPlanDetailByID(detailID);
					SQL4EAF::DelCarPlanBandByDetailID(detailID);
					return;
				}
				log.Info()<<"car is not empty , and status is start,  ready update this detailID to invalid ........."<<endl;
				//以下是已经配车，已经进场
				//根据pono , detailID对子表记录更新 layValid=2 非法 
				SQL4EAF::UpdDetailInvalidByDetailID(detailID);
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


void MsgEU01::InsEAFL2PlanDetail(SmartData sd)
{
	string functionName="MsgEU01 :: InsEAFL2PlanDetail()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string pono = sd["PONO"].toString();	//制造命令号
		string basketID;	//料篮号
		string pitNO;		//坑位号
		string status = "1";
		string layValid= "1";

		for (int index = 0; index < 3; index++)
		{
			log.Info()<<"sd recycle: EAF_PLAN_DETAIL , index = "<<index<<endl;
			basketID = sd["EAF_PLAN_DETAIL"][index]["B_SEQ_NUM"].toString();
			pitNO = sd["EAF_PLAN_DETAIL"][index]["PIT_NUM"].toString();
			if (basketID.empty())
			{
				log.Info()<<"EAF_PLAN_DETAIL , index = "<<index<<", B_SEQ_NUM  is empty......."<<endl;
				continue;
			}

			for (int i = 1; i <=20; i++)
			{
				log.Info()<<"basketID = "<<basketID<<" recycle:  i = "<<i<<endl;
				string scrIDName = "SCR_ID_" + StringHelper::ToString(i);
				string scrWeightName = "SCR_WEIGHT_" + StringHelper::ToString(i);
				long layNO = i;
				//料篮 层 对应的具体配方废钢代码和需求重量
				string scrID = sd["EAF_PLAN_DETAIL"][index][scrIDName].toString();
				long scrWeight = Str2Num(sd["EAF_PLAN_DETAIL"][index][scrWeightName].toString());

				if (scrID.empty())
				{
					log.Info()<<" SCR_ID_  is empty......."<<endl;
					continue;
				}
				SQL4EAF::InsEAFL2PlanDetailSingle(pono, basketID, pitNO, layNO, scrID, scrWeight, layValid, status);
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