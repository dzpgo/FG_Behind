/*********************************************************************
 *		
 *  文      件:    SmartData.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2009-07-27    UNKNOW    create
 *      1.1	 2011-07-27		Haykin-2011	Add Copy Struct   
*********************************************************************/
#ifndef __PACE_SMARTDATA_H__
#define __PACE_SMARTDATA_H__

#include <IceUtil/Shared.h>
#include <IceUtil/Handle.h>
#include <vector>
#include <log4cplus/LOG.h>

namespace iPlature
{
class SmartData;
class SmartBuffer;
typedef IceUtil::Handle<SmartData> SmartDataPtr;

class SmartDataException : public std::exception
{
public:
	virtual ~SmartDataException() throw();
	SmartDataException(const std::string& msg);
	SmartDataException(const SmartData& data,
		const std::string& msg);
	virtual const char* what() const throw();
private:
	std::string  _what;
};

class SmartDataVisitor
{
public:
	virtual ~SmartDataVisitor() = 0;
	virtual void VisitShort(SmartData& sd){}
	virtual void VisitInteger(SmartData& sd){}
	virtual void VisitFloat(SmartData& sd){}
	virtual void VisitDouble(SmartData& sd){}
	virtual void visitString(SmartData& sd){}
};

class SmartData : public IceUtil::SimpleShared
{
public:
  //typedefs
  typedef std::vector< IceUtil::Handle<SmartData> > SmartDataList;
  enum SmartDataType {DUMMY,SHORT,INTEGER,FLOAT,DOUBLE,STRING,COMPOSITE,VARSTRING,LSTRING,RSTRING};

  //ctors
  SmartData(); //equal to SmartData(DUMMY)
  SmartData(SmartDataType type);

  SmartData(const SmartData& sdSource);			//2011-7-27

  //builders
  SmartData& operator()(int size);//for INTEGER,FLOAT,DOUBLE type
  SmartData& operator()(int length,int size,char ch=0);//for STRING,LSTRING,RSTRING type
  SmartData& operator()(int size,char ch);//for LSTRING,RSTRING type
  SmartData& operator()(const SmartData& data);//for COMPOSITE
  SmartData& operator()(const SmartData& data,int arraySize);//for COMPOSITE array
  SmartData& operator()(int cloneSize,const SmartData& data);//for COMPOSITE array

  SmartData& operator()(const std::string& name,const SmartData& data);
  SmartData& build(const std::string& name,const SmartData& data);
  
  virtual SmartDataPtr clone() const;
  SmartData& clear(); 
  virtual SmartData& clearData();
  //base info
  const std::string name() const;
  int size() const;
  const std::string typeName() const;
  SmartDataType type() const;
  void setName(const std::string& name);
  
  virtual bool isomorphy(const SmartData& rhs) const;
  //dtors
  virtual ~SmartData();
  
  //serialization
  virtual void readFrom(SmartBuffer& buffer);
  void readFrom(std::vector<unsigned char>&);
  void readFrom(const std::vector<unsigned char>&);
  virtual void writeTo(SmartBuffer& buffer);
  void writeTo(std::vector<unsigned char>&);

  //locators
  virtual SmartData& operator[](int) const;
  virtual SmartData& operator[](const char*) const;
  virtual SmartData& operator[](const std::string&) const;

  //extractors
  virtual std::string toFormattedString(const std::string& ident="") const;
  virtual std::string toString() const;
  virtual int toInt() const;
  virtual float toFloat() const;
  virtual double toDouble() const;
  
  virtual operator const char*() const;
  virtual operator std::string() const;
  virtual operator int() const;
  virtual operator float() const;
  virtual operator double() const;
  virtual operator short() const;
  virtual operator bool() const;

  virtual operator std::vector<std::string>() const;
  virtual operator std::vector<int>() const;
  virtual operator std::vector<float>() const;
  virtual operator std::vector<double>() const;

  //assigners
  virtual void setString(const std::string&);
  virtual void setInt(int);
  virtual void setFloat(float);
  virtual void setDouble(double);

  virtual SmartData& operator=(const SmartData&);
  virtual SmartData& operator=(const char*);
  virtual SmartData& operator=(int);
  virtual SmartData& operator=(float);
  virtual SmartData& operator=(double);
  virtual SmartData& operator=(const std::string&);

  virtual SmartData& operator=(const std::vector<int>&);
  virtual SmartData& operator=(const std::vector<float>&);
  virtual SmartData& operator=(const std::vector<double>&);
  virtual SmartData& operator=(const std::vector<std::string>&);

  virtual bool IsNull() const;
  virtual void SetAsNull();

  virtual void Vist(SmartDataVisitor& visitor);

protected:
  SmartDataList _data;
  SmartDataType _type;
  std::string _name;
};
}//namespace

//output operators
std::ostream& operator<<(std::ostream& os,const iPlature::SmartData& data);
LOG& operator<<(LOG&,const iPlature::SmartData& data);

#define I2 iPlature::SmartData(iPlature::SmartData::SHORT)
#define I4 iPlature::SmartData(iPlature::SmartData::INTEGER)
#define R4 iPlature::SmartData(iPlature::SmartData::FLOAT  )
#define R8 iPlature::SmartData(iPlature::SmartData::DOUBLE )
#define CN iPlature::SmartData(iPlature::SmartData::STRING )
#define LCN iPlature::SmartData(iPlature::SmartData::LSTRING )
#define RCN iPlature::SmartData(iPlature::SmartData::RSTRING )
#define STR iPlature::SmartData(iPlature::SmartData::VARSTRING)
#define MX iPlature::SmartData(iPlature::SmartData::COMPOSITE)

#endif



