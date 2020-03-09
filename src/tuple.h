#pragma once

#include <iostream>
#include "math.h"
#include "rational.h"

namespace Polymate
{

template<typename T, size_t N>
class Tuple
{
public:
	inline Tuple() : m_size(N) {};
	inline size_t Size() const { return m_size; }
	inline T& operator[] (size_t i) { return *(m_data + i); }
	inline const T& operator[] (size_t i) const { return *(m_data + i); }

	Tuple<T,N-1>Exclude(size_t j) const;

private:
	T m_data[N];
	size_t m_size;
};
 
template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Tuple<T,N>& t);

Tuple<Rational,1> t1;
Tuple<Rational,2> t2;
Tuple<Rational,3> t3;
Tuple<Rational,4> t4;
Tuple<Rational,5> t5;
Tuple<Rational,6> t6;
Tuple<Rational,7> t7;
Tuple<Rational,8> t8;
Tuple<Rational,9> t9;
}