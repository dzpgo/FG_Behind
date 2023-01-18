/*********************************************************************
 *		
 *  ��      ��:    FileUtil.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2011-08-31    Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
 *      %USER%   
*********************************************************************/
#pragma once
#include <string>
namespace iPlature
{
	class FileUtil
	{
	public:
		/**********************************************************************
		 *  ����: make directory
		 *  �������� mkdir 
		 *  ����ֵ�� int	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    path  :    [IN/OUT] const std::string &	     ·��
		 *    recursive  :    [IN/OUT] bool					Allows the creation of nested directories specified in the pathname. Defaults to FALSE��or can create only one new directory per call, so only the last component of dirname can name a new directory
		 *    mode  :    [IN/OUT] int							he mode is 0777 by default, which means the widest possible access
		 *
		 *  �汾��ʷ		
		 *       1.0    2011-08-31  Haykin-2010    create
		 *  
		 **********************************************************************/
		static int MkDir(const std::string& path, bool recursive = false, int mode = 0777);

		/**********************************************************************
		 *  ����: //TODO:����Ӻ�������
		 *  �������� GetAppName 
		 *  ����ֵ�� std::string	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    path  :    [IN/OUT] const std::string &	     //TODO:����ȡֵ��Χ		  <//TODO:��������>
		 *
		 *  �汾��ʷ		
		 *       1.0    2011-08-31  Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
		 *  
		 **********************************************************************/
		static std::string GetAppName(const std::string& path);
	};
}

