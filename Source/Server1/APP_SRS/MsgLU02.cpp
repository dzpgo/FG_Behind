#include "MsgLU02.h"
#include "SQL4SRS.h"


using namespace Monitor;
using namespace iPlature;
using namespace iXcomTCP2;

MsgLU02*  MsgLU02::m_pMsgLU02 = NULL;

MsgLU02::MsgLU02() 
{

}

MsgLU02 :: ~MsgLU02(void)
{
	delete m_pMsgLU02;
}

MsgLU02* MsgLU02::getInstance(void)
{
	if (m_pMsgLU02 == NULL)
	{
		m_pMsgLU02 = new MsgLU02;
	}
	return m_pMsgLU02;
}

string MsgLU02 :: getMsgID()
{
	return m_strMsgId;
}
void MsgLU02 :: setMsgID(string theVal)
{
	m_strMsgId = theVal;
}


ByteSeq MsgLU02::HandleMessage(const string& jsonStr, string craneNO)
{
	string functionName = "MsgLU02 :: HandleMessage()";
	ByteSeq ret;

	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		//打印到测试日志 接收时间		
		log.Info()<<"jsonStr = "<<jsonStr<<endl;
		if(jsonStr == "{}")
		{
			log.Debug()<<"No strJsonScanResult............return.............."<<endl;
			return ret;
		}
		//获取LU02的json格式的smartdata格式
		SmartData sdLU02SD = MsgSmartDataManager::InsRef().GetMsgSmartData("LU02SD");
		if( MsgLU02Convert(jsonStr, sdLU02SD) == false)
		{
			log.Debug()<<"MsgLU02Convert  FAILED! return.................."<<endl;
			return ret;
		}

		//如果本模块自带的行车号和收到的激光电文中的行车号不一致，报警返回
		if ( craneNO != sdLU02SD["KEY_CraneNo"].toString() )
		{
			log.Debug()<<"craneNO != sdLU02SD[KEY_CraneNo]!   return.................."<<endl;
			return ret;
		}

		//对SD数据进行数据库表操作
		string scanNO = sdLU02SD["KEY_TreatmentNo"].toString();
		string scanResult = sdLU02SD["KEY_ResultState"].toString();

		if (scanResult == "0")
		{
			log.Info()<<" SRS Scan Car FAILED...........scanResult = "<<scanResult<<", return false............"<<endl;
			SQL4SRS::UpdParkingSRSCarInfo(scanNO, 
																		 scanResult, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL,
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL, 
																		 DB_INT_NULL );//车厢点都更新成0
			return ret;
		}

		log.Info()<<" SRS Scan Car SUCCESS...........scanResult = "<<scanResult<<endl;

		long pointX1 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][0]["KEY_PointX"].toString());
		long pointY1 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][0]["KEY_PointY"].toString());
		long pointZ1 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][0]["KEY_PointZ"].toString());
		long pointX2 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][1]["KEY_PointX"].toString());
		long pointY2 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][1]["KEY_PointY"].toString());
		long pointZ2 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][1]["KEY_PointZ"].toString());
		long pointX3 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][2]["KEY_PointX"].toString());
		long pointY3 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][2]["KEY_PointY"].toString());
		long pointZ3 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][2]["KEY_PointZ"].toString());
		long pointX4 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][3]["KEY_PointX"].toString());
		long pointY4 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][3]["KEY_PointY"].toString());
		long pointZ4 = StringHelper::ToNumber<long>(sdLU02SD["KEY_Boundary"][3]["KEY_PointZ"].toString());

		//对X  Y 坐标进行排序  从小到大
		//暂时这样处理一下  至于用处以后看情况再做处理
		vector<long> vecPointX;
		vector<long> vecPointY;
		vecPointX.push_back(pointX1);
		vecPointX.push_back(pointX2);
		vecPointX.push_back(pointX3);
		vecPointX.push_back(pointX4);
		vecPointY.push_back(pointY1);
		vecPointY.push_back(pointY2);
		vecPointY.push_back(pointY3);
		vecPointY.push_back(pointY4);
		sort(vecPointX.begin(), vecPointX.end());
		sort(vecPointY.begin(), vecPointY.end());

		//取 vecPointX[1]  vecPointX[2]  作为point_x_min  point_x_max
		//取 vecPointY[1]  vecPointY[2]  作为point_y_min  point_y_max
		//通过 这2个值  算出 centerX  CENTERy

		long pointXMax = vecPointX[2];
		long pointXMin = vecPointX[1];
		long pointYMax = vecPointY[2];
		long pointYMin = vecPointY[1];

		long centerX = (pointXMax + pointXMin) / 2;
		long centerY = (pointYMax + pointYMin) / 2;

		SQL4SRS::UpdParkingSRSCarInfo(scanNO, 
																	scanResult,
																	pointX1, 
																	pointY1, 
																	pointZ1, 
																	pointX2, 
																	pointY2, 
																	pointZ2, 
																	pointX3, 
																	pointY3,	
																	pointZ3, 
																	pointX4, 
																	pointY4, 
																	pointZ4, 
																	pointXMax, 
																	pointXMin, 
																	pointYMax, 
																	pointYMin, 
																	centerX, 
																	centerY );


		//获取此次扫描对应的orderNO, 组织tag数据通过EV点发给 行车模块
		long orderNO = 0;
		SQL4SRS::SelOrderNOByCarScanNO(scanNO, orderNO);

		//EV TAG名称："EV_SRS_" + craneNO + "_LU02"
		//Tag值格式：orderNO, carScanNO
		string scanCraneNO = sdLU02SD["KEY_CraneNo"].toString();
		string tagName = "EV_SRS_" + scanCraneNO + "_LU02";
		string tagValue = StringHelper::ToString(orderNO) + "," + scanNO;
		EVTagSnd(tagName, tagValue);

		


		
