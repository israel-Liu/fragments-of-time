#include <iostream>

#include "decorator_pattern/decorator_pattern.h"
#include "template_pattern/template_pattern.h"
//#include "observer_pattern.h"
#include "singleton/singleton_pattern.h"
#include "template_pattern/template.h"
#include "decorator_pattern/decorator.h"

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

    //std::cout << "***Template Pattern Demo***" << std::endl;
    //BasicEngineering* bs = new ComputerScience();
    //std::cout << "Computer Sc Papers:";
    //bs->Papers();
    //std::cout << std::endl;
    //bs = new Electronics();
    //std::cout << "Electronics Papers:";
    //bs->Papers();

    //ParaWeatherData* wdata = new ParaWeatherData;
    //CurrentConditionBoard* current_b = new CurrentConditionBoard(*wdata);
    //StatisticBoard* statistic_b = new StatisticBoard(*wdata);

    //wdata->SensorDataChange(10.2, 28.2, 1001);
    //wdata->SensorDataChange(12, 30.12, 1003);
    //wdata->SensorDataChange(10.2, 26, 806);
    //wdata->SensorDataChange(10.3, 35.9, 900);

    //wdata->RemoveOb(current_b);
    //wdata->SensorDataChange(100, 40, 1900);

    //delete statistic_b;
    //delete current_b;
    //delete wdata;

    //StringSingleton::Instance().SetString("StringSingleton");
    //std::cout << StringSingleton::Instance().GetString() << std::endl;

    //Game* game = nullptr;

    //Chess chess;
    //game = &chess;
    //for (unsigned i = 0; i < 100; ++i) {
    //    game->PlayOneGame();
    //}

    //Monopoly monopoly;
    //game = &monopoly;
    //for (unsigned i = 0; i < 100; ++i) {
    //    game->PlayOneGame();
    //}

    // Create our car that we want to buy
    Car* car = new CarModelA();
    cout << "Base model of " << car->GetDescription() << " costs $" << car->GetCost() << endl;

    // Who wants base model let's add some more features
    car = new Navigation(car);
    cout << car->GetDescription() << " will cost you $" << car->GetCost() << endl;

    car = new PremiumSoundSystem(car);
    car = new ManualTransmission(car);
    cout << car->GetDescription() << " will cost you $" << car->GetCost() << endl;

    // WARNING! Here we leak the CarModelA, Navigation and PremiumSoundSystem objects!
    // Either we delete them explicitly or rewrite the Decorators to take ownership
    // and delete their cars when destroyed.
    delete car;

    return 0;
}