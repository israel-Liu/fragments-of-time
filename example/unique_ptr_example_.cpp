#include <string>
#include <iostream>

#include "unique_ptr/unique_ptr.h"

int main(int argc, char** argv)
{
    hinata::unique_ptr<std::string> up(new std::string("nico"));
    (*up)[0] = 'N';                 // replace first character
    up->append("lai");              // append some characters
    std::cout << *up << std::endl;  // print whole string

    return 0;
}