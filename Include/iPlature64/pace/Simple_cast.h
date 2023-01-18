#ifndef SIMPLE_CAST_INCLUDE
#define SIMPLE_CAST_INCLUDE

#include <sstream>
#include <typeinfo>

namespace iPlature
{
//exception
class bad_simple_cast : public std::bad_cast
{
private:
	std::string _txt;
public:
	  bad_simple_cast();
	  bad_simple_cast(const std::string& strTargetType);
	  bad_simple_cast(const std::string& strTargetType, const std::string& strValue);
	  virtual ~bad_simple_cast() throw(){}
	  virtual const char *what() const throw()
	  {
		  return _txt.c_str();
	  }  
};


template<typename Target, typename Source>
Target simple_cast(Source arg)
{
	std::ostringstream o;
	o<<std::fixed;
	if(!(o << arg))throw(bad_simple_cast(std::string(typeid(Target).name())));
	std::istringstream i(o.str());
	Target result;
	if(!(i >> result))throw(bad_simple_cast(std::string(typeid(Target).name()), o.str()));
	return result;
}


}//namespace iPlature

#endif


