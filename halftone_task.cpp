#pragma once
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>
#include <iostream>


using namespace std;

template<typename T>
std::uniform_int_distribution<T> Dice(std::true_type)
{
	return std::uniform_int_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}
template<typename T>
std::uniform_real_distribution<T> Dice(std::false_type)
{
	return std::uniform_real_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template<typename T>
T random()
{
	std::random_device randomDevice;
	std::mt19937_64 generator(randomDevice());
	auto dice = Dice<T>(std::integral_constant<bool, std::numeric_limits<T>::is_integer>());
	return dice(generator);
}

template<>
char random<char>()
{
	std::random_device rand;
	std::mt19937 gen(rand());
	std::uniform_int_distribution <> distr('a', 'z');
	return (char)distr(gen);
}

template<>
bool random<bool>()
{
	std::random_device rand;
	std::mt19937 gen(rand());
	std::uniform_int_distribution <> distr(0, 1);
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

	friend std::ostream& operator<< (std::ostream& out, const HalftoneImg<T>& h)
	{
		for (int i = 0; i < h._n; i++)
		{
			for (int j = 0; j < h._m; j++)
			{
				std::cout << h._matrix[i][j] << " ";
			}
			cout << endl;
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
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] + other._matrix[i][j];
			}
		}
		return h;
	}