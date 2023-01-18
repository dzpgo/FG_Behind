#ifndef _BDBLMHELP_H_20071126
#define _BDBLMHELP_H_20071126
#include <pace/pace.h>

#include <bdblockmanager/BDBLockManager.h>
#include <log4cplus/LOG.h>

using namespace iPlature;
using namespace std;

namespace iPlature
{
	class BDBLocker
	{
	public:
		BDBLocker(const string& lockname,RWFlag flag)
			:m_LockName(lockname),m_flag(flag)
		{
			LOG log("Locker.ctor");

			m_LockSmith = ProxyWrapper<iPlature::BDBLockManagerPrx>("BDBLM/LockSmith"); 
			m_LockSmith = iPlature::BDBLockManagerPrx::uncheckedCast(m_LockSmith->ice_timeout(60000));

			if(m_LockSmith)
			{
				m_LockSmith->Lock(m_LockName,m_flag ,m_LockID);
			}
			else
			{
				log.Error()<<"failed"<<endl;
			}
		}
		~BDBLocker()
		{
			if(m_LockSmith)
			{
				m_LockSmith->Unlock(m_LockName,m_flag ,m_LockID);
			}
		}
	private:
		BDBLockManagerPrx m_LockSmith;
		string m_LockName;
		RWFlag m_flag;
		int m_LockID;
	};
}

#endif