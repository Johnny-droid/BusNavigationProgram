cmake_minimum_required(VERSION 3.21)
project(BusNavigationProgram)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(BusNavigationProgram main.cpp src/Node.h tests/test.cpp src/Graph.cpp src/Graph.h tests/GraphsForTests.cpp src/MinHeap.h)

target_link_libraries(BusNavigationProgram gtest gtest_main)