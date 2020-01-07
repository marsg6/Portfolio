#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//int Cal(vector<vector<char>>& Graph) {
//	int Count = 0;
//	int N = Graph.size();
//
//	for (int i = 0; i < N; ++i) {
//		for (int j = 0; j < N; ++j) {
//			if (Graph[i][j] == 1) {
//				for (int k = 0; k < N; ++k) {
//					if (Graph[j][k] == 1 && Graph[k][i] == 1) {
//						++Count;
//					}
//				}
//				Graph[i][j] = Graph[j][i] = 0;
//			}
//		}
//	}
//
//	return Count;
//}
//
//int main() {
//	int N, M;
//	cin >> N >> M;
//
//	vector<vector<char>> Graph(N, vector<char>(N, 0));
//
//	for (int i = 0; i < M; ++i) {
//		int Left, Right;
//		cin >> Left >> Right;
//		Graph[Left - 1][Right - 1] = 1;
//		Graph[Right - 1][Left - 1] = 1;
//	}
//
//	cout << Cal(Graph);
//}

int main() {
	int N, M;
	cin >> N >> M;

	map<int, vector<int>> Graph;
	vector<int> NodeList;
	for (int i = 0; i < M; ++i) {
		int Left, Right;
		cin >> Left >> Right;

		NodeList.push_back(Left);
		NodeList.push_back(Right);

		auto LeftIt = Graph.find(Left);
		if (LeftIt == Graph.end()) {
			Graph[Left] = { Right };
		}
		else {
			Graph[Left].push_back(Right);
		}

		auto RightIt = Graph.find(Right);
		if (RightIt == Graph.end()) {
			Graph[Right] = { Left };
		}
		else {
			Graph[Right].push_back(Left);
		}
	}
	unique(NodeList.begin(), NodeList.end());

	int Count = 0;

	for (auto& FirstNode : NodeList) {
		auto& FirstList = Graph[FirstNode];
		int FirstListSize = FirstList.size();
		for (int i = 0; i < FirstListSize; ++i) {
			int SecondNode = FirstList[i];
			auto SecondList = Graph[SecondNode];
			int SecondListSize = SecondList.size();
			
			for (auto& ThirdNode : SecondList) {
				auto& ThirdList = Graph[ThirdNode];
				for (auto& FourthNode : ThirdList) {
					if (FirstNode == FourthNode) {
						++Count;
					}
				}
			}
		}
	}


	//for (auto StartNodeList : Graph) {

	//	for (auto SecondNode : StartNodeList.second) {
	//		auto SecondNodeList = *(Graph.find(SecondNode));
	//		for (auto ThirdNode : SecondNodeList.second) {
	//			auto ThirdNodeList = *(Graph.find(ThirdNode));
	//			for (auto FourthNode : ThirdNodeList.second) {
	//				if (FourthNode == StartNodeList.first) {
	//					++Count;
	//				}
	//			}
	//		}
	//	}
	//}

	cout << Count / 6;
}