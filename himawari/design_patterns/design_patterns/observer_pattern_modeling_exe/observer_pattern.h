#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// The Abstract Observer
class ObserverBoardInterface
{
public:
    virtual void Update(double a, double b, double c) = 0;
};

// Abstract Interface for Displays
class DisplayBoardInterface
{
public:
    virtual void Show() = 0;
};

// The Abstract Subject
class WeatherDataInterface
{
public:
    virtual void RegisterOb(ObserverBoardInterface* ob) = 0;
    virtual void RemoveOb(ObserverBoardInterface* ob) = 0;
    virtual void NotifyOb() = 0;
};

// The Concrete Subject
class ParaWeatherData : public WeatherDataInterface
{
public:
    void SensorDataChange(double a, double b, double c)
    {
        humidity_ = a;
        temperature_ = b;
        pressure_ = c;
        NotifyOb();
    }

    void RegisterOb(ObserverBoardInterface* ob)
    {
        obs_.push_back(ob);
    }

    void RemoveOb(ObserverBoardInterface* ob)
    {
        obs_.remove(ob);
    }

protected:
    void NotifyOb()
    {
        list<ObserverBoardInterface*>::iterator pos = obs_.begin();
        while (pos != obs_.end()) {
            static_cast<ObserverBoardInterface*>(*pos)->Update(humidity_, temperature_, pressure_);
            dynamic_cast<DisplayBoardInterface*>(*pos)->Show();
            ++pos;
        }
    }
private:
    double humidity_ = 0.0;
    double temperature_ = 0.0;
    double pressure_ = 0.0;
    list<ObserverBoardInterface*> obs_;
};

// A Concrete Observer
class CurrentConditionBoard : public ObserverBoardInterface, public DisplayBoardInterface
{
public:
    CurrentConditionBoard(ParaWeatherData& a) : data_(a)
    {
        data_.RegisterOb(this);
    }

    void Show()
    {
        cout << "______CurrentConditionBoard______" << endl;
        cout << "humidity:" << h_ << endl;
        cout << "temperature_" << t_ << endl;
        cout << "pressure:" << p_ << endl;
        cout << "_________________________________" << endl;
    }

    void Update(double h, double t, double p)
    {
        h_ = h;
        t_ = t;
        p_ = p;
    }

private:
    double h_;
    double t_;
    double p_;
    ParaWeatherData& data_;
};

// A Concrete Observer
class StatisticBoard : public ObserverBoardInterface, public DisplayBoardInterface
{
public:
    StatisticBoard(ParaWeatherData& a) : data_(a)
    {
        data_.RegisterOb(this);
    }

    void Show()
    {
        cout << "______StatisticBoard______" << endl;
        cout << "lowest temperature: " << mint_ << endl;
        cout << "highest temperature: " << maxt_ << endl;
        cout << "average temperature: " << avet_ << endl;
        cout << "__________________________" << endl;
    }

    void Update(double h, double t, double p)
    {
        ++count_;
        if (t > maxt_) {
            maxt_ = t;
        }

        if (t < mint_) {
            mint_ = t;
        }

        avet_ = (avet_ * (count_ - 1) + t) / count_;
    }

private:
    double maxt_ = -1000;
    double mint_ = 1000;
    double avet_ = 0.0;
    int count_ = 0.0;
    ParaWeatherData& data_;
};