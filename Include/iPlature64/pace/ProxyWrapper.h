#ifndef __PACE_PROXYWRAPPER_H__
#define __PACE_PROXYWRAPPER_H__
/**
 * @file   :ProxyWrapper.h
 * 
 * @brief  : 
 * 
 * 
 * @version :1.0
 * @date    :2005年12月26日 11时42分32秒 CST
 * @revision:$Id$  
 * 
 * @author  :Yin Yun Qiao(YYQ,yinyunqiao@gmail.com)
 * @company :Baosteel,Co,ltd.
 * 
 */

#include <pace/Proxy.h>
#include <pace/ExceptionTracer.h>
namespace iPlature
{
/** 
 * @brief  create a IceStorm publisher proxy with template parameter T.
 */
template <typename T>
T getPublishProxy(const std::string topic)
{
  return T::uncheckedCast(Proxy(topic).getPublisher(true));
}


/** 
 * @brief  a easy to use wrapper for any proxy.
 */
template <typename T>
struct ProxyWrapper
{
 typedef typename T::element_type proxy_type;
 /** 
  * @brief  Get a remote proxy,according to diffrent call mode,
  *         a direct proxy or a IceStorm publisher may be created.  
  * @param id  proxy id.
  */
  ProxyWrapper(const std::string& id,const int timeout=10000)
  :_helper(id)
  {
     if(_helper.callMode() != PublishCall )
     {
        _proxy = T::uncheckedCast(_helper.getProxy(proxy_type::ice_staticId(),timeout));
     }   
     else
     { //get a publisher proxy,if no topic exist,we will create it.
        _proxy = T::uncheckedCast(_helper.getPublisher(true));
     }
  }
  operator T()
  {
     return _proxy;
  }
  T operator->() const
  {
     return _proxy;
  }
 /** 
  * @brief 
  * 
  * @return 
  */
  T twoway() const
  {
     return T::uncheckedCast(_proxy->ice_twoway());
  }
  T publish() const
  {
     return T::uncheckedCast(_helper.getPublisher(true));
  }  
 /** 
  * @brief 
  * 
  * @return 
  */
  T oneway() const
  {
     return T::uncheckedCast(_proxy->ice_oneway());
  }
  T timeout(int t) const
  {
     return T::uncheckedCast(_proxy->ice_timeout(t));
  }
 /** 
  * @brief 
  * 
  * @return 
  */
  T datagram() const
  {
     return T::uncheckedCast(_proxy->ice_datagram());
  }
 /** 
  * @brief 
  * 
  * @return 
  */
  T batchOneway() const
  {
     return T::uncheckedCast(_proxy->ice_batchOneway());
  }
 /** 
  * @brief 
  * 
  * @return 
  */
  T batchDatagram() const
  {
     return T::uncheckedCast(_proxy->ice_batchDatagram());
  }
 /** 
  * @brief 
  */
  void flush()
  {
     _proxy->ice_connection()->flushBatchRequests();
  } 
 
private:
   T _proxy;
   Proxy _helper;
};
}

#define PACE_CALLBACK(name,module,interface,method) \
        typedef module::AMI_##interface##_##method##Ptr name##Ptr; \
        class name : public module::AMI_##interface##_##method
#define PACE_CATCH_CALLBACK_EXCEPTION() virtual void ice_exception(const ::Ice::Exception& e) \
                                      { \
                                       try{ \
                                         e.ice_throw();\
                                       } \
                                       PACE_CATCH_EXCEPTION() \
                                      }
#endif



