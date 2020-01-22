#include <iostream>

using namespace std;

//https://app.codesignal.com/interview-practice/task/gX7NXPBrYThXZuanm

 template<typename T>
 struct ListNode {
   ListNode(const T &v) : value(v), next(nullptr) {}
   T value;
   ListNode *next;
 };

ListNode<int>* removeKFromList(ListNode<int>* l, int k) {
    while (l && l->value == k) {
        l = l->next;
    }
    auto res = l;
    while (l) {
        if (l->next && l->next->value == k) {
            l->next = l->next->next;
        }
        else {
            l = l->next;
        }
    }
    return res;
}

int main() {

}