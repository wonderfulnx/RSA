#include <iostream>
#include "src/BigInteger.h"
using namespace std;

int main()
{
    BigInteger a(4, 0xFFFFFFFF);
    BigInteger b(4, 0xFFFFFFFF);
    cout << a << endl << a.size() << endl;
    cout << b << endl << b.size() << endl;
    cout << a * b << endl << (a * b).size() << endl;

    return 0;
}
