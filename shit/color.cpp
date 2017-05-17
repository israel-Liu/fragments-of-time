#include <windows.h>

namespace {

int idFocus;
WNDPROC OldScroll[3];

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ScrollProc(HWND, UINT, WPARAM, LPARAM);

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
    static COLORREF crPrim[3] = {RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255)};
    static HBRUSH hBrush[3], hBrushStatic;
    static HWND hwndScroll[3], hwndLabel[3], hwndValue[3], hwndRect;
    static int color[3], cyChar;
    static RECT rcColor;
    static wchar_t* szColorLabel[] = {L"Red", L"Green", L"Blue"};

    switch (msg) {
    case WM_CREATE:
    {
        HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);

        // Create the white-rectangle window against which the scroll bars will be positioned.
        // The child window ID is 9.
        hwndRect = CreateWindow(L"static", nullptr, WS_CHILD | WS_VISIBLE | SS_WHITERECT,
                                0, 0, 0, 0, hwnd, (HMENU)9, hInstance, nullptr);

        for (int i = 0; i < 3; ++i) {
            // The three scroll bars have IDs 0, 1, and 2, with scroll bar ranges from 0 through 255.
            hwndScroll[i] = CreateWindow(L"scrollbar", nullptr, WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT,
                                         0, 0, 0, 0, hwnd, (HMENU)i, hInstance, nullptr);

            SetScrollRange(hwndScroll[i], SB_CTL, 0, 255, false);
            SetScrollPos(hwndScroll[i], SB_CTL, 0, false);

            // The three color-name labels have IDs 3, 4, 5, and text strings "Red", "Green", and "Blue".
            hwndLabel[i] = CreateWindow(L"static", szColorLabel[i], WS_CHILD | WS_VISIBLE | SS_CENTER,
                                        0, 0, 0, 0, hwnd, (HMENU)(i + 3), hInstance, nullptr);

            // The three color-value text fields have IDs 6, 7, and 8, and initial text strings of "0".
            hwndValue[i] = CreateWindow(L"static", L"0", WS_CHILD | WS_VISIBLE | SS_CENTER,
                                        0, 0, 0, 0, hwnd, (HMENU)(i + 6), hInstance, nullptr);

            OldScroll[i] = (WNDPROC)SetWindowLong(hwndScroll[i], GWL_WNDPROC, (LONG)ScrollProc);
            hBrush[i] = CreateSolidBrush(crPrim[i]);
        }

        hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
        cyChar = HIWORD(GetDialogBaseUnits());

        return 0;
    }

    case WM_SIZE:
    {
        int cxClient = LOWORD(lParam);
        int cyClient = HIWORD(lParam);
        SetRect(&rcColor, cxClient / 2, 0, cxClient, cyClient);
        MoveWindow(hwndRect, 0, 0, cxClient / 2, cyClient, true);

        for (int i = 0; i < 3; ++i) {
            MoveWindow(hwndScroll[i], (2 * i + 1) * cxClient / 14, 2 * cyChar,
                       cxClient / 14, cyClient - 4 * cyChar, true);

            MoveWindow(hwndLabel[i], (4 * i + 1) * cxClient / 28, cyChar / 2,
                       cxClient / 7, cyChar, true);

            MoveWindow(hwndValue[i], (4 * i + 1) * cxClient / 28, cyClient - 3 * cyChar / 2,
                       cxClient / 7, cyChar, true);
        }

        SetFocus(hwnd);

        return 0;
    }

    case WM_SETFOCUS:
    {
        SetFocus(hwndScroll[idFocus]);

        return 0;
    }

    case WM_VSCROLL:
    {
        int i = GetWindowLong((HWND)lParam, GWL_ID);

        switch (LOWORD(wParam)) {
        case SB_PAGEDOWN:
        {
            color[i] += 15;
        }

        // fall through
        case SB_LINEDOWN:
        {
            color[i] = min(255, color[i] + 1);

            break;
        }

        case SB_PAGEUP:
        {
            color[i] = max(0, color[i] - 1);
        }

        // fall through
        case SB_LINEUP:
        {
            color[i] = max(0, color[i] - 1);

            break;
        }

        case SB_TOP:
        {
            color[i] = 0;

            break;
        }

        case SB_BOTTOM:
        {
            color[i] = 255;

            break;
        }

        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
        {
            color[i] = HIWORD(wParam);

            break;
        }

        default:
            break;
        }

        SetScrollPos(hwndScroll[i], SB_CTL, color[i], true);
        wchar_t szBuffer[10];
        wsprintf(szBuffer, L"%i", color[i]);
        SetWindowText(hwndValue[i], szBuffer);

        DeleteObject((HBRUSH)SetClassLong(hwnd, GCL_HBRBACKGROUND,
                     (LONG)CreateSolidBrush(RGB(color[0], color[1], color[2]))));

        InvalidateRect(hwnd, &rcColor, true);

        return 0;
    }

    case WM_CTLCOLORSCROLLBAR:
    {
        int i = GetWindowLong((HWND)lParam, GWL_ID);

        return (LRESULT)hBrush[i];
    }

    case WM_CTLCOLORSTATIC:
    {
        int i = GetWindowLong((HWND)lParam, GWL_ID);

        // Static text controls
        if (i >= 3 && i <= 8) {
            SetTextColor((HDC)wParam, crPrim[i % 3]);
            SetBkColor((HDC)wParam, GetSysColor(COLOR_BTNHIGHLIGHT));

            return (LRESULT)hBrushStatic;
        }

        break;
    }

    case WM_SYSCOLORCHANGE:
    {
        DeleteObject(hBrushStatic);
        hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);
        ::EndPaint(hwnd, &cPs);

        return 0;
    }

    case WM_DESTROY:
    {
        DeleteObject((HBRUSH)SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(WHITE_BRUSH)));

        for (int i = 0; i < 3; ++i) {
            DeleteObject(hBrush[i]);
        }

        DeleteObject(hBrushStatic);

        ::PostQuitMessage(0);
        return 0;
    }

    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK ScrollProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int id = GetWindowLong(hwnd, GWL_ID);
    switch (msg) {
    case WM_KEYDOWN:
    {
        if (wParam == VK_TAB) {
            SetFocus(GetDlgItem(GetParent(hwnd), (id + (GetKeyState(VK_SHIFT) < 0 ? 2 : 1)) % 3));

            break;
        }
    }

    case WM_SETFOCUS:
    {
        idFocus = id;

        break;
    }

    default:
        break;
    }

    return CallWindowProc(OldScroll[id], hwnd, msg, wParam, lParam);
}