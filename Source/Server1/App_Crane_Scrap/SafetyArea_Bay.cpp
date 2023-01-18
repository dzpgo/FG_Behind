#include "SafetyArea_Bay.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;


const string SafetyArea_Bay::RIGHT="R";
const string SafetyArea_Bay::LEFT="L";

const string SafetyArea_Bay::TREND_INC="INC";
const string SafetyArea_Bay::TREND_DES="DES";

//单例函数指针
SafetyArea_Bay*  SafetyArea_Bay::m_pSafetyArea_Bay = NULL;

//构造行数
SafetyArea_Bay::SafetyArea_Bay() 
{
	
}

//析构函数
SafetyArea_Bay :: ~SafetyArea_Bay(void)
{
	
	delete m_pSafetyArea_Bay;


}

//获得指针的方法
 SafetyArea_Bay* SafetyArea_Bay::getInstance(void)
{
	if (m_pSafetyArea_Bay == NULL)
	{
		m_pSafetyArea_Bay = new SafetyArea_Bay;
	}
	return m_pSafetyArea_Bay;
}

 //1 xMinInBay
 long SafetyArea_Bay::getXMinInBay()
 {
	 return xMinInBay;
 }
 void SafetyArea_Bay::setXMinInBay(long theVal)
 {
	xMinInBay=theVal;
 }

//2 xMaxInBay
 long SafetyArea_Bay::getXMaxInBay()
 {
	 return xMaxInBay;
 }
 void SafetyArea_Bay::setXMaxInBay(long theVal)
 {
	xMaxInBay=theVal;
 }

  //3 yMinInBay
 long SafetyArea_Bay::getYMinInBay()
 {
	 return yMinInBay;
 }
 void SafetyArea_Bay::setYMinInBay(long theVal)
 {
	yMinInBay=theVal;
 }

//2 yMaxInBay
 long SafetyArea_Bay::getYMaxInBay()
 {
	 return yMaxInBay;
 }
 void SafetyArea_Bay::setYMaxInBay(long theVal)
 {
	yMaxInBay=theVal;
 }

//读取XML文件的方法
bool SafetyArea_Bay :: ReadFromXML(string theFilePath)
{
		string functionName="SafetyArea_Bay :: ReadFromXML()";
		LOG log(functionName, AUTO_CATCH_PID);

		bool ret=false;
		try
		{
			
			const char* filepath = theFilePath.c_str();//"C:\\iPlature\\conf\\APP_Crane\\Z33_RiverBank_Config.xml";  
			TiXmlDocument doc(filepath);
			bool loadOkay = doc.LoadFile();  
			if (!loadOkay) 
			{      
				log.Info()<<"Could not load the config XML file.............................."<<doc.ErrorDesc()<<endl;
			}  
			else
			{
				log.Info()<<"XML file has been loaded"<<endl;
			}

			TiXmlElement* root = doc.RootElement();  

			{
			TiXmlElement* subRoot_BayBaseConfig=root->FirstChildElement("BayBaseConfig");
			string strValue;
			//1 XMinInBay
			TiXmlNode* child=subRoot_BayBaseConfig->FirstChild("XMinInBay");
			strValue = child->ToElement()->GetText();  
			log.Info()<<"XMinInBay="<<strValue<<endl;  

			setXMinInBay(StringHelper::ToNumber<long>(strValue));


			//2 XMaxInBay
			child=subRoot_BayBaseConfig->FirstChild("XMaxInBay");
			strValue = child->ToElement()->GetText();  
			log.Info()<<"XMaxInBay="<<strValue<<endl;  

			setXMaxInBay(StringHelper::ToNumber<long>(strValue));


			//3 YMinInBay
			child=subRoot_BayBaseConfig->FirstChild("YMinInBay");
			strValue = child->ToElement()->GetText();  
			log.Info()<<"YMinInBay="<<strValue<<endl;  

			setYMinInBay(StringHelper::ToNumber<long>(strValue));

			//4 YMaxInBay
			child=subRoot_BayBaseConfig->FirstChild("YMaxInBay");
			strValue = child->ToElement()->GetText();  
			log.Info()<<"YMaxInBay="<<strValue<<endl; 

			setYMaxInBay(StringHelper::ToNumber<long>(strValue));
			}

			//read the config of SafetyArea-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


			TiXmlElement* subRoot_RiverBankConfig=root->FirstChildElement("SafetyAreaConfig");
			
			for( TiXmlNode*  item = subRoot_RiverBankConfig->FirstChild( "Area" );    item;           item = item->NextSibling( "Area" ) )
			{  
					log.Debug()<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

					SafteyAreaBase safteyArea_RiverBank;

					string strValue;

					//1 name
					TiXmlNode* child = item->FirstChild("Name");
					strValue = child->ToElement()->GetText();  
					StringHelper::Trim(strValue);
					log.Info()<<"Name="<<strValue<<endl;  
					safteyArea_RiverBank.setName(strValue);

					//2 XMin
					child = item->FirstChild("XMin");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"XMin="<<strValue<<endl;  
					safteyArea_RiverBank.setXMin( StringHelper::ToNumber<long>(strValue) );

					//3 XMax
					child = item->FirstChild("XMax");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"XMax="<<strValue<<endl;  
					safteyArea_RiverBank.setXMax( StringHelper::ToNumber<long>(strValue) );

					//4 YMin
					child = item->FirstChild("YMin");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"YMin="<<strValue<<endl;  
					safteyArea_RiverBank.setYMin( StringHelper::ToNumber<long>(strValue) );

					//5 XMax
					child = item->FirstChild("YMax");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"YMax="<<strValue<<endl;  
					safteyArea_RiverBank.setYMax( StringHelper::ToNumber<long>(strValue) );

					//6 AlwaysForbid
					child = item->FirstChild("AlwaysForbid");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"AlwaysForbid="<<strValue<<endl;  
					safteyArea_RiverBank.setAlwaysForbid( StringHelper::ToNumber<long>(strValue) );

					//7 SafeTag
					child = item->FirstChild("SafeTag");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"SafeTag="<<strValue<<endl;  
					safteyArea_RiverBank.setSafeTag( strValue );

					//8 OnBordY
					child = item->FirstChild("OnBordY");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"OnBordY="<<strValue<<endl;  
					safteyArea_RiverBank.setOnBordY( StringHelper::ToNumber<long>(strValue) );

					//9 RecommendArea1
					child = item->FirstChild("RecommendArea1");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"RecommendArea1="<<strValue<<endl;  
					safteyArea_RiverBank.setRecommendArea1( strValue );

					//10 RecommendArea2
					child = item->FirstChild("RecommendArea2");
					strValue = child->ToElement()->GetText();  
					log.Info()<<"RecommendArea2="<<strValue<<endl;  
					safteyArea_RiverBank.setRecommendArea2( strValue );


					//将riverBank定义压入自己的数据对象中
					InputSafteyArea( safteyArea_RiverBank );

					

			}

			

			//打印自身对象的值
			logOutValues();



		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName +"   error:"+ errorMessage;
			ret=false;
			log.Debug()<<msg<<endl;
		}
		catch (...)
		{
			string msg = functionName +"   error:";
			log.Debug()<<msg<<endl;
			ret=false;
		}

		return ret;
}


