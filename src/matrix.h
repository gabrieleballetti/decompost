#pragma once

#include <iostream>
#include "math.h"
#include "rational.h"
#include "tuple.h"

namespace Polymate
{

template<size_t M, size_t N>
class Matrix
{
    public:
    inline Matrix() : m_nrows(M), m_ncols(M) {};

    inline size_t NumberOfRows() const { return m_nrows; }
    inline size_t NumberOfColumns() const { return m_ncols; }

    inline Tuple<Rational,N>& operator[](size_t i) { return *(m_rows + i); }
    inline const Tuple<Rational,N>& operator[](size_t i) const { return *(m_rows + i); }

    Tuple<Rational,N> Row(size_t i) const;
    Tuple<Rational,N> Column(size_t j) const;

    Matrix<M-1,N-1> Submatrix(size_t i, size_t j) const;

    /*const Rational Determinant() const
    {
        if (this->m_ncols == 1)
        {
            return (*this)[0][0];
        }
        Rational determinant = Rational(0, 1);
        for (size_t j = 0; j < m_ncols; j++)
        {
            Rational sign = (static_cast<int>(j) % 2 == 0) ? 1 : -1;
            determinant += sign * (*this)[0][j] * this->Submatrix(0, j).Determinant();
        }
        return determinant;
    }*/

    private:
    size_t m_nrows;
    size_t m_ncols;

    Tuple<Rational,N> m_rows[M];
    size_t m_size;
};

template<size_t M, size_t N>
Matrix<M,N> operator+(const Matrix<M,N>& m, const Matrix<M,N>& n);

template<size_t M, size_t N, size_t O>
Matrix<M,N> operator*(const Matrix<M,N>& m, const Matrix<N,O>& n);

template<size_t M, size_t N>
std::ostream& operator<<(std::ostream& os, const Matrix<M,N>& m);

Matrix<1,1> m11;
Matrix<2,2> m22;
Matrix<3,3> m33;
Matrix<4,4> m44;
Matrix<5,5> m55;
Matrix<6,6> m66;
Matrix<7,7> m77;
Matrix<8,8> m88;
Matrix<9,9> m99;

}