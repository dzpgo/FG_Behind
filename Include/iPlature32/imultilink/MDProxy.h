/*********************************************************************
*		
*  ��      ��:    MDProxy.h   		֪ͨ�û��ӿ�
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������//TODO����ӱ��ļ�����������ϸ����
*        ��//TODO
*        ��//TODO
*
*  �汾��ʷ		
*      1.1    2009-09-19  jacklu    ʵ�ֹ���
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
*  ����: �¼�����
*  �������� MLEventPut 
*  ����ֵ�� IMULTILINK_EXPORT int	 	0���ɹ���10001��ʧ��
*  �����б�		��������    						ȡֵ��Χ     		    ����
*    mapTagPairs  :[IN] IN const MapItemNameValue &		//TODO:����ȡֵ��Χ		L2Tag������ֵ���б�
*    strEventName :[IN] IN const ::std::string &	    //TODO:����ȡֵ��Χ		L2�¼�����
*    strEventValue:[IN] IN const ::std::string &	    //TODO:��9��ȡֵ��Χ	�¼�ֵ
*
*  �汾��ʷ		
*       1.1    2009-09-19  jacklu    ʵ�ֹ���
*       1.1    2009-09-25  jacklu    ��ӵ��÷�ʽ�����slice���÷�ʽ
*  
**********************************************************************/
IMULTILINK_EXPORT int MLEventPut(IN const MapItemNameValue& mapTagPairs, IN const ::std::string& strEventName, IN const ::std::string& strEventValue);

/**********************************************************************
*  ����: ���ڴ���
*  �������� MLCyclicPut 
*  ����ֵ�� IMULTILINK_EXPORT int	 	0���ɹ���10001��ʧ��
*  �����б�			��������    					ȡֵ��Χ     		    ����
*    strSchedulerName: [IN] IN int						//TODO:����ȡֵ��Χ		L1��������
*    mapTagPairs  :    [IN] IN const MapItemNameValue&	//TODO:����ȡֵ��Χ		L2Tag������ֵ���б�
*
*  �汾��ʷ		
*       1.1    2009-09-19  jacklu    ʵ�ֹ���
*       1.1    2009-09-25  jacklu    ��ӵ��÷�ʽ�����slice���÷�ʽ
*  
**********************************************************************/
IMULTILINK_EXPORT int MLCyclicPut(IN const std::string& strSchedulerName, IN const MapItemNameValue& mapTagPairs);

#  endif