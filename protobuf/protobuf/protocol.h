
#pragma once

# if (defined(__GNUC__) && __GNUC__ >= 3) || ( defined(_MSC_VER) && _MSC_VER >= 2100)
	#include <functional>
	#include <memory>
	#include <mutex>
	#include <thread>
	#include <string>
	#include <vector>
	#include <map>
	#include <set>

	#include <stdint.h>
	#include <stdio.h>
	#include <string.h>
#else
	#include "zwldef.h"
#endif

# if (defined(__GNUC__) && __GNUC__ >= 3) || ( defined(_MSC_VER) && _MSC_VER >= 2100)
	typedef uint8_t				XBYTE;
	typedef uint16_t			XWORD;
	typedef	int16_t				XINT16;
	typedef	int32_t				XINT32;
	typedef	uint32_t			XDWORD;
	typedef	int64_t				XINT64;
	typedef	uint64_t			XBIGINT;
	typedef double				XLDOUBLE; 

	typedef char*				LPSTR;
	typedef const char*			LPCSTR;
	typedef wchar_t*			LPWSTR;
	typedef const wchar_t*      LPCWSTR;
	typedef const void*			LPCVOID;
	typedef void*				LPVOID;
	typedef uint8_t				BOOL;
	
	typedef uint32_t			__time32_t;

	#define FALSE				0
	#define TRUE				1
#endif

# if (defined(__GNUC__) && __GNUC__ >= 3) || ( defined(_MSC_VER) && _MSC_VER >= 2100)
	typedef uint8_t				uint8;
	typedef int8_t				int8;
	typedef uint16_t			uint16;
	typedef int16_t				int16;
	typedef uint32_t			uint32;
	typedef int32_t				int32;
	typedef uint64_t			uint64;
	typedef int64_t				int64;
#else
	typedef unsigned char		uint8;
	typedef signed char			int8;
	typedef unsigned __int16	uint16;
	typedef signed __int16		int16;
	typedef unsigned __int32	uint32;
	typedef signed __int32		int32;
	typedef unsigned __int64	uint64;
	typedef signed __int64		int64;
#endif

#if (defined(__GNUC__))

	typedef char			TCHAR;

#ifndef FILETIME
	typedef struct _FILETIME
	{
		XDWORD	dwLowDateTime;
		XDWORD	dwHighDateTime;
	}FILETIME, *PFILETIME, *LPFILETIME;
#endif

	typedef struct _SYSTEMTIME
	{
		XWORD	wYear;
		XWORD	wMonth;
		XWORD	wDayOfWeek;
		XWORD	wDay;
		XWORD	wHour;
		XWORD	wMinute;
		XWORD	wSecond;
		XWORD	wMilliseconds;
	}SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif


#define MAX_TALK_MSG_LENGTH			256
#define MAX_NAME_LENGTH				64
#define MAX_FRIEND_SIZE				500
#define MAX_GROUP_MEMBER_SIZE		200
#define MAX_GROUP_SIZE				20
#define MAX_DATA_SIZE				512*1024
#define MAX_CHACKSUM_SIZE			32

#pragma pack(push,1)

# if (defined(__GNUC__) && __GNUC__ >= 3) || ( defined(_MSC_VER) && _MSC_VER >= 2100)
typedef struct tagProtocolHead
{
	__time32_t	time_check;		//时间校验
	XDWORD	req_ans_command;	//req/ans command id
	XDWORD	source_size;		//source size(no compress)
	XDWORD	package_size;		//package size,if no compress,this must be 0
	XDWORD	self_param;			//HWND(x86)or other
}protocol_head, *pprotocol_head;
#endif

