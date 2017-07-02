#include <windows.h>

class Singleton
{
public:
    virtual ~Singleton()
    {
        if (singleton_) {
            delete singleton_;
            singleton_ = nullptr;
        }
    }

    static Singleton* GetSingleton()
    {
        EnterCriticalSection(&cs);

        if (singleton_) {
            singleton_ = new Singleton();
        }

        return singleton_;

        LeaveCriticalSection(&cs);
    }

    static Singleton* singleton_;

private:
    Singleton()
    {
        InitializeCriticalSection(&cs);
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton& other) = delete;

private:
    static CRITICAL_SECTION cs;
};

Singleton* Singleton::singleton_ = nullptr;