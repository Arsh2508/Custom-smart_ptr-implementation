#include <iostream>
#include "Unique_ptr.hpp"
#include "Shared_ptr.hpp"

int main()
{
    Unique_ptr<int> unique{ new int(5) };

    std::cout<<"The value in custom unique_ptr is: "<<*unique<<std::endl;

    Shared_ptr<double> shared{ new double(4.2)};
    
    std::cout<<"The value in custom shared_ptr is: "<<*shared<<std::endl;
    
    Shared_ptr<int> From_unique(std::move(unique));
    std::cout<<"From_unique: "<< *From_unique<<std::endl;

    return 0;
}