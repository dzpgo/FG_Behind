#include "CranePLCAlarmBase.h"

using namespace Monitor;
using namespace CLTS;


CranePLCAlarmBase :: CranePLCAlarmBase(void)
{

	initValues();
}



CranePLCAlarmBase :: ~CranePLCAlarmBase(void)
{
	


}

void CranePLCAlarmBase :: initValues()
{
	//1 craneNO
	craneNO=DB_STR_NULL;

	//2 encoderVal
	encoderVal=DB_STR_NULL;

	//3 ErrorNum==0
	errorNum=0;

	//4 ErrorList
	errorList=DB_STR_NULL;

	//5timeReceive
	timeReceive=DB_STR_NULL;

}

//1 craneNO
string CranePLCAlarmBase :: getCraneNO()
{
	return craneNO;
}
void CranePLCAlarmBase :: setCraneNO(string theVal)
{
	craneNO=theVal;
}

//2 EncoderVal
string CranePLCAlarmBase :: getEncoderVal()
{
	return encoderVal;
}
void CranePLCAlarmBase :: setEncodeVal(string theVal)
{
	encoderVal=theVal;
}

//3 errorNum
long CranePLCAlarmBase :: getErrorNum()
{
	return errorNum;
}
void CranePLCAlarmBase :: setErrorNum(long theVal)
{
	errorNum=theVal;
}

//4 ErrorList
string CranePLCAlarmBase :: getErrorList()
{
	return errorList;
}
void CranePLCAlarmBase :: setErrorList(string theVal)
{
	errorList=theVal;
}


//5 timeReceive
string CranePLCAlarmBase::getTimeReceive()
{
	return timeReceive;
}
void CranePLCAlarmBase::setTimeReceive(string theVal)
{
	timeReceive=theVal;
}

void CranePLCAlarmBase :: logOutValues()
{
	string functionName="CranePLCAlarmBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class CranePLCAlarmBase--------------------------------------"<<endl;
	//1
	log.Debug()<<"\t craneNO="<<craneNO;
	//2
	log.Debug()<<"\t encoderVal="<<encoderVal;
	//3
	log.Debug()<<"\t errorNum="<<errorNum<<endl;
	//4
	log.Debug()<<"\t errorList="<<errorList<<endl;;
	//5
	log.Debug()<<"\t timeReceive="<<timeReceive<<endl;
	

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;

	
}

void CranePLCAlarmBase :: wirteValues2TagSystem()
{
	string functionName="CranePLCAlarmBase :: wirteValues2TagSystem()";

	string adressHead=craneNO+"_";

	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

					//wirte to tag system

				TAGVALUEMAP Tags;
				string TagName="";
				string TagValue="";
				
				//2准备好
				TagName=adressHead+"ALARM_CURRENT";
				if(errorNum==0)
				{
					TagValue=" ";
				}
				else
				{
					TagValue=getErrorList();
				}
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );

				//tag点写入系统
				TAGVALUEMAP TagTimeStamp;
				Tag::GetInst().MDPut(TagTimeStamp,Tags);	

				log.Debug()<<"ALARM_CURRENT  written to tag system .........OK"<<endl;


		}
		catch(iDA::Exception &x)
		{
			try
			{
				CDataAccess::GetInstance()->m_DBCon.Rollback();
			}
			catch(iDA::Exception &)
			{
			}

			string msg = functionName +"   error:"+ x.ErrMsg();
			log.Debug()<<msg<<endl;
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


