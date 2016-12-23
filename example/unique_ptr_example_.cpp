#include <string>
#include <iostream>

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
    hinata::ref_count<int> rc_i;
    hinata::ref_count<int> rc_i_copy(rc_i);

    hinata::ref_count<char> rc_c;
    hinata::ref_count<char> rc_c_copy;
    rc_c_copy = rc_c;

    return 0;
}