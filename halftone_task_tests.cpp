#include "halftone_task.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>


using namespace std;

TEST(ImgTests, Constructor) {
    HalftoneImg<bool> h1(2, 2, false);
    h1(0, 0) = 0; h1(0, 1) = 1; h1(1, 0) = 1; h1(1, 1) = 0;
    bool* data = new bool[4] {0, 1, 1, 0 };
    HalftoneImg<bool> h2(2, 2, data);
    EXPECT_TRUE(h1 == h2);
    EXPECT_FALSE(h1 != h2);

    HalftoneImg<bool> h3(2, 2, false);
    h3(0, 0) = 0; h3(0, 1) = 1; h3(1, 0) = 1; h3(1, 1) = 0;
    HalftoneImg<bool> h4(h3);
    EXPECT_EQ(h3, h4);
}