enum MsgType
{
	Chat_Req = 1,
	Chat_Res = 2,
	Login_Req = 3,
	Login_Res = 4,
	Qurey_Msg_Req = 5,
	Qurey_Msg_Res = 6,
	Qurey_Index_Req = 7,
	Qurey_Index_Res = 8,
	Register_Req = 9,
	Register_Ans = 10,
	LoadUserInf_Req = 11,
	LoadUserInf_Ans = 12,
	LoadFriendList_Req = 13,
	LoadFriendList_Ans = 14,
	LoadGroupList_Req = 15,
	LoadGroupList_Ans = 16,
	AddFriend_Req = 17,
	AddFriend_Ans = 18,
	AlterFriendInf_Req = 19,
	AlterFriendInf_Ans = 20,
	AlterUserInf_Req = 21,
	AlterUserInf_Ans = 22,
	QueryUserPubInf_Req = 23,
	QueryUserPubInf_Ans = 24,
	Online_Notify = 25,
	Offline_Notify = 26,			//废弃
	DownLoadFile_Req = 27, 
	DownLoadFile_Ans = 28, 
	ReceiveFile_Ack = 29,
	UpdateUserInf_Req = 30,
	UpdateUserInf_Ans = 31,
	Heartbeat_Req = 32,
	Heartbeat_Ans = 33,
	OfflineMsgInf_Notify=34,
	TalkMsg_Pull=35,
	ServerTime_Req = 36,
	ServerTime_Ans = 37,
	UpFileInfo_Req = 39, 
	UpFileInfo_Ans = 40, 
	Msg_Post = 41,
	ConnectServer_Req = 42,
	ConnectServer_Ans = 43,


	FriendOperation = 44,		//对“好友”进行操作
	n_ReqSysMemberInfo = 45,
	n_AnsSysMemberInfo = 46,
	n_ReqSysMemberInfoList = 47,
	n_AnsSysMemberInfoList = 48,
	n_ReqSysGroupInfo = 49,
	n_AnsSysGroupInfo = 50,
	n_ReqSysGroupInfoList = 51,
	n_AnsSysGroupInfoList = 52,
	n_ReqSysGTalkInfoList = 53,
	n_AnsSysGTalkInfoList = 54,
	n_ReqJoinGTalk = 55,
	n_AnsJoinGTalk = 56,
	n_QuitGTalk = 57,
	n_ReqSysTargetInfo = 59,
	n_AnsSysTargetInfo = 60,
	n_ReqSysTargetInfoList = 61,
	n_AnsSysTargetInfoList = 62,

	// Protobuf标识
	ProtobufMsg = 1002,

	// 服务器内部消息
	Server_Begin=30000,
};

const int g_Proto = 1;

enum	//所有错误信息定义
{
	error_ok = 0,				//没有错误发生

	error_username = 1,		//帐号不存在,请重新输入
	error_password,			//密码错误,请重新输入
	error_netcard,			//网卡绑定错误,请联系管理员
	error_expiration,		//帐号已过期,请联系管理员
	error_disabled,			//帐号被禁用,请联系管理员
	error_database,			//数据库操作失败
	error_access,			//权限不够,请联系管理员
	error_fileread,			//文件读取失败,请稍候重试
	error_system,			//系统异常,请联系管理员
	error_nodata,			//没有数据需要传输
	error_remotesrv,		//远程服务未启动,请联系管理员
	error_version,			//版本错误,系统不支持
	error_netword,			//网络通讯失败
	error_filewrite,		//文件写入失败
	error_vdalrun,			//代码编译/执行失败

	// add by CDY 2015-08-13
	error_registered,  // 已注册
	error_invalidusername, // 无效用户名
	error_exists, // 已存在
	error_fail,
	error_max,
};

struct Msg
{
	Msg()
	{
		memset(this, 0, sizeof(Msg));
	}
	protocol_head header;
	XBIGINT reserve1;
	XBIGINT reserve2;
};

