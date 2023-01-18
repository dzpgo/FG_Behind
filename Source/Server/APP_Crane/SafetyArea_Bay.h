/*********************************************************************
 *		
 *  文      件:    SafetyArea_Bay.h   		
 *
 *
 *  概述：
 *        ：SafetyArea_Bay 为单例类，一个跨一个对象
 *        ：Map<long, Area对象>的河岸左侧区域集合
 *        ：Map<long, Area对象>的河岸右侧区域集合
 *        ：Vector< Area对象>的河岸左侧区域集合
 *        ：Vector<Area对象>的河岸右侧区域集合
 *        ：河流的对象
 *  版本历史		
 *      2017年04月建立
*********************************************************************/
#pragma once
#ifndef _SafetyArea_Bay_
#define _SafetyArea_Bay_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "tinyxml.h" 

#include "SafteyAreaBase.h"
#include "RouteStepPointBase.h"

#include "ACTION_COMMON_FUNCTION.h"

//#include "SafeAreaDoorBase.h"

namespace Monitor
{



		class SafetyArea_Bay
		{


		public:
				//构造行数
				SafetyArea_Bay(void);
				//析构函数
				~SafetyArea_Bay(void);

		private:
				//单例函数指针
				static SafetyArea_Bay*	m_pSafetyArea_Bay;

		public:
				//获得指针的方法
				static  SafetyArea_Bay*  getInstance(void);


		public:
			//读取XML文件的方法
			bool ReadFromXML(string theFilePath);
	

		//1 xMinInBay
		private:
			long xMinInBay;
		public:
			long getXMinInBay();
			void setXMinInBay(long theVal);

		//2 xMaxInBay
		private:
			long xMaxInBay;
		public:
			long getXMaxInBay();
			void setXMaxInBay(long theVal);

		//3 yMinInBay
		private:
			long yMinInBay;
		public:
			long getYMinInBay();
			void setYMinInBay(long theVal);

		//4 xMaxInBay
		private:
			long yMaxInBay;
		public:
			long getYMaxInBay();
			void setYMaxInBay(long theVal);

		
		private:
			//安全区域的Map
			map<string,SafteyAreaBase> mapSafteyAreas;

			//2018.12.16 zhangyuhong add
			//map<区域的极限X名称, 极限X数据>    <A1_X_MIN, 111111>
			map<string, long> mapAreaXMinMax;

			//20190730 zhangyuhong add
			////增加过PA2的特殊点  目的：到特殊点后，行车停5秒再通过
			//从C2C库区经过PA2龙门吊往C1B库区走 ，经过的等待特殊点
			map<string, long> mapPA02_SP_MIN_X_PT;
			//从C175出口经过PA2龙门吊往C2C库区走 ，经过的等待特殊点
			map<string, long> mapPA02_SP_MAX_X_PT;

			
			//通过区域的名称获得区域的对象
			bool getAreaByName(string theAreaName, SafteyAreaBase& safteyAreaBase);

			//安全区域的Vector
			vector<SafteyAreaBase>vectorSafteyAreas;

			TAGNAMEARRAY	arryTagNameSafeDoor;

			


		
		private:
			//将XML中读取到的区域数据保存到本身对象的方法
			void InputSafteyArea(SafteyAreaBase  safteyAreaBase);

			//2018.12.14
			//将安全门的tag名称压到自身对象中
			void InputTagNameSafeDoor();

			//2018.12.16 zhangyuhong add
			void InputAreaXMinXax(map<string,SafteyAreaBase> mapSafteyAreas);

			//2019.7.30 zhangyuhong add
			void InputPA2SPXPT();


			


		
		public:
			//打印本对象中的数据
			void logOutValues();



		public:

			 //坐标变化的描述，是变大还是变小
			 const static string TREND_INC;
			 const static string TREND_DES;

			 //左右手方向的描述
			 const static string LEFT;
			 const static string RIGHT;




		private:
			//通过直线上已知的两个点来推算直线参数的函数
			void getRouteParameter(long x1, long y1, long x2, long y2, float& k, float& b);

			//从起点射向终点的函数，试图找到 能否到达终点  或者  第一个阻碍我的区域  
			//返回值=true表示可以直接到达目标
			//返回值=false表示不能直达目标
			bool shotToDestination(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit);

			//2019.4.7 zhangyuhong add
			// > 50 的 射线方法
			bool shotMethod1(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit);
			// <= 50 的射线方法
			bool shotMethod2(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit);


			//按照x y，判断这个点是否落入了一个红块
			bool isPointInAnyReadArea(long x, long y, SafteyAreaBase& safteyAreaBase);

		private:
			void sortTwoNum(long numberA,long numberB,long& theMin, long& theMax);

		private:


			//按照起点坐标和终点坐标，寻找进入推荐区域的坐标位置，当前车在区域外，进入位置X取运动方向上第一条边的X ， Y去进入Y，并且对X进行补偿，要求侵入该区域
			//                                                                                                                     如果车在区域内，离开位置X取运动方向上最后一条表的X，Y保持当前Y不变，并且对X进行补偿，要求离开该区域
			void getRelatedPosForRecommendArea(long x, long y,long xEnd, long yEnd, SafteyAreaBase recommendArea , long& xPosRelated, long& yPosRelated);
	

		public:

			//2018.12.16 ZHANGYUHONG ADD
			//返回值=true表示可以直接到达目标
			//返回值=false表示不能直达目标
			bool shotToDestination_2(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea);

			//计算单步路径的函数
			void arrangeSingStep(long x, long y, long xTarget, long yTarget, bool canMoveNextStep,long& xNextStep, long& yNextSetp,bool& reachTarget, bool& startInRed);

		public:
			//从起点到终点的整个路径的规划函数，会反馈一系列的路径点，如果能到达目标，那么最后一个路径点会打上标志
			void arrangeRoute(long x, long y, long xTarget, long yTarget , vector<RouteStepPointBase>& vectorRoutePoints, bool& startInRed);

		//2018.5.9  zhangyuhong add
		//获取XML安全区配置文件中的map<name, SafteyAreaBase>
		public:
			map<string, SafteyAreaBase> getMapSafeAreaBase();
			vector<SafteyAreaBase> getVecSafeAreaBase();
			void	setVecSafeAreaBase(vector<SafteyAreaBase> theValue);

			//20190704 zhangyuhong
			void	setMapSafeAreaBase(map<string , SafteyAreaBase> mapSafeyAreas);

			//2018.12.14 zhangyuhong add
			TAGNAMEARRAY getArrayTagNameSafeDoor();

			map<string, long> getMapAreaXMinMax();

			//20190730 zhangyuhong add
			//获取经过龙门吊的2个特殊点，等待点
			map<string, long> getMapPA2SpMinPT();
			map<string, long> getMapPA2SpMaxPT();


			//20190909 zhangyuhong add
			//按照x y，判断这个点是否落入了一个红块
			bool isPointInAnyReadArea2(long x, long y, SafteyAreaBase& safteyAreaBase);


			//2018.8.3 zhangyuhong add
		public:

			bool  isPointInAnyReadAreaNew(long x, long y);

			bool shotMethodGet1stRedArea(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea );

			//通过区域的名称获得区域的对象
			bool getAreaByNameNew(string theAreaName, SafteyAreaBase& safteyAreaBase);

			//20200117 zhangyuhong add
			bool getAreaByPosXY(long x, long y, SafteyAreaBase& safteyAreaBase);


		};




}
#endif