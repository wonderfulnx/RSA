//
// Created by NaXin on 2020/11/6.
//

#include "BigInteger.h"
#include <random>
#include <fstream>

// Int is stored reversed in vector, the lsb is on the head and the msb is on the tail

/*
 *  --------------------------------------
 *  Construction Function Area
 *  --------------------------------------
 */
BigInteger::BigInteger(int unit_n) {
    unit_num = unit_n;
    length = 1;
    is_neg = false;
    num = vector<m_uint>(unit_num);
}

BigInteger::BigInteger(int unit_n, m_uint n) {
    unit_num = unit_n;
    is_neg = false;
    num = vector<m_uint>(unit_num);
    num[0] = get_low(n);
    num[1] = get_hig(n);
    if (num[1] == 0) length = 1;
    else length = 2;
}

BigInteger::BigInteger(int unit_n, const BigInteger &n) {
    unit_num = unit_n;
    is_neg = false;
    length = 1;
    num = vector<m_uint>(unit_num);
    *this = n;
}

const BigInteger& BigInteger::operator=(const BigInteger &n) {
    if (n.unit_num != unit_num) throw "Failed to assign, unit num not the same!";
    length = n.length;
    is_neg = n.is_neg;
    for (int i = 0; i < unit_num; i++) num[i] = n.num[i];
    return *this;
}

/*
 *  --------------------------------------
 *  Basic Public Function
 *  --------------------------------------
 */
BigInteger BigInteger::abs() const {
    BigInteger ans(*this);
    ans.is_neg = false;
    return ans;
}

bool BigInteger::neg() const { return is_neg; }

int BigInteger::size() const { return length; }

/*
 *  --------------------------------------
 *  Public Operator Area
 *  --------------------------------------
 */
BigInteger BigInteger::operator-() const {
    BigInteger ans(this->unit_num, *this);
    if (length == 1 && ans.num[0] == 0) ans.is_neg = false;
    else ans.is_neg = !ans.is_neg;
    return ans;
}

BigInteger operator + (const BigInteger& a, const BigInteger& b) {
    if (b.is_neg) return a - (-b);
    if (a.is_neg) return b - (-a);
    BigInteger ans(max(a.unit_num, b.unit_num));
    int len = max(a.length, b.length);
    for (int i = 0; i < len; i++) {
        BigInteger::m_uint aa = (i < a.length)? a.num[i] : 0;
        BigInteger::m_uint bb = (i < b.length)? b.num[i] : 0;
        ans.num[i] += aa + bb;
        if (ans.num[i] > BigInteger::LOW) {
            // do carry only when possible
            if (i + 1 < ans.unit_num) ans.num[i + 1] += 1;
            ans.num[i] = BigInteger::get_low(ans.num[i]);
        }
    }
    ans.trim();
    return ans;
}

BigInteger operator - (const BigInteger& a, const BigInteger& b) {
    if (b.is_neg) return a + (-b);
    if (a.is_neg) return -((-a) + b);
    if (a < b) return -(b - a);

    BigInteger ans(max(a.unit_num, b.unit_num));
    int len = max(a.length, b.length);
    unsigned int carry = 0;
    for (int i = 0; i < len; i++) {
        BigInteger::m_uint aa = (i < a.length)? a.num[i] : 0;
        BigInteger::m_uint bb = (i < b.length)? b.num[i] : 0;
        if (aa < bb + carry) {
            // requires carry
            ans.num[i] = BigInteger::BASE + aa - bb - carry;
            carry = 1;
        }
        else {
            ans.num[i] = aa - bb - carry;
            carry = 0;
        }
    }
    ans.trim();
    return ans;
}

