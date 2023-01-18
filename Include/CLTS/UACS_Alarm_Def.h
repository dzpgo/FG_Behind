#pragma once
#include <CLTS.h>
#include <Slice/CraneOrder.h>
#include <Slice/CranePlan.h>
#include <Slice/Stock.h>
#include <slice/LineTrack.h>
#include <stdio.h>
#include <UACS_Code_Def.h>

#if defined(__WINDOWS__) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__)
#undef STR_FORMAT
#define STR_FORMAT sprintf_s
#elif defined(__linux__) || defined(linux) || defined(__linux) || defined(__LINUX__) || defined(LINUX) || defined(_LINUX)
#undef STR_FORMAT
#define STR_FORMAT snprintf
#endif

namespace CLTS
{
    namespace Common
    {
		// *******************************************���˼ƻ�ģ��*****************************************
		// �����¼���
		static const int ALARM_CRANE_PLAN_INIT = 6000;		// ����-���˼ƻ���ʼ��
		static const int ALARM_CRANE_PLAN_NEW = 6010;		// ����-���˼ƻ�����
		static const int ALARM_CRANE_PLAN_UPD = 6012;		// ����-���˼ƻ�����

		static const int ALARM_CRANE_PLAN_DEL_REQBYL3 = 6020;	// ����-����ɾ�����˼ƻ�(ByL3)
		static const int ALARM_CRANE_PLAN_DEL_REQBYUACS = 6022;	// ����-����ɾ�����˼ƻ�(ByUACS)
		static const int ALARM_CRANE_PLAN_DEL = 6024;			// ����-���˼ƻ�ɾ��
		static const int ALARM_CRANE_PLAN_DEL_ACKTOL3 = 6026;	// ����-��Ӧɾ�����˼ƻ�(ToL3)

		static const int ALARM_CRANE_PLAN_SELECT = 6030;	// ����-���˼ƻ���ʼִ��
		static const int ALARM_CRANE_PLAN_CANCEL = 6040;	// ����-���˼ƻ�ȡ��ִ��
		static const int ALARM_CRANE_PLAN_LIFTUP = 6050;	// ����-���˼ƻ�������
		static const int ALARM_CRANE_PLAN_LIFTDOWN = 6060;	// ����-���˼ƻ�������
		
		// TAG����
		static const string EV_CRANE_PLAN_INIT_REQ = "EV_CRANE_PLAN_INIT_REQ";		// ���˼ƻ���ʼ��
		static const string EV_CRANE_PLAN_DEL_REQ_BYL3 = "EV_CRANE_PLAN_DEL_REQ_BYL3"; // ���˼ƻ���ʼ��
		// ************************************************************************************************

		// *******************************************��ͼģ��*****************************************
		// �����¼���
		static const int ALARM_YARDMAP_RECOM_REQ = 3000;		// ����-��ͼ�·���λ�Ƽ�����
		static const int ALARM_YARDMAP_RECOM_ACK = 3010;		// ����-��ͼ��ÿ�λ�Ƽ����

		static const int ALARM_YARDMAP_LIFTUP_COIL = 3020;		// ����-�־����ʵ��
		static const int ALARM_YARDMAP_LIFTUP_STOCK = 3030;		// ����-��λ���ʵ��
		static const int ALARM_YARDMAP_LIFTUP_CRANE = 3040;		// ����-�г����ʵ��
		static const int ALARM_YARDMAP_LIFTDOWN_COIL = 3050;	// ����-�־����ʵ��
		static const int ALARM_YARDMAP_LIFTDOWN_STOCK = 3060;	// ����-��λ���ʵ��
		static const int ALARM_YARDMAP_LIFTDOWN_CRANE = 3070;	// ����-�г����ʵ��

		static const int ALARM_YARDMAP_LOCK_STOCK = 3060;		// ����-��λ��Ϊ����
		static const int ALARM_YARDMAP_CHECKING_STOCK = 3070;	// ����-��λ��Ϊ����
		static const int ALARM_YARDMAP_CONFIRMED_STOCK = 3080;	// ����-��λ��ΪͶ��

		static const int ALARM_YARDMAP_EMPTY_STOCK = 3100;		// ����-��տ�λ
		static const int ALARM_YARDMAP_BOOK_STOCK = 3110;		// ����-ԤԼ��λ
		static const int ALARM_YARDMAP_OCCUPY_STOCK = 3120;		// ����-ռ�ÿ�λ

