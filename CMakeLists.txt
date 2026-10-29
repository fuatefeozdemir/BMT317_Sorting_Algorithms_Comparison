cmake_minimum_required(VERSION 3.29)
project(BMT317_Sorting_Algorithms_Comparison)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(SortingAlgorithmsComparison
        src/main.cpp
        src/algorithms.cpp
        src/utils.cpp
)