#define MULITYTALK_FLAG 0x01
#define IsMulityTalk(x) (((x) & MULITYTALK_FLAG) != 0)
#define MarkMulityTalk(x) ((x) |= MULITYTALK_FLAG)
struct tagTalkMsg : public Msg
{
	tagTalkMsg()
	{
		uTargetID = 0;
		header.req_ans_command = Chat_Req;
		bMsgFlag = 0;
	}
	XDWORD uSenderID;
	XDWORD uTargetID;
	XDWORD uMsgID;
	XBYTE  bMsgFlag;
	char   szData[1];
};

struct tagAnsTalkMsg : public Msg
{
	tagAnsTalkMsg()
	{
		uTargetID = 0;
		header.req_ans_command = Chat_Res;
		header.source_size = sizeof(tagAnsTalkMsg)-sizeof(header);
		header.package_size = 0;
		uSenderID = 0;
	}

	XDWORD uSenderID;
	XDWORD uTargetID;
	XDWORD uMsgid;
	XBYTE  bMsgFlag;
};

struct tagMsgNotifyInfo
{
	XBYTE  bMsgFlag;
	XDWORD uTargetID;
	XDWORD uMsgid;
};

//根据目标ID和消息ID拉消息
struct tagPullQueryTalkMsg : public Msg
{
	tagPullQueryTalkMsg()
	{
		uTargetID = 0;
		bMsgFlag = 0;
		uMaxCount = 5;
		header.req_ans_command = TalkMsg_Pull;
		header.source_size = sizeof(tagPullQueryTalkMsg)-sizeof(header);
	}

	XBYTE  bMsgFlag;
	XDWORD uTargetID;
	XDWORD uMsgid;
	XDWORD uMaxCount;
};


struct tagTalkMsgInfNotify : public Msg
{
	tagTalkMsgInfNotify()
	{
		uMsgNotifySize = 0;
		header.req_ans_command = OfflineMsgInf_Notify;
		header.source_size = sizeof(tagTalkMsgInfNotify)-sizeof(header);
	}

	uint16 uMsgNotifySize;
	tagMsgNotifyInfo szMsgNotify[1];
};

//struct tagAnsQueryTalkMsg : public Msg
//{
//	tagAnsQueryTalkMsg()
//	{
//		uTargetID = 0;
//		header.req_ans_command = Chat_Res;
//		header.source_size = sizeof(tagAnsQueryTalkMsg)-sizeof(header);
//		header.package_size = 0;
//		uSenderID = 0;
//	}
//
//	XDWORD uSenderID;
//	XDWORD uTargetID;
//	XDWORD uMsgid;
//	XBYTE  bMsgFlag;
//};

#define MAX_EMAIL_LENGTH 48
#define MAX_SHORT_NAME_LENGTH 32
#define MAX_BUF_SIZE 512
struct tagUserInf
{
	XDWORD		nFace;				// 头像
	XDWORD		nGender;			// 性别
	XDWORD		nShengXiao;			// 生肖
	XDWORD		nConstel;			// 星座
	XDWORD		nBlood;				// 血型
	XDWORD		nBirthday;			// 生日

	char		szCountry[MAX_SHORT_NAME_LENGTH];	// 国家
	char		szProvince[MAX_SHORT_NAME_LENGTH];	// 省份
	char		szCity[MAX_SHORT_NAME_LENGTH];		// 城市
	char		szPhone[MAX_SHORT_NAME_LENGTH];		// 电话
	char		szMobile[MAX_SHORT_NAME_LENGTH];	// 手机
	char		szOccupation[MAX_SHORT_NAME_LENGTH];// 职业
	char		szCollege[MAX_SHORT_NAME_LENGTH];	// 毕业院校
	char		szEmail[MAX_EMAIL_LENGTH];			// 邮箱
	char		szHomepage[MAX_NAME_LENGTH];		// 个人主页
	char		szSigature[MAX_TALK_MSG_LENGTH];	// 个性签名
	char		szPersonal[MAX_BUF_SIZE];			// 个人说明
	//char        szCustomFace[MAX_PATH];				// 自定义头像名
};


