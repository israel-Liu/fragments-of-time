#include "IUSocket.h"
#include "proto.h"
int main(int argc, char* argv[])
{
	CIUSocket m_SocketClient;
	m_SocketClient.Connect();

	tms::LoginInfo  tReqLogin;
	tReqLogin.set_straccountno("18841159992");
	tReqLogin.set_strpasswd("18841159992");
	tReqLogin.set_uloginflags(2);

	int iObjectSize = tReqLogin.ByteSize();
	char *pChar = new char[(iObjectSize + sizeof(tagServerMsg))];
	tagServerMsg *pMsg = new (pChar)tagServerMsg();

	if (NULL == pMsg)
	{
		return 0;
	}

	if (tReqLogin.SerializePartialToArray(pMsg->bData, iObjectSize))
	{
		pMsg->header.source_size = iObjectSize + sizeof(tagServerMsg)-sizeof(pMsg->header);
	}
	else
	{
		pMsg->header.source_size = sizeof(tagServerMsg)-sizeof(pMsg->header);
	}
	pMsg->nMsgType = tms::n_LoginInfo;
	pMsg->header.self_param = 1;

	if(!m_SocketClient.Send((const char*)pMsg, pMsg->header.source_size + sizeof(pMsg->header)))
		return 0;

	while (m_SocketClient.CheckReceivedData())
	{
		// 接收信息
		tagServerMsg SerMsg;
		memset(&SerMsg, 0, sizeof(SerMsg));
		if (!m_SocketClient.Recv((char*)&SerMsg, sizeof(SerMsg), FALSE))
			return FALSE;

		switch (SerMsg.nMsgType)
		{
		case tms::n_AnsInfo:
		{
							   tms::AnsInfo tAnsInfo;
							   tAnsInfo.ParsePartialFromArray(SerMsg.bData, SerMsg.data_lenghs());
							   tms::cmd tCmd = tAnsInfo.tcmd();
							   switch (tCmd)
							   {
							   case tms::n_LoginInfo:
							   {
														if (tAnsInfo.uerror() == error_ok)
														{
															tAnsInfo.uaccountid();
															tAnsInfo.straccountno();
														}
														break;
							   }


							   default:
								   break;
							   }
							   break;
		}

		default:
			break;
		}
	} 

	return 0;
}