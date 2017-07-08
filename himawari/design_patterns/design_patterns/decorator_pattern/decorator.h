#include <string>
#include <iostream>

using namespace std;

class Car
{ // Our Abstract base class
public:
    virtual ~Car()
    {
        cout << "~Car()" << endl;
    }

    virtual string GetDescription()
    {
        return car_name_;
    }

    virtual double GetCost() = 0;

protected:
    string car_name_ = "Unknown Car";
};

class OptionsDecorator : public Car
{ // Decorator Base class
public:
    virtual ~OptionsDecorator()
    {
        cout << "~OptionsDecorator()" << endl;
    }

    virtual string GetDescription() = 0;
};

class CarModelA : public Car
{
public:
    CarModelA()
    {
        car_name_ = "CarModelA";
    }

    ~CarModelA()
    {
        cout << "~CarModelA" << endl;
    }

    virtual double GetCost()
    {
        return 31000.23;
    }
};

class Navigation : public OptionsDecorator
{
public:
    Navigation(Car* car)
    {
        car_ = car;
    }

    ~Navigation()
    {
        cout << "~Navigation()" << endl;
        delete car_;
    }

    string GetDescription()
    {
        return car_->GetDescription() + ", Navigation";
    }

    double GetCost()
    {
        return 300.56 + car_->GetCost();
    }

private:
    Car* car_;
};

class PremiumSoundSystem : public OptionsDecorator
{
public:
    PremiumSoundSystem(Car* car)
    {
        car_ = car;
    }

    string GetDescription()
    {
        return car_->GetDescription() + ", PremiumSoundSystem";
    }

    double GetCost()
    {
        return 0.30 + car_->GetCost();
    }

    ~PremiumSoundSystem()
    {
        cout << "~PremiumSoundSystem()" << endl;
        delete car_;
    }

private:
    Car* car_;
};

class ManualTransmission : public OptionsDecorator
{
public:
    ManualTransmission(Car* car)
    {
        car_ = car;
    }

    virtual ~ManualTransmission()
    {
        cout << "~ManualTransmission()" << endl;
        delete car_;
    }

    string GetDescription()
    {
        return car_->GetDescription() + ", ManualTransmission";
    }

    double GetCost()
    {
        return 0.30 + car_->GetCost();
    }

private:
    Car* car_;
};