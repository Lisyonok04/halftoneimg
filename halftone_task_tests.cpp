#include "halftone_task.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>

using namespace std;


TEST(HalftoneImageTests, SwapCheck) {
    short* data1 = new short[6] {1, 2, 3, 4, 5, 6};
    HalftoneImg<short> h1(2, 3, data1);
    short* data2 = new short[6] {10, 11, 12, 13, 14, 15};
    HalftoneImg<short> h2(2, 3, data2);
    cout << h1;
    cout << h2;
    cout << endl;
    swap(h1, h2);
    cout << h1;
    cout << h2;
}

TEST(HalftoneImageTests, Check1) {
    HalftoneImg<short> h(3, 3, false);
    h(0, 1) = 6;
    EXPECT_EQ(6, h(0, 1));
}

TEST(HalftoneImageTests, OperatorCheck1) {
    short* data1 = new short[4] {1, 2, 3, 4};
    HalftoneImg<short> h1(2, 2, data1);
    short* data2 = new short[4] {-5, -6, -7, -8};
    HalftoneImg<short> h2(2, 2, data2);
    short* data3 = new short[4] {-4, -4, -4, -4};
    HalftoneImg<short> h3(2, 2, data3);
    EXPECT_TRUE(h3 == h1 + h2);
}

TEST(HalftoneImageTests, OperatorCheck2) {
    short* data1 = new short[4] {1, 2, 3, 4};
    HalftoneImg<short> h1(2, 2, data1);
    short* data2 = new short[4] {-5, -6, -7, -8};
    HalftoneImg<short> h2(2, 2, data2);
    short* data4 = new short[4] {-5, -12, -21, -32};
    HalftoneImg<short> h4(2, 2, data4);
    EXPECT_TRUE(h4 == h1 * h2);
}

TEST(HalftoneImageTests, ExceptionCheck) {
    EXPECT_ANY_THROW(HalftoneImg<short> h(3, -2, false));
    EXPECT_ANY_THROW(HalftoneImg<short> h(-3, 4, true));

    short* data1 = new short[6] {10, 5, 3, 0, 3, 4};
    HalftoneImg<short> h1(3, 2, data1);
    short* data2 = new short[4] {-5, 2, 1, -10 };
    HalftoneImg<short> h2(2, 2, data2);
    EXPECT_ANY_THROW(h1 + h2);
    EXPECT_ANY_THROW(h1 * h2);
}

TEST(HalftoneImageTests, CountFillFactorCheck) {
    HalftoneImg<short> h(3, 3, false);
    EXPECT_EQ(0, h.count_fill_factor());

    short* data1 = new short[16] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    HalftoneImg<short> h10(4, 4, data1);
}

 
TEST(HalftoneImageTests, Circle1) {
    short* data1 = new short[90] {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    HalftoneImg<short> h1(9, 9, data1);
    circle(h1, Point(4, 5, 3));
    
}

TEST(HalftoneImageTests, Circle2) {
    short* data1 = new short[90] {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    HalftoneImg<short> h1(9, 9, data1);
    circle(h1, Point(0, 6, 3));

}