//==================================RGV的处理，后面再说==========================================================

		//if (scanRGVFlag == "1")//rgv整车扫描数据 写入UACS_PARKING_RGV_STATUS
		//{
		//	//获取RGV中激光扫描数据中X最大最小  Y最大最小
		//	long xMax = GetMax(pointX1, pointX2, pointX3, pointX4);
		//	long xMin = GetMin(pointX1, pointX2, pointX3, pointX4);
		//	long yMax = GetMax(pointY1, pointY2, pointY3, pointY4);
		//	long yMin = GetMin(pointY1, pointY2, pointY3, pointY4);

		//	//安全起见，取激光扫描

		//	SQL4SRS::UpdParkingRGVStatusSRS(parkingNO, xMin, xMax, yMin, yMax);
		//}

//==============================================================================================================
//=====20220816 zhangyuhong add
//由于车辆扫描电文只返回车辆框架结果，不返回放料点结果，因此不需要发tag点通知，只需存入数据表即可，因此以下代码屏蔽
//==============================================================================================================
/*
		//向行车发送激光数据
		//tagName = EV_PARKING_SRS_CAR_INFO
		//tagValue = 行车号,指令号,激光扫描号,取放料标记（0-取料 1-放料  车辆是固定放料标记 1）,车扫描标志(1-RGV整车扫描 2-RGV分段扫描 3-卡车车辆扫描)，pointX，pointY，pointZ
		string craneNO = sdLU02SD["KEY_CraneNo"].toString();
		string strOrderNO = StringHelper::ToString(orderNO);
		//scanNO
		string scanType = "1";
		//scanRGVFlag 
		string strPointX = StringHelper::ToString(pointX);
		string strPointY = StringHelper::ToString(pointY);
		string strPointZ = StringHelper::ToString(pointZ);

		//当行车收到后，如果scanRGVFlag是
		//1. RGV整车扫描 ：行车模块写入scanNO到当前指令表,  并读取 UACS_PARKING_RGV_STATUS，获取RGV整车扫描数据，然后计算分段扫描区域 发送给parking模块再进行真正放料区域扫描
		//2. RGV分段扫描：行车模块写入scanNO到当前指令表,并将strPointXYZ 写入当前指令表
		//3. 卡车车辆扫描：行车模块写入scanNO到当前指令表,并将strPointXYZ 写入当前指令表
		string tagName = "EV_PARKING_SRS_CAR_INFO";
		string tagValue = craneNO + "," + strOrderNO + "," + scanNO + "," + scanType + "," + scanRGVFlag + ","+strPointX + "," + strPointY + "," + strPointZ;
		EVTagSnd(tagName, tagValue);
*/
		


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
		string errorMessage = stdex.what();
		string msg = functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;
}

