//********************************************************************
//** Copyright (c) 2016 �������
//** �����ˣ�������
//** ������\�ļ�����MsgDecoder.h
//** �๦�ܣ����Ľ�����
//** ����������PowerTranser�����ã������Ľ�����SmartData����
//** �������ڣ�2016-9-21
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#pragma once
#include <PowerTranser/MsgSmartData.h>
#include <iDA/iDA.h>
#include <Msg/MsgSetting.h>
#include <Ice/Ice.h>

namespace CLTS
{
	namespace MSG
	{
		class MsgDecoder
		{
		private:
			// decoderӳ������趨
			typedef multimap<string, MsgSetting> MapMsgId2Settings;

			// ���е����趨
			MapMsgId2Settings m_mapSettings;	// ���ķ����趨

			/** ��������[powertranser].
			 *   
			 */
			SmartData m_SmartData;

			/** ���ݿ�����ʵ��
			 *
			 */
			iPlature::iDA::Connection m_iDaConn;

			/** �������ʱ��ɸѡ�趨.
			 *
			 */
			MsgSetting m_msgSetting;

			/** ��ȡ�ļ��ڵ��趨.
			 *  �������� loadSettingFile 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    settingFile��string                                   �趨�ļ�����ȫ��·����
			 */
			void loadSettingFile(string settingFile);

			/** �趨���ݿ�����.
			 *  �������� connect 
			 *  ����ֵ�� 
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    strDbConn : string                                    ���ݿ������ַ���
			 *    strDbType : string                                    ���ݿ�����
			 */
			void connect(string strDbConn, string strDbType);

			/** �������¼���ϵ�ĵ����ֶβ�ֳ���С��Ԫ��ɵ��ֶ�����.
			 *  �������� split 
			 *  ����ֵ�� vector<SmartData>      ��ֺ���ֶ�����
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    sd : SmartData                                        �����ֶ�
			 */
			vector<SmartData> split(SmartData& sd);

		public:
			MsgDecoder();
			~MsgDecoder();

			/** �����趨
			 *  �������� load
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    settingFile��string                                   �趨�ļ�����ȫ��·����
			 *    strDbConn : string                                    ���ݿ������ַ���
			 *    strDbType : string                                    ���ݿ�����
			 */
			void load(string settingFile, string strDbConn, string strDbType);

			/** ��ȡpowertranser�еĵ�������.
			 *  �������� readPowerTranser
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    msgid : const string&                                 �������ĺ�
			 *    decoder : const string&                               ����������
			 */
			void readPowerTranser(const string& msgid, const string& decoder);

			/** ��������.
			 *  �������� decode 
			 *  ����ֵ�� SmartData        ������ĵ������ݿ�
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    ParamBuffer                   const Ice::ByteSeq&     ��������
			 */
			SmartData decode(const Ice::ByteSeq& ParamBuffer);

			/** �Ե��Ľ���ɸѡ���˴���.
			 *  �������� filter 
			 *  ����ֵ�� bool        �Ƿ���ϴ�������
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    data  :       SmartData&        						�����ֶ�
			 */
			bool filter(SmartData& data);

			/** ��ȡ���Ĵ����趨.
			 *  �������� getSetting 
			 *  ����ֵ�� MsgSetting        �趨
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 * 
			 */
			MsgSetting getSetting();
		};
	};
};
