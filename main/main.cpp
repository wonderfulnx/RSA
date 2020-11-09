#include <iostream>
#include <random>
#include <fstream>
#include "../src/BigInteger.h"
using namespace std;

int main()
{
    random_device rd;
    mt19937 mt(rd());
    BigInteger::load_prime();

    BigInteger a(0x614de8d0);
    BigInteger b(0xefba);
    BigInteger c(0xFFFF);

    a.random_prime(512, mt);
    cout << a << endl;


    return 0;
}
