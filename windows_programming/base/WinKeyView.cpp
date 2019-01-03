#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"WinKeyView";
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

    HWND hwnd = ::CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
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
    static int cxClientMax, cyClientMax, cxChar, cyChar, cxClient, cyClient;
    static int cLinesMax, cLines;
    static PMSG pMsg;
    static RECT rcScroll;

    switch (msg) {
    case WM_CREATE:
    case WM_DISPLAYCHANGE:
    {
        // Get maximum size of client area
        cxClientMax = GetSystemMetrics(SM_CXMAXIMIZED);
        cyClientMax = GetSystemMetrics(SM_CYMAXIMIZED);

        // Get character size for fixed-pitch font
        HDC hdc = GetDC(hwnd);
        SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
        TEXTMETRIC tm;
        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cyChar = tm.tmHeight;
        ReleaseDC(hwnd, hdc);

        // Allocate memory for display lines
        if (pMsg) {
            free(pMsg);
        }

        cLinesMax = cyClientMax / cyChar;
        pMsg = static_cast<PMSG>(malloc(cLinesMax * sizeof(MSG)));
        cLines = 0;
    }

    case WM_SIZE:
    {
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        // Calculate scrolling rectangle
        rcScroll.left = 0;
        rcScroll.right = cxClient;
        rcScroll.top = cyChar;
        rcScroll.bottom = cyChar * (cyClient / cyChar);

        InvalidateRect(hwnd, nullptr, TRUE);

        return 0;
    }

    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_CHAR:
    case WM_DEADCHAR:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_SYSCHAR:
    case WM_SYSDEADCHAR:
    {
        // Rearrange storage array
        for (int i = cLinesMax - 1; i > 0; --i) {
            pMsg[i] = pMsg[i - 1];
        }

        // Store new message
        pMsg[0].hwnd = hwnd;
        pMsg[0].message = msg;
        pMsg[0].wParam = wParam;
        pMsg[0].lParam = lParam;

        cLines = min(cLines + 1, cLinesMax);

        // Scroll up the display
        ScrollWindow(hwnd, 0, -cyChar, &rcScroll, &rcScroll);

        // Call DefWindowProc so sys messages work
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);
        SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
        SetBkMode(hdc, TRANSPARENT);

        static TCHAR szTop[] = TEXT("Message        Key     Char   Repeat   Scan    Ext     ALT     Prev    Tran");
        static TCHAR szUnd[] = TEXT("_______        ___     ____   ______   ____    ___     ___     ____    ____");

        TextOut(hdc, 0, 0, szTop, lstrlen(szTop));
        TextOut(hdc, 0, 0, szUnd, lstrlen(szUnd));

        int iType = 0;
        TCHAR szBuffer[128] = {}, szKeyName[32] = {};
        static TCHAR* szFormat[2] = { TEXT("%-13s %3d    %-15s    %c%6u    %4d  %3s    %3s    %4s   %4s"),
                                      TEXT("%-13s  0x%04X%1s    %c %6u    %4d  %3s    %3s   %4s    %4s") };

        static TCHAR* szMessage[] = { TEXT("WM_KEYDOWN"), TEXT("WM_KEYUP"),
                                      TEXT("WM_CHAR"), TEXT("WM_DEADCHAR"),
                                      TEXT("WM_SYSKEYDOWN"), TEXT("WM_SYSKEYUP"),
                                      TEXT("WM_SYSCHAR"), TEXT("WM_SYSDEADCHAR") };

        static TCHAR* szYes = TEXT("Yes");
        static TCHAR* szNo = TEXT("No");
        static TCHAR* szDown = TEXT("Down");
        static TCHAR* szUp = TEXT("Up");

        for (int i = 0; i < min(cLines, cyClient / cyChar -1); ++i) {
            iType = pMsg[i].message == WM_CHAR || pMsg[i].message == WM_SYSCHAR ||
                    pMsg[i].message == WM_DEADCHAR || pMsg[i].message == WM_SYSDEADCHAR;

            GetKeyNameText(pMsg[i].lParam, szKeyName, sizeof(szKeyName) / sizeof(TCHAR));
            TextOut(hdc, 0, (cyClient / cyChar - 1 - i) * cyChar, szBuffer,
                    wsprintf(szBuffer, szFormat[iType],
                                szMessage[pMsg[i].message - WM_KEYFIRST],
                                pMsg[i].wParam,
                                static_cast<PTSTR>(iType ? TEXT(" ") : szKeyName),
                                static_cast<TCHAR>(iType ? pMsg[i].wParam : ' '),
                                LOWORD(pMsg[i].lParam),
                                HIWORD(pMsg[i].lParam) & 0xFF,
                                0x01000000 & pMsg[i].lParam ? szYes : szNo,
                                0x20000000 & pMsg[i].lParam ? szYes : szNo,
                                0x40000000 & pMsg[i].lParam ? szDown : szUp,
                                0x80000000 & pMsg[i].lParam ? szUp : szDown
                            )
                    );
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