#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://app.codesignal.com/challenge/ktwqoNPfGDNeDW5rm

int numberMinimization(int n, int d) {
    int min = INT_MAX;

    /* 다 바꾼 다음 */
    vector<int> digits;
    int digitNum = log10(n) + 1;

    for (int i = digitNum; 0 < i; --i) {
        digits.push_back(static_cast<int>(n / pow(10, i - 1)) % 10);
    }
    sort(digits.begin(), digits.end());

    vector<int> changedNums;
    do {
        int changedNum = 0;
        for (int i = 0; i < digitNum; ++i) {
            changedNum += digits[i] * pow(10, digitNum - i - 1);
        }
        changedNums.push_back(changedNum);
    } while (next_permutation(digits.begin(), digits.end()));
    cout << "---------------" << endl;
    for (auto changedNum : changedNums) {
        cout << changedNum << endl;
    }
    cout << "---------------" << endl;
    for (auto changedNum : changedNums) {
        /* 나눠지면 나눠서 재귀호출 */
        if (changedNum != 0 && changedNum % d == 0) {
            int res = numberMinimization(changedNum / d, d);
            min = res < min ? res : min;
        }
        /* 안 나눠지면 최소값인지 검사 */
        else {
            min = changedNum < min ? changedNum : min;
        }
        if (min < d) { return min; }
    }

    return min;
}

int main() {
    cout << "결과는 : " << numberMinimization(501, 3) << endl;
    cout << "결과는 : " << numberMinimization(4006, 2) << endl;
}