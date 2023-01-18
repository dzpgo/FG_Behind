/*********************************************************************
 *		
 *  文      件:    iXcomDefine.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2009-06-29    jacklu    创建
 *      1.0    2009-07-03    jacklu    修改添加接口标示，string头文件
*      %USER%   
*********************************************************************/
#ifndef __IXCOMDEFINE_H__
#define __IXCOMDEFINE_H__

#include <string>
#include <vector>
namespace iXcomTCP2
{
	typedef std::vector<char> ArrayMsg;

#ifdef _WIN32
#  ifdef IXCOMTCP2_BUILD_DLL
#    define IXCOMTCP2_EXPORT extern "C" __declspec(dllexport)
#  else
#    define IXCOMTCP2_EXPORT extern "C" __declspec(dllimport)
#  endif
#else
#define IXCOMTCP2_EXPORT extern "C"
#endif

	#define _Interface 
	#define IN 
	#define OUT
	#define INOUT
	#define MAX_XCOM_TEL_LENGTH  9000	//定义9000是确保8192字节

	const int IXCOM_SUCCESS	= 0;
	const int IXCOM_FAILED	= 1;

#ifdef _WIN32
#pragma pack(push)
#endif

#pragma  pack(1)   

	typedef struct ReceiveInfo
	{
		std::string strLineNO;		//回线号
		std::string strMessageID;	//电文号
		ArrayMsg	arrayMsg;		//电文内容
	}RECEIVE_INFO;

	typedef enum
	{
		ONLINE = 1
		,OFFLINE = 2
		,RUN = 3
		,UNKNOWN = 4
	}enLineStatus;

	typedef enum
	{
		INTERPROCESS_ERROR = 1
		,INTERPROCESSQ_ERROR = 3
		,DB_ERROR = 2
		,STD_ERROR = 4
		,UNKNOWN_ERROR = 5
		,LINENO_ERROR = -1
		,LENGTH_ERROR = -2
		,EXIT_ERROR	= 6
		,IXCOM_NOT_RUNING = 7
		,INTERPROCESS_SEND_ERROR = 8
		,INTERPROCESS_TIMEOUT = 9
#ifdef _LINUX_4_6
		,MQ_OPEN_ERROR = 10
		,MQ_SEND_ERROR = 11
		,MQ_RECEIVE_ERROR = 12
#endif
		,ENVIRONMENT_ERROR = 13
	}enErrorCode;

	struct stSessionInfo
	{
		int nLineNo;
		int nClientStatus;
		int nServerStatus;
	};
	struct stSessionsInfo
	{
		stSessionInfo SessionInfo [32];
		int nSize;
	};

	typedef enum
	{
		API_START_SERVER_LINE		= 4
		,API_STOP_SERVER_LINE		= 5
		,API_START_CLIENT_LINE		= 6
		,API_STOP_CLIENT_LINE		= 7
	}enLineControl;

	typedef struct  
	{
		int nHandle;
		char strLineNo[10];
		char strProcessName[100];
	}ST_RPC_CMD;

	//++++++++++++++++++++++++++++++++++++++++++++++++++++
	//     <<< ---  Xcom 通讯双方电文头的结构  --- >>>
	//++++++++++++++++++++++++++++++++++++++++++++++++++++


