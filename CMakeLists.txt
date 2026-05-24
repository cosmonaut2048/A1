cmake_minimum_required(VERSION 3.31)
project(A1)

set(CMAKE_CXX_STANDARD 20)

add_executable(A1 main.cpp
        StringGenerator.cpp
        StringGenerator.h
        StringSortTester.h
        char_counter.h
        StringMergeSort.cpp
        Performance.cpp
        TernaryQuickSort.cpp
        MSDRadixSort.cpp
        Standard.cpp
        char_counter.cpp)
