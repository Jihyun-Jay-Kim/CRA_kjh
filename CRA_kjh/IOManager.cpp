#ifndef IOMANAGER
#define IOMANAGER

#include "SearchManager.cpp"
#include <fstream>

class IOManager {
public:
	void execute(string fileName) {
		SearchNode searchNode;
		SearchManager searchManager;

		ifstream fin{ fileName }; //데이터 입력
		if (!fin.is_open()) {
			throw std::runtime_error("cannot open");
		}
		while (!fin.eof()) {
			fin >> searchNode.keyword >> searchNode.day;
			string resultString = searchManager.search(searchNode);
			std::cout << resultString << "\n";
		}
	}
};
#endif