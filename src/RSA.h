//
// Created by NaXin on 2020/11/7.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include "BigInteger.h"
/*
 * RSA Class
 *     A function class contains all rsa related functions
 */
class RSA {
public:
    BigInteger e, n; // Public Key
    BigInteger d; // Private Key
    BigInteger p, q; // Primes
    BigInteger phi; // phi(n)

public:
    RSA(int bit_n, mt19937& mt);
    ~RSA() {}

public:
    BigInteger encrypt(const BigInteger& m);
    BigInteger decrypt(const BigInteger& c);
    BigInteger* encrypt_str(const string& m);
    string decrypt_str(const BigInteger *c, int length);
};


#endif //RSA_RSA_H
