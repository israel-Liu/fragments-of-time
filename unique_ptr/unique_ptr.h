#pragma once
#include <memory>

namespace hinata {

template <typename T, typename D> // D = default_delete<T>
    class unique_ptr : public std::_Unique_ptr_base<T, D>
    {
    public:
        typedef unique_ptr<T, D> Myt_;
        // ��ʱ��VS�ṩ�ģ��պ���д�����࣬����һ����һ���ڲ� pointer
        // Ҳ���԰� pointer д�������� // ��ʱ�򵥵㣬��ֹ�Դ��ձ�
        typedef _Unique_ptr_base<T, D> Mybase_;
        // �»��߷����ʱ����ԲУ�
        typedef typename Mybase_::pointer pointer_;
        // ��ʱ�����ȷ����� // ���Ӳ����찡
        typedef T element_type_;
        typedef D deleter_type_;

        using Mybase_::get_deleter;

        // constructors // ��ʱ�����ṩ2��
        constexpr unique_ptr() noexcept
            : Mybase_(pointer_())
        {	// constexpr(�������ʽ)����������Ĺ��캯����
            // ����֤����ṩ���ù��캯���Ĳ�������constexpr��
            // ��ô�����Ķ����е����г�Ա������constexpr��
            // �ö���Ҳ����constexpr�����ˣ������ڸ���ֻ��ʹ��constexpr�ĳ��ϡ�
            // note��constexpr���캯��������һ���յĺ����壬�����г�Ա�����ĳ�ʼ�����ŵ���ʼ���б��С�
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

        // assignment // assign by moving ʡ��
        // ��ʱ���ṩһ�� ����ֵ��
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

        // ��ʹ�û���ģ�Ӧ���Լ���ϰдһ����
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