//通过区域的名称获得区域的对象
bool SafetyArea_Bay :: getAreaByName(string theAreaName, SafteyAreaBase& safteyAreaBase)
{
		string functionName="SafetyArea_Bay :: getAreaByName()";
		LOG log(functionName, AUTO_CATCH_PID);
		bool finded=false;
		
		try
		{
			map<string , SafteyAreaBase>::iterator theIterator;
			theIterator=mapSafteyAreas.find( theAreaName );
			if(theIterator!=mapSafteyAreas.end())
			{
				safteyAreaBase=theIterator->second;
				finded=true;
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

		return finded;
}

//将XML中读取到的区域数据保存到本身对象的方法
void SafetyArea_Bay :: InputSafteyArea(SafteyAreaBase  safteyAreaBase)
{
		string functionName="SafetyArea_Bay :: InputSafteyArea()";
		LOG log(functionName, AUTO_CATCH_PID);


		try
		{
			mapSafteyAreas[safteyAreaBase.getName()]=safteyAreaBase;
			vectorSafteyAreas.push_back(safteyAreaBase);
			
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

void SafetyArea_Bay :: InputTagNameSafeDoor()
{
	string functionName="SafetyArea_Bay :: InputTagNameSafeDoor()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_1_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_2_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_3_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_4_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_5_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_6_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_7_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_8_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_9_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_10_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_11_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_12_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_13_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_14_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_15_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_16_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_17_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_18_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_19_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_20_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_21_OPEN_CLOSE");
		arryTagNameSafeDoor.push_back("SAFE_C2A_DO_22_OPEN_CLOSE");

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

void SafetyArea_Bay :: InputAreaXMinXax(map<string,SafteyAreaBase> mapSafteyAreas)
{
	string functionName="SafetyArea_Bay :: InputAreaXMinXax()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		int nCount = 0;
		map<string,SafteyAreaBase>::iterator iter;
		for (iter = mapSafteyAreas.begin(); iter != mapSafteyAreas.end(); iter ++)
		{
			if (iter->first == "C2A-A1")
			{
				mapAreaXMinMax["A1_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A1_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["A1_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["A1_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"A1_X_MIN = "<<mapAreaXMinMax["A1_X_MIN"]<<endl;
				log.Info()<<"A1_X_MAX = "<<mapAreaXMinMax["A1_X_MAX"]<<endl;
				log.Info()<<"A1_Y_MIN = "<<mapAreaXMinMax["A1_Y_MIN"]<<endl;
				log.Info()<<"A1_Y_MAX = "<<mapAreaXMinMax["A1_Y_MAX"]<<endl;
				nCount ++;
			}
			if (iter->first == "C2A-A2")
			{
				mapAreaXMinMax["A2_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A2_X_MAX"] = iter->second.getXMax();
				log.Info()<<"A2_X_MIN = "<<mapAreaXMinMax["A2_X_MIN"]<<endl;
				log.Info()<<"A2_X_MAX = "<<mapAreaXMinMax["A2_X_MAX"]<<endl;
				nCount ++;
			}
			if (iter->first == "C2A-A3")
			{
				mapAreaXMinMax["A3_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A3_X_MAX"] = iter->second.getXMax();
				log.Info()<<"A3_X_MIN = "<<mapAreaXMinMax["A3_X_MIN"]<<endl;
				log.Info()<<"A3_X_MAX = "<<mapAreaXMinMax["A3_X_MAX"]<<endl;
				nCount ++;
			}
			if (iter->first == "C2A-A4")
			{
				mapAreaXMinMax["A4_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A4_X_MAX"] = iter->second.getXMax();
				log.Info()<<"A4_X_MIN = "<<mapAreaXMinMax["A4_X_MIN"]<<endl;
				log.Info()<<"A4_X_MAX = "<<mapAreaXMinMax["A4_X_MAX"]<<endl;
				nCount ++;
			}
			if (iter->first == "C2A-A5")
			{
				mapAreaXMinMax["A5_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A5_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["A5_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["A5_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"A5_X_MIN = "<<mapAreaXMinMax["A5_X_MIN"]<<endl;
				log.Info()<<"A5_X_MAX = "<<mapAreaXMinMax["A5_X_MAX"]<<endl;
				log.Info()<<"A5_Y_MIN = "<<mapAreaXMinMax["A5_Y_MIN"]<<endl;
				log.Info()<<"A5_Y_MAX = "<<mapAreaXMinMax["A5_Y_MAX"]<<endl;
				nCount ++;
			}
			if (iter->first == "C2A-A6")
			{
				mapAreaXMinMax["A6_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A6_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["A6_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["A6_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"A6_X_MIN = "<<mapAreaXMinMax["A6_X_MIN"]<<endl;
				log.Info()<<"A6_X_MAX = "<<mapAreaXMinMax["A6_X_MAX"]<<endl;
				log.Info()<<"A6_Y_MIN = "<<mapAreaXMinMax["A6_Y_MIN"]<<endl;
				log.Info()<<"A6_Y_MAX = "<<mapAreaXMinMax["A6_Y_MAX"]<<endl;

				nCount ++;
			}
			if (iter->first == "C2A-A7")
			{
				mapAreaXMinMax["A7_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A7_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["A7_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["A7_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"A7_X_MIN = "<<mapAreaXMinMax["A7_X_MIN"]<<endl;
				log.Info()<<"A7_X_MAX = "<<mapAreaXMinMax["A7_X_MAX"]<<endl;
				log.Info()<<"A7_Y_MIN = "<<mapAreaXMinMax["A7_Y_MIN"]<<endl;
				log.Info()<<"A7_Y_MAX = "<<mapAreaXMinMax["A7_Y_MAX"]<<endl;
				nCount ++;
			}
			if (iter->first == "C2A-A8")
			{
				mapAreaXMinMax["A8_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A8_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["A8_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["A8_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"A8_X_MIN = "<<mapAreaXMinMax["A8_X_MIN"]<<endl;
				log.Info()<<"A8_X_MAX = "<<mapAreaXMinMax["A8_X_MAX"]<<endl;
				log.Info()<<"A8_Y_MIN = "<<mapAreaXMinMax["A8_Y_MIN"]<<endl;
				log.Info()<<"A8_Y_MAX = "<<mapAreaXMinMax["A8_Y_MAX"]<<endl;
				nCount ++;
			}
			if (iter->first == "C2A-A10")
			{
				mapAreaXMinMax["A10_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A10_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["A10_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["A10_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"A10_X_MIN = "<<mapAreaXMinMax["A10_X_MIN"]<<endl;
				log.Info()<<"A10_X_MAX = "<<mapAreaXMinMax["A10_X_MAX"]<<endl;
				log.Info()<<"A10_Y_MIN = "<<mapAreaXMinMax["A10_Y_MIN"]<<endl;
				log.Info()<<"A10_Y_MAX = "<<mapAreaXMinMax["A10_Y_MAX"]<<endl;
				nCount ++;
			}
			//20191128 zhangyuhong add
			if (iter->first == "C2A-A12")
			{
				mapAreaXMinMax["A12_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["A12_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["A12_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["A12_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"A12_X_MIN = "<<mapAreaXMinMax["A12_X_MIN"]<<endl;
				log.Info()<<"A12_X_MAX = "<<mapAreaXMinMax["A12_X_MAX"]<<endl;
				log.Info()<<"A12_Y_MIN = "<<mapAreaXMinMax["A12_Y_MIN"]<<endl;
				log.Info()<<"A12_Y_MAX = "<<mapAreaXMinMax["A12_Y_MAX"]<<endl;
				nCount ++;
			}

			//20190909 zhangyuyhong add
			//采集  SAFE_EQP_09  的数据   pa2离线包装区
			if (iter->first == "SAFE_EQP_09")
			{
				mapAreaXMinMax["SAFE_EQP_09_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["SAFE_EQP_09_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["SAFE_EQP_09_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["SAFE_EQP_09_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"SAFE_EQP_09_X_MIN = "<<mapAreaXMinMax["SAFE_EQP_09_X_MIN"]<<endl;
				log.Info()<<"SAFE_EQP_09_X_MAX = "<<mapAreaXMinMax["SAFE_EQP_09_X_MAX"]<<endl;
				log.Info()<<"SAFE_EQP_09_Y_MIN = "<<mapAreaXMinMax["SAFE_EQP_09_Y_MIN"]<<endl;
				log.Info()<<"SAFE_EQP_09_Y_MAX = "<<mapAreaXMinMax["SAFE_EQP_09_Y_MAX"]<<endl;
				nCount ++;
			}


			//20190909 zhangyuyhong add
			//采集  SAFE_EQP_12  的数据   C176离线拆包区
			if (iter->first == "SAFE_EQP_12")
			{
				mapAreaXMinMax["SAFE_EQP_12_X_MIN"] = iter->second.getXMin();
				mapAreaXMinMax["SAFE_EQP_12_X_MAX"] = iter->second.getXMax();
				mapAreaXMinMax["SAFE_EQP_12_Y_MIN"] = iter->second.getYMin();
				mapAreaXMinMax["SAFE_EQP_12_Y_MAX"] = iter->second.getYMax();
				log.Info()<<"SAFE_EQP_12_X_MIN = "<<mapAreaXMinMax["SAFE_EQP_12_X_MIN"]<<endl;
				log.Info()<<"SAFE_EQP_12_X_MAX = "<<mapAreaXMinMax["SAFE_EQP_12_X_MAX"]<<endl;
				log.Info()<<"SAFE_EQP_12_Y_MIN = "<<mapAreaXMinMax["SAFE_EQP_12_Y_MIN"]<<endl;
				log.Info()<<"SAFE_EQP_12_Y_MAX = "<<mapAreaXMinMax["SAFE_EQP_12_Y_MAX"]<<endl;
				nCount ++;
			}


			/*if (nCount == 9)
			{
				log.Info()<<"所有红区的X_MIN和X_MAX已经采集完毕......"<<endl;
				break;
			}*/
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


void SafetyArea_Bay :: InputPA2SPXPT()
{
	string functionName="SafetyArea_Bay :: InputPA2SPXPT()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//mapPA02_SP_MIN_X_PT["X"] = mapAreaXMinMax["A2_X_MIN"] - 100;
		mapPA02_SP_MIN_X_PT["X"] = 85224;//PA2 的16#位大车坐标 
		mapPA02_SP_MIN_X_PT["Y"] = 3600;

		//mapPA02_SP_MAX_X_PT["X"] = mapAreaXMinMax["A4_X_MAX"] + 100;
		mapPA02_SP_MAX_X_PT["X"] = 138000;//175出口下料位大车坐标 - 100
		mapPA02_SP_MAX_X_PT["Y"] = 3600;

		log.Info()<<"mapPA2SpMinXPT的 X ="<<mapPA02_SP_MIN_X_PT["X"]<<",   Y = "<<mapPA02_SP_MIN_X_PT["Y"]<<endl;
		log.Info()<<"mapPA2SpMaxXPT的 X ="<<mapPA02_SP_MAX_X_PT["X"]<<",   Y = "<<mapPA02_SP_MAX_X_PT["Y"]<<endl;

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



//打印本对象中的数据
void SafetyArea_Bay :: logOutValues()
{
		string functionName="SafetyArea_Bay :: logOutValues()";
		LOG log(functionName, AUTO_CATCH_PID);
		try
		{


				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
				log.Info()<<"                                                                      print out SafteyAreaBase  in vector                                                                                                         "<<endl;
				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

				log.Debug()<<"xMinInBay="<<xMinInBay<<endl;
				log.Debug()<<"xMaxInBay="<<xMaxInBay<<endl;
				log.Debug()<<"yMinInBay="<<yMinInBay<<endl;
				log.Debug()<<"yMaxInBay="<<yMaxInBay<<endl;


				for(vector<SafteyAreaBase>::size_type i=0;i<vectorSafteyAreas.size();i++)
				{
					vectorSafteyAreas[i].logOutValues();
				}

			


				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
				log.Info()<<"                                                                      print out SafteyAreaBase in MAP                                                                                                            "<<endl;
				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

				for ( map<string,SafteyAreaBase >::iterator m_Iter = mapSafteyAreas.begin( ); m_Iter != mapSafteyAreas.end( ); m_Iter++ )
				{
				   m_Iter->second.logOutValues();
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





bool SafetyArea_Bay :: isPointInAnyReadArea(long x, long y, SafteyAreaBase& safteyAreaBase)
{
		string functionName="SafetyArea_Bay :: isPointInAnyReadArea()";
		LOG log(functionName, AUTO_CATCH_PID);
		
		bool isInReadArea=false;

		try
		{
			for(vector<SafteyAreaBase>::size_type i=0;i<vectorSafteyAreas.size();i++)
			{
				if( x>=vectorSafteyAreas[i].getXMin()  && x<vectorSafteyAreas[i].getXMax() &&
					y>=vectorSafteyAreas[i].getYMin()  && y<vectorSafteyAreas[i].getYMax() )
					{
							if(vectorSafteyAreas[i].isRead()==true)
							{
								safteyAreaBase= vectorSafteyAreas[i];
								isInReadArea=true;
								return isInReadArea;
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
		return isInReadArea;
}

//20191216 
bool SafetyArea_Bay :: isPointInAnyReadAreaNew(long x, long y)
{
	string functionName="SafetyArea_Bay :: isPointInAnyReadArea()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool isInReadArea=false;

	try
	{
		for(vector<SafteyAreaBase>::size_type i=0;i<vectorSafteyAreas.size();i++)
		{
			if( x>=vectorSafteyAreas[i].getXMin()  && x<vectorSafteyAreas[i].getXMax() &&
				y>=vectorSafteyAreas[i].getYMin()  && y<vectorSafteyAreas[i].getYMax() )
			{
				if(vectorSafteyAreas[i].isRead()==true)
				{
					//safteyAreaBase= vectorSafteyAreas[i];
					isInReadArea=true;
					return isInReadArea;
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
	return isInReadArea;
}






void SafetyArea_Bay :: sortTwoNum(long numberA,long numberB,long& theMin, long& theMax)
{
		string functionName="SafetyArea_Bay :: sortTwoNum()";
		LOG log(functionName, AUTO_CATCH_PID);
		


		try
		{
			if(numberA>numberB)
			{
				theMax=numberA;
				theMin=numberB;
			}
			else
			{
				theMax=numberB;
				theMin=numberA;
			}
			//log.Debug()<<"numberA="<<numberA<<"\t  numberB="<<numberB<<"\t  xMin="<<theMin<<"\t  xMax="<<theMax<<endl;

		
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





//按照起点坐标和终点坐标，寻找进入推荐区域的坐标位置，当前车在区域外，进入位置X取运动方向上第一条边的X ， Y去进入Y，并且对X进行补偿，要求侵入该区域
//                                                                                                                     如果车在区域内，离开位置X取运动方向上最后一条表的X，Y保持当前Y不变，并且对X进行补偿，要求离开该区域

void SafetyArea_Bay :: getRelatedPosForRecommendArea(long x, long y,long xEnd, long yEnd, SafteyAreaBase recommendArea , long& xPosRelated, long& yPosRelated)
{
		string functionName="SafetyArea_Bay :: getRelatedPosForRecommendArea()";
		LOG log(functionName, AUTO_CATCH_PID);
		


		try
		{
			//还没有进区域情况1
			//x    xmin    xmax
			if(x<recommendArea.getXMin() && x<recommendArea.getXMax())
			{
				xPosRelated=recommendArea.getXMin()+100;
				yPosRelated=recommendArea.getOnBordY();
			}
			//还没有进区域情况2
			//  xmin  xmax   x
			else if(x>recommendArea.getXMin() && x>recommendArea.getXMax())
			{
				xPosRelated=recommendArea.getXMax()-100;
				yPosRelated=recommendArea.getOnBordY();
			}
		    //已经进入区域
			//  xmin   x   xmax  
			else 
			{
				//已经在区域内情况1
				//  xmin   x   xmax  xEnd
				if(x<xEnd && recommendArea.getXMax()<xEnd)
				{
					xPosRelated=recommendArea.getXMax()+100;
					yPosRelated=recommendArea.getOnBordY();
				}
				//已经在区域内情况2
				//  xEnd  xmin   x   xmax
				else if(x>xEnd && recommendArea.getXMin()>xEnd)
				{
					xPosRelated=recommendArea.getXMin()-100;
					yPosRelated=recommendArea.getOnBordY();
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

void SafetyArea_Bay :: getRouteParameter(long x1, long y1, long x2, long y2, float& k, float& b)
{
		string functionName="SafetyArea_Bay :: getRouteParameter()";
		LOG log(functionName, AUTO_CATCH_PID);
		
		bool ret=true;
		if(x1==x2 && y1==y2)
		{
			k=0;
			b=0;
			return;
		}

		try
		{
				//y1=kx1+b
				//y2=kx2+b;
				//(y1-y2)=k(x1-x2);
				//k=(y1-y2)/(x1-x2)

				k=  float( (y1-y2)  )  /  float(  (x1-x2) );
				b=y1-k*x1;

				log.Debug()<<"k="<<k<<"  b="<<b<<endl;

		
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



//从起点射向终点的函数，试图找到 能否到达终点  或者  第一个阻碍我的区域
bool SafetyArea_Bay :: shotToDestination(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit)
{
		string functionName="SafetyArea_Bay :: shotToDestination()";
		LOG log(functionName, AUTO_CATCH_PID);
		
	   bool  canReachDirectly=false;

		try
		{
			//2019.4.7 zhangyuhong add
				bool bXStartEndEqual =( abs(xStart - xEnd) == 0 );
				bool bXStartEndDisMore50 = ( abs(xStart - xEnd) > 50 );
				bool bXStartEndDisLessOrEqual50 = ( abs(xStart - xEnd) <= 50 );

				//距离 > 50 的射线方法
				if ( bXStartEndDisMore50 == true )
				{
						log.Info()<<"进入 距离 > 50 的射线方法：shotMethod1() "<<endl;
						canReachDirectly = shotMethod1(xStart, yStart, xEnd, yEnd, firstBlockArea, xCanGoLimit, yCanGoLimit);
				}
				//距离 <= 50 的射线
				if ( bXStartEndDisLessOrEqual50 == true )
				{
						log.Info()<<"进入 距离 <= 50 的射线方法：shotMethod2() "<<endl;
						canReachDirectly = shotMethod2(xStart, yStart, xEnd, yEnd, firstBlockArea, xCanGoLimit, yCanGoLimit);
				}


/********************************************************************************************************************************

				//先求出直线的参数
				float k;
				float b;
				getRouteParameter(xStart,yStart,  xEnd, yEnd, k,  b) ;

				//按照Max和Min的方式描述
				long xMax;
				long xMin;
				sortTwoNum(xStart,  xEnd,  xMin, xMax);
				//log.Debug()<<"xMin="<<xMin<<"  xMax="<<xMax<<endl;
				//步长
				long xStep;

				//大车走行从X小去往X大，步长为+50
				if(xStart<xEnd)
				{
					xStep=50;
				}
				//大车走行从X大往X小，步长为-50
				else
				{
					xStep= -50;
				}
				log.Debug()<<"xStep="<<xStep<<endl;

				//开始延伸直线
				long x=xStart+xStep;
				while( x>xMin && x<xMax)
				{
					//计算出这个步长下y的值
					long y=(long)(k*x+b);
					//log.Debug()<<"x="<<x<<"\t y="<<y<<" | \t";

					if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
					{
						//log.Debug()<<"find a red block on the route.......its name="<<firstBlockArea.getName()<<endl;
						log.Debug()<<"在射线路径上找到一个红区（Red Block）.......其名称 = "<<firstBlockArea.getName()<<endl;
						canReachDirectly=false;

						//计算撞墙坐标
						if(xStep>0)//x步长是增加的，那么退后是减少
						{
							xCanGoLimit=x-3000;
							if(xCanGoLimit<xStart){xCanGoLimit=xStart;}
							yCanGoLimit=(long)(k*xCanGoLimit+b);
						}
						else//x补偿是减少的，那么往后退x是增加
						{
							xCanGoLimit=x+3000;
							if(xCanGoLimit>xStart){xCanGoLimit=xStart;}
							yCanGoLimit=(long)(k*xCanGoLimit+b);
						}
						return canReachDirectly;
					}

					x=x+xStep;
				}


				//如果能运行到这里，那么就是没有任何一块阻挡物了
				canReachDirectly=true;
				xCanGoLimit=xEnd;
				yCanGoLimit=yEnd;
				//log.Debug()<<"on the route there is not any block area "<<endl;

********************************************************************************************************************************/

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

		return canReachDirectly;
}


//2019.4.7 zhangyuhong add
//xStart 与 xEnd 距离 > 50 的情况
bool SafetyArea_Bay :: shotMethod1(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit)
{
	string functionName="SafetyArea_Bay :: shotMethod1()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool  canReachDirectly=false;

	try
	{

		//先求出直线的参数
		float k;
		float b;
		getRouteParameter(xStart,yStart,  xEnd, yEnd, k,  b) ;

		//按照Max和Min的方式描述
		long xMax;
		long xMin;
		sortTwoNum(xStart,  xEnd,  xMin, xMax);
		//步长
		long xStep;

		//大车走行从X小去往X大，步长为+50
		if(xStart<xEnd)
		{
			xStep=50;
		}
		//大车走行从X大往X小，步长为-50
		else
		{
			xStep= -50;
		}
		log.Debug()<<"xStep="<<xStep<<endl;

		//开始延伸直线
		long x=xStart+xStep;
		while( x>xMin && x<xMax)
		{
			//计算出这个步长下y的值
			long y=(long)(k*x+b);

			if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
			{
				log.Debug()<<"在射线路径上找到一个红区（Red Block）.......其名称 = "<<firstBlockArea.getName()<<endl;
				canReachDirectly=false;

				//计算撞墙坐标
				if(xStep>0)//x步长是增加的，那么退后是减少
				{
					xCanGoLimit=x-3000;
					if(xCanGoLimit<xStart){xCanGoLimit=xStart;}
					yCanGoLimit=(long)(k*xCanGoLimit+b);
				}
				else//x补偿是减少的，那么往后退x是增加
				{
					xCanGoLimit=x+3000;
					if(xCanGoLimit>xStart){xCanGoLimit=xStart;}
					yCanGoLimit=(long)(k*xCanGoLimit+b);
				}
				return canReachDirectly;
			}

			x=x+xStep;
		}


		//如果能运行到这里，那么就是没有任何一块阻挡物了
		canReachDirectly=true;
		xCanGoLimit=xEnd;
		yCanGoLimit=yEnd;

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

	return canReachDirectly;
}


//2019.4.7 zhangyuhong add
//xStart 与 xEnd 距离 <= 50 的情况
//这种情况下，认为射线就是垂直于X轴坐标  采用步进 y 值的办法
bool SafetyArea_Bay :: shotMethod2(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit)
{
	string functionName="SafetyArea_Bay :: shotMethod2()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool  canReachDirectly=false;

	try
	{
		//按照Max和Min的方式描述
		long yMax;
		long yMin;
		sortTwoNum(yStart,  yEnd,  yMin, yMax);
		//步长
		long yStep;

		//大车走行从X小去往X大，步长为+50
		if(yStart<yEnd)
		{
			yStep=50;
		}
		//大车走行从X大往X小，步长为-50
		else
		{
			yStep= -50;
		}
		log.Debug()<<"yStep="<<yStep<<endl;

		//开始延伸直线
		long y=yStart+yStep;
		while( y>yMin && y<yMax)
		{
			//此情况下，x就取xEnd
			long x = xEnd;

			if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
			{
				log.Debug()<<"在射线路径上找到一个红区（Red Block）.......其名称 = "<<firstBlockArea.getName()<<endl;
				canReachDirectly=false;

				//计算撞墙坐标
				if(yStep>0)
				{
					yCanGoLimit=y-3000;
					if(yCanGoLimit<yStart){yCanGoLimit=yStart;}
					xCanGoLimit=x;
				}
				else
				{
					yCanGoLimit=y+3000;
					if(yCanGoLimit>yStart){yCanGoLimit=yStart;}
					xCanGoLimit=x;
				}
				return canReachDirectly;
			}

			y=y+yStep;
		}


		//如果能运行到这里，那么就是没有任何一块阻挡物了
		canReachDirectly=true;
		xCanGoLimit=xEnd;
		yCanGoLimit=yEnd;

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

	return canReachDirectly;
}





//从起点射向终点的函数，试图找到 能否到达终点  或者  第一个阻碍我的区域
//2018/.12.16 增加一个公有函数
bool SafetyArea_Bay :: shotToDestination_2(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea)
{
	string functionName="SafetyArea_Bay :: shotToDestination_2()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool  canReachDirectly=false;

	try
	{
		//先求出直线的参数
		float k;
		float b;
		getRouteParameter(xStart,yStart,  xEnd, yEnd, k,  b) ;

		//按照Max和Min的方式描述
		long xMax;
		long xMin;
		sortTwoNum(xStart,  xEnd,  xMin, xMax);
		//步长
		long xStep;

		//大车走行从X小去往X大，步长为+50
		if(xStart<xEnd)
		{
			xStep=50;
		}
		//大车走行从X大往X小，步长为-50
		else
		{
			xStep= -50;
		}
		log.Debug()<<"xStep="<<xStep<<endl;

		//开始延伸直线
		long x=xStart+xStep;
		while( x>xMin && x<xMax)
		{
			//计算出这个步长下y的值
			long y=(long)(k*x+b);

			if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
			{
				log.Debug()<<"shotToDestination_2找到一个红区 = "<<firstBlockArea.getName()<<endl;
				canReachDirectly=false;
				return canReachDirectly;
			}
			x=x+xStep;
		}
		//如果能运行到这里，那么就是没有任何一块阻挡物了
		canReachDirectly=true;

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

	return canReachDirectly;
}


//canMoveNextStep=false时 就是行车不能再移动了，判死刑了,外部调用就不用再尝试下一步计算了
void SafetyArea_Bay :: arrangeSingStep(long x, long y, long xTarget, long yTarget, bool canMoveNextStep,long& xNextStep, long& yNextSetp,bool& reachTarget, bool& startInRed)
{
		string functionName="SafetyArea_Bay :: arrangeSingStep()";
		LOG log(functionName, AUTO_CATCH_PID);
		
		try
		{
				log.Debug()<<"--------------------------------------------Start arrange single step for movement------------------------------------------------"<<endl;
				log.Debug()<<"xStart="<<x<<"\t yStart="<<y<<endl;
				log.Debug()<<"xTarget="<<xTarget<<" \t yTarget="<<yTarget<<endl;

				//先给与返回参数初始值，初始值为原地，不能再动了，无法到达目标
				xNextStep=x;
				yNextSetp=y;
				canMoveNextStep=false;
				reachTarget=false;

				//防止数据超出范围
				if(x>xMaxInBay  || x<xMinInBay  || y>yMaxInBay  || y<yMinInBay)
				{
					//log.Debug()<<" error x or y out of range of the bay cal is stopped"<<endl;
					log.Debug()<<" 错误的x或y坐标值：已经超出C1A跨范围！计算终止！"<<endl;
					return;
				}
				if(xTarget>xMaxInBay  || xTarget<xMinInBay  || yTarget>yMaxInBay  || yTarget<yMinInBay)
				{
					//log.Debug()<<" error xTarget or xTarget out of range of the bay cal is stopped"<<endl;
					log.Debug()<<" 错误的targetX或targetY值：已经超出C1A跨范围！计算终止！"<<endl;
					return;
				}

				//我是否当前就站立在了红块里面
				//log.Debug()<<"Now check whether the Start Point is in a read area"<<endl;
				log.Debug()<<"现在检查起始点是否就在红区内："<<endl;
				SafteyAreaBase currentArea;
				if( isPointInAnyReadArea(x, y , currentArea)==true)
				{
					xNextStep=x;
					yNextSetp=y;
					canMoveNextStep=false;
					reachTarget=false;
					startInRed = true;
					//log.Debug()<<" the Start Point is in red area AreaName="<<currentArea.getName()<<"\t xMin of the area="<<currentArea.getXMin()<<"\t xMax of the area="<<currentArea.getXMax()<<"\t yMin of the area="<<currentArea.getYMin()<<"\t yMax of the area="<<currentArea.getYMax()<<" function is finished...."<<endl;
					log.Debug()<<" 起始点就在红区内！红区名称 AreaName="<<currentArea.getName()<<"\t 其xMin值 = "<<currentArea.getXMin()<<"\t 其xMax值 = "<<currentArea.getXMax()<<"\t 其yMin值 = "<<currentArea.getYMin()<<"\t 其yMax值 = "<<currentArea.getYMax()<<" 计算完成...."<<endl;
					return;
				}
				else
				{
					//log.Debug()<<" the Start Point is not in a red area"<<endl;
					log.Debug()<<" 起始点不在红区内"<<endl;
				}

				if(x==xTarget && y==yTarget)
				{
					xNextStep=x;
					yNextSetp=y;
					canMoveNextStep=false;
					reachTarget=true;
					log.Debug()<<"x==xTargete 并且  y==yTarget 计算无意义.....计算过程返回"<<endl;
					return;
				}

				//尝试向目标点延伸直线
				bool canReachDirectly=false;
				SafteyAreaBase firstBlockArea;
				long xCanGoLimit;
				long yCanGoLimit;

				//log.Debug()<<"Now try to draw the line to the target...."<<endl;
				log.Debug()<<"现在尝试向目标点画直线，调用 shotToDestination()函数...."<<endl;
				canReachDirectly=shotToDestination(x, y, xTarget, yTarget, firstBlockArea,xCanGoLimit,yCanGoLimit);

				
				//发现可以直达目标
				if(canReachDirectly==true)
				{
					canMoveNextStep=true;
					xNextStep=xTarget;
					yNextSetp=yTarget;
					reachTarget=true;

					//log.Debug()<<"no read area on the route, move to target directly"<<endl;
					log.Debug()<<"在路径上没有红区，可以直接抵达目标位"<<endl;
					return;
				}
				//如果不能直接到
				if(canReachDirectly==false)
				{

					xNextStep=xCanGoLimit;
					yNextSetp=yCanGoLimit;
					canMoveNextStep=true;
					reachTarget=false;

					//log.Debug()<<"there is(are) read area(s) on the route"<<endl;
					log.Debug()<<"在路径上有1个或多个红区！"<<endl;

					SafteyAreaBase targetArea;
					if( isPointInAnyReadArea(xTarget, yTarget , targetArea)==true )
					{
							//log.Debug()<<"and the target is in a red area so chose to move to the limit position on the route"<<endl;
							log.Debug()<<"并且目标 位于 1个红区内，因此只能选择移动路径上的极限位置！"<<endl;
							canMoveNextStep=false;
							reachTarget=false;
							return;
					}
				}

				//发现不能直达目标，也就是说有阻拦区
				if( canReachDirectly==false)
				{
						log.Debug()<<"路径上的第1个红区的名称 = "<<firstBlockArea.getName()<<"    其推荐区域名称 = "<<firstBlockArea.getRecommendArea1()<<endl;

						//取得阻挡块给出的推荐人1
						//推荐块1通过位置准备好
						SafteyAreaBase area_Recommend_1;

						//2019.4.3 zhangyuhong add
						//增加推荐区域2
						SafteyAreaBase area_Recommend_2;

						bool recommend_1_finded=getAreaByName(firstBlockArea.getRecommendArea1(),  area_Recommend_1);

						bool recommend_2_finded=getAreaByName(firstBlockArea.getRecommendArea2(), area_Recommend_2);

						if(recommend_1_finded==false)
						{
							log.Debug()<<"在系统中无法找到推荐区域1，选择初始路径移动到极限位置"<<endl;
						}
						if(recommend_1_finded==true  &&  area_Recommend_1.isRead()==true)
						{
							log.Debug()<<"在系统中找到了推荐区域1，但是此区域也是红区，再看看推荐区域2情况，再选择初始路径是否移动到极限位置"<<endl;
							//****************************************************************************************************************************************
							//*
							//*				新加对推荐区域2的判断
							//*				START
							//*
							//****************************************************************************************************************************************
							if (recommend_2_finded == false)
							{
								log.Debug()<<"在系统中无法找到推荐区域2，选择初始路径移动到极限位置"<<endl;
							}
							if(recommend_2_finded==true  &&  area_Recommend_2.isRead()==true)
							{
								log.Debug()<<"在系统中找到了推荐区域2，但是此区域也是红区，选择初始路径是否移动到极限位置"<<endl;
							}
							if(recommend_2_finded==true  &&  area_Recommend_2.isRead()==false)
							{
								long x_RelatedToRecommend_1=0;
								long y_RelattedToRecommend_1=0;

								getRelatedPosForRecommendArea(x, y, xTarget, yTarget, area_Recommend_2, x_RelatedToRecommend_1, y_RelattedToRecommend_1);

								log.Debug()<<"找到了推荐区域2，结果 = "<<recommend_2_finded<<endl;

								log.Debug()<<"尝试根据推荐区域2创建 入口点 或 出口点 ： "<<"  x="<<x_RelatedToRecommend_1<<"  y="<<y_RelattedToRecommend_1<<endl;

								bool canReachDirectly_Recommend_1;
								SafteyAreaBase firstBlockAre_OnWayTo_Recommend_1;
								long xCanGoLimit_Recommend_1;
								long yCanGoLimit_Recommend_1;

								log.Debug()<<"尝试画一条新的直线到推荐区域1位置.."<<endl;

								canReachDirectly_Recommend_1=shotToDestination(x, y, x_RelatedToRecommend_1, y_RelattedToRecommend_1, firstBlockAre_OnWayTo_Recommend_1,xCanGoLimit_Recommend_1,yCanGoLimit_Recommend_1);

								if( canReachDirectly_Recommend_1==true)
								{
									canMoveNextStep=true;
									xNextStep=x_RelatedToRecommend_1;
									yNextSetp=y_RelattedToRecommend_1;
									reachTarget=false;

									log.Debug()<<"在新的路径上不存在红区，直接移动到推荐区域"<<endl;
									return;
								}
								else
								{
									log.Debug()<<"在新的路径上有1个或多个红区，选择初始路径移动到极限位置"<<endl;
								}
							}
							//****************************************************************************************************************************************
							//*
							//*				新加对推荐区域2的判断
							//*				END
							//*
							//****************************************************************************************************************************************
						}

						//找到了备用推荐人  并且备用推荐人还是可以进入的
						if(recommend_1_finded==true  &&  area_Recommend_1.isRead()==false)
						{
								long x_RelatedToRecommend_1=0;
								long y_RelattedToRecommend_1=0;

								getRelatedPosForRecommendArea(x, y, xTarget, yTarget, area_Recommend_1, x_RelatedToRecommend_1, y_RelattedToRecommend_1);

								log.Debug()<<"找到了推荐区域1，结果 = "<<recommend_1_finded<<endl;
								
								log.Debug()<<"尝试根据推荐区域1创建 入口点 或 出口点 ： "<<"  x="<<x_RelatedToRecommend_1<<"  y="<<y_RelattedToRecommend_1<<endl;

								bool canReachDirectly_Recommend_1;
								SafteyAreaBase firstBlockAre_OnWayTo_Recommend_1;
								long xCanGoLimit_Recommend_1;
								long yCanGoLimit_Recommend_1;

								log.Debug()<<"尝试画一条新的直线到推荐区域1位置.."<<endl;

								canReachDirectly_Recommend_1=shotToDestination(x, y, x_RelatedToRecommend_1, y_RelattedToRecommend_1, firstBlockAre_OnWayTo_Recommend_1,xCanGoLimit_Recommend_1,yCanGoLimit_Recommend_1);

								if( canReachDirectly_Recommend_1==true)
								{
									canMoveNextStep=true;
									xNextStep=x_RelatedToRecommend_1;
									yNextSetp=y_RelattedToRecommend_1;
									reachTarget=false;

									log.Debug()<<"在新的路径上不存在红区，直接移动到推荐区域"<<endl;
									return;
								}
								else
								{
									log.Debug()<<"在新的路径上有1个或多个红区，选择初始路径移动到极限位置"<<endl;
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



//从起点到终点的整个路径的规划函数，会反馈一系列的路径点，如果能到达目标，那么最后一个路径点会打上标志
void SafetyArea_Bay :: arrangeRoute(long x, long y, long xTarget, long yTarget , vector<RouteStepPointBase>& vectorRoutePoints, bool& startInRed)
{
		string functionName="SafetyArea_Bay :: arrangeRoute()";
		LOG log(functionName, AUTO_CATCH_PID);
		
		try
		{

				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
				log.Info()<<"                                                                      arrangeRoute       start                                                                                                                            "<<endl;
				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

				//记录起点的X和Y
				long startPointX=x;
				long startPointY=y;
				RouteStepPointBase  startPoint;
				startPoint.setX(startPointX);
				startPoint.setY(startPointY);
				startPoint.setFlagReachFinalTarget(false);
				vectorRoutePoints.push_back(startPoint);

				log.Debug()<<"xStart="<<startPointX<<"\t yStart="<<startPointY<<endl;
				log.Debug()<<"xTarget="<<xTarget<<" \t yTarget="<<yTarget<<endl;

				bool canMoveNextStep=true;
				bool reachTarget=false;
				//bool startInRed = false;

				long xNextStep;
				long yNextStep;

				int i=0;
				while(i<20  && canMoveNextStep==true && reachTarget==false   )
				{
						log.Debug()<<"step="<<i<<".............................................................................................................."<<endl;

						arrangeSingStep(x, y, xTarget , yTarget ,canMoveNextStep, xNextStep, yNextStep, reachTarget, startInRed);

						log.Debug()<<"xNextStep="<<xNextStep<<"\t    yNextSetp="<<yNextStep<<"\t  canMoveNextStep="<<canMoveNextStep<<"\t    reachTarget="<<reachTarget<<endl;
						

						bool canPushBackPoint=true;

						if(x==xNextStep  &&  y==yNextStep)
						{
							canMoveNextStep=false;
							canPushBackPoint=false;
						}
						if( abs(x-xNextStep)<50 && abs(y-yNextStep)<50)
						{
							canMoveNextStep=false;
							xNextStep=x;
							yNextStep=y;
							canPushBackPoint=false;

						}

						RouteStepPointBase  routeStepPointBase;
						routeStepPointBase.setX(xNextStep);
						routeStepPointBase.setY(yNextStep);
						routeStepPointBase.setFlagReachFinalTarget(reachTarget);
						
						if(canPushBackPoint==true)
						{
							vectorRoutePoints.push_back(routeStepPointBase);
						}


						x=xNextStep;
						y=yNextStep;
						i++;
				}

				


				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
				log.Info()<<"                                                                      arrangeRoute       Finished   now print out result                                                                                       "<<endl;
				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

				log.Debug()<<"FromX="<<startPointX<<"\t FromY="<<startPointY<<endl;
				log.Debug()<<"FinalX="<<xTarget<<" \t FinalY="<<yTarget<<endl;


				for(int i=0; i<vectorRoutePoints.size();i++)
				{
					vectorRoutePoints[i].logOutValues();
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



map<string, SafteyAreaBase> SafetyArea_Bay :: getMapSafeAreaBase()
{
		return mapSafteyAreas;	
}

map<string, long> SafetyArea_Bay :: getMapAreaXMinMax()
{
	return mapAreaXMinMax;	
}

map<string, long> SafetyArea_Bay :: getMapPA2SpMinPT()
{
	return mapPA02_SP_MIN_X_PT;	
}

map<string, long> SafetyArea_Bay :: getMapPA2SpMaxPT()
{
	return mapPA02_SP_MAX_X_PT;	
}


vector<SafteyAreaBase> SafetyArea_Bay :: getVecSafeAreaBase()
{
		return vectorSafteyAreas;
}

TAGNAMEARRAY SafetyArea_Bay :: getArrayTagNameSafeDoor()
{
	return arryTagNameSafeDoor;
}

void SafetyArea_Bay :: setVecSafeAreaBase(vector<SafteyAreaBase> theValue)
{
		vectorSafteyAreas = theValue;
}





void SafetyArea_Bay::setMapSafeAreaBase(map<string, SafteyAreaBase> theValue)
{
		mapSafteyAreas = theValue;
}

bool SafetyArea_Bay :: isPointInAnyReadArea2(long x, long y, SafteyAreaBase& safteyAreaBase)
{
	string functionName="SafetyArea_Bay :: isPointInAnyReadArea2()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool isInReadArea=false;

	try
	{
		for(vector<SafteyAreaBase>::size_type i=0;i<vectorSafteyAreas.size();i++)
		{
			if( x>=vectorSafteyAreas[i].getXMin()  && x<vectorSafteyAreas[i].getXMax() &&
				y>=vectorSafteyAreas[i].getYMin()  && y<vectorSafteyAreas[i].getYMax() )
			{
				if(vectorSafteyAreas[i].isRead()==true)
				{
					safteyAreaBase= vectorSafteyAreas[i];
					isInReadArea=true;
					return isInReadArea;
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
	return isInReadArea;
}




bool SafetyArea_Bay :: shotMethodGet1stRedArea(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea )
{
	string functionName="SafetyArea_Bay :: shotMethodGet1stRedArea()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool  canReachDirectly=false;

	try
	{

		//先求出直线的参数
		float k;
		float b;
		getRouteParameter(xStart,yStart,  xEnd, yEnd, k,  b) ;

		//按照Max和Min的方式描述
		long xMax;
		long xMin;
		sortTwoNum(xStart,  xEnd,  xMin, xMax);
		//步长
		long xStep;

		//大车走行从X小去往X大，步长为+50
		if(xStart<xEnd)
		{
			xStep=50;
		}
		//大车走行从X大往X小，步长为-50
		else
		{
			xStep= -50;
		}
		log.Debug()<<"xStep="<<xStep<<endl;

		//开始延伸直线
		long x=xStart+xStep;
		while( x>xMin && x<xMax)
		{
			//计算出这个步长下y的值
			long y=(long)(k*x+b);

			if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
			{
				log.Debug()<<"在射线路径上找到一个红区（Red Block）.......其名称 = "<<firstBlockArea.getName()<<endl;
				canReachDirectly=false;
				return canReachDirectly;
			}

			x=x+xStep;
		}
		//如果能运行到这里，那么就是没有任何一块阻挡物了
		canReachDirectly=true;

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

	return canReachDirectly;
}


//通过区域的名称获得区域的对象
bool SafetyArea_Bay :: getAreaByNameNew(string theAreaName, SafteyAreaBase& safteyAreaBase)
{
	string functionName="SafetyArea_Bay :: getAreaByNameNew()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool finded=false;

	try
	{
		map<string , SafteyAreaBase>::iterator theIterator;
		theIterator=mapSafteyAreas.find( theAreaName );
		if(theIterator!=mapSafteyAreas.end())
		{
			safteyAreaBase=theIterator->second;
			finded=true;
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

	return finded;
}


bool SafetyArea_Bay :: getAreaByPosXY(long x, long y, SafteyAreaBase& safteyAreaBase)
{
	string functionName="SafetyArea_Bay :: getAreaByPosXY()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool isFinded=false;

	try
	{
		for(vector<SafteyAreaBase>::size_type i=0;i<vectorSafteyAreas.size();i++)
		{
			if( x>=vectorSafteyAreas[i].getXMin()  && x<vectorSafteyAreas[i].getXMax() &&
				y>=vectorSafteyAreas[i].getYMin()  && y<vectorSafteyAreas[i].getYMax() )
			{
					safteyAreaBase= vectorSafteyAreas[i];
					isFinded=true;
					return isFinded;
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
	return isFinded;
}

