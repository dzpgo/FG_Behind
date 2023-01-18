#include "SafePLC4EAFYardBase.h"

#include "DataAccess.h"

using namespace Monitor;


//--------------------------------------------------安全PLC机组状态信号对应的系统内部tag点定义-------------------------------------
//修改TAG点名-----20221125
//1 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E1 = "AREA_SAFE_1";

//2 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E2 = "AREA_SAFE_2"; 

//3 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E3 = "AREA_SAFE_3"; 

//4
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E4 = "AREA_SAFE_4"; 

//5 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E5 = "AREA_SAFE_5"; 

//6 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E6 = "AREA_SAFE_6"; 

//7 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E7 = "AREA_SAFE_7"; 

//8 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E8 = "AREA_SAFE_8"; 

//9 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E9 = "AREA_SAFE_9"; 

//10 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E10 = "AREA_SAFE_10"; 

//11
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F1 = "AREA_SAFE_11";

//12 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F2 = "AREA_SAFE_12"; 

//13 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F3 = "AREA_SAFE_13"; 

//14
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F4 = "AREA_SAFE_141"; 

//15 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F5 = "AREA_SAFE_142"; 

//16 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F6 = "AREA_SAFE_15"; 

//17 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F7 = "AREA_SAFE_16"; 

//18 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F8 = "AREA_SAFE_17"; 

//19 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F9 = "AREA_SAFE_18"; 

//20 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F10 = "AREA_SAFE_19"; 

//21
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F11 = "AREA_SAFE_20"; 

//22 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F12 = "AREA_SAFE_21"; 

//23 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F13 = "AREA_SAFE_22"; 

//24 
const string SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F14 = "AREA_SAFE_23"; 



SafePLC4EAFYardBase :: SafePLC4EAFYardBase(void)
{
	initValues();
}



SafePLC4EAFYardBase :: ~SafePLC4EAFYardBase(void)
{
}

void SafePLC4EAFYardBase :: initValues()
{
	//--------------------------------------------------安全PLC机组状态信号对应的系统内部tag点定义-------------------------------------
	//--------------------------------------------------系统内部tag点主要供给画面使用，行车后台程序不使用------------------------------
	//1 
	E1Status = DB_STR_NULL;

	//2 
	E2Status = DB_STR_NULL; 

	//3 
	E3Status = DB_STR_NULL;

	//4 
	E4Status = DB_STR_NULL;

	//5 
	E5Status = DB_STR_NULL;

	//6 
	E6Status = DB_STR_NULL;

	//7 
	E7Status = DB_STR_NULL;

	//8 
	E8Status = DB_STR_NULL;

	//9
	E9Status = DB_STR_NULL;

	//10 
	E10Status = DB_STR_NULL;

	//11
	F1Status = DB_STR_NULL;

	//12
	F2Status = DB_STR_NULL;

	//13
	F3Status = DB_STR_NULL;

	//14
	F4Status = DB_STR_NULL;

	//15
	F5Status = DB_STR_NULL;

	//16
	F6Status = DB_STR_NULL;

	//17
	F7Status = DB_STR_NULL;

	//18
	F8Status = DB_STR_NULL;

	//19
	F9Status = DB_STR_NULL;

	//20
	F10Status = DB_STR_NULL;

	//21
	F11Status = DB_STR_NULL;

	//22
	F12Status = DB_STR_NULL;

	//23
	F13Status = DB_STR_NULL;

	//24
	F14Status = DB_STR_NULL;


}

//1 
 string SafePLC4EAFYardBase::getE1Status()
{
	return E1Status;
}
void SafePLC4EAFYardBase::setE1Status(string theVal)
{
	E1Status=theVal;
}

//2
string SafePLC4EAFYardBase::getE2Status()
{
	return E2Status;
}
void SafePLC4EAFYardBase::setE2Status(string theVal)
{
	E2Status=theVal;
}

//3
string SafePLC4EAFYardBase::getE3Status()
{
	return E3Status;
}
void SafePLC4EAFYardBase::setE3Status(string theVal)
{
	E3Status=theVal;
}

//4
string SafePLC4EAFYardBase::getE4Status()
{
	return E4Status;
}
void SafePLC4EAFYardBase::setE4Status(string theVal)
{
	E4Status=theVal;
}

//5
string SafePLC4EAFYardBase::getE5Status()
{
	return E5Status;
}
void SafePLC4EAFYardBase::setE5Status(string theVal)
{
	E5Status=theVal;
}

//6
string SafePLC4EAFYardBase::getE6Status()
{
	return E6Status;
}
void SafePLC4EAFYardBase::setE6Status(string theVal)
{
	E6Status=theVal;
}

//7
string SafePLC4EAFYardBase::getE7Status()
{
	return E7Status;
}
void SafePLC4EAFYardBase::setE7Status(string theVal)
{
	E7Status=theVal;
}

//8
string SafePLC4EAFYardBase::getE8Status()
{
	return E8Status;
}
void SafePLC4EAFYardBase::setE8Status(string theVal)
{
	E8Status=theVal;
}

