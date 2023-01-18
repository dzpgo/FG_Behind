/*********************************************************************
 *		
 *  文      件:    MsgSmartData.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2012-05-02    Haykin-2010    //TODO请添加本次主要修改内容
 *      1.0	 2012-05-02    Haykin-2010       ResetData
*********************************************************************/
#ifndef __MSG__SMART__DATA__
#define __MSG__SMART__DATA__

#include <pace/SmartData.h>
#include <PowerTranser/PTDefine.h>

#include <iDA/iDA.h>

#ifdef IPLATURE_USE_ORALIB
#include <db/_p.h>
#include <db/oralib.h>
#endif



using namespace iPlature;

class MsgSmartData
{
public:

#ifdef IPLATURE_USE_ORALIB
	MsgSmartData(oralib::connection& cn,const string &MsgName);
#endif
	
	MsgSmartData(iPlature::iDA::Connection& cn,const string &MsgName);

	//SQLite
	MsgSmartData(const string &MsgName);

	
	MsgSmartData(const MsgSmartData& msd);

	~MsgSmartData();

	//get SmartData function
	SmartData GetSmartData() const;
	const SmartData& GetSmartDataRef() const;
	operator SmartData() const;

	//serialization
	void readFrom(std::vector<unsigned char>&);
	void readFrom(const std::vector<unsigned char>&);
	void writeTo(std::vector<unsigned char>&);	

	// assign null value
	void ResetData();
	
protected:
	//SmartData CreateSmartDataFromMsgName(const string &MsgName);

	//connection&	m_cn;
	string		m_msgname;
	bool		m_isdelaybuild;
	SmartData	m_sd;		//head+data

public:
	// assign null value
	static void ResetData(SmartData& sd);
	static bool IsNullVal(SmartData& sd);
	static string DumpValue(SmartData& sd,const string& ident);
};

//exception
class MsgSmartDataException : public std::exception
{
public:
	MsgSmartDataException(const string& msg):_what(msg){}
	virtual ~MsgSmartDataException() throw(){}
	virtual const char* what() const throw(){return _what.c_str();}
private:
	string  _what;
};

#endif
