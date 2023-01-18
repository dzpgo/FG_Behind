#pragma once
#ifndef _SQL4SRS_
#define _SQL4SRS_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"


namespace Monitor
{
	class SQL4SRS
	{
	public:
		SQL4SRS(void);
		~SQL4SRS(void);		

		//��ȡɨ�账���
		static bool SelScanNO4Mat(string& scanNO);

		//��ȡɨ�账���
		static bool SelScanNO4Car(string& scanNO);

		//��ȡ����ģ��ͨ�Ż��ߺ�
		static bool SelComLineNO(string module, int& lineNO);

		//���뼤���϶�ɨ���
		static bool InsParkingSRSMatInfo(string scanNO, //ɨ�账���
																	string areaType, //��ɨ��������
																	string areaNO, //��ɨ��������
																	long orderNO, //��ǰָ���
																	string scanMessageNO, //ɨ���¼���
																	string scanCraneNO, //ɨ���г���
																	string scanType, //ɨ������ 0-ȡ�� 1-����
																	long startX, //ɨ��������ʼX
																	long endX, //ɨ���������X
																	long startY, //ɨ��������ʼY
																	long endY, //ɨ���������Y
																	long actX, //�г���ǰX
																	long actY);//�г���ǰY

		static bool InsParkingSRSMatInfo2(string scanNO, //ɨ�账���
																		string areaType, //��ɨ��������
																		string areaNO, //��ɨ��������
																		long orderNO, //��ǰָ���
																		string scanMessageNO, //ɨ���¼���
																		string scanCraneNO, //ɨ���г���
																		string scanType, //ɨ������ 0-ȡ�� 1-����
																		long carPointX1, //�������X1
																		long carPointY1, //�������X1
																		long carPointZ1, //�������X1
																		long carPointX2, //�������X1
																		long carPointY2, //�������X1
																		long carPointZ2, //�������X1
																		long carPointX3, //�������X1
																		long carPointY3, //�������X1
																		long carPointZ3, //�������X1
																		long carPointX4, //�������X1
																		long carPointY4, //�������X1
																		long carPointZ4, //�������X1	
																		long actX, //�г���ǰX
																		long actY);//�г���ǰY

		//���¼����϶�ɨ���,ͬʱ��ȡ��Ӧָ���orderNO
		static bool UpdParkingSRSMatInfo(string scanNO, 
																		string scanResult, 
																		long pointX, 
																		long pointY, 
																		long pointZ);

		//���¼����϶�ɨ���,ͬʱ��ȡ��Ӧָ���orderNO
		static bool SelOrderNOByMatScanNO(string matScanNO, long& orderNO);

		//���복������ɨ����Ϣ��
		static bool InsParkingSRSCarInfo(string scanNO, 
																	string treatmentNO, 
																	string parkingNO, 
																	string carNO, 
																	string carType, 
																	string matType, 
																	string loadFlag, 
																	string scanMode, 
																	long orderNO, 
																	string scanMessageNO, 
																	string scanCraneNO, 
																	long startPoint, 
																	long endPoint, 
																	long scanCount, 
																	string scanIP );

		//���³�������ɨ���ͬʱ��ȡ��Ӧָ���
		static bool UpdParkingSRSCarInfo(string scanNO, 
																		string scanResult, 
																		long pointX1, 
																		long pointY1, 
																		long pointZ1, 
																		long pointX2, 
																		long pointY2, 
																		long pointZ2, 
																		long pointX3, 
																		long pointY3, 
																		long pointZ3, 
																		long pointX4, 
																		long pointY4, 
																		long pointZ4,
																		long pointXMax,
																		long pointXMin, 
																		long pointYMax,
																		long pointYMin,
																		long centerX,
																		long centerY
																		);

		//����carscanNO��ȡָ���
		static bool SelOrderNOByCarScanNO(string carScanNO, long& orderNO);

		//��ȡ����ͣ��λ�ϴ���š�����
		static bool SelParkingTreatmentNOCarNO(string parkingNO, string& parkingTreatmentNO, string& carNO);

		//��ȡRGVͣ��λ�ϳ���
		static bool SelRGVNO(string parkingNO, string& rgvNO);

		//����UACS_PARKING_RGV_STATUS
		static bool UpdParkingRGVStatusSRS(string parkingNO, 
																			long pointXMin, 
																			long pointXMax, 
																			long pointYMin, 
																			long pointYMax);





	};
}

#endif

