#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP
#include <iostream>
#include <memory>
#include "ControlBlock.hpp"
#include "Weak_ptr.hpp" 

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

    template<typename U>
    Shared_ptr(Unique_ptr<U>&& other)
        : ptr{other.release()}
        , controlBlock{ ptr ? new ControlBlock<U>(ptr) : nullptr}
    {
        if(controlBlock){
            controlBlock->reference_count = 1;
        }
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
    
    template<typename W>
    Shared_ptr(const Weak_ptr<W>& other)
        : controlBlock{other.get_control_block()}
    {
        if(!controlBlock || controlBlock->reference_count == 0){
            throw std::bad_weak_ptr{};
        }
        ptr = other.get_data();
        controlBlock->reference_count++;
    }
    
    T& operator*(){
        return *ptr;
    }
    
    T* operator->(){
        return ptr;
    }

    const T& operator*() const {
        return *ptr;
    }
    
    const T* operator->() const {
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

    ControlBlock<T>* get_control_block() const noexcept {
        return controlBlock;
    }

private:
    T* ptr;
    ControlBlock<T>* controlBlock;
    
};

#endif