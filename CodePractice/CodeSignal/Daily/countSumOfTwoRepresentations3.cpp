#include <iostream>
#include <algorithm>

using namespace std;

//https://app.codesignal.com/challenge/mXCWzh37ibxEY822h

int countSumOfTwoRepresentations3(int n, int l, int r) {
	return l <= n/2 && n/2 <= r ? min(abs(n/2 - l), abs(n/2 - r)) + 1 : 0;
}

int main() {
	cout << countSumOfTwoRepresentations3(6, 2, 4) << endl;		// 2
	cout << countSumOfTwoRepresentations3(10, 3, 5) << endl;	// 1
}