#ifndef __PACE_H__
#define __PACE_H__

#include <pace/GenericDef.h>
#include <pace/Component.h>
#include <pace/Parameter.h>
#include <pace/ProxyWrapper.h>
#include <pace/ExceptionTracer.h>
#define PACE_SERVER_INSTALL(component) \
        int main(int argc, char* argv[]){iPlature::ApplicationT<component> app;int status = app.main(argc, argv);return status;}

#define PACE_PLATFORM_SERVER_INSTALL(component,version) \
	int main(int argc, char* argv[]){iPlature::PlatFormApplicationT<component> app;app.getAppVersion(version);int status = app.main(argc, argv);return status;}


#define PACE_ICEBOX_INSTALL(component) \
   extern "C"{ICE_DECLSPEC_EXPORT IceBox::Service* create(Ice::CommunicatorPtr communicator){return new iPlature::IceBoxServiceT<component>;}}

#define PACE_HMI_INSTALL(component) \
        extern "C" int HandleClientMessage(); \
        extern "C" void PostInitCall(int argc, char *argv[]); \
        void PostInitCall(int argc, char *argv[]) { \
            IceUtil::ThreadPtr app##component = new ThreadApplication<component>(argc,argv);\
            app##component->start(); \
            return; }
         

#define PACE_INSTALL(component) PACE_SERVER_INSTALL(component)

#endif


