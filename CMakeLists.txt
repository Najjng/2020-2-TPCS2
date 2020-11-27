cmake_minimum_required(VERSION 3.17)
project(2020_2_TPCS2)

set(CMAKE_CXX_STANDARD 20)

add_executable(2020_2_TPCS2 main.cpp homework03/main.cpp homework03/LinkedList.cpp homework03/dLinkedList.cpp homework03/dLinkedList.h homework03/LinkedList.h final/main.cpp)

project(homework01)

set(CMAKE_CXX_STANDARD 20)

add_executable(homework01 homework01/main.cpp)

project(homework02)

set(CMAKE_CXX_STANDARD 20)

add_executable(homework02 homework02/main.cpp homework02/polynomial.h homework02/polynomial.cpp)

project(homework03)

set(CMAKE_CXX_STANDARD 20)

add_executable(homework03 homework03/main.cpp)
