#include <gtest/gtest.h>
#include <Helo.h>

class DummyTest : public ::testing::Test {
	
};

TEST_F(DummyTest, Equals) {
	say_helo();
	EXPECT_EQ(1, 1);
}
