#include <iostream>
#include <vector>

using namespace std;

//https://app.codesignal.com/challenge/o9QW9r6JcBKqceGBq

template<typename T>
struct ListNode {
  ListNode(const T &v) : value(v), next(nullptr) {}
  T value;
  ListNode *next;
};

int nthElementFromTheEnd(ListNode<int>* l, int n) {
    int s = 0;
    auto m = l;
    while (m) {
        ++s;
        m = m->next;
    }
    
    for (int i = 0; l && i < s - n; ++i) {
        l = l->next;
    }
    return n <= s ? l->value : -1;
}

int main() {

}