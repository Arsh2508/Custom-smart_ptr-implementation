#include <iostream>
#include "Unique_ptr.hpp"
#include "Shared_ptr.hpp"
#include "Weak_ptr.hpp"

int main()
{
    Unique_ptr<int> unique{ new int(5) };

    std::cout<<"The value in custom unique_ptr is: "<<*unique<<std::endl;
    
    Weak_ptr<double> weak;

    Shared_ptr<double> shared1{new double(1.2)};

    {
        Shared_ptr<double> shared(shared1);
    
        std::cout<<"The value in custom shared_ptr is: "<<*shared<<std::endl;
        weak = shared;
    }

    Shared_ptr<double> ptr = weak.lock();

    std::cout<<*ptr<<std::endl;

    return 0;
}