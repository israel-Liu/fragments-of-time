#include <windows.h>

namespace {

const int DIVISIONS = 5;

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"Mouse_Hit_Test";
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
    static bool fState[DIVISIONS][DIVISIONS];
    static int cxBlock, cyBlock;

    switch (msg) {
    case WM_CREATE:
    {
        return 0;
    }

    case WM_SIZE:
    {
        cxBlock = LOWORD(lParam) / DIVISIONS;
        cyBlock = HIWORD(lParam) / DIVISIONS;

        return 0;
    }

    case WM_LBUTTONDOWN:
    {
        int x = LOWORD(lParam) / cxBlock;
        int y = HIWORD(lParam) / cyBlock;

        if (x < DIVISIONS && y < DIVISIONS) {
            fState[x][y] ^= 1;

            RECT rect;
            rect.left = x * cxBlock;
            rect.top = y * cyBlock;
            rect.right = (x + 1) * cxBlock;
            rect.bottom = (y + 1) * cyBlock;

            InvalidateRect(hwnd, &rect, FALSE);
        } else {
            MessageBeep(0);
        }

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);

        for (int x = 0; x < DIVISIONS; ++x) {
            for (int y = 0; y < DIVISIONS; ++y) {
                Rectangle(hdc, x * cxBlock, y * cyBlock, (x + 1) * cxBlock, (y + 1) * cyBlock);

                if (fState[x][y]) {
                    MoveToEx(hdc, x * cxBlock, y * cyBlock, nullptr);
                    LineTo(hdc, (x + 1) * cxBlock, (y + 1) * cyBlock);
                    MoveToEx(hdc, x * cxBlock, (y + 1) * cyBlock, nullptr);
                    LineTo(hdc, (x + 1) * cxBlock, y * cyBlock);
                }
            }

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