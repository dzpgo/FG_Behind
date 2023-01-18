
//��������Ŀ���ϸ���� MsgWG01
#include "MsgWG01.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "SQL4Parking.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgWG01::MsgWG01(void)
{
	m_strMsgId = "WG01";
}

MsgWG01::~MsgWG01(void)
{

}

void MsgWG01::HandleMessage(const string strValue)
{
	string functionName="MsgWG01::HandleMessage";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		log.Info()<<"WG01 send handle start.............."<<endl;
		//strValue��ʽ��
		//���� ,Ŀ���ϸ���,��ҵ����
		//carno,targetgridno,worktype
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 3)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string carNO = kValues[0];
		string targetGridNO = kValues[1];
		string workType = kValues[2];

		log.Info()<<"WG01 data: carNO = "<<carNO<<" , targetGridNO = "<<targetGridNO<<" , workType = "<<workType<<endl;

		//��֯�������ݵ��ĸ�ʽ
		string sndTel = m_strMsgId + "," + carNO + "," + targetGridNO + ","  + workType;

		ArrayMsg arrayMsgDataBuf;
		for (int i = 0; i < sndTel.length(); i ++)
		{
			arrayMsgDataBuf.push_back(*(sndTel.c_str() + i));
		}
		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//����ʵ������趨ͨ�Ż��ߺ�
		int lineNO = 0;
		if (false == SQL4Parking::SelComLineNO("GRID", lineNO))
		{
			log.Info()<<"GRID  lineNO  SelComLineNO is ERROR......return false.........."<<endl;
			return;
		}

		int ret = PCS_Send(lineNO, m_strMsgId, arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;
		log.Info()<<endl<<"WG01 sended out ............ "<<endl;
	}
	catch (std::exception& ex)
	{
		log.Info()<<endl<<"WG01 sended error .............. "<<endl;
	}
	catch (...)
	{
		log.Info()<<endl<<"WG01 sended error ............ "<<endl;
	}
}