struct tagReqUserLogon : public Msg
{
	tagReqUserLogon()
	{
		memset(this, 0, sizeof(tagReqUserLogon));
		header.req_ans_command = Login_Req;
		header.source_size = sizeof(tagReqUserLogon)-sizeof(header);
		header.package_size = 0;
	}
	char szAccountNo[MAX_NAME_LENGTH];
	char szPasswd[MAX_NAME_LENGTH];
	XBYTE bFlags; 
};

struct tagAnsUserLogon : public Msg
{
	tagAnsUserLogon()
	{
		memset(this, 0, sizeof(tagAnsUserLogon));
		header.req_ans_command = Login_Res;
		header.source_size = sizeof(tagAnsUserLogon)-sizeof(header);
		header.package_size = 0;
	}
	XDWORD uAccountID;
	XDWORD uAnsType;
	char szNickName[MAX_NAME_LENGTH];		//新版服务器这个字段返回空，要在加载用户信息协议里面去获取昵称信息
	char szAccountNo[MAX_NAME_LENGTH];
};

struct tagReqUserRegister : public Msg
{
	tagReqUserRegister()
	{
		memset(this, 0, sizeof(tagReqUserRegister));
		header.req_ans_command = Register_Req;
		header.source_size = sizeof(tagReqUserRegister)-sizeof(header);
		header.package_size = 0;
	}
	char szAccountNo[MAX_NAME_LENGTH];
	char szNickName[MAX_NAME_LENGTH];
	char szPasswd[MAX_NAME_LENGTH];
};

struct tagAnsUserRegister : public Msg
{
	tagAnsUserRegister()
	{
		memset(this, 0, sizeof(tagAnsUserRegister));
		header.req_ans_command = Register_Ans;
		header.source_size = sizeof(tagAnsUserRegister)-sizeof(header);
		header.package_size = 0;
	}
	XDWORD uRegisterType;
	char szAccountNo[MAX_NAME_LENGTH];
};

const XDWORD const_Online = 0x00;
const XDWORD const_Offline = 0x01;

struct tagFriend
{
    XDWORD uAccountID;
	XDWORD uMsgid;
	XBYTE bState;
	char szAccountNo[MAX_NAME_LENGTH];
	char szNickName[MAX_NAME_LENGTH];
};

struct tagMember
{
    XDWORD uAccountID;
	XDWORD uMsgid;
	char szAccountNo[MAX_NAME_LENGTH];
	char szNickName[MAX_NAME_LENGTH];
	XBYTE bRight;
	XBYTE bState;
};

struct tagGroup
{
    tagGroup()
    {
        uMemberSize = 0;
		memset(szMember, 0 ,sizeof(szMember));
		uGroupID = 0;
    }

	XDWORD uGroupID;
	uint16 uMemberSize;
	tagMember szMember[MAX_GROUP_MEMBER_SIZE];
};

struct tagRecordMsg
{
	XDWORD uSenderID;
};

struct tagReqUserInf : public Msg
{
	tagReqUserInf()
	{
		memset(this, 0, sizeof(tagReqUserInf));
		header.req_ans_command = LoadUserInf_Req;
		header.source_size = sizeof(tagReqUserInf)-sizeof(header);
		header.package_size = 0;
	};
};

struct tagAnsUserInf : public Msg
{
	tagAnsUserInf()
	{
		memset(this, 0, sizeof(tagAnsUserInf));
		header.req_ans_command = LoadUserInf_Ans;
		header.source_size = sizeof(tagAnsUserInf)-sizeof(header);
		header.package_size = 0;
		uFriendSize = 0;
		memset(szFriend, 0 ,sizeof(szFriend));
	}
	XDWORD uAccountID;
	char szAccountNo[MAX_NAME_LENGTH];
	char szNickName[MAX_NAME_LENGTH];
	tagUserInf PersonInf;
	uint16 uFriendSize;
	tagFriend szFriend[MAX_FRIEND_SIZE];
};

