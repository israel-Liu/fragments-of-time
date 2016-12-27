#pragma once

#ifndef noexcept
#define noexcept _NOEXCEPT
#endif

namespace hinata {

//template <typename T>
//    std::size_t length(const T* str)
//    {
//        return 16 / sizeof(T) < 1 ? 1 : 16 / sizeof(T)
//    }
//
//template <>
//    std::size_t length(const char* str)
//    {
//        return strlen(str);
//    }
//
//template <>
//    std::size_t length(const wchar_t* str)
//    {
//        return wcslen(str);
//    }

template <typename T>
    class string
    {
    public:
        // constructors
        string() = default;

        string(const string& rhs)
        {
            data_ = rhs.data_;
        }

        string(const T* str)
        {
            size_ = length(str);
            data_ = static_cast<T*>(::operator new(size_));
            copy(data_, str, size_);
        }

        ~string()
        {
            if (!data_) {
                delete data_;
            }
            data_ = nullptr;
        }

        // 内部使用 static 函数
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