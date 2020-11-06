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
    inline m_uint get_low(m_uint a) {return a & LOW;}
    inline m_uint get_hig(m_uint a) {return a >> 16;}

private:
    // requires unit num, 1 unit means able to store a half m_uint
    int unit_num;
    int length;
    bool is_neg; // is_neg = 1 means a negative number
    vector<m_uint> num;

public:
    BigInteger(int unit_n);
    BigInteger(int unit_n, m_uint n);
    BigInteger(const BigInteger& n);

    int size() const;
    BigInteger abs() const;

public:
    BigInteger operator-() const;
    friend BigInteger operator + (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator - (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator * (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator / (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator % (const BigInteger& a, const BigInteger& b);

    friend bool operator < (const BigInteger& a, const BigInteger& b);
    friend bool operator > (const BigInteger& a, const BigInteger& b);
    friend bool operator <= (const BigInteger& a, const BigInteger& b);
    friend bool operator >= (const BigInteger& a, const BigInteger& b);
    friend bool operator == (const BigInteger& a, const BigInteger& b);
    friend bool operator != (const BigInteger& a, const BigInteger& b);
    friend ostream& operator << (ostream& out, const BigInteger& a);

private:
    void trim(); // cut leading zeros
};


#endif //RSA_BIGINTEGER_H
