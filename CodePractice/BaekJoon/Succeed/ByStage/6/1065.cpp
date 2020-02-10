#include <iostream>

using namespace std;

bool isCorrect(int n) {
	if (!(n / 10 / 10)) { return true; }

	int prev = (n / 10) % 10;
	int d = prev - n % 10;
	n /= 100;
	while (n) {
		if (n % 10 - prev != d) {
			return false;
		}
		n /= 10;
	}
	return true;
}

int main() {
	int N;
	cin >> N;
	int count = 0;
	for (int i = 1; i <= N; ++i) {
		if (isCorrect(i)) {
			++count;
		}
	}
	cout << count;
}