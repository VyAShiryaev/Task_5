#ifndef WEAK_PTR_H
#define WEAK_PTR_H
#include <iostream>
#include "My_shared_ptr.h"
/*
Реализовать shared_ptr(1,4,7,10), 
weak_ptr(2,5,8), unique_ptr(3, 6,9), 
где в скобках указаны номера по списку - 
реализуем выпавший умный указатель в соответствии со списком
*/

template<class T>
class weak_ptr{
    private:
        T* _ptr = nullptr;
        T _element_type;
    public:
        //Конструкторы по умолчанию
        constexpr weak_ptr() noexcept;
        weak_ptr(const weak_ptr& r) noexcept {r=0;};
        template<class Y>
        weak_ptr(const weak_ptr<Y>& r) noexcept;
        template<class Y>
        weak_ptr(const My_shared_ptr<Y>& r) noexcept;
        weak_ptr(weak_ptr&& r) noexcept;
        template<class Y>
        weak_ptr(const weak_ptr<Y>&& r) noexcept;

        ~weak_ptr(){} //Деструктор

        weak_ptr& operator=(const weak_ptr& r)
        {
            r.swap(*this);
            return *this;
        }
        template <class Y>
        weak_ptr& operator=(const weak_ptr<Y>& r)
        {
            r.swap(*this);
            return *this;
        }
        template <class Y>
        weak_ptr& operator=(const My_shared_ptr<Y>& r)
        {
            r.swap(*this);
            return *this;
        }
        weak_ptr& operator=(weak_ptr&& r) noexcept
        {
            weak_ptr(std::move(r)).swap(*this);
            return *this;
        }
        template<class Y>
        weak_ptr& operator=(weak_ptr<Y>&& r) noexcept
        {
            weak_ptr(std::move(r)).swap(*this);
            return *this;
        }

        void reset() noexcept
        {
            *this = nullptr;
        }
        
        void swap(weak_ptr& r) noexcept
        {
            std::swap(*this, r);
        }

        long use_count() const noexcept
        {
            if (*this = nullptr)
                return 0;
            else
                return My_shared_ptr<T>.use_count();
            
        }
        
        bool expired() const noexcept
        {
            if (use_count() == 0)
            {
                return false;
            }
            else return true;
        }

        My_shared_ptr<T> lock() const noexcept
        {
            return expired() ? My_shared_ptr<T>() : My_shared_ptr<T>(*this);
        }

        // template<class Y>
        // bool owner_before(const weak_ptr<Y>& other) const noexcept
        // {
        //     if (*this < other)
        //         return true;
        //     else
        //         return false;
        // }

        // template<class Y>
        // bool owner_before(const std::shared_ptr<Y>& other) const noexcept
        // {
        //     if (*this < other)
        //         return true;
        //     else
        //         return false;
        // }

};

#endif