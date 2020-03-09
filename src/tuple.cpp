#include "tuple.h"
#include "rational.h"


namespace Polymate
{

template<typename T, size_t N>
Tuple<T,N-1> Tuple<T,N>::Exclude(size_t j) const
{
	Tuple<T,N-1> t;
	for (size_t i = 0; i < N-1; i++)
	{
		t[i] = i < j ? (*this)[i] : (*this)[i];
	}
	return t;
}

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Tuple<T,N>& t)
{
	for (size_t i = 0; i < N; i++)
	{
	    os << t[i] << " ";
	}
	return os;
}

}
