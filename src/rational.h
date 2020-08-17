#pragma once

#include <iostream>
#include "math.h"

namespace Polymate
{

class Rational
{
public:  
    Rational();
    Rational(const int);
    Rational(const int, const int);

    inline int Numerator() const { return m_num; }
    inline int Denominator() const { return m_den; }

    friend bool operator==(const Rational&, const Rational&);
    friend bool operator>(const Rational&, const Rational&);
    friend bool operator<(const Rational&, const Rational&);
    friend bool operator>=(const Rational&, const Rational&);
    friend bool operator<=(const Rational&, const Rational&);

    inline Rational operator+() const { return Rational(m_num, m_den); }
    inline Rational operator-() const { return Rational(-m_num, m_den); }

    friend Rational operator+(const Rational&, const Rational&);
    friend Rational operator-(const Rational&, const Rational&);
    friend Rational operator*(const Rational&, const Rational&);
    friend Rational operator/(const Rational&, const Rational&);

    Rational pow(const int) const;

    inline void operator+=(const Rational& r) { *this = *this + r; }
    inline void operator-=(const Rational& r) { *this = *this - r; }
    inline void operator*=(const Rational& r) { *this = *this * r; }
    inline void operator/=(const Rational& r) { *this = *this / r; }

    friend bool operator>(const Rational&, const Rational&);
    friend bool operator<(const Rational&, const Rational&);
    friend bool operator>=(const Rational&, const Rational&);
    friend bool operator<=(const Rational&, const Rational&);

    friend Rational abs(const Rational&);

    friend std::ostream& operator<<(std::ostream&, const Rational&);
    
private: 
    int m_num;
    int m_den;
};

}
