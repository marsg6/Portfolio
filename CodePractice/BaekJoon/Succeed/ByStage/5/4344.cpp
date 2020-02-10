#include <iostream>
#include <vector>

using namespace std;

int main() {
	int C;
	cin >> C;

	for (int i = 0; i < C; ++i) {
		int N;
		cin >> N;
		vector<int> Scores(N, 0);
		int Total = 0;
		for (int i = 0; i < N; ++i) {
			cin >> Scores[i];
			Total += Scores[i];
		}
		int Mean = Total / N;
		int Count = 0;
		for (const auto& S : Scores) {
			if (Mean < S) {
				++Count;
			}
		}
		cout.precision(3);
		cout << fixed << static_cast<float>(Count) / N * 100 << "%" << endl;
	}
}