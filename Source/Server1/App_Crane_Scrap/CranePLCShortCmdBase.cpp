#include "CranePLCShortCmdBase.h"

using namespace Monitor;


//--------------------------------------------------�´�PLCϵͳ�ĳ�ʼֵ�趨----------------------------------------------------------------
//����ͣ��
const long CranePLCShortCmdBase::SHORT_CMD_NORMAL_STOP=100;
//��ͣ
const long CranePLCShortCmdBase::SHORT_CMD_EMG_STOP=200;
////��λ
const long CranePLCShortCmdBase::SHORT_CMD_RESET=300;
//Ҫ�������Զ�
const long CranePLCShortCmdBase::SHORT_CMD_ASK_COMPUTER_AUTO=400;
//Ҫ��ȡ��������Զ�
const long CranePLCShortCmdBase::SHORT_CMD_CANCEL_COMPUTER_AUTO=500;
//---------------------------------------------------------------------------------------------------------------------------------------------------


CranePLCShortCmdBase :: CranePLCShortCmdBase(void)
{

	initValues();
}



CranePLCShortCmdBase :: ~CranePLCShortCmdBase(void)
{
	
}


void CranePLCShortCmdBase :: initValues()
{
	//1 CRANE_NO
	craneNO=DB_STR_NULL;

	//2 cmdCode
	cmdCode=SHORT_CMD_CANCEL_COMPUTER_AUTO;

}

//1 craneNO
string CranePLCShortCmdBase :: getCraneNO()
{
	return craneNO;
}
void CranePLCShortCmdBase :: setCraneNO(string theVal)
{
	craneNO=theVal;
}

//2 cmdCode
long CranePLCShortCmdBase :: getCmdCode()
{
	return cmdCode;
}
void CranePLCShortCmdBase :: setCmdCode(long theVal)
{
	cmdCode=theVal;
}



void CranePLCShortCmdBase :: logOutValues()
{
	string functionName="CranePLCShortCmdBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class CranePLCShortCmdBase--------------------------------------"<<endl;
	//1
	log.Debug()<<"\t craneNO="<<craneNO;
	//2
	log.Debug()<<"\t cmdCode="<<cmdCode<<endl;

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;

	
}