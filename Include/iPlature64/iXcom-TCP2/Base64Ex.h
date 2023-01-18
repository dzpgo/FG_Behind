/*********************************************************************
*  类      名:   	CBase64Ex
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*  类 职 责： 将二进制数据编码解码成BASE64码
*  版本历史		
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

		//二进制数转换成BASE64码
		static char *Encrypt(const char * srcp, int len, char * dstp);

		//BASE64码转换成二进制码
		static void *Decrypt(const char * srcp, int len, char * dstp);

		//BASE64码长度
		static size_t B64_length(size_t len)
		{
			size_t  npad = len%3;
			size_t  size = (npad > 0)? (len +3-npad ) : len; // padded for multiple of 3 bytes
			return  (size*8)/6;
		}

		//二进制码长度
		static size_t Ascii_length(size_t len)
		{
			return  (len*6)/8;
		}
	};
}

