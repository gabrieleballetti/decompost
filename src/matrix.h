#pragma once

#include <iostream>
#include <optional>
#include <utility>
#include "math.h"

#include "tuple.h"

namespace Polymate
{

template<typename T, size_t M, size_t N>
class Matrix
{
public:
	inline Matrix() {};

	inline size_t NumberOfRows() const { return M; }
	inline size_t NumberOfColumns() const { return N; }

	inline Tuple<T,N>& operator[](size_t i) { return *(m_rows + i); }
	inline const Tuple<T,N>& operator[](size_t i) const { return *(m_rows + i); }

	inline Tuple<T,N> Row(size_t i) const { return (*this)[i]; }
	inline Tuple<T,N> Column(size_t j) const
	{
		Tuple<T,M> t;
		for (size_t i = 0; i < M; i++)
		{
			t[i] = (*this)[i][j];
		}
		return t;
	}

	inline Matrix<T,M-1,N-1> Submatrix(size_t i, size_t j) const
	{
		Matrix<T,M-1,N-1> m;
		for (size_t h = 0; h < M-1; h++)
		{
			m[h] = h < i ? (*this)[h].Exclude(j) : (*this)[h+1].Exclude(j);
		}
		return m;
	}

	void LUPDecompose();
	T Determinant();
	Matrix<T,M,N> Inverse();
	Tuple<T,N> Solve(Tuple<T,M>& b);


	T LU[M][N];
	size_t P[M+1];
	bool m_LUDecomposed = false;

private:
	Tuple<T,N> m_rows[M];
};

template<typename T, size_t M, size_t N>
inline Matrix<T,M,N> operator+(const Matrix<T,M,N>& m, const Matrix<T,M,N>& n)
{
	Matrix<T,M,N> o;
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			o[i][j] = m[i][j] + n[i][j];
		}
	}
	return o;
}

template<typename T, size_t M, size_t N, size_t O>
inline Matrix<T,M,N> operator*(const Matrix<T,M,N>& m, const Matrix<T,N,O>& n)
{
	Matrix<T,M,O> o;
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < O; j++)
		{
			o[i][j] = 0;
			for (size_t k = 0; k < N; k++)
			{
				o[i][j] += m[i][k] * n[k][j];
			}
		}
	}
	return o;
}

template<typename T, size_t M, size_t N>
inline std::ostream& operator<<(std::ostream& os, const Matrix<T,M,N>& m)
{
	for (size_t i = 0; i < M; i++)
	{
		os << m[i] << std::endl;
	}
	return os;
}


template <typename T, size_t M, size_t N>
void Matrix<T,M,N>::LUPDecompose()
{
	for (size_t i = 0; i < M; i++)
	{
		P[i] = i;
	}
	P[M] = 0;

	std::memcpy(&LU, m_rows, sizeof(T) * M * N);

	size_t i_max; 
	T _max, _abs;
	for (size_t j = 0; j < M && j < N; j++)
	{
		_max = abs(LU[j][j]);
		i_max = j;
		for (size_t i = j + 1; i < M; i++)
		{
			_abs = abs(LU[i][j]);
			if (_abs > _max)
			{ 
				_max = _abs;
				i_max = i;
			}
		}
		if (_max == 0)
		{
			std::cout << "ERROR! singular matrix" << std::endl;
			return;
		}
		if (i_max != j)
		{
			std::swap(P[j], P[i_max]);
			std::swap(LU[j], LU[i_max]);
			P[M]++;
		}
		for (size_t i = j + 1; i < M && j < N; i++) {
			LU[i][j] /= LU[j][j];

			for (size_t k = j + 1; k < N && j < M; k++)
				LU[i][k] -= LU[i][j] * LU[j][k];
		}
	}
	m_LUDecomposed = true;
}

template<typename T, size_t M, size_t N>
T Matrix<T,M,N>::Determinant()
{
	if (!m_LUDecomposed)
	{
		this->LUPDecompose();
	}
	T _det = LU[0][0];
	for (size_t i = 1; i < M; i++)
	{
		_det *= LU[i][i];
	}
	if (P[M] % 2 == 0)
	{
		return _det;
	}
	else
	{
		return -_det;
	}
}

template<typename T, size_t M, size_t N>
Matrix<T,M,N> Matrix<T,M,N>::Inverse()
{
	if (!m_LUDecomposed)
	{
		this->LUPDecompose();
	}
	Matrix<T,M,N> inv;
	for (size_t j = 0; j < N; j++)
	{
		for (size_t i = 0; i < M; i++)
		{
			if (P[i] == j)
			{
				inv[i][j] = T(1);
			}
			else
			{
				inv[i][j] = T(0);
			}
			for (size_t k = 0; k < i; k++)
			{
				inv[i][j] -= LU[i][k] * inv[k][j];
			}
		}
		for (size_t i = M; i--;)
		{
			for (size_t k = i + 1; k < N; k++)
			{
				inv[i][j] -= LU[i][k] * inv[k][j];
			}
			inv[i][j] /= LU[i][i];
		}
	}
	return inv;
}


template<typename T, size_t M, size_t N>
Tuple<T,N> Matrix<T,M,N>::Solve(Tuple<T,M>& b)
{
	if (!m_LUDecomposed)
	{
		this->LUPDecompose();
	}
	Tuple<T,N> x;
	for (size_t i = 0; i < M; i++) {
		x[i] = b[P[i]];
		for (size_t j = 0; j < i; j++)
			x[i] -= LU[i][j] * x[j];
	}
	for (size_t i = M; i--;) {
		for (size_t j = i + 1; j < N; j++)
			x[i] -= LU[i][j] * x[j];
		x[i] = x[i] / LU[i][i];
	}
	return x;
}

}