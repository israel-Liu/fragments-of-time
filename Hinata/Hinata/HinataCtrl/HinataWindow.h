#pragma once

#include <afxwin.h>

class CHinataWindow
{
public:
	CHinataWindow(HWND hWnd = NULL) throw();
	CHinataWindow& operator = (HWND hWnd) throw();
	virtual ~CHinataWindow();
	BOOL CenterWindow(HWND hWndCenter = NULL) throw();							// ���õ�ǰ�ؼ�����ĳһ���ھ���

private:
	HWND m_hWnd;
};