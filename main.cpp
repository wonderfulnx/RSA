#include <iostream>
#include <random>
#include "src/BigInteger.h"
using namespace std;

int main()
{
    BigInteger a(32, 0x00010001);
    BigInteger b(32, 0x00010000);
    BigInteger c(32, 0xFFFFFFFF);
//    a = a * b;
    cout << a << " " << endl; cout << a.miller_rabbin(10) << endl;
//    c.random(a);
//    cout << c.miller_rabbin(10) << endl;

//    BigInteger c(32);
//    c = a * b * b + a;
//
//    cout << c.neg() << " " << c << endl;
//    cout << (c/a) << " " << c%a << endl;
//    cout << a << endl << a.size() << endl;
//    cout << b << endl << b.size() << endl;
//    cout << a * b << endl << (a * b).size() << endl;
//    BigInteger b(a);
//    cout << (a > 0) << endl;
//
//    a = a << 4;
//    cout << (a >> 0) << endl;
//    cout << (a >> 1) << endl;
//    cout << (a >> 2) << endl;
//    cout << (a >> 3) << endl;
//    cout << (a >> 4) << endl;
//    cout << (a >> 5) << endl;
//    cout << (a >> 6) << endl;
//    cout << (a >> 7) << endl;
//    cout << (a >> 8) << endl;
//    cout << (a >> 9) << endl;
//    cout << (a >> 10) << endl;
//    cout << (a >> 11) << endl;
//    cout << (a >> 12) << endl;
//    cout << (a >> 13) << endl;
//    cout << (a >> 14) << endl;
//    cout << (a >> 15) << endl;
//    cout << (a >> 16) << endl;

    return 0;
}
