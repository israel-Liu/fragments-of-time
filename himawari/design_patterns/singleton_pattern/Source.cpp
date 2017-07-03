#include <iostream>

#include "singleton.h"

int main()
{
    Singleton* s1 = Singleton::GetSingleton();
    Singleton* s2 = Singleton::GetSingleton();

    if (s1 == s2) {
        std::cout << "s1 and s2 are same instance" << std::endl;
    }

    return 0;
}