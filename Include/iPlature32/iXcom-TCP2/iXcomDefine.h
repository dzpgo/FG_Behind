/*********************************************************************
 *		
 *  ��      ��:    iXcomDefine.h   		//TODO������ļ�����
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������//TODO����ӱ��ļ�����������ϸ����
 *        ��//TODO
 *        ��//TODO
 *
 *  �汾��ʷ		
 *      1.0    2009-06-29    jacklu    ����
 *      1.0    2009-07-03    jacklu    �޸���ӽӿڱ�ʾ��stringͷ�ļ�
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
	#define MAX_XCOM_TEL_LENGTH  9000	//����9000��ȷ��8192�ֽ�

	const int IXCOM_SUCCESS	= 0;
	const int IXCOM_FAILED	= 1;

#ifdef _WIN32
#pragma pack(push)
#endif

#pragma  pack(1)   

	typedef struct ReceiveInfo
	{
		std::string strLineNO;		//���ߺ�
		std::string strMessageID;	//���ĺ�
		ArrayMsg	arrayMsg;		//��������
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
	//     <<< ---  Xcom ͨѶ˫������ͷ�Ľṹ  --- >>>
	//++++++++++++++++++++++++++++++++++++++++++++++++++++


	//---------------
	//Header type=1
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* ���ĳ��� */
		char   TelID[6];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[2];                   /* ���Ͷ������� */
		char   RecvUnit[2];                   /* ���ն������� */
		char   SendSeqNo[4];             	  /* ���к� */
		char   Spare[8];                	  /* ���� */

	} HEADER_TYPE1_T;

	//---------------
	//Header type=2
	//---------------
	typedef struct
	{
		char   TelegramLength[4];    		/* ���ĳ��� */
		char   TelegramCode[4];             /* ���Ĵ��� */
		char   Date[8];                     /* ����  YYYYMMDD */
		char   Time[6];                     /* ʱ��  HHMMSS */
		char   SendNode[2];            		/* ���Ͷ� */
		char   ReceiveNode[2];         		/* ���ն� */
		char   Squence[4];             		/*  */
		char   FunctionReq[2];             	/*  */
		char   Spare[8];              		/*  */

	} HEADER_TYPE2_T;

	//---------------
	//Header type=3
	//---------------
	typedef struct
	{
		char   TelID[6];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[2];                   /* ���Ͷ������� */
		char   RecvUnit[2];                   /* ���ն������� */
		char   SendSeqNo[1];             	  /* ���͹�����, ��ʾ���ĵ�Ŀ�ģ���д��ĸ��D����ʾ�������ݡ� */

	} HEADER_TYPE3_T;

	//---------------
	//Header type=4
	//---------------
	typedef struct
	{

		//	short  Spare1[2];                     /* ���� */
		//  short  TelegramLength;    		      /* ���ĳ��� */
		//	short  Spare2;                        /* ���� */
		//	short  TelID;                         /* ���ĺ� */

		char   Spare1[4];                     /* ���� */
		short  TelegramLength;    		      /* ���ĳ��� */
		char   Spare2[2];                     /* ���� */
		short  TelID;                         /* ���ĺ� */

	} HEADER_TYPE4_T;

	//---------------
	//Header type=5
	//---------------
	typedef struct
	{
		char   TelegramLength[4];    		/* ���ĳ��� */
		char   TelegramCode[4];             /* ���Ĵ��� */
		char   Date[8];                     /* ����  YYYYMMDD */
		char   Time[6];                     /* ʱ��  HHMMSS */
		char   SendNode[2];            		/* ���Ͷ� */
		char   ReceiveNode[2];         		/* ���ն� */
		char   Squence[4];             		/*  */
		char   FunctionReq[2];             	/*  */
		char   Spare[8];              		/*  */

	} HEADER_TYPE5_T;

	//---------------
	//Header type=6
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* ���ĳ��� */
		char   TelID[6];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[2];                   /* ���Ͷ������� */
		char   RecvUnit[2];                   /* ���ն������� */
		char   SendStatus;             		  /* ���͹����� */
		char   ActSendDate[17];               /* ���Ĳ������� */

	} HEADER_TYPE6_T;

	//---------------
	//Header type=7
	//---------------
	typedef struct
	{
		short	textlenth;    		      	 /* ���ĳ��� */
		short	textno;                      /* ���ĺ� */

	} HEADER_TYPE7_T;

	//---------------
	//Header type=8,�����ߣ�����ΪClient�ˣ���ABBͨ��
	//---------------
	typedef struct		// ȱʡ�ṹ!
	{
		short	textlenth;    		      	 /* ���ĳ��� */
		short	textno;                      /* ���ĺ� */

	} HEADER_TYPE8_T;

	//---------------
	//Header type=9
	//---------------
	//typedef struct		// ȱʡ�ṹ!
	//{
	//	short	textlenth;    		      	 /* ���ĳ��� */
	//	short	textno;                      /* ���ĺ� */

	//} HEADER_TYPE9_T;

	//---------------
	//Header type=10
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* ���ĳ��� */
		char   TelID[6];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[2];                   /* ���Ͷ������� */
		char   RecvUnit[2];                   /* ���ն������� */
		char   SendStatus;             		  /* ���͹����� */
		char   ActSendDate[17];               /* ���Ĳ������� */

	} HEADER_TYPE10_T;

	//---------------
	//Header type=11, 9672��̬
	//---------------
	typedef struct
	{
		char   TelID[6];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[2];                   /* ���Ͷ������� */
		char   RecvUnit[2];                   /* ���ն������� */
		char   SendSeqNo[1];             	  /* ���͹�����, ��ʾ���ĵ�Ŀ�ģ���д��ĸ��D����ʾ�������ݡ� */

	} HEADER_TYPE11_T;

	//---------------
	//Header type=12, ����FLS��̬����
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* ���ĳ��� */
		char   TelID[5];                      /* ���ĺ� */
		char   TelType[1];					  /* �������� */
		char   TelRet[1];					  /* ���Ĵ�����ֵ */
		char   SendUnit[8];                   /* ���Ͷ������� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   Bak[15];             		  /* ������ */

	} HEADER_TYPE12_T;

	//---------------
	//Header type=13, ÷�־�̬����
	//---------------
	typedef struct
	{
		char   TelID[6];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[2];                   /* ���Ͷ������� */
		char   RecvUnit[2];                   /* ���ն������� */
		char   SendStatus;             		  /* ���͹����� */
		char   TelLength[4];    		      /* ���ĳ��� */
		char   ActSendDate[17];               /* ���Ĳ������� */

	} HEADER_TYPE13_T;

	//---------------
	//Header type=14 ������Ԥ����
	//---------------
	struct HEADER_TYPE14_T
	{
		char   TelLength[4];    		      /* ���ĳ��� */
		char   ApName[5];             			/* Ӧ�ó����� */
		char   HandleType[1];					/* �������� */
		char   ReturnCode[1];					/* ������ */
		char   NodeID[8];					/* �ڵ��� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */

		char   Spare0[15];                	  /* ���� */
		char   Spare1[12];                	  /* ���� */
		char   TelID[4];                      /* ���ĺ� */	
	};
	//---------------
	//Header type=15 һ�ַֹ�˾��ǿ�ּ�����
	//---------------
	struct HEADER_TYPE15_T
	{
		int	textlenth;    		      	 /* ���ĳ��� */
		int	textno;                      /* ���ĺ� */
	};

	//---------------
	//Header type=16, ����¯L2�뱦��4��¯,��̬����
	//---------------
	typedef struct
	{
		char   TelID[5];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[5];                   /* ���Ͷ������� */
		char   RecvUnit[5];                   /* ���ն������� */
		char   TelLength[4];    		      /* ���ĳ��� */

	} HEADER_TYPE16_T;

	//---------------
	//Header type=17 �����ߣ�����ΪServer��
	//---------------
	struct HEADER_TYPE17_T
	{
		short	textlenth;    		      	 /* ���ĳ��� */
		short	textno;                      /* ���ĺ� */
	};

	//---------------
	//Header type=18
	//---------------
	typedef struct
	{
		char chHead;    		      	 /* ���ı�ʾͷ */
		char	chLength[5];                      /* ���ĳ���*/
	}HEADER_TYPE18_T;
	//---------------
	//Header type=19
	//---------------
	typedef struct
	{
		char   TelLength[4];    		      /* ���ĳ��� */
		char   TelID[6];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[2];                   /* ���Ͷ������� */
		char   RecvUnit[2];                   /* ���ն������� */
		char   SendStatus;             		  /* ���͹����� */

	} HEADER_TYPE19_T;

	//---------------
	//Header type=20
	//---------------
	typedef struct
	{
		char chHead;    		      	 /* ���ı�ʾͷ */
		char	chLength[5];                      /* ���ĳ���*/
	}HEADER_TYPE20_T;

	//---------------
	//Header type=21
	//---------------
	typedef struct 
	{
		char   TelLength[4];    		      /* ���ĳ��� */
		char   TelID[4];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� MMDDYYYY*/
		char   SendTime[6];                   /* ���ķ���ʱ�� HHMMSS*/
		char   Spare[2];                	  /* ���� */	
	}HEADER_TYPE21_T;

	//---------------
	//Header type=23
	//---------------
	typedef struct
	{
		char   TelLength[6];    		      /* ���ĳ��� */
		char   TelID[6];                      /* ���ĺ� */
		char   SendDate[8];                   /* ���ķ������� */
		char   SendTime[6];                   /* ���ķ���ʱ�� */
		char   SendUnit[2];                   /* ���Ͷ������� */
		char   RecvUnit[2];                   /* ���ն������� */
		char   SendStatus;             		  /* ���͹����� */
		char   ActSendDate[17];               /* ���Ĳ������� */

	} HEADER_TYPE23_T;


	//---------------
	//Header type=24
	//---------------
	typedef struct
	{
		short	texthead;                      /* ����ͷ */
		short	textlenth;    		      	 /* ���ĳ��� */
		unsigned short	msgid;    		      	 /* ���ĺ� */
		short	info;    		      	 /* Դ--Ŀ�ĵ���Ϣ */

	} HEADER_TYPE24_T;

	//---------------
	//Header type=25
	//---------------
	typedef struct
	{
		short	texthead;                      /* ����ͷ */
		short	textlenth;    		      	 /* ���ĳ��� */
	} HEADER_TYPE25_T;

	typedef struct
	{
		char   TelLength[4];    		      /* ���ĳ��� */
		char   TelID[4];                      /* ���ĺ� */
	} HEADER_TYPE26_T;

	typedef struct
	{
		char   TelID[5];                      /* ���Ĵ��� */
		char   SendDate[8];                   /* ���ķ������� MMDDYYYY*/
		char   SendTime[6];                   /* ���ķ���ʱ�� HHMMSS*/
		char   SendUnit[5];                   /* ���Ͷ������� */
		char   RecvUnit[5];                   /* ���ն������� */
		char   TelLength[4];    		      /* ���ĳ��� */
		char   MsgType[1];                      /* �������� */
		char   RC[1];							 /* ���͹�����*/
		char   APPID[5];                      /* ʵ�ʵ��ĺ� */		
		char   Spare[8];                	  /* ���� */	
	} HEADER_TYPE27_T;

	typedef struct
	{
		short	subHeader;    		      	 /* Sub Header 0x0060*/
		short	textlenth;                      /* ���ĳ��� */
		char	msgCode[4];						/* ���ĺ� */
	} HEADER_TYPE28_T;



	//++++++++++++++++++++++++++++++++++++++++++++++++++++
	//     <<< ---  XcomRcv���յĵ��ĵĽṹ  --- >>>
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
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE1_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-40-1];
		char	endflag;
	};

	struct stru_recvtext2				//Headtype=2
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE2_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-40-1];
		char	endflag;
	};

	struct stru_recvtext3				//Headtype=3
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE3_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-25-1];
		char	endflag;
	};

	struct stru_recvtext4				//Headtype=4
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE4_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-10];
	};

	struct stru_recvtext5				//Headtype=5
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE5_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-40-1];
		char	endflag;
	};

	struct stru_recvtext6				//Headtype=6
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE6_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-46-1];
		char	endflag;
	};

	struct stru_recvtext7				//Headtype=7
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE7_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-4];
	};

	struct stru_recvtext8				//Headtype=8
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		//HEADER_TYPE8_T  header;
		//char	textbuf[MAX_XCOM_TEL_LENGTH-16-TYPE_8_HEADERLENGTH];
		char	textbuf[MAX_XCOM_TEL_LENGTH-16];
	};

	struct stru_recvtext9				//Headtype=9
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		//HEADER_TYPE9_T  header;
		//char	textbuf[MAX_XCOM_TEL_LENGTH-16-TYPE_9_HEADERLENGTH];
		char	textbuf[MAX_XCOM_TEL_LENGTH-16];
	};

	struct stru_recvtext10				//Headtype=10
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE10_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-46-1];
		char	endflag;
	};

	struct stru_recvtext11				//Headtype=11, 9672��̬
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE11_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-25-1];
		char	endflag;
	};

	struct stru_recvtext12				//Headtype=12, ����FLS��̬����
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE12_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-48-1];
		char	endflag;
	};

	struct stru_recvtext13				//Headtype=13, ÷�־�̬����
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE13_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-46-1];
		char	endflag;
	};
	struct stru_recvtext14				//Headtype=14, ������Ԥ����̬����
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE14_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-64-1];
		char	endflag;
	};

	struct stru_recvtext15				//Headtype=15, һ�ַֹ�˾��ǿ�ּ�����
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE15_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-8 ];
	};
	struct stru_recvtext17				//Headtype=17
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		char	textbuf[MAX_XCOM_TEL_LENGTH-16];
	};
	struct stru_recvtext18				//Headtype=18
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE18_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-6-1];
		char	endflag;
	};
	struct stru_recvtext19				//Headtype=19
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE19_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-29-1];
		char	endflag;
	};
	struct stru_recvtext20				//Headtype=20
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE20_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-6-1];
		char	endflag;
	};
	struct stru_recvtext21				//Headtype=21
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE21_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-24-1];
		char	endflag;
	};
	struct stru_recvtext23				//Headtype=23
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE23_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-48-1];
		char	endflag;
	};
	struct stru_recvtext24				//Headtype=24
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE24_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-8];
	};
	struct stru_recvtext25				//Headtype=25
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE25_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-4];
	};
	struct stru_recvtext26				//Headtype=26
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE26_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-8];
	};
	struct stru_recvtext27				//Headtype=27
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
		HEADER_TYPE27_T  header;
		char	textbuf[MAX_XCOM_TEL_LENGTH-16-48-1];
	};
	struct stru_recvtext28				//Headtype=28
	{
		short	textlenth;				//Xcom�յ����ĺ����ӵ��ڲ����� <1>
		short	lineno;					//Xcom�յ����ĺ����ӵ��ڲ����� <2>
		char	ctextno[12];			//Xcom�յ����ĺ����ӵ��ڲ����� <3>
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
