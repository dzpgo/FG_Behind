#include "SafetyArea_Bay.h"


//#include <Util.h>

using namespace Monitor;
using namespace iPlature;


const string SafetyArea_Bay::RIGHT="R";
const string SafetyArea_Bay::LEFT="L";

const string SafetyArea_Bay::TREND_INC="INC";
const string SafetyArea_Bay::TREND_DES="DES";

//��������ָ��
SafetyArea_Bay*  SafetyArea_Bay::m_pSafetyArea_Bay = NULL;

//��������
SafetyArea_Bay::SafetyArea_Bay() 
{
	
}

//��������
SafetyArea_Bay :: ~SafetyArea_Bay(void)
{
	
	delete m_pSafetyArea_Bay;


}

//���ָ��ķ���
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

//��ȡXML�ļ��ķ���
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


					//��riverBank����ѹ���Լ������ݶ�����
					InputSafteyArea( safteyArea_RiverBank );

					

			}

			

			//��ӡ��������ֵ
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


//ͨ����������ƻ������Ķ���
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

//��XML�ж�ȡ�����������ݱ��浽�������ķ���
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
			//�ɼ�  SAFE_EQP_09  ������   pa2���߰�װ��
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
			//�ɼ�  SAFE_EQP_12  ������   C176���߲����
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
				log.Info()<<"���к�����X_MIN��X_MAX�Ѿ��ɼ����......"<<endl;
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
		mapPA02_SP_MIN_X_PT["X"] = 85224;//PA2 ��16#λ������ 
		mapPA02_SP_MIN_X_PT["Y"] = 3600;

		//mapPA02_SP_MAX_X_PT["X"] = mapAreaXMinMax["A4_X_MAX"] + 100;
		mapPA02_SP_MAX_X_PT["X"] = 138000;//175��������λ������ - 100
		mapPA02_SP_MAX_X_PT["Y"] = 3600;

		log.Info()<<"mapPA2SpMinXPT�� X ="<<mapPA02_SP_MIN_X_PT["X"]<<",   Y = "<<mapPA02_SP_MIN_X_PT["Y"]<<endl;
		log.Info()<<"mapPA2SpMaxXPT�� X ="<<mapPA02_SP_MAX_X_PT["X"]<<",   Y = "<<mapPA02_SP_MAX_X_PT["Y"]<<endl;

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



//��ӡ�������е�����
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





//�������������յ����꣬Ѱ�ҽ����Ƽ����������λ�ã���ǰ���������⣬����λ��Xȡ�˶������ϵ�һ���ߵ�X �� Yȥ����Y�����Ҷ�X���в�����Ҫ�����������
//                                                                                                                     ������������ڣ��뿪λ��Xȡ�˶����������һ�����X��Y���ֵ�ǰY���䣬���Ҷ�X���в�����Ҫ���뿪������

