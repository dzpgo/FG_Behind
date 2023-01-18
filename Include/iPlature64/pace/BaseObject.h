#ifndef __PACE_BASEOBJECT_H__
#define __PACE_BASEOBJECT_H__

#include <IceUtil/IceUtil.h>

namespace iPlature
{
class BaseObject : public IceUtil::AbstractMutexI<IceUtil::RecMutex>
{
public:
   // virtual ::std::string dump() const;
    //virtual void init();
	virtual bool deletable() {return false;}
};

}

#endif
