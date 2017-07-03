#include <iostream>

#include "decorator_pattern/decorator_pattern.h"

int main(int agrc, char** agrv)
{
    std::cout << "***Decorator Pattern Demo***" << std::endl;
    Component* cc = new ConcreteComponent();

    AbstractDecorator* cda = new ConcreteDecoratorA();
    cda->SetTheComponent(cc);
    cda->DoJob();

    AbstractDecorator* cdb = new ConcreteDecoratorB();
    cdb->SetTheComponent(cc);
    cdb->DoJob();

    return 0;
}