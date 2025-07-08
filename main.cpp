#include <iostream>
#include "Unique_ptr.hpp"

int main()
{
    Unique_ptr<int> p = new int(5);

    std::cout<<"The value of custom unique_ptr is: "<<*p<<std::endl;

    return 0;
}