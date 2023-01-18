/*********************************************************************
 *		
 *  文      件:    MsgSmartDataManager.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2014-05-08    haykin    //TODO请添加本次主要修改内容
 *      %USER%   
*********************************************************************/
#pragma once
#include <map>
#include <PowerTranser/MsgSmartData.h>
namespace iPlature
{
	typedef std::vector<std::string> MsgNameArray_t;

	class MsgSmartDataManager
	{
	public:
		static MsgSmartDataManager& InsRef();
		~MsgSmartDataManager(void){}

		//init all msg
		void InitAllMsgSmartData();
		void InitAllMsgSmartData(iDA::Connection& cnn);

		//int msg with spec destination. eg. L2, L3
		void InitDestMsgSmartData(const std::string& dest);
		void InitDestMsgSmartData(const std::string& dest, iDA::Connection& cnn);

		//int spec msg
		void InitMsgSmartData(const MsgNameArray_t& msgnames);
		void InitMsgSmartData(const MsgNameArray_t& msgnames, iDA::Connection& cnn);

		void InitRegexMsgSmartData(const std::string& strRegex);
		void InitRegexMsgSmartData(const std::string& strRegex, iDA::Connection& cnn);

		void InitDirectMsgSmartData(const std::string& strSource,const std::string& strDest);
		void InitDirectMsgSmartData(const std::string& strSource,const std::string& strDest, iDA::Connection& cnn);

		//get msg smart
		SmartData& GetMsgSmartData(const std::string& msgname);

		bool Empty() const;

	private:
		MsgSmartDataManager(void){}

		void InitMsgSmartData(const std::string& msgname, iDA::Connection& cnn);

		void InitMsgSmartData(const std::string& msgname);

		void OpenDefaultCnn(iDA::Connection& cnn);


	private:

		static MsgSmartDataManager* _ins;

		typedef std::map<std::string, SmartData*> MsgSDContainer_t;
		MsgSDContainer_t _sdContainer;
	};
}

