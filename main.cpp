#include <iostream>
#include "src/BigInteger.h"
using namespace std;

int main()
{
    BigInteger a(24, 0xFFFFFFFF);
    BigInteger b(1, 0x0001);
    BigInteger c(2, 0x0000FFFF);

    cout << (b-a).neg() << " " << b - a << endl;

//    cout << a << endl << a.size() << endl;
//    cout << b << endl << b.size() << endl;
//    cout << a * b << endl << (a * b).size() << endl;

    return 0;
}
