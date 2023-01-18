// YardMap_Global_Def.h
#pragma once

#include <Util.h>

// װж��
#include <Slice/LoadUnLoadFactory.h>
// ��ͼ
#include <Slice/Area.h>
#include <Slice/Bay.h>
#include <Slice/Coil.h>
#include <Slice/RowCol.h>
#include <Saddle.h>
#include <Slice/Stock.h>
#include <Slice/Yard.h>
#include <Slice/YardMapFactory.h>
#include <Slice/ProdLine.h>

namespace CLTS
{
    namespace Common
    {
        ///////////////////////////////////////////////////////////////////////////////
		// Ӧ�ó��������ļ�

		static const int DEVIATION_X = 800;	// �������������
		static const int DEVIATION_Y = 800;	// С�������������
		
		inline bool parseTruckStockNo(const string& stockNo, string& parkingNo)
		{
			bool bResult = false;
			size_t pos = stockNo.find("_");
			if (pos != string::npos)
			{
				parkingNo = stockNo.substr(0, pos);
				bResult = true;
			}
			return bResult;
		}

		//С������ת��
		inline AreaType convertToAreaType(int value)
		{
			AreaType areaType = NormalArea;
			switch (value)
			{
			case 0:
				areaType = NormalArea; 
				break;
			case 1:
				areaType = SmalCoilArea;
				break;
			case 2:
				areaType = ManPickArea;
				break;
			case 3:
				areaType = TaoTongArea;
				break;
			case 4:
				areaType = LineRWArea;
				break;
			case 5:
				areaType = LineCWArea;
				break;
			default:
				throwCltsEx(__FILE__, __LINE__, "ת��С������", "ֵ�Ƿ�","ֵ%d��С��ö������", value);
			}

			return areaType;
		}

		inline SaddleType convert2SaddleType(int value)
		{
			SaddleType type = Fixed4Coil;
			switch (value)
			{
			case 0:
				type = Fixed4Coil; 
				break;
			case 1:
				type = Wave4Coil;
				break;
			case 2:
				type = Fixed4Slab;
				break;
			case 3:
				type = Free4Slab;
				break;
			case 4:
				type = LineEntry;
				break;
			case 5:
				type = LineExit;
				break;
			case 6:
				type = Reserved;
				break;
			default:
				throwCltsEx(__FILE__, __LINE__, "convert INT to SaddleType", "ת��SaddleType����","ֵ%dδ��ö�������ж���", value);
			}

			return type;
		}

		inline StockStatus convert2StockStatus(int value)
		{
			StockStatus status = StockOccupied;
			switch (value)
			{
			case 0:
				status = StockEmpty; 
				break;
			case 1:
				status = StockReserved;
				break;
			case 2:
				status = StockOccupied;
				break;
			default:
				throwCltsEx(__FILE__, __LINE__, __FUNCTION__, "ת��StockStatus����", "ֵ%dδ��ö�������ж���", value);
			}

			return status;
		}

		inline LockStatus convert2LockStatus(int value)
		{
			LockStatus status = StockConfirmed;
			switch (value)
			{
			case 0:
				status = StockConfirmed; 
				break;
			case 1:
				status = StockWaitChecking;
				break;
			default:
				throwCltsEx(__FILE__, __LINE__, __FUNCTION__, "ת��LockStatus����", "ֵ%dδ��ö�������ж���", value);
			}

			return status;
		}


		inline StockType convert2StockType(int value)
		{
			StockType type = StockSaddle;
			switch (value)
			{
			case 0:
				type = StockSaddle;
				break;
			case 1:
				type = StockProdLine;
				break;
			case 2:
				type = StockCrane;
				break;
			case 3:
				type = StockTruck;
				break;
			default:
				throwCltsEx(__FILE__, __LINE__, __FUNCTION__, "ת��StockType����", "ֵ%dδ��ö�������ж���", value);
			}

			return type;
		}

		inline RecommType convert2RecommType(int value)
		{
			RecommType type = RecommByL3;
			switch (value)
			{
			case 0:
				type = RecommByMM;
				break;
			case 1:
				type = RecommByL3;
				break;
			default:
				throwCltsEx(__FILE__, __LINE__, __FUNCTION__, "ת��RecommType����", "ֵ%dδ��ö�������ж���", value);
			}

			return type;
		}
    };
};
