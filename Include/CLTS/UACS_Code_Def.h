#pragma once
#include <CLTS.h>
#include <slice/CraneOrder.h>
#include <slice/CranePlan.h>
#include <slice/Stock.h>

namespace CLTS
{
    namespace Common
    {
		// ***************************�����·����***************************
		static const int FLAG_DISPAT_INIT = 0;
		static const int FLAG_DISPAT_SND = 10;
		static const int FLAG_DISPAT_SND_ACK = 11;
		static const int FLAG_DISPAT_SND_NACK = 12;
		static const int FLAG_DISPAT_DEL = 20;
		static const int FLAG_DISPAT_DEL_ACK = 21;
		static const int FLAG_DISPAT_DEL_NACK = 22;
		// **************************************************************

		/** �·����.
		 *  �������� convertFlagDispatch 
		 *  ����ֵ�� string					�·����
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    nFlagDispatch : int									�·����
		 */
		inline string convertFlagDispatch(int nFlagDispatch)
		{
			char szFlagDispatch[256];

			switch (nFlagDispatch)
			{
			case FLAG_DISPAT_INIT:
				sprintf_s(szFlagDispatch, 256, "%d[��ʼ]", nFlagDispatch);
				break;
			case FLAG_DISPAT_SND:
				sprintf_s(szFlagDispatch, 256, "%d[�·�����]", nFlagDispatch);
				break;
			case FLAG_DISPAT_SND_ACK:
				sprintf_s(szFlagDispatch, 256, "%d[�·�ȷ��]", nFlagDispatch);
				break;
			case FLAG_DISPAT_SND_NACK:
				sprintf_s(szFlagDispatch, 256, "%d[�·��ܾ�]", nFlagDispatch);
				break;
			case FLAG_DISPAT_DEL:
				sprintf_s(szFlagDispatch, 256, "%d[ɾ������]", nFlagDispatch);
				break;
			case FLAG_DISPAT_DEL_ACK:
				sprintf_s(szFlagDispatch, 256, "%d[ɾ��ȷ��]", nFlagDispatch);
				break;
			case FLAG_DISPAT_DEL_NACK:
				sprintf_s(szFlagDispatch, 256, "%d[ɾ���ܾ�]", nFlagDispatch);
				break;
			default:
				sprintf_s(szFlagDispatch, 256, "%d[δ����]", nFlagDispatch);
				break;
			}

			return string(szFlagDispatch);
		}

		/** ��λ״̬.
		 *  �������� StockStatus2String 
		 *  ����ֵ�� string					��λ״̬
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    status : StockStatus									��λ״̬
		 */
		inline string convertStockStatus(StockStatus status)
		{
			char szStockStatus[256];

			switch (status)
			{
			case StockEmpty:
				sprintf_s(szStockStatus, 256, "%d[����]", status);
				break;
			case StockReserved:
				sprintf_s(szStockStatus, 256, "%d[ԤԼ]", status);
				break;
			case StockOccupied:
				sprintf_s(szStockStatus, 256, "%d[ռ��]", status);
				break;
			default:
				sprintf_s(szStockStatus, 256, "%d[δ����]", status); 
				break;
			}

			return szStockStatus;
		}

		/** ��λ����.
		 *  �������� convertStockLock 
		 *  ����ֵ�� string					��λ����
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    status : StockStatus									��λ����
		 */
		inline string convertLockStatus(LockStatus lock)
		{
			char szLockStatus[256];

			switch (lock)
			{
			case StockConfirmed:
				sprintf_s(szLockStatus, 256, "%d[ȷ��]", lock);
				break;
			case StockWaitChecking:
				sprintf_s(szLockStatus, 256, "%d[����]", lock);
				break;
			default:
				sprintf_s(szLockStatus, 256, "%d[δ����]", lock);
				break;
			}

			return string(szLockStatus);
		}

		/** ��λ����.
		 *  �������� convertStockType 
		 *  ����ֵ�� string					��λ����
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    type : StockType										��λ����
		 */
		inline string convertStockType(StockType type)
		{
			char szStockType[256];

			switch (type)
			{
			case StockSaddle:
				sprintf_s(szStockType, 256, "%d[����]", type);
				break;
			case StockProdLine:
				sprintf_s(szStockType, 256, "%d[����]", type);
				break;
			case StockCrane:
				sprintf_s(szStockType, 256, "%d[�г�]", type);
				break;
			case StockTruck:
				sprintf_s(szStockType, 256, "%d[��λ]", type);
				break;
			default:
				sprintf_s(szStockType, 256, "%d[δ����]", type); 
				break;
			}

			return string(szStockType);
		}

		/** �ȶԼƻ����.
		 *  �������� convertFlagPlanCheck 
		 *  ����ֵ�� string					��λ����
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    nFlagPlanCheck : int									�ȶԼƻ����
		 */
		inline string convertFlagCheckPlan(int nFlagCheckPlan)
		{
			char szCheckPlan[256];

			switch (nFlagCheckPlan)
			{
			case 0:
				sprintf_s(szCheckPlan, 256, "%d[���ƻ�]", nFlagCheckPlan);
				break;
			case 1:
				sprintf_s(szCheckPlan, 256, "%d[δ���ƻ�]", nFlagCheckPlan);
				break;
			case 2:
				sprintf_s(szCheckPlan, 256, "%d[�޼ƻ�]", nFlagCheckPlan);
				break;
			default:
				sprintf_s(szCheckPlan, 256, "%d[δ����]", nFlagCheckPlan);
				break;
			}

			return szCheckPlan;
		}

		/** ����ʵ���ӵ�����������.
		 *  �������� convertCmdStatus 
		 *  ����ֵ�� string
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    cmdStatus : const string&									ָ��״̬
		 */
		inline string convertCmdStatus(const string& cmdStatus)
		{
			char szCmdStatus[256];

			if (cmdStatus == "R")
			{
				sprintf_s(szCmdStatus, 256, "%s[��ʼ]", cmdStatus.c_str());
			}
			else if (cmdStatus == "C")
			{
				sprintf_s(szCmdStatus, 256, "%s[ȡ��]", cmdStatus.c_str());
			}
			else if (cmdStatus == "S")
			{
				sprintf_s(szCmdStatus, 256, "%s[���]", cmdStatus.c_str());
			}
			else if (cmdStatus == "E")
			{
				sprintf_s(szCmdStatus, 256, "%s[���]", cmdStatus.c_str());
			}
			else
			{
				sprintf_s(szCmdStatus, 256, "%s[δ����]", cmdStatus.c_str());
			}

			return szCmdStatus;
		}
    }
}
