#include "matrix.h"

namespace Polymate
{

template<size_t M, size_t N>
Tuple<Rational,N> Matrix<M,N>::Row(size_t i) const
{
    return (*this)[i];
}

template<size_t M, size_t N>
Tuple<Rational,N> Matrix<M,N>::Column(size_t j) const
{
    Tuple<Rational,M> t;
    for (size_t i = 0; i < M; i++)
    {
        t[i] = (*this)[i][j];
    }
    return t;
}

template<size_t M, size_t N>
inline Matrix<M-1,N-1> Matrix<M,N>::Submatrix(size_t i, size_t j) const
{
    Matrix<M-1,N-1> m;
    for (size_t h = 0; h < M-1; h++)
    {
        m[h] = h < i ? (*this)[h].Exclude(j) : (*this)[h+1].Exclude(j);
    }
    return m;
}

template<size_t M, size_t N>
Matrix<M,N> operator+(const Matrix<M,N>& m, const Matrix<M,N>& n)
{
    Matrix<M,N> o;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            o[i][j] = m[i][j] + n[i][j];
        }
    }
    return o;
}

template<size_t M, size_t N, size_t O>
Matrix<M,N> operator*(const Matrix<M,N>& m, const Matrix<N,O>& n)
{
    Matrix<M,O> o;
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

template<size_t M, size_t N>
std::ostream& operator<<(std::ostream& os, const Matrix<M,N>& m)
{
	for (size_t i = 0; i < M; i++)
	{
	    os << m[i] << std::endl;
	}
	return os;
}

}