		static const int ALARM_YARDMAP_SET_COIL_INFO = 3500;	// ����-ά���־���Ϣ
		static const int ALARM_YARDMAP_MOVE_COIL = 3510;		// ����-�ƶ��־���Ϣ
		
		// ************************************************************************************************
		
		// *******************************************����ָ��ģ��*****************************************
		// �����¼��ţ��߼�������
		static const int ALARM_CREATE_ORDER = 2000;		// ����-����ָ�������
		static const int ALARM_ORDER_UPDATE = 2010;		// ����-����ָ����±���
		static const int ALARM_ORDER_RECOMM = 2020;		// ����-����ָ����ؿ�λ����
		static const int ALARM_ORDER_L3_RECOMM = 2023;	// ����-����ָ������L3�Ƽ���λ
		static const int ALARM_ORDER_UACS_RECOMM = 2026;// ����-����ָ������MM�Ƽ���λ
		static const int ALARM_ORDER_RECOMM_ACK = 2030;	// ����-����ָ���λ�Ƽ���Ӧ
		static const int ALARM_ORDER_SET_TOSTOCK = 2040;// ����-����ָ���޸���ر���
		static const int ALARM_ORDER_DISPATCH = 2050;	// ����-����ָ���·�����ģ��
		static const int ALARM_ORDER_DISPATCH_ACK = 2060;// ����-����ָ���·�����ģ��
		static const int ALARM_ORDER_SELECT = 2070;		// ����-����ָ�ʼִ�б���
		static const int ALARM_ORDER_CANCEL = 2080;		// ����-����ָ��ȡ��ִ�б���
		static const int ALARM_ORDER_LIFTUP = 2090;		// ����-����ָ�������ɱ���
		static const int ALARM_ORDER_LIFTDOWN = 2100;	// ����-����ָ�������ɱ���
		static const int ALARM_ORDER_DEL = 2110;		// ����-����ָ��ɾ������
		static const int ALARM_ORDER_FIRSTJOB = 2120;	// ����-����ָ������ִ�б���
		static const int ALARM_ORDER_OVERBAY = 2130;	// ����-����ָ�������
		static const int ALARM_ORDER_CHANGE_CRANE = 2140;	// ����-����ָ���޸��г���
		static const int ALARM_ORDER_CHANGE_PRIORITY = 2150;// ����-����ָ���޸����ȼ�

		// �����¼��ţ����ݿ������
		static const int ALARM_DAL_INSERT_ORDER = 2500;	// ����-д�����ָ��
		static const int ALARM_DAL_SET_RECOMMID = 2510;	// ����-�趨��λ�Ƽ�����
		static const int ALARM_DAL_SET_FROMSTOCK = 2520;// ����-�趨ָ������λ
		static const int ALARM_DAL_SET_TOSTOCK = 2530;	// ����-�趨ָ����ؿ�λ
		static const int ALARM_DAL_SET_PLANNO = 2540;	// ����-�趨ָ���Ӧ�ƻ���
		static const int ALARM_DAL_SET_FLAG_DISP = 2550;// ����-�趨ָ����ȱ��(�·�ģ��)
		static const int ALARM_DAL_SET_ACK_DISP = 2560;	// ����-�趨ָ����ȱ��(ģ��Ӧ��)
		static const int ALARM_DAL_SET_FLAG_ENABLE = 2570;	// ����-�趨ָ��ɵ����
		static const int ALARM_DAL_SET_FLAG_DEL = 2580;	// ����-�趨ָ��ɾ�����
		static const int ALARM_DAL_SET_PRIORITY = 2590;	// ����-�趨ָ�����ȼ�
		static const int ALARM_DAL_INSERT_OPER = 2600;	// ����-д�����ʵ��
		static const int ALARM_DAL_DEL_ORDER = 2610;	// ����-ɾ������ָ��

		// ���ݿ��������
		static const int ALARM_LOGIC = 2000;
		static const int ALARM_DAL_OPER = 2500;

