/*********************************************************************
 *		
 *  文      件:    SafteyAreaBase.h   		
 *
 *
 *  概述：
 *        ：SafteyAreaBase 非单例类
 *        ：定义跨内一个区域，这个区域包括区域名字
 *        ：坐标的范围和安全点的地址，外部登录时候小车Y，以及本块不能通过时的推荐人
 *  版本历史		
 *      2017年04月建立
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
	
		//本块是否为红跨的关键函数
		public:
			bool isRead();

		public:
			void  logOutValues();

	
	

		};




}
#endif