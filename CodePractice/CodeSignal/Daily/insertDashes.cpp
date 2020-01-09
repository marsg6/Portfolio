#include <iostream>

using namespace std;

// https://app.codesignal.com/challenge/PLyDoCvsWjCNpSFux

string insertDashes(string inputString) {
    string Res;

    auto Start = inputString.begin();
    auto End = inputString.end();

    for (auto It = Start; It != End; ++It) {
        Res += *It;
        if (*It != ' ' && It != End - 1 && *(It + 1) != ' ') {
            Res += '-';
        }
    }

    return Res;
}

int main() {
    cout << insertDashes("aba caba") << endl;
    cout << insertDashes("x") << endl;
}