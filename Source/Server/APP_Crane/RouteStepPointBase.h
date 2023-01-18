/*********************************************************************
 *		
 *  文      件:    RouteStepPointBase.h   		
 *
 *
 *  概述：
 *        ：RouteStepPointBase 非单例类
 *        ：定义行车走行路线的一个点
 *        ：坐标点包括 X  Y  和是否到达目的地标志   注意：路径点不对行车的Z（是否落钩）负责，Z要主控程序自己负责
 *  版本历史		
 *      2017年04月建立
*********************************************************************/
#pragma once
#ifndef _RouteStepPointBase_
#define _RouteStepPointBase_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>



namespace Monitor
{



		class RouteStepPointBase
		{


		public:
				RouteStepPointBase(void);

				~RouteStepPointBase(void);

		private:
			    void initValues();
	


		//1 x
		private:
			long x;
		public:
			long getX();
			void   setX(long theVal);

		//2 y
		private:
			long y;
		public:
			long getY();
			void setY(long theVal);

		//3 flagReachFinalTarget
		private:
			bool flagReachFinalTarget;
		public:
			bool getFlagReachFinalTarget();
			void setFlagReachFinalTarget(bool theVal);

		public:
			void  logOutValues();

	
	

		};




}
#endif