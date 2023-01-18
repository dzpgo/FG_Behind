#include "OrderSelector.h"

using namespace Monitor;

OrderSelector::OrderSelector()
{

}
OrderSelector::~OrderSelector()
{

}

bool OrderSelector::Selector(string craneNO)
{
	bool ret = true;
	string functionName = "OrderSelector::selector()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"   �Ѿ�����ָ��ѡ���� OrderSelector::Selector()��׼����ʼ����  resolver_WMSCraneOrde()......"<<endl;

		//20220620 zhangyuhong add
		//��д ָ����� �߼�
		OrderQueueBase orderQueueData;
		if (false == WMSCraneOrder_Resolver::SelCraneOrder(craneNO, orderQueueData))
		{
			log.Info()<<"   SelCraneOrder() can not find order ...... return false..................."<<endl;
			ret  = false;
			return ret;
		}

		OrderCurrentBase  orderCurrentBase;
		if(false == WMSCraneOrder_Resolver::resolver_WMSCraneOrder(orderQueueData, orderCurrentBase))
		{
			log.Debug()<<"   resolver_WMSCraneOrde() ���ش���ָ���ӵ�ѹ��ʧ�ܣ�......"<<endl;
			ret  = false;
			return ret;
		}
		
		//����ָ��״̬Ϊ  COIL_UP
		log.Debug()<<"   ָ����������Ѿ�׼������������д���г���ǰָ���׼�����±��е�ָ��״̬Ϊ COIL_UP_PROCESS......"<<endl;
		Adapter_UACS_CRANE_ORDER_CURRENT::update_CMDStatus(craneNO, CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS);
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return ret;
}