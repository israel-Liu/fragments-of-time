#pragma once

#ifndef noexcept
#define noexcept _NOEXCEPT
#endif

namespace hinata {

class ref_count
{
public:
    ref_count()
    {}

    explicit ref_count(std::size_t*)
    {}
    
    ref_count(const ref_count& rc)
    {
        *cnt_ = ++*rc.cnt_;
    }

    ~ref_count()
    {}

    // assignment
    ref_count& operator=(const ref_count& rhs)
    {   // if (*this == rhs) { return; }
        ++*rhs.cnt_;

        release();

        cnt_ = rhs.cnt_;

        return *this;
    }

    // modifiers
    void swap(ref_count& rhs)
    {
        using std::swap;
        swap(cnt_, rhs.cnt_);
    }

    void release()
    {
        if (cnt_ && --*cnt_ == 0) {
            delete cnt_;
            cnt_ = nullptr;
        }
    }

    std::size_t* get_count()
    {
        return cnt_;
    }

private:
    std::size_t* cnt_ = new std::size_t(1);    // InterlockedIncrement
};

} // namesapce hinata