struct tagReqGroupList : public Msg
{
	tagReqGroupList()
	{
		memset(this, 0, sizeof(tagReqGroupList));
		header.req_ans_command = LoadGroupList_Req;
		header.source_size = sizeof(tagReqGroupList)-sizeof(header);
		header.package_size = 0;
	};
};

struct tagAnsGroupList : public Msg
{
	tagAnsGroupList()
	{
		memset(this, 0, sizeof(tagAnsGroupList));
		header.req_ans_command = LoadGroupList_Ans;
		header.source_size = sizeof(tagAnsGroupList)-sizeof(header);
		header.package_size = 0;
		uGroupSize = 0;
	}
	uint16 uGroupSize;
	tagGroup szGroup[MAX_GROUP_SIZE];
};

//通过账户查找用户ID请求
struct tagReqQueryUserPubInf : public Msg
{
	static const XDWORD const_FindTypeAccountNo = 0x01;
	static const XDWORD const_FindTypeAccountName = 0x02;
	tagReqQueryUserPubInf()
	{
		memset(this, 0, sizeof(tagReqQueryUserPubInf));
		header.req_ans_command = QueryUserPubInf_Req;
		header.source_size = sizeof(tagReqQueryUserPubInf)-sizeof(header);
		header.package_size = 0;
	};
	XDWORD uFindType;
	char szAccountNo[MAX_NAME_LENGTH];
	char szNickName[MAX_NAME_LENGTH];
};

struct tagAnsQueryUserPubInf : public Msg
{
	tagAnsQueryUserPubInf()
	{
		memset(this, 0, sizeof(tagAnsQueryUserPubInf));
		header.req_ans_command = QueryUserPubInf_Ans;
		header.source_size = sizeof(tagAnsQueryUserPubInf)-sizeof(header);
		header.package_size = 0;
	};
	uint16 uFriendSize;
	tagFriend szFriend[MAX_FRIEND_SIZE];
};

//BEGIN:旧的添加好友的逻辑
struct tagReqAddFriend : public Msg
{
	tagReqAddFriend()
	{
		memset(this, 0, sizeof(tagReqAddFriend));
		header.req_ans_command = AddFriend_Req;
		header.source_size = sizeof(tagReqAddFriend)-sizeof(header);
		header.package_size = 0;
	};
	XDWORD uAccountID;
};

//struct tagAnsAddFriend : public Msg
//{
//	tagAnsAddFriend()
//	{
//		memset(this, 0, sizeof(tagAnsAddFriend));
//		header.req_ans_command = AddFriend_Ans;
//		header.source_size = sizeof(tagAnsAddFriend)-sizeof(header);
//		header.package_size = 0;
//	};
//	XBYTE bFlag;
//	tagFriend stFriend;
//};
//END:旧的添加好友的逻辑

//BEGIN:新的好友操作逻辑

enum AddFriend_cmd{

	Apply = 0,// 申请

	Agree = 2,// 同意

	Refuse = 4, // 拒绝

	Delete = 6, // 删除
};

struct tagNewReqAddFriend : public tagReqAddFriend
{
	tagNewReqAddFriend()
	{
		memset(this, 0, sizeof(tagNewReqAddFriend));
		header.req_ans_command = AddFriend_Req;
		header.source_size = sizeof(tagNewReqAddFriend)-sizeof(header);
		header.package_size = 0;
	};
	uint8	nCmd;
};

struct tagAnsAddFriend : public Msg
{
	tagAnsAddFriend()
	{
		memset(this, 0, sizeof(tagAnsAddFriend));
		header.req_ans_command = AddFriend_Ans;
		header.source_size = sizeof(tagAnsAddFriend)-sizeof(header);
		header.package_size = 0;
	};
	XBYTE bFlag;		//添加好友的结果,如error_ok
	tagFriend stFriend;
	uint8	 nCmd;
};

//END:新的好友操作逻辑

