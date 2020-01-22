#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;

	int count = 0;

	int origin = n;
	do {
		int a = n / 10;
		int b = n % 10;

		n = b * 10 + (a + b) % 10;
		++count;
	} while (n != origin);
	
	cout << count;
}