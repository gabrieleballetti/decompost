#include <iostream>
#include <vector>
#include <string>

#include "rational.h"
#include "tuple.h"
#include "matrix.h"


int main()
{   
    const Polymate::Rational p = Polymate::Rational(1, 1);
    const Polymate::Rational q = Polymate::Rational(1, 2);
    const Polymate::Rational r = Polymate::Rational(1, 3);

    Polymate::Tuple<Polymate::Rational,3> t1, t2, t3;

    for (unsigned int i = 0; i < 3; i++)
    {
        t1[i] = p.pow(i);
        t2[i] = q.pow(i);
        t3[i] = r.pow(i);
    }

    Polymate::Matrix<3,3> m;  
    m[0] = t1;
    m[1] = t2;
    m[2] = t3;    
    std::cout << m << std::endl;  
    //std::cout << m.Column(1) << std::endl;
    //std::cout << m.Submatrix(2,2) << std::endl << std::endl;
    //std::cout << m + m << std::endl;
    //std::cout << m.Determinant() << std::endl;
}
