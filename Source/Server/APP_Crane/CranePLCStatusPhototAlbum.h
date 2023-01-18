/*********************************************************************
 *		
 *  ��      ��:    CranePLCStatusPhototAlbum.h   		
 *
 *
 *  ������
 *        ��CranePLCStatusPhtotAlbum �ǵ�����
 *        �������г�PLC����������״̬��Ϣ����Ƭ��һ�����ţ�Ϊ����Ƭ������Ƭ
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/
#pragma once
#ifndef _CranePLCStatusPhototAlbum_
#define _CranePLCStatusPhototAlbum_


#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "CranePLCStatusBase.h"

namespace Monitor
{



		class CranePLCStatusPhototAlbum
		{


		public:
				CranePLCStatusPhototAlbum(void);

				~CranePLCStatusPhototAlbum(void);

		private:
			//�г���
			string craneNO;
		public:
			string getCraneNO();
			void setCraneNO(string theVal);

		private:
			//����Ƭ������־λ
			bool oldPhotoOK;
			//����Ƭ������־λ
			bool newPhotoOK;
			//������������־λ
			bool PhtotAlbumOK;
		public:
			//���������������־λ�ķ���
			bool getPhtotAlbumOK();

		private:
			//����Ƭ
			CranePLCStatusBase cranePLCStatusNew;
			//����Ƭ
			CranePLCStatusBase cranePLCStatusOld;

		public:
			//�������Ƭ�ķ���
			CranePLCStatusBase getCranePLCStatusNew();
			//�������Ƭ�ķ���
			CranePLCStatusBase getCranePLCStatusOld();

			//���ⲿ��������Ƭ�����
			//�ⲿ��ֵ���κ�������
			void inputPLCStatus(CranePLCStatusBase cranePLCStatusBase);



		};




}
#endif