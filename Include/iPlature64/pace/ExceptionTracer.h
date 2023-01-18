#ifndef __PACE_EXCEPTION_TRACER_H__
#define __PACE_EXCEPTION_TRACER_H__
#include <string>
#include <Ice/Exception.h>
namespace iPlature
{
struct GlobalErrorHandler
{
      GlobalErrorHandler();
      static void UnkownExceptionHandler();
      static void SignalHandler(int signo);
      static void printStacks(const std::string& name);
      static void printIceException(const Ice::Exception& e,const std::string& msg="");
};

}//namespace

#define    PACE_CATCH_EXCEPTION_RETURN(ret) catch(const Ice::Exception& e) \
                                                {iPlature::GlobalErrorHandler::printIceException(e,"PACE_EXCEPTION_RETURN");return ret;}
#define    PACE_CATCH_EXCEPTION_THROW(ex)   catch(const Ice::Exception& e) \
                                                {iPlature::GlobalErrorHandler::printIceException(e,"PACE_EXCEPTION_THROW");throw ex;}
#define    PACE_CATCH_EXCEPTION_RETHROW()   catch(const Ice::Exception& e) \
                                                {iPlature::GlobalErrorHandler::printIceException(e,"PACE_EXCEPTION_RETHROW");throw e;}
#define    PACE_CATCH_EXCEPTION_CONTINUE()  catch(const Ice::Exception& e) \
                                                {iPlature::GlobalErrorHandler::printIceException(e,"PACE_EXCEPTION_CONTINUE");continue;}
#define    PACE_CATCH_EXCEPTION_BREAK()     catch(const Ice::Exception& e) \
                                                {iPlature::GlobalErrorHandler::printIceException(e,"PACE_EXCEPTION_BREAK");break;}
#define    PACE_CATCH_EXCEPTION_EXIT(code)  catch(const Ice::Exception& e) \
                                                {iPlature::GlobalErrorHandler::printIceException(e,"PACE_EXCEPTION_EXIT:"#code );exit(code);}
#define    PACE_CATCH_EXCEPTION()           catch(const Ice::Exception& e) \
                                                {iPlature::GlobalErrorHandler::printIceException(e,"PACE_EXCEPTION");}


#endif



