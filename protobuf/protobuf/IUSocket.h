#pragma once
#include <atlstr.h>
#include <WinSock2.h>
//����ͨ�Ų�ֻ�������ݴ���ͽ���
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
	BOOL    CheckReceivedData();							//�ж���ͨSocket���Ƿ��յ����ݣ��з���TRUE��û�з���FALSE
	BOOL	Send(const char* pBuffer, long nSize, BOOL bOnFileSocket=FALSE);
	BOOL	Recv(char* pBuffer, long nSize, BOOL bOnFileSocket=FALSE);

private:	
	SOCKET							m_hSocket;				//һ����;Socket
	CString							m_strServer;			//��������ַ

	long							m_nPort;
	long							m_nFilePort;
	BOOL							m_bConnected;
	BOOL							m_bConnectedOnFileSocket;
};