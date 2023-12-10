#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <iostream>
/*
Реализовать shared_ptr(1,4,7,10), 
weak_ptr(2,5,8), unique_ptr(3, 6,9), 
где в скобках указаны номера по списку - 
реализуем выпавший умный указатель в соответствии со списком
*/
template<class T>
class my_unique_ptr{
    private:
        T* _ptr;
    public:

    my_unique_ptr():_ptr(nullptr){}

    explicit my_unique_ptr(T* _ptr): _ptr(_ptr){}

    ~my_unique_ptr()
    {
        delete _ptr;
    }

    T& operator* ()          const {return *_ptr;}
    T* operator-> ()         const {return _ptr;}
    T* get()                 const {return _ptr;}
    explicit operator bool() const {return _ptr;}
    
    my_unique_ptr& operator=(const my_unique_ptr& r) noexcept = delete;

    my_unique_ptr& operator=(my_unique_ptr&& r) noexcept
    {
        r.swap(*this);
        return *this;
    }

    void swap (my_unique_ptr& r) noexcept 
    {
        std::swap(_ptr, r._ptr);
    }

    T* release() noexcept
    {
        T* res = nullptr;
        std::swap(res, _ptr);
        return res;
    }

    void reset()
    {
        T* tmp = release();
        delete tmp;
    }

};
template<class T>
void swap(my_unique_ptr<T>& lhs, my_unique_ptr<T>& rhs)
{
    lhs.swap(rhs);
}
#endif