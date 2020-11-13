//
// Created by NaXin on 2020/11/7.
//

#include "RSA.h"
#include <ctime>
#include <string>
#include <random>

const BigInteger One(1);

RSA::RSA(int bit_n, mt19937& mt) {
    // generate keys for RSA-n
    int start_ts = clock();
    int len = bit_n / 2;

    this->p = BigInteger(); this->p.random_prime(len, mt);
    this->q = BigInteger(); this->q.random_prime(len, mt);

    this->n = p * q;
    this->phi = (p - One) * (q - One);

    BigInteger t, y;
    this->e = BigInteger();
    this->d = BigInteger();
    this->e.random_prime(len, mt);
    t = BigInteger::ex_gcd(e, phi, d, y);
    if (!(t == One)) throw "GCD result is not 1!";
    d = ((d % phi) + phi) % phi;

    cout << "key generation used " << clock() - start_ts << "ms" << endl;
}

BigInteger RSA::encrypt(const BigInteger& m) {
    return BigInteger::binpow(m, e, n);
}

BigInteger RSA::decrypt(const BigInteger& c) {
    return BigInteger::binpow(c, d, n);
}

BigInteger* RSA::encrypt_str(string& m) {
    int len = m.size();
    BigInteger* res = new BigInteger[len];
    for (int i = 0; i < len; i++) {
        BigInteger t((int)m[i]);
        res[i] = encrypt(t);
    }
    return res;
}

string RSA::decrypt_str(const BigInteger* c, int length) {
    string res;
    for (int i = 0; i < length; i++) {
        BigInteger m = decrypt(c[i]);
        res.push_back((char)m.num[0]);
    }
    return res;
}


