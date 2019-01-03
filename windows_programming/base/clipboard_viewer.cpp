#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"clipboard_viewer";
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
    static HWND hwnd_next_viewer;

    switch (msg) {
    case WM_CREATE:
    {
        hwnd_next_viewer = SetClipboardViewer(hwnd);

        return 0;
    }

    case WM_CHANGECBCHAIN:
    {
        if ((HWND) wParam == hwnd_next_viewer) {
            hwnd_next_viewer = (HWND) lParam;
        } else if (hwnd_next_viewer) {
            SendMessage(hwnd_next_viewer, msg, wParam, lParam);
        }

        return 0;
    }

    case WM_DRAWCLIPBOARD:
    {
        if (hwnd_next_viewer) {
            SendMessage(hwnd_next_viewer, msg, wParam, lParam);
        }

        InvalidateRect(hwnd, NULL, TRUE);

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);

        RECT rect;
        GetClientRect(hwnd, &rect);
        OpenClipboard(hwnd);

#ifdef UNICODE
        HGLOBAL global_clipboard_handle = GetClipboardData(CF_UNICODETEXT);
#else
        HGLOBAL global_clipboard_handle = GetClipboardData(CF_TEXT);
#endif
        if (global_clipboard_handle != NULL) {
            PTSTR clipboard_str = static_cast<PTSTR>(GlobalLock(global_clipboard_handle));
            DrawText(hdc, clipboard_str, -1, &rect, DT_EXPANDTABS);
            GlobalUnlock(clipboard_str);
        }

        CloseClipboard();

        ::EndPaint(hwnd, &cPs);

        return 0;
    }

    case WM_DESTROY:
    {
        ChangeClipboardChain(hwnd, hwnd_next_viewer);

        ::PostQuitMessage(0);
        return 0;
    }

    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}