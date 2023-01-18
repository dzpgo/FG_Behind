/*********************************************************************
 *		
 *  ��      ��:    Component.h   		A base class for create Ice servant containner.
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.5    2010-11-18    Haykin-2010    ����connectstring
 *      1.6	 2011-08-31	  Haykin			 GetFreezeEvnHome   
 *      1.7    2012-2-2		  Haykin			 GetFreezeEvnHome
 *		1.8	 2012-4-23	  Haykin			stop����������־
*		1.9	 2012-4-24	  Haykin			 �ع�subscribe����
*********************************************************************/

#ifndef __PACE_COMPONENT_H__
#define __PACE_COMPONENT_H__

#include <Ice/Ice.h>
#include <IceStorm/IceStorm.h>
#include <IceGrid/Admin.h>
#include <IceGrid/Query.h>
#include <IceBox/IceBox.h>
#include <Freeze/Freeze.h>
#include <pace/Proxy.h>
#include <pace/AlarmWrapper.h>

namespace iPlature
{
	//#define IPLATURE_VERSION	102100											//unavailable from 2010-9-16
	//const string COMVERSION =	"iPlature1.2.1_BUILD_20100625";	//unavailable from 2010-9-16
 /** 
  * @brief 
  */
  class Component: private IceUtil::noncopyable
  {
  public:
    /** 
     * @brief 
     */
     Component();
    /** 
     * @brief 
     */
     virtual ~Component();
    /** 
     * @brief 
     * 
     * @return 
     */
     static Component* instance();
     void destroy();
     const std::string name() const;
	 const std::string connectionstring() const;

	 /**********************************************************************
	  *  ����: ��ȡ���ݿ����������ַ������������͡�����Ϣ������icegrid.conf�ļ��С�
	  *  �������� connectionstring 
	  *  ����ֵ�� const std::string	 	���ݿ������ַ�������Pace.DB.ConnectionStr��
	  *  �����б�	��������    					ȡֵ��Χ     		    ����
	  *    strDBType  :    [OUT] string &	     ���ݿ�����   "Pace.DB.Type"
	  *
	  *  �汾��ʷ		
	  *       1.0    2010-11-18  Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
	  *  
	  **********************************************************************/
	 const std::string connectionstring(string& strDBType) const;

	 /**********************************************************************
	  *  ����: ��ȡƽ̨�����ļ���
	  *  �������� AppConfDir 
	  *  ����ֵ�� const std::string	 	�����ļ���
	  *  �����б�	��������    					ȡֵ��Χ     		    ����
	  *
	  *  �汾��ʷ		
	  *       1.0    2010-11-19  Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
	  *  
	  **********************************************************************/
	 const std::string AppConfDir() const;

    /** 
     * @brief entry for Component class.
     * 
     * @return int return code from inherited class.
     */
     virtual int start() = 0;

	 virtual void stop();
    /** 
     * @brief add default ICE runtime enviroment for the component.
     * 
     * @param Ice::CommunicatorPtr a default ICE communicator for the component.
     * @warn This method should be called first and just once from application builder,called from some 
     *       concreted classes should be forbiddened.
     *  @return return code.
     */
     int create(const std::string& name,const Ice::CommunicatorPtr&);
    /** 
     * @brief  add a object will given id to default adapter.
     * 
     * @param id the servant's id.
     * @param object object will be registered.
     * @note if <i>ApplicationName</i>.AutoRegister=1 then
     *       the object will be registered to IceGrid automatically,
     *       but if <i>ApplicationName.Id</i>.Registrable=0 then
     *       the object with this id will not be registered.
     * 
     * @return  the registerd object's proxy.
     */
     Ice::ObjectPrx add(const std::string& id,const Ice::ObjectPtr& object);
    /** 
     * @brief  add and create a new thread object.
     * 
     * @param thread Thread instance need to be created.
     * 
     * @return  the threadcontrol object.
     * @see IceUtil::Thread
     * @see IceUtil::ThreadControl
     */
     IceUtil::ThreadControl addThread(IceUtil::ThreadPtr& thread );
     /** 
      * @brief  get the component's default adapter.
      * @return object adapter pointer.
      */
      Ice::ObjectAdapterPtr adapter() const;
      /**
       * get object locator which associated with given object category name.
       * if no associated locator found ,return default locator.
       *
       * @return object locator proxy.
       * @see Ice::Locator
       */
      Ice::LocatorPrx getLocator(const std::string& name) const;

     /** 
      * @brief 
      * 
      * @return 
      */
      IceStorm::TopicManagerPrx topicManager();
      IceStorm::TopicManagerPrx topicManager(const std::string& loc);
     /** 
      * @brief  get the component's default communicator.
      * 
      * @return  Communicator pointer.
      */
      Ice::CommunicatorPtr communicator() const; 
      Ice::PropertiesPtr properties() const;
      void loadProperties(const std::string& file);
      /**
       * @brief create a freeze map connection
       * 
       * 可以在配置文件中用Pace.Map.conn.EnvHome属性指定map表的数据库环境，conn代表map表的名字
       * @param[in] conn 连接字符�?
       * @return Freeze连接
       */
      Freeze::ConnectionPtr createFreezeConnection(const std::string& conn);
     /** 
      * @brief  subscribe a topic from default IceStorm service.
      * 
      * @param topic  the topic name.
      * @param object the listener servant.
      * 
      * @return the listener's proxy.
      */
      Ice::ObjectPrx subscribe(const std::string& topic,const Ice::ObjectPtr& object);
     /** 
      * @brief  subscribe a topic from default IceStorm service.
      * 
      * @param topic  the topic name.
      * @param proxy the listener proxy.
      * 
      * @return the listener's proxy.
      */
      Ice::ObjectPrx subscribe(const std::string& topic,const Ice::ObjectPrx& proxy);
     /** 
      * @brief  unsubscribe a topic from default IceStorm service.
      * 
      * @param topic the topic name.
      * @param prx the listener's proxy returned by subscribe call.
      * @see subscribe
      * 
      * @return true successfully unsubscribed from IceStorm;
      *         false something error while unsubscribe,see log for detail information.
      */
      bool unsubscribe(const std::string& topic,const Ice::ObjectPrx& prx);
      bool unsubscribe(const Ice::ObjectPtr object);

