/*********************************************************************
 *		
 *  文      件:    Parameter.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2011-04-10    IPLATURE    //TODO请添加本次主要修改内容
 *      1.3	 2011-05-10		HAYKIN		parameter作为独立property  
 *		1.31	 2011-09-26		HAYKIN		getAllWithPrefix返回所有值
*********************************************************************/
#ifndef __PACE_PARAMETER_H__
#define __PACE_PARAMETER_H__ 
#include <string>
#include <vector>
#include <Ice/Properties.h>
#include <Ice/Communicator.h>
#include <pace/Component.h>
#include "log4cplus/LOG.h"

using namespace iPlature;
//using namespace std;

namespace iPlature
{
   /** 
    * 配置文件参数处理类
    */
   class Parameter
   {
   public:
     /** 
      * 默认构造器
      */
      Parameter();
      /**
       * 由Ice::Properties属性集构造Parameter参数集
       * @param[in] rhs Ice::Properties属性集
       */
      Parameter(const Ice::PropertiesPtr rhs);
      /**
       * 由配置文件构造Parameter参数集
       * @param[in] filename 属性配置文件
       * @return 由配置文件生成的Parameter对象
       */
      static Parameter ConfigFile(const std::string& filename);
	  /** 
	  * 读无前缀的配置文件 
	  * @param[in] filename 属性配置文件
	  * 读不到文件则抛出异常 Ice::FileException
	  */
	  Parameter(const std::string& filename);
     /** 
      * 读有前缀的配置文件 
      * @param[in] filename 属性配置文件
      * @param[in] prefix 前缀
	  * 读不到文件则抛出异常 Ice::FileException
      */
      Parameter(const std::string& filename,const std::string& prefix);


	  /**********************************************************************
	   *  概述: 加载配置文件
	   *  函数名： loadFile 
	   *  返回值： void	 	
	   *  参数列表：	参数类型    					取值范围     		    描述
	   *    filename  :    [IN/OUT] const std::string &	     文件名 若带路径，默认目录为Pace.ParamConfig.Path
	   *    prefix  :    [IN/OUT] const std::string &	          前缀名
	   *
	   *  版本历史		
	   *       1.0    2011-05-10  Haykin-2010    create
	   *  
	   **********************************************************************/
	  void loadFile(const std::string& strFile, const std::string& strPreFix = "");
     /** 
      * 得到属性集的键前缀
      * 
      * @return 前缀字符串 
      */
      const std::string& prefix() const;
     /** 
      * 根据前缀得到属性子集 
      * 
      * @param[in] prefix 键的前缀
      */
      Ice::PropertyDict getAllWithPrefix(const std::string& prefix);
     /** 
      * 析构
      */
      virtual ~Parameter();
     /** 
      * 清空Parameter中的所有属性
      */
      void clear();
     /** 
      * 判断属性集合是否为空
      * 
      * @return true 空,false 非空
      */
      bool isEmpty() const;
     /** 
      * 返回属性个数
      * 
      * @return 属性个数
      */
      int count() const;
     /** 
      * 返回所有的属性集合
      * 
      * @return 全部属性的字符串
      */
      std::string dump() const;
     /** 
      * 判断属性是否为空
      * 
      * @param[in] key 键 
      * 
      * @return true 空属性， false 非空属性 
      */
      bool isNull(const std::string& key) const;
     /** 
      * 判断属性是否为数值
      * 
      * @param[in] key 键
      * 
      * @return true 可以转换为数值，false不能转换为数值
      */
      bool isNumber(const std::string& key) const;
     /** 
      * 根据指定的键值得到字符串 
      * @param[in] key 键 
      * @param[in] def 默认值
      * @return 转换后的属性值
	  * 读不到则返回空
      */
      std::string getString(const std::string& key,const std::string& def="") const;
      /**
       * 根据指定键值得到字符串序列
       * @param[in] key 键
       * @param[in] delim 分隔符
       * @return 字符串序列
	   * 读不到则不显示任何结果
       */
      std::vector<std::string> getStringSeq(const std::string& key) const;
     /** 
      * 根据指定键值得整数
      * 
      * @param[in] key 键
      * @param[in] def 默认值
      * @return 转换后的属性值
	  * 读不到则返回 0
      */
      int getInt(const std::string& key,const int def=0) const;
      /**
       * 根据指定键值得整数序列
       * @param[in] key 键
       * @param[in] delim 分隔符
       * @return 整数序列
	   * 读不到则返回 0
       */
      std::vector<int> getIntSeq(const std::string& key) const;
     /** 
      * 根据指定键值得到浮点数
      * 
      * @param[in] key 键 
      * @param[in] def 默认值 
      * @return 转换后的属性值
	  * 读不到则返回 0
      */
      float getFloat(const std::string& key,const float def=0.0) const;
      /**
       * 根据指定键值得到浮点数序列
       * @param[in] key 键
       * @return 浮点数序列
	   * 读不到则返回 0
       */
      std::vector<float> getFloatSeq(const std::string& key) const;
	  /** 
	  * 根据指定键值得到布尔型的数
	  * 
	  * @param[in] key 键 
	  * @param[in] def 默认值 
	  * @return 转换后的属性值
	  * 读不到则返回 0
	  */
	  bool getBool(const std::string& key,const bool def=false) const;
	  /**
	  * 根据指定键值得到布尔型序列
	  * @param[in] key 键
	  * @return 布尔型序列
	  * 读不到则返回 0
	  */
	  std::vector<bool> getBoolSeq(const std::string& key) const;
	  /**
	  * 根据指定分隔符分隔字符串
	  * @param[in] str 字符串
	  * @return 分割好的字符串序列
	  */
	  std::vector<std::string> split_str(const string& str) const;

		  

	  
   private:
      Ice::PropertiesPtr _properties;
      Ice::PropertyDict _parameters;
      std::string _prefix; 
	  LOG _log;
   }; 

}

#endif


