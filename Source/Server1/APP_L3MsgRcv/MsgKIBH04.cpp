#include "MsgKIBH04.h"
#include "L3PlanInfo.h"
#include "DealData.h"

using namespace Monitor;
using namespace iPlature;

MsgKIBH04*  MsgKIBH04::m_pMsgKIBH04 = NULL;


MsgKIBH04::MsgKIBH04() 
{
	msgId="KIBH04";
	readSmartDataSuccessed=false;
	writeToTagSystemTapper=false;
}


MsgKIBH04 :: ~MsgKIBH04(void)
{

	delete m_pMsgKIBH04;


}

MsgKIBH04* MsgKIBH04::getInstance(void)
{
	if (m_pMsgKIBH04 == NULL)
	{
		m_pMsgKIBH04 = new MsgKIBH04;
	}
	return m_pMsgKIBH04;
}

ByteSeq MsgKIBH04::HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName)
{
	string functionName="MsgKIBH04 :: HandleMessage()";
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
		log.Info()<<"....................................................log of samrt data..................................................."<<endl;
		string temp = "";

		//1		计划号
		temp = sd["PLAN_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["PLAN_NO"] = temp;
		log.Info()<<"PLAN_NO="<<sdTrim["PLAN_NO"].toString()<<endl;

		//2		料槽号
		temp = sd["HOPPER_NO"].toString();
		StringHelper::Trim(temp);
		sdTrim["HOPPER_NO"] = temp;
		log.Info()<<"HOPPER_NO="<<sdTrim["HOPPER_NO"].toString()<<endl;

		//3		实际称量重量
		temp = sd["MAT_NET_WT"].toString();
		StringHelper::Trim(temp);
		sdTrim["MAT_NET_WT"] = temp;
		log.Info()<<"MAT_NET_WT="<<sdTrim["MAT_NET_WT"].toInt()<<endl;

		////4		计量申请号
		//temp = sd["WEIGH_APP_NO"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["WEIGH_APP_NO"] = temp;
		//log.Info()<<" WEIGH_APP_NO="<<sdTrim["WEIGH_APP_NO"].toString()<<endl;

		////5		计量申请时刻
		//temp = sd["WEIGH_APP_TIME"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["WEIGH_APP_TIME"] = temp;
		//log.Info()<<"WEIGH_APP_TIME="<<sdTrim["WEIGH_APP_TIME"].toString()<<endl;

		////6		操作者
		//temp = sd["REC_CREATOR"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["REC_CREATOR"] = temp;
		//log.Info()<<"REC_CREATOR="<<sdTrim["REC_CREATOR"].toString()<<endl;

		////7		源库区代码
		//temp = sd["SRC_STOCK_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["SRC_STOCK_CODE"] = temp;
		//log.Info()<<"SRC_STOCK_CODE="<<sdTrim["SRC_STOCK_CODE"].toString()<<endl;

		////8		源库位代码
		//temp = sd["SRC_LOC_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["SRC_LOC_CODE"] = temp;
		//log.Info()<<"SRC_LOC_CODE="<<sdTrim["SRC_LOC_CODE"].toString()<<endl;

		////9		发方物料代码
		//temp = sd["SRC_MAT_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["SRC_MAT_CODE"] = temp;
		//log.Info()<<"SRC_MAT_CODE="<<sdTrim["SRC_MAT_CODE"].toString()<<endl;

		////10		发方钢制代码
		//temp = sd["SRC_COMP_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["SRC_COMP_CODE"] = temp;
		//log.Info()<<"SRC_COMP_CODE="<<sdTrim["SRC_COMP_CODE"].toString()<<endl;

		////11		目的库区代码
		//temp = sd["DST_STOCK_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["DST_STOCK_CODE"] = temp;
		//log.Info()<<"DST_STOCK_CODE="<<sdTrim["DST_STOCK_CODE"].toString()<<endl;

		////12		目的库位代码
		//temp = sd["DST_LOC_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["DST_LOC_CODE"] = temp;
		//log.Info()<<"DST_LOC_CODE="<<sdTrim["DST_LOC_CODE"].toString()<<endl;

		////13		收方物料代码
		//temp = sd["DST_MAT_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["DST_MAT_CODE"] = temp;
		//log.Info()<<"DST_MAT_CODE="<<sdTrim["DST_MAT_CODE"].toString()<<endl;

		////14		收方钢制代码
		//temp = sd["DST_COMP_CODE"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["DST_COMP_CODE"] = temp;
		//log.Info()<<"DST_COMP_CODE="<<sdTrim["DST_COMP_CODE"].toString()<<endl;

		////15		估计重量（对于装车出库有意义）
		//temp = sd["ESTIMATE_WGT"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["ESTIMATE_WGT"] = temp;
		//log.Info()<<"ESTIMATE_WGT="<<sdTrim["ESTIMATE_WGT"].toInt()<<endl;

		////16		建议归堆标志
		//temp = sd["START_FLAG"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["START_FLAG"] = temp;
		//log.Info()<<"START_FLAG="<<sdTrim["START_FLAG"].toString()<<endl;//G:建议归堆  C:取消归堆

		////17		是否需要质检标志
		//temp = sd["QC_FLAG"].toString();
		//StringHelper::Trim(temp);
		//sdTrim["QC_FLAG"] = temp;
		//log.Info()<<"QC_FLAG="<<sdTrim["QC_FLAG"].toString()<<endl;//1:需要  0：不需要

		//18 	备注1
		//log.Info()<<"\t\t BACK1="<<sd["BACK1"].toString();
		//19		备注2
		//log.Info()<<"\t\t BACK2="<<sd["BACK2"].toString();
		//20		备注3
		//log.Info()<<"\t\t BACK3="<<sd["BACK3"].toString();
		//21		备注4
		//log.Info()<<"\t\t BACK4="<<sd["BACK4"].toString();
		//22		备注5
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
		HandleDataIntoDB(sdTrim);

		////建议卸料归堆通知
		//CanXLStartNotify(sdTrim);

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


void MsgKIBH04::HandleDataIntoDB(SmartData sd)
{
	string functionName="MsgKIBH04 :: HandleDataIntoDB()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string planNO = sd["PLAN_NO"].toString();//计划号
		string hopperNO = sd["HOPPER_NO"].toString();//料槽号
		int netWeight = sd["MAT_NET_WT"].toInt();//实际称量重量


		//更新配料计划表
		SQL4L3::UpdateMatOutInfo_WT(planNO, hopperNO, netWeight);
		log.Info()<<"planNO = "<<planNO<<" , UpdateMatCarRelationInfo.........return.........."<<endl;
		return;


		////20220714 zhangyuhong add
		////判断原 目的库区是否是二炼钢 不是二炼钢堆场的 直接返回报警
		//string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		//string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		//if (srcStockCode != SCRAP_YARD_NAME && dstStockCode != SCRAP_YARD_NAME)
		//{
		//	log.Info()<<"srcStockCode or dstStockCode are not SCRAP_YARD_NAME, L3 plan is error .........return.........."<<endl;
		//	return;
		//}
		//
		//原先不存在记录的情况下，则直接插入新纪录
//		L3PlanInfo planInfo;
//		if (false == SQL4L3::SelL3PlanInfo(workSeqNO, planInfo))
//		{
//			log.Info()<<"workSeqNO = "<<workSeqNO<<" , no record in table , insert into .........return.........."<<endl;
//			string planType = GetL3PlanType(sd);
//			SQL4L3::InsertMatInOutInfo(sd, planType);
//			//绑定车辆计划信息表
//			BandCarPlanInfo(sd, planInfo, "0", "");
//			return;
//		}
//
////=========================================================================================
//		log.Info()<<"workSeqNO = "<<workSeqNO<<" , have record in table , need to judge something........."<<endl;
//		//存在记录的情况下
//		string wmsOperateFlag = planInfo.getOperateFlag();
//		string wmsPlanType = planInfo.getPlanType();
//		string wmsPlanValid = planInfo.getPlanValid();
//		
//		//如果原先记录是删除标记，则先删除，再插入
//		if (wmsOperateFlag == L3PlanInfo::OPERATE_FLAG_D)
//		{
//			log.Info()<<"wmsOperateFlag = D.........."<<endl;
//			SQL4L3::DelMatInOutInfo(workSeqNO);
//			string planType = GetL3PlanType(sd);
//			SQL4L3::InsertMatInOutInfo(sd, planType);
//
//			if (wmsPlanValid == L3PlanInfo::PLAN_VALID_YES)//原先是合法的,可以绑定车辆计划表
//			{
//				log.Info()<<"wmsPlanValid = 1  valid.........."<<endl;
//				//绑定车辆计划信息表
//				BandCarPlanInfo(sd, planInfo, "0", "");
//				return;
//			}
//
//			if (wmsPlanValid == L3PlanInfo::PLAN_VALID_NO)//原先是非法的，说明此计划之前已经有过车辆到达或作业完成,  因此还是非法的，不再绑定车辆计划表（需要换workSeqNO）
//			{
//				log.Info()<<"wmsPlanValid = 2  invalid.........."<<endl;
//				SQL4L3::UpdL3PlanInfoPlanVlaid(workSeqNO, wmsPlanValid);
//				return;
//			}
//		}
////=========================================================================================
//
////=========================================================================================
//		//如果原先记录是新增标记  ,收到记录是删除标记
//		if (wmsOperateFlag == L3PlanInfo::OPERATE_FLAG_I && operateFlag == L3PlanInfo::OPERATE_FLAG_D)
//		{
//			//对计划表进行操作
//			SQL4L3::DelMatInOutInfo(planInfo.getWorkSeqNO());
//			string sdPlanType = GetL3PlanType(sd);
//			SQL4L3::InsertMatInOutInfo(sd, sdPlanType);
//
//			log.Info()<<"wmsOperateFlag == I && operateFlag == D ....................................."<<endl;
//			string planValid = L3PlanInfo::PLAN_VALID_YES;
//
//			//1.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC...................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC)//如果原先是装车,现在取消了
//			{
//				log.Info()<<"planInfo.getPlanType() = ZC   .............."<<endl;
//				CheckWorkProg(planInfo, "ZC", planValid);
//			}
//
//			//2.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_XL..................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_XL)//如果原先是卸料，现在取消了
//			{
//				log.Info()<<"planInfo.getPlanType() = XL................."<<endl;
//				CheckWorkProg(planInfo, "XL", planValid);
//			}
//
//			//3.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC_XL..................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC_XL)//如果原先是装车+卸料
//			{
//				log.Info()<<"planInfo.getPlanType() = ZC_XL.........."<<endl;
//				//检查装车作业进度
//				string zcPlanValid = L3PlanInfo::PLAN_VALID_YES;
//				CheckWorkProg(planInfo, "ZC", zcPlanValid);
//				log.Info()<<"zcPlanValid = "<<zcPlanValid<<endl;
//
//				//检查卸料作业进度
//				string xlPlanValid = L3PlanInfo::PLAN_VALID_YES;
//				CheckWorkProg(planInfo, "XL", xlPlanValid);
//				log.Info()<<"xlPlanValid = "<<xlPlanValid<<endl;
//
//				//转车或卸料 有一个是非法 就是非法
//				if (zcPlanValid == L3PlanInfo::PLAN_VALID_NO || xlPlanValid == L3PlanInfo::PLAN_VALID_NO)
//				{
//					planValid = L3PlanInfo::PLAN_VALID_NO;
//				}
//			}			
//			SQL4L3::UpdL3PlanInfoPlanVlaid(planInfo.getWorkSeqNO(), planValid);
//			return;
//		}
////=========================================================================================
//
////=========================================================================================
//		if (wmsOperateFlag == L3PlanInfo::OPERATE_FLAG_I && operateFlag == L3PlanInfo::OPERATE_FLAG_I)
//		{
//			//对计划表进行操作
//			SQL4L3::DelMatInOutInfo(planInfo.getWorkSeqNO());
//			string sdPlanType = GetL3PlanType(sd);
//			SQL4L3::InsertMatInOutInfo(sd, sdPlanType);
//
//			log.Info()<<"wmsOperateFlag == I && operateFlag == I ....................................."<<endl;
//			string planValid = L3PlanInfo::PLAN_VALID_YES;			
//
////1.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC...................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC)//如果原先是装车
//			{
//				log.Info()<<"planInfo.getPlanType() = ZC.........."<<endl;
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC )//最新还是装车
//				{
//					log.Info()<<"sdPlanType = ZC .............."<<endl;
//					CheckZCSrcInfo(planInfo, sd, planValid);
//				}
//
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_XL)//最新只有卸料了   取消了装车
//				{
//					log.Info()<<"sdPlanType = XL   only.............."<<endl;
//					CheckWorkProg(planInfo, "ZC", planValid);
//					//取消了装车,新增了卸料，如果原先 planValid=1 合法 ，则可以新增卸料作业的 车辆 计划绑定表
//					if (planValid == L3PlanInfo::PLAN_VALID_YES)
//					{
//						BandCarPlanInfo(sd, planInfo, "1", "XL");
//					}					
//				}
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC_XL)
//				{
//					log.Info()<<"sdPlanType = ZC_XL .............."<<endl;
//					CheckZCSrcInfo(planInfo, sd, planValid);
//					//新增了卸料，如果原先 planValid=1 合法 ，则可以新增卸料作业的 车辆 计划绑定表
//					if (planValid == L3PlanInfo::PLAN_VALID_YES)
//					{
//						BandCarPlanInfo(sd, planInfo, "1", "XL");
//					}			
//				}
//			}
//
////2.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_XL...................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_XL)//如果原先是卸料
//			{
//				log.Info()<<"planInfo.getPlanType() = XL.........."<<endl;
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_XL) //最新是卸料
//				{
//					log.Info()<<"sdPlanType = XL.............."<<endl;
//					CheckXLDstInfo(planInfo, sd, planValid);
//				}
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC)//最新是装车   取消了卸料
//				{
//					log.Info()<<"sdPlanType = ZC   only.............."<<endl;
//					CheckWorkProg(planInfo, "XL", planValid);
//					//取消了卸料，新增了装车，如果原先 planValid=1 合法 ，则可以新增装车的 车辆 计划绑定表
//					if (planValid == L3PlanInfo::PLAN_VALID_YES)
//					{
//						BandCarPlanInfo(sd, planInfo, "1", "ZC");
//					}		
//				}
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC_XL)
//				{
//					log.Info()<<"sdPlanType = ZC_XL .............."<<endl;
//					CheckXLDstInfo(planInfo, sd, planValid);
//					//新增了装车，如果原先 planValid=1 合法 ，则可以新增装车作业的 车辆 计划绑定表
//					if (planValid == L3PlanInfo::PLAN_VALID_YES)
//					{
//						BandCarPlanInfo(sd, planInfo, "1", "ZC");
//					}			
//				}
//			}
//
//
////3.................planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC_XL...................................................................................................................................
//			if (planInfo.getPlanType() == L3PlanInfo::PLAN_TYPE_ZC_XL)//如果原先是装车+卸料
//			{
//				log.Info()<<"planInfo.getPlanType() = ZC_XL.........."<<endl;
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC )//最新是装车,  取消了卸料
//				{
//					log.Info()<<"sdPlanType = ZC only.............."<<endl;
//					//检查ZC信息是否变化
//					string zcPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckZCSrcInfo(planInfo, sd, zcPlanValid);
//
//					//获取卸料作业进度
//					string xlPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckWorkProg(planInfo, "XL", xlPlanValid);		
//					
//					if (zcPlanValid == L3PlanInfo::PLAN_VALID_NO || xlPlanValid == L3PlanInfo::PLAN_VALID_NO)
//					{
//						planValid = L3PlanInfo::PLAN_VALID_NO;
//					}
//				}
//
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_XL)//最新是卸料，取消了装车
//				{
//					log.Info()<<"sdPlanType = XL only.............."<<endl;
//					//检查XL信息是否变化
//					string xlPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckXLDstInfo(planInfo, sd, xlPlanValid);
//
//					//获取装车作业进度
//					string zcPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckWorkProg(planInfo, "ZC", zcPlanValid);	
//
//					if (xlPlanValid == L3PlanInfo::PLAN_VALID_NO || zcPlanValid == L3PlanInfo::PLAN_VALID_NO)
//					{
//						planValid = L3PlanInfo::PLAN_VALID_NO;
//					}
//				}
//
//				if (sdPlanType == L3PlanInfo::PLAN_TYPE_ZC_XL)
//				{
//					log.Info()<<"sdPlanType = ZC_XL .............."<<endl;
//					//检查ZC  XL信息是否变化
//					string zcPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckZCSrcInfo(planInfo, sd, zcPlanValid);
//
//					string xlPlanValid = L3PlanInfo::PLAN_VALID_YES;
//					CheckXLDstInfo(planInfo, sd, xlPlanValid);
//
//					if (xlPlanValid == L3PlanInfo::PLAN_VALID_NO || zcPlanValid == L3PlanInfo::PLAN_VALID_NO)
//					{
//						planValid = L3PlanInfo::PLAN_VALID_NO;
//					}
//				}
//			}
//			
//			SQL4L3::UpdL3PlanInfoPlanVlaid(planInfo.getWorkSeqNO(), planValid);
			
		//}//end of  wmsOperateFlag = I  operateFlag = I

		
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


