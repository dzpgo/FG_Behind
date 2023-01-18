/*********************************************************************
*  ��      ��:   	CBase64Ex
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*  �� ְ �� �����������ݱ�������BASE64��
*  �汾��ʷ		
*       1.0    2009-10-23    Haykin_2009    
*     
*********************************************************************/
#pragma once
#include <stdio.h>

namespace iXcomTCP2
{
	class CBase64Ex
	{
	public:
		static const char base64_map[];
		static const unsigned char B64_offset[];

		//��������ת����BASE64��
		static char *Encrypt(const char * srcp, int len, char * dstp);

		//BASE64��ת���ɶ�������
		static void *Decrypt(const char * srcp, int len, char * dstp);

		//BASE64�볤��
		static size_t B64_length(size_t len)
		{
			size_t  npad = len%3;
			size_t  size = (npad > 0)? (len +3-npad ) : len; // padded for multiple of 3 bytes
			return  (size*8)/6;
		}

		//�������볤��
		static size_t Ascii_length(size_t len)
		{
			return  (len*6)/8;
		}
	};
}