bool	MsgLU02::MsgLU02Convert(string jsonStr, SmartData& sdJson)
{
	bool ret=false;
	string functionName="MsgLU02 :: MsgLU02Convert()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		bool bIsJsonStr = isJsonStr(jsonStr.c_str());
		if (!bIsJsonStr)
		{
			log.Info()<<"Receive From MsgLU02 Result String IS NOT Json format! Exit........."<<endl;
			return ret;
		}

		Json::Value root;
		Json::Reader reader;

		if (jsonStr !="{}" && reader.parse(jsonStr, root))
		{
			sdJson["KEY_CraneNo"] = root["KEY_CraneNo"].asString();//行车号
			sdJson["KEY_MessageNo"] = root["KEY_MessageNo"].asString();//事件号			
			sdJson["KEY_TreatmentNo"] = root["KEY_TreatmentNo"].asString();//处理号
			sdJson["KEY_ParkingNo"] = root["KEY_ParkingNo"].asString();//停车位号
			//车厢四个点坐标
			//第1个坐标
			sdJson["KEY_Boundary"][0]["KEY_PointX"] = root["KEY_Boundary"]["1"]["KEY_PointX"].asString();//X
			sdJson["KEY_Boundary"][0]["KEY_PointY"] = root["KEY_Boundary"]["1"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Boundary"][0]["KEY_PointZ"] = root["KEY_Boundary"]["1"]["KEY_PointZ"].asString();//Z
			//第2个坐标
			sdJson["KEY_Boundary"][1]["KEY_PointX"] = root["KEY_Boundary"]["2"]["KEY_PointX"].asString();//X
			sdJson["KEY_Boundary"][1]["KEY_PointY"] = root["KEY_Boundary"]["2"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Boundary"][1]["KEY_PointZ"] = root["KEY_Boundary"]["2"]["KEY_PointZ"].asString();//Z
			//第3个坐标
			sdJson["KEY_Boundary"][2]["KEY_PointX"] = root["KEY_Boundary"]["3"]["KEY_PointX"].asString();//X
			sdJson["KEY_Boundary"][2]["KEY_PointY"] = root["KEY_Boundary"]["3"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Boundary"][2]["KEY_PointZ"] = root["KEY_Boundary"]["3"]["KEY_PointZ"].asString();//Z
			//第4个坐标
			sdJson["KEY_Boundary"][3]["KEY_PointX"] = root["KEY_Boundary"]["4"]["KEY_PointX"].asString();//X
			sdJson["KEY_Boundary"][3]["KEY_PointY"] = root["KEY_Boundary"]["4"]["KEY_PointY"].asString();//Y
			sdJson["KEY_Boundary"][3]["KEY_PointZ"] = root["KEY_Boundary"]["4"]["KEY_PointZ"].asString();//Z

			sdJson["KEY_ResultState"] = root["KEY_ResultState"].asString();//计算成功/失败

			//准备打印所有数据
			string strstart = "\n========================Json String Convert Result========================";
			string str1 = "\n KEY_CraneNo:" + sdJson["KEY_CraneNo"].toString() + "\n KEY_MessageNo:" + sdJson["KEY_MessageNo"].toString();
			str1 += "\n KEY_TreatmentNo:" + sdJson["KEY_TreatmentNo"].toString() +"\n KEY_ParkingNo:" + sdJson["KEY_ParkingNo"].toString();
			str1 += "\n 1:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Boundary"][0]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Boundary"][0]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Boundary"][0]["KEY_PointZ"].toString();
			str1 += "\n 2:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Boundary"][1]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Boundary"][1]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Boundary"][1]["KEY_PointZ"].toString();
			str1 += "\n 3:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Boundary"][2]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Boundary"][2]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Boundary"][2]["KEY_PointZ"].toString();
			str1 += "\n 4:";
			str1 += "\n KEY_PointX:" + sdJson["KEY_Boundary"][3]["KEY_PointX"].toString();
			str1 += "\n KEY_PointY:" + sdJson["KEY_Boundary"][3]["KEY_PointY"].toString();
			str1 += "\n KEY_PointZ:" + sdJson["KEY_Boundary"][3]["KEY_PointZ"].toString();

			str1 += "\n KEY_ResultState:" + sdJson["KEY_ResultState"].toString(); 
			string strend = "\n=================================================================";
			string strall = strstart + str1 + strend;
			log.Info()<<strall<<endl;

			ret = true;
			return ret;

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

