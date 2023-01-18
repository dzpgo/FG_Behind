#ifndef __CPROPERTY_H
#define __CPROPERTY_H

#include <string>
#include <utility/StringHelper.h>
using namespace std;
/*****************************************************************************
* 
* �ַ��������࣬����string�Ĺ���
* 2007-04-09  �쳤ʢ ����namespace��ע��
* 2007-04-05  ���ķ� ��ɴ���ı�д
* 2007-03-26  �쳤ʢ �����ӿ�
******************************************************************************/

namespace baosight{
	class  CProperty {
protected:
		//�����ļ���
		std::string filename;
		virtual void  Init();//��ʼ������
	public:
		CProperty(std::string& file):filename(file){}
		//������ֵ
		virtual std::string ReadProperty(const std::string& section,const std::string& key) const = 0;

		//д����ֵ
		virtual int WriteProperty(const std::string& section,const std::string& key,const string& value) = 0;


		virtual ~CProperty(){}
	};
};
#endif

