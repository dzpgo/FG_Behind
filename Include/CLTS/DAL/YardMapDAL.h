#pragma once
#include <CLTS.h>
#include <Slice/YardMapFactory.h>

namespace CLTS
{
	namespace DAL
	{
		const static int EMPTY_POSITION = 9999;

		class YardMapDAL
		{
		private:
			string m_strDbCfgFile; // 数据库连接配置文件
			iDA::Connection* m_pCon; // 数据库联接

		public:
			YardMapDAL(string strDbCfgFile, iDA::Connection* pCon);
			~YardMapDAL(void);

			/** 库图新增行车库位.
			 *  函数名： insertStock 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    stockDesc : StockDesc 								库位
			 */
			void insertCraneStock(StockDesc stockDesc);

			/** 库图新增鞍座库位.
			 *  函数名： insertStock 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    stockDesc : StockDesc 								库位
			 *    saddleDesc : SaddleDesc 								鞍座
			 */
			void insertStock(StockDesc stockDesc, SaddleDesc saddleDesc);

			/** 根据坐标找到鞍座号.
			 *  函数名： getSaddleNoByPos 
			 *  返回值： StringSeq				找到的鞍座号                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    bayNo : const string& 								跨号
			 *    posX : int											大车坐标
			 *    posY : int											小车坐标
			 */
			StringSeq getSaddleNoByPos(const string& bayNo, int posX, int posY);

			/** 根据坐标找到库位号.
			 *  函数名： getStockNoByPos 
			 *  返回值： bool                   是否找到库位
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    bayNo : const string& 								跨号
			 *    posX : int											大车坐标
			 *    posY : int											小车坐标				
			 *    stockNo : string&										小车坐标				
			 */
			bool getStockNoByPos(const string& bayNo, int posX, int posY, string& stockNo);

			/** 根据坐标找到停车位号.
			 *  函数名： getParkingNoByPos 
			 *  返回值： bool                   是否找到停车位
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneNo : const string& 								行车号
			 *    posX : int											大车坐标
			 *    posY : int											小车坐标				
			 *    stockNo : string&										小车坐标				
			 */
			bool getParkingNoByPos(const string& craneNo, int posX, int posY, string& parkingNo);

			/** 根据行车号找到跨号.
			 *  函数名： insertStock 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneNo : const string& 								行车号
			 */
			string getBayNobyCrane(const string& craneNo);

			/** 根据起吊库位号找到起吊坐标.
			 *  函数名： getLiftUpPosByStockNo 
			 *  返回值： bool                   是否找到库位
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    bayNo : const string& 								跨号
			 *    posX : int											大车坐标
			 *    posY : int											小车坐标				
			 *    stockNo : string&										小车坐标				
			 */
			bool getLiftUpPosByStockNo(const string& stockNo, int& posX, int& posY, int& posZ);

			/** 根据落关库位号找到落关坐标.
			 *  函数名： getLiftDownPosByStockNo 
			 *  返回值： bool                   是否找到库位
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    bayNo : const string& 								跨号
			 *    posX : int											大车坐标
			 *    posY : int											小车坐标				
			 *    stockNo : string&										小车坐标				
			 */
			bool getLiftDownPosByStockNo(const string& stockNo, int& posX, int& posY, int& posZ);

			/** 落关失败的后备操作函数.
			 *  函数名： liftDownAfterError 
			 *  返回值： void                   无
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    stockNo : const string& 								库位号
			 *    current : const Ice::Current&                         调用端信息
			 */
			void liftDownError(const string& stockNo, const Current& current);
		};
	}
}
