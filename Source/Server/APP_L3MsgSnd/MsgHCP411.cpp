#include "MsgHCP411.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "SQL4L3.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgHCP411::MsgHCP411(void)
{
	m_strMsgId = "HCP411";
}

MsgHCP411::~MsgHCP411(void)
{

}

void MsgHCP411::HandleMessage(const string strValue, const string logFileName)
{
	LOG log("MsgHCP411::HandleMessage",logFileName);
	try
	{
		log.Info()<<"send tel data is ready to start........................................................"<<endl;
		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		//strValue格式：
		//OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE，WORK_STATUS,  WORK_TIME
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 5)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string OPERATE_FLAG = kValues[0];//操作标志
		string WORK_SEQ_NO = kValues[1];//流水号
		string WORK_TYPE = kValues[2];//作业类型：1：ZC  2：XL
		string WORK_STATUS = kValues[3];//作业状态： 1：车辆入场  2：车到料格  3：车辆离开  4：归堆开始   5：归堆结束
		string WORK_TIME = kValues[4];//

		log.Info()<<"OPERATE_FLAG = "<<OPERATE_FLAG<<endl;
		log.Info()<<"WORK_SEQ_NO = "<<WORK_SEQ_NO<<endl;
		log.Info()<<"WORK_TYPE = "<<WORK_TYPE<<endl;
		log.Info()<<"WORK_STATUS = "<<WORK_STATUS<<endl;
		log.Info()<<"WORK_TIME = "<<WORK_TIME<<endl;

		//对UACS_L3_MAT_IN_OUT_INFO表中的PLAN_STATUS进行更新
		string planStatus = GetPlanStatus(WORK_TYPE, WORK_STATUS);
		if (!planStatus.empty())
		{
			log.Info()<<"update L3PLAN STATUS.................."<<endl;
			//更新表 PLAN_STATUS字段
			SQL4L3::UpdL3PLanStatus(WORK_SEQ_NO, planStatus);
		}

		//有重量 更新重量
		if (kValues.size() == 6)
		{
			long craneWgt = StringHelper::ToNumber<long>( kValues[5] );
			if (WORK_TYPE == "1") // 装车类型  更新对应重量字段
			{
				log.Info()<<"update L3PLAN CraneWgtZC.................."<<endl;
				SQL4L3::UpdL3PlanCraneWgtZC(WORK_SEQ_NO, craneWgt);
			}
			if (WORK_TYPE == "2") // 卸料类型  更新对应重量字段
			{
				log.Info()<<"update L3PLAN CraneWgtXL.................."<<endl;
				SQL4L3::UpdL3PlanCraneWgtXL(WORK_SEQ_NO, craneWgt);
			}

		}

		//只有 1  2  3  4  5  状态是需要向L3发送电文通知的
		if (WORK_STATUS != "1" && WORK_STATUS != "2" && WORK_STATUS != "3" && WORK_STATUS != "4" && WORK_STATUS != "5")
		{
			log.Info()<<"WORK_STATUS = "<<WORK_STATUS<<" , NOT 1 or 2 or 3 or 4 or 5,  no need to send HCP411 to L3..........return..........."<<endl;
			return;
		}

		//组织smartdata数据
		sd["OPERATE_FLAG"] = OPERATE_FLAG;
		sd["WORK_SEQ_NO"] = WORK_SEQ_NO;
		sd["WORK_TYPE"] = WORK_TYPE;
		sd["WORK_STATUS"] = WORK_STATUS;
		sd["WORK_TIME"] = WORK_TIME;
		
		//打印十六进制电文数据
		ByteSeq data;
		sd.writeTo(data);
		string sndTel = "";
		sndTel.assign(data.begin(), data.end());
		//data>>sndTel;	
		ArrayMsg arrayMsgDataBuf;
		for (int i = 0; i < sndTel.length(); i ++)
		{
			arrayMsgDataBuf.push_back(*(sndTel.c_str() + i));
		}
		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//将发送数据记录到数据库表中
		DealData dealdata = DealData();
		//明码电文
		string dataStr = dealdata.DumpValue(sd,",");
		//获取最大ID号
		int ID = dealdata.GetMaxId();
		//最大ID号加1
		ID += 1; 
		//将数据存到发送表中
		dealdata.InsertSendData(m_strMsgId,dataStr,data,ID);

		//开始发送电文
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//获取代理
		proxy->SendMsg(m_strMsgId, data);

		log.Info()<<"m_strMsgId = "<<m_strMsgId<<"  send ok....................................................."<<endl;

		//置发送标志位
		dealdata.UpdateSendDataFlag(ID);

		


	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
}


string MsgHCP411::GetPlanStatus(string workType, string workStaus)
{
	LOG log("MsgHCP411::GetPlanStatus", AUTO_CATCH_PID);
	string planStatus = "";
	try
	{
		if (workType == "1")
		{
			if (workStaus == "1")
			{
				planStatus = "2";//装车开始
			}
			if (workStaus == "F")
			{
				planStatus = "3";//装车结束
			}
		}

		if (workType == "2")
		{
			if (workStaus == "1")
			{
				planStatus == "4";//卸料开始
			}
			if (workStaus == "5")
			{
				planStatus == "5";//卸料结束
			}
		}
		

	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}

	return planStatus;
}
