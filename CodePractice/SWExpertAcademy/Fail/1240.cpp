#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Code {
    int a, b, c, d;
    int size = 0;

    void Push(int n) {
        switch (size) {
        case 0: a = n; break;
        case 1: b = n; break;
        case 2: c = n; break;
        case 3: d = n; break;
        }
        ++size;
    }

    bool operator==(const Code& Other) {
        return a == Other.a && b == Other.b && c == Other.c && d == Other.d;
    }
};

int main() {
    vector<Code> Codes {
        {3, 2, 1, 1},
        {2, 2, 2, 1},
        {2, 1, 2, 2},
        {1, 4, 1, 1},
        {1, 1, 3, 2},
        {1, 2, 3, 1},
        {1, 1, 1, 4},
        {1, 3, 1, 2},
        {1, 2, 1, 3},
        {3, 1, 1, 2}
    };

    int K;
    cin >> K;

    for (int k = 0; k < K; ++k) {
        int N, M;
        cin >> N >> M;
        
        vector<vector<char>> Info(N, vector<char>(M, '0'));

        pair<int, int> LastIndex;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                char BiDigit;
                cin >> BiDigit;
                if (BiDigit == '1') {
                    Info[i][j] = '1';
                    LastIndex = { i, j };
                }
            }
        }

        stack<char> ParsingStack;
        for (int i = LastIndex.first; 0 <= i; --i) {
            for (int j = LastIndex.second; 0 <= j; --j) {
                ParsingStack.push(Info[i][j]);
                if (ParsingStack.size() == 56) {
                    break;
                }
            }
            if (ParsingStack.size() == 56) {
                break;
            }
        }

        vector<int> Number;
        for (int i = 0; i < 8; ++i) {
            Code Temp;
            char Prev = '0';
            int Count = 0;
            for (int j = 0; j < 7; ++j) {
                char Curr = ParsingStack.top();
                if (Curr == Prev) {
                    ++Count;
                    if (j == 6) {
                        Temp.Push(Count);
                    }
                }
                else {
                    Temp.Push(Count);
                    Count = 1;
                }
                Prev = Curr;
                ParsingStack.pop();
            }

            for (int j = 0; j < Codes.size(); ++j) {
                if (Temp == Codes[j]) {
                    Number.push_back(j);
                    break;
                }
            }
        }

        int Sum = 0;
        int ResSum = 0;
        for (int i = 0; i < Number.size() - 1; ++i) {
            ResSum += Number[i];
            if (i % 2) {
                Sum += 3 * Number[i];
            }
            else {
                Sum += Number[i];
            }
        }
        Sum += Number[Number.size() - 1];
        ResSum += Number[Number.size() - 1];

        if (!(Sum % 10)) {
            ResSum = 0;
        }

        cout << "#" << k << " " << ResSum << endl;
    }
}