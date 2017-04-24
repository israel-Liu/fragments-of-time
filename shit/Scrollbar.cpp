#include <windows.h>

// System metrics display structure

namespace {

struct
{
    int         index_;
    wchar_t*    szLabel_;
    wchar_t*    szDesc_;
} cArrSysMetrics[] = {
    SM_CXSCREEN, TEXT("SM_CXSCREEN"), TEXT("Screen width in pixels"),

    SM_CYSCREEN, TEXT("SM_CYSCREEN"), TEXT("Screen height in pixels"),

    SM_CXVSCROLL, TEXT("SM_CXVSCROLL"), TEXT("Vertical scroll width"),

    SM_CYHSCROLL, TEXT("SM_CYHSCROLL"), TEXT("Horizontal scroll height"),

    SM_CYCAPTION, TEXT("SM_CYCAPTION"), TEXT("Caption bar height"),

    SM_CXBORDER, TEXT("SM_CXBORDER"), TEXT("Window border width"),

    SM_CYBORDER, TEXT("SM_CYBORDER"), TEXT("Window border height"),

    SM_CXFIXEDFRAME, TEXT("SM_CXFIXEDFRAME"), TEXT("Dialog window frame width"),

    SM_CYFIXEDFRAME, TEXT("SM_CYFIXEDFRAME"), TEXT("Dialog window frame height"),

    SM_CYVTHUMB, TEXT("SM_CYVTHUMB"), TEXT("Vertical scroll thumb height"),

    SM_CXHTHUMB, TEXT("SM_CXHTHUMB"), TEXT("Horizontal scroll thumb width"),

    SM_CXICON, TEXT("SM_CXICON"), TEXT("Icon width"),

    SM_CYICON, TEXT("SM_CYICON"), TEXT("Icon height"),

    SM_CXCURSOR, TEXT("SM_CXCURSOR"), TEXT("Cursor width"),

    SM_CYCURSOR, TEXT("SM_CYCURSOR"), TEXT("Cursor height"),

    SM_CYMENU, TEXT("SM_CYMENU"), TEXT("Menu bar height"),

    SM_CXFULLSCREEN, TEXT("SM_CXFULLSCREEN"), TEXT("Full screen client area width"),

    SM_CYFULLSCREEN, TEXT("SM_CYFULLSCREEN"), TEXT("Full screen client area height"),

    SM_CYKANJIWINDOW, TEXT("SM_CYKANJIWINDOW"), TEXT("Kanji window height"),

    SM_MOUSEPRESENT, TEXT("SM_MOUSEPRESENT"), TEXT("Mouse present flag"),

    SM_CYVSCROLL, TEXT("SM_CYVSCROLL"), TEXT("Vertical scroll arrow height"),

    SM_CXHSCROLL, TEXT("SM_CXHSCROLL"), TEXT("Horizontal scroll arrow width"),

    SM_DEBUG, TEXT("SM_DEBUG"), TEXT("Debug version flag"),

    SM_SWAPBUTTON, TEXT("SM_SWAPBUTTON"), TEXT("Mouse buttons swapped flag"),

    SM_CXMIN, TEXT("SM_CXMIN"), TEXT("Minimum window width"),

    SM_CYMIN, TEXT("SM_CYMIN"), TEXT("Minimum window height"),

    SM_CXSIZE, TEXT("SM_CXSIZE"), TEXT("Min/Max/Close button width"),

    SM_CYSIZE, TEXT("SM_CYSIZE"), TEXT("Min/Max/Close button height"),

    SM_CXSIZEFRAME, TEXT("SM_CXSIZEFRAME"), TEXT("Window sizing frame width"),

    SM_CYSIZEFRAME, TEXT("SM_CYSIZEFRAME"), TEXT("Window sizing frame height"),

    SM_CXMINTRACK, TEXT("SM_CXMINTRACK"), TEXT("Minimum window tracking width"),

    SM_CYMINTRACK, TEXT("SM_CYMINTRACK"), TEXT("Minimum window tracking height"),

    SM_CXDOUBLECLK, TEXT("SM_CXDOUBLECLK"), TEXT("Double click x tolerance"),

    SM_CYDOUBLECLK, TEXT("SM_CYDOUBLECLK"), TEXT("Double click y tolerance"),

    SM_CXICONSPACING, TEXT("SM_CXICONSPACING"), TEXT("Horizontal icon spacing"),

    SM_CYICONSPACING, TEXT("SM_CYICONSPACING"), TEXT("Vertical icon spacing"),

    SM_MENUDROPALIGNMENT, TEXT("SM_MENUDROPALIGNMENT"), TEXT("Left or right menu drop"),

    SM_PENWINDOWS, TEXT("SM_PENWINDOWS"), TEXT("Pen extensions installed"),

    SM_DBCSENABLED, TEXT("SM_DBCSENABLED"), TEXT("Double-Byte Char Set enabled"),

    SM_CMOUSEBUTTONS, TEXT("SM_CMOUSEBUTTONS"), TEXT("Number of mouse buttons"),

    SM_SECURE, TEXT("SM_SECURE"), TEXT("Security present flag"),

    SM_CXEDGE, TEXT("SM_CXEDGE"), TEXT("3-D border width"),

    SM_CYEDGE, TEXT("SM_CYEDGE"), TEXT("3-D border height"),

    SM_CXMINSPACING, TEXT("SM_CXMINSPACING"), TEXT("Minimized window spacing width"),

    SM_CYMINSPACING, TEXT("SM_CYMINSPACING"), TEXT("Minimized window spacing height"),

    SM_CXSMICON, TEXT("SM_CXSMICON"), TEXT("Small icon width"),

    SM_CYSMICON, TEXT("SM_CYSMICON"), TEXT("Small icon height"),

    SM_CYSMCAPTION, TEXT("SM_CYSMCAPTION"), TEXT("Small caption height"),

    SM_CXSMSIZE, TEXT("SM_CXSMSIZE"), TEXT("Small caption button width"),

    SM_CYSMSIZE, TEXT("SM_CYSMSIZE"), TEXT("Small caption button height"),

    SM_CXMENUSIZE, TEXT("SM_CXMENUSIZE"), TEXT("Menu bar button width"),

    SM_CYMENUSIZE, TEXT("SM_CYMENUSIZE"), TEXT("Menu bar button height"),

    SM_ARRANGE, TEXT("SM_ARRANGE"), TEXT("How minimized windows arranged"),

    SM_CXMINIMIZED, TEXT("SM_CXMINIMIZED"), TEXT("Minimized window width"),

    SM_CYMINIMIZED, TEXT("SM_CYMINIMIZED"), TEXT("Minimized window height"),

    SM_CXMAXTRACK, TEXT("SM_CXMAXTRACK"), TEXT("Maximum draggable width"),

    SM_CYMAXTRACK, TEXT("SM_CYMAXTRACK"), TEXT("Maximum draggable height"),

    SM_CXMAXIMIZED, TEXT("SM_CXMAXIMIZED"), TEXT("Width of maximized window"),

    SM_CYMAXIMIZED, TEXT("SM_CYMAXIMIZED"), TEXT("Height of maximized window"),

    SM_NETWORK, TEXT("SM_NETWORK"), TEXT("Network present flag"),

    SM_CLEANBOOT, TEXT("SM_CLEANBOOT"), TEXT("How system was booted"),

    SM_CXDRAG, TEXT("SM_CXDRAG"), TEXT("Avoid drag x tolerance"),

    SM_CYDRAG, TEXT("SM_CYDRAG"), TEXT("Avoid drag y tolerance"),

    SM_SHOWSOUNDS, TEXT("SM_SHOWSOUNDS"), TEXT("Present sounds visually"),

    SM_CXMENUCHECK, TEXT("SM_CXMENUCHECK"), TEXT("Menu check-mark width"),

    SM_CYMENUCHECK, TEXT("SM_CYMENUCHECK"), TEXT("Menu check-mark height"),

    SM_SLOWMACHINE, TEXT("SM_SLOWMACHINE"), TEXT("Slow processor flag"),

    SM_MIDEASTENABLED, TEXT("SM_MIDEASTENABLED"), TEXT("Hebrew and Arabic enabled flag"),

    SM_MOUSEWHEELPRESENT, TEXT("SM_MOUSEWHEELPRESENT"), TEXT("Mouse wheel present flag"),

    SM_XVIRTUALSCREEN, TEXT("SM_XVIRTUALSCREEN"), TEXT("Virtual screen x origin"),

    SM_YVIRTUALSCREEN, TEXT("SM_YVIRTUALSCREEN"), TEXT("Virtual screen y origin"),

    SM_CXVIRTUALSCREEN, TEXT("SM_CXVIRTUALSCREEN"), TEXT("Virtual screen width"),

    SM_CYVIRTUALSCREEN, TEXT("SM_CYVIRTUALSCREEN"), TEXT("Virtual screen height"),

    SM_CMONITORS, TEXT("SM_CMONITORS"), TEXT("Number of monitors"),

    SM_SAMEDISPLAYFORMAT, TEXT("SM_SAMEDISPLAYFORMAT"), TEXT("Same color format flag")
};

const int NUM_LINES = static_cast<int>(sizeof(cArrSysMetrics) / sizeof(cArrSysMetrics[0]));

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"hinata_player";
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = nullptr;
    wndclass.hCursor = nullptr;
    wndclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wndclass.lpszMenuName = nullptr;
    wndclass.lpszClassName = szAppName;

