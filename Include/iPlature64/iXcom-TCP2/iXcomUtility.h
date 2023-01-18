
/*********************************************************************
*		
*  ��      ��:    iXcomUtility.h   		//TODO������ļ�����
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������//TODO����ӱ��ļ�����������ϸ����
*        ��//TODO
*        ��//TODO
*
*  �汾��ʷ		
*      1.0    2009-06-15    gaoxin    ����
*     
*********************************************************************/
#ifndef __IXCOMUTILITY_H__
#define __IXCOMUTILITY_H__

#include <iXcom-TCP2/iXcomDefine.h>
#include <log4cplus/LOG.h>

namespace iXcomTCP2
{
	template<typename type>
	ArrayMsg& operator<<(ArrayMsg& seq,const type& input)
	{
		int nSize = sizeof(type);
		ArrayMsg::size_type nPreSize = seq.size();
		seq.resize(seq.size() + nSize);		
		memcpy(&seq[nPreSize],&input,nSize);
		return seq;
	}
	template<typename type>
	ArrayMsg& operator>>(ArrayMsg& seq,type& output)
	{
		//throw exception
		if (seq.size() < sizeof(type))
			;//throw (type_mismatch());

		int nSize = sizeof(type);
		memcpy(&output,&seq[0],nSize);
		//if there is other data remained, move forward
		if (seq.size() > (ArrayMsg::size_type)nSize)
		{
			memcpy(&seq[0],&seq[nSize],seq.size() - nSize);
		}
		seq.resize(seq.size() - nSize);
		return seq;
	}

	void ReadFromString(ArrayMsg& seq,const std::string& input,int length);
	void WriteToString(ArrayMsg& seq,std::string& output,int length);

	//specialization for std::string
	//������֧��string�Ĺ��ܣ�������֧�ִ���string��struct��
	//����ṹ�д���string�����밴��Ա�����������:>>Data.string>>Data.int>>Data.float��
	template<>	ArrayMsg& operator<<(ArrayMsg& seq,const std::string& input);
	template<>	ArrayMsg& operator>>(ArrayMsg& seq,std::string& output);
	
	/**********************************************************************
	 *  ����: ת��Ϊ�ֽ���
	 *  �������� ToByteSeq 
	 *  ����ֵ�� ArrayMsg	 	ת���������
	 *  �����б�	��������    		ȡֵ��Χ     		    ����
	 *    _value  : [IN] const type &	//TODO:����ȡֵ��Χ		��Ҫת��������
	 *    strType : [IN] const string &	//TODO:����ȡֵ��Χ		���ݵ�����
	 *    nLengh  : [IN] int			//TODO:����ȡֵ��Χ		���ݳ���
	 *
	 *  �汾��ʷ		
	 *       1.0    2009-07-25  jacklu    ʵ�ֹ���
	 *  
	 **********************************************************************/
	template<typename type>
	ArrayMsg ToByteSeq(const type& _value,const std::string& strType ,int nLengh)
	{
		ArrayMsg _arrayMsg;

		if (strType == "char")
		{
			std::ostringstream ostream;		
			ostream<<_value;
			std::istringstream istream(ostream.str());
			std::string strTemp;
			istream>>strTemp;
			int nCSize = strTemp.size();
			if (nCSize < nLengh)
			{
				_arrayMsg.insert(_arrayMsg.begin(), strTemp.begin(), strTemp.end());
				_arrayMsg.resize(nLengh, ' ');
			}
			else
			{
				std::string strValue(strTemp.c_str(), nLengh);
				_arrayMsg.insert(_arrayMsg.begin(), strValue.begin(), strValue.end());
			}
		}
		else if (strType == "number")
		{
			int nSize = sizeof(type);
			if (nSize < nLengh)
			{
				_arrayMsg.resize(nLengh, 0x0);
				memcpy(&_arrayMsg[nLengh - nSize], &_value, nSize);
			}
			else
			{
				_arrayMsg.resize(nSize);
				memcpy(&_arrayMsg[0], &_value, nSize);
			}
	
		}
		else
		{
			LOG log("ToByteSeq");
			log.Error()<<"type error!"<<endl;
		}

		return _arrayMsg;
	}
}
#endif
