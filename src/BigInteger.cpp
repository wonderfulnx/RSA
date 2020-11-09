//
// Created by NaXin on 2020/11/6.
//

#include "BigInteger.h"
#include <fstream>
#include <string>
#include <random>

const int init_prime_num = 1229;
long long primes[init_prime_num];
const BigInteger One(1);
const BigInteger Two(2);
BigInteger curr_moduli;
BigInteger curr_moduli_reciprocal;
int curr_fac_point;

/*
 *  --------------------------------------
 *  Construction Function Area
 *  --------------------------------------
 */
BigInteger::BigInteger(m_int n) {
    is_neg = false;
    len = 0;
    memset(num, 0, sizeof(num));
    while (n) { num[len] = n % base; n /= base; len++; }
    if (len == 0) len = 1;
}

BigInteger::BigInteger(const BigInteger &n) {
    is_neg = n.is_neg;
    len = n.len;
    memcpy(num, n.num, sizeof(num));
}

/*
 *  --------------------------------------
 *  Operators
 *  --------------------------------------
 */
BigInteger BigInteger::operator-() const {
    BigInteger ans(*this);
    if (ans.len == 1 && ans.num[0] == 0) ans.is_neg = false;
    else ans.is_neg = !ans.is_neg;
    return ans;
}

BigInteger operator + (const BigInteger& a, const BigInteger& b) {
    if (b.is_neg) return a - (-b);
    if (a.is_neg) return b - (-a);
    BigInteger ans;
    int len = max(a.len, b.len);
    for (int i = 0; i < len; i++) {
        ans.num[i] += a.num[i] + b.num[i];
        if (ans.num[i] >= base) {
            // do carry only when possible
            if (i + 1 < unit_num) ans.num[i + 1] += 1;
            ans.num[i] -= base;
        }
    }
    ans.trim();
    return ans;
}

BigInteger operator - (const BigInteger& a, const BigInteger& b) {
    if (b.is_neg) return a + (-b);
    if (a.is_neg) return -((-a) + b);
    if (a < b) return -(b - a);

    BigInteger ans;
    int len = max(a.len, b.len);
    for (int i = 0; i < len; i++) {
        ans.num[i] += a.num[i] - b.num[i];
        if (ans.num[i] < 0){
            // do carry only when possible
            if (i + 1 < unit_num) ans.num[i + 1] -= 1;
            ans.num[i] += base;
        }
    }
    ans.trim();
    return ans;
}

BigInteger operator * (const BigInteger& a, const BigInteger& b) {
    BigInteger ans;
    ans.is_neg = a.is_neg ^ b.is_neg;

    int len = a.len + b.len;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= i; j++) ans.num[i] += a.num[j] * b.num[i - j];
        if (ans.num[i] >= base) {
            if (i + 1 < unit_num) ans.num[i + 1] += ans.num[i] / base;
            ans.num[i] %= base;
        }
    }
    ans.trim();
    return ans;
}

m_int operator % (const BigInteger& a, const m_int& b) {
    m_int res = 0;
    for (int i = a.len - 1; i >= 0; i--) {
        res = (a.num[i] + res * base) % b;
    }
    return res;
}

BigInteger operator % (const BigInteger& a, const BigInteger& b) {
    if (a < b) return a;
    if (!(b == curr_moduli)) {
        // change the saved curr_moduli to b
        curr_moduli = b;
        curr_moduli_reciprocal = 1; // this is a big float
        curr_fac_point = curr_moduli.len;
        int lim = curr_moduli.len << 1;
        for (int i = 0; i < 100; i++) {
            // compute an(2-b*an)
            BigInteger two_float;
            two_float.len = curr_fac_point + 1;
            two_float.num[curr_fac_point] = 2;
            curr_moduli_reciprocal = curr_moduli_reciprocal * (two_float - curr_moduli * curr_moduli_reciprocal);
            curr_fac_point <<= 1; // two float multiple, fac point changes
            if (curr_moduli_reciprocal.len > lim) {
                curr_fac_point -= curr_moduli_reciprocal.len - lim;
                curr_moduli_reciprocal.left_shift(curr_moduli_reciprocal.len - lim);
            }
        }
    }
    BigInteger q(a * curr_moduli_reciprocal);
    q.left_shift(curr_fac_point);
    BigInteger res(a - q * curr_moduli);
    while (!(res < curr_moduli)) res = res - curr_moduli;
    return res;
}