    if (!::RegisterClass(&wndclass)) {
        ::MessageBox(nullptr, L"This program requires Windows NT!", szAppName, MB_ICONERROR);
        return -1;
    }

    HWND hwnd = ::CreateWindow(szAppName, szAppName,
                               WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               nullptr, nullptr, hInstance, nullptr);

    ::ShowWindow(hwnd, iCmdShow);
    ::UpdateWindow(hwnd);

    MSG msg;
    BOOL bRet;
    while (0 != (bRet = ::GetMessage(&msg, nullptr, 0, 0))) {
        if (-1 == bRet) {
            return -1;
        }

        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int cxChar, cxCaps, cyChar, cxClient, cyClient, iMaxWidth;
    int iVertPos, iHorzPos;
    SCROLLINFO si;

    switch (msg) {
    case WM_CREATE:
    {
        HDC hdc = ::GetDC(hwnd);
        TEXTMETRIC tm;
        ::GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
        cyChar = tm.tmHeight + tm.tmExternalLeading;
        ::ReleaseDC(hwnd, hdc);

        // Save the width of the three columns
        iMaxWidth = 40 * cxChar + 22 * cxCaps;

        return 0;
    }

    case WM_SIZE:
    {
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        // Set vertical scroll bar range and page size
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_PAGE;
        si.nMin = 0;
        si.nMax = NUM_LINES - 1;
        si.nPage = cyClient / cyChar;
        ::SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

        // Set horizontal scrool bar range and page size
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_PAGE;
        si.nMin = 0;
        si.nMax = 2 + iMaxWidth / cxChar;
        si.nPage = cxClient / cxChar;
        ::SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

        return 0;
    }

    case WM_VSCROLL:
    {
        // Get all the vertical scroll bar information
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        ::GetScrollInfo(hwnd, SB_VERT, &si);

        // Save the position for comparison later on
        iVertPos = si.nPos;

        switch (LOWORD(wParam)) {
        case SB_TOP:
        {
            si.nPos = si.nMin;
            break;
        }

        case SB_BOTTOM:
        {
            si.nPos = si.nMax;
            break;
        }

        case SB_LINEUP:
        {
            si.nPos -= 1;
            break;
        }

        case SB_LINEDOWN:
        {
            si.nPos += 1;
            break;
        }

        case SB_PAGEUP:
        {
            si.nPos -= si.nPage;
            break;
        }

        case SB_PAGEDOWN:
        {
            si.nPos += si.nPage;
            break;
        }

        case SB_THUMBTRACK:
        {
            si.nPos = si.nTrackPos;
            break;
        }

        default:
            break;
        }

        // Set the position and then retrieve it. Due to adjustments

        // by windows it may not be the same as the value set.

        si.fMask = SIF_POS;
        ::SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
        ::GetScrollInfo(hwnd, SB_VERT, &si);

        // If the position has changed, scroll the window and update it.
        if (si.nPos != iVertPos) {
            ::ScrollWindow(hwnd, 0, cyChar * (iVertPos - si.nPos), nullptr, nullptr);
            ::UpdateWindow(hwnd);
        }

        return 0;
    }

    case WM_HSCROLL:
    {
        // Get all the vertical scroll bar information
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;

        // Save the position for comparison later on
        ::GetScrollInfo(hwnd, SB_HORZ, &si);
        iHorzPos = si.nPos;

        switch (LOWORD(wParam)) {
        case SB_LINELEFT:
        {
            si.nPos -= 1;
            break;
        }

        case SB_LINERIGHT:
        {
            si.nPos += 1;
            break;
        }

        case SB_PAGELEFT:
        {
            si.nPos -= si.nPage;
            break;
        }

        case SB_PAGERIGHT:
        {
            si.nPos += si.nPage;
            break;
        }

        case SB_THUMBPOSITION:
        {
            si.nPos = si.nTrackPos;
            break;
        }

        default:
            break;
        }

        // Set the position and then retrieve it. Due to adjustments

        // by windows it may not be the same as the value set.

        si.fMask = SIF_POS;
        ::SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
        ::GetScrollInfo(hwnd, SB_HORZ, &si);

        // If the position has changed, scroll the window
        if (si.nPos != iHorzPos) {
            ::ScrollWindow(hwnd, cxChar * (iHorzPos - si.nPos), 0, nullptr, nullptr);
        }

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);

        // Get vertical scroll bar position
        si.cbSize = sizeof(si);
        si.fMask = SIF_POS;
        ::GetScrollInfo(hwnd, SB_VERT, &si);
        iVertPos = si.nPos;

        // Get horizontal scroll bar position
        ::GetScrollInfo(hwnd, SB_HORZ, &si);
        iHorzPos = si.nPos;

        // Find painting limits
        int iPaintBeg = max(0, iVertPos + cPs.rcPaint.top / cyChar);
        int iPaintEnd = min(NUM_LINES - 1, iVertPos + cPs.rcPaint.bottom / cyChar);

        for (auto i = iPaintBeg; i <= iPaintEnd; ++i) {
            int x = cxChar * (1 - iHorzPos);
            int y = cyChar * (i - iVertPos);

            ::TextOut(hdc, x, y, cArrSysMetrics[i].szLabel_, lstrlen(cArrSysMetrics[i].szLabel_));
            ::TextOut(hdc, x + 22 * cxCaps, y, cArrSysMetrics[i].szDesc_, lstrlen(cArrSysMetrics[i].szDesc_));

            ::SetTextAlign(hdc, TA_RIGHT | TA_TOP);
            wchar_t szBuffer[10] = {0};
            ::TextOut(hdc, x + 22 * cxCaps + 40 * cxChar, y, szBuffer,
                      wsprintf(szBuffer, L"%5d",
                      ::GetSystemMetrics(cArrSysMetrics[i].index_)));
            ::SetTextAlign(hdc, TA_LEFT | TA_TOP);
        }

        ::EndPaint(hwnd, &cPs);

        return 0;
    }

    case WM_DESTROY:
    {
        ::PostQuitMessage(0);
        return 0;
    }

    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}