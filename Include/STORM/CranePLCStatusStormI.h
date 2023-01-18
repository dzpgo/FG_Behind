#ifndef __CranePLCStatusStormI_h__
#define __CranePLCStatusStormI_h__

#include <CranePLCStatusStorm.h>

namespace CLTS
{

class CranePublisherI : public virtual CranePublisher
{
public:

    virtual void CWatchEventHandlerI(const CranePLCStatusDesc&,
                                     const Ice::Current&);
};

}

#endif
