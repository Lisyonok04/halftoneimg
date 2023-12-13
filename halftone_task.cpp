#pragma once
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>
#include<iomanip>
#include <iostream>


using namespace std;

template<typename T>
uniform_int_distribution<T> Dice(true_type)
{
	return uniform_int_distribution<T>(numeric_limits<T>::min(), numeric_limits<T>::max());
}

template<typename T>
uniform_real_distribution<T> Dice(false_type)
{
	return uniform_real_distribution<T>(numeric_limits<T>::min(), numeric_limits<T>::max());
}

template<typename T>
T random()
{
	random_device randomDevice;
	mt19937_64 generator(randomDevice());
	auto dice = Dice<T>(integral_constant<bool, numeric_limits<T>::is_integer>());
	return dice(generator);
}

template<>
char random<char>()
{
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution <> distr('a', 'z');
	return (char)distr(gen);
}

template<>
short random<short>()
{
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution <> distr(-9, 9);
	return distr(gen);
}

template<>
bool random<bool>()
{
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution <> distr(0, 1);
	return distr(gen);
}

template<>
float random<float>()
{
	random_device rand;
	mt19937 gen(rand());
	uniform_real_distribution <> distr(-9, 9);
	return distr(gen);
}

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

	~HalftoneImg()
	{
		for (int i = 0; i < _n; i++)
		{
			delete[] _matrix[i];
		}
		delete[] _matrix;
	}

	int get_n()
	{
		return _n;
	}
	int get_m()
	{
		return _m;
	}

	friend std::ostream& operator<< (std::ostream& out, const HalftoneImg<T>& h)
	{
		for (int i = 0; i < h._n; i++)
		{
			for (int j = 0; j < h._m; j++)
			{
				out << h._matrix[i][j] << " ";
			}
			out << endl;
		}
		;
		return out;
	}
	T& operator()(int i, int j) const
	{
		return _matrix[i][j];
	}

	friend HalftoneImg operator * (const HalftoneImg& first, const HalftoneImg& other)
	{
		if (first._n != other._n || first._m != other._m)
			throw runtime_error("In operator * : different size");
		HalftoneImg<T> h(first._n, first._m, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] * other._matrix[i][j] > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] * other._matrix[i][j] < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] * other._matrix[i][j];
			}
		}
		return h;
	}

	friend HalftoneImg<T> operator+(const HalftoneImg<T>& first, const HalftoneImg<T>& other)
	{
		if (first._n != other._n || first._m != other._m)
			throw runtime_error("In operator + : different size");
		HalftoneImg<T> h(first._n, first._m, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] + other._matrix[i][j] > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] + other._matrix[i][j] < std::numeric_limits<T>::min())
					h._matrix[i][j] = 0;
				else
					h._matrix[i][j] = first._matrix[i][j] + other._matrix[i][j];
			}
		}
		return h;
	}

	friend HalftoneImg<T> operator-(const HalftoneImg<T>& first, const HalftoneImg<T>& other)
	{
		if (first._n != other._n || first._m != other._m)
			throw runtime_error("In operator - : different size");
		HalftoneImg<T> h(first._n, first._n, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] - other._matrix[i][j] > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] - other._matrix[i][j] < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] - other._matrix[i][j];
			}
		}
		return h;
	}

	friend HalftoneImg operator * (const HalftoneImg& first, T a)
	{
		HalftoneImg<T> h(first._n, first._m, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] * a > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] * a < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] * a;
			}
		}
		return h;
	}

	friend HalftoneImg operator * (T a, const HalftoneImg& first)
	{
		HalftoneImg<T> h(first._n, first._m, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] * a > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] * a < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] * a;
			}
		}
		return h;
	}

	friend HalftoneImg<T> operator+(const HalftoneImg<T>& first, T a)
	{
		HalftoneImg<T> h(first._n, first._m, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] + a > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] + a < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] + a;
			}
		}
		return h;
	}

	friend HalftoneImg<T> operator+(T a, const HalftoneImg<T>& first)
	{
		HalftoneImg<T> h(first._n, first._m, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] + a > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] + a < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] + a;
			}
		}
		return h;
	}

	friend HalftoneImg<T> operator-(const HalftoneImg<T>& first, T a)
	{
		HalftoneImg<T> h(first._n, first._n, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] - a > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] - a < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] - a;
			}
		}
		return h;
	}

	friend HalftoneImg<T> operator-(T a, const HalftoneImg<T>& first)
	{
		HalftoneImg<T> h(first._n, first._n, false);
		for (int i = 0; i < first._n; i++)
		{
			for (int j = 0; j < first._m; j++)
			{
				if (first._matrix[i][j] - a > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] - a < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] - a;
			}
		}
		return h;
	}

	friend bool operator!=(HalftoneImg<T> first, HalftoneImg<T> second)
	{
		return !(first == second);
	}

	void swap(HalftoneImg& rhs) {
		for (int i = 0; i < _n; i++)
		{
			std::swap(_matrix[i], rhs._matrix[i]);
		}
	}

	HalftoneImg& operator=(HalftoneImg rhs)
	{
		if (_n != rhs._n || _m != rhs._m)
			throw runtime_error("In operator = : different size");
		rhs.swap(*this);
		return *this;
	}

	HalftoneImg(const HalftoneImg& other)
	{
		_n = other._n;
		_m = other._m;
		_matrix = new T * [_n];
		for (int i = 0; i < _n; i++)
		{
			_matrix[i] = new T[_m];
			for (int j = 0; j < _m; j++)
			{
				_matrix[i][j] = other._matrix[i][j];
			}
		}
	}

	double count_fill_factor()
	{
		double cff = 0;
		float denominator = _m * _n * numeric_limits<T>::max();
		for (int i = 0; i < _m; i++)
		{
			for (int j = 0; j < _n; j++)
			{
				cff += _matrix[i][j] / denominator;
			}
		}
		return cff;
	};

};

