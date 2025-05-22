#ifndef SEARCHMANAGER
#define SEARCHMANAGER

#include "SimilarChecker.cpp"

using namespace std;

struct SearchNode {
	string keyword;
	string day;
};

struct PointNode {
	string name;
	int point;

	bool operator<(const PointNode& other) const {
		return point > other.point; // 내림차수 정렬
	}
};
const int weekNum = 7;
const int categoryNum = 2;
const int basicScore = 10;
const int vectorMaxSize = 10;
const int limitScore = 80;
const int maxScore = 2100000000;

class SearchManager {
private:
	const string days[weekNum] = { "monday","tuesday","wednesday","thursday","friday","saturday","sunday" };
	enum dayEnum { monday, tuesday, wednesday, thursday, friday, saturday, sunday };

	vector<PointNode> weekBest[weekNum]; //월 ~ 일
	vector<PointNode> categoryBest[categoryNum]; //평일, 주말
	int UZ = basicScore;
	friend class SearchManagerTest_TestSetSecret_Test;

	string seachKeyword(SearchNode searchNode) {
		int point = UZ;
		UZ++;

		//요일
		int indexOfWeek = 0;
		for (int i = 0; i < weekNum; i++) {
			if (searchNode.day == days[i]) {
				indexOfWeek = i;
				break;
			}
		}
		//평일 / 주말
		int indexOfCateogry = 0;
		if (indexOfWeek >= monday && indexOfWeek <= friday) indexOfCateogry = 0;
		else indexOfCateogry = 1;

		//관리 목록에 존재하는지 확인
		//관리되는 키워드이면 점수가 증가

		bool hitFlag = false;
		for (PointNode& node : weekBest[indexOfWeek]) {
			if (node.name == searchNode.keyword) {
				node.point += (int)(node.point * 0.1);
				hitFlag = true;
				break;
			}
		}

		for (PointNode& node : categoryBest[indexOfCateogry]) {
			if (node.name == searchNode.keyword) {
				node.point += (int)(node.point * 0.1);
				hitFlag = true;
				break;
			}
		}

		if (hitFlag == true) {
			return searchNode.keyword;
		}
		CheckAlgorithms checkAlgorithms;
		checkAlgorithms.setAlgorithm(std::make_shared<LevenshteinAlgorithms>());
		SimilarChecker similarChecker = SimilarChecker(limitScore, checkAlgorithms);

		//찰떡 HIT
		for (PointNode& node : weekBest[indexOfWeek]) {
			if (similarChecker.similar(node.name, searchNode.keyword)) {
				return node.name;
			}
		}

		for (PointNode& node : categoryBest[indexOfCateogry]) {
			if (similarChecker.similar(node.name, searchNode.keyword)) {
				return node.name;
			}
		}

		//완벽 HIT / 찰떡 HIT 둘다 아닌경우
		if (weekBest[indexOfWeek].size() < vectorMaxSize) {
			weekBest[indexOfWeek].push_back({ searchNode.keyword, point });
			std::sort(weekBest[indexOfWeek].begin(), weekBest[indexOfWeek].end());
		}
		else if (weekBest[indexOfWeek].back().point < point) {
			weekBest[indexOfWeek].pop_back();
			weekBest[indexOfWeek].push_back({ searchNode.keyword, point });
			std::sort(weekBest[indexOfWeek].begin(), weekBest[indexOfWeek].end());
		}

		if (categoryBest[indexOfCateogry].size() < vectorMaxSize) {
			categoryBest[indexOfCateogry].push_back({ searchNode.keyword, point });
			std::sort(categoryBest[indexOfCateogry].begin(), categoryBest[indexOfCateogry].end());
		}
		else if (categoryBest[indexOfCateogry].front().point < point) {
			categoryBest[indexOfCateogry].pop_back();
			categoryBest[indexOfCateogry].push_back({ searchNode.keyword, point });
			std::sort(categoryBest[indexOfCateogry].begin(), categoryBest[indexOfCateogry].end());
		}

		return searchNode.keyword;
	}
private:
	void nodeSort() {
		if (UZ >= maxScore) {
			UZ = basicScore;
			for (int i = 0; i < weekNum; i++) {
				int num = 1;
				for (int j = weekBest[i].size() - 1; j >= 0; j--) { // 낮은 점수(vector의 back)부터 1을 줘야함
					weekBest[i][j].point = num;
					num++;
				}
			}
			for (int i = 0; i < categoryNum; i++) {
				int num = 1;
				for (PointNode& node : categoryBest[i]) {
					for (int j = categoryBest[i].size() - 1; j >= 0; j--) {
						categoryBest[i][j].point = num;
						num++;
					}
				}
			}
		}
	}
public:
	string search(SearchNode searchNode) {
		string result = seachKeyword(searchNode);
		nodeSort();
		return result;
	}
};

#endif