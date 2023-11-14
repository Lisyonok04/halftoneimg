#pragma once
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>
#include <iostream>


using namespace std;

template <typename T>
class HalftoneImg {
private:
	T** _matrix;
	int _n;
	int _m;
public:

	HalftoneImg(int n, int m, T* data)
	{
		if (n <= 0 || m <= 0)
			throw runtime_error("Wrong parameters");
		_n = n;
		_m = m;
		_matrix = new T * [n];
		for (int i = 0; i < n; i++)
		{
			_matrix[i] = new T[m];
			for (int j = 0; j < m; j++) {
				_matrix[i][j] = data[i * n + j];
			}
		}
	}

	HalftoneImg(int n, int m, bool randomize)
	{
		if (n <= 0 || m <= 0)
			throw runtime_error("Wrong parameters");
		_n = n;
		_m = m;
		_matrix = new T * [n];
		for (int i = 0; i < n; i++)
		{
			_matrix[i] = new T[m];
			for (int j = 0; j < m; j++) {
				if (randomize == true) {
					_matrix[i][j] = random<T>();
				}
				else {
					_matrix[i][j] = 0;
				}
			}
		}
	}




/*int ascii_normalize(int a)
{
    while (a > 255)
        a -= 255;
    while (a < 33)
        a += 255 - 33;
    return a;
}

void circle(int x, int y, int r)
{
    for (int i = 0; i <= 50; i++)
    {
        for (int j = 0; j <= 50; j++)
        {
            if (((x - i) * (x - i) + (y - j) * (y - j)) <= (r * r))
                cout << setw(2) << " ";
            else
                cout << setw(2) << char(2 * i + j + 33);
        }
        cout << '\n';
    }

}*/
