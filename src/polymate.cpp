#include <iostream>
#include <vector>
#include <string>

#include "rational.h"


using namespace std;

int main()
{

    vector<string> msg {"Hello", "C++", "World", "from", "VS Code!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    const Polymate::Rational q = Polymate::Rational(1, 3);
    const Polymate::Rational r = Polymate::Rational(1, -2);
    
    cout << (-q) << endl;

}
