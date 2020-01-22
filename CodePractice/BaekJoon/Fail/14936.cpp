#include <iostream>

using namespace std;

int main() {
	int Floors, Time;
	cin >> Floors >> Time;

	/* 모든 버튼이 안 눌린 상태 */
	int Count = 1;
	if (2 < Floors) {
		if ((Floors + 2) / 3 <= Time) {
			++Count;
		}
		if ((Floors + 1) / 2 <= Time) {
			++Count;
		}
		if (Floors / 2 <= Time) {
			++Count;
		}
		if ((Floors + 2) / 3 + (Floors + 1) / 2 <= Time) {
			++Count;
		}
		if ((Floors + 2) / 3 + Floors / 2 <= Time) {
			++Count;
		}
		if ((Floors + 1) / 2 + Floors / 2 <= Time) {
			++Count;
		}
		if ((Floors + 2) / 3 + (Floors + 1) / 2 + Floors / 2 <= Time) {
			++Count;
		}
	}
	else {
		if (Time == 1) {

		}
	}
	cout << Count;
}