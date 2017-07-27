#include <iostream>

class ICommand
{
public:
    virtual void Do() = 0;
};

class Receiver
{
public:
    void PerformUndo()
    {
        std::cout << "Executing - UndoCommand" << std::endl;
    }

    void PerformRedo()
    {
        std::cout << "Executing -RedoCommand" << std::endl;
    }
};

class UndoCommand : public ICommand
{
public:
    UndoCommand(Receiver* receiver)
        : receiver_(receiver)
    {}

    void Do()
    {
        receiver_->PerformUndo();
    }

private:
    Receiver* receiver_;
};

class RedoCommand : public ICommand
{
public:
    RedoCommand(Receiver* receiver)
        : receiver_(receiver)
    {}

    void Do()
    {
        receiver_->PerformRedo();
    }

private:
    Receiver* receiver_;
};

class Invoke
{
public:
    void ExecuteCommand(ICommand* cmd)
    {
        cmd_ = cmd;
        cmd_->Do();
    }

private:
    ICommand* cmd_;
};