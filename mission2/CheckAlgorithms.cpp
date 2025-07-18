#ifndef CHECKALGORITHMS
#define CHECKALGORITHMS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class VirtualAlgorithms {
public:
	virtual int check(const std::string& a, const std::string& b) = 0;
};

class LevenshteinAlgorithms : public VirtualAlgorithms {
	int check(const std::string& a, const std::string& b) {
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
};


class CheckAlgorithms {
private:
	std::shared_ptr<VirtualAlgorithms> algorithm;
public:
	void setAlgorithm(std::shared_ptr<VirtualAlgorithms> a) {
		algorithm = a;
	}
	int execute(const std::string& a, const std::string& b) const {
		return algorithm->check(a, b);
	}
};
#endif