#include "tagUtility.h"

tagUtility::tagUtility(void)
{

}

tagUtility::~tagUtility(void)
{

}


//д�ڲ�Tag��ĺ���
void tagUtility::setL2Tag(string strTagName,string strTagValue)
{
	LOG log("tagUtility::setL2Tag");
	try
	{
		iPlature::TAGVALUEMAP tagPairs;

		log.Debug()<<"дL2tag��:"<<strTagName<<"    ֵ:"<<strTagValue<<endl;

		Tag::GetInst().EventPut(tagPairs,strTagName,strTagValue);
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

		string msg = "error: tagUtility::setL2Tag" + x.ErrMsg();
		log.Debug()<<endl<<msg<<endl;
	}
	catch (...)
	{

	}
}