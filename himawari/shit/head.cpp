#include <windows.h>

namespace {

const int ID_LIST = 1;
const int ID_TEXT = 2;
const int MAX_READ = 8192;
const int DIR_ATTR = DDL_READWRITE | DDL_READONLY | DDL_HIDDEN | DDL_SYSTEM | DDL_DIRECTORY | DDL_ARCHIVE | DDL_DRIVES;
const int DT_FLAGS = DT_WORDBREAK | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX;

WNDPROC old_list;

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ListProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"hinata_head";
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
    static bool b_valid_file;
    static BYTE buffer[MAX_READ];
    static HWND hwnd_list, hwnd_text;
    static RECT rect;
    static wchar_t file_name[MAX_PATH + 1];

    switch (msg) {
    case WM_CREATE:
    {
        int cxChar = LOWORD(GetDialogBaseUnits());
        int cyChar = HIWORD(GetDialogBaseUnits());

        rect.left = 20 * cxChar;
        rect.top = 3 * cyChar;

        hwnd_list = CreateWindow(L"listbox", nullptr, WS_CHILDWINDOW | WS_VISIBLE | LBS_STANDARD, cxChar, cyChar * 13,
                                 cxChar * 13 + GetSystemMetrics(SM_CXVSCROLL), cyChar * 10, hwnd, (HMENU)ID_LIST,
                                 (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), nullptr);

        wchar_t dir[MAX_PATH + 1];
        GetCurrentDirectory(MAX_PATH + 1, dir);

        hwnd_text = CreateWindow(L"static", dir, WS_CHILDWINDOW | WS_VISIBLE | SS_LEFT, cxChar, cyChar,
                                 cxChar * MAX_PATH, cyChar, hwnd, (HMENU)ID_TEXT,
                                 (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), nullptr);

        old_list = (WNDPROC)SetWindowLong(hwnd_list, GWL_WNDPROC, (LPARAM)ListProc);

        SendMessage(hwnd_list, LB_DIR, DIR_ATTR, (LPARAM)L"*.*");

        return 0;
    }

    case WM_SIZE:
    {
        rect.right = LOWORD(lParam);
        rect.bottom = HIWORD(lParam);

        return 0;
    }

    case WM_SETFOCUS:
    {
        SetFocus(hwnd_list);

        return 0;
    }

    case WM_COMMAND:
    {
        int i = 0;
        if (LOWORD(wParam) == ID_LIST && HIWORD(wParam) == LBN_DBLCLK) {
            if (LB_ERR == (i = SendMessage(hwnd_list, LB_GETCURSEL, 0, 0))) {
                break;
            }

            wchar_t list_text[MAX_PATH + 1];
            SendMessage(hwnd_list, LB_GETTEXT, i, (LPARAM)list_text);

            HANDLE hFile;
            if (INVALID_HANDLE_VALUE != (hFile = CreateFile(list_text, GENERIC_READ, FILE_SHARE_READ, nullptr,
                                                            OPEN_EXISTING, 0, nullptr))) {
                CloseHandle(hFile);
                b_valid_file = true;
                lstrcpy(file_name, list_text);
                GetCurrentDirectory(MAX_PATH + 1, list_text);

                if (list_text[lstrlen(list_text) - 1] != '\\') {
                    lstrcat(list_text, L"\\");
                }

                SetWindowText(hwnd_text, lstrcat(list_text, file_name));
            } else {
                b_valid_file = false;
                list_text[lstrlen(list_text) - 1] = '\0';

                // If setting the directory does not work, maybe it is a drive change, so try that.
                if (!SetCurrentDirectory(list_text + 1)) {
                    list_text[3] = ':';
                    list_text[4] = '\0';
                    SetCurrentDirectory(list_text + 2);
                }

                // Get the new directory name and fill the list box.
                GetCurrentDirectory(MAX_PATH + 1, list_text);
                SetWindowText(hwnd_list, list_text);
                SendMessage(hwnd_list, LB_RESETCONTENT, 0, 0);
                SendMessage(hwnd_list, LB_DIR, DIR_ATTR, (LPARAM)L"*.*");
            }

            InvalidateRect(hwnd, nullptr, true);
        }

        return 0;
    }

    case WM_PAINT:
    {
        if (!b_valid_file) {
            break;
        }

        HANDLE hFile;
        if (INVALID_HANDLE_VALUE == (hFile = CreateFile(file_name, GENERIC_READ, FILE_SHARE_READ, nullptr,
            OPEN_EXISTING, 0, nullptr))) {
            b_valid_file = false;
            break;
        }

        int i = 0;
        ReadFile(hFile, buffer, MAX_READ, (LPDWORD)&i, nullptr);
        CloseHandle(hFile);

        // i now equals the number of bytes in buffer.
        // Commence getting a device context for displaying text.

        PAINTSTRUCT cPs;
        HDC hdc = ::BeginPaint(hwnd, &cPs);
        SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
        SetTextColor(hdc, GetSysColor(COLOR_BTNTEXT));
        SetBkColor(hdc, GetSysColor(COLOR_BTNFACE));

        // Assume the file is ASCII
        DrawTextA(hdc, (LPCSTR)buffer, i, &rect, DT_FLAGS);
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

LRESULT CALLBACK ListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_KEYDOWN && wParam == VK_RETURN) {
        SendMessage(GetParent(hwnd), WM_COMMAND, MAKELONG(1, LBN_DBLCLK), (LPARAM)hwnd);
    }

    return CallWindowProc(old_list, hwnd, msg, wParam, lParam);
}