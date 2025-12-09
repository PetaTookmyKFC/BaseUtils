//
// Created by jacka on 06/12/2025.
//

#include "../include/BaseUtils/types/SemiDynamicArray.h"
#include <iostream>
#include <thread>
#include <vector>

#include "BaseUtils/All.h"

using namespace base_utils::types;

int main() {
try {
    // Test 1: Basic construction and pushBack with initial size 0, increment 3
    SemiDynamicArray<int> arr(3);  // Default size 0, increment 3
    std::cout << "Initial size: " << arr.size() << ", Capacity: " << arr.CurrentCapacity() << std::endl;

    // Push 5 elements, should resize once (to 3) then again (to 6)
    for (int i = 1; i <= 5; ++i) {
        arr.pushBack(i);
        std::cout << "After pushing " << i << ": size=" << arr.size() << ", capacity=" << arr.CurrentCapacity() << std::endl;
    }

    // Access elements via operator[]
    std::cout << "Elements via operator[]: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Iterate via range-based for loop (uses begin/end)
    std::cout << "Elements via range-based for: ";
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Test available space
    std::cout << "Available space: " << arr.AvailableSpace() << std::endl;

    // Test changing increment size
    arr.setIncrementSize(5);
    // Push more to trigger resize with new increment (to 6 + 5 = 11)
    for (int i = 6; i <= 12; ++i) {
        arr.pushBack(i);
    }
    std::cout << "After more pushes: size=" << arr.size() << ", capacity=" << arr.CurrentCapacity() << std::endl;

    // Test out-of-range access
    // Uncomment to test: arr[100];  // Should throw std::out_of_range

    // Test with strings (different type)
    SemiDynamicArray<std::string> strArr(2, 1);  // Initial size 1, increment 2
    strArr.pushBack("Hello");
    strArr.pushBack("World");
    strArr.pushBack("!");
    std::cout << "String array size: " << strArr.size() << ", elements: ";
    for (const auto& s : strArr) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    // std::cout << base_utils::fmt::Underline("Attempting MultiThreads !!!") << std::endl;
    //
    // try {
    //     // Handle Multiple Threads
    //     SemiDynamicArray<int> MultThreadArr(3);
    //     std::vector<std::thread> threads;
    //     for (int i = 0; i < 10; ++i) {
    //         threads.emplace_back([&MultThreadArr, i]() {
    //             for (int j = 0; j < 100; ++j) {
    //                 MultThreadArr.pushBack(i * 100 + j);
    //             }
    //         });
    //     }
    //     for (auto& t : threads) t.join();
    //     std::cout << "Final size: " << MultThreadArr.size() << std::endl;  // Should be 1000
    //
    // }catch (const std::exception& e) {
    //     std::cerr << "Exception: " << e.what() << std::endl;
    //     return 1;
    // }

    return 0;
}