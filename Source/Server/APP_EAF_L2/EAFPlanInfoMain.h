/*********************************************************************
*		
*  ��      ��:    EAFPlanInfoMain.h   		
*
*
*********************************************************************/
#pragma once
#ifndef _EAFPlanInfoMain_
#define _EAFPlanInfoMain_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include <tag/Tag.h>

namespace Monitor
{
	class EAFPlanInfoMain
	{

	public:
		EAFPlanInfoMain(void);

		~EAFPlanInfoMain(void);

	private:
		void initValues();

		//1 PONO 
	private:
		string pono;
	public:
		string getPono();
		void   setPono(string theVal);

		//2 HTNO
	private:
		string htno;
	public:
		string getHtno();
		void setHtno(string theVal);

		//3 RECIPE_TYPE
	private:
		string recipeType;
	public:
		string getRecipeType();
		void setRecipeType(string theVal);

		//4 STEELGRADE
	private:
		string steelGrade;
	public:
		string getSteelGrade();
		void setSteelGrade(string theVal);

		//5 TAP_TIME
	private:
		iDA::DateTime tapTime;
	public:
		iDA::DateTime getTapTime();
		void setTapTime(iDA::DateTime theVal);

		//6 PLAN_SRC
	private:
		string planSrc;
	public:
		string getPlanSrc();
		void setPlanSrc(string theVal);

	public:
		void logOutValues();

		//recipeType
		const static string RECIPE_TYPE_ADD;//���� 1
		const static string RECIPE_TYPE_MODIFY;//�޸� 2
		const static string RECIPE_TYPE_DELETE;//ɾ�� 3

		//planSrc
		const static string PLAN_SRC_NEW_EAF;//�µ�¯
		const static string PLAN_SRC_OLD_EAF;//�ϵ�¯

		
		

		
	};




}
#endif