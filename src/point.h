#pragma once

#include <iostream>
#include "math.h"
#include "tuple.h"

namespace Polymate
{

template<typename T, size_t N>
class Point : public Tuple<T,N>
{
public:
    inline Point() : Tuple<T,N>() {};
    inline Point(const T (&arr)[N]) : Tuple<T,N>(arr) {};
};

template<typename T, size_t N>
inline std::ostream& operator<<(std::ostream& os, const Point<T,N>& t)
{
    os << "( ";
	for (size_t i = 0; i < N; i++)
	{
	    os << t[i];
        if (i < N-1)
        {
            os << ", ";
        }
	}
    os << " )";
	return os;
}

}
