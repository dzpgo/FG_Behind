/*********************************************************************
 *		
 *  文      件:    HMIControlContainer.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2011-09-22    haykin    //TODO请添加本次主要修改内容
 *      1.1    2013-09-22	 haykin    获取容器中所有控件key值  
*********************************************************************/
#pragma once
#include <pace/SmartData.h>
#include <HMIServer/HMIControl.h>

namespace iPlature
{
	
	class HMIControlContainer
	{
	public:
		HMIControlContainer(const SmartData& sd);
		HMIControlContainer(void);

		HMIControlContainer(const SmartData& sd, const string& serverKey);
		HMIControlContainer(const string& serverKey);

		~HMIControlContainer(void);

		template<typename T>
		T& GetControl(const string& strKey);

		void ClearAll();

		void ClearControl(const string& strKey);


		void UpdateControl(const SmartData& sd);

		SmartData GetSmartData();
		
		std::map<std::string, std::string>& GetMapData();
		
		void SetData(const SmartData& sd);

		/*template<typename T>
		static T& GetHMIControl(const string& strKey);*/

		void SetServerKey(const string& strKey);


		/**********************************************************************
		 *  概述: 获取容器中所有控件key值
		 *  函数名： GetAllControlKey 
		 *  返回值： std::vector<std::string>	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *
		 *  版本历史		
		 *       1.0    2013-09-22  haykin    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		std::vector<std::string> GetAllControlKey() const;

	private:
		typedef map<string, HMIControl*> Control_Map;
		Control_Map _data;
		SmartData _sd;

		std::string _serverkey;

		std::map<std::string, std::string> _mpData;
		bool _bIvalidate;

	};

	template<typename T>
	T& HMIControlContainer::GetControl(const string& strKey)
	{
		_bIvalidate = true;
		Control_Map::iterator it = _data.find(strKey);
		if (it == _data.end())
		{
			HMIControl* p = NULL;
			try
			{
				SmartData& sd = _sd[strKey];
				p = new T(sd, _serverkey);
			}
			catch (const SmartDataException&)
			{
				p = new T(strKey, _serverkey);
			}
			it = _data.insert(make_pair(strKey, p)).first;
		}
		T* p = dynamic_cast<T*>(it->second);
		return *p;
	}

	
}

