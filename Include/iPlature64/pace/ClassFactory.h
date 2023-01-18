#ifndef __PACE_CLASSFACTORY_H__
#define __PACE_CLASSFACTORY_H__

#include <Ice/ObjectFactory.h>
#include <IceUtil/RecMutex.h>

namespace iPlature
{
/**
 * @brief
 * 
 * 
 */ 
template <typename T>
class ClassFactory : public Ice::ObjectFactory
{
public:
    /**
     * @brief
     */
    ClassFactory()
    {
    };
    /**
     * @brief
     * @param type
     * @return
     */
    virtual Ice::ObjectPtr create(const std::string& type)
    {
       assert( type == T::ice_staticId() );
       return new T();
    };
    /**
     * @brief
     */
    virtual void destroy()
    {
    };

};
}
#endif


