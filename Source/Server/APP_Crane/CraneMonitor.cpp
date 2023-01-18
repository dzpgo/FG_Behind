#include "CraneMonitor.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;



CraneMonitor*  CraneMonitor::m_pCraneMonitor = NULL;

CraneMonitor::CraneMonitor() 
{
	
}


CraneMonitor :: ~CraneMonitor(void)
{
	
	delete m_pCraneMonitor;


}

 CraneMonitor* CraneMonitor::getInstance(void)
{
	if (m_pCraneMonitor == NULL)
	{
		m_pCraneMonitor = new CraneMonitor;
	}
	return m_pCraneMonitor;
}



//行车号
string CraneMonitor :: getCraneNO()
{
	return craneNO;
}
void CraneMonitor :: setCraneNO( string theVal)
{
	craneNO=theVal;
}

//initialise系列
void CraneMonitor :: initialise_MapCranePLCStatusPhototAlbum( vector<string> vectorCraneNOList)
{
		string functionName="CraneMonitor :: initialise_MapCranePLCStatusPhototAlbum()";
		LOG log(functionName, AUTO_CATCH_PID);


		try
		{
				for(vector<string>::size_type i=0;i<vectorCraneNOList.size();i++)
				{
					string craneNO=vectorCraneNOList[i];
					CranePLCStatusPhototAlbum cranePLCStatusPhototAlbum;
					cranePLCStatusPhototAlbum.setCraneNO(craneNO);
					mapCranePLCStatusPhototAlbum[craneNO]=cranePLCStatusPhototAlbum;
					log.Debug()<<"Create Crane Plc Status Photo Album in the Crane Monitor class the craneNO="<<craneNO<<endl;
					
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


void CraneMonitor :: inputPLCStatus(CranePLCStatusBase cranePLCStatusBase)
{
		string functionName="CraneMonitor :: inputPLCStatus()";
		LOG log(functionName, AUTO_CATCH_PID);


		try
		{
			map<string , CranePLCStatusPhototAlbum>::iterator theIterator;
			theIterator=mapCranePLCStatusPhototAlbum.find( cranePLCStatusBase.getCraneNO() );
			if(theIterator!=mapCranePLCStatusPhototAlbum.end())
			{
				theIterator->second.inputPLCStatus(cranePLCStatusBase);
			}
			else
			{
				log.Debug()<<"error Crane Monitor Class has not the photo Album of Crane PLC Status according to the CraneNO, theCraneNO="<<cranePLCStatusBase.getCraneNO()<<endl;
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


bool CraneMonitor :: getPLCStatus(CranePLCStatusBase& cranePLCStatusBase)
{
		string functionName="CraneMonitor :: getPLCStatus()";
		LOG log(functionName, AUTO_CATCH_PID);

		bool ret=false;

		try
		{
			map<string , CranePLCStatusPhototAlbum>::iterator theIterator;
			theIterator=mapCranePLCStatusPhototAlbum.find( craneNO );
			if(theIterator!=mapCranePLCStatusPhototAlbum.end())
			{
				cranePLCStatusBase=theIterator->second.getCranePLCStatusNew();
				if(cranePLCStatusBase.getXAct()>0 && cranePLCStatusBase.getXAct()<1000000)
				{
					ret=true;
				}
				else 
				{
					ret=false;
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
		return ret;
}


bool CraneMonitor :: getNeighborPLCStatus(string neightborCraneNO, CranePLCStatusBase& cranePLCStatusBase)
{
		string functionName="CraneMonitor :: getNeighborPLCStatus()";
		LOG log(functionName, AUTO_CATCH_PID);

		bool ret=false;

		try
		{
			map<string , CranePLCStatusPhototAlbum>::iterator theIterator;
			theIterator=mapCranePLCStatusPhototAlbum.find( neightborCraneNO );
			if(theIterator!=mapCranePLCStatusPhototAlbum.end())
			{
				cranePLCStatusBase=theIterator->second.getCranePLCStatusNew();
				//C612后库实际库区大小
				if(cranePLCStatusBase.getXAct()>0 && cranePLCStatusBase.getXAct()<450000  &&
					cranePLCStatusBase.getYAct()>0 && cranePLCStatusBase.getYAct()<33000  //&&	
					//cranePLCStatusBase.getZAct()>0 && cranePLCStatusBase.getZAct()<10000)	
					)
				{
					ret=true;
				}
				else 
				{
					ret=false;
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
		return ret;
}

void CraneMonitor :: inputPLCAlamrs(CranePLCAlarmBase theCranePLCAlarm)
{
		string functionName="CraneMonitor :: inputPLCAlamrs()";
		LOG log(functionName, AUTO_CATCH_PID);


		try
		{
			cranePLCAlarm=theCranePLCAlarm;
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



bool CraneMonitor :: getPLCAlamrs(CranePLCAlarmBase& theCranePLCAlarm)
{
		string functionName="CraneMonitor :: getPLCAlamrs()";
		LOG log(functionName, AUTO_CATCH_PID);

		bool ret=false;

		try
		{
			theCranePLCAlarm=cranePLCAlarm;
			
			ret=true;

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

void CraneMonitor :: DownLoadCranePLCOrder(CranePLCOrderBase cranePLCOrderBase)
{
		string functionName="CraneMonitor :: DownLoadCranePLCOrder()";
		LOG log(functionName, AUTO_CATCH_PID);


		try
		{

				MsgEUCR01::getInstance()->SendOutMessage(cranePLCOrderBase);

			
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



void CraneMonitor :: DownLoadCranePLCShortCmd(CranePLCShortCmdBase cranePLCShortCmdBase)
{
		string functionName="CraneMonitor :: DownLoadCranePLCShortCmd()";
		LOG log(functionName, AUTO_CATCH_PID);


		try
		{
				
				MsgEUCR02::getInstance()->SendOutMessage(cranePLCShortCmdBase);

			
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










