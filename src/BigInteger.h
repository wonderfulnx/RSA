//
// Created by NaXin on 2020/11/6.
//

#ifndef RSA_BIGINTEGER_H
#define RSA_BIGINTEGER_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInteger {
public:
    // 32 bits in one unit, takes half of it to store number
    typedef uint32_t m_uint;
    static const int BITS_PER_UNIT = 16;
    static const m_uint LOW = 0x0000FFFF;
    static const m_uint HIG = 0xFFFF0000;
    static const m_uint BASE = 0x00010000; // BASE is low + 1
private:
    inline static m_uint get_low(m_uint a) {return a & LOW;}
    inline static m_uint get_hig(m_uint a) {return a >> 16;}

private:
    // requires unit num, 1 unit means able to store a half m_uint
    int unit_num;
    int length;
    bool is_neg; // is_neg = 1 means a negative number
    vector<m_uint> num;

public: // basic functions
    BigInteger(int unit_n);
    BigInteger(int unit_n, m_uint n);
    BigInteger(int unit_n, const BigInteger& n);

    const BigInteger& operator=(const BigInteger &n);

    int size() const;
    bool neg() const;
    BigInteger abs() const;

public: // public operators
    BigInteger operator-() const;
    friend BigInteger operator + (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator - (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator * (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator / (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator % (const BigInteger& a, const BigInteger& b);

    friend bool operator < (const BigInteger& a, const BigInteger& b);
    friend bool operator <= (const BigInteger& a, const BigInteger& b) { return !(b < a); }
    friend bool operator > (const BigInteger& a, const BigInteger& b) { return b < a; }
    friend bool operator >= (const BigInteger& a, const BigInteger& b){ return !(a < b); }
    friend bool operator == (const BigInteger& a, const BigInteger& b) { return !(a < b) && !(b < a); }
    friend bool operator != (const BigInteger& a, const BigInteger& b) { return (a < b) || (b < a); }

    friend bool operator < (const BigInteger& a, const m_uint& b);
    friend bool operator <= (const BigInteger& a, const m_uint &b) { return !(a > b); }
    friend bool operator >  (const BigInteger& a, const m_uint &b);
    friend bool operator >= (const BigInteger& a, const m_uint &b) { return !(a < b); }
    friend bool operator == (const BigInteger& a, const m_uint &b) { return !(a < b) && !(a > b); }
    friend bool operator != (const BigInteger& a, const m_uint &b) { return (a < b) || (a > b); }

    friend ostream& operator << (ostream& out, const BigInteger& a);
    friend BigInteger operator << (const BigInteger& a, const BigInteger::m_uint &b);
    friend BigInteger operator >> (const BigInteger& a, const BigInteger::m_uint &b);
    const BigInteger& operator <<=(const BigInteger::m_uint &b);
    const BigInteger& operator >>=(const BigInteger::m_uint &b);

public:
    void random(const BigInteger& n); // random a int less than n
    void random(int unit_n); // random a int with unit_n units
    void random_prime(int unit_n); // random a prime with length no more than unit_n
    static BigInteger binpow(const BigInteger& a, const BigInteger& b, const BigInteger& m);

private:
    void trim(); // cut leading zeros
public:
    bool miller_rabbin(int test_time); //miller rabbin test for prime

    inline friend bool greater_eq(const BigInteger& a, const BigInteger& b, int last_dg);
    friend void div(const BigInteger& a, const BigInteger& b, BigInteger& c, BigInteger &d);
};


#endif //RSA_BIGINTEGER_H
