#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int rec(const string& name, string& curr, int i, int count) {
    int res = count;
    bool check = false;
    for (int j = 1; j <= name.size() / 2; ++j) {
        int rIndex = (i + j) % name.size();
        int lIndex = i - j < 0 ? i - j + name.size() : i - j;
        int rRes = 100000;
        int lRes = 100000;
        if (name[rIndex] != curr[rIndex]) {
            int rCount = count + j + 13 - abs('N' - name[rIndex]);
            curr[rIndex] = name[rIndex];
            rRes = rec(name, curr, rIndex, rCount);
            check = true;
        }
        if (name[lIndex] != curr[lIndex]) {
            int lCount = count + j + 13 - abs('N' - name[lIndex]);
            curr[lIndex] = name[lIndex];
            lRes = rec(name, curr, lIndex, lCount);
            check = true;
        }
        if (check) {
            res = min(rRes, lRes);
            break;
        }
    }
    return res;
}

int solution(string name) {
    int answer = 13 - abs('N' - name[0]);
    string curr(name.size(), 'A');
    curr[0] = name[0];
    answer = rec(name, curr, 0, answer);

    return answer;
}