# RSA
This is the project for the graduate course "Applied Cryptography" 2020. A simple RSA system is implemented.

The implementation mainly includes a BigInteger class and an RSA class. Prime numbers used in RSA are generated with the Miller Rabbin test. The highlight design is the "Newton Division" algorithm which yields a time complexity of `O(nlog(n))`. The idea is to use a sequence to approximate the `1/B` value when dividing `A` with `B`. Refer to the code for the specific implementation.
