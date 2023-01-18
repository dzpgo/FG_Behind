#pragma  once
#ifndef   _WMSCRANEORDER_RESOLVER_
#define   _WMSCRANEORDER_RESOLVER_

#include <pace/SmartData.h>
#include <pace/SmartBuffer.h>
#include "DataAccess.h"
#include "CraneOrderCurrentBase.h"
#include "OrderCurrentBase.h"
#include "CranePLCStatusBase.h"
#include "OrderQueueBase.h"

#include "log4cplus/LOG.h"
#include "CranePLCOrderBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"



namespace Monitor
{

	class   WMSCraneOrder_Resolver
	{

	public:

		WMSCraneOrder_Resolver();

		~WMSCraneOrder_Resolver();


	public:
		const static long OUT_DIA_MAX_LIMIT_SAMLL_COIL;
		const static long X_MIN_CRANE_CAN_RUN_4000;
		const static long X_MAX_CRANE_CAN_RUN_428000;
		const static long Y_MIN_CRANE_CAN_RUN_3000;
		const static long Y_MAX_CRANE_CAN_RUN_30000;
	public:

		

       //�����г�ָ������  
       //static bool resolver_WMSCraneOrder(WMSCraneOrderBase wmsCraneOrder, CraneOrderCurrentBase & craneOrderCurrent);

	   static bool resolver_WMSCraneOrder(OrderQueueBase orderQueueData, OrderCurrentBase & orderCurrent);

		//2019.4.24 zhangyuhong add
		//ͨ��дָ�ʽ���صǳ�λ
		static bool		resolver_BoardingCraneOrder(string craneNO, CranePLCStatusBase cranePLCStatusCurrent);

		 //20220621 zhangyuhong add
		 //��ȡ�ϸ�ָ��
		 static bool SelCraneOrder(string craneNO, OrderQueueBase& orderQueueData);

		 //��ȡ����matType ��� �з�  �ط�
		 static bool SelMatType(string matCode, string compCode, string& matType);

		 //��ȡ�ϸ� ж��λ��ж��ʱ�� ͣ��λ��װ��ʱ�� ���ĵ�����  Ŀǰж��λ��ͣ��λ�ǹ��õģ�ͬһʱ��ֻ����һ��ҵ����ҵ
		 //ֻȡ X Y ����  ��Z���겻����
		 static bool SelStockPosData(string orderType, string fromStockNO, string toStockNO, vector<long>& vecFromStockPos, vector<long>& vecToStockPos);	

		 //20221008 zhangyuhong add
		 //����ָ��Ż�ȡʱ��������ĳ�������ɨ��ţ�һ����ɨ��ɹ���
		 static bool SelCarScanNO(long orderNO, string& carScanNO);
	
      

	};
}

#endif

