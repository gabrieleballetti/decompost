#include <iostream>
#include <vector>
#include <string>

#include <cstdio>
#include <ctime>

#include "rational.h"
#include "tuple.h"
#include "matrix.h"
#include "point.h"
#include "hyperplane.h"

void TestRational()
{
	assert(Polymate::Rational(1) == Polymate::Rational(2,2));
    assert(Polymate::Rational(1) > Polymate::Rational(1,2));
    assert(Polymate::Rational(1) < Polymate::Rational(3,2));
    assert(Polymate::Rational(1) >= Polymate::Rational(1));
	assert(Polymate::Rational(1) >= Polymate::Rational(1,2));
    assert(Polymate::Rational(1) <= Polymate::Rational(1));
	assert(Polymate::Rational(1) <= Polymate::Rational(3,2));

	assert(Polymate::Rational(1) == 1);
	assert(1 == Polymate::Rational(1));

	assert(+Polymate::Rational(1) == 1);
	assert(-1 == -Polymate::Rational(1));

	assert(Polymate::Rational(1) + Polymate::Rational(1,2) == Polymate::Rational(3,2));
	assert(Polymate::Rational(1) - Polymate::Rational(1,2) == Polymate::Rational(1,2));
	assert(Polymate::Rational(1) * Polymate::Rational(1,2) == Polymate::Rational(1,2));
	assert(Polymate::Rational(1) / Polymate::Rational(1,2) == Polymate::Rational(2));

	assert(Polymate::Rational(2).pow(2) == Polymate::Rational(4));
	assert(Polymate::Rational(2).pow(-2) == Polymate::Rational(1,4));

	Polymate::Rational p(1);
	Polymate::Rational q(1, 2);
	Polymate::Rational r(1, 3);
	q += 1;
	assert(q == Polymate::Rational(3,2));
	q -= 1;
	assert(q == Polymate::Rational(1,2));
	q *= 2;
	assert(q == 1);
	q /= 2;
	assert(q == Polymate::Rational(1,2));
}

int main()
{
	TestRational();
	
	// Identity matrix
	Polymate::Matrix<Polymate::Rational,2,2> mm;
	mm[0] = Polymate::Tuple<Polymate::Rational,2>({Polymate::Rational(2), Polymate::Rational(0)});
	mm[1] = Polymate::Tuple<Polymate::Rational,2>({Polymate::Rational(0), Polymate::Rational(1)});
	std::cout << mm << std::endl;
	std::cout << mm.Inverse() << std::endl;

	// Just a point
	Polymate::Point<Polymate::Rational,3> point({Polymate::Rational(1), Polymate::Rational(2), Polymate::Rational(3)});
	std::cout << point << std::endl;

	// Just an hyperplane
	Polymate::Hyperplane<Polymate::Rational,3> h({Polymate::Rational(1), Polymate::Rational(2), Polymate::Rational(3)}, Polymate::Rational(0));
	std::cout << h << std::endl << std::endl;

	// Test LUP factorization for a square matrix
	Polymate::Matrix<Polymate::Rational,4,4> n;
	n[0] = Polymate::Tuple<Polymate::Rational,4>({Polymate::Rational(1), Polymate::Rational(0), Polymate::Rational(0), Polymate::Rational(1)});
	n[1] = Polymate::Tuple<Polymate::Rational,4>({Polymate::Rational(2), Polymate::Rational(7), Polymate::Rational(1), Polymate::Rational(2)});
	n[2] = Polymate::Tuple<Polymate::Rational,4>({Polymate::Rational(1), Polymate::Rational(2), Polymate::Rational(1), Polymate::Rational(1)});
	n[3] = Polymate::Tuple<Polymate::Rational,4>({Polymate::Rational(0), Polymate::Rational(2), Polymate::Rational(0), Polymate::Rational(3)});
	std::cout << n << std::endl << std::endl;
	n.LUPDecompose();
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << n.LU[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << n.Determinant() << std::endl;
	std::cout << n.Inverse() * n << std::endl << std::endl;

	// Test LUP factorization for a rectangular 'wide' matrices
	Polymate::Matrix<Polymate::Rational,3,4> re;
	re[0] = Polymate::Tuple<Polymate::Rational,4>({Polymate::Rational(1), Polymate::Rational(2), Polymate::Rational(-3), Polymate::Rational(1)});
	re[1] = Polymate::Tuple<Polymate::Rational,4>({Polymate::Rational(2), Polymate::Rational(4), Polymate::Rational(0), Polymate::Rational(7)});
	re[2] = Polymate::Tuple<Polymate::Rational,4>({Polymate::Rational(-1), Polymate::Rational(3), Polymate::Rational(2), Polymate::Rational(0)});
	std::cout << re << std::endl << std::endl;
	re.LUPDecompose();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			std::cout << re.LU[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Test LUP factorization for a rectangular 'tall' matrices
	Polymate::Matrix<Polymate::Rational,4,3> m43;
	m43[0] = Polymate::Tuple<Polymate::Rational,3>({Polymate::Rational(1), Polymate::Rational(2), Polymate::Rational(-1)});
	m43[1] = Polymate::Tuple<Polymate::Rational,3>({Polymate::Rational(2), Polymate::Rational(4), Polymate::Rational(3)});
	m43[2] = Polymate::Tuple<Polymate::Rational,3>({Polymate::Rational(-3), Polymate::Rational(0), Polymate::Rational(2)});
	m43[3] = Polymate::Tuple<Polymate::Rational,3>({Polymate::Rational(1), Polymate::Rational(7), Polymate::Rational(0)});
	std::cout << m43 << std::endl << std::endl;
	m43.LUPDecompose();
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			std::cout << m43.LU[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//// Test hyperplane through random points
    //std::clock_t start;
    //double duration;
    //start = std::clock();
	//
	//const size_t N = 10;
	//Polymate::Point<Polymate::Rational,N> t[N];
	//for (size_t i = 0; i < N; i++)
	//{
	//	for (size_t j = 0; j < N; j++)
	//	{
	//		t[i][j] = Polymate::Rational(rand() % static_cast<int>(2));
	//	}
	//	std::cout << t[i] << std::endl;
	//}
	//Polymate::Hyperplane<Polymate::Rational,N> H(t);
	//std::cout << H << std::endl;
	//
	//Polymate::Rational sum = 0;
	//for (size_t i = 0; i < N; i++)
	//{
	//	sum += H[i] * t[1][i];
	//}
	//std::cout << sum << std::endl;
	//
    //duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    //std::cout<< "printf: " << duration << std::endl;
	//
	//// Test hyperplane through random points
	//Polymate::Point<Polymate::Rational,2> pts[2];
	//pts[0] = Polymate::Point<Polymate::Rational,2>({Polymate::Rational(1), Polymate::Rational(1)});
	//pts[1] = Polymate::Point<Polymate::Rational,2>({Polymate::Rational(-1), Polymate::Rational(-1)});
	//Polymate::Hyperplane<Polymate::Rational,2> H1(pts);
	//std::cout << H1 << std::endl;

	Polymate::Matrix<Polymate::Rational,2,3> m23;
	m23[0] = Polymate::Tuple<Polymate::Rational,3>({Polymate::Rational(1), Polymate::Rational(1), Polymate::Rational(2)});
	m23[1] = Polymate::Tuple<Polymate::Rational,3>({Polymate::Rational(1), Polymate::Rational(2), Polymate::Rational(4)});
	std::cout << m23 << std::endl << std::endl;
	m23.LUPDecompose();
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			std::cout << m23.LU[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
