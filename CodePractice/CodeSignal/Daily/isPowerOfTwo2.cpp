#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/challenge/o4P4CzeyHATP9xfm3

bool isPowerOfTwo2(long long n) {
	while (n % 2 == 0) {
		n /= 2;
	}
	return n == 1;
}

int main() {
	cout << isPowerOfTwo2(64) << endl; // true
	cout << isPowerOfTwo2(5) << endl; // false
}