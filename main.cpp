#include <iostream>
#include "gtest/gtest.h"
#include "src/Menu.h"


int main(int argc, char* argv[]) {
    Menu menu("dataset");
    menu.run();
    /*
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    */
}
