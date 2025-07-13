#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

template<typename T>
class Unique_ptr{
public:

    explicit Unique_ptr(T* p = nullptr)
        : ptr{p}
    {}

    ~Unique_ptr() {delete ptr;} 

    Unique_ptr(const Unique_ptr&) = delete;
    Unique_ptr& operator=(const Unique_ptr&) = delete;
    
    Unique_ptr(Unique_ptr&& other) noexcept
         : ptr{other.ptr}
    {
        other.ptr = nullptr;
    }

    Unique_ptr& operator=(Unique_ptr&& rhs) noexcept
    {
        if(this == &rhs){
            return *this;
        }

        delete ptr;
        ptr = rhs.ptr;
        rhs.ptr = nullptr;

        return *this;
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

    void reset(T* p = nullptr) noexcept
    {
        delete ptr;
        ptr = p;
    }

    T* release() noexcept
    {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T* get() const noexcept
    {
        return ptr;
    }

private:
    T* ptr;
};

#endif


