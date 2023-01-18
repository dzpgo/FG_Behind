#pragma once
#include <vector>
#include <map>
#include <iDA/iDA.h>
namespace iPlature
{
	typedef struct _PCSMsgInfo
	{
		int headLen;
		int lineno;
		std::string msgid;
		_PCSMsgInfo(int hdlen, int line, const std::string& id) : headLen(hdlen), lineno(line), msgid(id) {}
	} PCSMsgInfo, *PCSMsgInfoPtr;
	typedef std::vector<PCSMsgInfoPtr> VecPCSMsgInfo;
	typedef std::map<std::string, int> MapPcsMsgInfoIndex;

	class PCSConfig
	{
	public:
		static PCSConfig& InstRef();
		void Init(iDA::Connection& cnn);
		PCSMsgInfoPtr GetInfoFromMsgID(const std::string& msgid);
		PCSMsgInfoPtr GetInfoFromMsgName(const std::string& msgname);
	private:
		PCSMsgInfoPtr GetInfo(const std::string& msgkey, const MapPcsMsgInfoIndex& mapIndex);
	private:
		static PCSConfig _ins;
		PCSConfig() {}
	private:
		VecPCSMsgInfo _vcPCSMsgInfo;
		MapPcsMsgInfoIndex _mpMsgIDIndex;
		MapPcsMsgInfoIndex _mpMsgNameIndex;
	};
}

