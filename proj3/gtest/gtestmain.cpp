// gtestmain.cpp
//
// ICS 46 Winter 2021
// Project #3: Black and White
//
// DO NOT MODIFY THIS FILE AT ALL.  Its job is to launch Google Test and run
// any unit tests that you wrote in source files in the "gtest" directory.
// Simply add new source files to the "gtest" directory and write unit tests
// in them and they should be picked up automatically the next time you
// run gtest.

#include <gtest/gtest.h>


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