void MsgKIBH04::BandCarPlanInfo(SmartData sd, L3PlanInfo planInfo, string assignFlag, string assignWorkType)
{
	string functionName="MsgKIBH04 :: BandCarPlan()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//源库位代码
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//发方物料代码
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//发方钢制代码
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		string dstLocCode = sd["DST_LOC_CODE"].toString();//目的库位代码
		string dstMatCode = sd["DST_MAT_CODE"].toString();//收方物料代码
		string dstCompCode = sd["DST_COMP_CODE"].toString();//收方钢制代码

		//需要插入或更新的数据有：
		//车号   车类型   作业类型    计划号（流水号）  计划来源   是否进入库区标记（1）   有无指令标记     绑定时刻
		//
		string carNO = sd["CAR_NO"].toString();//车号
		string carType = "1";
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//流水号
		string planSrc = "L3";
		string enterFlag = "1";
		string orderFlag = "1";
		iDA::DateTime bandTime = iDA::DateTime::Now();
		iDA::DateTime bandTime1 = iDA::DateTime::Now();

		int bandTimeSec = bandTime.GetSecond();
		bandTime1.SetSecond(bandTimeSec - 1);

		string workType = "";

		if (operateFlag == "D")
		{
			//执行删除车辆计划绑定信息表
			log.Info()<<"tel SD  operateFlag == D.........  no need do ...........return..."<<endl;
			return;
		}

		if (operateFlag == "I" && assignFlag == "0")//不指定
		{
			//以下就是执行新增 operateFlag=="I"的情况
			//先DELETE 然后INSERT
			//先删除
			SQL4L3::DelCarPlanBandInfo(planInfo.getCarNO(), workSeqNO);
			//库区名称待定，由L3给出定义
			if  (srcStockCode == SCRAP_YARD_NAME && dstStockCode == SCRAP_YARD_NAME)//对于L3来说，电炉EF跨库区和二炼钢ABC跨库区都是同一个库区
			{			
				//这种情况就是 从电炉废钢库区到二炼钢废钢库区  或者  二炼钢废钢库区到电炉废钢库区
				//这种情况 有ZC  有XL  因此，目的料格也就有2个
				//需要插入2条记录：装车和卸料  
				workType = "ZC";
				//如果同时有装车和卸料,则装车的绑定时间-1秒,为的是后续按照时间ASC排序能先选到
				SQL4L3::InsCarPlanBandInfo(carNO, carType, workType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime1);
				workType = "XL";
				SQL4L3::InsCarPlanBandInfo(carNO, carType, workType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime);
				return;			
			}
			//以下情况就是：要么 srcStockCode是WMS作业库区，要么  dstStockCode 是WMS作业库区  ，不可能同时是WMS作业库区
			if (srcStockCode == SCRAP_YARD_NAME)
			{
				//源库区是WMS库区，是装车作业
				workType = "ZC";
				SQL4L3::InsCarPlanBandInfo(carNO, carType, workType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime);
				return;
			}
			if (dstStockCode == SCRAP_YARD_NAME)
			{
				//目的库区是WMS库区，是卸料作业
				workType = "XL";
				SQL4L3::InsCarPlanBandInfo(carNO, carType, workType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime);
				return;
			}
		}

		if (operateFlag == "I" && assignFlag == "1") //指定
		{
			//以下就是执行新增 operateFlag=="I"的情况
			//先DELETE 然后INSERT
			SQL4L3::DelCarPlanBandInfoByWorkType(planInfo.getCarNO(), workSeqNO, assignWorkType);
			SQL4L3::InsCarPlanBandInfo(carNO, carType, assignWorkType, workSeqNO, planSrc, enterFlag, orderFlag, bandTime);
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


string MsgKIBH04::GetL3PlanType(SmartData sd)
{
	string functionName="MsgKIBH04 :: GetL3PlanType()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码

		string planType = "";
		if  (srcStockCode == SCRAP_YARD_NAME && dstStockCode == SCRAP_YARD_NAME)//对于L3来说，电炉EF跨库区和二炼钢ABC跨库区都是同一个库区
		{
			planType = L3PlanInfo::PLAN_TYPE_ZC_XL;//既有装车  也有卸车
			return planType;
		}
		if (srcStockCode == SCRAP_YARD_NAME)
		{
			planType = L3PlanInfo::PLAN_TYPE_ZC;//装车 
			return planType;
		}
		if (dstStockCode == SCRAP_YARD_NAME)
		{
			planType = L3PlanInfo::PLAN_TYPE_XL;//卸车
			return planType;
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


bool MsgKIBH04::SrcInfoNotChange(L3PlanInfo planInfo, SmartData sd)
{
	string functionName="MsgKIBH04 :: SrcInfoNotChange()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		string wmsSrcStockCode = planInfo.getSrcStockCode();
		string wmsSrcLocCode = planInfo.getSrcLocCode();
		string wmsSrcMatCode = planInfo.getSrcMatCode();
		string wmsSrcCompCode = planInfo.getSrcCompCode();

		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//源料格代码
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//源料格代码
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//源料格代码

		if (wmsSrcStockCode == SCRAP_YARD_NAME && srcStockCode == SCRAP_YARD_NAME)//
		{
			if (wmsSrcLocCode == srcLocCode && wmsSrcMatCode == srcMatCode && wmsSrcCompCode == srcCompCode)//如果料格 物料代码 钢制码 有1个不一致 就认为是有变化
			{
				ret = true;
				return ret;
			}
			else
			{
				ret = false;
				return ret;
			}
		}		
		return ret;
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


bool MsgKIBH04::DstInfoNotChange(L3PlanInfo planInfo, SmartData sd)
{
	string functionName="MsgKIBH04 :: DstInfoNotChange()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		string wmsDstStockCode = planInfo.getDstStockCode();
		string wmsDstLocCode = planInfo.getDstLocCode();
		string wmsDstMatCode = planInfo.getDstMatCode();
		string wmsDstCompCode = planInfo.getDstCompCode();

		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		string dstLocCode = sd["DST_LOC_CODE"].toString();//目的料格代码
		string dstMatCode = sd["DST_MAT_CODE"].toString();//目的料格代码
		string dstCompCode = sd["DST_COMP_CODE"].toString();//目的料格代码

		if (wmsDstStockCode == SCRAP_YARD_NAME && dstStockCode == SCRAP_YARD_NAME)//
		{
			if (wmsDstLocCode == dstLocCode && wmsDstMatCode == dstMatCode && wmsDstCompCode == dstCompCode)//如果料格 物料代码 钢制码 有1个不一致 就认为是有变化
			{
				ret = true;
				return ret;
			}
			else
			{
				ret = false;
				return ret;
			}
		}		
		return ret;
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

bool MsgKIBH04::CarNONotChange(L3PlanInfo planInfo, SmartData sd)
{
	string functionName="MsgKIBH04 :: CarNONotChange()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		string wmsCarNO = planInfo.getCarNO();//车号
		string sdCarNO = sd["CAR_NO"].toString();//车号
		if (wmsCarNO == sdCarNO)//
		{
			ret = true;
			return ret;
		}		
		return ret;
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


//检查是否需要重新编辑 车辆信息绑定表
void MsgKIBH04::CheckZCSrcInfo(L3PlanInfo planInfo, SmartData sd, string& planValid)
{
	string functionName="MsgKIBH04 :: CheckZCSrcInfo()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		if (true == SrcInfoNotChange(planInfo, sd) && true == CarNONotChange(planInfo, sd))//源料格信息不变 车号不变
		{
			log.Info()<<" SrcInfoNotChange = true,  CarNONotChange = true........"<<endl;
			planValid = L3PlanInfo::PLAN_VALID_YES;//合法
		}
		else//源料格信息变化或车号变化
		{
			//获取原先车辆进度
			string enterFlag = "";
			if (false == SQL4L3::SelCarStatusByWokrType(planInfo.getCarNO(), planInfo.getWorkSeqNO(), "ZC", enterFlag))
			{
				//装车已经完成，已变化信息认定非法
				log.Info()<<" SelCarStatus  false, plan  not exist in carplanband table....................."<<endl;
				planValid = L3PlanInfo::PLAN_VALID_NO;//非法
			}
			else	
			{
				if (enterFlag == "1")
				{
					log.Info()<<"enterFlag = 1, car not arrive in yard , can change carplanband table........."<<endl;
					BandCarPlanInfo(sd, planInfo, "1", "ZC");
					planValid = L3PlanInfo::PLAN_VALID_YES;
				}
				else
				{
					log.Info()<<"enterFlag != 1, car  in yard , can not  change carplanband table........."<<endl;
					planValid = L3PlanInfo::PLAN_VALID_NO;
				}				
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

//检查是否需要重新编辑 车辆信息绑定表
void MsgKIBH04::CheckXLDstInfo(L3PlanInfo planInfo, SmartData sd, string& planValid)
{
	string functionName="MsgKIBH04 :: CheckXLDstInfo()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		if (true == DstInfoNotChange(planInfo, sd) && true == CarNONotChange(planInfo, sd))//目的料格信息不变 车号不变
		{
			log.Info()<<" DstInfoNotChange = true,  CarNONotChange = true........"<<endl;
			planValid = "1";//合法
		}
		else//目的料格信息变化或车号变化
		{
			//获取原先车辆进度
			string enterFlag = "";
			if (false == SQL4L3::SelCarStatusByWokrType(planInfo.getCarNO(), planInfo.getWorkSeqNO(), "XL", enterFlag))
			{
				//卸料已经完成，已变化信息认定非法
				log.Info()<<" SelCarStatus  false, plan  not exist in carplanband table....................."<<endl;
				planValid = "2";//非法
			}
			else	
			{
				if (enterFlag == "1")
				{
					log.Info()<<"enterFlag = 1, car not arrive in yard , can change carplanband table........."<<endl;
					BandCarPlanInfo(sd, planInfo, "1", "XL");
					planValid = "1";
				}
				else
				{
					log.Info()<<"enterFlag != 1, car  in yard , can not  change carplanband table........."<<endl;
					planValid = "2";
				}				
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

//检查是否需要删除 车辆计划信息绑定表
void MsgKIBH04::CheckWorkProg(L3PlanInfo planInfo, string workType, string& planValid)
{
	string functionName="MsgKIBH04 :: CheckWorkProg()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string enterFlag = "";
		if (false == SQL4L3::SelCarStatusByWokrType(planInfo.getCarNO(), planInfo.getWorkSeqNO(), workType, enterFlag))
		{
			//已经完成，已变化信息认定非法
			log.Info()<<" SelCarStatus  false, plan  not exist in carplanband table....................."<<endl;
			planValid = L3PlanInfo::PLAN_VALID_NO;//非法
		}
		else	
		{
			if (enterFlag == "1")
			{
				log.Info()<<"enterFlag = 1, car not arrive in yard , can change carplanband table........."<<endl;//车辆还没到，删除绑定信息
				SQL4L3::DelCarPlanBandInfoByWorkType(planInfo.getCarNO(), planInfo.getWorkSeqNO(), workType);
				planValid = L3PlanInfo::PLAN_VALID_YES;
			}
			else
			{
				log.Info()<<"enterFlag != 1, car  in yard , can not  change carplanband table........."<<endl;
				planValid = L3PlanInfo::PLAN_VALID_NO;
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


//L3建议归堆启动通知:采用EVtag点通知
void MsgKIBH04::CanXLStartNotify(SmartData sd)
{
	string functionName="MsgKIBH04 :: CanXLStartNotify()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		string workSeqNO = sd["WORK_SEQ_NO"].toString();
		string sdPlanType = GetL3PlanType(sd);
		if (sdPlanType == L3PlanInfo::PLAN_TYPE_XL || sdPlanType == L3PlanInfo::PLAN_TYPE_ZC_XL)
		{
			string canXLNotify = sd["START_FLAG"].toString();
			string tagName = "";
			string tagValue = workSeqNO;

			log.Info()<<"canXLNotify = "<<canXLNotify<<endl;
			if (canXLNotify == L3PlanInfo::START_FLAG_G)//可以卸料归堆标识：G
			{
				tagName = "EV_L3_START_FLAG_G";//卸料归堆标记tag点
				EVTagSnd(tagName, tagValue);
				log.Info()<<"Send EV_L3_START_FLAG_G , workSeqNO = "<<workSeqNO<<endl;
			}
			if (canXLNotify == L3PlanInfo::START_FLAG_C)
			{
				tagName = "EV_L3_START_FLAG_C";//卸料归堆标记tag点
				EVTagSnd(tagName, tagValue);
				log.Info()<<"Send EV_L3_START_FLAG_C , workSeqNO = "<<workSeqNO<<endl;
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


bool MsgKIBH04::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgKIBH04 :: EVTagSnd()";
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