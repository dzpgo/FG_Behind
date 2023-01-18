#pragma once
#include <PowerTranser/MsgDataVisitor.h>
#include <iDA/iDA.h>
#include <pace/SmartData.h>
#include <Ice/BuiltinSequences.h>
#include <PowerTranser/MsgItemInfo.h>

namespace iPlature
{

	typedef enum {
		COM_XCOM_PCS = 1,
		COM_XCOM = 2,
		COM_DBLINK = 3,
		COM_DI = 4
	}E_COM_MOD;

	typedef enum {
		SPLIT_FLAG = 1,
		SPLIT_FIELD = 2,
		SPLIT_SIZE = 3,
		SPLIT_BINARY = 4
	}E_SPLIT_MOD;

	typedef enum {
		DIRECT_RECV,
		DIRECT_SND,
		DIRECT_UNKNOW
	}E_DIRECT_MOD;

	//////////////////////////////////////////////////////////////////////////
	class MsgStruct : public IceUtil::SimpleShared
	{
	public:
		MsgStruct(const std::string& msgname
				, const std::string& msgid
				, E_SPLIT_MOD splitMode
				, E_COM_MOD cmmMode
				, E_DIRECT_MOD dirmod
				, std::string const & dumpTb
				, std::string const & hdlProc);
		void Init(iDA::Connection& cnn, const std::string& msgname);

		MsgItemInfo::VecMsgItemInfo& GetMsgItemInfo() {	return _vcMsgItem;	}
		const MsgItemInfo::VecMsgItemInfo& GetMsgItemInfo() const {	return _vcMsgItem;	}

		string MsgName() const {return _MsgName; }
		std::string MsgID() const { return _MsgID; }
		E_SPLIT_MOD SplitMode() const {return _SplitMode; }
		E_COM_MOD ComMode() const {return _ComMode; }
		E_DIRECT_MOD DirectMod() const {return _directMode; }
		int MsgLength() const { return _pairLen.first; }
		int MsgBinaryLength() const { return _pairLen.second; }
		std::string const & DumpTableName() const { return _DumpTableName; }
		std::vector<std::string> const & ProcName() const { return _HandleProcName;}
	private:
		std::pair<int, int> InitSubItem(iDA::Connection& cnn, const std::string& msgname
									, MsgItemInfo::VecMsgItemInfo& vcMsgItem);
	private:
		std::string _MsgName;
		std::string _MsgID;		//电文号
		E_SPLIT_MOD _SplitMode;		//分隔模式
		E_COM_MOD _ComMode;		//通讯方式
		E_DIRECT_MOD _directMode;
		std::string _DumpTableName;	//Dump数据表名
		std::vector<std::string> _HandleProcName;	//对应的处理程序名
		std::pair<int, int> _pairLen;

		MsgItemInfo::VecMsgItemInfo _vcMsgItem;
	};
	typedef IceUtil::Handle<MsgStruct> MsgStructPtr;

	//////////////////////////////////////////////////////////////////////////


	class MsgHandler;
	class MsgObject : public IceUtil::SimpleShared
	{
	public:
		MsgObject(const std::string& msgname
						, const std::string& msgid
						, E_SPLIT_MOD splitMode
						, E_COM_MOD cmmMode
						, E_DIRECT_MOD dirmod
						, std::string const & dumpTb
						, std::string const & hdlProc);
		MsgObject(const MsgObject& msgobj);

		void Init(iDA::Connection& cnn);

		void visit(MsgDataVisit* dtVisitPtr);

		const MsgStructPtr GetMsgStruct() const { return _msgStructPtr; }


		void DumpValue();


		void ResetData();

		std::string MsgName() {return _msgname;}

		void WriteTo(Ice::ByteSeq& seq) {  _sdVal.writeTo(seq); }

		void RcvMsg(std::string const & data);
		void SndMsg(std::string const & data);
	private:
		void visit(MsgDataVisit* dtVisitPtr, const MsgItemInfo::VecMsgItemInfo& vcMsgItemInfo, SmartData& sd);
	private:
		SmartData _sdVal;  //val
		MsgStructPtr _msgStructPtr;
		std::string _msgname;
		MsgHandler* _rcvHdler;
		MsgHandler* _sndHdler;
		//ComSimulator* _pComSimulator;
		//DumpVisitPtr _dumpVisitPtr;
	};
	typedef IceUtil::Handle<MsgObject> MsgObjectPtr;

	//////////////////////////////////////////////////////////////////////////////////
	class MsgContainer
	{
	private:
		typedef std::vector<MsgObjectPtr> VecMsgObj;
		VecMsgObj _vcMsgObj;

		typedef std::map<std::string, int> MsgNameIndex;
		MsgNameIndex _mpNameIndex;
	public:
		typedef VecMsgObj::const_iterator VecMsgObjIT;
	public:
		static MsgContainer& InstRef();
		void Init(iDA::Connection& cnn);
		MsgObjectPtr GetMsgObject(const std::string& msgname);

		VecMsgObjIT Begin() { return _vcMsgObj.begin(); }
		VecMsgObjIT End() {return _vcMsgObj.end(); }
	private:
		MsgContainer() {}
		MsgContainer(const MsgContainer&) {}
	private:
		static MsgContainer _msgContainer;
	
	};
}//namespace iPlature
