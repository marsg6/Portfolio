#include <iostream>

using namespace std;

// https://app.codesignal.com/challenge/eoi6ETDgQPJaEuwWk

int returnTwelve(int number) {
    return number > 12 ? number : 12;
}

int main() {
    cout << returnTwelve(13) << endl;
    cout << returnTwelve(10) << endl;
}