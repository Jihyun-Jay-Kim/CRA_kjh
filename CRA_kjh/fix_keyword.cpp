#include "gmock/gmock.h"
#include "IOManager.cpp"

int main() {
	IOManager iomgr;
	iomgr.execute("keyword_weekday_500.txt");
	//testing::InitGoogleMock();
	//return RUN_ALL_TESTS();
}