bool	MsgLU02::isJsonStr(const char *jsoncontent)
{
	std::stack<char> jsonstr;
	const char *p = jsoncontent;
	char startChar = jsoncontent[0];
	char endChar = '\0';
	bool isObject = false; //防止 {}{}的判断
	bool isArray = false;  //防止[][]的判断

	while (*p != '\0')
	{
		endChar = *p;
		switch (*p)
		{
		case '{':
			if (!isObject)
			{
				isObject = true;
			}
			else if (jsonstr.empty()) //对象重复入栈
			{
				return false;
			}
			jsonstr.push('{');
			break;
		case '"':
			if (jsonstr.empty() || jsonstr.top() != '"')
			{
				jsonstr.push(*p);
			}
			else
			{
				jsonstr.pop();
			}
			break;
		case '[':
			if (!isArray)
			{
				isArray = true;
			}
			else if (jsonstr.empty()) //数组重复入栈
			{
				return false;
			}
			jsonstr.push('[');
			break;
		case ']':
			if (jsonstr.empty() || jsonstr.top() != '[')
			{
				return false;
			}
			else
			{
				jsonstr.pop();
			}
			break;
		case '}':
			if (jsonstr.empty() || jsonstr.top() != '{')
			{
				return false;
			}
			else
			{
				jsonstr.pop();
			}
			break;
		case '\\': //被转义的字符,跳过
			p++;
			break;
		default:;
		}
		p++;
	}

	if (jsonstr.empty())
	{
		//确保是对象或者是数组,之外的都不算有效
		switch (startChar) //确保首尾符号对应
		{
		case '{':
			{
				if (endChar = '}')
				{
					return true;
				}
				return false;
			}
		case '[':
			{
				if (endChar = ']')
				{
					return true;
				}
				return false;
			}
		default:
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}


bool MsgLU02::EVTagSnd(string tagName, string tagValue)
{
	string functionName="MsgLU02 :: EVTagSnd()";
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

long MsgLU02::GetMax(long a, long b, long c, long d)
{
	string functionName="MsgLU02 :: GetMax()";
	LOG log(functionName, AUTO_CATCH_PID);
	long maxValue = a;
	try
	{
		if (b >maxValue)
		{
			maxValue = b;
		}
		if (c > maxValue)
		{
			maxValue = c;
		}
		if (d > maxValue)
		{
			maxValue = d;
		}
	}
	catch(...)
	{
		log.Debug()<<"GetMax  error..........."<<endl;
	}
	return maxValue;
}

long MsgLU02::GetMin(long a, long b, long c, long d)
{
	string functionName="MsgLU02 :: GetMin()";
	LOG log(functionName, AUTO_CATCH_PID);
	long minValue = a;
	try
	{
		if (b < minValue)
		{
			minValue = b;
		}
		if (c < minValue)
		{
			minValue = c;
		}
		if (d < minValue)
		{
			minValue = d;
		}
	}
	catch(...)
	{
		log.Debug()<<"GetMin  error..........."<<endl;
	}
	return minValue;
}