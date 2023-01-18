#pragma once
#ifndef _SQL4Parking_
#define _SQL4Parking_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "CarPlanBandInfo.h"
#include "EventGateHandler.h"


namespace Monitor
{
	class SQL4Parking
	{
	public:
		SQL4Parking(void);
		~SQL4Parking(void);		

		//��ѯ�����ƻ�����Ϣ
		static bool SelCarPlanBandInfo(string carNO, CarPlanBandInfo& carPlanBandInfoBase);

		//���ݳ��ƺŲ�ѯ�����ƻ��󶨱���ENTER_FLAG=2�ļ�¼������У�����true
		static bool CarEnterYardExist(string carNO);

		//��ѯL3�ƻ����Դ��ķϸִ����Ҫ������(�����ж�ϣ�reqWgt������)
		static bool SelScrapCodeReqWgtFormL3(string planNO, 
																					string workType, //L3��ж��XL����װ��ZC
																					string& locCode, //L3�������ϸ��
																					string& scrapCode, //���ϴ���
																					string& compCode, //���ƴ���  ����+���� Ψһȷ��һ������
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

		//���������ϸ�Ż�ȡ��Ӧ�Ŀ�ź͵�բ��
		static bool SelBayNOGateNOByGridNO(string gridNO, string& bayNO, string& gateNO);

		//���³����ƻ��󶨱��е�Ŀ���ϸ�� ��բ�� ���ݳ��š��ƻ���
		static bool InitGateGridParking(string carNO, string planNO);

		//���³����ƻ��󶨱��е�Ŀ���ϸ�� ��բ�� ���ݳ��š��ƻ��š��Ӽƻ���
		static bool UpdGridGateByCarNOPlanNOPlanDetailID(string carNO, 
																										string planNO, 
																										long planDetailID, 
																										string targetGridNO, 
																										string gateNO, 
																										string targetParkingNO);

		//��ȡ���������Ƿ�����scrapCodeҪ�������ϸ��,���տ�����Ӵ�С����
		static bool SelGridNOMatchScrapCode(string bayNO, string scrapCode, long reqWgt, string scrapType, string& maxStockGridNO);
		//ֻ��ȡΨһ���������������ϸ�ţ����տ�����Ӵ�С���л�ȡ�����ϸ��
		//����Ҫ�ж��ϸ��Ӧ��ͣ��λ�Ƿ����
		//falseReson 1:  �޿���ͣ��λ  2����治��
		static bool SelGridNOMatchScrapCode2(string bayNO, 
																					string scrapCode, 
																					long reqWgt, 
																					string scrapType, 
																					string& targetGridNO, 
																					string& parkingNO, 
																					long& falseReason);

		//���ݵ�բ�Ż�ȡ���ڿ��
		static bool SelBayNOByGateNO(string gateNO, string& bayNO);

		//���ݳ��ŵ�բ�Ż�ȡû�н�������ļ�¼
		static bool SelTargetGridNO(string carNO, 
															string gateNO, 
															string& carType, 
															string& targetGridNO, 
															string& targetParkingNO, 
															string& workType,
															string& planNO, 
															string& planSrc, 
															long& planDetailID);

		//���½����־=2
		static bool UpdEnterFlag2Enter(string carNO, string gateNO);

		//���ݳ��źͽ����ǻ�ȡĿ��ͣ��λ��
		static bool SelParkingNOByCarNOFlag(string carNO, 
																			string enterFlag, 
																			string& parkingNO, 
																			string& workType, 
																			string& carType,
																			string& planSrc, 
																			string& planNO, 
																			long& planDetailID);

		//����ͣ��λ�Ż�ȡͣ��λ״̬
		static bool SelStatusByParkingNO(string parkingNO, string& workStatus, string& workType, string& carNO);

		//����ͣ��λ�Ż�ȡ��Ӧ����
		static bool SelCarNOByParkingNO(string parkingNO, string& carNO);

		//����ͣ��λ״̬��
		static bool UpdParkingStatus(string parkingNO, string workStatus);

		//��ȡ�ϸ��Ӧ���ϴ���͸�����
		static bool SelGridInfoByGridNO(string gridNO, string& matCode, string& compCode, long& matWgt);

		//�����ϸ�Ż�ȡ��Ӧͣ��λ״̬
		static bool SelPKStatusByGridNO(string gridNO, string& parkingNO, string& workStatus);

		//���³����ƻ��󶨱��� ��բ�� ,Ŀ���ϸ��,Ŀ��ͣ��λ��
		static bool UpdGateGridPKByCarPlan(string carNO, string planNO, string gateNO, string gridNO, string parkingNO);

		//��ȡͣ��λ�����(���ݿ����з�ʽ��ȡ,��100000��ʼ,�����Ϊ ZC+���к�  ����  XL+���к�)
		static bool SelParkingTM(long& parkingTM);

		//����ͣ��λ״̬��
		static bool UpdParkingWorkStautsInfo(string parkingNO, 
																				string treatmentNO, 
																				string workStatus, 
																				string workType, 
																				string carNO,
																				string carType );

		//����װ��ж��������Ϣ�������� UACS_PARKING_MAT_INFO 
		//����ţ�ͣ��λ�ţ����ţ��ƻ���Դ���ƻ��ţ��Ӽƻ��ţ����ϴ��룬�����룬��ҵ���ͣ��Ƿ����=1��δ��ɣ�
		static bool InsParkingMatInfo(string treatmentNO, 
																string parkingNO, 
																string carNO, 
																string planSrc, 
																string planNO, 
																long planDetailID, 
																string matCode, 
																string compCode, 
																string workType, 
																string fromPlace, 
																string toPlace, 
																string finishFlag);

		//����ͣ��λ�Ż�ȡͣ��λ״̬���е���������
		static bool SelAllFromParkingWorkStatus(string parkingNO, 
																					string& treatmentNO, 
																					string& workStauts, 
																					string& workType, 
																					string& carNO, 
																					string& carType );

		//��ʼ��ͣ��λ״̬
		static bool InitParkingWorkStauts(string parkingNO);

		//���ݳ���,�����־=2,��ҵ����=ZC����  ɾ��������Ϣ�󶨱�
		static bool DelCarPlanInfoByCarNO(string carNO, string carType, string workType);

		//����UACS_PARKING_MAT_INFO������  FINISH_FLAG=2
		static bool UpdParkingMatInfoFinish(string treatmentNO);

		//����ͣ��λ״̬
		static bool UpdParkingStatusByValue(string pakringNO, string workStatus);

		//���ݳ��ţ������־=2 ��ҵ����=XL�����³�����Ϣ�󶨱��еĽ����־=3 ж���뿪  
		static bool UpdEnterFlag2XLLeave(string carNO, 
																		string carType, 
																		string workType, 
																		string lastEnterFlag, 
																		string nowEnterFlag);

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
																		long pointZ, 
																		long& orderNO);

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
																	string scanIP, 
																	string scanRGVFlag);

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
																	  long pointX, 
																	  long pointY, 
																	  long pointZ, 
																	  long& orderNO, 
																	  string& scanRGVFlag, 
																	  string& parkingNO);

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

