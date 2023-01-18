#pragma once
#ifndef _Adapter_UACS_YARDMAP_STOCK_INFO_
#define _Adapter_UACS_YARDMAP_STOCK_INFO_

#include "log4cplus/LOG.h"

#include "DataAccess.h"

namespace Monitor
{


	class Adapter_UACS_YARDMAP_STOCK_INFO
	{
	public:
		Adapter_UACS_YARDMAP_STOCK_INFO(void);

		~Adapter_UACS_YARDMAP_STOCK_INFO(void);

		//����X,Y��������stockno
		static bool SelStockNOByXY(string bayNO, long x, long y, string& stockNO);

		//����stockNO �� ж���� ����X_START  X_END  X_CENTER   Y_START Y_END Y_CENTER  �������map<long>
		static bool SelXYZValueFromDumpingInfo(string stockNO, map<string, long>& mapXYZValue);

		//����stockNO �� �ϸ��� ����X_START  X_END  X_CENTER   Y_START Y_END Y_CENTER  �������map<long>
		static bool SelXYZValueFromGridInfo(string stockNO, map<string, long>& mapXYZValue);

		//�����ϸ�Ż�ȡ�ϸ���������ϴ���͸�����
		static bool SelMatCompCodeFromGridInfo(string stockNO, string& matCode, string& compCode);

		//���ݳ���ɨ��Ż�ȡ����ɨ�����ĵ㣨����ģ�
		static bool SelCarCenterXY(string carScanNO, long& centerX, long& centerY);

		//����toStockNO��ȡͣ��λ������е�ͣ��λ��  X_START X_END X_CENTER Y_START Y_END  Y_CENTER  ɨ�跽��
		static bool SelParkingInfo(string pakringNO, 
														long& xStart, 
														long& xEnd, 
														long& xCenter, 
														long& yStart, 
														long& yEnd, 
														long& yCenter, 
														string& scanDir);


	};
}



#endif

