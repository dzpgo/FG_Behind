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

//�г���
string CranePLCStatusPhototAlbum :: getCraneNO()
{
	return craneNO;
}
void CranePLCStatusPhototAlbum :: setCraneNO( string theVal)
{
	craneNO=theVal;
}

//���������������־λ�ķ���
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



//�������Ƭ�ķ���
CranePLCStatusBase CranePLCStatusPhototAlbum :: getCranePLCStatusNew()
{
	return cranePLCStatusNew;
}

//�������Ƭ�ķ���
CranePLCStatusBase CranePLCStatusPhototAlbum :: getCranePLCStatusOld()
{
	return cranePLCStatusOld;
}

//���ⲿ��������Ƭ�����
//�ⲿ��ֵ���κ�������
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
			//����Ƭ�Ѿ�OK������Ƭ��û��OK����ô���θ�ֵ֮������ƬOK��
			if(oldPhotoOK==true && newPhotoOK==false){ newPhotoOK=true;}
			//����Ƭû��OK����ô���θ�ֵ������ƬOK��
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


