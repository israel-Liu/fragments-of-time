
// HinataDlg.h : 头文件
//

#pragma once
#include "HinataCtrl.h"

// CHinataDlg 对话框
class CHinataDlg : public CDialog
{
// 构造
public:
	CHinataDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HINATA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//私有函数
private:
	BOOL InitTabCtrl();			// 初始化Tab栏

//私有变量
private:
	CHinataTabCtrl	m_TabCtrl;
};
