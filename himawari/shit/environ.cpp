/*

//  Environment List Box

*/
#include <windows.h>

namespace {

const int ID_LIST = 1;
const int ID_TEXT = 2;

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR szCmdLine, int iCmdShow)
{
    static wchar_t szAppName[] = L"hinata_environ";
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

void fill_list_box(HWND hwnd_list)
{
    // Get pointer to environment block
    wchar_t* p_var_block = GetEnvironmentStrings();

    while (*p_var_block) {

        // Skip variable names beginning with '='
        if (*p_var_block != '=') {

            // Beginning of variable name
            wchar_t* p_var_beg = p_var_block;

            // Scan until '='
            while (*p_var_block++ != '=') {
                ;
            }

            // Points to '=' sign
            wchar_t* p_var_end = p_var_block - 1;

            // Length of variable name
            int length = p_var_end - p_var_beg;

            // Allocate memory for the variable name and terminating zero.
            // Copy the variable name and append a zero.
            wchar_t* p_var_name = static_cast<wchar_t*>(calloc(length + 1, sizeof(wchar_t)));
            CopyMemory(p_var_name, p_var_beg, length * sizeof(wchar_t));
            p_var_name[length] = '\0';

            // Put the variable name in the list box and free memory.
            SendMessage(hwnd_list, LB_ADDSTRING, 0, (LPARAM)p_var_name);
            free(p_var_name);
        }

        while (*p_var_block++ != '\0') {
            ;
        }
    }

    FreeEnvironmentStrings(p_var_block);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwnd_list, hwnd_text;

    switch (msg) {
    case WM_CREATE:
    {
        int cxChar = LOWORD(GetDialogBaseUnits());
        int cyChar = HIWORD(GetDialogBaseUnits());

        // Create listbox and static text windows.
        hwnd_list = CreateWindow(L"listbox", nullptr, WS_CHILD | WS_VISIBLE | LBS_STANDARD, cxChar, cyChar * 3,
                                 cxChar * 16 + GetSystemMetrics(SM_CXVSCROLL), cyChar * 5, hwnd, (HMENU)ID_LIST,
                                 (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), nullptr);

        hwnd_text = CreateWindow(L"static", nullptr, WS_CHILD | WS_VISIBLE | SS_LEFT, cxChar, cyChar,
                                 GetSystemMetrics(SM_CXSCREEN), cyChar, hwnd, (HMENU)ID_TEXT,
                                 (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), nullptr);

        fill_list_box(hwnd_list);

        return 0;
    }

    case WM_SETFOCUS:
    {
        SetFocus(hwnd_list);

        return 0;
    }

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == ID_LIST && HIWORD(wParam) == LBN_SELCHANGE) {
            // Get current selection
            int index = SendMessage(hwnd_list, LB_GETCURSEL, 0, 0);
            int length = SendMessage(hwnd_list, LB_GETTEXTLEN, index, 0) + 1;
            wchar_t* p_var_name = static_cast<wchar_t*>(calloc(length, sizeof(wchar_t)));
            SendMessage(hwnd_list, LB_GETTEXT, index, (LPARAM)p_var_name);

            // Get environment string.
            length = GetEnvironmentVariable(p_var_name, nullptr, 0);
            wchar_t* p_var_value = static_cast<wchar_t*>(calloc(length, sizeof(wchar_t)));
            GetEnvironmentVariable(p_var_name, p_var_value, length);

            // Show it in window.
            SetWindowText(hwnd_text, p_var_value);
            free(p_var_name);
            free(p_var_value);
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