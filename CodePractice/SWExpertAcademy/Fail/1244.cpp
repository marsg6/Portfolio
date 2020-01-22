#include <iostream>

#define CHAR_MIN -128
#define INT_MIN -2147483647

using namespace std;

void MakeMax(string& Numbers, int ChangeCount, int CurrIndex) {
	if (ChangeCount == 0) { return; }
	cout << ChangeCount << " : " << Numbers << endl;
	char Max = CHAR_MIN;
	int MaxIndex = INT_MIN;
	for (int i = CurrIndex; i < Numbers.size(); ++i) {
		if (Max <= Numbers[i]) {
			Max = Numbers[i];
			MaxIndex = i;
		}
	}

	char Min = Numbers[CurrIndex];
	int MinIndex = CurrIndex;
	for (int i = CurrIndex; i < Numbers.size() && i < CurrIndex + ChangeCount; ++i) {
		if (Numbers[i] < Min && i < MaxIndex) {
			Min = Numbers[i];
			MinIndex = i;
		}
	}

	if (Numbers[MaxIndex] != Numbers[CurrIndex]) {
		char Temp = move(Numbers[MinIndex]);
		Numbers[MinIndex] = move(Numbers[MaxIndex]);
		Numbers[MaxIndex] = move(Temp);

		if (MinIndex == CurrIndex) {
			MakeMax(Numbers, ChangeCount - 1, CurrIndex + 1);
		}
		else {
			MakeMax(Numbers, ChangeCount - 1, CurrIndex);
		}
	}
	else {
		if (CurrIndex != Numbers.size() - 1) {
			MakeMax(Numbers, ChangeCount, CurrIndex + 1);
		}
		else {
			char Temp = move(Numbers[CurrIndex - 1]);
			Numbers[CurrIndex - 1] = move(Numbers[CurrIndex]);
			Numbers[CurrIndex] = move(Temp);

			MakeMax(Numbers, ChangeCount - 1, CurrIndex - 1);
		}
	}
}

int main() {
	int Cases;
	cin >> Cases;

	for (int i = 1; i <= Cases; ++i) {
		cout << "#" << i << " ";
		/* 로직 시작 */

		string Numbers;
		int ChangeCount;
		cin >> Numbers >> ChangeCount;

		MakeMax(Numbers, ChangeCount, 0);
		cout << Numbers;

		/* 로직 끝 */
		cout << endl;
	}

	return 0;
}