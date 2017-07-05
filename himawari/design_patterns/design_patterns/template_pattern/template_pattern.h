#include <iostream>

class BasicEngineering
{
public:
    void Papers()
    {
        // Common Papers
        Math();
        SoftSkills();
        SpecialPaper();
    }

    void Math()
    {
        std::cout << "Mathematics" << std::endl;
    }

    void SoftSkills()
    {
        std::cout << "SoftSkills" << std::endl;
    }

    virtual void SpecialPaper() = 0;
};

class Electronics : public BasicEngineering
{
public:
    void SpecialPaper()
    {
        std::cout << "Object Oriented Programming" << std::endl;
    }
};

class ComputerScience : public BasicEngineering
{
public:
    void SpecialPaper()
    {
        std::cout << "Diaital Logic and Circuit Theory" << std::endl;
    }
};