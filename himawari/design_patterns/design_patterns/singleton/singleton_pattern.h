#include <string>

class StringSingleton
{
public:
    // Some accessor functions for the class, itself
    std::string GetString() const
    {
        return string_;
    }

    void SetString(const std::string& str)
    {
        string_ = str;
    }

    static StringSingleton& Instance()
    {
        static StringSingleton* instance = new StringSingleton;
        return *instance;
    }

private:
    StringSingleton()
    {}

    StringSingleton(const StringSingleton& old) = delete;
    const StringSingleton& operator=(const StringSingleton& old) = delete;
    ~StringSingleton();

private:
    std::string string_;
};