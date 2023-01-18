/*********************************************************************
*  类      名:   	HMIServerComponent
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*  类 职 责：HMIServer框架类
*              ：
*              ：
*  版本历史		
*       1.0    2010-11-01    Haykin-2010    //create
*		 1.1	 2011-08-22		Haykin-2011	新增参数为SmartData的Update
*********************************************************************/
#pragma once
#include <pace/pace.h>
#include <pace/Component.h>
#include <pace/P99Component.h>
#include <pace/SmartData.h>

#include <HMIServer/FormServer.h>
#include <HMIServer/HMIServerException.h>
#include <HMIServer/HMIControlContainer.h>

namespace iPlature
{
	class HMIComponent : public Component
	{
	public:
	
		virtual ~HMIComponent();
		virtual void StartUp() = 0;
		virtual void ShutDown() {}
		

		void RegisterServer(FormServer* pFormServer);

		int start();

		void UpdateControl2Client(HMIControl& ctl, const std::string& serverKey, const ::std::string& clientKey);
		void UpdateControl2Client(HMIControl& ctl, const std::string& serverKey);

		void UpdateControl2Client(const SmartData& sd, const std::string& serverKey, const ::std::string& clientKey);
		void UpdateControl2Client(const SmartData& sd, const std::string& serverKey);

		void UpdateForm2Client(HMIControlContainer& ctlContainer, const std::string& serverKey, const ::std::string& clientKey);
		void UpdateForm2Client(HMIControlContainer& ctlContainer, const std::string& serverKey);

		void UpdateForm2Client(const SmartData& sd, const std::string& serverKey, const ::std::string& clientKey);
		void UpdateForm2Client(const SmartData& sd, const std::string& serverKey);


		virtual void HandleServerMessage(Ice::ByteSeq&){}

		void RegisterP99Componet();

		void RegisterP99Componet(const std::string& p99name);

		
	public:
		void stop();

	private:
		std::string DefaultP99Name();

	protected:
		std::string _serverProcess;

		
	};

	class HMIServerComponent : public HMIComponent
	{
	public:
		HMIServerComponent();

		virtual ~HMIServerComponent();

		virtual void InitForm();
		/**********************************************************************
		 *  概述:  画面信息处理函数。但后台接收到前台画面信息时，该函数被调用。用户必须继承实现该方法
		 *  
		 **********************************************************************/
		virtual void HandleClientMessage(const SmartData& data,const std::string& comeFrom, const std::string& stCmd) {}

		virtual void HandleClientMessage(const SmartData& data
																,const std::string& comeFrom
																,  const std::string& formKey
																, const std::string& stCmd) {}

		/**********************************************************************
		 *  概述: 向HMIServerManager注册服务
		 *  
		 **********************************************************************/
		void RegisterForm(const string& serverKey);


		/**********************************************************************
		 *  概述: 前台客户端被激活
		 *  
		 **********************************************************************/
		virtual void ClientActive(const ::std::string& clientKey);
		virtual void ClientActive(const ::std::string& clientKey, const std::string& formKey){}


		/**********************************************************************
		 *  概述: 前台客户端未激活
		 *  
		 **********************************************************************/
		virtual void ClientUnactive(const ::std::string& clientKey);
		virtual void ClientUnactive(const ::std::string& clientKey, const std::string& formKey){}

		/**********************************************************************
		 *  概述: 向特定客户端刷新控件
		 *  
		 **********************************************************************/
		//void UpdateControl(const ::std::string& clientKey, const std::string& serverKey, HMIControl& ctl);
		void UpdateControl(const ::std::string& clientKey, HMIControl& ctl);
		void UpdateControl(HMIControl& ctl);

		

		void UpdateForm(const ::std::string& clientKey);
		void UpdateForm();

		/**********************************************************************
		*  概述: 客户端画面打开(非切换)
		*  
		**********************************************************************/
		virtual void ClientStandby(const std::string& clientKey);
		

		HMIControlContainer& GetHMIControlContainer();
		const HMIControlContainer& GetHMIControlContainer() const;




		const string& ServerKey();


	

	protected:	

		string _serverKey;

		HMIControlContainer _ctlContainer;

	private:
	/*	typedef std::map<std::string, FormServer*> ServerFormMap;
		ServerFormMap _mpServerForm;*/
		
	};

	inline HMIControlContainer& HMIServerComponent::GetHMIControlContainer(){	return _ctlContainer; }
	inline const HMIControlContainer& HMIServerComponent::GetHMIControlContainer() const {return _ctlContainer;}

	inline const string& HMIServerComponent::ServerKey(){ return _serverKey;}

	/*template<typename T>
	T& GetHMIGobalControl(const string& strKey)
	{
		Component* pComp = Component::Instance();
		HMIServerComponent* pComp = dynamic_cast<HMIServerComponent*>(Component::Instance());
		return pComp->GetHMIControlContainer().GetControl<T>(strKey);
	}*/
}
