
// HinataTabCtrl.cpp : 自定义应用程序的Tab页。
//

#include "HinataTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CHinataTabCtrlItem::CHinataTabCtrlItem(void)
{
	m_nID = 0;
	m_nWidth = m_nHeight = 0;
	m_nLeftWidth = m_nRightWidth = 0;
	m_nPadding = 0;
}

CHinataTabCtrlItem::~CHinataTabCtrlItem(void)
{
	
}

CHinataTabCtrl::CHinataTabCtrl()
{

}

CHinataTabCtrl::~CHinataTabCtrl()
{

}

BEGIN_MESSAGE_MAP(CHinataTabCtrl, CTabCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

long CHinataTabCtrl::AddItem(long nID)
{
	CHinataTabCtrlItem *pItem = new CHinataTabCtrlItem;
	if (NULL == pItem)
		return -1;
	pItem->m_nID = nID;
	m_arrItems.push_back(pItem);
	return m_arrItems.size() - 1;
}

CHinataTabCtrlItem * CHinataTabCtrl::GetItemByIndex(long nIndex)
{
	if (nIndex >= 0 && nIndex < (long)m_arrItems.size())
		return m_arrItems[nIndex];
	else
		return NULL;
}

void CHinataTabCtrl::SetItemSize(long nIndex, long nWidth, long nHeight, long nLeftWidth/* 0 */, long nRightWidth/* 0 */)
{
	CHinataTabCtrlItem * pItem = GetItemByIndex(nIndex);
	if (pItem != NULL)
	{
		pItem->m_nWidth = nWidth;
		pItem->m_nHeight = nHeight;
		pItem->m_nLeftWidth = nLeftWidth;
		pItem->m_nRightWidth = nRightWidth;
	}
}

// 画图相关
void CHinataTabCtrl::OnPaint()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CPaintDC PaintDC(this);
	CDC MemDC();

	for (long i = 0; i < (long)m_arrItems.size(); ++i)
	{
		DrawItem(MemDC.m_hDC, i);
	}
}

