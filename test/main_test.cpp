//
// Created by NaXin on 2020/11/8.
//

#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include "../src/BigInteger.h"
using namespace std;

int RUN_TIME = 100000;
int UNIT_NUM = 128;
string filename = "data/data.txt";

void test_plus() {
    BigInteger a(UNIT_NUM);
    BigInteger b(UNIT_NUM);
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(UNIT_NUM / 2);
        b.random(UNIT_NUM / 2);
        outfile << a << " " << b << endl;
        outfile << a + b << endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_sub() {
    BigInteger a(UNIT_NUM);
    BigInteger b(UNIT_NUM);
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(UNIT_NUM / 2);
        b.random(UNIT_NUM / 2);
        outfile << a << " " << b << endl;
        outfile << a - b << endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_mul() {
    BigInteger a(UNIT_NUM);
    BigInteger b(UNIT_NUM);
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(UNIT_NUM / 2);
        b.random(UNIT_NUM / 2);
        outfile << a << " " << b << endl;
        outfile << a * b << endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_div() {
    BigInteger a(UNIT_NUM);
    BigInteger b(UNIT_NUM);
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(UNIT_NUM / 2);
        b.random(UNIT_NUM / 2);
        outfile << a << " " << b << endl;
        outfile << a / b << " " << a % b <<  endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

int main()
{
    test_plus();
    cout << "finished, Please verify the result with python." << endl;
    return 0;
}