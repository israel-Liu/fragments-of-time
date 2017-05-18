#include <windows.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int cxClient = 0, cyClient = 0;

void DrawRectangle(HWND);

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

    HWND hwnd = ::CreateWindow(szAppName, szAppName, WS_OVERLAPPED,
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               nullptr, nullptr, hInstance, nullptr);

    ::ShowWindow(hwnd, iCmdShow);
    ::UpdateWindow(hwnd);

    MSG msg;
    BOOL bRet;
    while (TRUE) {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if	(msg.message == WM_QUIT) {
				break;
			}

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
        } else {
			DrawRectangle(hwnd);
		}
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		return 0;
	}

	case WM_DESTROY:
	{
		::PostQuitMessage(0);

		return 0;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;

}

void DrawRectangle(HWND hwnd)
{
	if (0 == cxClient || 0 == cyClient) {
		return;
	}

	RECT rect;
	SetRect(&rect, rand() % cxClient, rand() % cyClient, rand() % cxClient, rand() % cyClient);
	HBRUSH hBrush = ::CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	HDC hdc = ::GetDC(hwnd);
	::FillRect(hdc, &rect, hBrush);
	::ReleaseDC(hwnd, hdc);
	::DeleteObject(hBrush);
}