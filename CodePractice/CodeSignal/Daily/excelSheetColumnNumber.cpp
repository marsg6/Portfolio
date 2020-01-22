#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/challenge/ESBdiMSa8YTr95qFx

int excelSheetColumnNumber(string s) {
    int res = 0;
    for (int i = 0, j = s.size() - 1; 0 <= j; ++i, --j) {
        res += (s[j] - 'A' + 1) * pow(26, i);
    }
    return res;
}

int main() {
    cout << excelSheetColumnNumber("AB") << endl; // 28
    cout << excelSheetColumnNumber("A") << endl; // 1
}