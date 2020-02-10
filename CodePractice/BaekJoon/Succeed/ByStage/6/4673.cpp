#include <iostream>

using namespace std;

int d(int n) {
	int c = n;
	while (n) {
		c += n % 10;
		n /= 10;
	}
	return c;
}

int main() {
	bool checks[10001] = { false, };
	for (int i = 1; i <= 10000; ++i) {
		int c = d(i);
		while (c <= 10000 && !checks[c]) {
			checks[c] = true;
			c = d(c);
		}
	}
	for (int i = 1; i < 10001; ++i) {
		if (!checks[i]) {
			cout << i << endl;
		}
	}
}