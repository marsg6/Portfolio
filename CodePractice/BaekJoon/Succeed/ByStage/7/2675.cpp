#include <iostream>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; ++i) {
		int k;
		string s;
		cin >> k >> s;

		for (auto c : s) {
			for (int j = 0; j < k; ++j) {
				cout << c;
			}
		}
		cout << endl;
	}
}