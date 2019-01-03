#include <windows.h>

namespace {

const int DIVISIONS = 5;

static wchar_t szChildClass[] = L"Child_Wnd";

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"Child_Wnd_Hit_Test";
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

    wndclass.lpfnWndProc = ChildWndProc;
    wndclass.cbWndExtra = sizeof(long);
    wndclass.hIcon = nullptr;
    wndclass.lpszClassName = szChildClass;
    RegisterClass(&wndclass);

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
    static HWND hwndChild[DIVISIONS][DIVISIONS];

    switch (msg) {
    case WM_CREATE:
    {
        for (int x = 0; x < DIVISIONS; ++x) {
            for (int y = 0; y < DIVISIONS; ++y) {
                hwndChild[x][y] = CreateWindow(szChildClass, nullptr,
                                               WS_CHILDWINDOW | WS_VISIBLE,
                                               0, 0, 0, 0,
                                               hwnd,
                                               //static_cast<HMENU>(y << 8 | x),
                                               (HMENU)(y << 8 | x),
                                               //static_cast<HINSTANCE>(GetWindowLong(hwnd, GWL_HINSTANCE)),
                                               (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                                               nullptr);

                return 0;
            }
        }
        return 0;
    }

    case WM_SIZE:
    {
        int cxBlock = LOWORD(lParam) / DIVISIONS;
        int cyBlock = HIWORD(lParam) / DIVISIONS;

        for (int x = 0; x < DIVISIONS; ++x) {
            for (int y = 0; y < DIVISIONS; ++y) {
                MoveWindow(hwndChild[x][y], x * cxBlock, y * cyBlock, cxBlock, cyBlock, TRUE);
            }
        }

        return 0;
    }

    case WM_LBUTTONDOWN:
    {
        MessageBeep(0);

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
        ::PostQuitMessage(0);
        return 0;
    }

    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE:
    {
        // On / Off flag
        SetWindowLong(hwnd, 0, 0);

        return 0;
    }

    case WM_LBUTTONDOWN:
    {
        SetWindowLong(hwnd, 0, 1 ^ GetWindowLong(hwnd, 0));
        InvalidateRect(hwnd, nullptr, FALSE);

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);
        Rectangle(hdc, 0, 0, rect.right, rect.bottom);

        if (GetWindowLong(hwnd, 0)) {
            MoveToEx(hdc, 0, 0, nullptr);
            LineTo(hdc, rect.right, rect.bottom);
            MoveToEx(hdc, 0, rect.bottom, nullptr);
            LineTo(hdc, rect.right, 0);
        }

        EndPaint(hwnd, &ps);

        return 0;
    }

    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}