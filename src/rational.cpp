#include "rational.h"

namespace Polymate
{

Rational::Rational(const int n) :
    num(n),
    den(1)
{
}

Rational::Rational(const int m, const int n)
{
    if (n==0)
        throw 1;
    int gcd = Math::gcd(Math::abs(m), Math::abs(n));
    num = Math::sign(n) * m / gcd;
    den = Math::abs(n) / gcd;
}

Rational Rational::pow(const int n) const {
    if (n < 0)
        return Rational(this->den, this->num) * this->pow(n + 1);
    if (n > 0)
        return *this * this->pow(n - 1);
    else
        if (*this == 0)
            throw 1;
        return Rational(1);
}

bool operator==(const Rational& q, const Rational& r) {
    return q.num == r.num && q.den == r.den;
}
bool operator>(const Rational& q, const Rational& r) {
    return q.num * r.den > r.num * q.den;
}
bool operator<(const Rational& q, const Rational& r) {
    return q.num * r.den < r.num * q.den;
}
bool operator>=(const Rational& q, const Rational& r) {
    return q.num * r.den >= r.num * q.den;
}
bool operator<=(const Rational& q, const Rational& r) {
    return q.num * r.den <= r.num * q.den;
}

Rational operator+(const Rational& q, const Rational& r) {
    return Rational(q.num * r.den + r.num * q.den, q.den * r.den);
}
Rational operator-(const Rational& q, const Rational& r) {
    return Rational(q.num * r.den - r.num * q.den, q.den * r.den);
}
Rational operator*(const Rational& q, const Rational& r) {
    return Rational(q.num * r.num, q.den * r.den);
}
Rational operator/(const Rational& q, const Rational& r) {
    return q * r.pow(-1);
}

std::ostream& operator<<(std::ostream& os, const Rational& q)
{
    if (q.num >= 0)
        os << " ";
    else
        os << "-";
    os << q.num;
    if (q.den != 1)
        os << "/" << q.den;
    return os;
}

}
