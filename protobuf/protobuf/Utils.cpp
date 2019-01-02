#include "Utils.h"

BOOL UnicodeToAnsi(const WCHAR * lpszUnicode, CHAR * lpszAnsi, int nLen)
{
	int nRet = ::WideCharToMultiByte(CP_ACP, 0, lpszUnicode, -1, lpszAnsi, nLen, NULL, NULL);
	return (0 == nRet) ? FALSE : TRUE;
}
