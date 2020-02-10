#include <iostream>

using namespace std;

int main() {
	int maxVal = 0;
	int maxIndex = -1;
	for (int i = 0; i < 9; ++i) {
		int P;
		cin >> P;

		if (maxVal < P) {
			maxVal = P;
			maxIndex = i + 1;
		}
	}

	cout << maxVal << endl << maxIndex << endl;
}