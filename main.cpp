#include "my_unique_ptr.h"

void check(){


    my_unique_ptr<int> p1(new int(600));
    my_unique_ptr<int> p2(new int(200));
    my_unique_ptr<int> p3(new int(400));

    std::cout<<"Data p1: "<<*p1<<"\n";
    std::cout<<"Data p2: "<<*p2<<"\n";
    std::cout<<"Data p3: "<<*p3<<"\n";
    std::cout<<"p1: "<<((p1)?"unique ptr":"not unique ptr")<<"\n";
    std::cout<<"p2: "<<((p2)?"unique ptr":"not unique ptr")<<"\n";
    std::cout<<"p3: "<<((p3)?"unique ptr":"not unique ptr")<<"\n";

    p3.release();
    std::cout<<"Data p1: "<<*p1<<"\n";
    std::cout<<"Data p2: "<<*p2<<"\n";
    std::cout<<"p1: "<<((p1)?"unique ptr":"not unique ptr")<<"\n";
    std::cout<<"p2: "<<((p2)?"unique ptr":"not unique ptr")<<"\n";
    std::cout<<"p3: "<<((p3)?"unique ptr":"not unique ptr")<<"\n";

    p1.swap(p3);
    std::cout<<"p1: "<<((p1)?"unique ptr":"not unique ptr")<<"\n";
    std::cout<<"p2: "<<((p2)?"unique ptr":"not unique ptr")<<"\n";
    std::cout<<"p3: "<<((p3)?"unique ptr":"not unique ptr")<<"\n";
}
int main(){

    check();
    return 0;
}