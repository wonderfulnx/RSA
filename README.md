# RSA
This is the project for the graduate course "Applied Cryptography" 2020. A simple RSA system is implemented.

The implementation mainly includes a BigInteger class and a RSA class. Primes numbers used in RSA is generated with miller rabbin test. The highlight design is the "Newton Division" algorithm which give a time complexity of `O(nlog(n))`. The insight is to use a sequence to approximate the `1/B` value when doing `A/B`. Refer the code for the specific implementation.
