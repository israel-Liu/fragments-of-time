
// HinataDlg.h : ͷ�ļ�
//

#pragma once
#include "HinataCtrl.h"

// CHinataDlg �Ի���
class CHinataDlg : public CDialog
{
// ����
public:
	CHinataDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HINATA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//˽�к���
private:
	BOOL InitTabCtrl();			// ��ʼ��Tab��

//˽�б���
private:
	CHinataTabCtrl	m_TabCtrl;
};
