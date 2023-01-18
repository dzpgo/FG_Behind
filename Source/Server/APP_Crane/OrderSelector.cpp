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
		log.Debug()<<"   已经进入指令选择器 OrderSelector::Selector()，准备开始调用  resolver_WMSCraneOrde()......"<<endl;

		//20220620 zhangyuhong add
		//重写 指令解析 逻辑
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
			log.Debug()<<"   resolver_WMSCraneOrde() 返回错误！指令子弹压膛失败！......"<<endl;
			ret  = false;
			return ret;
		}
		
		//更新指令状态为  COIL_UP
		log.Debug()<<"   指令相关数据已经准备就绪，并已写入行车当前指令表，准备更新表中的指令状态为 COIL_UP_PROCESS......"<<endl;
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