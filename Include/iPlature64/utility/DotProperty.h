#ifndef __DotProperty_H
#define __DotProperty_H
#include <string>
#include <map>
#include <fstream>
#include <utility/StringHelper.h>
using namespace std;

/*****************************************************************************
* 
*  .��ʽ�������ļ������� obj.a=1
* �ַ��������࣬����string�Ĺ���
* 2007-04-09  �쳤ʢ ����namespace��ע��
* 2007-04-05  ���ķ� ��ɴ���ı�д
* 2007-03-26  �쳤ʢ �����ӿ�
******************************************************************************/
namespace baosight
{
	struct DRecord
	{
		std::string	key;
		std::string value;
		std::string comment;
	};
	class  CDotProperty
	{
	private:
		std::map<std::string,DRecord> datas;
		std::string filename;
		bool write;//�����ж��Ƿ�д���ļ�
	public:
		CDotProperty(){}

		CDotProperty(const std::string& file);
		
		int Load(const std::string& file);

		virtual ~CDotProperty();
		DRecord split(std::string& line);//�ָ��¼
		std::string ReadProperty(const std::string &section,const std::string &key);
		std::string ReadProperty(const std::string& key);

		int WriteProperty( const std::string& key,const std::string& value,const std::string& comment="");
	};   
};

#endif

