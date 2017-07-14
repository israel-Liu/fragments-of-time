#include <iostream>

class Hindu
{
public:
    virtual ~Hindu() = default;
    virtual void PerformsHinduRitual() const = 0;
};

class HinduFemale : public Hindu
{
public:
    void PerformHinduRitual()
    {
        std::cout << "Hindu female" << std::endl;
    }
};

class Muslim
{
public:
    virtual ~Muslim() = default;
    virtual void PerformsMuslimRitual() const = 0;
};

class MuslimFemale : public Muslim
{
public:
    void PerformsMuslimRitual()
    {
        std::cout << "Muslim female" << std::endl;
    }
};

class HinduRitual
{
public:
    void CarryOutRitual(Hindu* hindu)
    {
        hindu->PerformsHinduRitual();
    }
};

class HinduAdapter
{
public:
    HinduAdapter(Muslim* muslim) : muslim_(muslim)
    {}

    void PerformsHinduRitual()
    {
        muslim_->PerformsMuslimRitual();
    }

private:
    Muslim* muslim_;
};