//上线或下线通知
struct tagNoteOnline : public Msg
{
	tagNoteOnline()
	{
		memset(this, 0, sizeof(tagNoteOnline));
		header.req_ans_command = Online_Notify;
		header.source_size = sizeof(tagNoteOnline)-sizeof(header);
		header.package_size = 0;
	};
	XDWORD uAccountID;
	XBYTE  bFlags;			//下线会填0
};

//struct tagNoteOffline : public Msg
//{
//	tagNoteOffline()
//	{
//		memset(this, 0, sizeof(tagNoteOffline));
//		header.req_ans_command = Offline_Notify;
//		header.source_size = sizeof(tagNoteOffline)-sizeof(header);
//		header.package_size = 0;
//	};
//	XDWORD uAccountID;
//};

//上传文件步骤：
//1  tagReqUpFileInfo
//2  tagReqDownLoadFile
//3  tagAnsDownLoadFile 文件未传完 执行 2 否则下一步
//4  tagAnsUpFileInfo 
struct tagReqUpFileInfo : public Msg
{
	tagReqUpFileInfo()
	{
		memset(this, 0, sizeof(tagReqUpFileInfo));
		header.req_ans_command = UpFileInfo_Req;
		header.source_size = sizeof(tagReqUpFileInfo)-sizeof(header);
		header.package_size = 0;
	};
	
	char    cflname[256];	// 文件名(相对路径)
	char    checksum[MAX_CHACKSUM_SIZE + 1];
	XINT32	downsize;		//流量
	XINT32	filesize;		//客户端本地的文件大写
};

struct tagAnsUpFileInfo : public Msg
{
	tagAnsUpFileInfo()
	{
		memset(this, 0, sizeof(tagAnsUpFileInfo));
		header.req_ans_command = UpFileInfo_Ans;
		header.source_size = sizeof(tagAnsUpFileInfo)-sizeof(header);
		header.package_size = 0;
	};
	XDWORD	error;			//必须放第一位!
	char    cflname[256];	// 文件名(相对路径)
	XINT32	filesize;		// 上传服务的文件大小
};

struct tagReqDownLoadFile : public Msg
{
	tagReqDownLoadFile()
	{
		memset(this, 0, sizeof(tagReqDownLoadFile));
		header.req_ans_command = DownLoadFile_Req;
		header.source_size = sizeof(tagReqDownLoadFile)-sizeof(header);
		header.package_size = 0;
	};
	
	char	cflname[256];	// 文件名(相对路径)
	XINT32	offset;			//偏移
	XINT32	downsize;		//流量（为每次请求下载的大小）
	//如果客户端本地的文件时间/大小与服务器一致,则认为数据未发生变更,不用传输
	XINT32	localsize;		//客户端本地的文件大写
	XINT32	localtime;		//客户端本地的文件最后修改时间
	//版本号
	XBYTE	reqVersion;
};


struct tagAnsDownLoadFile : public Msg
{

	tagAnsDownLoadFile()
	{
		memset(this, 0, sizeof(tagAnsDownLoadFile));
		header.req_ans_command = DownLoadFile_Ans;
		header.source_size = sizeof(tagAnsDownLoadFile);
		header.package_size = 0;
		error = 0;
		filesize = 0;
	};
	XDWORD	error;		//必须放第一位!
	XINT32	filesize;	//文件总长(注意:不支持大文件!)
	XINT32	offset;		//偏移
	XINT32	downsize;	//流量
	__time32_t	tmmodified;	//最后修改时间
	char	reserved[16];//保留
	char	buffer[1];	//内容（当前协议包中文件内容字节数等于header.source_size加上协议头大小并减去tagAnsDownLoadFile结构大小）
};

struct tagAckReceiveFile : public Msg
{
	tagAckReceiveFile()
	{
		memset(this, 0, sizeof(tagAckReceiveFile));
		header.req_ans_command = DownLoadFile_Req;
		header.source_size = sizeof(tagAckReceiveFile);
		header.package_size = 0;
		uBeginPos = 0;
		uEndPos = 0;
	};
	char szFileName[MAX_NAME_LENGTH];
	uint32 uBeginPos;
	uint32 uEndPos;
};


