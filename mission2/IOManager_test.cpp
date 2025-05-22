#include "gmock/gmock.h"
#include "IOManager.cpp"

using namespace testing;

TEST(Group, TC10) {
	const char* tmp = "temp.txt";
	std::ofstream out(tmp);
	out << "hello monday\n";
	out.close();

	IOManager iomgr;

	internal::CaptureStdout();
	iomgr.execute(tmp);
	EXPECT_EQ("hello\nhello\n", internal::GetCapturedStdout());
}

TEST(Group, TC11) {
	const char* tmp = "temp3.txt";

	IOManager iomgr;
	
	EXPECT_THROW(iomgr.execute(tmp), std::runtime_error);
}
