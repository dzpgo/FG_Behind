/*********************************************************************
 *		
 *  ��      ��:    SafteyAreaBase.h   		
 *
 *
 *  ������
 *        ��SafteyAreaBase �ǵ�����
 *        ���������һ������������������������
 *        ������ķ�Χ�Ͱ�ȫ��ĵ�ַ���ⲿ��¼ʱ��С��Y���Լ����鲻��ͨ��ʱ���Ƽ���
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/
#pragma once
#ifndef _SafteyAreaBase_
#define _SafteyAreaBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>



namespace Monitor
{



		class SafteyAreaBase
		{


		public:
				SafteyAreaBase(void);

				~SafteyAreaBase(void);

		private:
			    void initValues();
	


		//1 name
		private:
			string name;
		public:
			string getName();
			void   setName(string theVal);

		//2 XMin
		private:
			long xMin;
		public:
			long getXMin();
			void setXMin(long theVal);

		//3 XMax
		private:
			long xMax;
		public:
			long getXMax();
			void setXMax(long theVal);

		//4 YMin
		private:
			long yMin;
		public:
			long getYMin();
			void setYMin(long theVal);

		//5 YMax
		private:
			long yMax;
		public:
			long getYMax();
			void setYMax(long theVal);

		//6 AlwaysForbid
		private:
			long alwaysForbid;
		public:
			long getAlwaysForbid();
			void setAlwaysForbid(long theVal);

		//7 safeTag
		private:
			string safeTag;
		public:
			string getSafeTag();
			void setSafeTag(string theVal);
		
		//8 OnBordY
		private:
			long onBordY;
		public:
			long getOnBordY();
			void setOnBordY(long theVal);

		//9 RecommendArea1
		private:
			string recommendArea1;
		public:
			string getRecommendArea1();
			void setRecommendArea1(string theVal);

		//10 RecommendArea2
		private:
			string recommendArea2;
		public:
			string getRecommendArea2();
			void setRecommendArea2(string theVal);

		// getSafeTagValue
		public:
			long getSafeTagValue();
	
		//�����Ƿ�Ϊ���Ĺؼ�����
		public:
			bool isRead();

		public:
			void  logOutValues();

	
	

		};




}
#endif