      std::string identityToString(const Ice::Identity&) const;
      Ice::Identity stringToIdentity(const std::string&) const;

	  void setLogLevel(LogLevel ll);
	/**********************************************************************
	 *  ����: ��ȡ���øó���ĵ��ö˳�������
	 *  �������� getInvokeProcessName 
	 *  ����ֵ�� std::string	 	���ö˳�������
	 *  �����б�	��������    			ȡֵ��Χ     		    ����
	 *    ctx  :    [IN] Ice::Context						  ���ýӿ���Current�����е�ctx����
	 *
	 *  �汾��ʷ		
	 *       1.0    2009-02-24  lmy   ����
	 *  
	 **********************************************************************/
	  static std::string getInvokeProcessName(const Ice::Context& ctx);

	  /**********************************************************************
	  *  ����: ��ȡ�汾��Ϣ��ͨ����Ϣ��
	  *  �������� collectVersion 
	  *  ����ֵ�� ��
	  *  �����б�	��������    			ȡֵ��Χ     		    ����
	  *    ��
	  *
	  *  �汾��ʷ		
	  *       1.0    2009-04-21  gx   ����
	  *  
	  **********************************************************************/
	  string collectVersion(void);
	  /**********************************************************************
	  *  ����: ��ȡӦ�ð汾��Ϣ
	  *  �������� setAppVersion 
	  *  ����ֵ�� ��
	  *  �����б�	��������    			ȡֵ��Χ     		    ����
	  *  strVersion��[IN] string::strAppVersion				����Ӧ�õİ汾��Ϣ��ȱʡΪ0000
	  *
	  *  �汾��ʷ		
	  *       1.0    2009-04-21  gx   ����
	  *  
	  **********************************************************************/
	  void setAppVersion(const string& strAppVersion = "0000");

	  /**********************************************************************
	   *  ����: Get freeze enviroment home
	   *  �������� GetFreezeEvnHome 
	   *  ����ֵ�� std::string	 	//TODO:����ֵ����
	   *  �����б�	��������    					ȡֵ��Χ     		    ����
	   *
	   *  �汾��ʷ		
	   *       1.0    2011-08-31  Haykin-2010    create
	   *       1.1    2012-01-12  Haykin-2010    ���ݿ�������ΪĿ¼һ����
	   **********************************************************************/
	  std::string GetFreezeEvnHome(const std::string& strDBName = "");

	  std::string GetComponentClassName(void);
	private:
	  void PollStorm(const float para);
	  void ResubscribeAll();

};

/**
* @brief template class for build a standard standalone Ice application server.
   ��ƽ̨�ڲ��ķ���ʹ��
   gaoxin 2009-05-14
*/
template <typename T>
class PlatFormApplicationT : public Ice::Application
{
public:
	virtual int run(int argc, char* argv[])
	{
		T component;
		int status;
		
		status = component.create(appName(),communicator());

//#ifdef APPVERSION
//	component.setAppVersion(APPVERSION);
//#else
//	component.setAppVersion();
//#endif
		component.setAppVersion(m_appVersion);
		
		if(status == EXIT_SUCCESS)
		{
			shutdownOnInterrupt();
			communicator()->waitForShutdown();
		}
		component.destroy();
		if (interrupted())
		{
			std::cerr<<appName()<<": received signal, shutting down."<<endl;
		}
		return status; 
	}

public:
	void getAppVersion(const std::string& appVersion)
	{
		m_appVersion = appVersion;
	}
private:
	std::string m_appVersion;
};

/**
 * @brief template class for build a standard standalone Ice application server.
 */
template <typename T>
class ApplicationT : public Ice::Application
{
public:
    virtual int run(int argc, char* argv[])
    {
        T component;
        int status;
        status = component.create(appName(),communicator());
        if(status == EXIT_SUCCESS)
        {
			shutdownOnInterrupt();
            communicator()->waitForShutdown();
        }
		component.destroy();

		if (interrupted())
		{
			std::cerr<<appName()<<": received signal, shutting down."<<endl;
		}
		
        return status; 
     }
};
/**
 * @brief template class for build a standard IceBox service.
 */
template <typename T>
class ICE_DECLSPEC_EXPORT  IceBoxServiceT : public ::IceBox::Service
{
public:
        IceBoxServiceT(){}
        virtual ~IceBoxServiceT(){}
        virtual void start(const std::string& name, const Ice::CommunicatorPtr& communicator, const Ice::StringSeq& args)
         { 
            T component;
            component.create(name,communicator);
          }
         virtual void stop()
          { 
            T::instance()->adapter()->deactivate();
          }
};
/**
 * @brief template class for build a standalone Component Thread.
 */
template <typename T>
class ThreadApplication : public IceUtil::Thread
{
public:
   ThreadApplication(const int argc,char** argv)
   :_argc(argc),_argv(argv){   }
   virtual void run(){
      iPlature::ApplicationT<T> app;
      int status = app.main(_argc, _argv);return;
   }
private:
   int _argc;
   char** _argv;
};

}//namespace iPlature

#endif



