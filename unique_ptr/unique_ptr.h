#pragma once
#include <memory>

namespace hinata {

template <typename T>
    class default_delete
    {
    public:
        // Default constructor
        default_delete()
        {

        }

    template <class U>
        default_delete(const default_delete<U>&)
        {

        }

        void operator()(T* ptr) const
        {
            delete ptr;
        }
    private:

    };

template <typename T, typename D = default_delete<T>> // D = default_delete<T>
    class unique_ptr
    {
    public:
        unique_ptr()
        {

        }
        explicit unique_ptr(T* ptr)
        {
            ptr_ = ptr;
        }

        // destructor
        ~unique_ptr()
        {
            delete ptr_;
        }

        // disable copy from lvalue
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

    private:
        T* ptr_;
    };

} // namespace hinata