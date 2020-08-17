#pragma once

#include <iostream>

namespace Polymate
{

template<typename T, size_t N>
class Tuple
{
public:
	inline Tuple() {};
	inline Tuple(const T (&arr)[N]) { std::copy(std::begin(arr), std::end(arr), std::begin(m_data)); }
	inline size_t Size() const { return N; }
	inline T& operator[] (size_t i) { return *(m_data + i); }
	inline const T& operator[] (size_t i) const { return *(m_data + i); }

	inline Tuple<T,N-1> Exclude(size_t j) const
	{
		Tuple<T,N-1> t;
		for (size_t i = 0; i < N-1; i++)
		{
			t[i] = i < j ? (*this)[i] : (*this)[i+1];
		}
		return t;
	}

	friend T DotProduct(const Tuple<T,N>&, const Tuple<T,N>&);

private:
	T m_data[N];
};

template<typename T, size_t N>
inline std::ostream& operator<<(std::ostream& os, const Tuple<T,N>& t)
{
	for (size_t i = 0; i < N; i++)
	{
	    os << t[i] << " ";
	}
	return os;
}

template<typename T, size_t N>
T DotProduct(const Tuple<T,N>& t1, const Tuple<T,N>& t2)
{
	T t = t1[0] * t2[0];

	for (size_t i = 1; i < N; i++)
	{
		t += t1[i] * t2[i];
	}
	return t;
}

}
