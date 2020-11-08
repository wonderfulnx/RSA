#include <iostream>
#include <random>
#include <fstream>
#include "src/BigInteger.h"
using namespace std;

int main()
{
    random_device rd;
    mt19937 mt(rd());
    int UNIT_NUM = 128;
    BigInteger a(UNIT_NUM, 0x614de8d0);
    BigInteger b(UNIT_NUM, 0xefba);
    BigInteger c(UNIT_NUM, 0xFFFF);

    a.random_prime(UNIT_NUM / 2, mt);
    cout << a << endl;


    return 0;
}
