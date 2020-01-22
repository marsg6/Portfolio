#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

using namespace std;

bool isPrime(int n) {
    if (n < 2) { return false; }
    for (int i = 2; i * i < n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int solution(string numbers) {
    if (numbers.empty()) { return 0; }
    int answer = 0;

    sort(numbers.begin(), numbers.end());

    do {
        int number = stoi(numbers);
        int digit = numbers.size();
        if (isPrime(number)) {
            cout << "-----------" << endl;
            cout << number << endl;
            cout << "-----------" << endl;
            ++answer;
        }
    } while (next_permutation(numbers.begin(), numbers.end()));

    for (int i = 0; i < numbers.size(); ++i) {
        cout << "재귀 시작" << endl;
        cout << numbers.substr(0, i) + numbers.substr(i + 1, numbers.size() - i - 1) << endl;
        answer += solution(numbers.substr(0, i) + numbers.substr(i + 1, numbers.size() - i - 1));
        cout << "재귀 끝" << endl;
    }

    return answer;
}


int main() {
    cout << solution("011");
}