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

    BigInteger a(198);
    BigInteger b(252);
    BigInteger x, y;

    // a.random_prime(512, mt);
    // cout << a << endl;
    BigInteger::ex_gcd(a, b, x, y);
    
    return 0;
}
