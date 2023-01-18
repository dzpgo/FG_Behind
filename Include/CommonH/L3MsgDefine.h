#pragma once
namespace ZJCS
{
	namespace Common
	{
		//=======================电文名称列表====================
		const string strCSKH51 = "CSKH51";
		const string strCSKH52 = "CSKH52";
		const string strCSKH53 = "CSKH53";
		const string strCSKH54 = "CSKH54";
		const string strCSKH55 = "CSKH55";
		const string strCSKH56 = "CSKH56";
		const string strCSKH57 = "CSKH57";
		const string strCSKH58 = "CSKH58";

		const string strKHCS51 = "KHCS51";
		const string strKHCS52 = "KHCS52";
		const string strKHCS53 = "KHCS53";
		const string strKHCS54 = "KHCS54";
		const string strKHCS55 = "KHCS55";
		const string strKHCS56 = "KHCS56";
		const string strKHCS57 = "KHCS57";
		const string strKHCS58 = "KHCS58";
		const string strKHCS59 = "KHCS59";
		const string strKHCS60 = "KHCS60";
		const string strKHCS61 = "KHCS61";
		const string strKHCS62 = "KHCS62";
		const string strKHCS63 = "KHCS63";
		const string strKHCS65 = "KHCS65";
		const string strKHCS66 = "KHCS66";


		//-------------------------L2——>L3----------------
		const string CSKH51_NAME="InfoRequest";			//信息请求。请求装船情况
		const string CSKH52_NAME= "TL3CheckBank";		//对库电文
		const string CSKH53_NAME="MaterielInBankInfo";	//材料入库实绩
		const string CSKH54_NAME="MaterielOutBankInfo";	//材料出库实绩
		const string CSKH55_NAME="SiteChangedInfo";		//库位变更实绩
		const string CSKH56_NAME="IOFinish";				//发L3入/出库完成通知
		const string CSKH57_NAME="Ask4Site";				//发L3请求库位信息
		const string CSKH58_NAME ="CarLoadingInfo2L3";

		//-------------------------L3——>L2----------------
		const string KHCS51_NAME="InPlanInfo";		//入库计划信息
		const string KHCS52_NAME="InPlanDetail";	//入库材料信息
		const string KHCS53_NAME="OutPlanInfo";		//出库计划信息
		const string KHCS54_NAME="OutPlanDetail";	//出库材料信息
		const string KHCS55_NAME="CanclePlan";		//接L3计划撤销
		const string KHCS56_NAME="PlanCompleted";	//收L3计划完成通知
		const string KHCS57_NAME="RailWayOutMat";		//接L3铁路出厂组批材料信息
		const string KHCS58_NAME="FL3CheckBank";		//接L3对库电文
		const string KHCS59_NAME="SiteRecommend";		//接L3库位推荐信息
		const string KHCS60_NAME="RailWayCarriageList";	//接L3铁路库股道车皮清单
		const string KHCS61_NAME="CarLoadingInfo";	//框架材料信息
		const string KHCS62_NAME="TruckFramePosInfo";	//接L3框架卡车位信息
		const string KHCS63_NAME="TrainPreAssignInfo";		//接L3火车预配载信息
		const string KHCS64_NAME="LorryPreAssignInfo";	//接L3汽车预配载信息
		const string KHCS65_NAME = "AskOutMaterielOrder";	//要货顺序
		const string KHCS66_NAME = "UserInfo";				//用户信息

	}
}