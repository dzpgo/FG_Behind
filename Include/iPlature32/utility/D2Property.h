#ifndef _D2Property_H
#define _D2Property_H
/**
*�������ڶ�ȡ��ά�������ļ�����
Line   TelId  eventId     A  B
1        abc    1000          -     -
2        ccc    2000          -     -
3        ddd    3000          -     -
 ���ݹؼ�������Ŀ�������ݣ������(1,2)�� ��3������
*/
#include <stdarg.h>		
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace baosight
{
	class CD2Property{
	public:
		CD2Property(const std::string& file,int ommitfirstline = 1);
		CD2Property();
		
		~CD2Property();
		//�������ļ�
		int OpenFile(std::string file,int ommitfirstline = 1);
		//���ݴӵڼ��е��ڼ���ȥ��ȡָ��Ŀ���е�����
		int ReadProperty(const std::string columnname,std::string& value,std::vector<std::string>keys);

		//ʹ�ò���������ʽȥ��ȡָ���е�����
		//int ReadProperty(const std::string columnname,std::string& value,int keyscount,...);
		int ReadProperty(int index,std::string& value,std::vector<std::string>keys);
		
		//ʹ�ò���������ʽȥ��ȡָ���е�����
		//int ReadProperty(int index,std::string& value,int keyscount,...);
	protected:
		void Init();
	private:
		std::string filename;
		std::vector<std::string> columns;
		std::vector<std::vector<std::string> > alldata;
		int omitfirstline;//��һ���Ƿ�����е�������
		int openflag;
		bool write;//�����ļ��Ƿ񱻸��Ĺ�
	};
};
#endif

