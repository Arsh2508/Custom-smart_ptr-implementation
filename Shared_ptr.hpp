#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP
#include <iostream>
//#include "Weak_ptr.hpp"

template<typename T>
struct ControlBlock{
    ControlBlock(T* ptr)
        : reference_count{0}
        , weak_ref_count{0}
        , obj{ptr}
    {}
    size_t reference_count;
    size_t weak_ref_count;
    T* obj;
};

template<typename T>
class Shared_ptr{
public:
    explicit Shared_ptr(T* p = nullptr)
        : ptr{p}
        , controlBlock{new ControlBlock<T>(p)}
    {
        controlBlock->reference_count = 1;
    }

    Shared_ptr(const Shared_ptr& other)
        : ptr{other.ptr}
        , controlBlock{other.controlBlock}
    {
       controlBlock->reference_count++;
    }

    Shared_ptr& operator=(Shared_ptr rhs){
        swap(rhs);
        return *this;
    }

    Shared_ptr(Shared_ptr&& other) noexcept
        : ptr{other.ptr}
        , controlBlock{other.controlBlock}
    {
        other.ptr = nullptr;
        other.controlBlock = nullptr;
    }

    Shared_ptr& operator=(Shared_ptr&& rhs) noexcept{
        if(this == &rhs){
            return *this;
        }

        if(controlBlock){
            controlBlock->reference_count--;
            if(controlBlock->reference_count == 0){
                delete ptr;
                if(controlBlock->weak_ref_count == 0){
                    delete controlBlock;
                }
            }
        }

        ptr = rhs.ptr;
        controlBlock = rhs.controlBlock;

        rhs.ptr = nullptr;
        rhs.controlBlock = nullptr;

        return *this;
    }
    
    //Shared_ptr(const Weak_ptr& other);
    
    T& operator*(){
        return *ptr;
    }
    
    T* operator->(){
        return ptr;
    }
    
    void reset(T* p = nullptr) noexcept{
        delete ptr;
        ptr = p;
    }
    
    T* get() const noexcept{
        return ptr;
    }

    int use_count() const{
        return controlBlock->reference_count;
    }

    void swap(Shared_ptr& rhs) noexcept{
        std::swap(ptr, rhs.ptr);
        std::swap(controlBlock, rhs.controlBlock);
    }
    
    ~Shared_ptr(){
        if(controlBlock->reference_count == 1){
            delete ptr;
            if(controlBlock->weak_ref_count == 0){
                delete controlBlock;
            }
        }
        else{
            controlBlock->reference_count--;
        }
    }

private:
    T* ptr;
    ControlBlock<T>* controlBlock;
    
};

#endif