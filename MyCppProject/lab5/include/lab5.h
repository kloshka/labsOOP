#include <memory_resource>
#include <list>
#include <cstddef>
#include <iostream>
#include <memory>
#include <iterator>
#include <utility>
#include <string>

class ListMemoryResource : public std::pmr::memory_resource {
private:
    std::list<void*> allocated_blocks;

protected:
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        allocated_blocks.remove(p);
        ::operator delete(p);
        std::cout << "Deallocated " << bytes << " bytes\n";
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* ptr = ::operator new(bytes);
        allocated_blocks.push_back(ptr);
        std::cout << "Allocated " << bytes << " bytes\n";
        return ptr;
    }

public:
    ~ListMemoryResource() {
        for (void* ptr : allocated_blocks) {
            ::operator delete(ptr);
            std::cout << "Cleaned up memory\n";
        }
    }
};

template <typename T>
class DynamicArray {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;

private:
    allocator_type allocator;
    T* data;
    std::size_t capacity;
    std::size_t size;

    void expand_capacity() {
        std::size_t new_capacity = capacity ? capacity * 2 : 1;
        T* new_data = allocator.allocate(new_capacity);
        std::uninitialized_copy_n(data, size, new_data);
        allocator.deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
    }

public:
    explicit DynamicArray(allocator_type alloc = {})
        : allocator(alloc), data(nullptr), capacity(0), size(0) {}

    void pop_back() {
        if (size > 0) {
            allocator.destroy(data + size - 1);
            --size;
        }
    }

    void push_back(const T& value) {
        if (size == capacity) {
            expand_capacity();
        }
        allocator.construct(data + size, value);
        ++size;
    }

    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    std::size_t get_size() const { return size; }

    ~DynamicArray() {
        for (std::size_t i = 0; i < size; ++i) {
            allocator.destroy(data + i);
        }
        allocator.deallocate(data, capacity);
    }

    class Iterator {
    private:
        T* ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(T* ptr) : ptr(ptr) {}

        T& operator*() const { return *ptr; }
        T* operator->() { return ptr; }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.ptr == b.ptr;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.ptr != b.ptr;
        }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
};

// #endif
