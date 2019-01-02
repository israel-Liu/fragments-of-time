
// HinataWindow.cpp : 自定义应用程序的窗口类。
//

#include "HinataWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CHinataWindow::CHinataWindow(HWND hWnd) throw() :
	m_hWnd(hWnd)
{

}

CHinataWindow& CHinataWindow::operator = (HWND hWnd) throw()
{
	m_hWnd = hWnd;
	return *this;
}

CHinataWindow::~CHinataWindow()
{

}

BOOL CHinataWindow::CenterWindow(HWND hWndCenter) throw()
{
	RECT rcDlg;
	::GetWindowRect(m_hWnd, &rcDlg);
	long lDlgWidth = rcDlg.right - rcDlg.left;
	long lDlgHeight = rcDlg.bottom - rcDlg.top;
	RECT rcDesktop;
	::GetClientRect(hWndCenter, &rcDesktop);
	long xLeft = (rcDesktop.left + rcDesktop.right) / 2 - lDlgWidth / 2;									// 对话框初始化桌面居中
	long yTop = (rcDesktop.top + rcDesktop.bottom) / 2 - lDlgHeight / 2;									// 找到对话框在桌面的左上角
	::MoveWindow(m_hWnd, xLeft, yTop, lDlgWidth, lDlgHeight, FALSE);	

	return TRUE;
}