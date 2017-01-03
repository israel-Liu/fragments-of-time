#include <string>
#include <iostream>

#include "strings/string.h"
#include "unique_ptr/unique_ptr.h"
#include "utility/ref_count.h"

int main(int argc, char** argv)
{
    // string
    hinata::string<char> str_c("hinata::string<char>");
    hinata::string<char> str_c_eq(str_c);

    return 0;
}