#include "SafteyAreaBase.h"

using namespace Monitor;



SafteyAreaBase :: SafteyAreaBase(void)
{

	initValues();
}



SafteyAreaBase :: ~SafteyAreaBase(void)
{
	


}

void SafteyAreaBase :: initValues()
{
	
	//1 name
	name=DB_STR_NULL;

	//2 XMin
	xMin=DB_INT_NULL;

	//3 XMax
	xMax=DB_INT_NULL;

	//4 YMin
	yMin=DB_INT_NULL;

	//5 YMax
	yMax=DB_INT_NULL;

	//6 AlwaysForbid
	alwaysForbid=DB_INT_NULL;

	//7 safeTag
	safeTag=DB_STR_NULL;

	//8 OnBordY
	onBordY=DB_INT_NULL;

	//9 RecommendArea1
	recommendArea1=DB_STR_NULL;

	//10 RecommendArea2
	recommendArea2=DB_STR_NULL;
}



//1 name
string SafteyAreaBase :: getName()
{
	return name;
}
void SafteyAreaBase :: setName(string theVal)
{
	name=theVal;
}

//2 xMin
long SafteyAreaBase :: getXMin()
{
	return xMin;
}
void SafteyAreaBase :: setXMin(long theVal)
{
	xMin=theVal;
}

//3 xMax
long SafteyAreaBase :: getXMax()
{
	return xMax;
}
void SafteyAreaBase :: setXMax(long theVal)
{
	xMax=theVal;
}

//4 yMin
long SafteyAreaBase :: getYMin()
{
	return yMin;
}
void SafteyAreaBase :: setYMin(long theVal)
{
	yMin=theVal;
}

//5 YMax
long SafteyAreaBase :: getYMax()
{
	return yMax;
}
void SafteyAreaBase :: setYMax(long theVal)
{
	yMax=theVal;
}

//6 AlwaysForbid
long SafteyAreaBase :: getAlwaysForbid()
{
	return alwaysForbid;
}
void SafteyAreaBase :: setAlwaysForbid(long theVal)
{
	alwaysForbid=theVal;
}

//7 safeTag
string SafteyAreaBase :: getSafeTag()
{
	return safeTag;
}
void SafteyAreaBase :: setSafeTag(string theVal)
{
	safeTag=theVal;
}


//8 OnBordY
long SafteyAreaBase :: getOnBordY()
{
	return onBordY;
}
void SafteyAreaBase :: setOnBordY(long theVal)
{
	onBordY=theVal;
}

//9 RecommendArea1
string SafteyAreaBase :: getRecommendArea1()
{
	return recommendArea1;
}
void SafteyAreaBase :: setRecommendArea1(string theVal)
{
	recommendArea1=theVal;
}

//10 RecommendArea2
string SafteyAreaBase :: getRecommendArea2()
{
	return recommendArea2;
}
void SafteyAreaBase :: setRecommendArea2(string theVal)
{
	recommendArea2=theVal;
}

//11
long SafteyAreaBase :: getSafeTagValue()
{
	return 1;
}

bool SafteyAreaBase :: isRead()
{
	if(alwaysForbid==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void SafteyAreaBase :: logOutValues()
{
	string functionName="SafteyAreaBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class SafteyAreaBase--------------------------------------"<<endl;

	//1
	log.Debug()<<"\t name="<<name;
	//2
	log.Debug()<<"\t xMin="<<xMin;
	//3
	log.Debug()<<"\t xMax="<<xMax;
	//4
	log.Debug()<<"\t yMin="<<yMin;
	//5
	log.Debug()<<"\t yMax="<<yMax;
	//6
	log.Debug()<<"\t alwaysForbid="<<alwaysForbid;
	//7
	log.Debug()<<"\t safeTag="<<safeTag;
	//8
	log.Debug()<<"\t onBordY="<<onBordY;
	//9
	log.Debug()<<"\t recommendArea1="<<recommendArea1;
	//10
	log.Debug()<<"\t recommendArea2="<<recommendArea2<<endl;

	

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;

	
}
