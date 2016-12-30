#pragma once

#ifndef noexcept
#define noexcept _NOEXCEPT
#endif

#include "utility/ref_count.h"

namespace hinata {

//ref_count ref_cnt;

template <typename T>
    class string // : public ref_count // String is a ref_count or has a ref_count, which one is better
    {
    public:
        // constructors
        string() = default;

        string(const string& rhs)
        {
            // use ref_count& operator=
            ref_cnt_ = rhs.ref_cnt_;
            data_ = rhs.data_;
            size_ = rhs.size_;
        }

        string(const T* str)
        {
            size_ = length(str);
            data_ = static_cast<T*>(::operator new(size_));
            copy(data_, str, size_);
        }

        string& operator=(const string& rhs)
        {
            if (*this == rhs) {
                return;
            }

            release();

            return (*this = string(rhs));
        }

        string& operator=(const T* str)
        {
            release();

            return (*this = string(str));
        }

        ~string()
        {
            release();
        }

    private:
        // Static function internal used
        static bool eq(const T& lhs, const T& rhs)
        {
            return (lhs == rhs);
        }

        static std::size_t length(const T* first)
        {
            std::size_t count;
            for (count = 0; !eq(*first, T()); ++first) {
                ++count;
            }
            return count;
        }

        static T* copy(T* dest, const T* src, std::size_t count)
        {   // copy [src, src + count) to [dest, ...)
            T* next = dest;
            for (; 0 < count; --count, ++next, ++src) {
                *next = *src;
            }
            return dest;
        }

    private:
        void release()
        {
            ref_cnt_.release();
            if (!ref_cnt_.get_count() && data_) {
                delete data_;
                data_ = nullptr;
                size_ = 0;
            }
        }

    private:
        T* data_                    = nullptr;
        std::size_t size_           = 0;
        // 引用成员被初始化为临时成员，临时成员在构造函数退出后就不再存在
        // ref_count& ref_cnt_      = ref_count();
        ref_count ref_cnt_          = ref_count();
    };
}