struct tagReqUpdateUserInf : public Msg
{
	tagReqUpdateUserInf()
	{
		memset(this, 0, sizeof(tagReqUpdateUserInf));
		header.req_ans_command = UpdateUserInf_Req;
		header.source_size = sizeof(tagReqUpdateUserInf)-sizeof(header);
		header.package_size = 0;
	};
	char szNickName[MAX_NAME_LENGTH];
	tagUserInf PersonInf;
};

struct tagAnsUpdateUserInf : public Msg
{
	tagAnsUpdateUserInf()
	{
		memset(this, 0, sizeof(tagAnsUpdateUserInf));
		header.req_ans_command = UpdateUserInf_Ans;
		header.source_size = sizeof(tagAnsUpdateUserInf)-sizeof(header);
		header.package_size = 0;
	}
	XBYTE bFlag;
};

struct tagReqHeartbeat : public Msg
{
	tagReqHeartbeat()
	{
		memset(this, 0, sizeof(tagReqHeartbeat));
		header.req_ans_command = Heartbeat_Req;
		header.source_size = sizeof(tagReqHeartbeat)-sizeof(header);
		header.package_size = 0;
	};
};

struct tagAnsHeartbeat : public Msg
{
	tagAnsHeartbeat()
	{
		memset(this, 0, sizeof(tagAnsHeartbeat));
		header.req_ans_command = Heartbeat_Ans;
		header.source_size = sizeof(tagAnsHeartbeat)-sizeof(header);
		header.package_size = 0;
	}
};


//发在线文件（由服务器中转）
struct tagPostMsg : public Msg
{
	tagPostMsg()
	{
		memset(this, 0, sizeof(tagPostMsg));
		header.req_ans_command = Msg_Post;
		header.source_size = sizeof(tagPostMsg)-sizeof(header);
		header.package_size = 0;
	};
	XDWORD uTargetID;	 //发送方填写目标用户ID，服务器收到以后会改写成发送方ID并发送给目标方。
	XBYTE  bMsgFlag;
	char   buffer[1];	//内容
};

struct tagReqConnectServer : public Msg
{
	tagReqConnectServer()
	{
		memset(this, 0, sizeof(tagReqConnectServer));
		header.req_ans_command = ConnectServer_Req;
		header.source_size = sizeof(tagReqConnectServer)-sizeof(header);
		header.package_size = 0;
	};
	XDWORD uAccountID;
	XDWORD uSessionID;
};

struct tagAnsConnectServer : public Msg
{
	tagAnsConnectServer()
	{
		memset(this, 0, sizeof(tagAnsConnectServer));
		header.req_ans_command = ConnectServer_Ans;
		header.source_size = sizeof(tagAnsConnectServer)-sizeof(header);
		header.package_size = 0;
	};
	XDWORD	error;
};

//请求服务器时间
struct tagReqServerTime : public Msg
{
	tagReqServerTime()
	{
		memset(this, 0, sizeof(tagReqServerTime));
		header.req_ans_command = ServerTime_Req;
		header.source_size = sizeof(tagReqServerTime)-sizeof(header);
		header.package_size = 0;
	};
};

//服务器返回的时间结果
struct tagAnsServerTime : public Msg
{
	tagAnsServerTime()
	{
		memset(this, 0, sizeof(tagAnsServerTime));
		uServerTime = 0;
		header.req_ans_command = ServerTime_Ans;
		header.source_size = sizeof(tagAnsServerTime)-sizeof(header);
		header.package_size = 0;
	}
	
	uint64 uServerTime;
};

struct Bytes
{
	Bytes()
	:size(0)
	{
	}
	uint32 size;
	char	byte[1];	//内容
};

