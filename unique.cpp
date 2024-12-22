// Use any tools at your disposal to understand what std::unique_ptr does and write your own version of it.

#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
class MyUniquePointer
{
public:
    /** 
     * Constructor which is by default a nullptr
    */
    MyUniquePointer(T* ptr = nullptr) : ptr_here(ptr) {}

    /**
     * Destructor deallocates the stored pointer
    */
    ~MyUniquePointer() { delete ptr_here; ptr_here = nullptr; }

    /**
     * Copy constructor and assignment operator are deleted
     */
    MyUniquePointer(const MyUniquePointer&) = delete;
    MyUniquePointer& operator=(const MyUniquePointer&) = delete;

    /**
     * Move constructor
     */
    MyUniquePointer(MyUniquePointer&& other) noexcept
    {
        ptr_here = other.ptr_here;
        other.ptr_here = nullptr;
    }

    /**
     * Move assignment operator
     */
    MyUniquePointer& operator=(MyUniquePointer&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr_here;
            ptr_here = other.ptr_here;
            other.ptr_here = nullptr;
        }
        return *this;
    }

    /**
     * Dereference the stored pointer
     */
    T& operator*() const { return *ptr_here; }

    /**
     * @brief Get the address of the stored pointer
     */
    T* get() const { return ptr_here; }


    /**
     * @brief Reset the stored pointer
     * Deallocate it and assign it to nullptr
     */
    void reset(T* ptr = nullptr)
    {
        delete ptr_here;
        ptr_here = ptr;
    }

    /**
     * @brief Release the stored pointer
     * Assign it to nullptr and return it
     */
    T* release()
    {
        T* temp = ptr_here;
        ptr_here = nullptr;
        return temp;
    }

private:
    T* ptr_here;
};