#ifndef _DB_CONNECTION_MANAGER_H_
#define _DB_CONNECTION_MANAGER_H_

#ifndef _WIN32_WINNT
#   define _WIN32_WINNT 0x400
#endif

#include <db/_p.h>
#include <db/oralib.h>
#include <db/orahelper.h>
#include <utility/StringHelper.h>
#include <Ice/Properties.h>
#include <Ice/Initialize.h>
#include <Ice/LocalException.h>
#include <IceUtil/RecMutex.h>
#include <log4cplus/LOG.h>

using namespace std;
using namespace oralib;

class CBaseDataAccess
{
protected:
	CBaseDataAccess();
	~CBaseDataAccess();
	connection& getConnection();
public:
	static int createConnection();
	static int closeConnection();
	static int Commit();
	static int Rollback();
private:
	static connection m_cn;
	static bool m_alreadyopen;
	static IceUtil::RecMutex m_mutex;
};




#endif