		// TAG����
		static const string EV_ORDER_DEL = "EV_ORDER_DEL";		// ָ��ɾ���ź�
		static const string EV_ORDER_UPDATE = "EV_ORDER_UPDATE";	// ָ������ź�
		static const string EV_ORDER_FIRSTJOB = "EV_ORDER_FIRSTJOB";	// ָ����ǰ�ź�
		static const string EV_ORDER_SET_TO_STOCK = "EV_ORDER_SET_TO_STOCK";	// ָ���޸�Ŀ���λ
		static const string EV_ORDER_CHANGE_CRANE = "EV_ORDER_CHANGE_CRANE";	// ָ���޸��г���
		static const string EV_ORDER_CREATE = "EV_ORDER_CREATE";	// ָ���½��ź�			
		// ************************************************************************************************

		/** ��ʼ����������.
		 *  �������� initAlarmMsg 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    alarmMsg : AlarmMsg&				                	������Ϣ
		 *    nEventID : int										�����¼���
		 *    strTitle : string										������Ϣ
		 *    format : const char*									�������ݸ�ʽ�ַ���
		 */
		inline void initAlarmMsg(AlarmMsg& alarmMsg, int nEventID, string strTitle, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];

			// ��ʼ������
			if (strTitle.length() == 0)
			{
				// �趨����������Ϣ
				STR_FORMAT(szAlarmMsg, 
					MAX_BUFFER_LENGTH, 
					"�¼�%d",
					nEventID);
				alarmMsg.strTitle = szAlarmMsg;
			}
			else
			{
				// �趨����������Ϣ
				STR_FORMAT(szAlarmMsg, 
					MAX_BUFFER_LENGTH, 
					"�¼�%d, %s", 
					nEventID,
					strTitle.c_str());
				alarmMsg.strTitle = szAlarmMsg;
			}

