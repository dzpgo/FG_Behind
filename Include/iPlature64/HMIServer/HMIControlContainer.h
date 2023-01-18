/*********************************************************************
 *		
 *  ��      ��:    HMIControlContainer.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2011-09-22    haykin    //TODO����ӱ�����Ҫ�޸�����
 *      1.1    2013-09-22	 haykin    ��ȡ���������пؼ�keyֵ  
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
		 *  ����: ��ȡ���������пؼ�keyֵ
		 *  �������� GetAllControlKey 
		 *  ����ֵ�� std::vector<std::string>	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-09-22  haykin    //TODO����ӱ�����Ҫ�޸�����
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

