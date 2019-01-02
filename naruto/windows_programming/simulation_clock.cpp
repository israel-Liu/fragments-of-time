#include <windows.h>
#include <cmath>

namespace {

const int ID_TIMER = 1;
const int TWOPI = 2 * 3.14159;

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"simulation_clock";
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

void SetIsotropic(HDC hdc, int cxClient, int cyClient)
{
    SetMapMode(hdc, MM_ISOTROPIC);
    SetWindowExtEx(hdc, 1000, 1000, nullptr);
    SetViewportExtEx(hdc, cxClient / 2, -cyClient / 2, nullptr);
    SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, nullptr);
}

void RotatePoint(POINT pt[], int iNum, int iAngle)
{
    POINT ptTemp;
    for (int i = 0; i < iNum; ++i) {
        ptTemp.x = static_cast<int>(pt[i].x * cos(TWOPI * iAngle / 360) + pt[i].y * sin(TWOPI * iAngle / 360));
        ptTemp.y = static_cast<int>(pt[i].y * cos(TWOPI * iAngle / 360) - pt[i].x * sin(TWOPI * iAngle / 360));

        pt[i] = ptTemp;
    }
}

void DrawHands(HDC hdc, SYSTEMTIME* pSt, bool fChange)
{
    static POINT pt[3][5] = {0, -150, 100, 0, 0, 600, -100, 0, 0, -150,
                             0, -200, 50, 0, 0, 800, -50, 0, 0, -200,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 800};

    int iAngle[3] = {pSt->wHour * 30 % 360 + pSt->wMinute / 2,
                     pSt->wMinute * 6, pSt->wSecond * 6};

    POINT ptTemp[3][5];
    memcpy(ptTemp, pt, sizeof(pt));

    for (int i = fChange ? 0 : 2; i < 3; ++i) {
        RotatePoint(ptTemp[i], 5, iAngle[i]);
        Polyline(hdc, ptTemp[i], 5);
    }
}

void DrawClock(HDC hdc)
{
    POINT pt[3];
    for (int iAngle = 0; iAngle < 360; iAngle += 6) {
        pt[0].x = 0;
        pt[0].y = 900;

        RotatePoint(pt, 1, iAngle);

        pt[2].x = pt[2].y = iAngle % 5 ? 33 : 100;
        pt[0].x -= pt[2].x / 2;
        pt[0].y -= pt[2].y / 2;

        pt[1].x = pt[0].x + pt[2].x;
        pt[1].y = pt[0].y + pt[2].y;

        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        Ellipse(hdc, pt[0].x, pt[0].y, pt[1].x, pt[1].y);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    static SYSTEMTIME stPrevious;

    switch (msg) {
    case WM_CREATE:
    {
        SetTimer(hwnd, ID_TIMER, 1000, nullptr);
        SYSTEMTIME st;
        GetLocalTime(&st);
        stPrevious = st;

        return 0;
    }

    case WM_SIZE:
    {
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        return 0;
    }

    case WM_TIMER:
    {
        SYSTEMTIME st;
        GetLocalTime(&st);

        bool fChange = st.wHour != stPrevious.wHour || st.wMinute != stPrevious.wMinute;

        HDC hdc = GetDC(hwnd);
        SetIsotropic(hdc, cxClient, cyClient);

        SelectObject(hdc, GetStockObject(WHITE_PEN));
        DrawHands(hdc, &stPrevious, fChange);
        SelectObject(hdc, GetStockObject(BLACK_PEN));
        DrawHands(hdc, &st, true);

        ReleaseDC(hwnd, hdc);
        stPrevious = st;

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);
        SetIsotropic(hdc, cxClient, cyClient);

        DrawClock(hdc);
        DrawHands(hdc, &stPrevious, true);

        ::EndPaint(hwnd, &cPs);

        return 0;
    }

    case WM_DESTROY:
    {
        KillTimer(hwnd, ID_TIMER);
        ::PostQuitMessage(0);
        return 0;
    }

    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}