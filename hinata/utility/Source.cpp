#include "convert_character_type.h"

int main()
{
    int a = 1;
    int* b = &a;
    int*& c = b;

    char buff_cc[100] = "七月流火";
    const wchar_t* out_cc = A2BT<CP_UTF8, char, wchar_t>(buff_cc).c_str();

    wchar_t buff_wc[100] = L"八月流火";
    const char* out_wc = A2BT<CP_UTF8, wchar_t, char>(buff_wc).c_str();

    return 0;
}