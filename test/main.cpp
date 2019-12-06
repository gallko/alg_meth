#include <gtest/gtest.h>

TEST(blaTest, test1) {
    EXPECT_EQ(0,  0) << "Ups...";
    EXPECT_EQ (0,  0);
}

TEST(blaTest, test2) {
    EXPECT_EQ (0,  0);
    EXPECT_EQ (0,  0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}