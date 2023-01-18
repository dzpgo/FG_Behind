#ifndef __CYC_THREAD
#define __CYC_THREAD

#include <pace/Component.h>

namespace iPlature
{
const int SUPPORTED_PRECISION = 1000;	//CycSchedule支持的最小精度.eg:值为1000时精度为1秒;值为100时精度为0.1秒

class CycSchedule;
class DelaySchedule;
typedef IceUtil::Handle<CycSchedule> CycSchedulePtr;
typedef IceUtil::Handle<DelaySchedule> DelaySchedulePtr;

class ScheduleMethod : public IceUtil::SimpleShared
{
public:
	virtual void Execute(float cycleTime)=0;
};
typedef IceUtil::Handle<ScheduleMethod> ScheduleMethodPtr;

// 调用stopScheduling后会执行析构函数
class CycSchedule:public IceUtil::Shared
{
public:
	typedef void (*Function)(const float cycleTime);
	typedef void (Component::*Method)(const float cycleTime);
	typedef enum { NORMAL, ORDERED} CycRunTyp;

	virtual ~CycSchedule();

	static CycSchedulePtr GetObject(string strName);


	string getName() const;
	bool isRunning() const;
	bool isWorking() const;
	bool operator==(const CycSchedule&) const;
	bool operator!=(const CycSchedule&) const;

	// 注册函数
	void registerMethod(Component* const callingObj,Method pMethod,const float cycleTime,const float startTime = -1);
	void registerFunction(Function pFunction,const float cycleTime,const float startTime = -1);
	void registerMethod(ScheduleMethodPtr callObj, const float cycleTime,const float startTime = -1);

	// 开始执行时序安排
	void startScheduling(CycRunTyp runType = NORMAL);
	// 停止执行时序安排
	// pMaxTimeOut：结束标志 -1:等待线程结束 0:立即结束 n:最多等待n秒后结束
	void stopScheduling(int pMaxTimeOut=-1);
private:
	CycSchedule(string strName);

	class _CycScheduleImpl;
	typedef IceUtil::Handle<_CycScheduleImpl> _CycScheduleImplPtr;
	_CycScheduleImplPtr _impl;

	// Object Factory
	typedef vector<CycSchedulePtr> CycScheduleFactory;
	static CycScheduleFactory m_ObjectFactory;
};

class DelaySchedule:public IceUtil::Shared
{
public:
	//为与CycSchedule匹配,故不改变参数名
	typedef void (*Function)(const float cycleTime);
	typedef void (Component::*Method)(const float cycleTime);

	virtual ~DelaySchedule();

	static DelaySchedulePtr GetObject(string strName);
	string getName() const;
	bool isRunning() const;
	bool operator==(const DelaySchedule&) const;
	bool operator!=(const DelaySchedule&) const;
	
	//返回ID号，供cancelScheduling调用
	int registerMethod(Component* const callingObj,Method pMethod,const float delayTime);
	int registerFunction(Function pFunction,const float delayTime);

	// 开始执行时序安排
	void startScheduling();
	// 停止执行时序安排
	// pMaxTimeOut：结束标志 -1:等待线程结束 0:立即结束 n:最多等待n秒后结束
	void stopScheduling(int pMaxTimeOut=-1);
	void cancelScheduling(int nID);
private:

	DelaySchedule(string strName);
	/////////////////////////begin///////////////
	class _DelayCycScheduleImpl;
	typedef IceUtil::Handle<_DelayCycScheduleImpl> _DelayCycScheduleImplPtr;
	_DelayCycScheduleImplPtr _impl;

	////////////////////////end//////////////////


	// Object Factory
	typedef vector<DelaySchedulePtr> DelayScheduleFactory;
	static DelayScheduleFactory m_ObjectFactory;
};

}//namespace iPlature
#endif


