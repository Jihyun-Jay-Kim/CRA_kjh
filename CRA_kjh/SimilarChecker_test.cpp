#include "gmock/gmock.h"
#include "SimilarChecker.cpp"


TEST(Group, TC3) {

	CheckAlgorithms checkAlgorithms;
	checkAlgorithms.setAlgorithm(std::make_shared<LevenshteinAlgorithms>());
	SimilarChecker similarChecker = SimilarChecker(80, checkAlgorithms);

	EXPECT_EQ(true, similarChecker.similar("AAA","AAA"));
}

TEST(Group, TC4) {

	CheckAlgorithms checkAlgorithms;
	checkAlgorithms.setAlgorithm(std::make_shared<LevenshteinAlgorithms>());
	SimilarChecker similarChecker = SimilarChecker(80, checkAlgorithms);

	EXPECT_EQ(false, similarChecker.similar("AAA", "BBB"));
}

