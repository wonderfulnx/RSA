#include <iostream>
#include "src/BigInteger.h"
using namespace std;

int main()
{
    BigInteger a(2, 0xFFFFFFFF);
    BigInteger b(2, 0x00010000);
    BigInteger c(2, 0x0000FFFF);

    BigInteger d = a * b * b * b + a * b + c;
    cout << d << ", " << d.size() << endl;
    cout << d*d << endl;

//    cout << a << endl << a.size() << endl;
//    cout << b << endl << b.size() << endl;
//    cout << a * b << endl << (a * b).size() << endl;

    return 0;
}
