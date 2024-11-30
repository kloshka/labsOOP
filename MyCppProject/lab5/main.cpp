#include <memory_resource>  
#include <iostream>
#include "lab5.h"  

struct MyStruct {
    int id;
    std::string name;
};

int main() {
    ListMemoryResource memory_resource;

    std::pmr::polymorphic_allocator<int> int_allocator(&memory_resource);
    DynamicArray<int> int_array(int_allocator);

    int_array.push_back(10);
    int_array.push_back(20);
    int_array.push_back(30);

    std::cout << "DynamicArray<int> contents:\n";
    for (const auto& elem : int_array) {
        std::cout << elem << '\n';
    }

    std::pmr::polymorphic_allocator<MyStruct> struct_allocator(&memory_resource);
    DynamicArray<MyStruct> struct_array(struct_allocator);

    struct_array.push_back(MyStruct{1, "Alice"});
    struct_array.push_back(MyStruct{2, "Bob"});

    std::cout << "\nDynamicArray<MyStruct> contents:\n";
    for (const auto& elem : struct_array) {
        std::cout << "ID: " << elem.id << ", Name: " << elem.name << '\n';
    }

    return 0;  
}
