#ifndef PTR_H
#define PTR_H
#include <iostream>
/*
Реализовать shared_ptr(1,4,7,10), 
weak_ptr(2,5,8), unique_ptr(3, 6,9), 
где в скобках указаны номера по списку - 
реализуем выпавший умный указатель в соответствии со списком
*/

class S_Ptr{
    private:
        int* _data;
        unsigned int* _count = 0;
        void predestruct(){//оптимизировать
        (*_count)--;
        if(_count == 0)
        {
            std::cout <<*_count<< "Memory dealocated\n";
            delete _data;
            delete _count;
        }
        };

    public:
    S_Ptr(int* data){

        _data = data;
        _count = new unsigned int(1);
    }
    S_Ptr(S_Ptr& r){
        this->_data = r._data;
        this->_count = r._count;
        (*_count)++;

    }
    ~S_Ptr(){
        std::cout << this->use_count();
        predestruct();
       // _count--;

    }

    int& operator* (){
        return *_data;
    }
    int* operator-> (){
        return _data;
    }
    
    S_Ptr& operator=(const S_Ptr& r) noexcept
    {
        predestruct();
        this->_data = r._data;
        this->_count = r._count;
        (*_count)++;

        return *this;
    }
    S_Ptr& operator=(S_Ptr&& r) noexcept
    {
        predestruct();
        this->_data = std::move(r._data);
        this->_count = std::move(r._count);
        r._data = nullptr;
        r._count = nullptr;
        return *this;
    }

    void swap (S_Ptr& r ){

    }

    unsigned int use_count() const
    {
        return *_count;
    }


};
#endif