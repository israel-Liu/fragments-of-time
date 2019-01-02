
// HinataWindow.cpp : �Զ���Ӧ�ó���Ĵ����ࡣ
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
	long xLeft = (rcDesktop.left + rcDesktop.right) / 2 - lDlgWidth / 2;									// �Ի����ʼ���������
	long yTop = (rcDesktop.top + rcDesktop.bottom) / 2 - lDlgHeight / 2;									// �ҵ��Ի�������������Ͻ�
	::MoveWindow(m_hWnd, xLeft, yTop, lDlgWidth, lDlgHeight, FALSE);	

	return TRUE;
}