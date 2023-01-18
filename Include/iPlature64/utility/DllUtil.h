/*********************************************************************
 *		
 *  ��      ��:    DllUtil.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2013-08-20    hanlu    create
 *      %USER%   
*********************************************************************/
#pragma once
#include <string>

#ifdef _WIN32
#	include <windows.h> 
#	include <tchar.h> 
#else
#	include <dlfcn.h>
#endif


namespace iPlature
{
#ifdef _WIN32
	typedef HMODULE DLLHandle;
	typedef FARPROC DLLFunAddress;
#else
	typedef void* DLLHandle;
	typedef void* DLLFunAddress;
#endif

	class DllUtilException : public std::exception
	{
	public:
		DllUtilException(const std::string& msg):_what(msg){}
		virtual ~DllUtilException() throw(){}
		virtual const char* what() const throw(){return _what.c_str();}
	private:
		std::string  _what;
	};

	class DllUtil
	{
	public:
		/**********************************************************************
		 *  ����: ���ض�̬�� ������ʧ�ܷ���NULL
		 *  �������� LoadDll 
		 *  ����ֵ�� iPlature::DLLHandle	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    dllName  :    [IN] std::string	     //TODO:����ȡֵ��Χ		��̬��·��
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-09-23  hanlu     create
		 *  
		 **********************************************************************/
		static DLLHandle LoadDll(const std::string& dllName);
		

		/**********************************************************************
		 *  ����: ��ȡ��̬����ָ��������ַ, ����ȡʧ�ܷ���NULL
		 *  �������� GetFunAddress 
		 *  ����ֵ�� iPlature::DLLFunAddress	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    hModule  :    [IN] DLLHandle	     //TODO:����ȡֵ��Χ		  
		 *    procName  :    [IN] std::string	     //TODO:����ȡֵ��Χ		  
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-09-23  hanlu     create
		 *  
		 **********************************************************************/
		static DLLFunAddress GetFunAddress(DLLHandle hModule, const std::string& fucName);


		/**********************************************************************
		 *  ����: �ͷŶ�̬�� ��ʧ�ܷ���false
		 *  �������� FreeDll 
		 *  ����ֵ�� void	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    hModule  :    [IN/OUT] DLLHandle	     //TODO:����ȡֵ��Χ		  <//TODO:��������>
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-09-23  hanlu    //TODO����ӱ�����Ҫ�޸�����
		 *  
		 **********************************************************************/
		static bool FreeDll(DLLHandle hModule);

		/**********************************************************************
		 *  ����: ������Ϣ
		 *  �������� DllError 
		 *  ����ֵ�� std::string	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-09-23  haykin    //TODO����ӱ�����Ҫ�޸�����
		 *  
		 **********************************************************************/
		static std::string DllError();

		/**********************************************************************
		 *  ����: ����ָ����̬�� ��ʧ���׳��쳣
		 *  �������� LoadDllEx 
		 *  ����ֵ�� iPlature::DLLHandle	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    dllName  :    [IN/OUT] const std::string &	     //TODO:����ȡֵ��Χ		  <//TODO:��������>
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-09-24  haykin    //TODO����ӱ�����Ҫ�޸�����
		 *  
		 **********************************************************************/
		static DLLHandle LoadDllEx(const std::string& dllName);

		/**********************************************************************
		*  ����: ��ȡ��̬����ָ��������ַ����̬�������һ�Σ� ��ʧ���׳��쳣
		*  �������� GetFunAddress 
		*  ����ֵ�� iPlature::DLLFunAddress	 	//TODO:����ֵ����
		*  �����б�	��������    					ȡֵ��Χ     		    ����
		*    dllName  :    [IN/OUT] std::string	     //TODO:����ȡֵ��Χ		  ��̬������
		*    procName  :    [IN/OUT] std::string	     //TODO:����ȡֵ��Χ		  ��������
		*
		*  �汾��ʷ		
		*       1.0    2013-09-23  haykin   create
		*  
		**********************************************************************/
		static DLLFunAddress GetFunAddressEx(DLLHandle hModule, const std::string& fucName);
		static DLLFunAddress GetFunAddressEx(const std::string& dllName, const std::string& fucName);

		/**********************************************************************
		 *  ����: �ͷŶ�̬�� ��ʧ���׳��쳣
		 *  �������� FreeDllEx 
		 *  ����ֵ�� bool	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    hModule  :    [IN/OUT] DLLHandle	     //TODO:����ȡֵ��Χ		  <//TODO:��������>
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-09-24  haykin    //TODO����ӱ�����Ҫ�޸�����
		 *  
		 **********************************************************************/
		static bool FreeDllEx(DLLHandle hModule);

		static bool FreeDllEx(const std::string& dllName);

	};


	


	
}