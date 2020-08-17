#pragma once

#include <iostream>
#include "rational.h"
#include "tuple.h"
#include "point.h"
#include "matrix.h"

namespace Polymate
{

template<typename T, size_t N>
class Hyperplane : public Tuple<T,N>
{
public:
	inline Hyperplane() : Tuple<T,N>() {};
	inline Hyperplane(const T (&arr)[N], const T constant) : Tuple<T,N>(arr), m_constant(constant) {};
	inline Hyperplane(const Point<T,N> (&points)[N]);

	inline T Constant() const { return m_constant; }

private:
	T m_constant;
};

template<typename T, size_t N>
Hyperplane<T,N>::Hyperplane(const Point<T,N> (&points)[N])
{
	for (size_t k = 0; k < N; k++)
	{
		Matrix<T,N-1,N-1> m;
		for (size_t i = 0; i < N-1; i++)
		{
			for (size_t j = 0; j < N-1; j++)
			{
				size_t _j = j >= k ? j+1 : j;
				m[i][j] = points[i+1][_j] - points[0][_j];
			}
		}
		T _det = m.Determinant();
		(*this)[k] = (k % 2 == 0) ? _det : -_det;
	}
	m_constant = (*this)[0] * points[0][0];
	for (size_t i = 1; i < N; i++)
	{
		m_constant += (*this)[i] * points[0][i];
	}

	// seems to be faster when dim => ~5
	//Matrix<T,N+1,N+1> m;
	//Tuple<T,N+1> t;
	//for (size_t i = 0; i < N; i++)
	//{
	//	for (size_t j = 0; j < N; j++)
	//	{
	//		m[i][j] = points[i][j];
	//	}
	//	m[i][N] = T(1);
	//	m[N][i] = T(0);
	//}
	//m[N][N] = 1;
	//
	//T _det = m.Determinant();
	//for (size_t i = 0; i < N; i++)
	//{
	//	t[i] = _det;
	//}
	//t[N+1] = T(1);
//
	//t = m.Solve(t);
	//
	//for (size_t i = 0; i < N; i++)
	//{
	//	(*this)[i] = t[i];
	//}
	//m_constant = _det;
}

template<typename T, size_t N>
inline std::ostream& operator<<(std::ostream& os, const Hyperplane<T,N>& t)
{
	for (size_t i = 0; i < N; i++)
	{
		os << t[i] << " x_" << i;
		if (i < N-1)
		{
			os << " + ";
		}
	}
	os << " = " << t.Constant();
	return os;
}

}