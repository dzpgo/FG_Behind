//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 创建人：张晓荣
//** 类名称\文件名：YardMapCompare.h
//** 类功能：库图数据结构的比较函数
//** 描述：
//** 创建日期：2016-12-5
//** 修改人：
//** 修改日期：
//** 整理日期：
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
				sprintf_s(szTmp, 512, "鞍座%s与鞍座%s不在同一排无法进行排序", desc1.no.c_str(), desc2.no.c_str());
				throw invalid_argument(szTmp);
			}
		}
	};
};