#include <strsafe.h>

#include "resource.h"
#include "functions.h"

namespace {

// Global variables
const int ID_EDIT = 1;
static wchar_t szAppName[] = L"hinata_notepad";
static wchar_t* untitled = L"untitled";
static HWND hwnd_edit;
static HWND hwnd_modeless_dlg;

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

        if (hwnd_modeless_dlg != NULL && IsDialogMessage(hwnd_modeless_dlg, &msg)) {
            continue;
        }

        if (TranslateAccelerator(hwnd, hAccel, &msg)) {
            continue;
        }

        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Functions

inline int AskConfirmation(HWND hwnd)
{
    return MessageBox(hwnd, L"Really want to close hinata_notepad ?", szAppName, MB_YESNO | MB_ICONQUESTION);
}

DWORD ListFilesInDir()
{
    wchar_t szDir[] = L"D:\\Zoom\\trunk\\Client\\src\\application\\windows\\Images\\zm_emoji\\*";
    //StringCchCat(szDir, MAX_PATH, L"\\*");

    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile(szDir, &ffd);

    // List all the files in the directory with some info about them.
    LARGE_INTEGER filesize;
    wchar_t szFileName[MAX_PATH - 11] = { };
    wchar_t szFileNameList[MAX_PATH * 1000] = { };
    int cnt = 0;
    do {

        memset(szFileName, 0, sizeof(szFileName));

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            //_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
        } else {
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            //StringCbPrintf(szFileName, (MAX_PATH - 11) * sizeof(wchar_t),
            //               L"  %s   %ld bytes\r\n\r\n", ffd.cFileName, filesize.QuadPart);

            StringCbPrintf(szFileName, (MAX_PATH - 11) * sizeof(wchar_t), L"%s\r\n\r\n", ffd.cFileName);

            StringCbCat(szFileNameList, (MAX_PATH * 1000) * sizeof(wchar_t), szFileName);

            cnt++;

            SendMessage((HWND)0x000B1208, WM_SETTEXT, 0, (LPARAM)ffd.cFileName);
            SendMessage((HWND)0x000E0664, WM_COMMAND, MAKEWPARAM(1, BN_CLICKED), (LPARAM)0x00061922);
            //Sleep(10000);
        }
    } while (FindNextFile(hFind, &ffd) != 0);

    StringCbPrintf(szFileName, (MAX_PATH - 11) * sizeof(wchar_t), L"%d\r\n\r\n", cnt);

    StringCbCat(szFileNameList, (MAX_PATH * 1000) * sizeof(wchar_t), szFileName);

    SendMessage(hwnd_edit, WM_SETTEXT, 0, (LPARAM)szFileNameList);

    FindClose(hFind);

    return GetLastError();
}

DWORD GetTextFromEdit()
{
    return GetLastError();
}

inline short AskAboutSave(HWND hwnd, wchar_t* szTitleName)
{
    wchar_t szBuffer[64 + MAX_PATH] = {0};

    wsprintf(szBuffer, L"Save current changes in %s ?", szTitleName[0] ? szTitleName : untitled);

    int ret = MessageBox(hwnd, szBuffer, szAppName, MB_YESNOCANCEL | MB_ICONQUESTION);

    if (ret == IDYES) {
        if (!SendMessage(hwnd, WM_COMMAND, IDM_FILE_SAVE, 0)) {
            ret = IDCANCEL;
        }
    }

    return ret;
}

inline void DoCaption(HWND hwnd, wchar_t* szTitleName)
{
    wchar_t szCaption[64 + MAX_PATH];
    wsprintf(szCaption, TEXT("%s - %s"), szAppName, szTitleName[0] ? szTitleName : untitled);
    SetWindowText(hwnd, szCaption);
}

