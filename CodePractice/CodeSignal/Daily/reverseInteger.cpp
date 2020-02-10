#include <iostream>

using namespace std;

//https://app.codesignal.com/challenge/jiDd9pPSvaLzxjZrG

int reverseInteger(int x) {
	int res = 0;
	while (x) {
		res += x % 10;
		res *= 10;
		x /= 10;
	}
	return res / 10;
}

int main() {
	cout << reverseInteger(12345) << endl; // 54321
	cout << reverseInteger(-4243) << endl; // -3424
}