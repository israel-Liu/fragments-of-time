#include <iostream>

using namespace std;

class IChoice
{
public:
    virtual void MyChoice(string, string) = 0;
};

class FirstChoice : public IChoice
{
public:
    void MyChoice(string s1, string s2) override
    {
        cout << "You wanted to add the numbers." << endl;

    }
};

class SecondChoice : public IChoice
{
public:
    void MyChoice(string s1, string s2)
    {

    }
};

class Context
{
public:
    void SetChoice(IChoice* choice)
    {
        choice_= choice;
    }

    void ShowChoice(string s1, string s2)
    {
        choice_->MyChoice(s1, s2);
    }

private:
    IChoice* choice_;
};