#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP
#include "Shared_ptr.hpp"
#include "ControlBlock.hpp"

template<typename T>
class Weak_ptr{
public:

    Weak_ptr(const Weak_ptr& other) noexcept;

    

    template<typename S>
    Weak_ptr(const Shared_ptr<S>& p) noexcept;



private:    
    T* data;
    ControlBlock<>
};

#include "Weak_ptr.cpp"

#endif