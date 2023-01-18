#pragma once
#ifndef _SQL4Order_
#define _SQL4Order_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "CarPlanBandInfo.h"
#include "EventParkingHandler.h"

using namespace Monitor;

namespace Monitor
{

	//���eaf�ƻ���Ƶ�ȡ��map���� map<���, vectro<�ϸ��, ���ϴ���, ȡ����>>
	typedef map< long, vector<string> > MapGridMatWgtEAF;


	class SQL4Order
	{
	public:
		SQL4Order(void);
		~SQL4Order(void);

		//��ѯ������� ͨ��DB2����sequence
		static bool SelOrderGroupNO(long& orderGroupNO);

		static bool SelOrderNO(long& orderNO);

		//��ѯָ�����Ͷ�������ȼ�
		static bool SelOrderPriority(string orderType, long& orderPriority);


		//��ѯ�����ƻ�����Ϣ
		static bool SelCarPlanBandInfo(string carNO, string workType, CarPlanBandInfo& carPlanBandInfoBase);

		//���ݳ��ƺŲ�ѯ�����ƻ��󶨱���ENTER_FLAG=2�ļ�¼������У�����true
		static bool CarEnterYardExist(string carNO);

		//���ݳ��ƺŲ�ѯ�����ƻ��󶨱���ORDER_FLAG=2�ļ�¼������У�����true
		static bool CarOrderFlagExist(string carNO, string workType);

		//��ѯL3�ƻ����Դ��ķϸִ����Ҫ������(�����ж�ϣ�reqWgt������)
		static bool SelScrapCodeReqWgtFormL3(string planNO, 
																					string workType, //L3��ж��XL����װ��ZC
																					string& locCode, //L3�������ϸ��
																					string& scrapCode, 
																					string& compCode, 
																					long& reqWgt);

		//��ѯ��¯L2�ƻ����Դ��ķϸִ����Ҫ������
		static bool SelScrapCodeReqWgtFromEAF(string planNO, 
																						long planDetailID, 
																						string& scrapCode, 
																						long& reqWgt);

		//��ѯת¯L2�ƻ����Դ��ķϸִ����Ҫ������
		static bool SelScrapCodeReqWgtFromBOF(string planNO, 
																						long planDetailID, 
																						string& scrapCode, 
																						long& reqWgt);

		//����ͣ��λ�Ż�ȡ���ڿ��
		static bool SelBayNOByParkingNO(string parkingNO, string& bayNO);

		//�����ϸ�Ż�ȡ��Ӧ���ϴ���
		static bool SelMatStockInfoByGridNO(string gridNO, string&matCode, string& compCode, long& stockWgt);

		//��ȡͣ��λ���ڿ�ţ�X���ĵ�����
		static bool SelBayXCenterByParkingNO(string parkingNO, string& bayNO, long& xCenter);

		//���ݵ�¯�ϸִ����Ӧ��wms���ϴ��룬��¯�ϸ�Ҫ����������ȡwms�������������ϸ�ţ����ϴ���   ԭ�򣺰��մ�������װ��λ�ӽ���Զ����ѡ��
		static bool SelMapGMWEAFData(string scrapCode, 
																	long reqWgt, 
																	string bayNO, 
																	long xCenterParking,  
																	MapGridMatWgtEAF& mapGridMatWgtEAFBase );

		//��orderdatabase���ݲ����
		static bool InsOrderDataBase(OrderDataBase matOrderDataBase);
		//��orderqueue���ݲ����
		static bool InsOrderQueueBase(OrderQueueBase matOrderQueueBase);

		//��ѯL3�ƻ��е�qcflag
		static bool SelQCFlag(string planNO, string& qcFlag);

		//��ȡָ���
		static bool SelOrderNO();

		//��ȡ�ϸֶ�Ӧ�ĵ��˷�ʽ 1:ץ��  2������  3������
		static bool SelLiftMode(string matCode, string compCode, string& liftMode);

		//���ݿ�� ���˷�ʽ ��ȡ��Ӧ�г���
		static bool SelCraneNOEAFBayByLfitMode(string bayNO, string liftMode, string& craneNO);

		//��ȡ�糤
		static long SelBayLength(string bayNO);
		//��ȡ�����г�����
		static long SelCraneNumInBay(string bayNO);
		//��ȡ�ϸ����ĵ�����
		static long SelGridXCenter(string gridNO);

		//���ݿ�� seqNO ��ȡ�г���
		static bool SelCraneNOByBaySeq(string bayNO, long seqNO, string& craneNO);

		//==================================================================
		//�г�֪ͨ���
		//==================================================================
		static bool UpdOrderQueueCmdStatus(long orderNO, long cmdSeq, string cmdStauts, long curWgt);

		static bool UpdOrderDataStatus(long orderNO, string stauts);

		static bool UpdOrderQueueWgt(long orderNO, long curWgt);

		static bool UpdOrderDataWgt(long orderNO, long curWgt);

		static bool SelOrderQueueWgt(long orderNO, long& reqWgt,  long& actWgt);

		static bool SelOrderQueueInfo(long orderNO, OrderQueueBase& orderQueueInfo);

		static bool DelOrderQueue(long orderNO);

		static bool UpdYardMapMatWgt(string gridNO, long matWgt, string calChar);//calChar:�����  + -

		static bool DelParkingCarBandInfo(string planNO);


	};
}

#endif

