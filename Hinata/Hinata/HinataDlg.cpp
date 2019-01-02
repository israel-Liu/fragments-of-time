
// HinataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Hinata.h"
#include "HinataDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHinataDlg 对话框



CHinataDlg::CHinataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_HINATA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHinataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHinataDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CHinataDlg 消息处理程序

BOOL CHinataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	long lDlgWidth = 820;
	long lDlgHeight = 510;
	RECT rcDesktop;
	::GetClientRect(::GetDesktopWindow(), &rcDesktop);
	long xLeft = (rcDesktop.left + rcDesktop.right) / 2 - lDlgWidth / 2;									// 对话框初始化桌面居中
	long yTop = (rcDesktop.top + rcDesktop.bottom) / 2 - lDlgHeight / 2;									// 找到对话框在桌面的左上角
	::MoveWindow(m_hWnd, xLeft, yTop, lDlgWidth, lDlgHeight, FALSE);									
	SetIcon(m_hIcon, TRUE);																					// 设置大图标
	SetIcon(m_hIcon, FALSE);																				// 设置小图标
																											
	InitTabCtrl();																							// 初始化Tab栏

	return TRUE;																							// 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
// 来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
// 这将由框架自动完成。

void CHinataDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHinataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CHinataDlg::InitTabCtrl()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	long nWidth = 170;
	long nHeight = 50;
	CRect rcTabCtrl(0, 100/*预留给头像和账号信息*/, nWidth, rcClient.bottom);
	m_TabCtrl.CreateEx(NULL, WS_CHILD | WS_VISIBLE, rcTabCtrl, this, ID_TABCTRL_MAIN);
	long lIndex = 0;
	m_TabCtrl.AddItem(lIndex++);
	m_TabCtrl.SetItemSize(lIndex - 1, nWidth, nHeight, nHeight, nHeight);
	m_TabCtrl.AddItem(lIndex++);
	m_TabCtrl.SetItemSize(lIndex - 1, nWidth, nHeight, nHeight, nHeight);
	m_TabCtrl.AddItem(lIndex++);
	m_TabCtrl.SetItemSize(lIndex - 1, nWidth, nHeight, nHeight, nHeight);

	return TRUE;
}