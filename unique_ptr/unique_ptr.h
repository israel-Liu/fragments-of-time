#pragma once
#include <memory>

#ifndef noexcept
#define noexcept _NOEXCEPT
#endif

namespace hinata {

template <typename T>
    class default_delete
    {
    public:
        // Default constructor
        default_delete()
        {}

    template <class U>
        default_delete(const default_delete<U>&)
        {}

        void operator()(T* ptr) const
        {
            delete ptr;
        }

    private:

    };

template <typename T, typename D = default_delete<T>>
    class unique_ptr
    {
    public:
        typedef T   element_type;
        typedef D   deleter_type;

        unique_ptr() noexcept
        {}

        explicit unique_ptr(T* ptr) noexcept
            : ptr_(ptr), del_(deleter_type())
        {}

        unique_ptr(T* ptr, D del) noexcept
            : ptr_(ptr), del_(del)
        {}

        // destructor
        ~unique_ptr()
        {
            get_deleter()(ptr_);
        }

        //// assignment
        //unique_ptr& operator=(unique_ptr&& rhs)
        //{
        //    swap(*this, rhs);
        //    return *this;
        //}

        // observers
        T& operator*() noexcept
        {   // Requires: get() != nullptr.
            return *get();
        }

        T* operator->() noexcept
        {   // Requires: get() != nullptr.
            return get();
        }

        T* get() noexcept
        {
            return ptr_;
        }

        deleter_type& get_deleter() noexcept
        {
            return del_;
        }

        const deleter_type& get_deleter() const noexcept
        {
            return del_;
        }

        explicit operator bool() const noexcept
        {
            return get() != nullptr;
        }

        // modifiers
        void swap(unique_ptr& rhs) noexcept
        {
            using std::swap;
            swap(ptr_, rhs.ptr_);
            swap(del_, rhs.del_);
        }

        // disable copy from lvalue
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

    private:
        T*  ptr_;
        D   del_;
    };

} // namespace hinata