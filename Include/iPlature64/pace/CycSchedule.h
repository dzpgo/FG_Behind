#ifndef __CYC_THREAD
#define __CYC_THREAD

#include <pace/Component.h>

namespace iPlature
{
const int SUPPORTED_PRECISION = 1000;	//CycSchedule֧�ֵ���С����.eg:ֵΪ1000ʱ����Ϊ1��;ֵΪ100ʱ����Ϊ0.1��

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

// ����stopScheduling���ִ����������
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

	// ע�ắ��
	void registerMethod(Component* const callingObj,Method pMethod,const float cycleTime,const float startTime = -1);
	void registerFunction(Function pFunction,const float cycleTime,const float startTime = -1);
	void registerMethod(ScheduleMethodPtr callObj, const float cycleTime,const float startTime = -1);

	// ��ʼִ��ʱ����
	void startScheduling(CycRunTyp runType = NORMAL);
	// ִֹͣ��ʱ����
	// pMaxTimeOut��������־ -1:�ȴ��߳̽��� 0:�������� n:���ȴ�n������
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
	//Ϊ��CycScheduleƥ��,�ʲ��ı������
	typedef void (*Function)(const float cycleTime);
	typedef void (Component::*Method)(const float cycleTime);

	virtual ~DelaySchedule();

	static DelaySchedulePtr GetObject(string strName);
	string getName() const;
	bool isRunning() const;
	bool operator==(const DelaySchedule&) const;
	bool operator!=(const DelaySchedule&) const;
	
	//����ID�ţ���cancelScheduling����
	int registerMethod(Component* const callingObj,Method pMethod,const float delayTime);
	int registerFunction(Function pFunction,const float delayTime);

	// ��ʼִ��ʱ����
	void startScheduling();
	// ִֹͣ��ʱ����
	// pMaxTimeOut��������־ -1:�ȴ��߳̽��� 0:�������� n:���ȴ�n������
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