//9
string SafePLC4EAFYardBase::getE9Status()
{
	return E9Status;
}
void SafePLC4EAFYardBase::setE9Status(string theVal)
{
	E9Status=theVal;
}

//10
string SafePLC4EAFYardBase::getE10Status()
{
	return E10Status;
}
void SafePLC4EAFYardBase::setE10Status(string theVal)
{
	E10Status=theVal;
}

//11
string SafePLC4EAFYardBase::getF1Status()
{
	return F1Status;
}
void SafePLC4EAFYardBase::setF1Status(string theVal)
{
	F1Status=theVal;
}

//12
string SafePLC4EAFYardBase::getF2Status()
{
	return F2Status;
}
void SafePLC4EAFYardBase::setF2Status(string theVal)
{
	F2Status=theVal;
}

//13
string SafePLC4EAFYardBase::getF3Status()
{
	return F3Status;
}
void SafePLC4EAFYardBase::setF3Status(string theVal)
{
	F3Status=theVal;
}

//14
string SafePLC4EAFYardBase::getF4Status()
{
	return F4Status;
}
void SafePLC4EAFYardBase::setF4Status(string theVal)
{
	F4Status=theVal;
}

//15
string SafePLC4EAFYardBase::getF5Status()
{
	return F5Status;
}
void SafePLC4EAFYardBase::setF5Status(string theVal)
{
	F5Status=theVal;
}

//16
string SafePLC4EAFYardBase::getF6Status()
{
	return F6Status;
}
void SafePLC4EAFYardBase::setF6Status(string theVal)
{
	F6Status=theVal;
}

//17
string SafePLC4EAFYardBase::getF7Status()
{
	return F7Status;
}
void SafePLC4EAFYardBase::setF7Status(string theVal)
{
	F7Status=theVal;
}

//18
string SafePLC4EAFYardBase::getF8Status()
{
	return F8Status;
}
void SafePLC4EAFYardBase::setF8Status(string theVal)
{
	F8Status=theVal;
}

//19
string SafePLC4EAFYardBase::getF9Status()
{
	return F9Status;
}
void SafePLC4EAFYardBase::setF9Status(string theVal)
{
	F9Status=theVal;
}

//20
string SafePLC4EAFYardBase::getF10Status()
{
	return F10Status;
}
void SafePLC4EAFYardBase::setF10Status(string theVal)
{
	F10Status=theVal;
}

//21
string SafePLC4EAFYardBase::getF11Status()
{
	return F11Status;
}
void SafePLC4EAFYardBase::setF11Status(string theVal)
{
	F11Status=theVal;
}

//22
string SafePLC4EAFYardBase::getF12Status()
{
	return F12Status;
}
void SafePLC4EAFYardBase::setF12Status(string theVal)
{
	F12Status=theVal;
}

//23
string SafePLC4EAFYardBase::getF13Status()
{
	return F13Status;
}
void SafePLC4EAFYardBase::setF13Status(string theVal)
{
	F13Status=theVal;
}

//24
string SafePLC4EAFYardBase::getF14Status()
{
	return F14Status;
}
void SafePLC4EAFYardBase::setF14Status(string theVal)
{
	F14Status=theVal;
}



void SafePLC4EAFYardBase :: wirteValues2TagSystem()
{
	string functionName="SafePLC4EAFYardBase :: wirteValues2TagSystem()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		TAGVALUEMAP Tags;
		string TagName="";
		string TagValue="";

		//1 
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E1;
		TagValue=E1Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//2
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E2;
		TagValue=E2Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//3
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E3;
		TagValue=E3Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//4
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E4;
		TagValue=E4Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//5
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E5;
		TagValue=E5Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//6
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E6;
		TagValue=E6Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//7
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E7;
		TagValue=E7Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//8
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E8;
		TagValue=E8Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//9
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E9;
		TagValue=E9Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//10
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_E10;
		TagValue=E10Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//11
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F1;
		TagValue=F1Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//12
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F2;
		TagValue=F2Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//13
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F3;
		TagValue=F3Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//14
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F4;
		TagValue=F4Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//15
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F5;
		TagValue=F5Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//16
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F6;
		TagValue=F6Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//17
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F7;
		TagValue=F7Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//18
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F8;
		TagValue=F8Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//19
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F9;
		TagValue=F9Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//20
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F10;
		TagValue=F10Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//21
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F11;
		TagValue=F11Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//22
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F12;
		TagValue=F12Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//23
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F13;
		TagValue=F13Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//24
		TagName=SafePLC4EAFYardBase::ADRESS_SAFE_PLC_DL_YARD_F14;
		TagValue=F14Status;
		Tags.insert(map<string,string>::value_type(TagName,TagValue));

		//tag点写入系统
		TAGVALUEMAP TagTimeStamp;
		Tag::GetInst().MDPut(TagTimeStamp,Tags);	

		log.Debug()<<"SAFEPLC-ProductLine tags written to tag system .........OK"<<endl;
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

