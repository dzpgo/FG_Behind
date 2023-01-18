
/*********************************************************************
*		
*  文      件:    iXcomUtility.h   		//TODO请概述文件功能
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：//TODO请添加本文件包含功能详细描述
*        ：//TODO
*        ：//TODO
*
*  版本历史		
*      1.0    2009-06-15    gaoxin    创建
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
	//增加了支持string的功能，不过不支持带有string的struct。
	//如果结构中带有string，必须按成员逐个解析。如:>>Data.string>>Data.int>>Data.float。
	template<>	ArrayMsg& operator<<(ArrayMsg& seq,const std::string& input);
	template<>	ArrayMsg& operator>>(ArrayMsg& seq,std::string& output);
	
	/**********************************************************************
	 *  概述: 转换为字节流
	 *  函数名： ToByteSeq 
	 *  返回值： ArrayMsg	 	转换后的数据
	 *  参数列表：	参数类型    		取值范围     		    描述
	 *    _value  : [IN] const type &	//TODO:参数取值范围		需要转换的数据
	 *    strType : [IN] const string &	//TODO:参数取值范围		数据的类型
	 *    nLengh  : [IN] int			//TODO:参数取值范围		数据长度
	 *
	 *  版本历史		
	 *       1.0    2009-07-25  jacklu    实现功能
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
