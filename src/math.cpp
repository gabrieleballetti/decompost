#include "math.h"

namespace Math 
{

    int abs(const int n)
    {
        return n >= 0 ? n : -n;
    }

    int gcd(const int m, const int n)
    {
        // a = q * b + r
        int a = m;
        int b = n;
        int q, r;
        while (true)
        {
            q = a / b;
            r = a - q * b;
            if (r == 0)
                return b;
            a = b;
            b = r;
        }
    }

    int sign(const int n) {
        return n >= 0 ? 1 : -1;
    }

}
