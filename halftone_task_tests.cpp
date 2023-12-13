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
    cout << 6 * h1 << endl;
    short* data2 = new short[4] {-5, -6, -7, -8};
    HalftoneImg<short> h2(2, 2, data2);
    short* data4 = new short[4] {-5, -12, -21, -32};
    HalftoneImg<short> h4(2, 2, data4);
    EXPECT_TRUE(h4 == h1 * h2);
}

TEST(HalftoneImageTests, OperatorCheck3) {
    bool* data1 = new bool[4] {1, 0, 0, 1 };
    HalftoneImg<bool> h1(2, 2, data1);
    bool* data2 = new bool[4] {0, 1, 1, 0 };
    HalftoneImg<bool> h2(2, 2, data2);
    EXPECT_TRUE(h1 == !h2);
}


TEST(HalftoneImageTests, OperatorCheck4) {
    float* data1 = new float[4] {1, 2, 3, 400};
    HalftoneImg<float> h1(2, 2, data1);
    HalftoneImg<float> h2 = !h1;
    HalftoneImg<float> h3 = HalftoneImg<float>(2, 2, false);
    EXPECT_EQ(h1 + h2, h3);
}

TEST(HalftoneImageTests, OperatorCheck5) {
    char* data1 = new char[4] {'a', 'b', 'c', 'd' };
    HalftoneImg<char> h10(2, 2, data1);
    HalftoneImg<char> h11 = !h10;
    EXPECT_EQ(h11, HalftoneImg<char>(2, 2, new char[4] {'z', 'y', 'x', 'w'}));
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
    short x = 5;
    circle(h1, Point(4, 5, 3), x);
    
}

TEST(HalftoneImageTests, Circle2) {
    short* data1 = new short[90] {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    HalftoneImg<short> h1(9, 9, data1);
    short x = 0;
    circle(h1, Point(0, 6, 3), x);

}

TEST(HalftoneImageTests, Circle3) {
    HalftoneImg<bool> h1(30, 50, true);
    bool x = 0;
    circle(h1, Point(10, 15, 10), x);
}

TEST(HalftoneImageTests, Circle4) {
    HalftoneImg<char> h1(30, 50, true);
    char x;
    x = ' ';
    circle(h1, Point(10, 15, 10), x);
}