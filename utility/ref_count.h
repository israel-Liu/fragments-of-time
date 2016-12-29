#pragma once

#ifndef noexcept
#define noexcept _NOEXCEPT
#endif

namespace hinata {

class ref_count
{
public:
    ref_count()
        : cnt_(new std::size_t(1))
    {}

    ref_count(const ref_count& rc)
        : cnt_(rc.cnt_)
    {
        ++*cnt_;
    }

    ~ref_count()
    {
        if (--*cnt_ == 0) {
            delete cnt_;
        }

        cnt_ = nullptr;
    }

    // assignment
    ref_count& operator=(const ref_count& rhs)
    {
        ++*rhs.cnt_;

        if (--*cnt_ == 0) {
            delete cnt_;
        }

        cnt_ = rhs.cnt_;

        return *this;
    }

    // modifiers
    void swap(ref_count& rhs)
    {
        using std::swap;
        swap(cnt_, rhs.cnt_);
    }

    void add_ref()
    {
        ++*cnt_;
    }

    void release()
    {
        if (--*cnt_ == 0) {
            delete cnt_;
        }

        cnt_ = nullptr;
    }

private:
    std::size_t* cnt_ = nullptr;
};

} // namesapce hinata