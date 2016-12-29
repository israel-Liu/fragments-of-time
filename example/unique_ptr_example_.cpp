#include <string>
#include <iostream>

#include "strings/string.h"
#include "unique_ptr/unique_ptr.h"
#include "utility/ref_count.h"

int main(int argc, char** argv)
{
    // unique_ptr
    hinata::unique_ptr<std::string> up(new std::string("nico"));
    (*up)[0] = 'N';                 // replace first character
    up->append("lai");              // append some characters
    std::cout << *up << std::endl;  // print whole string

    // ref_count
    hinata::ref_count rc_i;
    hinata::ref_count rc_i_copy(rc_i);

    hinata::ref_count rc_c;
    hinata::ref_count rc_c_copy;
    rc_c_copy = rc_c;

    // string
    wchar_t* s_n_c = new wchar_t[20];
    s_n_c = L"new_ten_char";
    std::basic_string<wchar_t> w_str(s_n_c);
    std::basic_string<wchar_t> w_str_eq;
    w_str_eq = w_str;
    std::cout << w_str.length() << std::endl;

    hinata::string<char> str_c("hinata::string<char>");
    hinata::string<wchar_t> str_wc(L"hinata::string<wchar_t>");
    hinata::string<char> str_c_eq(str_c);
    //std::cout << str_c << std::endl;

    return 0;
}