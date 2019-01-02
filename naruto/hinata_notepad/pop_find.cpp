#include <tchar.h>                        // for _tcsstr (strstr for Unicode & non-Unicode)

#include "functions.h"

const int MAX_STRING_LEN = 256;
static wchar_t szFindText[MAX_STRING_LEN];
static wchar_t szReplText[MAX_STRING_LEN];

HWND PopFindFindDlg(HWND hwnd)
{
    static FINDREPLACE fr;       // must be static for modeless dialog!!!

    fr.lStructSize = sizeof (FINDREPLACE);
    fr.hwndOwner = hwnd;
    fr.hInstance = NULL;
    fr.Flags = FR_HIDEUPDOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD;
    fr.lpstrFindWhat = szFindText;
    fr.lpstrReplaceWith = NULL;
    fr.wFindWhatLen = MAX_STRING_LEN;
    fr.wReplaceWithLen = 0;
    fr.lCustData = 0;
    fr.lpfnHook = NULL;
    fr.lpTemplateName = NULL;

    return FindText(&fr);
}

HWND PopFindReplaceDlg(HWND hwnd)
{
    static FINDREPLACE fr;       // must be static for modeless dialog!!!

    fr.lStructSize = sizeof (FINDREPLACE);
    fr.hwndOwner = hwnd;
    fr.hInstance = NULL;
    fr.Flags = FR_HIDEUPDOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD;
    fr.lpstrFindWhat = szFindText;
    fr.lpstrReplaceWith = szReplText;
    fr.wFindWhatLen = MAX_STRING_LEN;
    fr.wReplaceWithLen = MAX_STRING_LEN;
    fr.lCustData = 0;
    fr.lpfnHook = NULL;
    fr.lpTemplateName = NULL;

    return ReplaceText(&fr);
}

BOOL PopFindFindText(HWND hwnd_edit, int* search_offset, LPFINDREPLACE find_replace)
{
    // Read in the edit document
    int len = GetWindowTextLength(hwnd_edit);

    PTSTR  pstrDoc, pstrPos;
    if (NULL == (pstrDoc = (PTSTR)malloc((len + 1) * sizeof (TCHAR)))) {
        return FALSE;
    }

    GetWindowText(hwnd_edit, pstrDoc, len + 1);

    // Search the document for the find string
    pstrPos = _tcsstr(pstrDoc + *search_offset, find_replace->lpstrFindWhat);
    free(pstrDoc);

    // Return an error code if the string cannot be found
    if (pstrPos == NULL) {
        return FALSE;
    }

    // Find the position in the document and the new start offset
    int pos = pstrPos - pstrDoc;
    *search_offset = pos + lstrlen(find_replace->lpstrFindWhat);

    // Select the found text
    SendMessage(hwnd_edit, EM_SETSEL, pos, *search_offset);
    SendMessage(hwnd_edit, EM_SCROLLCARET, 0, 0);

    return TRUE;
}

BOOL PopFindReplaceText(HWND hwnd_eidt, int* search_offset, LPFINDREPLACE find_replace)
{
    // Find the text
    if (!PopFindFindText(hwnd_eidt, search_offset, find_replace)) {
        return FALSE;
    }

    // Replace it
    SendMessage(hwnd_eidt, EM_REPLACESEL, 0, (LPARAM)find_replace->lpstrReplaceWith);

    return TRUE;
}

BOOL PopFindNextText(HWND hwnd_eidt, int* search_offset)
{
    FINDREPLACE fr;

    fr.lpstrFindWhat = szFindText;

    return PopFindFindText(hwnd_eidt, search_offset, &fr);
}

BOOL PopFindValidFind(void)
{
    return *szFindText != '\0';
}
