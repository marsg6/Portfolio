#include <iostream>
#include <vector>

using namespace std;

int main() {
	int M, N;
	cin >> M >> N;

	vector<int> increases(2 * M - 1, 1);
	for (int i = 0; i < N; ++i) {
		int zero, one, two;
		cin >> zero >> one >> two;

		for (int j = zero; j < zero + one; ++j) {
			++increases[j];
		}
		for (int j = zero + one; j < 2 * M - 1; ++j) {
			increases[j] += 2;
		}
	}

	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			if (j == 0) {
				cout << increases[M - 1 - i] << " ";
			}
			else {
				cout << increases[M - 1 + j] << " ";
			}
		}
		cout << endl;
	}
}