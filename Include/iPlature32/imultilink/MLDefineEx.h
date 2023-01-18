#ifndef __MLDefineEx_h__
#define __MLDefineEx_h__

//#include "imultilink/MLDefine.h"
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// iMultiLink macro define

// max opc group mask
const int ML_MAX_GROUP_MASK = 100000;
const int ML_TIMER_INTERVAL = 1000;

//////////////////////////////////////////////////////////////////////////
// iMultiLink error code define
const int ML_SUCCESS = 0;
const int ML_FAILED = 10001;

//////////////////////////////////////////////////////////////////////////
// iMultiLink mocro define
const string ML_DEFAULT_CONFIG_FILE	= "imultilink.config";

//////////////////////////////////////////////////////////////////////////
// iMultiLink struct define
typedef map <string, string> MapItemNameValue;
typedef map <unsigned long, string> MapItemHandleValue;
typedef map <string, unsigned long> MapItemNameHandle;

#ifdef _IMULTILINK_1_1
typedef map <unsigned long, unsigned long> MapItemIDHandle;
#endif	

// configuration of opc server
typedef struct st_opc_server
{
	unsigned short _server_id;
	string _server_name;
	string _node_name;
	string _clsid_string;
	bool _is_local;
	unsigned short _reconnect_time;
	unsigned long _trigger_rate;
	string _remark;
}ML_OPC_SERVER;
typedef vector <ML_OPC_SERVER> ArrayServer;

// configuration of opc group header
typedef struct str_group_header 
{
	int _code;
	string _descripion;
}ML_GROUP_HEADER;

// configuration of opc group
typedef struct st_opc_group 
{
	ML_GROUP_HEADER _header;
	string _group_name;
	unsigned long _req_update_rate;
	bool _is_active;
	bool _is_use_head;
	string _remark;
#ifdef _IMULTILINK_1_1
	bool _is_async;
#endif
}ML_OPC_GROUP;
typedef vector <ML_OPC_GROUP> ArrayGroup;

// configuration of opc item
typedef struct st_opc_item
{
#ifdef _IMULTILINK_1_1
	unsigned long _item_id;
#endif	
	string _item_name;				//L1 OPC Tag Name
	unsigned short _item_type;
	float _coefficient;
	string _remark;
	string _tag_name;				//L2 Tag Name
	unsigned long _client_handle;
	unsigned long _server_handle;
}ML_OPC_ITEM;
typedef vector <ML_OPC_ITEM> ArrayItem;

// configuration of event
typedef struct st_event 
{
#ifdef _IMULTILINK_1_1
	unsigned long _event_id;
#endif
	string _event_name;
//	ML_OPC_ITEM _trigger_item;
	string _trigger_item_name;
	string _condition_string;
	string _feedback_item_name;
#ifdef _IMULTILINK_1_1
	unsigned long _feedback_item_id;
#endif
	string _feedback_item_value;
}ML_EVENT;
typedef vector <ML_EVENT> ArrayEvent;

#ifdef _IMULTILINK_1_1
// configuration of access
typedef struct st_access 
{
	unsigned long _access_id;
	string _access_name;
	string _trigger_item_name;
	string _feedback_item_name;
	string _feedback_item_value;
	unsigned short _item_type;
}ML_ACCESS;
typedef vector <ML_ACCESS> ArrayAccess;
#endif

// configuration of action
typedef struct st_action 
{
#ifdef _IMULTILINK_1_1
	unsigned long _action_id;
#endif
	string _action_name;
	unsigned short _action_type;
#ifdef _IMULTILINK_1_1
	unsigned long _object_id;
#endif
	string _object_name;
}ML_ACTION;
typedef vector <ML_ACTION> ArrayAction;

// configuration of scheduler
typedef struct st_scheduler 
{
#ifdef _IMULTILINK_1_1
	unsigned long _scheduler_id;
	unsigned long _server_id;
#endif	
	string _scheduler_name;
	unsigned long _scanrate;
	unsigned short _start_type;
}ML_SCHEDULER;
typedef vector <ML_SCHEDULER> ArrayScheduler;

// callback event info
typedef struct st_callback_group
{
	unsigned long _client_handle;
	MapItemHandleValue _map_item_handle_value;
}ML_GROUP_EVENT;

#ifdef _IMULTILINK_1_1
// tag status info
typedef struct st_tag_status_info
{
	bool			_btag_status;
	unsigned long	_item_id;
	string			_strtag_availab_value;
	string			_strTag_disable_value;
	int				_nramp;
}ML_STATUS_INFO;

#endif
//////////////////////////////////////////////////////////////////////////
// iMultiLink enum define
enum SWITCH_STATUS
{
	SWITCH_INIT   = 0,
	SWITCH_MASTER = 1,
	SWITCH_SLAVE  =2
};

enum AGENT_STATUS
{
	AGENT_INIT = 0,
	AGENT_GOOD = 1,
	AGENT_BAD  = 2
};

enum ACTION_TYPE
{
	ACTION_READ_ITEMS = 0,
	ACTION_START_SCHE = 1,
	ACTION_STOP_SCHE  = 2,
	ACTION_FEEDBACK   = 3
};

enum SCHEDULER_TYPE
{
	SCHE_ALWAYS = 0,
	SCHE_EVENT = 1,
};

enum LOG_LEVEL
{
	LOG_DEBUG_LEVEL = 0,
	LOG_INFO_LEVEL  = 1,
	LOG_WARN_LEVEL  = 2,
	LOG_ERROR_LEVEL = 3,
	LOG_FATAL_LEVEL = 4
};

enum LOG_READ_WRITE
{
	LOG_READ  = 0,
	LOG_WRITE = 1
};

typedef struct st_log_read_write
{
	string			_strlog_file_name;
	string			_strcategory;
	string			_strlog_value;
	LOG_LEVEL       _enLogLevel;
	LOG_READ_WRITE	_enLogReadWrite;
}ML_LOG_INFO;

#endif