inline void OkMessage(HWND hwnd, wchar_t* szMessage, wchar_t* szTitleName)
{
    wchar_t szBuffer[64 + MAX_PATH];
    wsprintf(szBuffer, szMessage, szTitleName[0] ? szTitleName : untitled);
    MessageBox(hwnd, szBuffer, szAppName, MB_OK | MB_ICONEXCLAMATION);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool need_save = false;
    static wchar_t szFileName[MAX_PATH], szTitleName[MAX_PATH];
    static UINT msg_find_replace;
    static int off_set;

    switch (msg) {
    case WM_CREATE:
    {
        // Create the edit control child window
        hwnd_edit = CreateWindow(L"edit", nullptr, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER |
                                 ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0, hwnd,
                                 (HMENU)ID_EDIT, ((LPCREATESTRUCT)lParam)->hInstance, nullptr);

        SendMessage(hwnd_edit, EM_LIMITTEXT, 32000, 0L);

        // Initialize common dialog box stuff
        PopFileInitialize(hwnd);
        PopFontInitialize(hwnd_edit);

        msg_find_replace = RegisterWindowMessage(FINDMSGSTRING);

        DoCaption(hwnd, szTitleName);

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
        if (lParam && LOWORD(wParam) == ID_EDIT) {
            switch (HIWORD(wParam)) {
            case EN_UPDATE:
            {
                need_save = true;

                return 0;
            }

            case EN_ERRSPACE:
            case EN_MAXTEXT:
            {
                MessageBox(hwnd, L"Edit control out of space.", szAppName, MB_OK | MB_ICONSTOP);

                return 0;
            }

            default:
                break;
            }

            break;
        }

        switch (LOWORD(wParam)) {

        // Messages from File menu
        case IDM_FILE_NEW:
        {
            if (need_save && IDCANCEL == AskAboutSave(hwnd, szTitleName)) {
                return 0;
            }

            SetWindowText(hwnd_edit, L"\0");
            szFileName[0] = '\0';
            szTitleName[0] = '\0';
            DoCaption(hwnd, szTitleName);
            need_save = false;

            return 0;
        }

        case IDM_FILE_OPEN:
        {
            if (need_save && IDCANCEL == AskAboutSave(hwnd, szTitleName)) {
                return 0;
            }

            if (PopFileOpenDlg(hwnd, szFileName, szTitleName)) {
                if (!PopFileRead(hwnd_edit, szFileName)) {
                    OkMessage(hwnd, L"Could not read file %s !", szTitleName);
                    szFileName[0] = '\0';
                    szTitleName[0] = '\0';
                }
            }

            DoCaption(hwnd, szTitleName);

            need_save = false;

            return 0;
        }

        case IDM_FILE_SAVE:
        {
            if (szFileName[0]) {
                if (PopFileWrite(hwnd_edit, szFileName)) {
                    need_save = false;

                    return 1;
                } else {
                    OkMessage(hwnd, L"Could not write file %s", szTitleName);

                    return 0;
                }
            }
        }

        // Fall through
        case IDM_FILE_SAVE_AS:
        {
            if (PopFileSaveDlg(hwnd, szFileName, szTitleName)) {
                DoCaption(hwnd, szTitleName);

                if (PopFileWrite(hwnd_edit, szFileName)) {
                    need_save = false;

                    return 1;
                } else {
                    OkMessage(hwnd, L"Could not write file %s", szTitleName);

                    return 0;
                }
            }

            return 0;
        }

        case IDM_FILE_PRINT:
        {
            if (!PopPrntPrintFile(((LPCREATESTRUCT)lParam)->hInstance, hwnd, hwnd_edit, szTitleName)) {
                OkMessage(hwnd, L"Could not print file %s", szTitleName);
            }

            return 0;
        }

        case IDM_APP_EXIT:
        {
            SendMessage(hwnd, WM_CLOSE, 0, 0);

            return 0;
        }

        // Messages from Edit menu
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

        // Messages from Search menu
        case IDM_SEARCH_FIND:
        {
            SendMessage(hwnd_edit, EM_GETSEL, 0, (LPARAM)&off_set);

            if (PopFindValidFind()) {
                PopFindNextText(hwnd_edit, &off_set);
            } else {
                hwnd_modeless_dlg = PopFindFindDlg(hwnd);
            }

            return 0;
        }

        case IDM_SEARCH_REPLACE:
        {
            SendMessage(hwnd_edit, EM_GETSEL, 0, (LPARAM)&off_set);

            hwnd_modeless_dlg = PopFindReplaceDlg(hwnd);

            return 0;
        }

        // Messages from Format menu
        case IDM_FORMAT_FONT:
        {
            if (PopFontChooseFont(hwnd)) {
                PopFontSetFont(hwnd_edit);
            }

            return 0;
        }

        // Messages from Tool menu
        case IDM_LIST_FILES:
        {
            ListFilesInDir();

            return 0;
        }

        case IDM_SEARCH_TEXT:
        {
            GetTextFromEdit();

            return 0;
        }

        // Messages from Help menu
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
            // Process "Find-Replace" messages
            if (msg == msg_find_replace) {
                LPFINDREPLACE find_replace_ptr;
                find_replace_ptr = (LPFINDREPLACE)lParam;

                if (find_replace_ptr->Flags & FR_DIALOGTERM) {
                    hwnd_modeless_dlg = nullptr;
                }

                if (find_replace_ptr->Flags & FR_FINDNEXT) {
                    if (!PopFindFindText(hwnd_edit, &off_set, find_replace_ptr)) {
                        OkMessage(hwnd, L"Text not found !", L"\0");
                    }
                }

                if (find_replace_ptr->Flags & FR_REPLACE || find_replace_ptr->Flags & FR_REPLACEALL) {
                    if (!PopFindReplaceText(hwnd_edit, &off_set, find_replace_ptr)) {
                        OkMessage(hwnd, L"Text not found !", L"\0");
                    }
                }

                if (find_replace_ptr->Flags & FR_REPLACEALL) {
                    while (PopFindReplaceText(hwnd_edit, &off_set, find_replace_ptr));
                }

                return 0;
            }
            break;
        }

        return 0;
    }

    case WM_CLOSE:
    {
        if (!need_save || IDYES == AskConfirmation(hwnd)) {
            DestroyWindow(hwnd);
        }

        return 0;
    }

    case WM_QUERYENDSESSION:
    {
        if (!need_save || IDYES == AskConfirmation(hwnd)) {
            return 1;
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
        PopFontDeinitialize();
        ::PostQuitMessage(0);
        return 0;
    }

    default:
    {
        // Process "Find-Replace" messages
        break;
    }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}