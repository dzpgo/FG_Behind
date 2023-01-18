/*********************************************************************
 *		
 *  ��      ��:    SafetyArea_Bay.h   		
 *
 *
 *  ������
 *        ��SafetyArea_Bay Ϊ�����࣬һ����һ������
 *        ��Map<long, Area����>�ĺӰ�������򼯺�
 *        ��Map<long, Area����>�ĺӰ��Ҳ����򼯺�
 *        ��Vector< Area����>�ĺӰ�������򼯺�
 *        ��Vector<Area����>�ĺӰ��Ҳ����򼯺�
 *        �������Ķ���
 *  �汾��ʷ		
 *      2017��04�½���
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
				//��������
				SafetyArea_Bay(void);
				//��������
				~SafetyArea_Bay(void);

		private:
				//��������ָ��
				static SafetyArea_Bay*	m_pSafetyArea_Bay;

		public:
				//���ָ��ķ���
				static  SafetyArea_Bay*  getInstance(void);


		public:
			//��ȡXML�ļ��ķ���
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
			//��ȫ�����Map
			map<string,SafteyAreaBase> mapSafteyAreas;

			//2018.12.16 zhangyuhong add
			//map<����ļ���X����, ����X����>    <A1_X_MIN, 111111>
			map<string, long> mapAreaXMinMax;

			//20190730 zhangyuhong add
			////���ӹ�PA2�������  Ŀ�ģ����������г�ͣ5����ͨ��
			//��C2C��������PA2���ŵ���C1B������ �������ĵȴ������
			map<string, long> mapPA02_SP_MIN_X_PT;
			//��C175���ھ���PA2���ŵ���C2C������ �������ĵȴ������
			map<string, long> mapPA02_SP_MAX_X_PT;

			
			//ͨ����������ƻ������Ķ���
			bool getAreaByName(string theAreaName, SafteyAreaBase& safteyAreaBase);

			//��ȫ�����Vector
			vector<SafteyAreaBase>vectorSafteyAreas;

			TAGNAMEARRAY	arryTagNameSafeDoor;

			


		
		private:
			//��XML�ж�ȡ�����������ݱ��浽�������ķ���
			void InputSafteyArea(SafteyAreaBase  safteyAreaBase);

			//2018.12.14
			//����ȫ�ŵ�tag����ѹ�����������
			void InputTagNameSafeDoor();

			//2018.12.16 zhangyuhong add
			void InputAreaXMinXax(map<string,SafteyAreaBase> mapSafteyAreas);

			//2019.7.30 zhangyuhong add
			void InputPA2SPXPT();


			


		
		public:
			//��ӡ�������е�����
			void logOutValues();



		public:

			 //����仯���������Ǳ���Ǳ�С
			 const static string TREND_INC;
			 const static string TREND_DES;

			 //�����ַ��������
			 const static string LEFT;
			 const static string RIGHT;




		private:
			//ͨ��ֱ������֪��������������ֱ�߲����ĺ���
			void getRouteParameter(long x1, long y1, long x2, long y2, float& k, float& b);

			//����������յ�ĺ�������ͼ�ҵ� �ܷ񵽴��յ�  ����  ��һ���谭�ҵ�����  
			//����ֵ=true��ʾ����ֱ�ӵ���Ŀ��
			//����ֵ=false��ʾ����ֱ��Ŀ��
			bool shotToDestination(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit);

			//2019.4.7 zhangyuhong add
			// > 50 �� ���߷���
			bool shotMethod1(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit);
			// <= 50 �����߷���
			bool shotMethod2(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea,long& xCanGoLimit, long& yCanGoLimit);


			//����x y���ж�������Ƿ�������һ�����
			bool isPointInAnyReadArea(long x, long y, SafteyAreaBase& safteyAreaBase);

		private:
			void sortTwoNum(long numberA,long numberB,long& theMin, long& theMax);

		private:


			//�������������յ����꣬Ѱ�ҽ����Ƽ����������λ�ã���ǰ���������⣬����λ��Xȡ�˶������ϵ�һ���ߵ�X �� Yȥ����Y�����Ҷ�X���в�����Ҫ�����������
			//                                                                                                                     ������������ڣ��뿪λ��Xȡ�˶����������һ�����X��Y���ֵ�ǰY���䣬���Ҷ�X���в�����Ҫ���뿪������
			void getRelatedPosForRecommendArea(long x, long y,long xEnd, long yEnd, SafteyAreaBase recommendArea , long& xPosRelated, long& yPosRelated);
	

		public:

			//2018.12.16 ZHANGYUHONG ADD
			//����ֵ=true��ʾ����ֱ�ӵ���Ŀ��
			//����ֵ=false��ʾ����ֱ��Ŀ��
			bool shotToDestination_2(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea);

			//���㵥��·���ĺ���
			void arrangeSingStep(long x, long y, long xTarget, long yTarget, bool canMoveNextStep,long& xNextStep, long& yNextSetp,bool& reachTarget, bool& startInRed);

		public:
			//����㵽�յ������·���Ĺ滮�������ᷴ��һϵ�е�·���㣬����ܵ���Ŀ�꣬��ô���һ��·�������ϱ�־
			void arrangeRoute(long x, long y, long xTarget, long yTarget , vector<RouteStepPointBase>& vectorRoutePoints, bool& startInRed);

		//2018.5.9  zhangyuhong add
		//��ȡXML��ȫ�������ļ��е�map<name, SafteyAreaBase>
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
			//��ȡ�������ŵ���2������㣬�ȴ���
			map<string, long> getMapPA2SpMinPT();
			map<string, long> getMapPA2SpMaxPT();


			//20190909 zhangyuhong add
			//����x y���ж�������Ƿ�������һ�����
			bool isPointInAnyReadArea2(long x, long y, SafteyAreaBase& safteyAreaBase);


			//2018.8.3 zhangyuhong add
		public:

			bool  isPointInAnyReadAreaNew(long x, long y);

			bool shotMethodGet1stRedArea(long xStart, long yStart, long xEnd, long yEnd,SafteyAreaBase& firstBlockArea );

			//ͨ����������ƻ������Ķ���
			bool getAreaByNameNew(string theAreaName, SafteyAreaBase& safteyAreaBase);

			//20200117 zhangyuhong add
			bool getAreaByPosXY(long x, long y, SafteyAreaBase& safteyAreaBase);


		};




}
#endif