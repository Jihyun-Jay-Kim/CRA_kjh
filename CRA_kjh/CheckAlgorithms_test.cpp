#include "gmock/gmock.h"
#include "CheckAlgorithms.cpp"

TEST(Group, TC1) {

	CheckAlgorithms checkAlgorithms;
	checkAlgorithms.setAlgorithm(std::make_shared<LevenshteinAlgorithms>());

	int dist = checkAlgorithms.execute("AAA", "AAA");

	EXPECT_EQ(0, dist);
}

TEST(Group, TC2) {

	CheckAlgorithms checkAlgorithms;
	checkAlgorithms.setAlgorithm(std::make_shared<LevenshteinAlgorithms>());

	int dist = checkAlgorithms.execute("AAA", "BBB");

	EXPECT_EQ(3, dist);
}