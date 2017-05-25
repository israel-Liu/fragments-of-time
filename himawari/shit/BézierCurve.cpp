#include <windows.h>

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

void DrawBezier(HDC hdc, POINT apt[])
{
    ::PolyBezier(hdc, apt, 4);
    ::MoveToEx(hdc, apt[0].x, apt[0].y, nullptr);
    ::LineTo(hdc, apt[1].x, apt[1].y);

    ::MoveToEx(hdc, apt[2].x, apt[2].y, nullptr);
    ::LineTo(hdc, apt[3].x, apt[3].y);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static POINT apt[4];

    switch (msg) {
    case WM_CREATE:
    {
        return 0;
    }

    case WM_SIZE:
    {
        int cxClient = LOWORD(lParam);
        int cyClient = HIWORD(lParam);

        apt[0].x = cxClient / 4;
        apt[0].y = cyClient / 2;

        apt[1].x = cxClient / 2;
        apt[1].y = cyClient / 4;

        apt[2].x = cxClient / 2;
        apt[2].y = 3 * cyClient / 4;

        apt[3].x = 3 * cxClient / 4;
        apt[3].y = cyClient / 2;

        return 0;
    }

    case WM_LBUTTONDOWN:
    {}

    case WM_RBUTTONDOWN:
    {}

    case WM_MOUSEMOVE:
    {
        if (wParam & MK_LBUTTON || wParam & MK_RBUTTON) {
            HDC hdc = ::GetDC(hwnd);
            ::SelectObject(hdc, ::GetStockObject(WHITE_PEN));
            DrawBezier(hdc, apt);

            if (wParam & MK_LBUTTON) {
                apt[1].x = LOWORD(lParam);
                apt[1].y = HIWORD(lParam);
            }

            if (wParam & MK_RBUTTON) {
                apt[2].x = LOWORD(lParam);
                apt[2].y = HIWORD(lParam);
            }

            ::SelectObject(hdc, ::GetStockObject(BLACK_PEN));
            DrawBezier(hdc, apt);
            ::ReleaseDC(hwnd, hdc);
        }

        return 0;
    }

    case WM_PAINT:
    {
        ::InvalidateRect(hwnd, nullptr, true);
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);
        DrawBezier(hdc, apt);
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