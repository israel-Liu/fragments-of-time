#include <windows.h>

#include "resource.h"

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
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ID_HINATA_NOTEPAD));
    wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wndclass.lpszMenuName = MAKEINTRESOURCE(ID_HINATA_NOTEPAD);
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
    HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(ID_HINATA_NOTEPAD));

    while (0 != (bRet = ::GetMessage(&msg, nullptr, 0, 0))) {
        if (-1 == bRet) {
            return -1;
        }

        if (TranslateAccelerator(hwnd, hAccel, &msg)) {
            continue;
        }

        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return msg.wParam;
}

int AskConfirmation(HWND hwnd)
{
    return MessageBox(hwnd, L"Really want to close hinata_notepad?", szAppName, MB_YESNO | MB_ICONQUESTION);
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

    case WM_INITMENUPOPUP:
    {
        if (lParam == 1) {
            EnableMenuItem((HMENU)wParam, IDM_EDIT_UNDO,
                            SendMessage(hwnd_edit, EM_CANUNDO, 0, 0) ? MF_ENABLED : MF_GRAYED);

            EnableMenuItem((HMENU)wParam, IDM_EDIT_PASTE,
                            IsClipboardFormatAvailable(CF_TEXT) ? MF_ENABLED : MF_GRAYED);

            int enable = 0, select = SendMessage(hwnd_edit, EM_GETSEL, 0, 0);

            if (HIWORD(select) == LOWORD(select)) {
                enable = MF_GRAYED;
            } else {
                enable = MF_ENABLED;
            }

            EnableMenuItem((HMENU)wParam, IDM_EDIT_CUT, enable);
            EnableMenuItem((HMENU)wParam, IDM_EDIT_COPY, enable);
            EnableMenuItem((HMENU)wParam, IDM_EDIT_CLEAR, enable);

            return 0;
        }

        break;
    }

    case WM_COMMAND:
    {
        if (lParam) {
            if (LOWORD(lParam) == ID_EDIT && (HIWORD(wParam) == EN_ERRSPACE || HIWORD(wParam) == EN_MAXTEXT)) {
                MessageBox(hwnd, L"Edit control out of space.", szAppName, MB_OK | MB_ICONSTOP);

                return 0;
            }
        } else {
            switch (LOWORD(wParam)) {
            case IDM_FILE_NEW:
            case IDM_FILE_OPEN:
            case IDM_FILE_SAVE:
            case IDM_FILE_SAVE_AS:
            case IDM_FILE_PRINT:
            {
                MessageBeep(0);

                return 0;
            }

            case IDM_APP_EXIT:
            {
                SendMessage(hwnd, WM_CLOSE, 0, 0);

                return 0;
            }

            case IDM_EDIT_UNDO:
            {
                SendMessage(hwnd_edit, WM_UNDO, 0, 0);

                return 0;

            }

            case IDM_EDIT_CUT:
            {
                SendMessage(hwnd_edit, WM_CUT, 0, 0);

                return 0;
            }

            case IDM_EDIT_COPY:
            {
                SendMessage(hwnd_edit, WM_COPY, 0, 0);

                return 0;
            }

            case IDM_EDIT_PASTE:
            {
                SendMessage(hwnd_edit, WM_PASTE, 0, 0);

                return 0;
            }

            case IDM_EDIT_CLEAR:
            {
                SendMessage(hwnd_edit, WM_CLEAR, 0, 0);

                return 0;
            }

            case IDM_EDIT_SELECT_ALL:
            {
                SendMessage(hwnd_edit, EM_SETSEL, 0, -1);

                return 0;
            }

            case IDM_HELP_HELP:
            {
                MessageBox(hwnd, L"Help not yet implemented!", szAppName, MB_OK | MB_ICONEXCLAMATION);

                return 0;
            }

            case IDM_APP_ABOUT:
            {
                MessageBox(hwnd, L"Hinata_Notepad (c) Charles Petzold, 1998", szAppName, MB_OK | MB_ICONINFORMATION);

                return 0;
            }

            default:
                break;
            }
        }

        return 0;
    }

    case WM_CLOSE:
    {
        if (IDYES == AskConfirmation(hwnd)) {
            DestroyWindow(hwnd);
        }

        return 0;
    }

    case WM_QUERYENDSESSION:
    {
        if (IDYES == AskConfirmation(hwnd)) {
            return 1;
        } else {
            return 0;
        }
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