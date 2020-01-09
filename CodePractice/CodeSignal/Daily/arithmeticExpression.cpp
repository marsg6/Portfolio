#include <iostream>

using namespace std;

// https://app.codesignal.com/challenge/PG2nQ9fDwfhhyBEQn

bool arithmeticExpression(int a, int b, int c) {
    return a + b == c || a == b + c || a * b == c || (a / b == c && a % b == 0);
}

int main() {
    cout << arithmeticExpression(2, 3, 5) << endl;
    cout << arithmeticExpression(8, 2, 4) << endl;
}