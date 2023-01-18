#include "ACTION_CHECK_BEFORE_EVADE.h"

using namespace Monitor;



ACTION_CHECK_BEFORE_EVADE :: ACTION_CHECK_BEFORE_EVADE(void)
{

}



ACTION_CHECK_BEFORE_EVADE :: ~ACTION_CHECK_BEFORE_EVADE(void)
{
	


}



//1 doAction
bool ACTION_CHECK_BEFORE_EVADE :: doAction(string craneNO, 
																string bayNO,
																CraneEvadeRequestBase craneEvadeRequest, 
																CranePLCStatusBase cranePLCStatus)
{
	//�ٶ�Ϊ������������ͬ������
	bool ret=false;

	string functionName="ACTION_CHECK_BEFORE_EVADE :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool retject=true;
	try
	{

			log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
			log.Debug()<<" --------------------------------- ACTION_CHECK_BEFORE_EVAD-----------------------------"<<endl;
			log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

			log.Debug()<<"craneNO="<<craneNO<<"   bayNO="<<bayNO<<"  hasCoil="<< cranePLCStatus.getHasCoil()<<"   XAct="<<cranePLCStatus.getXAct()<<"   YAct="<<cranePLCStatus.getYAct()<<endl;

			/*if(craneNO=="3_1")
			{
				retject=RejectconditionEvade_C1A::isRejceted( craneNO, craneEvadeRequest.getEvadeDirection(),  cranePLCStatus.getHasCoil() , cranePLCStatus.getXAct(), cranePLCStatus.getYAct());
			}
			if(craneNO=="3_2")
			{
				retject=RejectconditionEvade_C1A::isRejceted( craneNO, craneEvadeRequest.getEvadeDirection(),  cranePLCStatus.getHasCoil() , cranePLCStatus.getXAct(), cranePLCStatus.getYAct());
			}*/
			/*if(craneNO=="4_2")
			{
				retject=RejectconditionEvade_Z32::isRejceted( craneNO, craneEvadeRequest.getEvadeDirection(),  cranePLCStatus.getHasCoil() , cranePLCStatus.getXAct(), cranePLCStatus.getYAct());
			}			
			if(craneNO=="4_3")
			{
				retject=RejectconditionEvade_Z32::isRejceted( craneNO, craneEvadeRequest.getEvadeDirection(),  cranePLCStatus.getHasCoil() , cranePLCStatus.getXAct(), cranePLCStatus.getYAct());
			}

			if(craneNO=="4_4")
			{
				retject=RejectconditionEvade_Z33::isRejceted( craneNO, craneEvadeRequest.getEvadeDirection(),  cranePLCStatus.getHasCoil() , cranePLCStatus.getXAct(), cranePLCStatus.getYAct());
			}
			if(craneNO=="4_5")
			{
				retject=RejectconditionEvade_Z33::isRejceted( craneNO, craneEvadeRequest.getEvadeDirection(),  cranePLCStatus.getHasCoil() , cranePLCStatus.getXAct(), cranePLCStatus.getYAct());
			}*/

			log.Debug()<<"�����ö���Evade֮ǰ�ļ��������ֵ ret="<<ret<<endl;
			if(retject==false)
			{
				ret=true;
			}
			//2017.12.21 zhangyuhong add
			//��Ҫ����C612ǰ��� 3-1  3-2�ľ����г����ù���
			//��ʱ������  Ĭ�ϲ��ñ���
			/*log.Debug()<<" ���Խ׶Σ���ʱ��3-1 3-2�ı��ù��򣬷���true��"<<endl;
			ret = true;*/
			
			return ret;

	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}
