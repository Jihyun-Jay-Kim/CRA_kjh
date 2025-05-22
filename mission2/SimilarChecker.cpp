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
	// ���� ȯ��
	bool similar(const std::string& a, const std::string& b) {
		if (a.empty() || b.empty()) return false;

		int dist = checkAlgorithms.execute(a, b);
		int max_len = std::max(a.length(), b.length());
		// ���絵 ���� (1.0: ������ ����, 0.0: ���� �ٸ�)
		double similarity = 1.0 - (double)dist / max_len;

		int score = 1 + static_cast<int>(similarity * 99);

		if (score >= limitScore) return true;
		return false;
	}
};
#endif