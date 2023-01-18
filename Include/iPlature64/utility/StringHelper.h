#ifndef __STRINGHELPER_H_BAOSIGHT
#define __STRINGHELPER_H_BAOSIGHT
/*****************************************************************************
* 
* �ַ��������࣬����string�Ĺ���
*2008-11-27 add DoubleToStr����
*2008-07-25 add Split����
* 2008-07-23 �쳤ʢ  ע�� ToVector��TrimChar����
* 2007-11-25 �쳤ʢ  fix bug:ToHex������const char*p --> const unsigned char *p
* 2007-09-25  ��� fix bug ��stringstream��vs2005 sp1ǰmemory leak ����
* 2007-05-17  �쳤ʢ ����ToVector���ܺ�ȥ���ַ������ߵ����ŵȹ���
* 2007-04-10  �쳤ʢ ���� int->string,��ѡ��ǰ��0
* 2007-04-06  �쳤ʢ ����namespace,16���ƵĹ���
* 2007-04-05  ���ķ� ��ɴ���ı�д
* 2007-03-26  �쳤ʢ ������ȡ����
* 2006-12-25  �쳤ʢ ��Berkely Client�г���

@version 1.4 since 2006-12-25
******************************************************************************/
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>
#include <sstream>
#include <map>
#include <limits>
using namespace std;

namespace baosight
{
	//ȫ���Ǿ�̬����
	class StringHelper{
	private:
		static char change(int c);

		static bool oneofchar(char c,char split[] ,int len){
			for( int i= 0 ; i < len ; i++){
				if( c == split[i]) return true;
			}
			return false;
		}

	public:
		//*******************************************************************
		// ����:	  С�����վ���ת��Ϊ�ַ���
		// �������:  value��ת����С��,decplaces����
		// ����ֵ:	  ת������ַ������
		//*******************************************************************
		static std::string DoubleToStr(const long double value,const int decplaces);
		/**
		* ȥ����ո�   
		*/
		static void LeftTrim(std::string& str);

		/**
		* ȥ���ҿո�
		*/
		static void RightTrim(std::string& str);

		/**
		* ȥ�����ҿո�
		*/
		static void Trim(std::string& str);


		/**
		* ת��Ϊ��д
		*/
		static void ToUpper(std::string& str);

		/**
		* ת��ΪСд
		*/
		static void ToLower(std::string& str);


		/*�� string�����ܻ�����ǰ��0��
		*len��ת����ĳ���
		*/
		template <class T> static std::string ToString(const T& str ,const int len )
		{

			std::string s = ToString(str);
			int a = len-(int)s.length();
			if(a>0) //��Ҫ����ǰ��0
			{
				std::string t(a,'0');
				return t+s;
			}
			else
				return s;

		}

		/**
		* ת������,�������T�͵�ֵת��Ϊstring
		*/
		template <class T> static std::string ToString(const T& str)
		{
			std::ostringstream ostream;		
			ostream<<str;
			std::istringstream istream(ostream.str());
			std::string value;
			istream>>value;
			return value; 
		}

		/**
		* ת������,�������string��ֵת��ΪT��
		*/
		template <typename T> static  T ToNumber(const std::string& str);


		/**
		*���16���ƣ�2007-04-12
		const void *p  ����
		const string&  16��������֮�������ָ����
		*/
		static std::string ToHex(const void *p,const int len,const std::string& split="",bool needorigin=false);
		static std::string ToHex(const unsigned char *p,const int len,const std::string& split="",bool needorigin=false);
		static std::string ToHex(const std::string& str,const std::string& split="",bool needorigin=false);

		//��numת��Ϊlen����16�����ַ���
		static std::string ToHex(const unsigned char num,int len = 2);

	   /***
		*
		*ʹ�ö���ָ��ָ������ַ����ָ�
		* 
		*/
		template<class K> static std::vector<K> ToVector(const std::string& field,char split[],int len = 1)
		{
			std::vector<K> vec;

			//2010-1-6 lumengyi ��������string��ֵ���ж�
			string localvalue = field;
			Trim(localvalue);
			if(localvalue.empty()) return vec;
			if (len == 1 )
				return  ToVector<K>(field,split[0]);

			std::string ss = field+split[0]; //���һ���Է���ָ�.

			size_t  strlen= ss.length();
			unsigned int i = 0;
			bool found = false;
			std::string::size_type pos0 = 0;
			
			while( i < strlen )
			{
				if( oneofchar(ss[i],split,len)){
					std::string s = ss.substr(pos0,i-pos0);
					
					K a = ToNumber<K>(s);
					vec.push_back(a);
					pos0 = i + 1; //Ҫ�� �ָ�������
				}
				i++;
			}
			return vec;
		}

