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
	int indexOfWeek;
	int indexOfCategory;

	bool checkCompHit(string keyword) {
		bool hitFlag = false;
		for (PointNode& node : weekBest[indexOfWeek]) {
			if (node.name == keyword) {
				node.point += (int)(node.point * 0.1);
				hitFlag = true;
				break;
			}
		}

		for (PointNode& node : categoryBest[indexOfCategory]) {
			if (node.name == keyword) {
				node.point += (int)(node.point * 0.1);
				hitFlag = true;
				break;
			}
		}
		return hitFlag;
	}

	string seachKeyword(SearchNode searchNode) {
		int point = UZ;
		UZ++;

		//요일
		indexOfWeek = 0;
		for (int i = 0; i < weekNum; i++) {
			if (searchNode.day == days[i]) {
				indexOfWeek = i;
				break;
			}
		}
		//평일 / 주말
		indexOfCategory = 0;
		if (indexOfWeek >= monday && indexOfWeek <= friday) indexOfCategory = 0;
		else indexOfCategory = 1;

		//관리 목록에 존재하는지 확인
		//관리되는 키워드이면 점수가 증가
		if (checkCompHit(searchNode.keyword) == true) {
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

		for (PointNode& node : categoryBest[indexOfCategory]) {
			if (similarChecker.similar(node.name, searchNode.keyword)) {
				return node.name;
			}
		}

		//완벽 HIT / 찰떡 HIT 둘다 아닌경우
		weekBest[indexOfWeek].push_back({ searchNode.keyword, point });
		categoryBest[indexOfCategory].push_back({ searchNode.keyword, point });

		return searchNode.keyword;
	}


private:
	void nodeSort() {
		std::sort(weekBest[indexOfWeek].rbegin(), weekBest[indexOfWeek].rend());
		std::sort(categoryBest[indexOfCategory].rbegin(), categoryBest[indexOfCategory].rend());

		while (weekBest[indexOfWeek].size() > 10) {
			weekBest[indexOfWeek].pop_back();
		}

		while (categoryBest[indexOfCategory].size() > 10) {
			categoryBest[indexOfCategory].pop_back();
		}

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