#pragma once

#ifndef noexcept
#define noexcept _NOEXCEPT
#endif

namespace hinata {

template <typename T>
    class string
    {
    public:
        // constructors
        string() = default;

        string(const string& rhs)
        {
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

            return (*this = string(rhs));
        }

        string& operator=(const T* str)
        {
            return (*this = string(str));
        }

        ~string()
        {
            if (!data_) {
                delete data_;
            }
            data_ = nullptr;
        }

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
        T* data_            = nullptr;
        std::size_t size_   = 0;
    };
}