// Multiple should only be done when a.unit_num == b.unit_num
BigInteger operator * (const BigInteger& a, const BigInteger& b) {
    if (a.unit_num != b.unit_num) throw "Multiple numbers must have the same unit num.";

    BigInteger ans(a.unit_num);
    ans.is_neg = a.is_neg ^ b.is_neg;

    int len = min(a.length + b.length, a.unit_num);
    for (int i = 0; i < len; i++) {
        // every time reaches i, check if carry required, make sure num[i] is lower than BASE
        if (ans.num[i] > BigInteger::LOW) {
            if (i + 1 < ans.unit_num) ans.num[i + 1] += ans.get_hig(ans.num[i]); // only if carry is able to take place, we do carry
            ans.num[i] = BigInteger::get_low(ans.num[i]);
        }
        for (int j = 0; j <= i; j++) {
            // start to compute number in num[i].
            // num[i] is sure to be lower than BASE currently, this += will not cause a overflow
            ans.num[i] += a.num[j] * b.num[i - j];
            // do the same carry again every time, same as up there
            if (ans.num[i] > BigInteger::LOW) {
                if (i + 1 < ans.unit_num) ans.num[i + 1] += ans.get_hig(ans.num[i]);
                ans.num[i] = BigInteger::get_low(ans.num[i]);
            }
        }
    }
    ans.trim();
    return ans;
}

BigInteger operator / (const BigInteger& a, const BigInteger& b) {
    if (a.unit_num != b.unit_num) throw "Division numbers must have the same unit num.";
    BigInteger c(a.unit_num), d(a.unit_num);
    div(a, b, c, d);
    return c;
}

BigInteger operator % (const BigInteger& a, const BigInteger& b) {
    if (a.unit_num != b.unit_num) throw "Division numbers must have the same unit num.";
    BigInteger c(a.unit_num), d(a.unit_num);
    div(a, b, c, d);
    return d;
}

bool operator < (const BigInteger& a, const BigInteger& b) {
    if (a.is_neg && !b.is_neg) return true;
    if (!a.is_neg && b.is_neg) return false;
    if (!a.is_neg && !b.is_neg) {
        if (a.length < b.length) return true;
        if (a.length > b.length) return false;
        for (int i = a.length - 1; i >= 0; i--){
            if (a.num[i] > b.num[i]) return false;
            if (a.num[i] < b.num[i]) return true;
        }
        return false;
    }
    else return -b < -a;
}

bool operator < (const BigInteger& a, const BigInteger::m_uint &b) {
    if (a.is_neg) return true;
    if (a.length > 1) return false;
    return a.num[0] < b;
}

bool operator > (const BigInteger& a, const BigInteger::m_uint &b) {
    if (a.is_neg) return false;
    if (a.length > 1) return true;
    return a.num[0] > b;
}

ostream& operator << (ostream& out, const BigInteger& a) {
    if (a.is_neg) out << "-";
    out << hex << "0x";
    for (int i = a.length - 1; i >= 0; i--) { out.fill('0'); out.width(4); out << a.num[i]; }
    return out;
}

const BigInteger& BigInteger::operator<<=(const BigInteger::m_uint &b) {
    // left shift, only support no more than BITS_PER_UNIT.
    // remember number is stored reversely
    if (b > BITS_PER_UNIT) throw "left shift only support no more than BITS_PER_UNIT bit.";
    BigInteger::m_uint mask = ((1 << b) - 1) << BigInteger::BITS_PER_UNIT;
    BigInteger::m_uint carry = 0;
    BigInteger::m_uint temp = 0;
    for (int i = 0; i < unit_num; i++) {
        temp = num[i] << b;
        num[i] = BigInteger::get_low(temp) | carry;
        carry = (temp & mask) >> BigInteger::BITS_PER_UNIT;
    }
    trim();
    return *this;
}

