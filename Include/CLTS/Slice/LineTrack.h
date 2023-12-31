// **********************************************************************
//
// Copyright (c) 2003-2010 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.4.1

// <auto-generated>
//
// Generated from file `LineTrack.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

#ifndef ___________include_clts_slice_LineTrack_h__
#define ___________include_clts_slice_LineTrack_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/StreamF.h>
#include <CltsException.h>
#include <Saddle.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 304
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

}

namespace IceInternal
{

}

namespace CLTS
{

struct ExitSaddleTrack
{
    ::std::string unitNo;
    ::Ice::Int saddleCnt;
    ::std::string saddleL2Name;
    ::Ice::Int hasCoil;
    ::std::string coilNo;
    ::Ice::Int weight;
    ::Ice::Int width;
    ::Ice::Int inDia;
    ::Ice::Int outDia;
    ::Ice::Int sleeveWidth;
    ::Ice::Int coilOpenDirection;
    ::std::string alarmCode;
    ::std::string nextUnitNo;
    ::std::string packCode;
    ::std::string workOrderNo;
    ::std::string productDate;

    bool operator==(const ExitSaddleTrack& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(unitNo != __rhs.unitNo)
        {
            return false;
        }
        if(saddleCnt != __rhs.saddleCnt)
        {
            return false;
        }
        if(saddleL2Name != __rhs.saddleL2Name)
        {
            return false;
        }
        if(hasCoil != __rhs.hasCoil)
        {
            return false;
        }
        if(coilNo != __rhs.coilNo)
        {
            return false;
        }
        if(weight != __rhs.weight)
        {
            return false;
        }
        if(width != __rhs.width)
        {
            return false;
        }
        if(inDia != __rhs.inDia)
        {
            return false;
        }
        if(outDia != __rhs.outDia)
        {
            return false;
        }
        if(sleeveWidth != __rhs.sleeveWidth)
        {
            return false;
        }
        if(coilOpenDirection != __rhs.coilOpenDirection)
        {
            return false;
        }
        if(alarmCode != __rhs.alarmCode)
        {
            return false;
        }
        if(nextUnitNo != __rhs.nextUnitNo)
        {
            return false;
        }
        if(packCode != __rhs.packCode)
        {
            return false;
        }
        if(workOrderNo != __rhs.workOrderNo)
        {
            return false;
        }
        if(productDate != __rhs.productDate)
        {
            return false;
        }
        return true;
    }

