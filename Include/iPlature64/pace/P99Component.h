#ifndef __P99_COMPONENT_H__
#define __P99_COMPONENT_H__

#include <pace/pace.h>
#include <pace/Component.h>
#include <pace/MsgTube.h>
using namespace Ice;

namespace iPlature
{
	//error code in ipsexprg
	const int P99COM_SUCCESS = 0;
	const int FLAG_NOT_VALID = 1001;
	const int GET_PROXY_FAILED = 1002;
	const int ICE_CALL_FAILED = 1003;        //2011-5-30  haykin

	const int TWO_WAY_CALL = 3;
	const int ONE_WAY_CALL = 4;

	//exception
	class type_mismatch : public std::exception
	{
	public:
		type_mismatch(){}
		~type_mismatch() throw(){}
		const char *what() const throw()
		{
			return "communication type mismatch";
		}
	};

	static ByteSeq DefualtBuffer = ByteSeq(0);
	int ipsexprg(const string& PrgName,const int nFlag,const ByteSeq& ParamBuffer=DefualtBuffer, 
		ByteSeq& ResultBuffer=DefualtBuffer, int nLimitTime=60000);

	class P99Component : public Component
	{
	public:
		virtual ~P99Component();
		virtual void PostInitCall() = 0;
		virtual ByteSeq HandleMessage(const ByteSeq&) = 0;
	private:
		virtual int start();
		virtual string GetClassName();
	};

	//type supposed to be POD
	//使用<<或>>的类型必须是内置类型如;int,float,char[5]或者是由内置类型组成的struct
	template<typename type>
	ByteSeq& operator<<(ByteSeq& seq,const type& input)
	{
		int nSize = sizeof(type);
		ByteSeq::size_type nPreSize = seq.size();
		seq.resize(seq.size() + nSize);		
		memcpy(&seq[nPreSize],&input,nSize);
		return seq;
	}
	template<typename type>
	ByteSeq& operator>>(ByteSeq& seq,type& output)
	{
		//throw exception
		if (seq.size() < sizeof(type))
			throw (type_mismatch());

		int nSize = sizeof(type);
		memcpy(&output,&seq[0],nSize);
		//if there is other data remained, move forward
		if (seq.size() > (ByteSeq::size_type)nSize)
		{
			memcpy(&seq[0],&seq[nSize],seq.size() - nSize);
		}
		seq.resize(seq.size() - nSize);
		return seq;
	}

	/*template<>
	ByteSeq& operator>>(ByteSeq& seq,char*& output);*/

	//specialization for std::string
	//增加了支持string的功能，不过不支持带有string的struct。
	//如果结构中带有string，必须按成员逐个解析。如:>>Data.string>>Data.int>>Data.float。
	template<>	ByteSeq& operator<<(ByteSeq& seq,const string& input);
	template<>	ByteSeq& operator>>(ByteSeq& seq,string& output);
}

#endif

