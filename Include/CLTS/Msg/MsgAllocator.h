//********************************************************************
//** Copyright (c) 2016 �������
//** �����ˣ�������
//** ������\�ļ�����MsgAllocator.h
//** �๦�ܣ����Ĵ��������
//** ���������ݷ����ļ��趨�ķ������ã������ķ����ָ�����������
//** �������ڣ�2016-9-21
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#pragma once
#include <Msg/MsgSetting.h>
#include <map>
#include <Ice/Ice.h>

using namespace std;

namespace CLTS
{
	namespace MSG
	{
		class MsgAllocator
		{
		// msgidӳ������趨
		typedef multimap<string, MsgSetting> MapMsgId2Settings;

		private:
			MapMsgId2Settings m_mapSettings;	// ���ķ����趨

		public:
			MsgAllocator(void);
			~MsgAllocator(void);

			/** ��ȡ�ļ��ڵĵ��ķ����趨.
			 *  �������� loadSettingFile 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    settingFile��string                                   �趨�ļ�����ȫ��·����
			 */
			void loadSettingFile(string settingFile);

			/** ������ĵ���Ӧ�Ĵ������.
			 *  �������� allocate 
			 *  ����ֵ�� bool        ������
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    data    :     Ice::ByteSeq&                           ��������
			 */
			bool allocate(Ice::ByteSeq& data);
		};
	};
};