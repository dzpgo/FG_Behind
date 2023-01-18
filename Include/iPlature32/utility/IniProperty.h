#ifndef IniProperty_H
#define IniProperty_H
#include <utility/StringHelper.h>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;
/*****************************************************************************
* ini��ʽ�������ļ�
* 2007-09-25  �쳤ʢ ����û��ע�͵ı�д��ע��
* 2007-04-09  �쳤ʢ ����namespace��ע��
* 2007-04-05  ���ķ� ��ɴ���ı�д
* 2007-03-26  �쳤ʢ �����ӿ�
******************************************************************************/
namespace baosight
{
	struct Record//���ڼ�¼ÿ����¼����Ϣ
	{
		std::string key;  //key
		std::string value;//ֵ
		std::string comment;//ע��
	};

	struct SectionArea//��¼�ε���Ϣ
	{
		std::string section;//����
		std::vector<std::string>keylist;//�εļ�¼�ļ�ֵ
		std::string comment;//ע��
	};

	class CIniProperty{
	private:
		std::string filename;//ini�ļ���·��
		std::map<std::string,Record> datas;
		std::vector<SectionArea>sectlist;//��¼�����еĶ�

		Record split(std::string& line);

		bool write;//�����ж��Ƿ�д
	private:
		int flush();//������ļ���ȥ
	protected:
		void  Init();
	public:
		CIniProperty(const std::string& file);

	public:
		std::string ReadProperty(const std::string& section,const std::string& key);
		int WriteProperty(const std::string& section,const std::string& key="",const std::string& value="",const std::string& comment="");//���ĸ�����Ϊע��

		virtual ~CIniProperty();

	};
};
#endif

