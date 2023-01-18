/*----------------------------------------------------------------------------------------
��������PARKINGϵͳ���¼�֪ͨ��
1. ��������ͣ��λ  �������� ���� ͣ��λ��
2. �����뿪ͣ��λ  �� ������ ���� ͣ��λ��

------------------------------------------------------------------------------------------*/

#pragma once
#ifndef _EventParkingHandler_
#define _EventParkingHandler_

#include <map>
#include <vector>
#include <tag/Tag.h>
#include <utility/StringHelper.h>
#include <tag/Tag.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
//#include "DealData.h"
#include "OrderDataBase.h"
#include "CarPlanBandInfo.h"
#include "OrderQueueBase.h"
#include "SQL4Order.h"
//#include <CLTS.h>

namespace Monitor
{
	typedef map<long, OrderDataBase> MapOrderDataBase;

	//���eaf�ƻ���Ƶ�ȡ��map���� map<���, vectro<�ϸ��, ���ϴ���, ȡ����>>
	typedef map<long, vector<string> > MapGridMatWgtEAF;

	//���bof�ƻ���Ƶ�ȡ��map���� map<����˳���, vectro<�ϸ��, ���ϴ���, ȡ����>>
	typedef map<long, vector<string> > MapGridMatWgtBOF;


	class EventParkingHandler
	{
	public:
			EventParkingHandler(void);
			~EventParkingHandler(void);
			//
			const static string EXTER_SYSTEM_EAF;
			const static string EXTER_SYSTEM_BOF;

			const static long MPE_WGT;	

			void OrderCreateReqForL3EAFL2(string strValue, string logFileName);

		private:

			//bool OrderCreateL3(CarPlanBandInfo carPlanBandInfoBase,  string parkingNO, MapOrderDataBase& mapOrderData);
			bool OrderCreateL3(CarPlanBandInfo carPlanBandInfoBase,  string parkingNO, OrderDataBase& orderDataBaseL3);

			bool OrderCreateEAFMap(CarPlanBandInfo carPlanBandInfoBase,  string parkingNO, MapOrderDataBase& mapOrderData);
			bool OrderCreateEAF(CarPlanBandInfo carPlanBandInfoBase,  string parkingNO, OrderDataBase& orderDataBaseEAF);

			bool GetScrapCodeReqWgt(CarPlanBandInfo carPlanBandInfoBase, string& locCode, string& scrapCode, string& compCode, long& reqWgt);

			bool MakeSingleOrderEAF(CarPlanBandInfo  carPlanBandInfoBase, 
															long orderGroupNO, 
															string parkingNO, 
															long exeSeq, 
															string gridNO, 
															string matCode, 
															long calWgt, 
															OrderDataBase& orderDataBaseEAF);

			string GetOrderType(string planSrc, string workType);

			bool GetOrderQueue(OrderDataBase orderData, OrderQueueBase& orderQueue);

			bool GetRecCraneNO(OrderDataBase orderData, string& recCraneNO);

			//���ݿ糤 ���ȷ� ʵ��X���� ��ȷ����Ӧ���ǵڼ��ȷ�  ����X��С��������
			long GetXPosSeqInBayDivide(long bayLength, long divideNum, long xPos);

			//����ָ�����ͻ�ȡ�ϸ���
			string GetGridNOByOrderType(OrderDataBase orderData);


		
	};

	
}
#endif