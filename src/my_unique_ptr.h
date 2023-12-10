#ifndef MY_UNIQUE_PTR_H
#define MY_UNIQUE_PTR_H
#include <iostream>
/*
Реализовать shared_ptr(1,4,7,10), 
weak_ptr(2,5,8), unique_ptr(3, 6,9), 
где в скобках указаны номера по списку - 
реализуем выпавший умный указатель в соответствии со списком
*/
template<class T> struct default_delete
{
    constexpr default_delete() noexcept = default;
    constexpr default_delete(const default_delete&) = default;

    template<class U>
    constexpr default_delete(const default_delete<U>& d) noexcept;

    constexpr void operator() (T* ptr) const {delete ptr; }
};

template<class T, class Deleter=default_delete<T>>
class my_unique_ptr{
    private:
        T* _ptr = nullptr;
        T _element_type;
        Deleter _deleter_type = Deleter();
    public:
        //Конструкторы по умолчанию
        constexpr my_unique_ptr(std::nullptr_t) noexcept;
        explicit my_unique_ptr(T* p) noexcept: _ptr(p) {};
        my_unique_ptr(T* p, const Deleter& d1) noexcept: _ptr(p),_deleter_type(d1){};
        my_unique_ptr(my_unique_ptr&& u) noexcept
            :_ptr(u.release()),_deleter_type(u.get_deleter()){};
        template<class U, class E>
        my_unique_ptr(my_unique_ptr<U,E>&& u) noexcept
            :_ptr(u.release(),_deleter_type(std::forward<E>(u.get_deleter()))){};
        my_unique_ptr(const my_unique_ptr&) = delete;

        ~my_unique_ptr(){_deleter_type(_ptr);} //Деструктор

        my_unique_ptr& operator=(const my_unique_ptr& u) = delete;
        my_unique_ptr& operator=(my_unique_ptr&& u) noexcept
        {
            my_unique_ptr(std::move(u)).swap(*this);
            return *this;
        }

    // template<class U, class... Args>
    //     inline my_unique_ptr<U> make_unique(Args&&... args)
    //     {
    //         return my_unique_ptr<U>(new T(std::forward<Args>(args)...));
    //     };


        void reset(T* p) noexcept
        {
            _deleter_type(_ptr);
            _ptr = p;
        }
        
        T* release() noexcept 
        {
            auto old_ptr = _ptr;
            _ptr = nullptr;
            return old_ptr;
        }

        void swap(my_unique_ptr& u) noexcept
        {
            std::swap(_ptr, u._ptr);
        }

        T& operator*() const noexcept{return *_ptr;}
        T* operator->() const noexcept{return _ptr;}
        T* get() const noexcept {return _ptr;}
        Deleter get_deleter() const noexcept {return _deleter_type;}
        explicit operator bool(){return _ptr != nullptr;}
};

#endif