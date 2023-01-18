#pragma once
#include <vector>
#include <string>
namespace iPlature
{
	class MsgObject;

	class MsgHandler
	{
	public:
		virtual void HandleMsg(std::string const & data) = 0;
	};

	class MsgBaseHandler : public MsgHandler
	{
	public:
		MsgBaseHandler(MsgObject* msgobj);
		virtual ~MsgBaseHandler();
	protected:
		//virtual MsgDataVisit* CreateDataVisitor() = 0;

		void VisitScale();
		//virtual void VisitData();

		void Prepare();
	protected:
		MsgObject* _msgobj;
		//MsgDataVisit* _dtVisitor;
	};

	//////////////////////////////////////////////////////////////////////////
	

	class MsgRcvHandler : public MsgBaseHandler
	{
	public:
		MsgRcvHandler(MsgObject* msgobj) : MsgBaseHandler(msgobj) {}
		virtual ~MsgRcvHandler() {}

		virtual void HandleMsg(std::string const & data);

	protected:
		//MsgDataVisit* CreateDataVisitor(const std::vector<unsigned char>& data);
		void ParseData(std::string const & data);

		virtual void VisitData(std::string const & data);
		void VisitSizeData(std::string const & data);
		void VisitBinaryData(std::string const & data);

		void CallApp();
		//void CallProc(std::string const & procname, const std::vector<unsigned char>& data);

	};

	class MsgSndHandler : public MsgBaseHandler
	{
	public:
		MsgSndHandler(MsgObject* msgobj) : MsgBaseHandler(msgobj) {}
		virtual ~MsgSndHandler() {}

		virtual void HandleMsg(std::string const & data);

	protected:
		//MsgDataVisit* CreateDataVisitor();
		void FormData(std::string const & data);

		virtual void CallApp() = 0;
	};

	class MsgXcomSndHandler : public MsgSndHandler
	{
	public:
		MsgXcomSndHandler(MsgObject* msgobj) : MsgSndHandler(msgobj) {}
	protected:
		virtual void CallApp();
	};

	class MsgDISndHandler : public MsgSndHandler
	{
	public:
		MsgDISndHandler(MsgObject* msgobj) : MsgSndHandler(msgobj) {}
	protected:
		virtual void CallApp();
	};


	class MsgHandlerFactory
	{
	public:
		static MsgHandler* CreateMsgRcvHandler(MsgObject* msgobj);
		static MsgHandler* CreateMsgSndHandler(MsgObject* msgobj);
	};

	
}