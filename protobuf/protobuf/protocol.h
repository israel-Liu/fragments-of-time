
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
	__time32_t	time_check;		//ʱ��У��
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
	Offline_Notify = 26,			//����
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


	FriendOperation = 44,		//�ԡ����ѡ����в���
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

	// Protobuf��ʶ
	ProtobufMsg = 1002,

	// �������ڲ���Ϣ
	Server_Begin=30000,
};

const int g_Proto = 1;

enum	//���д�����Ϣ����
{
	error_ok = 0,				//û�д�����

	error_username = 1,		//�ʺŲ�����,����������
	error_password,			//�������,����������
	error_netcard,			//�����󶨴���,����ϵ����Ա
	error_expiration,		//�ʺ��ѹ���,����ϵ����Ա
	error_disabled,			//�ʺű�����,����ϵ����Ա
	error_database,			//���ݿ����ʧ��
	error_access,			//Ȩ�޲���,����ϵ����Ա
	error_fileread,			//�ļ���ȡʧ��,���Ժ�����
	error_system,			//ϵͳ�쳣,����ϵ����Ա
	error_nodata,			//û��������Ҫ����
	error_remotesrv,		//Զ�̷���δ����,����ϵ����Ա
	error_version,			//�汾����,ϵͳ��֧��
	error_netword,			//����ͨѶʧ��
	error_filewrite,		//�ļ�д��ʧ��
	error_vdalrun,			//�������/ִ��ʧ��

	// add by CDY 2015-08-13
	error_registered,  // ��ע��
	error_invalidusername, // ��Ч�û���
	error_exists, // �Ѵ���
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

//����Ŀ��ID����ϢID����Ϣ
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
	XDWORD		nFace;				// ͷ��
	XDWORD		nGender;			// �Ա�
	XDWORD		nShengXiao;			// ��Ф
	XDWORD		nConstel;			// ����
	XDWORD		nBlood;				// Ѫ��
	XDWORD		nBirthday;			// ����

	char		szCountry[MAX_SHORT_NAME_LENGTH];	// ����
	char		szProvince[MAX_SHORT_NAME_LENGTH];	// ʡ��
	char		szCity[MAX_SHORT_NAME_LENGTH];		// ����
	char		szPhone[MAX_SHORT_NAME_LENGTH];		// �绰
	char		szMobile[MAX_SHORT_NAME_LENGTH];	// �ֻ�
	char		szOccupation[MAX_SHORT_NAME_LENGTH];// ְҵ
	char		szCollege[MAX_SHORT_NAME_LENGTH];	// ��ҵԺУ
	char		szEmail[MAX_EMAIL_LENGTH];			// ����
	char		szHomepage[MAX_NAME_LENGTH];		// ������ҳ
	char		szSigature[MAX_TALK_MSG_LENGTH];	// ����ǩ��
	char		szPersonal[MAX_BUF_SIZE];			// ����˵��
	//char        szCustomFace[MAX_PATH];				// �Զ���ͷ����
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
	char szNickName[MAX_NAME_LENGTH];		//�°����������ֶη��ؿգ�Ҫ�ڼ����û���ϢЭ������ȥ��ȡ�ǳ���Ϣ
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

//ͨ���˻������û�ID����
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

//BEGIN:�ɵ���Ӻ��ѵ��߼�
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
//END:�ɵ���Ӻ��ѵ��߼�

//BEGIN:�µĺ��Ѳ����߼�

enum AddFriend_cmd{

	Apply = 0,// ����

	Agree = 2,// ͬ��

	Refuse = 4, // �ܾ�

	Delete = 6, // ɾ��
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
	XBYTE bFlag;		//��Ӻ��ѵĽ��,��error_ok
	tagFriend stFriend;
	uint8	 nCmd;
};

//END:�µĺ��Ѳ����߼�

//���߻�����֪ͨ
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
	XBYTE  bFlags;			//���߻���0
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

//�ϴ��ļ����裺
//1  tagReqUpFileInfo
//2  tagReqDownLoadFile
//3  tagAnsDownLoadFile �ļ�δ���� ִ�� 2 ������һ��
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
	
	char    cflname[256];	// �ļ���(���·��)
	char    checksum[MAX_CHACKSUM_SIZE + 1];
	XINT32	downsize;		//����
	XINT32	filesize;		//�ͻ��˱��ص��ļ���д
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
	XDWORD	error;			//����ŵ�һλ!
	char    cflname[256];	// �ļ���(���·��)
	XINT32	filesize;		// �ϴ�������ļ���С
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
	
	char	cflname[256];	// �ļ���(���·��)
	XINT32	offset;			//ƫ��
	XINT32	downsize;		//������Ϊÿ���������صĴ�С��
	//����ͻ��˱��ص��ļ�ʱ��/��С�������һ��,����Ϊ����δ�������,���ô���
	XINT32	localsize;		//�ͻ��˱��ص��ļ���д
	XINT32	localtime;		//�ͻ��˱��ص��ļ�����޸�ʱ��
	//�汾��
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
	XDWORD	error;		//����ŵ�һλ!
	XINT32	filesize;	//�ļ��ܳ�(ע��:��֧�ִ��ļ�!)
	XINT32	offset;		//ƫ��
	XINT32	downsize;	//����
	__time32_t	tmmodified;	//����޸�ʱ��
	char	reserved[16];//����
	char	buffer[1];	//���ݣ���ǰЭ������ļ������ֽ�������header.source_size����Э��ͷ��С����ȥtagAnsDownLoadFile�ṹ��С��
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


//�������ļ����ɷ�������ת��
struct tagPostMsg : public Msg
{
	tagPostMsg()
	{
		memset(this, 0, sizeof(tagPostMsg));
		header.req_ans_command = Msg_Post;
		header.source_size = sizeof(tagPostMsg)-sizeof(header);
		header.package_size = 0;
	};
	XDWORD uTargetID;	 //���ͷ���дĿ���û�ID���������յ��Ժ���д�ɷ��ͷ�ID�����͸�Ŀ�귽��
	XBYTE  bMsgFlag;
	char   buffer[1];	//����
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

//���������ʱ��
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

//���������ص�ʱ����
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
	char	byte[1];	//����
};

struct MemberInfo
{
	MemberInfo()
	:uRight(0)
	{

	}
    uint32 uRight; //Ȩ��
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
    uint32 uVersion; // �汾��
    uint32 uTargetID;
};

struct AnsSysTargetInfo
{
	uint32 uVersion; // �汾��
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
    uint32 uVersion; // �汾��
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
    uint32 uVersion ; // �汾��
    uint32 uTargetID; //  Ⱥ��ID
    ReqSysMemberInfoList tReqSysMemberInfoList; // ��Ա�б�
};

struct AnsSysGroupInfo
{
    uint32 uVersion ; // �汾��
    uint32 uTargetID ; //  Ⱥ��ID
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
    uint32 uVersion ; // �汾��
    ReqSysGroupInfoList tReqSysGroupInfoList; 
};

struct AnsSysGTalkInfoList
{
    uint32 uVersion ; // �汾��
    AnsSysGroupInfoList tAnsSysGroupInfoList;
};

struct ReqJoinGTalk
{
    uint32 uTargetID;
	uint32 uGTalkID;
	TargetInfo tTargetInfo; // ������Ϣ
};
struct AnsJoinGTalk
{
    uint32 uTargetID ;
	uint32 uGTalkID ;
	//TargetInfo tTargetInfo; // ������Ϣ
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