			// ��ʽ��������Ϣ
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);
			// ��ʼ������
			alarmMsg.strMsg = szMessage;
		}

		/** �г��ƻ���Ϣ�ӵ�����������.
		 *  �������� addAlarmMsg 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    cranePlanDesc : const CranePlanDesc&                	���˼ƻ�
		 *    alarmMsg : AlarmMsg&			                        ��������
		 *    format : const char*									������ʽ�ַ���
		 *    ...													�����ַ��������б�
		 */
		inline void addAlarmMsg(const CranePlanDesc& cranePlanDesc, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];

			// ��ʽ��������Ϣ
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// �趨����������Ϣ
			alarmMsg.strMsg += szMessage;

			// �趨������ϸ��Ϣ
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"L3���˼ƻ���Ϣ: �ƻ���%d, ���Ϻ�%s, ����%s, ����˳���%d, ������%d, �����λ%s, ��ؿ�λ%s", 
				cranePlanDesc.planNo,
				cranePlanDesc.matNo.c_str(),
				cranePlanDesc.craneInstCode.c_str(),
				cranePlanDesc.craneSeq,
				cranePlanDesc.hgNo,
				cranePlanDesc.fromStockNo.c_str(),
				cranePlanDesc.toStockNo.c_str());
			alarmMsg.strDetail = szAlarmMsg;
		}
		
		/** �г�ָ����Ϣ�ӵ�����������.
		 *  �������� addAlarmMsg 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    craneOrderDesc : const CraneOrderDesc&                ����ָ��
		 *    szAlarmMsg : char*			                        �����ַ���
		 *    nMsgLength : int										�����ַ�������
		 *    nEventID : int										�ڲ��¼���
		 */
		inline void addAlarmMsg(const CraneOrderDesc& craneOrderDesc, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];

			// ��ʽ��������Ϣ
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// �趨����������Ϣ
			alarmMsg.strMsg += szMessage;

			// �趨������ϸ��Ϣ
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"����ָ����Ϣ: ���Ϻ�%s, ָ����%d, ����%d, �ƻ���%d, ������%d, ���λ%s, ���λ%s, ���ȼ�%d, �г���%s", 
				craneOrderDesc.matNo.c_str(),
				craneOrderDesc.orderNo,
				craneOrderDesc.orderType,
				craneOrderDesc.planNo,
				craneOrderDesc.groupNo,
				craneOrderDesc.fromStockNo.c_str(),
				craneOrderDesc.toStockNo.c_str(),
				craneOrderDesc.orderPriority,
				craneOrderDesc.craneNo.c_str());
			alarmMsg.strDetail = szAlarmMsg;
		}

		/** ��λ��Ϣ�ӵ�����������.
		 *  �������� addAlarmMsg 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    stockDesc : const StockDesc&							��λ��Ϣ
		 *    szAlarmMsg : char*			                        �����ַ���
		 *    nMsgLength : int										�����ַ�������
		 *    nEventID : int										�ڲ��¼���
		 */
		inline void addAlarmMsg(const StockDesc& stockDesc, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];
			string strStockStatus = convertStockStatus(stockDesc.status);
			string strLockStatus = convertLockStatus(stockDesc.lock);
			string strStockType = convertStockType(stockDesc.type);

			// ��ʽ��������Ϣ
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// �趨����������Ϣ
			alarmMsg.strMsg += szMessage;

			// �趨������ϸ��Ϣ
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"��λ��ǰ��Ϣ: ��λ��=%s, ��λ״̬=%s, ���Ϻ�=%s, ����״̬=%s, ��λ����=%s, �����=%s, ��������=(%d, %d, %d)",
				stockDesc.no.c_str(),
				strStockStatus.c_str(),
				stockDesc.matNo.c_str(),
				strLockStatus.c_str(),
				strStockType.c_str(),
				stockDesc.areaNo.c_str(),
				stockDesc.xCenter,
				stockDesc.yCenter,
				stockDesc.zCenter);
			alarmMsg.strDetail = szAlarmMsg;
		}

		/** ����ʵ���ӵ�����������.
		 *  �������� addAlarmMsg 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    orderOperDesc : const OrderOperDesc&					����ʵ��
		 *    szAlarmMsg : char*			                        �����ַ���
		 *    nMsgLength : int										�����ַ�������
		 *    nEventID : int										�ڲ��¼���
		 */
		inline void addAlarmMsg(const OrderOperDesc& orderOperDesc, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];
			string strCmdStatus = convertCmdStatus(orderOperDesc.cmdStatus);
			string strFlagCheckPlan = convertFlagCheckPlan(orderOperDesc.flagCheckPlan);

			// ��ʽ��������Ϣ
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// �趨����������Ϣ
			alarmMsg.strMsg += szMessage;

			// �趨������ϸ��Ϣ
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"����ʵ����Ϣ: ʵ������=%s, ָ����=%d, �г���=%s, ������=%s, ʵ����λ=%s, ʵ������=(%d, %d, %d), ʵ�����ռƻ�=%s", 
				strCmdStatus.c_str(),
				orderOperDesc.orderNo,
				orderOperDesc.craneNo.c_str(),
				orderOperDesc.userName.c_str(),
				orderOperDesc.stockNo.c_str(),
				orderOperDesc.xCranePos,
				orderOperDesc.yCranePos,
				orderOperDesc.zCranePos,
				strFlagCheckPlan.c_str());
			alarmMsg.strDetail = szAlarmMsg;
		}

		/** ����ʵ���ӵ�����������.
		 *  �������� addAlarmMsg 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    orderOperDesc : const OrderOperDesc&					����ʵ��
		 *    szAlarmMsg : char*			                        �����ַ���
		 *    nMsgLength : int										�����ַ�������
		 *    nEventID : int										�ڲ��¼���
		 */
		inline void addAlarmMsg(const ExitSaddleTrack& exitSaddleTrack, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];

			// ��ʽ��������Ϣ
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// �趨����������Ϣ
			alarmMsg.strMsg += szMessage;

			// �趨������ϸ��Ϣ
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"���ڸ�����Ϣ: L2������=%s, ���=%s, ����=%d, ���=%d, �ھ�=%d, �⾶=%d, ������=%d, �µ�����=%s, ��װ����=%s, ��ͬ��=%s, ��������=%s", 
				exitSaddleTrack.saddleL2Name.c_str(),
				exitSaddleTrack.coilNo.c_str(),
				exitSaddleTrack.weight,
				exitSaddleTrack.width,
				exitSaddleTrack.inDia,
				exitSaddleTrack.outDia,
				exitSaddleTrack.coilOpenDirection,
				exitSaddleTrack.nextUnitNo.c_str(),
				exitSaddleTrack.packCode.c_str(),
				exitSaddleTrack.workOrderNo.c_str(),
				exitSaddleTrack.productDate.c_str());
			alarmMsg.strDetail = szAlarmMsg;
		}
    }
}

#undef STR_FORMAT
