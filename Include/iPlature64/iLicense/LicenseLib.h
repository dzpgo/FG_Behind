#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <utility/StringHelper.h>
//#include <pace/Simple_cast.h>
using namespace std;
using namespace baosight;
//using namespace iPlature;

#ifdef _WIN32
#include <Windows.h>
#include <IPTypes.h>
#include <IPHlpApi.h>
#pragma comment(lib,"IPHlpApi")
#endif

#ifdef _LINUX
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#define MAXINTERFACES   16
#endif

const int BuffSize = 4096;
const int license_success = 0;	//�ɹ�
const int license_not_start = 1;  //License��Ч��δ��ʼ
const int license_mode_invalid = 2;  //Licenseģʽ����ȷ
const int license_key_invalid = 3; //License��֤�벻��ȷ
const int license_time_invalid = 4; //License�ѹ���
const int license_file_invalid = 5; //License�ļ���ʽ����ȷ
const int license_file_open_failed = 6; //License�ļ���ʧ��
const int license_file_read_failed = 7; //License�ļ���ȡʧ��
const int license_dll_load_failed = 8; //DLL��ȡʧ��(Reg.dll)

const int license_invalid = 999;  //License����

typedef string (*MacSelectFunction)(map<string,string>);

int _checkLicense(string infilename); //���License��Ϣ
int _generateKey(string inbuffer,string outfilename); //ͨ��ϵͳ��Ϣ����license
int _collectSysInfo(string outfilename); //ϵͳ��Ϣ�����ɵ��ļ���
int _LicenseConvertOut(string infilename,ostream& os); //licenseת������
string _getIssueDateAndleftTime(string infilename);//��ȡLicenseǩ�����ں�ʣ����Ч���ʱ��