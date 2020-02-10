#include <iostream>

using namespace std;

int main() {
	int Sum = 0;

	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		char t;
		cin >> t;
		Sum += t - '0';
	}
	cout << Sum;
}