	//---------------
	//Header type=1
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* 电文长度 */
		char   TelID[6];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[2];                   /* 发送端描述码 */
		char   RecvUnit[2];                   /* 接收端描述码 */
		char   SendSeqNo[4];             	  /* 序列号 */
		char   Spare[8];                	  /* 备用 */

	} HEADER_TYPE1_T;

	//---------------
	//Header type=2
	//---------------
	typedef struct
	{
		char   TelegramLength[4];    		/* 电文长度 */
		char   TelegramCode[4];             /* 电文代码 */
		char   Date[8];                     /* 日期  YYYYMMDD */
		char   Time[6];                     /* 时间  HHMMSS */
		char   SendNode[2];            		/* 传送端 */
		char   ReceiveNode[2];         		/* 接收端 */
		char   Squence[4];             		/*  */
		char   FunctionReq[2];             	/*  */
		char   Spare[8];              		/*  */

	} HEADER_TYPE2_T;

	//---------------
	//Header type=3
	//---------------
	typedef struct
	{
		char   TelID[6];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[2];                   /* 发送端描述码 */
		char   RecvUnit[2];                   /* 接收端描述码 */
		char   SendSeqNo[1];             	  /* 传送功能码, 表示电文的目的，大写字母‘D’表示发送数据。 */

	} HEADER_TYPE3_T;

	//---------------
	//Header type=4
	//---------------
	typedef struct
	{

		//	short  Spare1[2];                     /* 备用 */
		//  short  TelegramLength;    		      /* 电文长度 */
		//	short  Spare2;                        /* 备用 */
		//	short  TelID;                         /* 电文号 */

		char   Spare1[4];                     /* 备用 */
		short  TelegramLength;    		      /* 电文长度 */
		char   Spare2[2];                     /* 备用 */
		short  TelID;                         /* 电文号 */

	} HEADER_TYPE4_T;

	//---------------
	//Header type=5
	//---------------
	typedef struct
	{
		char   TelegramLength[4];    		/* 电文长度 */
		char   TelegramCode[4];             /* 电文代码 */
		char   Date[8];                     /* 日期  YYYYMMDD */
		char   Time[6];                     /* 时间  HHMMSS */
		char   SendNode[2];            		/* 传送端 */
		char   ReceiveNode[2];         		/* 接收端 */
		char   Squence[4];             		/*  */
		char   FunctionReq[2];             	/*  */
		char   Spare[8];              		/*  */

	} HEADER_TYPE5_T;

	//---------------
	//Header type=6
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* 电文长度 */
		char   TelID[6];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[2];                   /* 发送端描述码 */
		char   RecvUnit[2];                   /* 接收端描述码 */
		char   SendStatus;             		  /* 传送功能码 */
		char   ActSendDate[17];               /* 电文产生日期 */

	} HEADER_TYPE6_T;

	//---------------
	//Header type=7
	//---------------
	typedef struct
	{
		short	textlenth;    		      	 /* 电文长度 */
		short	textno;                      /* 电文号 */

	} HEADER_TYPE7_T;

	//---------------
	//Header type=8,单回线，本方为Client端，与ABB通信
	//---------------
	typedef struct		// 缺省结构!
	{
		short	textlenth;    		      	 /* 电文长度 */
		short	textno;                      /* 电文号 */

	} HEADER_TYPE8_T;

	//---------------
	//Header type=9
	//---------------
	//typedef struct		// 缺省结构!
	//{
	//	short	textlenth;    		      	 /* 电文长度 */
	//	short	textno;                      /* 电文号 */

	//} HEADER_TYPE9_T;

	//---------------
	//Header type=10
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* 电文长度 */
		char   TelID[6];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[2];                   /* 发送端描述码 */
		char   RecvUnit[2];                   /* 接收端描述码 */
		char   SendStatus;             		  /* 传送功能码 */
		char   ActSendDate[17];               /* 电文产生日期 */

	} HEADER_TYPE10_T;

	//---------------
	//Header type=11, 9672静态
	//---------------
	typedef struct
	{
		char   TelID[6];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[2];                   /* 发送端描述码 */
		char   RecvUnit[2];                   /* 接收端描述码 */
		char   SendSeqNo[1];             	  /* 传送功能码, 表示电文的目的，大写字母‘D’表示发送数据。 */

	} HEADER_TYPE11_T;

	//---------------
	//Header type=12, 宝钢FLS静态连接
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* 电文长度 */
		char   TelID[5];                      /* 电文号 */
		char   TelType[1];					  /* 电文种类 */
		char   TelRet[1];					  /* 电文处理返回值 */
		char   SendUnit[8];                   /* 发送端描述码 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   Bak[15];             		  /* 备用域 */

	} HEADER_TYPE12_T;

	//---------------
	//Header type=13, 梅钢静态连接
	//---------------
	typedef struct
	{
		char   TelID[6];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[2];                   /* 发送端描述码 */
		char   RecvUnit[2];                   /* 接收端描述码 */
		char   SendStatus;             		  /* 传送功能码 */
		char   TelLength[4];    		      /* 电文长度 */
		char   ActSendDate[17];               /* 电文产生日期 */

	} HEADER_TYPE13_T;

	//---------------
	//Header type=14 二炼钢预处理
	//---------------
	struct HEADER_TYPE14_T
	{
		char   TelLength[4];    		      /* 电文长度 */
		char   ApName[5];             			/* 应用程序名 */
		char   HandleType[1];					/* 处理类型 */
		char   ReturnCode[1];					/* 返回码 */
		char   NodeID[8];					/* 节点名 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */

		char   Spare0[15];                	  /* 备用 */
		char   Spare1[12];                	  /* 备用 */
		char   TelID[4];                      /* 电文号 */	
	};
	//---------------
	//Header type=15 一钢分公司高强钢剪切线
	//---------------
	struct HEADER_TYPE15_T
	{
		int	textlenth;    		      	 /* 电文长度 */
		int	textno;                      /* 电文号 */
	};

	//---------------
	//Header type=16, 加热炉L2与宝信4号炉,静态连接
	//---------------
	typedef struct
	{
		char   TelID[5];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[5];                   /* 发送端描述码 */
		char   RecvUnit[5];                   /* 接收端描述码 */
		char   TelLength[4];    		      /* 电文长度 */

	} HEADER_TYPE16_T;

	//---------------
	//Header type=17 单回线，本方为Server端
	//---------------
	struct HEADER_TYPE17_T
	{
		short	textlenth;    		      	 /* 电文长度 */
		short	textno;                      /* 电文号 */
	};

	//---------------
	//Header type=18
	//---------------
	typedef struct
	{
		char chHead;    		      	 /* 电文标示头 */
		char	chLength[5];                      /* 电文长度*/
	}HEADER_TYPE18_T;
	//---------------
	//Header type=19
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* 电文长度 */
		char   TelID[6];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[2];                   /* 发送端描述码 */
		char   RecvUnit[2];                   /* 接收端描述码 */
		char   SendStatus;             		  /* 传送功能码 */

	} HEADER_TYPE19_T;

	//---------------
	//Header type=20
	//---------------
	typedef struct
	{
		char chHead;    		      	 /* 电文标示头 */
		char	chLength[5];                      /* 电文长度*/
	}HEADER_TYPE20_T;

	//---------------
	//Header type=21
	//---------------
	typedef struct 
	{
		char   TelLength[4];    		      /* 电文长度 */
		char   TelID[4];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 MMDDYYYY*/
		char   SendTime[6];                   /* 电文发送时间 HHMMSS*/
		char   Spare[2];                	  /* 备用 */	
	}HEADER_TYPE21_T;

	//---------------
	//Header type=23
	//---------------
	typedef struct
	{
		char   TelLength[6];    		      /* 电文长度 */
		char   TelID[6];                      /* 电文号 */
		char   SendDate[8];                   /* 电文发送日期 */
		char   SendTime[6];                   /* 电文发送时间 */
		char   SendUnit[2];                   /* 发送端描述码 */
		char   RecvUnit[2];                   /* 接收端描述码 */
		char   SendStatus;             		  /* 传送功能码 */
		char   ActSendDate[17];               /* 电文产生日期 */

	} HEADER_TYPE23_T;


	//---------------
	//Header type=24
	//---------------
	typedef struct
	{
		short	texthead;                      /* 电文头 */
		short	textlenth;    		      	 /* 电文长度 */
		unsigned short	msgid;    		      	 /* 电文号 */
		short	info;    		      	 /* 源--目的地信息 */

	} HEADER_TYPE24_T;

	//---------------
	//Header type=25
	//---------------
	typedef struct
	{
		short	texthead;                      /* 电文头 */
		short	textlenth;    		      	 /* 电文长度 */
	} HEADER_TYPE25_T;

	typedef struct
	{
		char   TelLength[4];    		      /* 电文长度 */
		char   TelID[4];                      /* 电文号 */
	} HEADER_TYPE26_T;

	typedef struct
	{
		char   TelID[5];                      /* 电文代号 */
		char   SendDate[8];                   /* 电文发送日期 MMDDYYYY*/
		char   SendTime[6];                   /* 电文发送时间 HHMMSS*/
		char   SendUnit[5];                   /* 发送端描述码 */
		char   RecvUnit[5];                   /* 接收端描述码 */
		char   TelLength[4];    		      /* 电文长度 */
		char   MsgType[1];                      /* 电文种类 */
		char   RC[1];							 /* 传送功能码*/
		char   APPID[5];                      /* 实际电文号 */		
		char   Spare[8];                	  /* 备用 */	
	} HEADER_TYPE27_T;

	typedef struct
	{
		short	subHeader;    		      	 /* Sub Header 0x0060*/
		short	textlenth;                      /* 电文长度 */
		char	msgCode[4];						/* 电文号 */
	} HEADER_TYPE28_T;



	//++++++++++++++++++++++++++++++++++++++++++++++++++++
	//     <<< ---  XcomRcv接收的电文的结构  --- >>>
	//++++++++++++++++++++++++++++++++++++++++++++++++++++

	struct stru_recvtext0				//normal struct
	{
		short	textlenth;
		short	lineno;
		char	ctextno[12];
		char	textbuf[MAX_XCOM_TEL_LENGTH-16];	// Include Telegram Header
	};

	struct stru_recvtext1				//Headtype=1
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE1_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-40-1];
		char	endflag;
	};

	struct stru_recvtext2				//Headtype=2
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE2_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-40-1];
		char	endflag;
	};

	struct stru_recvtext3				//Headtype=3
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE3_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-25-1];
		char	endflag;
	};

	struct stru_recvtext4				//Headtype=4
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE4_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-10];
	};

	struct stru_recvtext5				//Headtype=5
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE5_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-40-1];
		char	endflag;
	};

	struct stru_recvtext6				//Headtype=6
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE6_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-46-1];
		char	endflag;
	};

	struct stru_recvtext7				//Headtype=7
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE7_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-4];
	};

	struct stru_recvtext8				//Headtype=8
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		//HEADER_TYPE8_T  header;
		//char	textbuf[MAX_XCOM_TEL_LENGTH-16-TYPE_8_HEADERLENGTH];
		char	textbuf[MAX_XCOM_TEL_LENGTH-16];
	};

	struct stru_recvtext9				//Headtype=9
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		//HEADER_TYPE9_T  header;
		//char	textbuf[MAX_XCOM_TEL_LENGTH-16-TYPE_9_HEADERLENGTH];
		char	textbuf[MAX_XCOM_TEL_LENGTH-16];
	};

	struct stru_recvtext10				//Headtype=10
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE10_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-46-1];
		char	endflag;
	};

	struct stru_recvtext11				//Headtype=11, 9672静态
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE11_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-25-1];
		char	endflag;
	};

	struct stru_recvtext12				//Headtype=12, 宝钢FLS静态连接
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE12_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-48-1];
		char	endflag;
	};

	struct stru_recvtext13				//Headtype=13, 梅钢静态连接
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE13_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-46-1];
		char	endflag;
	};
	struct stru_recvtext14				//Headtype=14, 二炼钢预处理静态连接
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE14_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-64-1];
		char	endflag;
	};

	struct stru_recvtext15				//Headtype=15, 一钢分公司高强钢剪切线
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE15_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-8 ];
	};
	struct stru_recvtext17				//Headtype=17
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		char	textbuf[MAX_XCOM_TEL_LENGTH-16];
	};
	struct stru_recvtext18				//Headtype=18
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE18_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-6-1];
		char	endflag;
	};
	struct stru_recvtext19				//Headtype=19
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE19_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-29-1];
		char	endflag;
	};
	struct stru_recvtext20				//Headtype=20
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE20_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-6-1];
		char	endflag;
	};
	struct stru_recvtext21				//Headtype=21
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE21_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-24-1];
		char	endflag;
	};
	struct stru_recvtext23				//Headtype=23
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE23_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-48-1];
		char	endflag;
	};
	struct stru_recvtext24				//Headtype=24
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE24_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-8];
	};
	struct stru_recvtext25				//Headtype=25
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE25_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-4];
	};
	struct stru_recvtext26				//Headtype=26
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE26_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-8];
	};
	struct stru_recvtext27				//Headtype=27
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE27_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-48-1];
	};
	struct stru_recvtext28				//Headtype=28
	{
		short	textlenth;				//Xcom收到电文后增加的内部数据 <1>
		short	lineno;					//Xcom收到电文后增加的内部数据 <2>
		char	ctextno[12];			//Xcom收到电文后增加的内部数据 <3>
		HEADER_TYPE28_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-8];
	};

#ifdef _WIN32
#pragma pack(pop)
#else
#pragma   pack()   
#endif

}

#endif
