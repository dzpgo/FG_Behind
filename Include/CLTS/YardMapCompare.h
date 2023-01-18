//********************************************************************
//** Copyright (c) 2016 �������
//** �����ˣ�������
//** ������\�ļ�����YardMapCompare.h
//** �๦�ܣ���ͼ���ݽṹ�ıȽϺ���
//** ������
//** �������ڣ�2016-12-5
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#pragma once
#include <Slice/Saddle.h>

namespace CLTS
{
	struct lesserSaddleDesc
	{
		bool operator()(const SaddleDesc& desc1, const SaddleDesc& desc2) const
		{
			if (desc1.colRowNo == desc2.colRowNo)
			{
				if (desc1.seqSaddle < desc2.seqSaddle)
					return true;
				else if (desc1.seqSaddle == desc2.seqSaddle)
					return 0;
				else
					return false;
			}
			else
			{
				char szTmp[512];
				sprintf_s(szTmp, 512, "����%s�배��%s����ͬһ���޷���������", desc1.no.c_str(), desc2.no.c_str());
				throw invalid_argument(szTmp);
			}
		}
	};
};