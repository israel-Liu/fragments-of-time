#include <iostream>

using namespace std;

class StrategyInterface
{
public:
    virtual void execute() const = 0;
};

class ConcreteStrategyA : public StrategyInterface
{
public:
    void execute() const override
    {
        cout << "Called ConcreteStrategyA execute method" << endl;
    }
};

class ConcreteStrategyB : public StrategyInterface
{
public:
    void execute() const override
    {
        cout << "Called ConcreteStrategyB execute method" << endl;
    }
};

class ConcreteStrategyC : public StrategyInterface
{
public:
    void execute() const override
    {
        cout << "Called ConcreteStrategyC execute method" << endl;
    }
};

class Context
{
public:
    explicit Context(StrategyInterface* strategy) : strategy_(strategy)
    {}

    void set_strategy(StrategyInterface* strategy)
    {
        strategy_ = strategy;
    }

    void execute() const
    {
        strategy_->execute();
    }

private:
    StrategyInterface* strategy_;
};