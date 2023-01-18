// DBConst.h

#pragma once
#include <DAL/YardMapDAL.h>
#include <DAL/CoilDAL.h>
#include <DAL/StockAlgrDAL.h>
#include <DAL/EventDAL.h>

extern iDA::Connection g_iDACon; // 数据库连接

namespace CLTS
{
    namespace Common
    {
        ///////////////////////////////////////////////////////////////////////////////
		// 应用程序配置文件
		static const string APPCFGFILE =  "uacs.global.conf";

		static const string NAME_YARDMAP_FACTORY = "YardMapFactory";
		static const string CATEGORY_YARDMAP_BAY = "BAY";
		static const string CATEGORY_YARDMAP_AREA = "AREA";
		static const string CATEGORY_YARDMAP_COIL = "COIL";
		static const string CATEGORY_YARDMAP_ROWCOL = "ROWCOL";
		static const string CATEGORY_YARDMAP_SADDLE = "SADDLE";
		static const string CATEGORY_YARDMAP_STOCK_SADDLE = "STOCK_SADDLE";
		static const string CATEGORY_YARDMAP_STOCK_PROD_LINE = "STOCK_PRODLINE";
		static const string CATEGORY_YARDMAP_STOCK_CRANE = "STOCK_CRANE";
		static const string CATEGORY_YARDMAP_STOCK_TRUCK = "STOCK_TRUCK";
		static const string CATEGORY_YARDMAP_RECOMM = "RECOMMEND";
		static const string NAME_LOAD_FACTORY = "LoadUnloadFactory";
    };
};
