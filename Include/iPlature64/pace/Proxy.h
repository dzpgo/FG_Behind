#ifndef __PACE_PROXY_H__
#define __PACE_PROXY_H__

#include <Ice/ProxyF.h>
#include <Ice/Identity.h>


namespace iPlature
{
enum ProxyCallMode {DirectCall,PublishCall,DummyCall};

class Proxy
{
public:
    Proxy(const std::string& id);
    Ice::ObjectPrx getProxy(const std::string& id,int timeout=500);
    Ice::ObjectPrx getPublisher(bool createTopic=true);
   /**
    * hints: Pace.Proxy.id.callmode = 1  DirectCall (default)
    *        Pace.Proxy.id.callmode = 2  PublishCall
    *        Pace.Proxy.id.callmode = 0  DummyCall
    */
    ProxyCallMode callMode() const;
private:
    std::string _id;
    std::string _cat;
};

}

#endif



