#include <windows.h>

namespace {

const int ID_EDIT = 1;
static wchar_t szAppName[] = L"hinata_notepad";

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
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
    static HWND hwnd_edit;

    switch (msg) {
    case WM_CREATE:
    {
        hwnd_edit = CreateWindow(L"edit", nullptr, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER |
                                 ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0, hwnd,
                                 (HMENU)ID_EDIT, ((LPCREATESTRUCT)lParam)->hInstance, nullptr);

        return 0;
    }

    case WM_SETFOCUS:
    {
        SetFocus(hwnd_edit);

        return 0;
    }

    case WM_SIZE:
    {
        MoveWindow(hwnd_edit, 0, 0, LOWORD(lParam), HIWORD(lParam), true);

        return 0;
    }

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == ID_EDIT) {
            if (HIWORD(wParam) == EN_ERRSPACE || HIWORD(wParam) == EN_MAXTEXT) {
                MessageBox(hwnd, L"Edit control out of space.", szAppName, MB_OK | MB_ICONSTOP);
            }
        }

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