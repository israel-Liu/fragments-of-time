#pragma once
#include <memory>

namespace hinata {

template <typename T, typename D> // D = default_delete<T>
    class unique_ptr : public std::_Unique_ptr_base<T, D>
    {
    public:
        typedef unique_ptr<T, D> Myt_;
        // 暂时用VS提供的，日后在写两个类，或者一个加一个内部 pointer
        // 也可以把 pointer 写到这里来 // 暂时简单点，防止脑袋烧爆
        typedef _Unique_ptr_base<T, D> Mybase_;
        // 下划线风格有时候好脑残，
        typedef typename Mybase_::pointer pointer_;
        // 暂时不用先放这里 // 轮子不好造啊
        typedef T element_type_;
        typedef D deleter_type_;

        using Mybase_::get_deleter;

        // constructors // 暂时就先提供2个
        constexpr unique_ptr() noexcept
            : Mybase_(pointer_())
        {	// constexpr(常量表达式)用于修饰类的构造函数，
            // 即保证如果提供给该构造函数的参数都是constexpr，
            // 那么产生的对象中的所有成员都会是constexpr，
            // 该对象也就是constexpr对象了，可用于各种只能使用constexpr的场合。
            // note，constexpr构造函数必须有一个空的函数体，即所有成员变量的初始化都放到初始化列表中。
            static_assert(!is_pointer<D>::value,
                "unique_ptr constructed with null deleter pointer")
        }

        explicit unique_ptr(pointer_ p) noexcept
            : Mybase_(pointer_())
        {	// null pointer construct
            static_assert(!is_pointer<D>::value,
                "unique_ptr constructed with null deleter pointer")
        }

        unique_ptr(unique_ptr&& right) _NOEXCEPT
            : Mybase_(right.release(),
            ::std::forward<_Dx>(right.get_deleter()))
        {	// construct by moving _Right
        }

        // destructor
        ~unique_ptr() noexcept
        {
            if (get() != pointer_())
            this->get_deleter()(get());
        }

        // assignment // assign by moving 省略
        // 暂时就提供一个 赋空值的
        Myt_& operator=(nullptr_t)
        {
            reset();
            return (*this);
        }

        // observers
        pointer_ operator->() const noexcept
        {	// return pointer to class object
            return pointer_();
        }

        pointer_ get() const noexcept
        {	// return pointer to object
            return (this->_Myptr());
        }

        explicit operator bool() const noexcept
        {	// test for non-null pointer
            return (get() != pointer());
        }

        // 先使用基类的，应该自己练习写一个的
        //// Returns: A reference to the stored deleter.
        //deleter_type& get_deleter() noexcept;
        //const deleter_type& get_deleter() const noexcept;

        // modifiers
        pointer_ release() noexcept
        {	// yield ownership of pointer
            pointer_ ans = get();
            this->_Myptr() = pointer();
            return (ans);
        }

        void reset(pointer_ ptr = pointer_()) noexcept
        {	// establish new pointer
            pointer old = get();
            this->_Myptr() = ptr;
            if (old != pointer_())
                this->get_deleter()(old);
        }

        // void swap(unique_ptr& u) noexcept;

        // disable copy from lvalue
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

    private:

    };

// operator == , != , > , >= , < , <=
template <class T1, class D1, class T2, class D2>
    bool operator==(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y)
    {
        return false;
    }

} // namespace hinata