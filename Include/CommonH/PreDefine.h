#pragma once
#include "DataStructure.h"
#include "L3MsgDefine.h"
#include "SQLCmd.h"

#ifdef __GNUC__
#define PLUGINCORE_EXPORTS __attribute__((dllexport))
#else
#define PLUGINCORE_EXPORTS __declspec(dllexport)
#endif

#ifdef __GNUC__
#define PLUGINCORE_IMPORTS __attribute__((dllimport))
#else
#define PLUGINCORE_IMPORTS __declspec(dllimport)
#endif

//#ifdef __GNUC__
//#define byte unsigned char
//#endif

namespace ZJCS
{
	namespace Common
	{
		const int		PT_DB_SUCCESS = 0;
		const int		PT_DB_FAILED = -1;
		const int		DB_CONNECTSIZE = 4;	
		const string	PT_DATAACCESS_CONFIG_FILE = "PTModule.config";			//config file string
		const string	PT_DATAACCESS_CONNECTION_PROPERTY = "DBAccess.ConnectionString";  //connection property string in config file 
		const string	PT_CCEVENT_STARTINTERVAL = "PT.CCStartInterval";  //connection property string in config file
		const int		PT_PRO_SUCCESS = 0;
		const int		PT_PRO_FAILED	= -1;

		const int		SPR_DB_SUCCESS = 0;
		const int		SPR_DB_FAILED = -1;

		const string	SPR_DATAACCESS_CONFIG_FILE = "SPRModule.config";			//config file string
		const string	SPR_DATAACCESS_CONNECTION_PROPERTY = "DBAccess.ConnectionString";  //connection property string in config file 
		const string	SPR_CCEVENT_STARTINTERVAL = "SPR.CCStartInterval";  //connection property string in config file
		const int		SPR_PRO_SUCCESS = 0;
		const int		SPR_PRO_FAILED	= -1;

		const string UnKnowSite = "00000000";

		const string UnCompleteStatus = "1";

		//=======================常见数据项名=======================
		const string ciMACHINE_ID = "MACHINE_ID";
		const string ciSEND_TIME = "SEND_TIME";
		const string ciSHIFTNO = "SHIFTNO";
		const string ciSHIFTID = "SHIFTID";
		const string ciINSTORE_ID = "INSTORE_ID";
		const string ciREC_CREATOR = "REC_CREATOR";
		const string ciMACHINE_NO = "MACHINE_NO";
		const string ciSLING_NO3 = "SLING_NO3";
		const string ciSLING_NO4 = "SLING_NO4";
		const string ciSLING_NO = "SLING_NO";
		const string ciFRAME_NO = "FRAME_NO";
		const string ciFINISH_TIME = "FINISH_TIME";
		const string ciSYS_CODE = "SYSTEM_CODE";
		const string ciUL_FLAG = "UL_FLAG";
		const string ciCOUNT = "COUNT";
		const string ciMANUFACT_UNIT_CODE = "MANUFACT_UNIT_CODE";
		const string ciPLAN_NO = "PLAN_NO";
		const string ciMAT_NO = "MAT_NO";
		const string ciTIME = "TIME";
		const string ciQUALITY = "QUALITY";
		const string ciROW_NO = "ROW_NO";
		const string ciCOL_NO = "COL_NO";
		const string ciLAYER_NO = "LAYER_NO";
		const string ciLOCATION_X = "LOCATION_X";
		const string ciLOCATION_Y = "LOCATION_Y";
		const string ciLOCATION_Z = "LOCATION_Z";
		const string ciParking_NO = "Parking_No";
		const string ciAREA_NO = "AREA_NO";
		const string ciSTORE_PLACE = "STORE_PLACE";
		const string ciPONCHOS1 = "PONCHOS1";
		const string ciPONCHOS2 = "PONCHOS2";
		const string ciFLAG = "FLAG";
		const string ciZZFLAG = "ZZFLAG";
		const string ciPLACE_NO = "PLACE_NO";
		const string ci = "";

		const string ciCrane1= "FT1001";
		const string ciCrane2= "FT1002";
		const string ciCrane3= "FT1003";
		const string ciCrane4= "FT2004";
		const string ciCrane5= "FT2005";
		const string ciCrane6= "FT2006";
		const string ciCrane7= "FT3007";
		const string ciCrane8= "FT3008";


		//=======================Tag名称列表====================
		const string cTag_InfoRequest = "TrigInfoRequist";				//电文名CSKH51

		const string cTag_IOFinish = "TrigIOFinish";				//电文名CSKH56  格式：类型|车号|完成时间
				
		const string cTag_Ask4Site = "TrigAsk4Site";				//电文名CSKH51
		const string cTag_SiteChange = "TrigSiteChange";			//电文名CSKH55	格式:库别|位置|变更时间|材料号|层


		const string cTag_Salb_in = "SLAB_IN";
		const string cTag_Slab_out = "SLAB_OUT";
		const string cTag_Slab_inventory = "CL_INVENTORY";
		const string cTag_Crane_Plan = "CRANE_PLAN";
		const string cTag_presend = "PRESEND";

		//=======================数据库表名====================
		const string ctnSlab_Out_PreLoad = "Slab_Out_PreLoad";
	}
}