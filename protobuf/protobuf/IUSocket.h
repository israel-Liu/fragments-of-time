#pragma once
#include <atlstr.h>
#include <WinSock2.h>
//网络通信层只负责数据传输和接收
class CIUSocket
{
public:
	CIUSocket(void);
	~CIUSocket(void);
	
	void	SetServer(PCTSTR lpszServer);
	void	SetPort(long nPort);
	void	Close();

	BOOL	Connect();
	BOOL	IsConnected();
	BOOL    CheckReceivedData();							//判断普通Socket上是否收到数据，有返回TRUE，没有返回FALSE
	BOOL	Send(const char* pBuffer, long nSize, BOOL bOnFileSocket=FALSE);
	BOOL	Recv(char* pBuffer, long nSize, BOOL bOnFileSocket=FALSE);

private:	
	SOCKET							m_hSocket;				//一般用途Socket
	CString							m_strServer;			//服务器地址

	long							m_nPort;
	long							m_nFilePort;
	BOOL							m_bConnected;
	BOOL							m_bConnectedOnFileSocket;
};