		/***
		* ����ֵ�� ��ʽ��(1,2,3,4)����ʽ
		* ת��Ϊvector���͵�ֵ
		* 
		*/
		template<class K> static std::vector<K>  ToVector(const std::string& field,const char split='#')
		{
			std::vector<K> vec;

			//2010-1-6 lumengyi ��������string��ֵ���ж�
			string localvalue = field;
			Trim(localvalue);
			if(localvalue.empty()) return vec;

			//2008-07-23ȡ�����д��룬������ʹ�����ֶ�����
		    //std::string str = StringHelper::TrimChar(field); //ȥ�����ܵ�����
			std::string str = field;
			std::string::size_type pos0 = str.find_last_of(split);
    		if(pos0 == std::string::npos || pos0 != str.length()-1)   //���û��,�������һ��û��,
	    		str = str+split; //����һ���������
	    	
	    	pos0 = 0;
		    std::string::size_type pos1 = 0;
        	
			 while(true)
			 {
				pos1=str.find(split,pos0);//��pos0��ʼ����#
				if(pos1 == pos0) 
					break;//ֻ��#����
				std::string field = str.substr(pos0,pos1-pos0);

				K a = ToNumber<K>(field);
				vec.push_back(a);
	
				pos0 = pos1+1;
				if(pos0>=str.length())
					break;//����ѭ��
			}
			return vec; 			    
		}

		/**
		* �ָ��ַ���,����key1=value1,���ָ�õ�pair����
		* @return ����ֵ:pair  ,pair.first = key1,pair.second=value
		*
		*/
		template <class K,class V> static std::pair<K,V>  ToPair(const std::string& str,const char split='=')
		{
			std::pair<K,V> p1;
			
			//2010-1-6 lumengyi ��������string��ֵ���ж�
			string localvalue = str;
			Trim(localvalue);
			if(localvalue.empty()) return p1;

			std::string::size_type pos = str.find(split);
			std::string key = str.substr(0,pos);
			std::string value = str.substr(pos+1);
			Trim(key);
			Trim(value);
			
			p1.first =StringHelper::ToNumber<K>(key);
			p1.second = StringHelper::ToNumber<V>(value);
			return p1;
		}

		/**
		* �ָ��ַ���,����key1=value1#key2=value2#key3=value3���õ�һ��map
		*
		*/
		template<class K,class V>static std::map<K,V>  ToMap(const std::string& str,const char split='=',const char Split='#')
		{
			std::map<K,V> datas;

			//2010-1-6 lumengyi ��������string��ֵ���ж�
			string localvalue = str;
			Trim(localvalue);
			if(localvalue.empty()) return datas;

			std::string s1,s2=str;
			s2=s2+Split;//ĩβ����һ���ָ��
			std::string::size_type pos=s2.find(Split);
			s1=s2.substr(0,pos);
			s2=s2.substr(pos+1);
			Trim(s1);
			std::pair<K,V>p=ToPair<K,V>(s1,split);//ͨ������pair���뵽ͼ��
			datas.insert(p);
			while(s2.length()>1)
			{
				std::string::size_type pos=s2.find(Split);
				s1=s2.substr(0,pos);
				Trim(s1);
				s2=s2.substr(pos+1);
				p=ToPair<K,V>(s1,split);//����pair
				datas.insert(p);
			}
			return datas;
		}



		/**
		* ����������ȥ���ַ�����β���ߵ��ض��ַ����罫(f1=abc)--��f1=abc
		* 
		*/	
		static std::string TrimChar(const std::string& str,char c= '(');

		static bool ParseMessage(std::vector<std::string> &obj, const std::string& field, const char seperator=',');
		
		static bool ParseMessage(std::vector<std::string> &obj, const std::string& field, const std::vector<int> & membersize);

		static std::string ToOctal(unsigned int n);

		static std::wstring string2wstring(const std::string& s);

		static std::string wstring2string(const std::wstring& ws);

		static std::string doubleTostring(const long double value,const int decplaces);

		//��str�ָ��std::string���飬�ָ�����delimiterָ��������abcd###efg###ddd--����������ַ���
		static std::vector<std::string> Split(const std::string str,char delimiter);
	};  //class

	template <typename T> inline T StringHelper::ToNumber(const std::string& str)
	{
		T value;
		std::istringstream istream(str);
		istream>>value;
		return value;
	}

	template <> inline std::string StringHelper::ToNumber<std::string>(const std::string& str)
	{
		return str;
	}

};//namespace



#endif

