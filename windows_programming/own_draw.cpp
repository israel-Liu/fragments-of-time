#include <windows.h>

namespace {

const int ID_SMALLER = 1;
const int ID_LARGER = 2;

inline int btn_width(int cxChar)
{
    return 8 * cxChar;
}

inline int btn_height(int cyChar)
{
    return 4 * cyChar;
}

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"own_draw";
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

void Triangle(HDC hdc, POINT pt[])
{
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    Polygon(hdc, pt, 3);
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwnd_smaller, hwnd_larger;
    static int cxClient, cyClient, cxChar, cyChar;
    static HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;

    switch (msg) {
    case WM_CREATE:
    {
        cxChar = LOWORD(GetDialogBaseUnits());
        cyChar = HIWORD(GetDialogBaseUnits());

        // Create the owner-draw pushbuttons
        hwnd_smaller = CreateWindow(L"button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                                    0, 0, btn_width(cxChar), btn_height(cyChar), hwnd,
                                    (HMENU)ID_SMALLER, hInst, nullptr);

        hwnd_larger = CreateWindow(L"button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                                   0, 0, btn_width(cxChar), btn_height(cyChar), hwnd,
                                   (HMENU)ID_LARGER, hInst, nullptr);

        return 0;
    }

    case WM_SIZE:
    {
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        // Move the buttons to the new center
        MoveWindow(hwnd_smaller, cxClient / 2 - 3 * btn_width(cxChar), cyClient / 2 - btn_height(cyChar) / 2,
                   btn_width(cxChar), btn_height(cyChar), true);

        MoveWindow(hwnd_larger, cxClient / 2 + btn_width(cxChar) / 2, cyClient / 2 - btn_height(cyChar) / 2,
                   btn_width(cxChar), btn_height(cyChar), true);

        return 0;
    }

    case WM_COMMAND:
    {
        RECT rc;
        GetWindowRect(hwnd, &rc);

        // Make the window 10% smaller or larger
        switch (wParam) {
        case ID_SMALLER:
        {
            rc.left += cxClient / 20;
            rc.right -= cxClient / 20;
            rc.top += cyClient / 20;
            rc.bottom -= cyClient / 20;

            break;
        }

        case ID_LARGER:
        {
            rc.left -= cxClient / 20;
            rc.right += cxClient / 20;
            rc.top -= cyClient / 20;
            rc.bottom += cyClient / 20;

            break;
        }

        default:
            break;
        }

        MoveWindow(hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, true);

        return 0;
    }

    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT pDis = (LPDRAWITEMSTRUCT)lParam;

        // Fill area with white and frame it black
        FillRect(pDis->hDC, &pDis->rcItem, (HBRUSH)GetStockObject(WHITE_BRUSH));
        FrameRect(pDis->hDC, &pDis->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));

        // Draw inward and outward black triangles
        int cx = pDis->rcItem.right - pDis->rcItem.left;
        int cy = pDis->rcItem.bottom - pDis->rcItem.top;

        switch (pDis->CtlID) {

        POINT pt[3];

        case ID_SMALLER:
        {
            pt[0].x = 3 * cx / 8;   pt[0].y = 1 * cy / 8;
            pt[1].x = 5 * cx / 8;   pt[1].y = 1 * cy / 8;
            pt[2].x = 4 * cx / 8;   pt[2].y = 3 * cy / 8;

            Triangle(pDis->hDC, pt);

            pt[0].x = 7 * cx / 8;   pt[0].y = 3 * cy  / 8;
            pt[1].x = 7 * cx / 8;   pt[1].y = 5 * cy / 8;
            pt[2].x = 5 * cx / 8;   pt[2].y = 4 * cy / 8;

            Triangle(pDis->hDC, pt);

            pt[0].x = 5 * cx / 8;   pt[0].y = 7 * cy / 8;
            pt[1].x = 3 * cx / 8;   pt[1].y = 7 * cy / 8;
            pt[2].x = 4 * cx / 8;   pt[2].y = 5 * cy / 8;

            Triangle(pDis->hDC, pt);

            pt[0].x = 1 * cx / 8;   pt[0].y = 5 * cy / 8;
            pt[1].x = 1 * cx / 8;   pt[1].y = 3 * cy / 8;
            pt[2].x = 3 * cx / 8;   pt[2].y = 4 * cy / 8;

            Triangle(pDis->hDC, pt);

            break;
        }

        case ID_LARGER:
        {
            pt[0].x = 5 * cx / 8;   pt[0].y = 3 * cy / 8;
            pt[1].x = 3 * cx / 8;   pt[1].y = 3 * cy / 8;
            pt[2].x = 4 * cx / 8;   pt[2].y = 1 * cy / 8;

            Triangle(pDis->hDC, pt);

            pt[0].x = 5 * cx / 8;   pt[0].y = 5 * cy / 8;
            pt[1].x = 5 * cx / 8;   pt[1].y = 3 * cy / 8;
            pt[2].x = 7 * cx / 8;   pt[2].y = 4 * cy / 8;

            Triangle(pDis->hDC, pt);

            pt[0].x = 3 * cx / 8;   pt[0].y = 5 * cy / 8;
            pt[1].x = 5 * cx / 8;   pt[1].y = 5 * cy / 8;
            pt[2].x = 4 * cx / 8;   pt[2].y = 7 * cy / 8;

            Triangle(pDis->hDC, pt);

            pt[0].x = 3 * cx / 8;   pt[0].y = 3 * cy / 8;
            pt[1].x = 3 * cx / 8;   pt[1].y = 5 * cy / 8;
            pt[2].x = 1 * cx / 8;   pt[2].y = 4 * cy / 8;

            Triangle(pDis->hDC, pt);

            break;
        }

        default:
            break;
        }

        if (pDis->itemState & ODS_FOCUS) {
            pDis->rcItem.left += cx / 16;
            pDis->rcItem.top += cy / 16;
            pDis->rcItem.right -= cx / 16;
            pDis->rcItem.bottom -= cy / 16;

            DrawFocusRect(pDis->hDC, &pDis->rcItem);
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