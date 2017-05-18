#include <iostream>

class Mutex
{

};

class Lock
{
public:
    Lock(Mutex& m)
        : mutex_(m)
    {}

    virtual ~Lock()
    {}

private:
    Mutex& mutex_;
};

class Singleton
{
public:
    static Singleton& GetInstance();

    int a_;

    virtual ~Singleton()
    {
        std::cout << "In Destructor" << std::endl;
    }

private:
    Singleton(int a)
        : a_(a)
    {
        std::cout << "In Constructor" << std::endl;
    }

    static Mutex mutex;

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton&) = delete;
};

Mutex Singleton::mutex;

Singleton& Singleton::GetInstance()
{
    Lock lock(mutex);

    std::cout << "Get Instance" << std::endl;

    // Initialized during first access
    static Singleton inst(1);

    return inst;
}

int main()
{
    Singleton& singleton = Singleton::GetInstance();
    std::cout << "The value of the singleton: " << singleton.a_ << std::endl;

    return 0;
}