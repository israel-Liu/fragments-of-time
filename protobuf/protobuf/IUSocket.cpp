#include <iostream>
#include "IUSocket.h"
#include "Utils.h"

CIUSocket::CIUSocket() : m_strServer(_T("iu.zealink.com"))
{
	m_hSocket = INVALID_SOCKET;
	m_nPort = 35251;
	m_bConnected = FALSE;
}

CIUSocket::~CIUSocket()
{

}

void CIUSocket::SetServer(PCTSTR lpszServer)
{
	m_strServer = lpszServer;
}

void CIUSocket::SetPort(long nPort)
{
	m_nPort = nPort;
}

BOOL CIUSocket::Connect()
{
	if(IsConnected())
		return TRUE;
	Close();

	// Initialize WinSock2.2 DLL
	// low word = major, highword = minor
	WSADATA wsaData = {0};
	WORD wVer = MAKEWORD(2,2);
	int nRet = WSAStartup( wVer, &wsaData );

	if( nRet == SOCKET_ERROR ) {
		std::cout << "Failed to init Winsock library" << std::endl;
		return -1;
	}

	std::cout << "Opening connection to server" << std::endl;

	m_hSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if(m_hSocket == INVALID_SOCKET)
	{
		int nSocErr = WSAGetLastError();
		return FALSE;
	}

	long tmSend = 3*1000L;
	long tmRecv = 3*1000L;
	long noDelay = 1;
	setsockopt(m_hSocket, IPPROTO_TCP, TCP_NODELAY,(LPSTR)&noDelay, sizeof(long));
	setsockopt(m_hSocket, SOL_SOCKET,  SO_SNDTIMEO,(LPSTR)&tmSend, sizeof(long));
	setsockopt(m_hSocket, SOL_SOCKET,  SO_RCVTIMEO,(LPSTR)&tmRecv, sizeof(long));

	struct sockaddr_in addrSrv = {0}; 
	struct hostent* pHostent = NULL;
	unsigned int addr = 0;
	
	CStringA strServer;
	UnicodeToAnsi(m_strServer, strServer.GetBuffer(64), 64);
	strServer.ReleaseBuffer();
	if((addrSrv.sin_addr.s_addr=inet_addr(strServer)) == INADDR_NONE)
	{
		pHostent = ::gethostbyname(strServer) ;
		if (!pHostent) 
			return FALSE;
		else
			addrSrv.sin_addr.s_addr = *((unsigned long*)pHostent->h_addr);
	}

	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons((u_short)m_nPort); 
	if(::connect(m_hSocket, (struct sockaddr*)&addrSrv, sizeof(addrSrv)) == SOCKET_ERROR)
		return FALSE;


	m_bConnected = TRUE;

	return TRUE;
}

BOOL CIUSocket::CheckReceivedData()
{
	if(!m_bConnected && !Connect())
		return FALSE;
	
	fd_set readset;
	FD_ZERO(&readset);
	FD_SET(m_hSocket, &readset);

	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 500;
	
	long nRet = ::select(m_hSocket+1, &readset, NULL, NULL, &timeout);
	if(nRet == 1)
		return TRUE;
	else if(nRet == SOCKET_ERROR)		//一旦出现错误，立即关闭Socket
	{
		Close();
	}

	return FALSE;
}

BOOL CIUSocket::Send(const char* pBufferBuf, long nSize, BOOL bOnFileSocket/*=FALSE*/)
{
	//assert(pBufferBuf!=NULL && nSize>0);
	//如果未连接则重连，重连也失败则返回FALSE
	if(!m_bConnected && !Connect())
		return FALSE;

	int nSentBytes = 0;
	int nRet = 0;
	const SOCKET& socket = m_hSocket;
	do 
	{
		nRet = ::send(socket, pBufferBuf+nSentBytes, nSize-nSentBytes, 0);
		if(nRet == SOCKET_ERROR)				//一旦出现错误就立刻关闭Socket
		{
			Close();
			return FALSE;
		}
		
		nSentBytes += nRet;
		
		if(nSentBytes>=nSize)
			break;

	}while (TRUE);

	return TRUE;
}


BOOL CIUSocket::Recv(char* pBuffer, long nSize, BOOL bOnFileSocket/*=FALSE*/)
{
	//assert(pBuffer!=NULL && nSize>0);

	if(!m_bConnected && !Connect())
		return FALSE;

	int nRet = 0;
	long nRecvBytes = 0;
	const SOCKET& socket = m_hSocket;
	do 
	{
		nRet = ::recv(socket, pBuffer+nRecvBytes, nSize-nRecvBytes, 0);
		if(nRet == SOCKET_ERROR)				//一旦出现错误就立刻关闭Socket
		{
			Close();
			return FALSE;
		}
		
		nRecvBytes += nRet;
		if(nRecvBytes >= nSize)
			break;

	} while (TRUE);


	return TRUE;
}

inline BOOL CIUSocket::IsConnected()
{
	return m_bConnected;
}

void CIUSocket::Close()
{
	if(m_hSocket == INVALID_SOCKET)
		return;
	
	::shutdown(m_hSocket, SD_BOTH);
	::closesocket(m_hSocket);
	m_hSocket = INVALID_SOCKET;

	m_bConnected = FALSE;
}
