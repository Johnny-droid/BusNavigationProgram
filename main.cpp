#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World of Graphs!" << std::endl;
    std::cout << "We love you Graphs!" << std::endl;
    std::cout << "(Well, we need to)" << std::endl;

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


}
