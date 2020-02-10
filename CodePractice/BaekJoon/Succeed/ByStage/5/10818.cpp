#include <iostream>

using namespace std;

int main() {
	int N;
	cin >> N;

	int min = 1000001;
	int max = -1000001;
	for (int i = 0; i < N; ++i) {
		int P;
		cin >> P;
		if (P < min) {
			min = P;
		}
		if (max < P) {
			max = P;
		}
	}
	cout << min << " " << max;
}