/*********************************************************************
 *		
 *  ��      ��:    ClientManager.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2013-07-22    hanlu    ClientManager
 *      %USER%   
*********************************************************************/
#include "ClientStatus.h"
#include <string>

using namespace std;

namespace iPlature
{
	enum StatusEnum
	{
		STATUS_FAILED,
		STATUS_SUCCESS,
		STATUS_UNKNOWN
	};
	class ClientManager
	{
	public:
		
		/**********************************************************************
		 *  ����: //TODO:����Ӻ�������
		 *  �������� SetClientStatus 
		 *  ����ֵ�� int	 	//TODO:����ֵ����
		 *  �����б�	��������    					ȡֵ��Χ     		    ����
		 *    strName  :    [IN/OUT] string	          						   Ӧ������
		 *    nStatus  :    [IN/OUT] int	            StatusEnum		       Ӧ��״̬
		 *
		 *  �汾��ʷ		
		 *       1.0    2013-07-22  hanlu    //TODO����ӱ�����Ҫ�޸�����
		 *  
		 **********************************************************************/
		static int SetClientStatus(string strName,int nStatus);
	};


}