    bool operator<(const ExitSaddleTrack& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(unitNo < __rhs.unitNo)
        {
            return true;
        }
        else if(__rhs.unitNo < unitNo)
        {
            return false;
        }
        if(saddleCnt < __rhs.saddleCnt)
        {
            return true;
        }
        else if(__rhs.saddleCnt < saddleCnt)
        {
            return false;
        }
        if(saddleL2Name < __rhs.saddleL2Name)
        {
            return true;
        }
        else if(__rhs.saddleL2Name < saddleL2Name)
        {
            return false;
        }
        if(hasCoil < __rhs.hasCoil)
        {
            return true;
        }
        else if(__rhs.hasCoil < hasCoil)
        {
            return false;
        }
        if(coilNo < __rhs.coilNo)
        {
            return true;
        }
        else if(__rhs.coilNo < coilNo)
        {
            return false;
        }
        if(weight < __rhs.weight)
        {
            return true;
        }
        else if(__rhs.weight < weight)
        {
            return false;
        }
        if(width < __rhs.width)
        {
            return true;
        }
        else if(__rhs.width < width)
        {
            return false;
        }
        if(inDia < __rhs.inDia)
        {
            return true;
        }
        else if(__rhs.inDia < inDia)
        {
            return false;
        }
        if(outDia < __rhs.outDia)
        {
            return true;
        }
        else if(__rhs.outDia < outDia)
        {
            return false;
        }
        if(sleeveWidth < __rhs.sleeveWidth)
        {
            return true;
        }
        else if(__rhs.sleeveWidth < sleeveWidth)
        {
            return false;
        }
        if(coilOpenDirection < __rhs.coilOpenDirection)
        {
            return true;
        }
        else if(__rhs.coilOpenDirection < coilOpenDirection)
        {
            return false;
        }
        if(alarmCode < __rhs.alarmCode)
        {
            return true;
        }
        else if(__rhs.alarmCode < alarmCode)
        {
            return false;
        }
        if(nextUnitNo < __rhs.nextUnitNo)
        {
            return true;
        }
        else if(__rhs.nextUnitNo < nextUnitNo)
        {
            return false;
        }
        if(packCode < __rhs.packCode)
        {
            return true;
        }
        else if(__rhs.packCode < packCode)
        {
            return false;
        }
        if(workOrderNo < __rhs.workOrderNo)
        {
            return true;
        }
        else if(__rhs.workOrderNo < workOrderNo)
        {
            return false;
        }
        if(productDate < __rhs.productDate)
        {
            return true;
        }
        else if(__rhs.productDate < productDate)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const ExitSaddleTrack& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ExitSaddleTrack& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ExitSaddleTrack& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ExitSaddleTrack& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::CLTS::ExitSaddleTrack> ExitSaddleTrackSeq;
void __writeExitSaddleTrackSeq(::IceInternal::BasicStream*, const ::CLTS::ExitSaddleTrack*, const ::CLTS::ExitSaddleTrack*);
void __readExitSaddleTrackSeq(::IceInternal::BasicStream*, ExitSaddleTrackSeq&);

struct EntrySaddleTrack
{
    ::std::string unitNo;
    ::Ice::Int usingPorNo;
    ::Ice::Int seq;
    ::std::string saddleNo;
    ::std::string coilNo;
    ::std::string hasCoil;

    bool operator==(const EntrySaddleTrack& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(unitNo != __rhs.unitNo)
        {
            return false;
        }
        if(usingPorNo != __rhs.usingPorNo)
        {
            return false;
        }
        if(seq != __rhs.seq)
        {
            return false;
        }
        if(saddleNo != __rhs.saddleNo)
        {
            return false;
        }
        if(coilNo != __rhs.coilNo)
        {
            return false;
        }
        if(hasCoil != __rhs.hasCoil)
        {
            return false;
        }
        return true;
    }

    bool operator<(const EntrySaddleTrack& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(unitNo < __rhs.unitNo)
        {
            return true;
        }
        else if(__rhs.unitNo < unitNo)
        {
            return false;
        }
        if(usingPorNo < __rhs.usingPorNo)
        {
            return true;
        }
        else if(__rhs.usingPorNo < usingPorNo)
        {
            return false;
        }
        if(seq < __rhs.seq)
        {
            return true;
        }
        else if(__rhs.seq < seq)
        {
            return false;
        }
        if(saddleNo < __rhs.saddleNo)
        {
            return true;
        }
        else if(__rhs.saddleNo < saddleNo)
        {
            return false;
        }
        if(coilNo < __rhs.coilNo)
        {
            return true;
        }
        else if(__rhs.coilNo < coilNo)
        {
            return false;
        }
        if(hasCoil < __rhs.hasCoil)
        {
            return true;
        }
        else if(__rhs.hasCoil < hasCoil)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const EntrySaddleTrack& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const EntrySaddleTrack& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const EntrySaddleTrack& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const EntrySaddleTrack& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::CLTS::EntrySaddleTrack> EntrySaddleTrackSeq;
void __writeEntrySaddleTrackSeq(::IceInternal::BasicStream*, const ::CLTS::EntrySaddleTrack*, const ::CLTS::EntrySaddleTrack*);
void __readEntrySaddleTrackSeq(::IceInternal::BasicStream*, EntrySaddleTrackSeq&);

struct SaddleL1Status
{
    ::std::string saddleNo;
    ::Ice::Int occupied;
    ::Ice::Int lockRequest;
    ::Ice::Int locked;
    ::Ice::Int running;

    bool operator==(const SaddleL1Status& __rhs) const
    {
        if(this == &__rhs)
        {
            return true;
        }
        if(saddleNo != __rhs.saddleNo)
        {
            return false;
        }
        if(occupied != __rhs.occupied)
        {
            return false;
        }
        if(lockRequest != __rhs.lockRequest)
        {
            return false;
        }
        if(locked != __rhs.locked)
        {
            return false;
        }
        if(running != __rhs.running)
        {
            return false;
        }
        return true;
    }

    bool operator<(const SaddleL1Status& __rhs) const
    {
        if(this == &__rhs)
        {
            return false;
        }
        if(saddleNo < __rhs.saddleNo)
        {
            return true;
        }
        else if(__rhs.saddleNo < saddleNo)
        {
            return false;
        }
        if(occupied < __rhs.occupied)
        {
            return true;
        }
        else if(__rhs.occupied < occupied)
        {
            return false;
        }
        if(lockRequest < __rhs.lockRequest)
        {
            return true;
        }
        else if(__rhs.lockRequest < lockRequest)
        {
            return false;
        }
        if(locked < __rhs.locked)
        {
            return true;
        }
        else if(__rhs.locked < locked)
        {
            return false;
        }
        if(running < __rhs.running)
        {
            return true;
        }
        else if(__rhs.running < running)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const SaddleL1Status& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const SaddleL1Status& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const SaddleL1Status& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const SaddleL1Status& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::CLTS::SaddleL1Status> SaddleL1StatusSeq;
void __writeSaddleL1StatusSeq(::IceInternal::BasicStream*, const ::CLTS::SaddleL1Status*, const ::CLTS::SaddleL1Status*);
void __readSaddleL1StatusSeq(::IceInternal::BasicStream*, SaddleL1StatusSeq&);

}

namespace IceProxy
{

}

namespace IceDelegate
{

}

namespace IceDelegateM
{

}

namespace IceDelegateD
{

}

#endif
