//
// Created by NaXin on 2020/11/8.
//

#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <random>
#include "../src/BigInteger.h"
using namespace std;

int RUN_TIME = 100000;
int UNIT_NUM = 128;
string filename = "data.txt";
random_device rd;
mt19937 mt(rd());

void test_plus() {
    BigInteger a(UNIT_NUM);
    BigInteger b(UNIT_NUM);
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(UNIT_NUM / 2, mt);
        b.random(UNIT_NUM / 2, mt);
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
        a.random(UNIT_NUM / 2, mt);
        b.random(UNIT_NUM / 2, mt);
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
        a.random(UNIT_NUM / 2, mt);
        b.random(UNIT_NUM / 2, mt);
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
        a.random(UNIT_NUM, mt);
        b.random(UNIT_NUM / 2, mt);
        outfile << a << " " << b << endl;
        outfile << a / b << " " << a % b <<  endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_binpow() {
    BigInteger a(UNIT_NUM);
    BigInteger b(UNIT_NUM);
    BigInteger m(UNIT_NUM);
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(UNIT_NUM / 2, mt);
        b.random(UNIT_NUM / 2, mt);
        m.random(UNIT_NUM / 2, mt);
        outfile << a << " " << b << " " << m << endl;
        outfile << BigInteger::binpow(a, b, m) <<  endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

int main()
{
    test_binpow();
    cout << "finished, Please verify the result with python." << endl;
    return 0;
}