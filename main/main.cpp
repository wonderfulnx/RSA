#include <iostream>
#include <random>
#include <fstream>
#include <ctime>
#include "../src/BigInteger.h"
#include "../src/RSA.h"
using namespace std;

int main()
{
    random_device rd;
    mt19937 mt(rd());
    if (!BigInteger::load_prime()) return 0;

	int first_start = clock();
	int cnt = 0;
	for (int i = 0; i < 1000; ++i)
	{
		int start = clock();
		RSA rsa(768, mt);
		int end = clock();
		if (end - start > 1000)
			++cnt;
		if (i % 20 == 0)
			cout << i << endl;
	}
	int final_end = clock();
	cout << "time is : " << final_end - first_start << "ms" << endl;
	cout << cnt << " of 1000 experiments exceeded 1000 ms." << endl;

    return 0;
}
