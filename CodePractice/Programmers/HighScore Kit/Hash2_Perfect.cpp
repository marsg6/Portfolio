#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool solution(vector<string> phone_book) {
    sort(phone_book.begin(), phone_book.end());

    for (int i = 0; i < phone_book.size(); ++i) {
        string currStr = phone_book[i];
        for (int j = i + 1; j < phone_book.size(); ++j) {
            string subStr = phone_book[j].substr(0, currStr.size());
            if (currStr == subStr) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    solution({ "123", "456", "789" });
}