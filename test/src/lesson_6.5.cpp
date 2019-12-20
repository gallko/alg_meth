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

TEST(TestCount_less_equal, case_1) {
    std::vector<int> in{1};
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 1), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 2), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), -1), 0);
}
TEST(TestCount_less_equal, case_2) {
    std::vector<int> in{1,5};
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), -1), 0);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 1), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 2), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 5), 2);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 6), 2);
}
TEST(TestCount_less_equal, case_3) {
    std::vector<int> in{1,5,10};
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), -1), 0);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 1), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 2), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 5), 2);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 7), 2);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 10), 3);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 11), 3);
}
TEST(TestCount_less_equal, case_4) {
    std::vector<int> in{1,5,5,10};
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), -1), 0);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 1), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 2), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 5), 3);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 7), 3);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 10), 4);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 11), 4);
}
TEST(TestCount_less_equal, case_5) {
    std::vector<int> in{1,5,5,10,10};
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), -1), 0);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 1), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 2), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 5), 3);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 7), 3);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 10), 5);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 11), 5);
}
TEST(TestCount_less_equal, case_6) {
    std::vector<int> in{0,1,2,3,3,3};
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 1), 2);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 2), 3);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 3), 6);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 4), 6);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 5), 6);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 6), 6);
}
TEST(TestCount_less_equal, case_7) {
    std::vector<int> in{0,7};
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 1, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 6, std::less<int>()), 1);
    EXPECT_EQ(lesson_6_5::count_less_equal(in.begin(), in.end(), 11, std::less<int>()), 2);
}

TEST(TestCount_greate_equal, case_6) {
    std::vector<int> in{0,1,2,3,3,3};
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 1), 5);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 2), 4);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 3), 3);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 4), 0);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 5), 0);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 6), 0);
}
TEST(TestCount_greate_equal, case_1) {
    std::vector<int> in{1};
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 1), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 2), 0);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), -1), 1);
}
TEST(TestCount_greate_equal, case_2) {
    std::vector<int> in{1,5};
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), -1), 2);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 1), 2);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 2), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 5), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 6), 0);
}
TEST(TestCount_greate_equal, case_3) {
    std::vector<int> in{1,5,10};
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), -1), 3);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 1), 3);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 2), 2);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 5), 2);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 7), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 10), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 11), 0);
}
TEST(TestCount_greate_equal, case_4) {
    std::vector<int> in{1,5,5,10};
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), -1), 4);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 1), 4);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 2), 3);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 5), 3);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 7), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 10), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 11), 0);
}
TEST(TestCount_greate_equal, case_5) {
    std::vector<int> in{1,5,5,10,10};
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), -1), 5);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 1), 5);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 2), 4);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 5), 4);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 7), 2);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 10), 2);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 11), 0);
}
TEST(TestCount_greate_equal, case_7) {
    std::vector<int> in{0,7};
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 1), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 6), 1);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 11), 0);
}
TEST(TestCount_greate_equal, case_9) {
    std::vector<int> in{3,3,3,4,5,6};
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 1), 6);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 2), 6);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 3), 6);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 4), 3);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 5), 2);
    EXPECT_EQ(lesson_6_5::count_greater_equal(in.begin(), in.end(), 6), 1);
}


class TestFull: public ::testing::Test {
private:
    std::streambuf *cin_buf;
    std::streambuf *cout_buf;
protected:
    void SetUp() override {
        cin_buf = std::cin.rdbuf();
        cout_buf = std::cout.rdbuf();
    }
    void TearDown() override {
        std::cout.clear();
        std::cin.clear();
        std::cin.rdbuf(cin_buf);
        std::cout.rdbuf(cout_buf);
    }
};

TEST_F(TestFull, test1) {
    std::istringstream iss{"2 3 0 5 7 10 1 6 11"};
    std::cin.rdbuf(iss.rdbuf());

    std::stringstream result_ss;
    std::cout.rdbuf(result_ss.rdbuf());

    lesson_6_5::main_1();

    EXPECT_TRUE(std::cin.eof());
    EXPECT_FALSE(std::cin.fail());
    EXPECT_FALSE(std::cout.fail());
    EXPECT_EQ(result_ss.str(), "1 0 0 ");
}

TEST_F(TestFull, test2) {
    std::istringstream iss{"6 6 0 3 1 3 2 3 3 4 3 5 3 6 1 2 3 4 5 6"};
    std::cin.rdbuf(iss.rdbuf());
    std::stringstream result_ss{};
    std::cout.rdbuf(result_ss.rdbuf());

    lesson_6_5::main_1();

    EXPECT_TRUE(std::cin.eof());
    EXPECT_FALSE(std::cin.fail());
    EXPECT_FALSE(std::cout.fail());
    EXPECT_EQ(result_ss.str(), "2 3 6 3 2 1 ");
}

TEST_F(TestFull, test3) {
    std::istringstream iss{"10 5 \n"
                           "-2 3\n"
                           "0 3\n"
                           "-1 0\n"
                           "-1 3\n"
                           "0 1\n"
                           "-2 -1\n"
                           "1 3\n"
                           "2 3\n"
                           "1 2\n"
                           "2 3\n"
                           "-3 -1 0 2 3"};
    std::cin.rdbuf(iss.rdbuf());
    std::stringstream result_ss{};
    std::cout.rdbuf(result_ss.rdbuf());

    lesson_6_5::main_1();

    EXPECT_TRUE(std::cin.eof());
    EXPECT_FALSE(std::cin.fail());
    EXPECT_FALSE(std::cout.fail());
    EXPECT_EQ(result_ss.str(), "0 4 5 7 6 ");
}
