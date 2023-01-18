#include "tagUtility.h"

tagUtility::tagUtility(void)
{

}

tagUtility::~tagUtility(void)
{

}


//写内部Tag点的函数
void tagUtility::setL2Tag(string strTagName,string strTagValue)
{
	LOG log("tagUtility::setL2Tag");
	try
	{
		iPlature::TAGVALUEMAP tagPairs;

		log.Debug()<<"写L2tag点:"<<strTagName<<"    值:"<<strTagValue<<endl;

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