#include <iostream>

#include "decorator_pattern/decorator_pattern.h"
#include "template_pattern/template_pattern.h"

int main(int agrc, char** agrv)
{
    //std::cout << "***Decorator Pattern Demo***" << std::endl;
    //Component* cc = new ConcreteComponent();

    //AbstractDecorator* cda = new ConcreteDecoratorA();
    //cda->SetTheComponent(cc);
    //cda->DoJob();

    //AbstractDecorator* cdb = new ConcreteDecoratorB();
    //cdb->SetTheComponent(cc);
    //cdb->DoJob();

    std::cout << "***Template Pattern Demo***" << std::endl;
    BasicEngineering* bs = new ComputerScience();
    std::cout << "Computer Sc Papers:";
    bs->Papers();
    std::cout << std::endl;
    bs = new Electronics();
    std::cout << "Electronics Papers:";
    bs->Papers();

    return 0;
}