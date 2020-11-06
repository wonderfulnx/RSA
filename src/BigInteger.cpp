//
// Created by NaXin on 2020/11/6.
//

#include "BigInteger.h"

// Int is stored reversed in vector, the lsb is on the head and the msb is on the tail

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

BigInteger::BigInteger(const BigInteger &n) {
    unit_num = n.unit_num;
    length = n.length;
    is_neg = n.is_neg;
    num = n.num;
}

// ``remove'' the zeros on the back and find the length
void BigInteger::trim() {
    int i = unit_num - 1;
    for (; i > 0; i--)
        if (num[i] != 0) break;
    length = i + 1;
    return;
}

BigInteger BigInteger::abs() const {
    BigInteger ans(*this);
    ans.is_neg = false;
    return ans;
}

int BigInteger::size() const { return length; }

BigInteger BigInteger::operator-() const {
    BigInteger ans(*this);
    if (length == 1 && ans.num[0] == 0) ans.is_neg = false;
    else ans.is_neg = !ans.is_neg;
    return ans;
}

BigInteger operator + (const BigInteger& a, const BigInteger& b) {
    if (b.is_neg) return a - (-b);
    if (a.is_neg) return b - (-a);
    BigInteger ans(a.unit_num);
    int len = max(a.length, b.length);
    for (int i = 0; i < len; i++) {
        ans.num[i] += a.num[i] + b.num[i];
        if (ans.num[i] > a.LOW) {
            ans.num[i + 1] += 1;
            ans.num[i] = ans.get_low(ans.num[i]);
        }
    }
    if (ans.num[len]) ans.length = len + 1;
    else ans.length = len;
    return ans;
}

BigInteger operator - (const BigInteger& a, const BigInteger& b) {
    if (b.is_neg) return a + (-b);
    if (a.is_neg) return -((-a) + b);
    if (a < b) return -(b - a);

    BigInteger ans(a.unit_num);
    int len = max(a.length, b.length);
    for (int i = 0; i < len; i++) {
        ans.num[i] += a.num[i] - b.num[i];
        if (ans.num[i] < 0) {
            ans.num[i + 1] -= 1;
            ans.num[i] += ans.BASE;
        }
    }
    ans.trim();
    return ans;
}

BigInteger operator * (const BigInteger& a, const BigInteger& b) {
    BigInteger ans(a.unit_num);
    ans.is_neg = a.is_neg ^ b.is_neg;

    int len = min(a.length + b.length, a.unit_num);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= i; j++) {
            ans.num[i] += a.num[j] * b.num[i - j];
            if (ans.num[i] > ans.LOW) {
                ans.num[i + 1] += ans.get_hig(ans.num[i]);
                ans.num[i] = ans.get_low(ans.num[i]);
            }
        }
    }
    ans.trim();
    return ans;
}

BigInteger operator / (const BigInteger& a, const BigInteger& b) {

}

BigInteger operator % (const BigInteger& a, const BigInteger& b) {

}

bool operator < (const BigInteger& a, const BigInteger& b) {
    if (a.is_neg && !b.is_neg) return true;
    if (!a.is_neg && a.is_neg) return false;
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

bool operator <= (const BigInteger& a, const BigInteger& b) { return !(b < a); }
bool operator > (const BigInteger& a, const BigInteger& b) { return b < a; }
bool operator >= (const BigInteger& a, const BigInteger& b){ return !(a < b); }
bool operator == (const BigInteger& a, const BigInteger& b) { return !(a < b) && !(b < a); }
bool operator != (const BigInteger& a, const BigInteger& b) { return (a < b) || (b < a); }

ostream& operator << (ostream& out, const BigInteger& a) {
    out << hex << "0x";
    for (int i = a.length - 1; i >= 0; i--) { out.fill('0'); out.width(4); out << a.num[i]; }
    return out;
}