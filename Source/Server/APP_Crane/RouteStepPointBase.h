/*********************************************************************
 *		
 *  ��      ��:    RouteStepPointBase.h   		
 *
 *
 *  ������
 *        ��RouteStepPointBase �ǵ�����
 *        �������г�����·�ߵ�һ����
 *        ���������� X  Y  ���Ƿ񵽴�Ŀ�ĵر�־   ע�⣺·���㲻���г���Z���Ƿ��乳������ZҪ���س����Լ�����
 *  �汾��ʷ		
 *      2017��04�½���
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