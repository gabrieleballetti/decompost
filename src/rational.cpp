#include "rational.h"
#include "math.h"

namespace Polymate
{

Rational::Rational():
    m_num(0),
    m_den(1)
{
}

Rational::Rational(const int n) :
    m_num(n),
    m_den(1)
{
}

Rational::Rational(const int m, const int n)
{
    if (n==0)
        throw 1;
    int _gcd = gcd(abs(m), abs(n));
    m_num = sign(n) * m / _gcd;
    m_den = abs(n) / _gcd;
}

Rational Rational::pow(const int n) const
{
    if (n < 0)
        return Rational(this->m_den, this->m_num) * this->pow(n + 1);
    if (n > 0)
        return *this * this->pow(n - 1);
    else
        if (*this == 0)
            throw 1;
        return Rational(1);
}

bool operator==(const Rational& q, const Rational& r)
{
    return q.m_num == r.m_num && q.m_den == r.m_den;
}
bool operator>(const Rational& q, const Rational& r)
{
    return q.m_num * r.m_den > r.m_num * q.m_den;
}
bool operator<(const Rational& q, const Rational& r)
{
    return q.m_num * r.m_den < r.m_num * q.m_den;
}
bool operator>=(const Rational& q, const Rational& r)
{
    return q.m_num * r.m_den >= r.m_num * q.m_den;
}
bool operator<=(const Rational& q, const Rational& r)
{
    return q.m_num * r.m_den <= r.m_num * q.m_den;
}

Rational operator+(const Rational& q, const Rational& r)
{
    return Rational(q.m_num * r.m_den + r.m_num * q.m_den, q.m_den * r.m_den);
}
Rational operator-(const Rational& q, const Rational& r)
{
    return Rational(q.m_num * r.m_den - r.m_num * q.m_den, q.m_den * r.m_den);
}
Rational operator*(const Rational& q, const Rational& r)
{
    return Rational(q.m_num * r.m_num, q.m_den * r.m_den);
}
Rational operator/(const Rational& q, const Rational& r)
{
    return q * r.pow(-1);
}

Rational abs(const Rational& q)
{
    return Rational(abs(q.m_num), q.m_den);
}

std::ostream& operator<<(std::ostream& os, const Rational& q)
{
    os << q.m_num;
    if (q.m_den != 1)
        os << "/" << q.m_den;
    return os;
}

}