template <typename T>
HalftoneImg<T> operator !(HalftoneImg<T> f)
{
	HalftoneImg<T> h(f.get_m(), f.get_n(), false);
	for (int i = 0; i < f.get_m(); i++)
	{
		for (int j = 0; j < f.get_n(); j++)
		{
			h(i, j) = -1 * f(i, j);
		}
	}
	return h;
}

template<>
HalftoneImg<bool> operator !(HalftoneImg<bool> f)
{
	HalftoneImg<bool> h(f.get_m(), f.get_n(), false);
	for (int i = 0; i < f.get_m(); i++)
	{
		for (int j = 0; j < f.get_n(); j++)
		{
			if (f(i, j) == 1)
				h(i, j) = 0;
			else
				h(i, j) = 1;
		}
	}
	return h;
}

template<>
HalftoneImg<char> operator !(HalftoneImg<char> f)
{
	HalftoneImg<char> h(f.get_m(), f.get_n(), false);
	for (int i = 0; i < f.get_m(); i++)
	{
		for (int j = 0; j < f.get_n(); j++)
		{
			h(i, j) = 'a' + ('z' - f(i, j));
		}
	}
	return h;
}

template <typename T>
bool operator==(HalftoneImg<T> a, HalftoneImg<T> b)
{
	if (a.get_m() != b.get_m() || a.get_n() != b.get_n())
		return false;
	for (int i = 0; i < a.get_m(); i++)
	{
		for (int j = 0; j < a.get_n(); j++)
		{
			if (a(i, j) != b(i, j))
			{
				return false;
			}
		}
	}
	return true;
}


class Point {
public:
	float _x;
	float _y;
	float _r;
	Point(float x, float y, float r)
	{
		_x = x;
		_y = y;
		_r = r;
	}
};

template<typename T>
void circle(HalftoneImg<T>&matrix, Point a) {
	for (int i = 0; i < matrix.get_n(); i++) {
		for (int j = 0; j < matrix.get_m(); j++) {
			if (((a._x - i) * (a._x - i) + (a._y - j) * (a._y - j)) <= (a._r * a._r))
				matrix(i, j) = 1;
		}
	}
	cout << matrix;
}