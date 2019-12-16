#include <gtest/gtest.h>
#include <algorithm>
#include <functional>
#include "sequences.h"
#include "../../src/utils.h"
#include "../../src/lesson_6.5.h"


class TestQuickSort: public ::testing::Test
{
public:
    static std::vector<std::vector<int>> increasing;
    static std::vector<std::vector<int>> decreasing;
    static void SetUpTestSuite() {
        std::cout << std::endl << std::endl << "SetUpTestSuite" << std::endl;
        for(auto &line: increasing) {
            std::sort(line.begin(), line.end(), std::less<int>());
        }
        for(auto &line: decreasing) {
            std::sort(line.begin(), line.end(), std::greater<int>());
        }
    }
};
std::vector<std::vector<int>> TestQuickSort::increasing = sequences::sequence;
std::vector<std::vector<int>> TestQuickSort::decreasing = sequences::sequence;

TEST_F(TestQuickSort, increasing) {
    for(size_t i = 0; i < increasing.size(); ++i) {
        auto tmp(sequences::sequence[i]);
        lesson_6_5::quick_sort(tmp, [](int p1, int p2){
            if (p1 == p2) return 0;
            if (p1 > p2) return 1;
            return -1;
        });
        EXPECT_EQ(tmp, increasing[i]);
    }
}

TEST_F(TestQuickSort, decreasing) {
    for(size_t i = 0; i < decreasing.size(); ++i) {
        auto tmp(sequences::sequence[i]);
        lesson_6_5::quick_sort(tmp, [](int p1, int p2){
            if (p1 == p2) return 0;
            if (p1 < p2) return 1;
            return -1;
        });
        EXPECT_EQ(tmp, decreasing[i]);
    }
}

TEST(TestCountIfIncrease, vector_1) {
    std::vector<int> in{1};
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 1, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 2, std::less<int>()), 0);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), -1, std::less<int>()), 1);
}
TEST(TestCountIfIncrease, vector_2) {
    std::vector<int> in{1,5};
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 1, std::less<int>()), 2);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 2, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 5, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), -1, std::less<int>()), 2);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 6, std::less<int>()), 0);
}
TEST(TestCountIfIncrease, vector_3) {
    std::vector<int> in{1,5,10};
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), -1, std::less<int>()), 3);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 1, std::less<int>()), 3);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 2, std::less<int>()), 2);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 5, std::less<int>()), 2);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 7, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 10, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 11, std::less<int>()), 0);
}
TEST(TestCountIfIncrease, vector_3_dublicate) {
    std::vector<int> in{1,5,5,10};
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), -1, std::less<int>()), 4);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 1, std::less<int>()), 4);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 2, std::less<int>()), 3);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 5, std::less<int>()), 3);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 7, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 10, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 11, std::less<int>()), 0);
}
TEST(TestCountIfIncrease, vector_5_dublicate) {
    std::vector<int> in{1,5,5,10,10};
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), -1, std::less<int>()), 5);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 1, std::less<int>()), 5);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 2, std::less<int>()), 4);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 5, std::less<int>()), 4);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 7, std::less<int>()), 2);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 10, std::less<int>()), 2);
    EXPECT_EQ(lesson_6_5::count_if(in.begin(), in.end(), 11, std::less<int>()), 0);
}

