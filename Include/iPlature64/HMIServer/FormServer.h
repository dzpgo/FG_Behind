/*********************************************************************
 *		
 *  ��      ��:    FormServer.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2012-01-30    Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
 *      1.1	2012-01-30	  Haykin             ����ClientStandby�ӿ�   
*********************************************************************/
#ifndef __HMISERVER_FORMSERVER_H__
#define __HMISERVER_FORMSERVER_H__

#include <string>
#include <HMIServer/HMIControlContainer.h>
namespace iPlature
{
	class HMIComponent;
	class FormServer
	{
	public:
		FormServer(const std::string& serverKey);
		virtual ~FormServer(void);

		virtual void InitForm();

		virtual void ClientActive(const ::std::string& clientKey, 	const ::std::string& formKey);

		virtual void ClientUnactive(const ::std::string& clientKey, 	const ::std::string& formKey);

		virtual void HandleClientMessage(const SmartData& data
															, const std::string& comeFrom
															, const std::string& formKey
															, const std::string& stCmd) = 0;
		virtual void ClientStandby(const std::string& clientKey);

		void UpdateControl(const ::std::string& clientKey, HMIControl& ctl);
		void UpdateControl(HMIControl& ctl);

		void UpdateForm(const ::std::string& clientKey);
		void UpdateForm();

		void UpdateControl(const ::std::string& clientKey, const SmartData& sd);
		void UpdateControl(const SmartData& sd);

		void UpdateForm(const ::std::string& clientKey, const SmartData& sd);
		void UpdateForm(const SmartData& sd);

		std::string ServerKey() const;
		void UpdateContainerData(const SmartData&);
	protected:
		std::string _serverKey;
		HMIControlContainer _ctlContainer;
		HMIComponent* _pComp;
	};

	inline std::string FormServer::ServerKey() const {return _serverKey;}
}

#endif

