#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Node {
	int Parent;
	vector<int> Childs;
};

int Level(const vector<Node>& Tree, int NodeNum) {
	int Count = 1;
	for (int i = NodeNum; i != 1; i = Tree[i].Parent) {
		++Count;
	}
	return Count;
}

int FindCommomParent(const vector<Node>& Tree, int NodeA, int NodeB) {
	int LevelA = Level(Tree, NodeA);
	int LevelB = Level(Tree, NodeB);

	while (NodeA != NodeB) {
		if (LevelA < LevelB) {
			NodeB = Tree[NodeB].Parent;
			--LevelB;
		}
		else {
			NodeA = Tree[NodeA].Parent;
			--LevelA;
		}
	}

	return NodeA;
}

int NumOfSubNodes(const vector<Node>& Tree, int NodeNum) {
	int Count = 0;

	stack<Node> S;
	S.push(Tree[NodeNum]);

	while (!S.empty()) {
		Node CurrNode = S.top();
		S.pop();
		++Count;
		for (int i = 0; i < CurrNode.Childs.size(); ++i) {
			S.push(Tree[CurrNode.Childs[i]]);
		}
	}

	return Count;
}

int main() {
	int Cases;
	cin >> Cases;

	for (int i = 1; i <= Cases; ++i) {
		cout << "#" << i << " ";
		/* 로직 시작 */

		int V, E, NodeA, NodeB;
		cin >> V >> E >> NodeA >> NodeB;

		vector<Node> Tree(V + 1);
		for (int j = 0; j < E; ++j) {
			int Parent, Child;
			cin >> Parent >> Child;
			Tree[Parent].Childs.push_back(Child);
			Tree[Child].Parent = Parent;
		}

		int CommonParent = FindCommomParent(Tree, NodeA, NodeB);
		cout << CommonParent << " ";
		cout << NumOfSubNodes(Tree, CommonParent);

		/* 로직 끝 */
		cout << endl;
	}

	return 0;
}