const BigInteger& BigInteger::operator>>=(const BigInteger::m_uint &b) {
    // right shift, only support no more than BITS_PER_UNIT.
    // remember number is stored reversely
    if (b > BITS_PER_UNIT) throw "right shift only support no more than BITS_PER_UNIT bit.";
    BigInteger::m_uint mask = ((1 << b) - 1);
    BigInteger::m_uint carry = 0;
    BigInteger::m_uint n_car = 0;
    for (int i = unit_num - 1; i >= 0; i--) {
        n_car = (num[i] & mask) << (BigInteger::BITS_PER_UNIT - b);
        num[i] = BigInteger::get_low(num[i] >> b) | carry;
        carry = n_car;
    }
    trim();
    return *this;
}

BigInteger operator<<(const BigInteger &a, const BigInteger::m_uint &b) {
    BigInteger ans(a.unit_num, a);
    ans <<= b;
    return ans;
}

BigInteger operator>>(const BigInteger &a, const BigInteger::m_uint &b) {
    BigInteger ans(a.unit_num, a);
    ans >>= b;
    return ans;
}

/*
 *  --------------------------------------
 *  Public Function Area
 *  --------------------------------------
 */
BigInteger BigInteger::binpow(const BigInteger &a, const BigInteger &b, const BigInteger &m) {
    // quick pow to get a * b % m
    if (a.unit_num != b.unit_num || a.unit_num != m.unit_num) throw "BinPow can only be done with the same unit num.";
    BigInteger aa(a.unit_num ,a % m), bb(b.unit_num, b);
    BigInteger res(a.unit_num, 1);
    while (bb > 0) {
        if (bb.num[0] & 1) res = res * aa % m;
        aa = aa * aa % m;
        bb >>= 1;
    }
    res.trim();
    return res;
}

void BigInteger::random(const BigInteger& n, mt19937& mt) {
    uniform_int_distribution<BigInteger::m_uint> dist(0, LOW);
    for (int i = 0; i < n.length; i++) this->num[i] = dist(mt) & LOW;
    trim();
    *this = *this % n;
}

void BigInteger::random(int unit_n, mt19937& mt) {
    if (unit_n > this->unit_num) throw "Unit number too large.";

    uniform_int_distribution<BigInteger::m_uint> dist(0, LOW);
    int i = 0;
    for (; i < unit_n; i++) this->num[i] = dist(mt) & LOW;
    for (; i < unit_num; i++) this->num[i] = 0;
    trim();
}

void BigInteger::random_prime(int unit_n, mt19937& mt) {
    if (unit_n > this->unit_num) throw "Unit number too large.";

    int i = 0;
    BigInteger TWO(this->unit_num, 2);
    uniform_int_distribution<BigInteger::m_uint> dist(0, LOW);
    for (; i < unit_n; i++) this->num[i] = dist(mt) & LOW;
    for (; i < unit_num; i++) this->num[i] = 0;

    while (1) {
        this->num[unit_n - 1] |= (1 << (BITS_PER_UNIT - 1));
        this->num[0] |= 1;
        trim();

        int j = 0;
        for (; j < primes.size(); j++)
            if (*this % primes[i] == 0) break;
        if (j == primes.size() && this->miller_rabbin(10, mt)) break;
        else *this = *this + 2;
    }
}

void BigInteger::load_prime(int unit_n) {
    primes = vector<BigInteger>();
    ifstream infile;
    infile.open("prime.txt");
    BigInteger::m_uint data;
    while (!infile.eof()) {
        infile >> data;
        if (data) primes.push_back(BigInteger(unit_n, data));
    }
    infile.close();
}

/*
 *  --------------------------------------
 *  Private Function Area
 *  --------------------------------------
 */
// ``remove'' the zeros on the back and find the length
void BigInteger::trim() {
    int i = unit_num - 1;
    for (; i > 0; i--)
        if (num[i] != 0) break;
    length = i + 1;

    // for debug
    for (int j = 0; j < unit_num; j++) if (num[j] > LOW) throw "Trim: a number exceeds LOW!";
}

