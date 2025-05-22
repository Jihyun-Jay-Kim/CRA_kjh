#ifndef SIMILARCHECKER
#define SIMILARCHECKER

#include <string>
#include "CheckAlgorithms.cpp"

class SimilarChecker {
private:
	int limitScore;
	CheckAlgorithms checkAlgorithms;
public:
	SimilarChecker(int ls, CheckAlgorithms ca) {
		limitScore = ls;
		checkAlgorithms = ca;
	}
	// 점수 환산
	bool similar(const std::string& a, const std::string& b) {
		if (a.empty() || b.empty()) return false;

		int dist = checkAlgorithms.execute(a, b);
		int max_len = std::max(a.length(), b.length());
		// 유사도 비율 (1.0: 완전히 같음, 0.0: 전혀 다름)
		double similarity = 1.0 - (double)dist / max_len;

		int score = 1 + static_cast<int>(similarity * 99);

		if (score >= limitScore) return true;
		return false;
	}
};
#endif