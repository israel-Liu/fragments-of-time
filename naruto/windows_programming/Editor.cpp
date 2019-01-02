#include <windows.h>

inline TCHAR& BufferChar(TCHAR* pBuffer, int cxBuffer, int x, int y)
{
    return *(pBuffer + y * cxBuffer + x);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"Editor";
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
    static DWORD dwCharSet = DEFAULT_CHARSET;
    static int cxChar, cyChar, cxClient, cyClient, cxBuffer, cyBuffer, xCaret, yCaret;
    static TCHAR* pBuffer = nullptr;

    switch (msg) {

    case WM_INPUTLANGCHANGE:
    {
        dwCharSet = wParam;
    }

    case WM_CREATE:
    {
        HDC hdc = GetDC(hwnd);
        SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, nullptr));

        TEXTMETRIC tm;
        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cyChar = tm.tmHeight;

        DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
        ReleaseDC(hwnd, hdc);
    }

    case WM_SIZE:
    {
        // Obtain window size in pixels
        if (msg == WM_SIZE) {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
        }

        // Calculate window size in characters
        cxBuffer = max(1, cxClient / cxChar);
        cyBuffer = max(1, cyClient / cyChar);

        // Allocate memory for buffer and clear it
        if (pBuffer != nullptr) {
            free(pBuffer);
        }

        pBuffer = static_cast<TCHAR*>(malloc(cxBuffer * cyBuffer * sizeof(TCHAR)));

        for (int y = 0; y < cyBuffer; ++y) {
            for (int x = 0; x < cxBuffer; ++x) {
                BufferChar(pBuffer, cxBuffer, x, y) = ' ';
            }
        }

        // Set caret to upper left corner
        xCaret = 0;
        yCaret = 0;

        if (hwnd == GetFocus()) {
            SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        }

        InvalidateRect(hwnd, nullptr, TRUE);

        return 0;
    }

    case WM_SETFOCUS:
    {
        // Create and show the caret
        CreateCaret(hwnd, nullptr, cxChar, cyChar);
        SetCaretPos(xCaret * cxChar, yCaret * cyChar);
        ShowCaret(hwnd);

        return 0;
    }

    case WM_KILLFOCUS:
    {
        HideCaret(hwnd);
        DestroyCaret();

        return 0;
    }

    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_HOME:
        {
            xCaret = 0;

            break;
        }

        case VK_END:
        {
            xCaret = cxBuffer - 1;

            break;
        }

        case VK_PRIOR:
        {
            yCaret = 0;

            break;
        }

        case VK_NEXT:
        {
            yCaret = cyBuffer - 1;

            break;
        }

        case VK_LEFT:
        {
            xCaret = max(xCaret - 1, 0);

            break;
        }

        case VK_RIGHT:
        {
            xCaret = min(xCaret + 1, cxBuffer - 1);

            break;
        }

        case VK_UP:
        {
            yCaret = max(yCaret - 1, 0);

            break;
        }

        case VK_DOWN:
        {
            yCaret = min(yCaret + 1, cyBuffer - 1);

            break;
        }

        case VK_DELETE:
        {
            for (int x = xCaret; x < cxBuffer - 1; ++x) {
                BufferChar(pBuffer, cxBuffer, x, yCaret) = BufferChar(pBuffer, cxBuffer, x + 1, yCaret);
            }

            BufferChar(pBuffer, cxBuffer, cxBuffer - 1, yCaret) = ' ';
            HideCaret(hwnd);

            HDC hdc = GetDC(hwnd);
            SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, nullptr));
            TextOut(hdc, xCaret * cxChar, yCaret * cyChar,
                    &BufferChar(pBuffer, cxBuffer, xCaret, yCaret), cxBuffer - xCaret);
            DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
            ReleaseDC(hwnd, hdc);
            ShowCaret(hwnd);

            break;
        }

        default:
            break;
        }

        SetCaretPos(xCaret * cxChar, yCaret * cyChar);

        return 0;
    }

    case WM_CHAR:
    {
        for (int i = 0; i < static_cast<int>(LOWORD(lParam)); ++i) {
            switch (wParam) {
            case '\b':
            {
                // Backspace
                if (xCaret > 0) {
                    xCaret--;
                    SendMessage(hwnd, WM_KEYDOWN, VK_DELETE, 1);
                }

                break;
            }

            case '\t':
            {
                // Tab
                do {
                    SendMessage(hwnd, WM_CHAR, ' ', 1);
                } while (xCaret % 8 != 0);

                break;
            }

            case '\n':
            {
                // Line feed
                if (++yCaret == cyBuffer) {
                    yCaret = 0;
                }

                break;
            }

            case '\r':
            {
                // Carriage return
                xCaret = 0;
                if (++yCaret == cyBuffer) {
                    yCaret = 0;
                }

                break;
            }

            case '\x1b':
            {
                // Escape
                for (int y = 0; y < cyBuffer; ++y) {
                    for (int x = 0; x <cxBuffer; ++x) {
                        BufferChar(pBuffer, cxBuffer, x, y) = ' ';
                    }
                }

                xCaret = 0;
                yCaret = 0;

                InvalidateRect(hwnd, nullptr, FALSE);

                break;
            }

            default:
            {
                // Character codes
                BufferChar(pBuffer, cxBuffer, xCaret, yCaret) = static_cast<TCHAR>(wParam);
                HideCaret(hwnd);
                HDC hdc = GetDC(hwnd);
                SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, nullptr));
                TextOut(hdc, xCaret * cxChar, yCaret * cyChar,
                        &BufferChar(pBuffer, cxBuffer, xCaret, yCaret), 1);
                DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
                ReleaseDC(hwnd, hdc);
                ShowCaret(hwnd);

                if (++xCaret == cxBuffer) {
                    xCaret = 0;
                    if (++yCaret == cyBuffer) {
                        yCaret = 0;
                    }
                }

                break;
            }
            } // switch
        } // for

        SetCaretPos(xCaret * cxChar, yCaret * cyChar);

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);
        SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, nullptr));

        for (int y = 0; y < cyBuffer; ++y) {
            TextOut(hdc, 0, y * cyChar, &BufferChar(pBuffer, cxBuffer, 0, y), cxBuffer);
        }

        DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));

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