void SafetyArea_Bay :: getRelatedPosForRecommendArea(long x, long y,long xEnd, long yEnd, SafteyAreaBase recommendArea , long& xPosRelated, long& yPosRelated)
{
		string functionName="SafetyArea_Bay :: getRelatedPosForRecommendArea()";
		LOG log(functionName, AUTO_CATCH_PID);
		


		try
		{
			//��û�н��������1
			//x    xmin    xmax
			if(x<recommendArea.getXMin() && x<recommendArea.getXMax())
			{
				xPosRelated=recommendArea.getXMin()+100;
				yPosRelated=recommendArea.getOnBordY();
			}
			//��û�н��������2
			//  xmin  xmax   x
			else if(x>recommendArea.getXMin() && x>recommendArea.getXMax())
			{
				xPosRelated=recommendArea.getXMax()-100;
				yPosRelated=recommendArea.getOnBordY();
			}
		    //�Ѿ���������
			//  xmin   x   xmax  
			else 
			{
				//�Ѿ������������1
				//  xmin   x   xmax  xEnd
				if(x<xEnd && recommendArea.getXMax()<xEnd)
				{
					xPosRelated=recommendArea.getXMax()+100;
					yPosRelated=recommendArea.getOnBordY();
				}
				//�Ѿ������������2
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



//����������յ�ĺ�������ͼ�ҵ� �ܷ񵽴��յ�  ����  ��һ���谭�ҵ�����
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

				//���� > 50 �����߷���
				if ( bXStartEndDisMore50 == true )
				{
						log.Info()<<"���� ���� > 50 �����߷�����shotMethod1() "<<endl;
						canReachDirectly = shotMethod1(xStart, yStart, xEnd, yEnd, firstBlockArea, xCanGoLimit, yCanGoLimit);
				}
				//���� <= 50 ������
				if ( bXStartEndDisLessOrEqual50 == true )
				{
						log.Info()<<"���� ���� <= 50 �����߷�����shotMethod2() "<<endl;
						canReachDirectly = shotMethod2(xStart, yStart, xEnd, yEnd, firstBlockArea, xCanGoLimit, yCanGoLimit);
				}


/********************************************************************************************************************************

				//�����ֱ�ߵĲ���
				float k;
				float b;
				getRouteParameter(xStart,yStart,  xEnd, yEnd, k,  b) ;

				//����Max��Min�ķ�ʽ����
				long xMax;
				long xMin;
				sortTwoNum(xStart,  xEnd,  xMin, xMax);
				//log.Debug()<<"xMin="<<xMin<<"  xMax="<<xMax<<endl;
				//����
				long xStep;

				//�����д�XСȥ��X�󣬲���Ϊ+50
				if(xStart<xEnd)
				{
					xStep=50;
				}
				//�����д�X����XС������Ϊ-50
				else
				{
					xStep= -50;
				}
				log.Debug()<<"xStep="<<xStep<<endl;

				//��ʼ����ֱ��
				long x=xStart+xStep;
				while( x>xMin && x<xMax)
				{
					//��������������y��ֵ
					long y=(long)(k*x+b);
					//log.Debug()<<"x="<<x<<"\t y="<<y<<" | \t";

					if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
					{
						//log.Debug()<<"find a red block on the route.......its name="<<firstBlockArea.getName()<<endl;
						log.Debug()<<"������·�����ҵ�һ��������Red Block��.......������ = "<<firstBlockArea.getName()<<endl;
						canReachDirectly=false;

						//����ײǽ����
						if(xStep>0)//x���������ӵģ���ô�˺��Ǽ���
						{
							xCanGoLimit=x-3000;
							if(xCanGoLimit<xStart){xCanGoLimit=xStart;}
							yCanGoLimit=(long)(k*xCanGoLimit+b);
						}
						else//x�����Ǽ��ٵģ���ô������x������
						{
							xCanGoLimit=x+3000;
							if(xCanGoLimit>xStart){xCanGoLimit=xStart;}
							yCanGoLimit=(long)(k*xCanGoLimit+b);
						}
						return canReachDirectly;
					}

					x=x+xStep;
				}


				//��������е������ô����û���κ�һ���赲����
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
//xStart �� xEnd ���� > 50 �����
bool SafetyArea_Bay :: shotMethod1(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit)
{
	string functionName="SafetyArea_Bay :: shotMethod1()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool  canReachDirectly=false;

	try
	{

		//�����ֱ�ߵĲ���
		float k;
		float b;
		getRouteParameter(xStart,yStart,  xEnd, yEnd, k,  b) ;

		//����Max��Min�ķ�ʽ����
		long xMax;
		long xMin;
		sortTwoNum(xStart,  xEnd,  xMin, xMax);
		//����
		long xStep;

		//�����д�XСȥ��X�󣬲���Ϊ+50
		if(xStart<xEnd)
		{
			xStep=50;
		}
		//�����д�X����XС������Ϊ-50
		else
		{
			xStep= -50;
		}
		log.Debug()<<"xStep="<<xStep<<endl;

		//��ʼ����ֱ��
		long x=xStart+xStep;
		while( x>xMin && x<xMax)
		{
			//��������������y��ֵ
			long y=(long)(k*x+b);

			if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
			{
				log.Debug()<<"������·�����ҵ�һ��������Red Block��.......������ = "<<firstBlockArea.getName()<<endl;
				canReachDirectly=false;

				//����ײǽ����
				if(xStep>0)//x���������ӵģ���ô�˺��Ǽ���
				{
					xCanGoLimit=x-3000;
					if(xCanGoLimit<xStart){xCanGoLimit=xStart;}
					yCanGoLimit=(long)(k*xCanGoLimit+b);
				}
				else//x�����Ǽ��ٵģ���ô������x������
				{
					xCanGoLimit=x+3000;
					if(xCanGoLimit>xStart){xCanGoLimit=xStart;}
					yCanGoLimit=(long)(k*xCanGoLimit+b);
				}
				return canReachDirectly;
			}

			x=x+xStep;
		}


		//��������е������ô����û���κ�һ���赲����
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
//xStart �� xEnd ���� <= 50 �����
//��������£���Ϊ���߾��Ǵ�ֱ��X������  ���ò��� y ֵ�İ취
bool SafetyArea_Bay :: shotMethod2(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit)
{
	string functionName="SafetyArea_Bay :: shotMethod2()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool  canReachDirectly=false;

	try
	{
		//����Max��Min�ķ�ʽ����
		long yMax;
		long yMin;
		sortTwoNum(yStart,  yEnd,  yMin, yMax);
		//����
		long yStep;

		//�����д�XСȥ��X�󣬲���Ϊ+50
		if(yStart<yEnd)
		{
			yStep=50;
		}
		//�����д�X����XС������Ϊ-50
		else
		{
			yStep= -50;
		}
		log.Debug()<<"yStep="<<yStep<<endl;

		//��ʼ����ֱ��
		long y=yStart+yStep;
		while( y>yMin && y<yMax)
		{
			//������£�x��ȡxEnd
			long x = xEnd;

			if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
			{
				log.Debug()<<"������·�����ҵ�һ��������Red Block��.......������ = "<<firstBlockArea.getName()<<endl;
				canReachDirectly=false;

				//����ײǽ����
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


		//��������е������ô����û���κ�һ���赲����
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





//����������յ�ĺ�������ͼ�ҵ� �ܷ񵽴��յ�  ����  ��һ���谭�ҵ�����
//2018/.12.16 ����һ�����к���
bool SafetyArea_Bay :: shotToDestination_2(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea)
{
	string functionName="SafetyArea_Bay :: shotToDestination_2()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool  canReachDirectly=false;

	try
	{
		//�����ֱ�ߵĲ���
		float k;
		float b;
		getRouteParameter(xStart,yStart,  xEnd, yEnd, k,  b) ;

		//����Max��Min�ķ�ʽ����
		long xMax;
		long xMin;
		sortTwoNum(xStart,  xEnd,  xMin, xMax);
		//����
		long xStep;

		//�����д�XСȥ��X�󣬲���Ϊ+50
		if(xStart<xEnd)
		{
			xStep=50;
		}
		//�����д�X����XС������Ϊ-50
		else
		{
			xStep= -50;
		}
		log.Debug()<<"xStep="<<xStep<<endl;

		//��ʼ����ֱ��
		long x=xStart+xStep;
		while( x>xMin && x<xMax)
		{
			//��������������y��ֵ
			long y=(long)(k*x+b);

			if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
			{
				log.Debug()<<"shotToDestination_2�ҵ�һ������ = "<<firstBlockArea.getName()<<endl;
				canReachDirectly=false;
				return canReachDirectly;
			}
			x=x+xStep;
		}
		//��������е������ô����û���κ�һ���赲����
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


//canMoveNextStep=falseʱ �����г��������ƶ��ˣ���������,�ⲿ���þͲ����ٳ�����һ��������
void SafetyArea_Bay :: arrangeSingStep(long x, long y, long xTarget, long yTarget, bool canMoveNextStep,long& xNextStep, long& yNextSetp,bool& reachTarget, bool& startInRed)
{
		string functionName="SafetyArea_Bay :: arrangeSingStep()";
		LOG log(functionName, AUTO_CATCH_PID);
		
		try
		{
				log.Debug()<<"--------------------------------------------Start arrange single step for movement------------------------------------------------"<<endl;
				log.Debug()<<"xStart="<<x<<"\t yStart="<<y<<endl;
				log.Debug()<<"xTarget="<<xTarget<<" \t yTarget="<<yTarget<<endl;

				//�ȸ��뷵�ز�����ʼֵ����ʼֵΪԭ�أ������ٶ��ˣ��޷�����Ŀ��
				xNextStep=x;
				yNextSetp=y;
				canMoveNextStep=false;
				reachTarget=false;

				//��ֹ���ݳ�����Χ
				if(x>xMaxInBay  || x<xMinInBay  || y>yMaxInBay  || y<yMinInBay)
				{
					//log.Debug()<<" error x or y out of range of the bay cal is stopped"<<endl;
					log.Debug()<<" �����x��y����ֵ���Ѿ�����C1A�緶Χ��������ֹ��"<<endl;
					return;
				}
				if(xTarget>xMaxInBay  || xTarget<xMinInBay  || yTarget>yMaxInBay  || yTarget<yMinInBay)
				{
					//log.Debug()<<" error xTarget or xTarget out of range of the bay cal is stopped"<<endl;
					log.Debug()<<" �����targetX��targetYֵ���Ѿ�����C1A�緶Χ��������ֹ��"<<endl;
					return;
				}

				//���Ƿ�ǰ��վ�����˺������
				//log.Debug()<<"Now check whether the Start Point is in a read area"<<endl;
				log.Debug()<<"���ڼ����ʼ���Ƿ���ں����ڣ�"<<endl;
				SafteyAreaBase currentArea;
				if( isPointInAnyReadArea(x, y , currentArea)==true)
				{
					xNextStep=x;
					yNextSetp=y;
					canMoveNextStep=false;
					reachTarget=false;
					startInRed = true;
					//log.Debug()<<" the Start Point is in red area AreaName="<<currentArea.getName()<<"\t xMin of the area="<<currentArea.getXMin()<<"\t xMax of the area="<<currentArea.getXMax()<<"\t yMin of the area="<<currentArea.getYMin()<<"\t yMax of the area="<<currentArea.getYMax()<<" function is finished...."<<endl;
					log.Debug()<<" ��ʼ����ں����ڣ��������� AreaName="<<currentArea.getName()<<"\t ��xMinֵ = "<<currentArea.getXMin()<<"\t ��xMaxֵ = "<<currentArea.getXMax()<<"\t ��yMinֵ = "<<currentArea.getYMin()<<"\t ��yMaxֵ = "<<currentArea.getYMax()<<" �������...."<<endl;
					return;
				}
				else
				{
					//log.Debug()<<" the Start Point is not in a red area"<<endl;
					log.Debug()<<" ��ʼ�㲻�ں�����"<<endl;
				}

				if(x==xTarget && y==yTarget)
				{
					xNextStep=x;
					yNextSetp=y;
					canMoveNextStep=false;
					reachTarget=true;
					log.Debug()<<"x==xTargete ����  y==yTarget ����������.....������̷���"<<endl;
					return;
				}

				//������Ŀ�������ֱ��
				bool canReachDirectly=false;
				SafteyAreaBase firstBlockArea;
				long xCanGoLimit;
				long yCanGoLimit;

				//log.Debug()<<"Now try to draw the line to the target...."<<endl;
				log.Debug()<<"���ڳ�����Ŀ��㻭ֱ�ߣ����� shotToDestination()����...."<<endl;
				canReachDirectly=shotToDestination(x, y, xTarget, yTarget, firstBlockArea,xCanGoLimit,yCanGoLimit);

				
				//���ֿ���ֱ��Ŀ��
				if(canReachDirectly==true)
				{
					canMoveNextStep=true;
					xNextStep=xTarget;
					yNextSetp=yTarget;
					reachTarget=true;

					//log.Debug()<<"no read area on the route, move to target directly"<<endl;
					log.Debug()<<"��·����û�к���������ֱ�ӵִ�Ŀ��λ"<<endl;
					return;
				}
				//�������ֱ�ӵ�
				if(canReachDirectly==false)
				{

					xNextStep=xCanGoLimit;
					yNextSetp=yCanGoLimit;
					canMoveNextStep=true;
					reachTarget=false;

					//log.Debug()<<"there is(are) read area(s) on the route"<<endl;
					log.Debug()<<"��·������1������������"<<endl;

					SafteyAreaBase targetArea;
					if( isPointInAnyReadArea(xTarget, yTarget , targetArea)==true )
					{
							//log.Debug()<<"and the target is in a red area so chose to move to the limit position on the route"<<endl;
							log.Debug()<<"����Ŀ�� λ�� 1�������ڣ����ֻ��ѡ���ƶ�·���ϵļ���λ�ã�"<<endl;
							canMoveNextStep=false;
							reachTarget=false;
							return;
					}
				}

				//���ֲ���ֱ��Ŀ�꣬Ҳ����˵��������
				if( canReachDirectly==false)
				{
						log.Debug()<<"·���ϵĵ�1������������ = "<<firstBlockArea.getName()<<"    ���Ƽ��������� = "<<firstBlockArea.getRecommendArea1()<<endl;

						//ȡ���赲��������Ƽ���1
						//�Ƽ���1ͨ��λ��׼����
						SafteyAreaBase area_Recommend_1;

						//2019.4.3 zhangyuhong add
						//�����Ƽ�����2
						SafteyAreaBase area_Recommend_2;

						bool recommend_1_finded=getAreaByName(firstBlockArea.getRecommendArea1(),  area_Recommend_1);

						bool recommend_2_finded=getAreaByName(firstBlockArea.getRecommendArea2(), area_Recommend_2);

						if(recommend_1_finded==false)
						{
							log.Debug()<<"��ϵͳ���޷��ҵ��Ƽ�����1��ѡ���ʼ·���ƶ�������λ��"<<endl;
						}
						if(recommend_1_finded==true  &&  area_Recommend_1.isRead()==true)
						{
							log.Debug()<<"��ϵͳ���ҵ����Ƽ�����1�����Ǵ�����Ҳ�Ǻ������ٿ����Ƽ�����2�������ѡ���ʼ·���Ƿ��ƶ�������λ��"<<endl;
							//****************************************************************************************************************************************
							//*
							//*				�¼Ӷ��Ƽ�����2���ж�
							//*				START
							//*
							//****************************************************************************************************************************************
							if (recommend_2_finded == false)
							{
								log.Debug()<<"��ϵͳ���޷��ҵ��Ƽ�����2��ѡ���ʼ·���ƶ�������λ��"<<endl;
							}
							if(recommend_2_finded==true  &&  area_Recommend_2.isRead()==true)
							{
								log.Debug()<<"��ϵͳ���ҵ����Ƽ�����2�����Ǵ�����Ҳ�Ǻ�����ѡ���ʼ·���Ƿ��ƶ�������λ��"<<endl;
							}
							if(recommend_2_finded==true  &&  area_Recommend_2.isRead()==false)
							{
								long x_RelatedToRecommend_1=0;
								long y_RelattedToRecommend_1=0;

								getRelatedPosForRecommendArea(x, y, xTarget, yTarget, area_Recommend_2, x_RelatedToRecommend_1, y_RelattedToRecommend_1);

								log.Debug()<<"�ҵ����Ƽ�����2����� = "<<recommend_2_finded<<endl;

								log.Debug()<<"���Ը����Ƽ�����2���� ��ڵ� �� ���ڵ� �� "<<"  x="<<x_RelatedToRecommend_1<<"  y="<<y_RelattedToRecommend_1<<endl;

								bool canReachDirectly_Recommend_1;
								SafteyAreaBase firstBlockAre_OnWayTo_Recommend_1;
								long xCanGoLimit_Recommend_1;
								long yCanGoLimit_Recommend_1;

								log.Debug()<<"���Ի�һ���µ�ֱ�ߵ��Ƽ�����1λ��.."<<endl;

								canReachDirectly_Recommend_1=shotToDestination(x, y, x_RelatedToRecommend_1, y_RelattedToRecommend_1, firstBlockAre_OnWayTo_Recommend_1,xCanGoLimit_Recommend_1,yCanGoLimit_Recommend_1);

								if( canReachDirectly_Recommend_1==true)
								{
									canMoveNextStep=true;
									xNextStep=x_RelatedToRecommend_1;
									yNextSetp=y_RelattedToRecommend_1;
									reachTarget=false;

									log.Debug()<<"���µ�·���ϲ����ں�����ֱ���ƶ����Ƽ�����"<<endl;
									return;
								}
								else
								{
									log.Debug()<<"���µ�·������1������������ѡ���ʼ·���ƶ�������λ��"<<endl;
								}
							}
							//****************************************************************************************************************************************
							//*
							//*				�¼Ӷ��Ƽ�����2���ж�
							//*				END
							//*
							//****************************************************************************************************************************************
						}

						//�ҵ��˱����Ƽ���  ���ұ����Ƽ��˻��ǿ��Խ����
						if(recommend_1_finded==true  &&  area_Recommend_1.isRead()==false)
						{
								long x_RelatedToRecommend_1=0;
								long y_RelattedToRecommend_1=0;

								getRelatedPosForRecommendArea(x, y, xTarget, yTarget, area_Recommend_1, x_RelatedToRecommend_1, y_RelattedToRecommend_1);

								log.Debug()<<"�ҵ����Ƽ�����1����� = "<<recommend_1_finded<<endl;
								
								log.Debug()<<"���Ը����Ƽ�����1���� ��ڵ� �� ���ڵ� �� "<<"  x="<<x_RelatedToRecommend_1<<"  y="<<y_RelattedToRecommend_1<<endl;

								bool canReachDirectly_Recommend_1;
								SafteyAreaBase firstBlockAre_OnWayTo_Recommend_1;
								long xCanGoLimit_Recommend_1;
								long yCanGoLimit_Recommend_1;

								log.Debug()<<"���Ի�һ���µ�ֱ�ߵ��Ƽ�����1λ��.."<<endl;

								canReachDirectly_Recommend_1=shotToDestination(x, y, x_RelatedToRecommend_1, y_RelattedToRecommend_1, firstBlockAre_OnWayTo_Recommend_1,xCanGoLimit_Recommend_1,yCanGoLimit_Recommend_1);

								if( canReachDirectly_Recommend_1==true)
								{
									canMoveNextStep=true;
									xNextStep=x_RelatedToRecommend_1;
									yNextSetp=y_RelattedToRecommend_1;
									reachTarget=false;

									log.Debug()<<"���µ�·���ϲ����ں�����ֱ���ƶ����Ƽ�����"<<endl;
									return;
								}
								else
								{
									log.Debug()<<"���µ�·������1������������ѡ���ʼ·���ƶ�������λ��"<<endl;
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



//����㵽�յ������·���Ĺ滮�������ᷴ��һϵ�е�·���㣬����ܵ���Ŀ�꣬��ô���һ��·�������ϱ�־
void SafetyArea_Bay :: arrangeRoute(long x, long y, long xTarget, long yTarget , vector<RouteStepPointBase>& vectorRoutePoints, bool& startInRed)
{
		string functionName="SafetyArea_Bay :: arrangeRoute()";
		LOG log(functionName, AUTO_CATCH_PID);
		
		try
		{

				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
				log.Info()<<"                                                                      arrangeRoute       start                                                                                                                            "<<endl;
				log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

				//��¼����X��Y
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

		//�����ֱ�ߵĲ���
		float k;
		float b;
		getRouteParameter(xStart,yStart,  xEnd, yEnd, k,  b) ;

		//����Max��Min�ķ�ʽ����
		long xMax;
		long xMin;
		sortTwoNum(xStart,  xEnd,  xMin, xMax);
		//����
		long xStep;

		//�����д�XСȥ��X�󣬲���Ϊ+50
		if(xStart<xEnd)
		{
			xStep=50;
		}
		//�����д�X����XС������Ϊ-50
		else
		{
			xStep= -50;
		}
		log.Debug()<<"xStep="<<xStep<<endl;

		//��ʼ����ֱ��
		long x=xStart+xStep;
		while( x>xMin && x<xMax)
		{
			//��������������y��ֵ
			long y=(long)(k*x+b);

			if( isPointInAnyReadArea(x,y,firstBlockArea)==true)
			{
				log.Debug()<<"������·�����ҵ�һ��������Red Block��.......������ = "<<firstBlockArea.getName()<<endl;
				canReachDirectly=false;
				return canReachDirectly;
			}

			x=x+xStep;
		}
		//��������е������ô����û���κ�һ���赲����
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


//ͨ����������ƻ������Ķ���
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

