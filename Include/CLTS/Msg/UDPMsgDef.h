//********************************************************************
//** Copyright (c) 2016 �������
//** �����ˣ�������
//** ������\�ļ�����UDPMsgDef.h
//** �๦�ܣ�UDP�������ݽṹ
//** ������
//** �������ڣ�2016-12-09
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#pragma once
#include <string>
#include <vector>
#include <Ice/Ice.h>
#include <pace/SmartData.h>

using namespace std;

namespace CLTS
{
	namespace MSG
	{
		const int MAX_MSG_BUFFER_LENGTH = 4096;
		const int POWER_TRANS_HEAD = 32;

		/** �Զ���UDP���Ľṹ.
		 *   
		 */
		struct MY_UDP_MSG
		{
			unsigned char msgId[POWER_TRANS_HEAD];	  // ���ĺ�
			int lenMsgId;					  // ���ĺų���
			unsigned char msgData[MAX_MSG_BUFFER_LENGTH];  // ��������
		};

		class UdpUtil
		{
		public:
			/** ��������Ϣת����PowerTranser�ɶ�����.
			 *  �������� trans2SmartData
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    msg : MY_UDP_MSG*										UDP�в�ֳ��ĵ�����Ϣ
			 *    lenMsgData : const int								ʵ�ʵ��ĳ���
			 *    sd : Ice::ByteSeq&									PowerTranser�ɶ�����
			 *    vecField : Ice::StringSeq&							���ݷָ�����ֳ����ֶ�
			 *    split : char											������Ϣ�еķָ���[������]
			 */
			static void trans2SmartData(MY_UDP_MSG* msg, const int lenMsgData, Ice::ByteSeq& sd);

			/** ����UDP����ת�����Զ�����Ľṹ.
			 *  �������� rcv2UdpMsg
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    rcv : Ice::ByteSeq&									����UDP����
			 *    msg : MY_UDP_MSG&										�Զ�����Ľṹ.
			 *    lenMsgId : const int									UDP���İ����ĵ��ĺų���
			 */
			static void rcv2UdpMsg(const Ice::ByteSeq& rcv, MY_UDP_MSG& msg, const int lenMsgId);

			/** ������Ľṹ���.
			 *  �������� splitUdpMsg
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    msg : MY_UDP_MSG&										�Զ�����Ľṹ
			 *    lenMsgData : const int								ʵ�ʵ��ĳ���
			 *    vecField : Ice::StringSeq&							��ֺ���ֶ�����
			 *    lenMsgId : const int									���õķָ���
			 */
			static void splitUdpMsg(MY_UDP_MSG& msg, const int lenMsgData, Ice::StringSeq& vecField, char split='#');

			static void wrapSmartData(const Ice::StringSeq& vecField, iPlature::SmartData& sd, int& index);
		};
	};
};
