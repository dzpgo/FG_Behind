#include "CranePLCStatusPhototAlbum.h"

using namespace Monitor;


CranePLCStatusPhototAlbum :: CranePLCStatusPhototAlbum(void)
{
		newPhotoOK=false;
		oldPhotoOK=false;
}



CranePLCStatusPhototAlbum :: ~CranePLCStatusPhototAlbum(void)
{
	


}

//行车号
string CranePLCStatusPhototAlbum :: getCraneNO()
{
	return craneNO;
}
void CranePLCStatusPhototAlbum :: setCraneNO( string theVal)
{
	craneNO=theVal;
}

//获得整个相册就绪标志位的方法
bool CranePLCStatusPhototAlbum :: getPhtotAlbumOK()
{
	if(oldPhotoOK==true && newPhotoOK==true)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//获得新照片的方法
CranePLCStatusBase CranePLCStatusPhototAlbum :: getCranePLCStatusNew()
{
	return cranePLCStatusNew;
}

//获得老照片的方法
CranePLCStatusBase CranePLCStatusPhototAlbum :: getCranePLCStatusOld()
{
	return cranePLCStatusOld;
}

//从外部接收新照片的入口
//外部赋值两次后，相册就绪
void CranePLCStatusPhototAlbum :: inputPLCStatus(CranePLCStatusBase cranePLCStatusBase)
{
	string functionName="CranePLCStatusPhototAlbum :: inputPLCStatus()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
			if(cranePLCStatusBase.getCraneNO()!=craneNO)
			{
				return;
			}
			//老照片已经OK，新照片还没有OK，那么本次赋值之后新照片OK了
			if(oldPhotoOK==true && newPhotoOK==false){ newPhotoOK=true;}
			//老照片没有OK，那么本次赋值后老照片OK了
			if(oldPhotoOK==false){oldPhotoOK=true;}

			cranePLCStatusOld=cranePLCStatusNew;
			cranePLCStatusNew=cranePLCStatusBase;

			log.Debug()<<"photos updated in the Album,  the CraneNO of the Album="<<cranePLCStatusBase.getCraneNO()<<" the flag oldPhotoOK="<<oldPhotoOK<<"   the flag newPhotoOK="<<newPhotoOK<<endl;

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

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
	}
    catch (std::exception& stdex)
    {
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
    }
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

}


