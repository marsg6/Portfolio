#include <iostream>

using namespace std;

void func(int n) {
	for (int i = 1; i <= 9; ++i) {
		cout << n << " * " << i << " = " << n * i << endl;
	}
}

int main() {
	int n;
	cin >> n;
	func(n);
}