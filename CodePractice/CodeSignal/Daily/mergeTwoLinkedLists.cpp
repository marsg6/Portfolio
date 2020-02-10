#include <iostream>

using namespace std;

//https://app.codesignal.com/challenge/tLjmbhkSeYbvxa6Wi

 template<typename T>
 struct ListNode {
   ListNode(const T &v) : value(v), next(nullptr) {}
   T value;
   ListNode *next;
 };

ListNode<int>* mergeTwoLinkedLists(ListNode<int>* l1, ListNode<int>* l2) {
    ListNode<int>* res = new ListNode<int>(0);
    auto t = res;
    while (l1 && l2) {
        auto temp1 = l1->next;
        auto temp2 = l2->next;

        if (l1->value < l2->value) {
            t->next = l1;
            l1 = temp1;
        }
        else {
            t->next = l2;
            l2 = temp2;
        }
        t = t->next;
    }
    while (l1) {
        auto temp1 = l1->next;
        t->next = l1;
        l1 = temp1;
        t = t->next;
    }
    while (l2) {
        auto temp2 = l2->next;
        t->next = l2;
        l2 = temp2;
        t = t->next;
    }
    return res->next;
}

ListNode<int>* mergeTwoLinkedLists(ListNode<int>* l1, ListNode<int>* l2) {
    auto r = new ListNode<int>(0), t = r;

    for (; l1 && l2; t = t->next) {
        if (l1->value < l2->value) {
            t->next = l1;
            l1 = l1->next;
        }
        else {
            t->next = l2;
            l2 = l2->next;
        }
    }

    auto l = l1 ? l1 : l2;
    for (; l; t = t->next, l = l->next) {
        t->next = l;
    }

    return r->next;
}

int main() {

}