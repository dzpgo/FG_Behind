/*********************************************************************
 *		
 *  ��      ��:    Parameter.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2011-04-10    IPLATURE    //TODO����ӱ�����Ҫ�޸�����
 *      1.3	 2011-05-10		HAYKIN		parameter��Ϊ����property  
 *		1.31	 2011-09-26		HAYKIN		getAllWithPrefix��������ֵ
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
    * �����ļ�����������
    */
   class Parameter
   {
   public:
     /** 
      * Ĭ�Ϲ�����
      */
      Parameter();
      /**
       * ��Ice::Properties���Լ�����Parameter������
       * @param[in] rhs Ice::Properties���Լ�
       */
      Parameter(const Ice::PropertiesPtr rhs);
      /**
       * �������ļ�����Parameter������
       * @param[in] filename ���������ļ�
       * @return �������ļ����ɵ�Parameter����
       */
      static Parameter ConfigFile(const std::string& filename);
	  /** 
	  * ����ǰ׺�������ļ� 
	  * @param[in] filename ���������ļ�
	  * �������ļ����׳��쳣 Ice::FileException
	  */
	  Parameter(const std::string& filename);
     /** 
      * ����ǰ׺�������ļ� 
      * @param[in] filename ���������ļ�
      * @param[in] prefix ǰ׺
	  * �������ļ����׳��쳣 Ice::FileException
      */
      Parameter(const std::string& filename,const std::string& prefix);


	  /**********************************************************************
	   *  ����: ���������ļ�
	   *  �������� loadFile 
	   *  ����ֵ�� void	 	
	   *  �����б�	��������    					ȡֵ��Χ     		    ����
	   *    filename  :    [IN/OUT] const std::string &	     �ļ��� ����·����Ĭ��Ŀ¼ΪPace.ParamConfig.Path
	   *    prefix  :    [IN/OUT] const std::string &	          ǰ׺��
	   *
	   *  �汾��ʷ		
	   *       1.0    2011-05-10  Haykin-2010    create
	   *  
	   **********************************************************************/
	  void loadFile(const std::string& strFile, const std::string& strPreFix = "");
     /** 
      * �õ����Լ��ļ�ǰ׺
      * 
      * @return ǰ׺�ַ��� 
      */
      const std::string& prefix() const;
     /** 
      * ����ǰ׺�õ������Ӽ� 
      * 
      * @param[in] prefix ����ǰ׺
      */
      Ice::PropertyDict getAllWithPrefix(const std::string& prefix);
     /** 
      * ����
      */
      virtual ~Parameter();
     /** 
      * ���Parameter�е���������
      */
      void clear();
     /** 
      * �ж����Լ����Ƿ�Ϊ��
      * 
      * @return true ��,false �ǿ�
      */
      bool isEmpty() const;
     /** 
      * �������Ը���
      * 
      * @return ���Ը���
      */
      int count() const;
     /** 
      * �������е����Լ���
      * 
      * @return ȫ�����Ե��ַ���
      */
      std::string dump() const;
     /** 
      * �ж������Ƿ�Ϊ��
      * 
      * @param[in] key �� 
      * 
      * @return true �����ԣ� false �ǿ����� 
      */
      bool isNull(const std::string& key) const;
     /** 
      * �ж������Ƿ�Ϊ��ֵ
      * 
      * @param[in] key ��
      * 
      * @return true ����ת��Ϊ��ֵ��false����ת��Ϊ��ֵ
      */
      bool isNumber(const std::string& key) const;
     /** 
      * ����ָ���ļ�ֵ�õ��ַ��� 
      * @param[in] key �� 
      * @param[in] def Ĭ��ֵ
      * @return ת���������ֵ
	  * �������򷵻ؿ�
      */
      std::string getString(const std::string& key,const std::string& def="") const;
      /**
       * ����ָ����ֵ�õ��ַ�������
       * @param[in] key ��
       * @param[in] delim �ָ���
       * @return �ַ�������
	   * ����������ʾ�κν��
       */
      std::vector<std::string> getStringSeq(const std::string& key) const;
     /** 
      * ����ָ����ֵ������
      * 
      * @param[in] key ��
      * @param[in] def Ĭ��ֵ
      * @return ת���������ֵ
	  * �������򷵻� 0
      */
      int getInt(const std::string& key,const int def=0) const;
      /**
       * ����ָ����ֵ����������
       * @param[in] key ��
       * @param[in] delim �ָ���
       * @return ��������
	   * �������򷵻� 0
       */
      std::vector<int> getIntSeq(const std::string& key) const;
     /** 
      * ����ָ����ֵ�õ�������
      * 
      * @param[in] key �� 
      * @param[in] def Ĭ��ֵ 
      * @return ת���������ֵ
	  * �������򷵻� 0
      */
      float getFloat(const std::string& key,const float def=0.0) const;
      /**
       * ����ָ����ֵ�õ�����������
       * @param[in] key ��
       * @return ����������
	   * �������򷵻� 0
       */
      std::vector<float> getFloatSeq(const std::string& key) const;
	  /** 
	  * ����ָ����ֵ�õ������͵���
	  * 
	  * @param[in] key �� 
	  * @param[in] def Ĭ��ֵ 
	  * @return ת���������ֵ
	  * �������򷵻� 0
	  */
	  bool getBool(const std::string& key,const bool def=false) const;
	  /**
	  * ����ָ����ֵ�õ�����������
	  * @param[in] key ��
	  * @return ����������
	  * �������򷵻� 0
	  */
	  std::vector<bool> getBoolSeq(const std::string& key) const;
	  /**
	  * ����ָ���ָ����ָ��ַ���
	  * @param[in] str �ַ���
	  * @return �ָ�õ��ַ�������
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


