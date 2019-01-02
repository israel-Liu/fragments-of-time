#pragma once

#include <afxcmn.h>
#include <string>
#include <vector>

class CHinataTabCtrlItem
{
public:
	CHinataTabCtrlItem(void);
	~CHinataTabCtrlItem(void);

public:
	long			m_nID;
	long			m_nWidth, m_nHeight;
	long			m_nLeftWidth, m_nRightWidth;
	long			m_nPadding;
	std::string		m_strText;
	std::string		m_strToolTipText;
};

class CHinataTabCtrl : public CTabCtrl
{
public:
	CHinataTabCtrl();
	virtual ~CHinataTabCtrl();

	long AddItem(long nID);
	void SetItemSize(long nIndex, long nWidth, long nHeight, long nLeftWidth = 0, long nRightWidth = 0);
	CHinataTabCtrlItem * GetItemByIndex(long nIndex);

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnPaint();
	void DrawItem(HDC hDC, long nIndex);

private:
	std::vector<CHinataTabCtrlItem *> m_arrItems;
};