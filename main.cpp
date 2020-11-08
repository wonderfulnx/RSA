#include <iostream>
#include <random>
#include <fstream>
#include "src/BigInteger.h"
using namespace std;

int main()
{
    int UNIT_NUM = 128;
    BigInteger a(UNIT_NUM, 0x614de8d0);
    BigInteger b(UNIT_NUM, 0xefba);
    BigInteger c(UNIT_NUM, 0xFFFF);
//    a <<= 16;
//    a = a + c;
//    cout << a << " " << b << endl;
    cout << (a / b) << endl << (a % b) << endl;


    return 0;
}
