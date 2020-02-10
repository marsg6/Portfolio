#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;

	vector<int> scores(N, 0);
	for (int i = 0; i < N; ++i) {
		string s;
		cin >> s;
		int count = 0;
		for (const auto& c : s) {
			if (c == 'O') {
				++count;
				scores[i] += count;
			}
			else {
				count = 0;
			}
		}
	}

	for (const auto& s : scores) {
		cout << s << endl;
	}
}