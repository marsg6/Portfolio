#include <iostream>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;

	int c = 0;
	for (int i = 0; i < N; ++i) {
		string s;
		cin >> s;

		bool p[26] = { false };
		char prev = '0';
		for (int j = 0; j < s.size(); ++j) {
			if (!p[s[j] - 'a']) {
				p[s[j] - 'a'] = true;
			}
			else {
				if (prev != s[j]) {
					break;
				}
			}
			if (j == s.size() - 1) {
				++c;
			}

			prev = s[j];
		}
	}
	cout << c;
}