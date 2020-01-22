#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct Node {
    string name;
    shared_ptr<Node> prev;
    shared_ptr<Node> next;
};

size_t hash_str(const string& str) {
    size_t res = 0;
    for (const auto& c : str) {
        res += c;
    }
    return res % 1000;
}

string solution(vector<string> participant, vector<string> completion) {
    vector<shared_ptr<Node>> hash_map(1000, nullptr);
    for (const auto& c : completion) {
        size_t index = hash_str(c);
        auto node = hash_map[index];
        if (node) {
            while (node->next) {
                node = node->next;
            }
            auto newNode{ make_shared<Node>(Node{ c, node, nullptr }) };
            node->next = newNode;
        }
        else {
            hash_map[index] = make_shared<Node>(Node{ c, nullptr, nullptr });
        }
    }

    for (const auto& p : participant) {
        size_t index = hash_str(p);
        auto node = hash_map[index];
        bool exist = false;
        while (node) {
            if (node->name != p) {
                node = node->next;
            }
            else {
                if (node->prev) {
                    node->prev->next = node->next;
                }
                else {
                    hash_map[index] = node->next;
                }
                if (node->next) {
                    node->next->prev = node->prev;
                }
                exist = true;
                break;
            }
        }
        if (!exist) {
            return p;
        }
    }
}

int main() {
    cout << solution({ "mislav", "stanko", "mislav", "ana" }, { "stanko", "mislav", "ana" }) << endl;
}