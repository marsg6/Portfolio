#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int MaxConsecutiveSum(vector<int>& Temperatures, int K) {
	int CurrSum;
	int CurrMax = CurrSum = accumulate(Temperatures.begin(), Temperatures.begin() + K, 0);

	for (int j = K; j < Temperatures.size(); ++j) {
		/* 추가되는 맨 뒤의 것 */
		int ValToAdd = Temperatures[j];
		/* 제거되는 맨 앞의 것 */
		int ValToSub = Temperatures[j - K];

		CurrSum += ValToAdd - ValToSub;
		/* 갱신 */
		CurrMax = CurrMax < CurrSum ? CurrSum : CurrMax;
	}

	return CurrMax;
}

int main() {
	int N, K;
	cin >> N >> K;

	vector<int> Temperatures(N);

	for (int i = 0; i < N; ++i) {
		int Temperature;
		cin >> Temperature;
		Temperatures[i] = Temperature;
	}

	cout << MaxConsecutiveSum(Temperatures, K);
}