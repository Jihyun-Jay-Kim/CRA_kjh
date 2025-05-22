#include "gmock/gmock.h"
#include "SearchManager.cpp"

using namespace testing;

class SearchManagerTest : public Test {
protected:
	SearchManager obj;
};

TEST(Group, TC5) {

	SearchManager searchManager;
	SearchNode searchNode = { "water" ,"monday" };

	for (int i = 0; i < 10; i++) {
		searchManager.search(searchNode);
	}
	searchNode = { "weter" ,"monday" };
	searchManager.search(searchNode);
	searchNode = { "wwwww" ,"monday" };
	string result = searchManager.search(searchNode);

	EXPECT_EQ("wwwww", result);
}

TEST(Group, TC6) {

	SearchManager searchManager;
	SearchNode searchNode = { "water" ,"monday" };

	for (int i = 0; i < 10; i++) {
		searchManager.search(searchNode);
	}
	searchNode = { "weter" ,"tuesday" };
	searchManager.search(searchNode);
	searchNode = { "wwwww" ,"tuesday" };
	string result = searchManager.search(searchNode);

	EXPECT_EQ("wwwww", result);
}

TEST(Group, TC7) {

	SearchManager searchManager;
	SearchNode searchNode = { "water" ,"sunday" };

	for (int i = 0; i < 10; i++) {
		searchManager.search(searchNode);
	}
	searchNode = { "weter" ,"sunday" };
	searchManager.search(searchNode);
	searchNode = { "wwwww" ,"sunday" };
	string result = searchManager.search(searchNode);

	EXPECT_EQ("wwwww", result);
}

TEST(Group, TC8) {

	SearchManager searchManager;
	SearchNode searchNode = { "water" ,"saturday" };

	for (int i = 0; i < 10; i++) {
		searchManager.search(searchNode);
	}
	searchNode = { "weter" ,"sunday" };
	searchManager.search(searchNode);
	searchNode = { "wwwww" ,"sunday" };
	string result = searchManager.search(searchNode);

	EXPECT_EQ("wwwww", result);
}

TEST(Group, TC9) {
	SearchManager searchManager;
	string keywordArr[10] = { "water", "bread", "potato", "light", "shrimp",
								"pepper", "music", "pizza", "coke", "samsung" };
	SearchNode searchNode = { "water" ,"sunday" };

	for (int i = 0; i < 10; i++) {
		searchNode.keyword = keywordArr[i];
		searchManager.search(searchNode);
	}
	searchNode = { "juice" ,"sunday" };
	searchManager.search(searchNode);
	searchNode = { "drink" ,"sunday" };
	string result = searchManager.search(searchNode);

	EXPECT_EQ("drink", result);
}


TEST_F(SearchManagerTest, TestSetSecret) {
	SearchNode searchNode = { "water" ,"saturday" };

	for (int i = 0; i < 10; i++) {
		obj.search(searchNode);
	}
	obj.UZ = 2100000000;

	searchNode = { "drink" ,"sunday" };
	string result = obj.search(searchNode);

	EXPECT_EQ(10, obj.UZ);
	EXPECT_EQ("drink", result);
}