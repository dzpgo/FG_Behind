/*********************************************************************
*		
*  文      件:    MDProxy.h   		通知用户接口
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：//TODO请添加本文件包含功能详细描述
*        ：//TODO
*        ：//TODO
*
*  版本历史		
*      1.1    2009-09-19  jacklu    实现功能
*      %USER%   
*********************************************************************/

#ifndef __MDPROXY_H__
#define __MDPROXY_H__

#include <imultilink/MLDefineEx.h>

//#  ifdef IMULTILINK_BUILD_DLL
//#    define IMULTILINK_EXPORT __declspec(dllexport)
//#  else
//#    define IMULTILINK_EXPORT __declspec(dllimport)
//#  endif

#define IMULTILINK_EXPORT extern "C" __declspec(dllexport)

#define _Interface 
#define IN 
#define OUT
#define INOUT

/**********************************************************************
*  概述: 事件触发
*  函数名： MLEventPut 
*  返回值： IMULTILINK_EXPORT int	 	0：成功，10001：失败
*  参数列表：		参数类型    						取值范围     		    描述
*    mapTagPairs  :[IN] IN const MapItemNameValue &		//TODO:参数取值范围		L2Tag名及其值的列表
*    strEventName :[IN] IN const ::std::string &	    //TODO:参数取值范围		L2事件名称
*    strEventValue:[IN] IN const ::std::string &	    //TODO:参9数取值范围	事件值
*
*  版本历史		
*       1.1    2009-09-19  jacklu    实现功能
*       1.1    2009-09-25  jacklu    添加调用方式。完成slice调用方式
*  
**********************************************************************/
IMULTILINK_EXPORT int MLEventPut(IN const MapItemNameValue& mapTagPairs, IN const ::std::string& strEventName, IN const ::std::string& strEventValue);

/**********************************************************************
*  概述: 周期触发
*  函数名： MLCyclicPut 
*  返回值： IMULTILINK_EXPORT int	 	0：成功，10001：失败
*  参数列表：			参数类型    					取值范围     		    描述
*    strSchedulerName: [IN] IN int						//TODO:参数取值范围		L1周期名称
*    mapTagPairs  :    [IN] IN const MapItemNameValue&	//TODO:参数取值范围		L2Tag名及其值的列表
*
*  版本历史		
*       1.1    2009-09-19  jacklu    实现功能
*       1.1    2009-09-25  jacklu    添加调用方式。完成slice调用方式
*  
**********************************************************************/
IMULTILINK_EXPORT int MLCyclicPut(IN const std::string& strSchedulerName, IN const MapItemNameValue& mapTagPairs);

#  endif