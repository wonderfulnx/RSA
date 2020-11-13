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

private:
    BigInteger d; // Private Key
    BigInteger p, q; // Primes
    BigInteger phi; // \phi(n)

public:
    RSA();
    ~RSA();
    void init(int n);

public:
    // BigInteger encr
};


#endif //RSA_RSA_H
