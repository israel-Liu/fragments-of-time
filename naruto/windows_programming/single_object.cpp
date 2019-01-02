#include <windows.h>
#include <process.h>
#include <cmath>

const int rep = 10000000;
const int status_ready = 0;
const int status_working = 1;
const int status_done = 2;

const int WM_CALC_DONE = WM_USER + 0;
const int WM_CALC_ABORTED = WM_USER + 1;

typedef struct PARAMS
{
    HWND hwnd;
    HANDLE hEvent;
    bool bContinue;
} *PPARAMS;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"single_object";
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

void Thread(PVOID pvoid)
{
    double A = 1.0;
    volatile PPARAMS pparams = static_cast<PPARAMS>(pvoid);

    while (true) {
        WaitForSingleObject(pparams->hEvent, INFINITE);
        long time = GetCurrentTime();
        int i = 0;
        for (; i < rep && pparams->bContinue; ++i) {
            A = tan(atan(exp(log(sqrt(A * A))))) + 1.0;
        }

        if (i == rep) {
            time = GetCurrentTime() - time;
            PostMessage(pparams->hwnd, WM_CALC_DONE, 0, time);
        } else {
            PostMessage(pparams->hwnd, WM_CALC_ABORTED, 0, 0);
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HANDLE hEvent;
    static int iStatus;
    static long iTime;
    static PARAMS params;
    static wchar_t* status_msg[] = { L"Ready (left mouse button begins)",
                                     L"Working (right mouse button ends)",
                                     L"%d repetitions in %ld msec"};


    switch (msg) {
    case WM_CREATE:
    {
        hEvent = CreateEvent(nullptr, false, false, nullptr);
        params.hwnd = hwnd;
        params.hEvent = hEvent;
        params.bContinue = false;

        _beginthread(Thread, 0, &params);

        return 0;
    }

    case WM_LBUTTONDOWN:
    {
        if (iStatus == status_working) {
            MessageBeep(0);
            return 0;
        }

        iStatus = status_working;
        params.bContinue = true;

        SetEvent(hEvent);

        InvalidateRect(hwnd, nullptr, true);

        return 0;
    }

    case WM_RBUTTONDOWN:
    {
        params.bContinue = false;

        return 0;
    }

    case WM_CALC_DONE:
    {
        iTime = lParam;
        iStatus = status_done;

        InvalidateRect(hwnd, nullptr, true);

        return 0;
    }

    case WM_CALC_ABORTED:
    {
        iStatus = status_ready;

        InvalidateRect(hwnd, nullptr, true);

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);
        RECT rect;
        GetClientRect(hwnd, &rect);

        wchar_t buff[64] = {0};
        wsprintf(buff, status_msg[iStatus], rep, iTime);
        DrawText(hdc, buff, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

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