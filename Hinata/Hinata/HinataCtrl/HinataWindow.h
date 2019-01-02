#pragma once

#include <afxwin.h>

class CHinataWindow
{
public:
	CHinataWindow(HWND hWnd = NULL) throw();
	CHinataWindow& operator = (HWND hWnd) throw();
	virtual ~CHinataWindow();
	BOOL CenterWindow(HWND hWndCenter = NULL) throw();							// 设置当前控件基于某一窗口剧中

private:
	HWND m_hWnd;
};