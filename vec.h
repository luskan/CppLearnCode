//
// Created by marci_000 on 08.05.2016.
//

#ifndef TESTCPP1_VEC_H
#define TESTCPP1_VEC_H

#include <cstddef>
#include <memory>

template<typename T>
class vec {
public:
    vec() : elements(nullptr), first_free(nullptr), elements_end(nullptr){}

    ~vec() {
        free();
    }

    vec(const vec<T>& rop) : vec() {
        copyFrom(rop);
    }

    vec<T>& operator=(const vec<T>& rhs) {
        copyFrom(rhs);
    }

    T& operator[](std::size_t i) {
        return elements[i];
    }

    void push_back(const T& rop) {
        ensure_space();
        std::allocator<T> alloc;
        alloc.construct(first_free++, rop);
    }

    void free() {
        if (elements == nullptr)
            return;
        std::allocator<T> alloc;
        alloc.deallocate(elements, size());
        elements = nullptr;
        first_free=nullptr;
        elements_end = nullptr;
    }

    std::size_t size() const {
        return first_free - elements;
    }

    std::size_t capacity() const {
        return elements_end - elements;
    }

private:

    void ensure_space(){
        if ( elements == nullptr ) {
            std::allocator<T> alloc;
            const int initialSize = 16;
            elements = alloc.allocate(initialSize);
            first_free=elements;
            elements_end = elements + initialSize;
            return;
        }

        if (first_free == elements_end) {
            std::allocator<T> alloc;
            size_t org_size = size(); // == capacity
            T* new_buf = alloc.allocate(org_size*2);
            std::uninitialized_copy(elements, elements_end, new_buf);
            alloc.deallocate(elements, org_size);
            elements = new_buf;
            first_free=elements;
            elements_end = elements + org_size*2;
            return;
        }
    }


    void copyFrom(const vec<T>& rop) {
        free();
        std::allocator<T> alloc;
        std::size_t capsize = rop.capacity();
        T* new_buf = alloc.allocate(capsize);
        if (rop.size())
            std::uninitialized_copy(rop.elements, rop.first_free, new_buf);
        elements = new_buf;
        first_free=elements+rop.size();
        elements_end = elements + rop.capacity();
    }

    T* elements;
    T* first_free;
    T* elements_end;
};


#endif //TESTCPP1_VEC_H
