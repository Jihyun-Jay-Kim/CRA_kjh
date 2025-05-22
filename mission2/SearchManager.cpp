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
		return point > other.point; // �������� ����
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

	vector<PointNode> weekBest[weekNum]; //�� ~ ��
	vector<PointNode> categoryBest[categoryNum]; //����, �ָ�
	int UZ = basicScore;
	friend class SearchManagerTest_TestSetSecret_Test;

	string seachKeyword(SearchNode searchNode) {
		int point = UZ;
		UZ++;

		//����
		int indexOfWeek = 0;
		for (int i = 0; i < weekNum; i++) {
			if (searchNode.day == days[i]) {
				indexOfWeek = i;
				break;
			}
		}
		//���� / �ָ�
		int indexOfCateogry = 0;
		if (indexOfWeek >= monday && indexOfWeek <= friday) indexOfCateogry = 0;
		else indexOfCateogry = 1;

		//���� ��Ͽ� �����ϴ��� Ȯ��
		//�����Ǵ� Ű�����̸� ������ ����

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

		//���� HIT
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

		//�Ϻ� HIT / ���� HIT �Ѵ� �ƴѰ��
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
				for (int j = weekBest[i].size() - 1; j >= 0; j--) { // ���� ����(vector�� back)���� 1�� �����
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