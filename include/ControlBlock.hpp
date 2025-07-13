#ifndef CONTROL_BLOCK_HPP
#define CONTROL_BLOCK_HPP

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

#endif