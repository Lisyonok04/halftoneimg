#include "halftone_task.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>

using namespace std;


TEST(HalftoneImageTests, SwapCheck) {
    short* data1 = new short[4] {1, 2, 3, 4};
    HalftoneImg<short> h1(2, 2, data1);
    short* data2 = new short[4] {5, 6, 7, 8};
    HalftoneImg<short> h2(2, 2, data2);
    cout << h1;
    cout << h2;
    cout << endl;
    swap(h1, h2);
    cout << h1;
    cout << h2;
}