void CHinataTabCtrl::DrawItem(HDC hDC, long nIndex)
{
	CHinataTabCtrlItem * pItem = GetItemByIndex(nIndex);
	if (NULL == pItem)
		return;

	CRect rcItem(0, 100, 170, 150);
	//GetItemRectByIndex(nIndex, rcItem);

	//if (m_nSelIndex == nIndex)
	//{
	//	if (lpItem->m_lpBgImgD != NULL && !lpItem->m_lpBgImgD->IsNull())
	//		lpItem->m_lpBgImgD->Draw2(hDC, rcItem);
	//	else if (m_lpItemBgImgD != NULL && !m_lpItemBgImgD->IsNull())
	//		m_lpItemBgImgD->Draw2(hDC, rcItem);
	//}
	//else if (m_nHoverIndex == nIndex)
	//{
	//	if (lpItem->m_lpBgImgH != NULL && !lpItem->m_lpBgImgH->IsNull())
	//		lpItem->m_lpBgImgH->Draw2(hDC, rcItem);
	//	else if (m_lpItemBgImgH != NULL && !m_lpItemBgImgH->IsNull())
	//		m_lpItemBgImgH->Draw2(hDC, rcItem);
	//}
	//else
	//{
	//	if (lpItem->m_lpBgImgN != NULL && !lpItem->m_lpBgImgN->IsNull())
	//		lpItem->m_lpBgImgN->Draw2(hDC, rcItem);
	//	else if (m_lpItemBgImgN != NULL && !m_lpItemBgImgN->IsNull())
	//		m_lpItemBgImgN->Draw2(hDC, rcItem);
	//}

	//CImageEx * lpIconImg;
	//if (m_nSelIndex == nIndex)
	//	lpIconImg = lpItem->m_lpSelIconImg;
	//else
	//	lpIconImg = lpItem->m_lpIconImg;

	//BOOL bHasText = FALSE;
	//if (lpItem->m_strText.GetLength() > 0)
	//	bHasText = TRUE;

	//BOOL bHasIcon = FALSE;
	//if (lpIconImg != NULL && !lpIconImg->IsNull())
	//	bHasIcon = TRUE;

	//if (bHasIcon && bHasText)	// 带图标和文字
	//{
	//	int cxIcon = lpIconImg->GetWidth();
	//	int cyIcon = lpIconImg->GetHeight();

	//	int nMode = ::SetBkMode(hDC, TRANSPARENT);
	//	HFONT hFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
	//	if (NULL == hFont)
	//		hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	//	HFONT hOldFont = (HFONT)::SelectObject(hDC, hFont);

	//	CRect rcText(0,0,0,0);	// 计算文字宽高
	//	::DrawText(hDC, lpItem->m_strText, lpItem->m_strText.GetLength(), &rcText, DT_SINGLELINE | DT_CALCRECT);

	//	int cx = cxIcon+1+rcText.Width();
	//	int cy = cyIcon;

	//	CRect rcCenter;
	//	CalcCenterRect(rcItem, cx, cy, rcCenter);

	//	CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left+cxIcon, rcCenter.bottom);
	//	lpIconImg->Draw2(hDC, rcIcon);

	//	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
	//	rcText = CRect(rcIcon.right+1, rcItem.top, rcIcon.right+1+rcText.Width(), rcItem.bottom);
	//	::DrawText(hDC, lpItem->m_strText, lpItem->m_strText.GetLength(), &rcText, nFormat);

	//	::SelectObject(hDC, hOldFont);
	//	::SetBkMode(hDC, nMode);
	//}
	//else if (bHasIcon)	// 仅图标
	//{
	//	int cxIcon = lpIconImg->GetWidth();
	//	int cyIcon = lpIconImg->GetHeight();

	//	CRect rcIcon;
	//	CalcCenterRect(rcItem, cxIcon, cyIcon, rcIcon);

	//	lpIconImg->Draw2(hDC, rcIcon);
	//}
	//else if (bHasText)	// 仅文字
	//{
		UINT nFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		long nMode = ::SetBkMode(hDC, TRANSPARENT);
		HFONT hFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
		if (NULL == hFont)
			hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		HFONT hOldFont = (HFONT)::SelectObject(hDC, hFont);
		::DrawText(hDC, (pItem->m_strText).begin(), pItem->m_strText.size(), &rcItem, nFormat);
		::SelectObject(hDC, hOldFont);
		::SetBkMode(hDC, nMode);
	//}

	//if (m_nSelIndex == nIndex)
	//{
	//	if (lpItem->m_dwStyle & STCI_STYLE_DROPDOWN)
	//	{
	//		CRect rcArrow(rcItem);
	//		rcArrow.left += lpItem->m_nLeftWidth;
	//		rcArrow.right = rcArrow.left + lpItem->m_nRightWidth;

	//		if (m_bPressArrow)
	//		{
	//			if (lpItem->m_lpArrowImgD != NULL && !lpItem->m_lpArrowImgD->IsNull())
	//				lpItem->m_lpArrowImgD->Draw2(hDC, rcArrow);
	//			else if (m_lpArrowImgD != NULL && !m_lpArrowImgD->IsNull())
	//				m_lpArrowImgD->Draw2(hDC, rcArrow);
	//		}
	//		else if (m_nHoverIndex == nIndex)
	//		{
	//			if (lpItem->m_lpArrowImgH != NULL && !lpItem->m_lpArrowImgH->IsNull())
	//				lpItem->m_lpArrowImgH->Draw2(hDC, rcArrow);
	//			else if (m_lpArrowImgH != NULL && !m_lpArrowImgH->IsNull())
	//				m_lpArrowImgH->Draw2(hDC, rcArrow);
	//		}
	//	}
	//}
}