#include <iostream>

using namespace std;

int main() {
	int A, B, C;
	cin >> A >> B >> C;

	int Sum = A * B * C;

	int Digits[10] = { 0, };

	while (Sum) {
		++Digits[Sum % 10];
		Sum /= 10;
	}

	for (int i = 0; i < 10; ++i) {
		cout << Digits[i] << endl;
	}
}