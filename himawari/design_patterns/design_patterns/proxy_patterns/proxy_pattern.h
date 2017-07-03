#include <iostream>

class Subject
{
public:
    virtual void DoSomeWork() = 0;
};

class ConcreteSubject : public Subject
{
public:
    void DoSomeWork()
    {
        std::cout << "In Concrete Subject" << std::endl;
    }
};

class ProxySubject : public Subject
{
public:
    void DoSomeWork()
    {
        std::cout << "Proxy call happening now" << std::endl;

        if (!cs_) {
            cs_ = new ConcreteSubject();
        }

        cs_->DoSomeWork();
    }

private:
    ConcreteSubject* cs_ = nullptr;
};