bool operator < (const BigInteger& a, const BigInteger& b) {
    if (a.is_neg && !b.is_neg) return true;
    if (!a.is_neg && b.is_neg) return false;
    if (!a.is_neg && !b.is_neg) {
        if (a.len < b.len) return true;
        if (a.len > b.len) return false;
        for (int i = a.len - 1; i >= 0; i--){
            if (a.num[i] > b.num[i]) return false;
            if (a.num[i] < b.num[i]) return true;
        }
        return false;
    }
    else return -b < -a;
}

ostream& operator << (ostream& out, const BigInteger& a) {
    if (a.is_neg) out << "-";
    out << hex << "0x";
    for (int i = a.len - 1; i >= 0; i--) { out.fill('0'); out.width(base_bits / 4); out << a.num[i]; }
    return out;
}

/*
 *  --------------------------------------
 *  Public Function Area
 *  --------------------------------------
 */
BigInteger BigInteger::binpow(const BigInteger &a, const BigInteger &b, const BigInteger &m) {
    // quick pow to get a * b % m
    BigInteger aa(a % m);
    BigInteger res(1);
    m_int cur_unit = 0, tmp = 1;
    while (cur_unit < b.len) {
        if (b.num[cur_unit] & tmp) res = res * aa % m;
        aa = aa * aa % m;
        tmp <<= 1;
        if (tmp >= base) tmp = 1, cur_unit++;
        // highest unit, no longer need to compute
        if (cur_unit == b.len - 1 && tmp > b.num[cur_unit]) break;
    }
    res.trim();
    return res;
}

void BigInteger::random(int bit_n, mt19937& mt) {
    int i = 0;
    uniform_int_distribution<m_int> dist(0, base - 1);
    for (; i < bit_n / base_bits; i++)
        num[i] = dist(mt) & (base - 1);
    num[i] = dist(mt) & ((1ll << (bit_n % base_bits)) - 1);
    trim();
}

void BigInteger::random(const BigInteger& n, mt19937& mt) {
    this->random(n.len * base_bits, mt);
    *this = *this % n;
}

void BigInteger::random_prime(int bit_n, mt19937& mt) {
    this->random(bit_n, mt);
    while (1) {
        // set the highest bit and lowest bit to 1
        if (bit_n % base_bits) this->num[len - 1] |= (1ll << (bit_n % base_bits - 1));
        else this->num[len - 1] |= (base >> 1);
        this->num[0] |= 1;
        trim();

        int j = 0;
        for (; j < init_prime_num; j++)
            if (*this % primes[j] == 0) break;
        if (j == init_prime_num && this->miller_rabbin(10, mt)) break;
        else *this = *this + Two;
    }
}

void BigInteger::load_prime() {
    ifstream infile;
    infile.open("prime.txt");
    m_int data;
    for (int i = 0; i < init_prime_num; i++) {
        infile >> data;
        primes[i] = data;
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
    len = i + 1;

    // for debug
    for (int j = 0; j < unit_num; j++) if (num[j] >= base) throw "Trim: a number exceeds LOW!";
}

void BigInteger::left_shift(int unit_n) {
    for (int i = 0; i < len - unit_n; i++) num[i] = num[i + unit_n];
    for (int i = len - unit_n; i < len; i++) num[i] = 0;
    len = len - unit_n;
}

bool BigInteger::miller_rabbin(int test_time, mt19937& mt) {
    if (*this < 3) return (*this) == 2;
    BigInteger n_1(*this - One), d(n_1), a, x;
    int s = 0;

    // compute n_1 = d * 2 ^ s
    while ((d.num[s / base_bits] & (1 << (s % base_bits))) == 0) s++;
    int unit_n = s / base_bits;
    int bit_n = s % base_bits;
    for (int i = unit_n; i < d.len; i++) d.num[i - unit_n] = d.num[i];
    for (int i = d.len - unit_n; i < d.len; i++) d.num[i] = 0;
    for (int i = 0; i < d.len; i++)
        d.num[i] = (d.num[i] >> bit_n) | (d.num[i + 1] & ((1ll << bit_n) - 1) << (base_bits - bit_n));
    d.trim();

    // if test time is k, then the error rate is 1/4^(k)
    for (int i = 0, r; i < test_time; i++) {
        a.random(*this - Two, mt); a = a + Two;
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




