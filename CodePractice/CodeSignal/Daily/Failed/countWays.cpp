#include <iostream>
#include <cmath>

using namespace std;

// https://app.codesignal.com/challenge/a8GNsYr8FQxZmMhJj

int countWays(int n, int k) {
	int res = 1;
	for (int i = 0; i < k; ++i) {
		res = res * (n - i) / (i + 1);
		res %= static_cast<int>(pow(10, 9) + 7);
		cout << "res : " << res << endl;
	}

	return res;
}

int main() {
	cout << countWays(12, 5) << endl;
}