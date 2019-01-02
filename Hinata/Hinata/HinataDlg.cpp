
// HinataDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Hinata.h"
#include "HinataDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHinataDlg �Ի���



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


// CHinataDlg ��Ϣ�������

BOOL CHinataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	long lDlgWidth = 820;
	long lDlgHeight = 510;
	RECT rcDesktop;
	::GetClientRect(::GetDesktopWindow(), &rcDesktop);
	long xLeft = (rcDesktop.left + rcDesktop.right) / 2 - lDlgWidth / 2;									// �Ի����ʼ���������
	long yTop = (rcDesktop.top + rcDesktop.bottom) / 2 - lDlgHeight / 2;									// �ҵ��Ի�������������Ͻ�
	::MoveWindow(m_hWnd, xLeft, yTop, lDlgWidth, lDlgHeight, FALSE);									
	SetIcon(m_hIcon, TRUE);																					// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);																				// ����Сͼ��
																											
	InitTabCtrl();																							// ��ʼ��Tab��

	return TRUE;																							// ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
// �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
// �⽫�ɿ���Զ���ɡ�

void CHinataDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	CRect rcTabCtrl(0, 100/*Ԥ����ͷ����˺���Ϣ*/, nWidth, rcClient.bottom);
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