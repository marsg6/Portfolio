#include <iostream>

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	int mul = a * b;
	while (b) {
		cout << a * (b % 10) << endl;
		b /= 10;
	}
	cout << mul << endl;
}