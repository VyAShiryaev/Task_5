#ifndef MY_SHARED_PTR_HPP
#define MY_SHARED_PTR_HPP
#include <iostream>

template <class Type>
class My_shared_ptr
{
private:
    Type* _data;
    unsigned int* _count;

    void preDestruct()
    {
        if (!_count)
        {
            return;
        }
        if (--(*_count) == 0)
        {
            delete _data;
            delete _count;
        }
        this->_data = nullptr;
        this->_count = nullptr;
    };
public:
    My_shared_ptr()
    {
        this->_data = nullptr;
        this->_count = nullptr;
    };

    My_shared_ptr(Type* ptr)
    {
        this->_data = ptr;
        this->_count = new unsigned int(1);
    };

    My_shared_ptr(const My_shared_ptr& r)
    {
        this->_data = r._data;
        this->_count = r._count;
        ++(*_count);
    };

    ~My_shared_ptr()
    {
        preDestruct();
    };

    My_shared_ptr& operator=(const My_shared_ptr& r) noexcept
    {
        if (this != &r)
        {
        //preDestruct();
        reset();
        this->_data = r._data;
        this->_count = r._count;
        ++(*_count);
        }
        return *this;
    };

    My_shared_ptr& operator=(My_shared_ptr&& r) noexcept
    {
        if (this != &r)
        {
        //preDestruct();
        reset();
        this->_data = r._data;
        this->_count = r._count;
        r._data = nullptr;
        r._count = nullptr;
        }
        return *this;
    };

    void reset()
    {
        if (_count && --(*_count) == 0) // проверка на последний указатель
        {
            delete _data;
            delete _count;
        }
        _data = nullptr;
        _count = nullptr;  
    };

    void reset(Type* ptr)
    {
        *this = std::move(My_shared_ptr<Type>(ptr));
    };

    void swap(My_shared_ptr& r)
    {
        std::swap(this->_data, r._data);
        std::swap(this->_count, r._count);
    };

    Type* get() const noexcept
    {
        return _data;
    };

    Type& operator*() const noexcept
    {
        return *_data;
    };

    Type* operator->() const noexcept
    {
        return _data;
    };

    Type& operator[](std::size_t index)  // оператор индексации
    {
        if (_data && index >= 0) // проверка на ненулевой указкатель и индекс >= 0
        {
            return _data[index];
        } 
        else 
        {
            throw std::out_of_range("Index out of bounds");
        }
    };

    unsigned int use_count()
    {
        return (*_count);
    };

    explicit operator bool() const noexcept
    {
        if (_data != nullptr)
        {
            std::cout << "valid pointer.";
            return true;
        }
        else
        {
            std::cout << "not valid pointer.";
            return false;
        }
    };

    bool owner_before(const My_shared_ptr<Type>& r) const noexcept
    {
        return this->_count < r._count; // true - текущий объект владеет данными до объекта r
    };

    template <typename... Args>
    static My_shared_ptr<Type> make_shared(Args&&... args) 
    {
        return My_shared_ptr<Type>(new Type(std::forward<Args>(args)...));
    };
};

#endif // MY_SHARED_PTR_HPP