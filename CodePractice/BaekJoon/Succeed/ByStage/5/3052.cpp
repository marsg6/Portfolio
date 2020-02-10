#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
	unordered_set<int> remains;
	for (int i = 0; i < 10; ++i) {
		int P;
		cin >> P;

		remains.emplace(P % 42);
	}
	cout << remains.size();
}