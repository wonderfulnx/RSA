#include <iostream>
#include <random>
#include <fstream>
#include "../src/BigInteger.h"
#include "../src/RSA.h"
using namespace std;

int main()
{
    random_device rd;
    mt19937 mt(rd());
    BigInteger::load_prime();

    /*RSA rsa(768, mt);
    BigInteger m(47324832);
    BigInteger c(rsa.encrypt(m));
    BigInteger res(rsa.decrypt(c));

    cout << "origin num: " << m << endl;
    cout << "encrypt num: " << c << endl;
    cout << "decrypt num: " << res << endl;*/

    RSA rsa(768, mt);
    string m = "fguyisewgfwseif";
    BigInteger* C = rsa.encrypt_str(m);
    string res = rsa.decrypt_str(C, m.size());

    cout << "origin string: " << m << endl;
    cout << "decrypt string: " << res << endl;
    delete[] C;
    
    return 0;
}
