#pragma once
#include <string>
namespace iPlature
{
	class MsgItemDataType
	{
	public:
		typedef enum _enMsgDataType
		{
											//DB				//SmartData			//SPLIT_MOD		//Default Length
			//  DT_ACK				//NOT DATA TYPE												HAYKIN 2012-9-24	
			  DT_BCD2
			, DT_BCD4				//BCD4			//INTEGER			//Binary				4
			, DT_BCD8					//BCD8			//INTEGER			//Binary				4
			, DT_BYTE					//BYTE			//STRING				//Binary				0

			, DT_FLOAT				//FLOAT		//DOUBLE				//Binary|Size			4
			, DT_DOUBLE				//DOUBLE	//DOUBLE				//Binary|Size			8
			, DT_HEX					//HEX			//INTEGER			//Binary				2

			, DT_INT2					//INT2			//SHORT				//Binary|Size			2
			, DT_INT					//INTEGER	//INTEGER			//Binary|Size			4
			
			, DT_RFLOAT				//RFLOAT		//DOUBLE				//Binary				4
			, DT_RINT2				//RINT2		//SHORT				//Binary				2
			, DT_RINT4				//RINT4		//INTEGER			//Binary				4

			, DT_TIME					//TIME			//STRING				//Binary|Size			0
			, DT_STRING				//STRING		//STRING				//Binary|Size			0

			, DT_UNKNOW
		}MsgDataType;

		MsgItemDataType();
		MsgItemDataType(const std::string& strDtType);

		MsgDataType DataType() const;

		static MsgDataType ToDataType(const std::string& strDtType);
		static int GetDefaultBinaryLen(MsgDataType typ);

		MsgItemDataType(const MsgItemDataType& msgDtType);

		MsgItemDataType& operator = (const std::string& strDtType);
		MsgItemDataType& operator = (const MsgDataType& strDtType);

		bool operator == (const MsgItemDataType& msgDtType);

		operator MsgDataType();

		bool IsShort() const;

		bool IsInterger() const;

		bool IsNumber() const;

		bool IsTime() const;

		bool IsString() const;

		bool IsByte() const;

		bool IsCompoist() const;

		std::string ToString() const;

		//int DefaultBinaryLen() const;

	private:
		MsgDataType _type;
		//int _defBinaryLen;
	};

	inline MsgItemDataType::MsgDataType MsgItemDataType::DataType() const { return _type; }
}