struct MemberInfo
{
	MemberInfo()
	:uRight(0)
	{

	}
    uint32 uRight; //权限
	Bytes selfparam;
};

struct TargetInfo
{
	uint32  nFace;
	char szNickName[MAX_NAME_LENGTH];
	char szAccountNo[MAX_NAME_LENGTH];
};

struct ReqSysTargetInfo
{
    uint32 uVersion; // 版本号
    uint32 uTargetID;
};

struct AnsSysTargetInfo
{
	uint32 uVersion; // 版本号
	uint32 uTargetID;
	TargetInfo tTargetInfo;
};

struct ReqSysTargetInfoList
{
	ReqSysTargetInfoList()
	:size(0)
	{}
	uint32 size;
	ReqSysTargetInfo tReqSysTargetInfo[1];
};

struct AnsSysTargetInfoList
{
	AnsSysTargetInfoList()
	:size(0){}
	uint32 size;
	AnsSysTargetInfo  tAnsSysTargetInfo[1];
};

struct ReqSysMemberInfo
{
    uint32 uVersion; // 版本号
    uint32 uTargetID;
};

struct AnsSysMemberInfo
{
	ReqSysMemberInfo tReq;
    MemberInfo tMemberInfos; 
};

struct ReqSysMemberInfoList
{
	ReqSysMemberInfoList()
	:size(0)
	{}
	uint32 size;
	ReqSysMemberInfo tReqSysMemberInfo[1];
};

struct AnsSysMemberInfoList
{
	AnsSysMemberInfoList()
	:size(0){}
	uint32 size;
	AnsSysMemberInfo  tAnsSysMemberInfo[1];
};

struct ReqSysGroupInfo
{
    uint32 uVersion ; // 版本号
    uint32 uTargetID; //  群组ID
    ReqSysMemberInfoList tReqSysMemberInfoList; // 成员列表
};

struct AnsSysGroupInfo
{
    uint32 uVersion ; // 版本号
    uint32 uTargetID ; //  群组ID
	AnsSysMemberInfoList tAnsSysMemberInfoList;
};

struct ReqSysGroupInfoList
{
	ReqSysGroupInfoList()
	:size(0)
	{}
	uint32 size;
    ReqSysGroupInfo tReqSysGroupInfo[1];
};

struct AnsSysGroupInfoList
{
	AnsSysGroupInfoList()
	:size(0)
	{}
	uint32 size;
    AnsSysGroupInfo tAnsSysGroupInfo[1];
};

struct ReqSysGTalkInfoList
{
    uint32 uVersion ; // 版本号
    ReqSysGroupInfoList tReqSysGroupInfoList; 
};

struct AnsSysGTalkInfoList
{
    uint32 uVersion ; // 版本号
    AnsSysGroupInfoList tAnsSysGroupInfoList;
};

struct ReqJoinGTalk
{
    uint32 uTargetID;
	uint32 uGTalkID;
	TargetInfo tTargetInfo; // 基本信息
};
struct AnsJoinGTalk
{
    uint32 uTargetID ;
	uint32 uGTalkID ;
	//TargetInfo tTargetInfo; // 基本信息
};

struct QuitGTalk
{
    uint32 uTargetID;
	uint32 uGTalkID;
};


#define StaticTypeSourceSize(T) (sizeof(T)-sizeof(protocol_head))


struct tagServerMsg : public Msg
{
	uint32 nMsgType;
	uint8 nCmdID;
	char bData[1];
	tagServerMsg(void)
	{
		header.req_ans_command = ProtobufMsg;
		header.package_size = 0;
		bData[0] = 0;
		nCmdID = 0;
	}
	uint32 data_lenghs(void) const
	{
		return (header.source_size - (sizeof(tagServerMsg)-sizeof(header)));
	}
	void set_length(uint32 length)
	{
		header.source_size = length + (sizeof(tagServerMsg)-sizeof(header));
	}
};

#pragma pack(pop)
