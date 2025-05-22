#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

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

const string days[weekNum] = { "monday","tuesday","wednesday","thursday","friday","saturday","sunday" };
enum dayEnum { monday , tuesday, wednesday, thursday, friday, saturday, sunday};

vector<PointNode> weekBest[weekNum]; //월 ~ 일
vector<PointNode> categoryBest[categoryNum]; //평일, 주말

int UZ = basicScore;
int indexOfWeek;
int indexOfCategory;

// 레벤슈타인 거리 계산 알고리즘 (문자열 유사도 검사)
int levenshtein(const std::string& a, const std::string& b) {
	const size_t len_a = a.size();
	const size_t len_b = b.size();

	std::vector<std::vector<int>> d(len_a + 1, std::vector<int>(len_b + 1));

	for (size_t i = 0; i <= len_a; ++i) d[i][0] = i;
	for (size_t j = 0; j <= len_b; ++j) d[0][j] = j;

	for (size_t i = 1; i <= len_a; ++i) {
		for (size_t j = 1; j <= len_b; ++j) {
			if (a[i - 1] == b[j - 1])
				d[i][j] = d[i - 1][j - 1];
			else
				d[i][j] = 1 + std::min({ d[i - 1][j], d[i][j - 1], d[i - 1][j - 1] });
		}
	}
	return d[len_a][len_b];
}

int checkAlgorithm(const std::string& a, const std::string& b) {
	return levenshtein(a, b);
}

// 점수 환산
bool similer(const std::string& a, const std::string& b) {
	if (a.empty() || b.empty()) return false;

	int dist = checkAlgorithm(a, b);
	int max_len = std::max(a.length(), b.length());
	// 유사도 비율 (1.0: 완전히 같음, 0.0: 전혀 다름)
	double similarity = 1.0 - (double)dist / max_len;

	int score = 1 + static_cast<int>(similarity * 99);

	if (score >= limitScore) return true;
	return false;
}

bool checkCompHit(int indexOfWeek, int indexOfCateogry, string keyword) {
	bool hitFlag = false;
	for (PointNode& node : weekBest[indexOfWeek]) {
		if (node.name == keyword) {
			node.point += (int)(node.point * 0.1);
			hitFlag = true;
			break;
		}
	}

	for (PointNode& node : categoryBest[indexOfCateogry]) {
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
	if (checkCompHit(indexOfWeek, indexOfCategory, searchNode.keyword) == true) {
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

void nodeSort() {
	std::sort(weekBest[indexOfWeek].rbegin(), weekBest[indexOfWeek].rend());
	std::sort(categoryBest[indexOfCategory].rbegin(), categoryBest[indexOfCategory].rend());

	while (weekBest[indexOfWeek].size() > 10)
	{
		weekBest[indexOfWeek].pop_back();
	}

	while (categoryBest[indexOfCategory].size() > 10)
	{
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

string search(SearchNode searchNode) {
	string result = seachKeyword(searchNode);
	nodeSort();

	return result;
}

void input() {
	SearchNode searchNode;
	try {
		ifstream fin{ "keyword_weekday_500.txt" }; //500개 데이터 입력
		while (!fin.eof()) {
			fin >> searchNode.keyword >> searchNode.day;
			string resultString = search(searchNode);
			std::cout << resultString << "\n";
		}
	}
	catch (const std::exception& e) {
		std::cerr << "예외 발생: " << e.what() << std::endl;
	}
}

int main() {
	input();
}
