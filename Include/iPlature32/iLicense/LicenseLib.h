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
const int license_success = 0;	//成功
const int license_not_start = 1;  //License有效期未开始
const int license_mode_invalid = 2;  //License模式不正确
const int license_key_invalid = 3; //License验证码不正确
const int license_time_invalid = 4; //License已过期
const int license_file_invalid = 5; //License文件格式不正确
const int license_file_open_failed = 6; //License文件打开失败
const int license_file_read_failed = 7; //License文件读取失败
const int license_dll_load_failed = 8; //DLL读取失败(Reg.dll)

const int license_invalid = 999;  //License出错

typedef string (*MacSelectFunction)(map<string,string>);

int _checkLicense(string infilename); //检查License信息
int _generateKey(string inbuffer,string outfilename); //通过系统信息生成license
int _collectSysInfo(string outfilename); //系统信息，生成到文件中
int _LicenseConvertOut(string infilename,ostream& os); //license转出工具
string _getIssueDateAndleftTime(string infilename);//获取License签发日期和剩余有效许可时间