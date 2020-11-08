#include <iostream>
#include <random>
#include <fstream>
#include "src/BigInteger.h"
using namespace std;

int main()
{
    int UNIT_NUM = 128;
    BigInteger a(UNIT_NUM);
    BigInteger b(UNIT_NUM);
    ofstream outfile;
    outfile.open("data/data.txt");

    for (int i = 0; i < 100000; i++) {
        a.random(UNIT_NUM / 2);
        b.random(UNIT_NUM / 2);
        outfile << a << " " << b << endl;
        outfile << a / b << " " << a % b << endl;
        if (i % 10000 == 0) cout << "done with " << i << endl;
    }
    outfile.close();
    return 0;
}
