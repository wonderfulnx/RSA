//
// Created by NaXin on 2020/11/6.
//

#ifndef RSA_BIGINTEGER_H
#pragma comment(linker, "/STACK:52428800")
#define RSA_BIGINTEGER_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <random>
using namespace std;

typedef long long m_int;
const int base_bits = 24;
const int max_bit_num = 2048;
const long long base = 1ll << base_bits;
const int unit_num = max_bit_num * 4 * 2 / base_bits + 10;

/*
 * Big Integer Class
 * 
 * - Change max_bit_num to supprt higher bits
 * - base bits are used to store number
 * - primes are predefined.
 * - Int is stored reversed in vector
 * - The lsb is on the head and the msb is on the tail
 */
class BigInteger {
public:
    int len;
    bool is_neg;
    m_int num[unit_num];

public: // basic functions
    BigInteger(m_int n = 0);
    BigInteger(const BigInteger& n);
    const BigInteger& operator=(m_int n);
    const BigInteger& operator=(const BigInteger& n);
    ~BigInteger() { }

    BigInteger operator-() const;
    friend BigInteger operator + (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator - (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator * (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator % (const BigInteger& a, const BigInteger& b);
    friend m_int operator % (const BigInteger& a, const m_int& b);

    friend bool operator < (const BigInteger& a, const BigInteger& b);
    friend bool operator == (const BigInteger& a, const BigInteger& b) { return !(a < b) && !(b < a);}
    friend ostream& operator << (ostream& out, const BigInteger& a);
    string to_hex(int length = 0);

public:
    static bool load_prime();
    void random(int bit_n, mt19937& mt); // random a number with bit_n bits
    void random_prime(int bit_n, mt19937& mt); // random a prime with bit_n bits
    void random(const BigInteger& n, mt19937& mt); // random a number less than n
    bool miller_rabbin(int test_time, mt19937& mt); //miller rabbin test for prime
    static BigInteger binpow(const BigInteger& a, const BigInteger& b, const BigInteger& m);
    static BigInteger ex_gcd(const BigInteger& a, const BigInteger& b, BigInteger& x, BigInteger& y);
        
private:
    void trim(); // cut leading zeros
    void left_shift(int unit_n);
};

#endif //RSA_BIGINTEGER_H
