#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;

	int max = 0;
	vector<float> scores(N, 0);
	for (auto& s : scores) {
		cin >> s;
		if (max < s) {
			max = s;
		}
	}

	float sum = 0;
	for (auto& s : scores) {
		s = s / max * 100;
		sum += s;
	}

	cout.fixed;
	cout.precision(2);
	cout << fixed << sum / N << endl;
}