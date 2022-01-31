cmake_minimum_required(VERSION 3.20)
project(BusNavigationProgram)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(BusNavigationProgram main.cpp src/Node.h tests/test.cpp src/Graph.cpp src/Graph.h src/MinHeap.h tests/GraphsForTests.cpp tests/GraphsForTests.h src/Menu.cpp src/Menu.h src/DisjointSets.cpp src/DisjointSets.h tests/GraphsForTests.cpp tests/GraphsForTests.h)

target_link_libraries(BusNavigationProgram gtest gtest_main)