#pragma once
#include <PowerTranser/MsgItemInfo.h>

namespace iPlature
{
	class SmartData;

	class MsgDataVisit
	{
	public:
		virtual ~MsgDataVisit () = 0;
		virtual void visitInteger(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitFloat(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitDouble(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitString(SmartData& sd, const MsgItemInfo& itemInfo) {}
		//virtual void visitACK(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD8(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBYTE(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitHEX(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitTIME(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRFLOAT(SmartData& sd, const MsgItemInfo& itemInfo) {}
	};

	class SizeRcvVisit : public MsgDataVisit
	{
	public:
		SizeRcvVisit(const std::string& data) : _data(data), _pos(0) {}
		~SizeRcvVisit(){}
		virtual void visitInteger(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitFloat(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitDouble(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitString(SmartData& sd, const MsgItemInfo& itemInfo);
		//virtual void visitACK(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD2(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitBCD4(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitBCD8(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitBYTE(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitHEX(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitINT2(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitRINT2(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitRINT4(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitTIME(SmartData& sd, const MsgItemInfo& itemInfo);
		virtual void visitRFLOAT(SmartData& sd, const MsgItemInfo& itemInfo);
	private:
		void vistData(SmartData& sd, const MsgItemInfo& itemInfo);
	private:
		std::string _data;
		int _pos;
	};

	class SizeSndVisit : public MsgDataVisit
	{
	public:
		virtual void visitInteger(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitFloat(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitDouble(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitString(SmartData& sd, const MsgItemInfo& itemInfo) {}
		//virtual void visitACK(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD8(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBYTE(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitHEX(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitTIME(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRFLOAT(SmartData& sd, const MsgItemInfo& itemInfo) {}
	};

	class BinaryRcvVisit : public MsgDataVisit
	{
	public:
		virtual void visitInteger(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitFloat(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitDouble(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitString(SmartData& sd, const MsgItemInfo& itemInfo) {}
		//virtual void visitACK(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD8(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBYTE(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitHEX(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitTIME(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRFLOAT(SmartData& sd, const MsgItemInfo& itemInfo) {}
	};

	class BinarySndVisit : public MsgDataVisit
	{
	public:
		virtual void visitInteger(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitFloat(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitDouble(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitString(SmartData& sd, const MsgItemInfo& itemInfo) {}
		//virtual void visitACK(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD8(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBYTE(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitHEX(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitTIME(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRFLOAT(SmartData& sd, const MsgItemInfo& itemInfo) {}
	};

	class ScaleVisit : public MsgDataVisit
	{
	public:
		virtual ~ScaleVisit(){}
		virtual void visitInteger(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitFloat(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitDouble(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitString(SmartData& sd, const MsgItemInfo& itemInfo) {}
		//virtual void visitACK(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBCD8(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitBYTE(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitHEX(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT2(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRINT4(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitTIME(SmartData& sd, const MsgItemInfo& itemInfo) {}
		virtual void visitRFLOAT(SmartData& sd, const MsgItemInfo& itemInfo) {}
	};
}