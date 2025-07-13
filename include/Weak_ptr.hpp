#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP
#include "ControlBlock.hpp"

template <typename T>
class Shared_ptr;

template<typename T>
class Weak_ptr{
public:

    Weak_ptr() = default;  

    Weak_ptr(const Weak_ptr& other) noexcept
        : controlBlock{other.controlBlock} 
    {
        if(controlBlock){
            controlBlock->weak_ref_count++;
        }
    }

    template<typename S> 
    Weak_ptr(const Shared_ptr<S>& p) noexcept
        : controlBlock{p.get_control_block()}
    {
        if(controlBlock){
            controlBlock->weak_ref_count++;
        }
    }

    Weak_ptr(Weak_ptr&& other) noexcept
        : controlBlock{other.controlBlock}
    {
        other.controlBlock = nullptr;
    }

    ~Weak_ptr()
    {
        if(controlBlock) { 
            controlBlock->weak_ref_count--;
        
            if(controlBlock->weak_ref_count == 0 && controlBlock->reference_count == 0){
                delete controlBlock;
            }

        }
    }

    Weak_ptr& operator=(const Weak_ptr& rhs) noexcept
    {
        if(this != &rhs){
            Weak_ptr<T> tmp(rhs);
            swap(tmp);
        }
        return *this;
    }

    Weak_ptr& operator=(Weak_ptr&& rhs) noexcept
    {
        if(this == &rhs){
            return *this;
        }

        if(controlBlock){
            controlBlock->weak_ref_count--;
            if(controlBlock->weak_ref_count == 0 && controlBlock->reference_count == 0){
                delete controlBlock;
            }
        }

        controlBlock = rhs.controlBlock;

        rhs.controlBlock = nullptr;

        return *this;
    }

    template<typename S> 
    Weak_ptr& operator=(const Shared_ptr<S>& rhs) noexcept
    {
        Weak_ptr<T> tmp(rhs);
        swap(tmp);

        return *this;
    }

    void swap(Weak_ptr& rhs) noexcept
    {
        std::swap(controlBlock, rhs.controlBlock);
    }

    size_t use_count() const noexcept
    {
        if(controlBlock){
            return controlBlock->reference_count;
        }
        return 0;
    }

    bool expired() const noexcept
    {
        if(!controlBlock || controlBlock->reference_count == 0){
            return true;
        }
        return false;
    }

    Shared_ptr<T> lock() const noexcept
    {
        return expired() ? Shared_ptr<T>() : Shared_ptr<T>(*this);
    }

    ControlBlock<T>* get_control_block() const noexcept
    {
        return controlBlock;
    }

    T* get_data() const noexcept
    {
        if(controlBlock){
            return controlBlock->obj;
        }
        return nullptr;
    }
    

private:    
    ControlBlock<T>* controlBlock = nullptr;
};

#endif