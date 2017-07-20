#include <windows.h>
#include <string>
#include <cassert>

size_t GetLength(const char* cc)
{
  return strlen(cc);
}

size_t GetLength(const wchar_t* cwc)
{
  return wcslen(cwc);
}

size_t Map2New(long code_page, const char* cc, int cb_of_cc, wchar_t* cwc, int cch_of_cwc)
{
    assert(cb_of_cc ? nullptr != cc : 1);
    assert(cch_of_cwc ? nullptr != cwc : 1);

    if (cb_of_cc == 0) {
        return 0;
    } else {
        enum { max_len = INT_MAX / sizeof(wchar_t) };
        cch_of_cwc = min(cch_of_cwc, max_len);
        int num = MultiByteToWideChar(code_page, 0, cc, cb_of_cc, cwc, cch_of_cwc);
        if (num == 0) {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
                memset(cwc, 0, cch_of_cwc);
                MultiByteToWideChar(code_page, 0, cc, cb_of_cc, cwc, cch_of_cwc);
                return GetLength(cwc);
            }

            return 0;
        }

        return cwc[num - 1] == 0 ? num - 1 : num;
    }
}

size_t Map2New(long code_page, const wchar_t* cwc, int cb_of_cwc, char* cc, int cch_of_cc)
{
    assert(cb_of_cwc ? nullptr != cwc : 1);
    assert(cch_of_cc ? nullptr != cc : 1);

    if (cb_of_cwc == 0) {
        return 0;
    } else {
        cch_of_cc = min(cch_of_cc, INT_MAX);
        int num = WideCharToMultiByte(code_page, 0, cwc, cb_of_cwc, cc, cch_of_cc, 0, 0);
        if (num == 0) {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
                memset(cc, 0, cch_of_cc);
                WideCharToMultiByte(code_page, 0, cwc, cb_of_cwc, cc, cch_of_cc, 0, 0);

                return GetLength(cc);
            }
        }

        return cc[num - 1] == 0 ? num - 1 : num;
    }
}

template <long code_page, typename T1, typename T2>
class A2BT : public std::basic_string<T2>
{
public:
  A2BT(const T1* pa)
  {
    Convert(pa, GetLength(pa));
  }

private:
  void Convert(const T1* pa, size_t len)
  {
    assert(len ? nullptr != pa : 1);
    size_t buff_size = sizeof(T2) > sizeof(T1) ? len : len * 4;
    resize(buff_size + 1);
    resize(Map2New(CP_UTF8, pa, len, &*begin(), buff_size));
  }
};