int greater_eq(const BigInteger &a, const BigInteger &b, int last_dg) {
    // Dividend a and divisor b. Take last_dg as the lowest bit in a, return if a can sub b
    // 2 -> overlong, 1 -> able to sub, 0 -> not able to sub
    int len = b.length;
    if (last_dg + len < a.unit_num && a.num[last_dg + len] != 0) return 2;
    // start from high bit to low bit
    for (int i = len - 1; i >= 0; i--) {
        if (a.num[last_dg + i] > b.num[i]) return 1;
        if (a.num[last_dg + i] < b.num[i]) return 0;
    }
    return 1; // true if equal
}

void div(const BigInteger &a, const BigInteger &b, BigInteger &c, BigInteger &d) {
    // for div function, all a, b, c, and d should have the same unit_num;
    if (a.unit_num != b.unit_num || a.unit_num != c.unit_num || a.unit_num != d.unit_num) throw "Multiple numbers must have the same unit num.";
    if (b.length == 1 && b.num[0] == 0) throw "Division by zero!";

    vector<BigInteger::m_uint> tmp(b.length + 1); // store the temp res of b.length * over_number
    // c is quotient and d is remainder
    for (int i = 0; i < a.length; i++) d.num[i] = a.num[i];
    for (int i = a.length - b.length; i >= 0; i--) {
        while (greater_eq(d, b, i) == 2) {
            // over long. we do ``d -= b * over_number'' and ``c[i] += over_number''
            BigInteger::m_uint over_num = d.num[i + b.length];
            // step 1: compute b * over_number
            for (int k = 0; k < b.length; k++) tmp[k] = b.num[k] * over_num;
            tmp[b.length] = 0;
            for (int k = 0; k < b.length; k++) if (tmp[k] > BigInteger::LOW) {
                tmp[k + 1] += BigInteger::get_hig(tmp[k]);
                tmp[k] = BigInteger::get_low(tmp[k]);
            }
            // step 2: d -= res, but take i as start
            unsigned int carry = 0;
            for (int j = 0; j <= b.length; j++) {
                if (d.num[i + j] < tmp[j] + carry) {
                    // requires carry
                    d.num[i + j] = d.num[i + j] + BigInteger::BASE - tmp[j] - carry;
                    carry = 1;
                }
                else d.num[i + j] -= tmp[j] + carry, carry = 0;
            }
            c.num[i] += over_num;
        }

        while (greater_eq(d, b, i) == 1) {
            // start to subtract
            unsigned int carry = 0;
            for (int j = 0; j < b.length; j++) {
                // a in-place sub
                if (d.num[i + j] < b.num[j] + carry) {
                    // requires carry
                    d.num[i + j] = d.num[i + j] + BigInteger::BASE - b.num[j] - carry;
                    carry = 1;
                }
                else d.num[i + j] -= b.num[j] + carry, carry = 0;
            }
            if (i + b.length < a.length) d.num[i + b.length] -= carry;
            c.num[i] += 1;
        }
    }

    c.is_neg = a.is_neg ^ b.is_neg;
    d.is_neg = a.is_neg;
    c.trim(); d.trim();
}

bool BigInteger::miller_rabbin(int test_time, mt19937& mt) {
    if (*this < 3) return (*this) == 2;
    BigInteger ONE(this->unit_num, 1);
    BigInteger TWO(this->unit_num, 2);
    BigInteger n_1(this->unit_num, *this - ONE);
    BigInteger d(this->unit_num, n_1);
    BigInteger a(this->unit_num);
    BigInteger x(this->unit_num);
    int s = 0;

    while ((d.num[0] & 1) == 0) d >>= 1, s++;
    // if test time is k, then the error rate is 1/4^(k)
    for (int i = 0, r; i < test_time; i++) {
        a.random(*this - TWO, mt); a = a + TWO;
        x = binpow(a, d, *this);
        if (x == 1 || x == n_1) continue;
        for (r = 0; r < s - 1; r++) {
            x = x * x % (*this);
            if (x == 1) return false;
            if (x == n_1) break;
        }
        if (r >= s - 1) return false;
    }
    return true;
}



