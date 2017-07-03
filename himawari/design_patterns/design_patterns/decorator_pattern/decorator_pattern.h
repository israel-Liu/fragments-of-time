#include <iostream>

class Component
{
public:
    virtual void DoJob() = 0;
};

class ConcreteComponent : public Component
{
public:
    void DoJob()
    {
        std::cout << "I am from Concrete Component-I am closed for modification." << std::endl;
    }
};

class AbstractDecorator : public Component
{
public:
    void SetTheComponent(Component* component)
    {
        component_ = component;
    }

    void DoJob()
    {
        if (component_) {
            component_->DoJob();
        }
    }

protected:
    Component* component_ = nullptr;
};

class ConcreteDecoratorA : public AbstractDecorator
{
public:
    void DoJob()
    {
        AbstractDecorator::DoJob();

        std::cout << "I am explicitly from ConcreteDecoratorA" << std::endl;
    }
};

class ConcreteDecoratorB : public AbstractDecorator
{
public:
    void DoJob()
    {
        AbstractDecorator::DoJob();

        std::cout << "I am explicitly from ConcreteDecoratorB" << std::endl;
    }
};