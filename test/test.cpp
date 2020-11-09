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

int RUN_TIME = 20000;
int BIT_NUM = 768;
string filename = "data.txt";
random_device rd;
mt19937 mt(rd());

void test_plus() {
    BigInteger a;
    BigInteger b;
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(BIT_NUM, mt);
        b.random(BIT_NUM, mt);
        outfile << a << " " << b << endl;
        outfile << a + b << endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_sub() {
    BigInteger a;
    BigInteger b;
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(BIT_NUM, mt);
        b.random(BIT_NUM, mt);
        outfile << a << " " << b << endl;
        outfile << a - b << endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_mul() {
    BigInteger a;
    BigInteger b;
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(BIT_NUM / 2, mt);
        b.random(BIT_NUM / 2, mt);
        outfile << a << " " << b << endl;
        outfile << a * b << endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_div() {
    BigInteger a;
    BigInteger b;
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(BIT_NUM, mt);
        b.random(BIT_NUM / 2, mt);
        outfile << a << " " << b << endl;
        outfile << a % b <<  endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_binpow() {
    BigInteger a;
    BigInteger b;
    BigInteger m;
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        a.random(BIT_NUM / 2, mt);
        b.random(BIT_NUM / 2, mt);
        m.random(BIT_NUM / 2, mt);
        outfile << a << " " << b << " " << m << endl;
        outfile << BigInteger::binpow(a, b, m) <<  endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

void test_miller() {
    BigInteger p;
    ofstream outfile;
    outfile.open(filename);

    for (int i = 0; i < RUN_TIME; i++) {
        p.random(BIT_NUM / 2, mt);
        outfile << p << endl;
        outfile << p.miller_rabbin(10, mt) << endl;
        if (i % (RUN_TIME / 10) == 0) cout << "done with " << i << endl;
    }
    outfile.close();
}

int main()
{
    BigInteger::load_prime();

    //test_plus();
    //test_sub();
    //test_mul();
    //test_div();
    //test_binpow();
    test_miller();

    cout << "finished, Please verify the result with python." << endl;
    return 0;
}